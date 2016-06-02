//
// Created by Sashank on 3/26/2016.
//
#include <cstring>
#include "Camera.h"
#include "../Image/CreateImage.h"

Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint) {
    this->position = position;
    Vector3D differenceBetweenImageAndCamera = lookAtPoint - position;       //The difference between the camera and the point where we want to look
    bool cameraIsLookingFromTop = (position.getX() == 0 && position.getZ() == 0 && position.getY() != 0);

    // CREATE A VIRTUAL COORDINATE SYSTEM FOR THE CAMERA. IN ORTHONORMAL BASIS
    w = differenceBetweenImageAndCamera.unitVector();                           //Normalize the difference and make it positive by multiplying with -1
    u = !cameraIsLookingFromTop ? CrossProduct(Vector3D(0,1,0),w).unitVector() : CrossProduct(Vector3D(-1,0,0),w).unitVector();
    v = CrossProduct(w, u);
    fov = 52.0;
    useSampling(SamplingTypes::RANDOM, 1);
    depthOfFieldEnabled = false;
}

Camera::Camera(const Vector3D &position, const Vector3D &lookAtPoint, double fov):
    Camera(position, lookAtPoint) {
        this->fov = fov;
    }

Vector3D Camera::convertCameraToWorldCoordinates(const Vector3D &point) {
    return ((point.getX() * u + (point.getY() * v) + (point.getZ() * w)));
}

void Camera::render(const int width, const int height, std::vector<std::shared_ptr<Shape>> shapes, std::vector<std::shared_ptr<Light>> lights) {
    std::cout << "Rendering scene with "<< shapes.size() << " objects..." << std::endl;
    std::cout << "Please wait." << std::endl;

    heightOfScene = height;
    widthOfScene = width;
    this->shapes = shapes;
    this->lights = lights;
    
    int resolution = width * height;
    ColorRGB *pixels = new ColorRGB[resolution];
    long loopCounter = 0;
    
    std::vector<double> combinationsOfOffSets;
    if (typeOfSampling == SamplingTypes::JITTERED){
        for (int index = 0; index < numberOfSamples; index++){
            combinationsOfOffSets.emplace_back((double)(2 * index + 1) / (2 * numberOfSamples));
        }
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            pixels[loopCounter] = getFinalColorFromSampling(i, j, combinationsOfOffSets);
            loopCounter++;
        }
    }
    CreateImage::createRasterImage(height, width, "RenderedImage.bmp", pixels);
    std::cout << "Done rendering." <<std::endl;
    std::cout << "Rendered Image Size: " << width << " x " << height<< std::endl;
    delete [] pixels;
}

ColorRGB Camera::getFinalColorFromSampling(int i, int j, std::vector<double> combinationsOfOffsets){
    ColorRGB finalColor = ColorRGB(0,0,0,0);
    double wCamDir = depthOfFieldEnabled ? focalLength : 1;
    double pixelSize =  tan(Algebra::deg2rad(fov * 0.5)) * wCamDir / (heightOfScene/2);

    double uOffset = 0;
    double vOffset = 0;

    for (int multiSamplingLoopIndex = 0 ; multiSamplingLoopIndex < numberOfSamples; multiSamplingLoopIndex++) {

        if (typeOfSampling == JITTERED) {
            uOffset = combinationsOfOffsets[multiSamplingLoopIndex % numberOfSamples];
            vOffset = combinationsOfOffsets[multiSamplingLoopIndex / numberOfSamples];
        } else {
            double randomNumber = Algebra::getRandomBetween(0,1);
            uOffset = randomNumber;
            vOffset = randomNumber;
        }

        double uCamDir = ((i - (widthOfScene / 2)) + (numberOfSamples == 1 ? 0.5 : uOffset)) * pixelSize;
        double vCamDir = (((heightOfScene / 2) - j) + (numberOfSamples == 1 ? 0.5 : vOffset)) * pixelSize;

        //Also randomize origin if depth of field has been used
        Vector3D camRayOrigin = !depthOfFieldEnabled ? Vector3D() : randomizeOriginXY();
        Vector3D camRayDirection = Vector3D (uCamDir, vCamDir, wCamDir) - camRayOrigin;

        // Convert both origin and direction to world coordinates
        camRayDirection = convertCameraToWorldCoordinates(camRayDirection).unitVector();
        camRayOrigin = convertCameraToWorldCoordinates(camRayOrigin) + getCameraPosition();

        Ray r(camRayOrigin, camRayDirection);
        finalColor = finalColor + getColorFromRay(r, 1);
    }
    return finalColor / numberOfSamples;
}

ColorRGB Camera::getColorFromRay(const Ray &r, int depth){

    if (depth == MAX_TRACE_DEPTH){
        return ColorRGB(0,0,0,0);
    }
    // Render all objects that are inside the shape container
    // If more than one object is hit, the one with the intersection point closer to the observer commands the pixel color,
    int numberOfObjectsToRender = (int) shapes.size();
    int lowestTposition = 0;

    double leastValueOfT = 100000000;
    Ray intersectingTransformedRay = r;
    for (int l = 0; l < numberOfObjectsToRender; ++l) {
        //Move the ray from world space to object space
        Vector3D newRayOrigin = transformPoint(shapes[l]->getInverseTransformationMatrix(), r.getOrigin());
        Vector3D newRayDirection = transformDirection(shapes[l]->getInverseTransformationMatrix(), r.getDirection());
        Ray newRay(newRayOrigin, newRayDirection);
        double intersectionDistance = shapes[l]->rayIntersectionDistance(newRay);
        if (intersectionDistance > 0.000001 && intersectionDistance < leastValueOfT) {  //0.000001 for accuracy purpose
            leastValueOfT = intersectionDistance;
            lowestTposition = l;
            intersectingTransformedRay = newRay;
        }
    }

    if ( leastValueOfT < 100000000) {
        Vector3D intersectingPosition = intersectingTransformedRay.getOrigin() + leastValueOfT * intersectingTransformedRay.getDirection();
        //find P in world-coordinate space
        Vector3D realIntersectingPosition = transformPoint(shapes[lowestTposition]->getTransformationMatrix(), intersectingPosition);
        return getColorAt(realIntersectingPosition, lowestTposition, depth) / (depth);
    }
    return ColorRGB();
}

ColorRGB Camera::getColorAt(const Vector3D &intersectionPosition, int indexOfIntersectionPosition, int depth) {

    //Base case
    if (depth == MAX_TRACE_DEPTH)
        return ColorRGB(0,0,0,0);

    ColorRGB finalColor(0,0,0,0);
    ColorRGB colorOfObject = shapes[indexOfIntersectionPosition]->getMaterial().getColor();
    for (int i = 0; i < lights.size(); i++) {
        bool isShadowed = false;
        double distanceBetweenLightAndObject = 10000000000;
        if (lights[i]->getLightType() == TypesOfLight::POINTLIGHT)
            distanceBetweenLightAndObject = std::abs((lights[i]->getLightPosition() - intersectionPosition).magnitude());
        Vector3D directionOfLight = lights[i]->getLightDirection(intersectionPosition);

        for (int j = 0; j < shapes.size(); j++){
            // /calculate shadows
            Vector3D newIntersectionPosition = transformPoint(shapes[j]->getInverseTransformationMatrix(), intersectionPosition);
            Vector3D newDirection = transformDirection(shapes[j]->getInverseTransformationMatrix(), directionOfLight);

            Ray shadowRay(newIntersectionPosition, newDirection);
            if (j == indexOfIntersectionPosition) continue;                             // Ignore what happens later because we do not want the shape to cast shadow onto itself
            double t = shapes[j]->rayIntersectionDistance(shadowRay);
            if (t > 0.000001 && distanceBetweenLightAndObject >= t){
                isShadowed = true;
                break;
            }
            isShadowed = false;
        }
        if (isShadowed) continue;                                   // Check if the other light falls on the currently shadowed reason
                                                                    // , in which case I'd not want a shadow

        Vector3D intersectionPositionInIntersectedObjectSpace = transformPoint(shapes[indexOfIntersectionPosition]->getInverseTransformationMatrix(),
                                                                               intersectionPosition);
        Vector3D normalAtIntersectionPosition = transformDirection(shapes[indexOfIntersectionPosition]->getInverseTransformationMatrix().transposeMatrix(),
                                                                   shapes[indexOfIntersectionPosition]->getNormalAt(intersectionPositionInIntersectedObjectSpace));
        ColorRGB colorOfCurrentLight = lights[i]->getColorOfLight();
        double intensityOfCurrentLight = lights[i]->getLightIntensity();

        //SPECULAR SHADING
        Vector3D vertexToEye = (getCameraPosition() - intersectionPosition).unitVector();
        Vector3D reflectedLightDir = getReflectedLightDirection(normalAtIntersectionPosition, -directionOfLight);
        double specularFactor = DotProduct(vertexToEye, reflectedLightDir);
        if (specularFactor < 0) {
            specularFactor = 0;
        }

        //Specular power is about how big the specular reflection is
        specularFactor = pow(specularFactor, shapes[indexOfIntersectionPosition]->getMaterial().getSpecularPower());
        specularFactor *= shapes[indexOfIntersectionPosition]->getMaterial().getSpecularCoeff();


        //DIFFUSE SHADING
        double diffuseFactor = DotProduct(normalAtIntersectionPosition, directionOfLight);
        if (diffuseFactor < 0) {
            diffuseFactor = 0;
        }
        diffuseFactor *= shapes[indexOfIntersectionPosition]->getMaterial().getDiffuseCoefficient();

        double sumOfFactors = diffuseFactor + specularFactor;

        if (sumOfFactors + shapes[indexOfIntersectionPosition]->getMaterial().getAmbience() > 1)
            sumOfFactors = 1;

        //REFLECTION
        ColorRGB reflectedRayColor;
        if (shapes[indexOfIntersectionPosition]->getMaterial().isReflective && depth < MAX_TRACE_DEPTH) {
            Ray reflectedRay(intersectionPosition, reflectedLightDir);
            reflectedRayColor = getColorFromRay(reflectedRay, depth + 1);
        }

        finalColor = finalColor + shapes[indexOfIntersectionPosition]->getMaterial().getReflectivity() * reflectedRayColor + (sumOfFactors * intensityOfCurrentLight * colorOfObject  * colorOfCurrentLight);
    }
    return  finalColor + shapes[indexOfIntersectionPosition]->getMaterial().getAmbience() * colorOfObject;
}

Vector3D Camera::transformPoint(const Matrix4x4 &tm, const Vector3D &point) {
    Vector4D pointIn4D = Vector4D(point.getX(), point.getY(), point.getZ(), 1);
    Vector4D transformedPoint = tm * pointIn4D;
    return Vector3D(transformedPoint.getX(), transformedPoint.getY(), transformedPoint.getZ());
}

Vector3D Camera::transformDirection(const Matrix4x4 &tm, const Vector3D &direction) {
    Vector4D directionIn4D = Vector4D(direction.getX(), direction.getY(),direction.getZ(), 0);
    Vector4D transformedPoint = tm * directionIn4D;
    return Vector3D(transformedPoint.getX(), transformedPoint.getY(), transformedPoint.getZ()).unitVector();
}

Vector3D Camera::getCameraPosition() {
    return position;
}

void Camera::useSampling(SamplingTypes typeOfSampling, int numberOfSamples) {
    this->typeOfSampling = typeOfSampling;
    this->numberOfSamples = typeOfSampling == JITTERED ? numberOfSamples * numberOfSamples : numberOfSamples;
}

void Camera::useDepthOfField(double apertureSize, const Vector3D& focalPoint) {
    apertureRadius = apertureSize;
    focalLength = (focalPoint - getCameraPosition()).magnitude();
    depthOfFieldEnabled = true;
}

Vector3D Camera::randomizeOriginXY() {
    // Use polar coordinates to convert from (radius, angle) to cartesian coordinates
    const float PI = 3.1415926535f;
    double cosineOfRandomAngle = cos(Algebra::getRandomBetween(0, 2 * PI));
    double sineOfRandomAngle = sin(Algebra::getRandomBetween(0, 2 * PI));
    double randomRadius = Algebra::getRandomBetween(0, apertureRadius);

    double xComponent = randomRadius * cosineOfRandomAngle;
    double yComponent = randomRadius * sineOfRandomAngle;
    return Vector3D(xComponent, yComponent, 0);
}

Vector3D Camera::getReflectedLightDirection(const Vector3D & normal, const Vector3D & incidentLightDirection) {
    return (incidentLightDirection  - 2 * DotProduct(normal, incidentLightDirection) * normal).unitVector();
}

void Camera::setMaxDepth(int maxDepth) {
    this->MAX_TRACE_DEPTH = maxDepth;
}