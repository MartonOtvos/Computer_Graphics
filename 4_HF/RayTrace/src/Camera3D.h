//
// Created by Marci on 6/1/2024.
//

#ifndef GRAPHICS_CAMERA3D_H
#define GRAPHICS_CAMERA3D_H

#include "RayTraceFramework.h"

class Camera3D {
    vec3 eye, lookat, right, up;
    float fov;
public:
    void Set(vec3 _eye, vec3 _lookat, vec3 vup, float _fov);
    Ray GetRay(int X, int Y);
    void Animate(float dt);
};


#endif //GRAPHICS_CAMERA3D_H
