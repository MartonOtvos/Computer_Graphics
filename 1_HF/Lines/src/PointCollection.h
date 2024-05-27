//
// Created by Marci on 5/26/2024.
//

#ifndef GRAPHICS_POINTCOLLECTION_H
#define GRAPHICS_POINTCOLLECTION_H


#include "Object.h"

class PointCollection : Object {

public:
    explicit PointCollection(unsigned int shader);
    void CreatePoint(vec2 coords);
    vec2 FindPoint(vec2 coords);
    void Draw();
};


#endif //GRAPHICS_POINTCOLLECTION_H
