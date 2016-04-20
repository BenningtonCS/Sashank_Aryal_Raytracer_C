
# Raytracer in C++

#This document is a WIP

This document is still a work in progress. 


### Update 0.1
*So far, this raytracer has the following abilities:*

1. You can add shapes like spheres, Axis Aligned Bounding Boxes(AABBs), discs or planes in your scene. Add a new object in **initializeObjects()** method inside **main.cpp**.

2. You can add two types of lights, point lights and directional lights. You can have as many lights as you want in the scene. Add a new light in **initializeLights()** method inside **main.cpp**.

3. The camera is modeled as a perspective camera, so you can change its **position** and **lookat**.

4. Anti-aliasing is disabled by default. To enable anti-aliasing, use **useSampling** method of the **Camera** class. 
