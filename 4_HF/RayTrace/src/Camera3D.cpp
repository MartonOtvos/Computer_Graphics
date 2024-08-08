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

    vec3 p = lookat + ( ( 2 * ((float) X + 0.5f ) ) / windowWidth - 1 ) * right + ( ( 2 * ((float) Y + 0.5f ) ) / windowHeight - 1 ) * up;
    vec3 dir = normalize(p - eye);

    return Ray(eye, dir, true);
}

void Camera3D::Animate(float dt) {
    // Calculate the angle increment (45 degrees or π/4 radians)
    float angleIncrement = M_PI / -4.0f; // 45 degrees in radians

    // Calculate the current distance from the lookat point to the eye position in the xz-plane
    float distance = sqrt(pow(eye.x - lookat.x, 2) + pow(eye.z - lookat.z, 2));

    // Calculate the current angle of the eye position relative to the lookat point
    float currentAngle = atan2(eye.z - lookat.z, eye.x - lookat.x);

    // Increment the current angle by 45 degrees
    float newAngle = currentAngle + angleIncrement;

    // Update the eye position based on the new angle
    eye.x = lookat.x + distance * cos(newAngle);
    eye.z = lookat.z + distance * sin(newAngle);

    // Set the new camera parameters
    Set(eye, lookat, vec3(0,1,0), fov);

}
