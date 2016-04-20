cmake_minimum_required(VERSION 3.3)
project(RaytracerC__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Color/Color.h Image/CreateImage.cpp Image/CreateImage.h EasyBMP/EasyBMP.h EasyBMP/EasyBMP.cpp EasyBMP/EasyBMP_BMP.h
        EasyBMP/EasyBMP_DataStructures.h EasyBMP/EasyBMP_VariousBMPutilities.h
        Vector3D/Vector3D.cpp Vector3D/Vector3D.h
       Ray/Ray.h Camera/Camera.h Shapes/Shape.h Shapes/Sphere/Sphere.cpp Shapes/Sphere/Sphere.h Scene/Scene.cpp Scene/Scene.h Lights/Light.h Shapes/Plane/Plane.cpp Shapes/Plane/Plane.h Point3D/Point3D.h Algebra/Algebra.cpp Algebra/Algebra.h Shapes/Disk/Disk.cpp Shapes/Disk/Disk.h Shapes/Box/Box.cpp Shapes/Box/Box.h Camera/Camera.cpp Shapes/Triangle/Triangle.cpp Shapes/Triangle/Triangle.h Algebra/Matrix.cpp Algebra/Matrix.h)
add_executable(RaytracerC__ ${SOURCE_FILES})