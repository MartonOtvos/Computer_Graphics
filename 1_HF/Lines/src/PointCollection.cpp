//
// Created by Marci on 5/26/2024.
//

#include "PointCollection.h"

vec2 PointCollection::FindPoint(vec2 coords) {
    for(auto vertex : vertices){
        if(length(vertex - coords) < 0.01) return vertex;
    }
    return {NAN,NAN};
}

void PointCollection::CreatePoint(vec2 coords) {
    AddVtx(coords);
    printf("Point (%.2f, %.2f) added",coords.x,coords.y);
}

void PointCollection::Draw() {
    Object::Draw(GL_POINTS,vec3(1,0,0));
}

PointCollection::PointCollection(unsigned int shader) : Object(shader) {}
