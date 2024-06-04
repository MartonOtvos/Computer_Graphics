//
// Created by Marci on 6/1/2024.
//

#include "Camera3D.h"

void Camera3D::Set(vec3 _eye, vec3 _lookat, vec3 vup, float _fov) {
    eye = _eye;
    lookat = _lookat;
    fov = _fov;
    vec3 w = eye - lookat;
    float windowSize = length(w) * tanf(fov/2);
    right = normalize(cross(vup,w)) * windowSize;
    up = normalize(cross(w,right)) * windowSize;
}

Ray Camera3D::GetRay(int X, int Y) {

    vec3 p = lookat + ( ( 2 * ( X + 0.5f ) ) / windowWidth - 1 ) * right + ( ( 2 * ( Y + 0.5f ) ) / windowHeight - 1 ) * up;
    vec3 dir = p - eye;

    return Ray(eye, dir, false);
}

void Camera3D::Animate(float dt) {


}
