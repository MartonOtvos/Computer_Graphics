//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H
#include "RayTraceFramework.h"
#include "Camera3D.h"

using namespace std;

class Scene {
    vec3 La;
    Camera3D camera;
    vector<Intersectable*> objects;
    vector<DirectionalLight*> lights;
    vec3 Trace(Ray ray, int depth);
    Hit FirstIntersect(Ray ray);
    vec3 DirectLight(Hit hit);

public:
    Scene();
    void Build();
    vector<vec4> Render();



};


#endif //GRAPHICS_SCENE_H
