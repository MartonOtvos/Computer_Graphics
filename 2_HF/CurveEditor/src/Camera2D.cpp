//
// Created by Marci on 5/28/2024.
//

#include "Camera2D.h"

Camera2D::Camera2D(vec2 size, vec2 center) {
    this->size=size;
    this->center = center;
}

mat4 Camera2D::View() {
    return TranslateMatrix(-center);
}

mat4 Camera2D::Projection() {
    return ScaleMatrix(vec2(2/size.x,2/size.y));
}

mat4 Camera2D::InverseView() {
    return TranslateMatrix(vec3(center.x,center.y,1));
}

mat4 Camera2D::InverseProjection() {
    return ScaleMatrix(vec2(size.x/2,size.y/2));
}

void Camera2D::Zoom(float d) {
    size = size * d;
}

void Camera2D::Pan(float d) {
    center.x = center.x + d;
}
