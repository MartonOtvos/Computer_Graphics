//
// Created by Marci on 5/27/2024.
//

#include "LineCollection.h"

LineCollection::LineCollection(unsigned int shader) : Object(shader) {

}

void LineCollection::CreateLine(vec2 coords1, vec2 coords2) {
    Line* l = new Line(coords1, coords2);
    lines.push_back(l);
    vec4 ends = l->generateEnds();
    Object::AddVtx(vec2(ends.x,ends.y));
    Object::AddVtx(vec2(ends.z,ends.w));
}

Line* LineCollection::FindLine(vec2 coords) {
    for(size_t i = 0; i < lines.size(); i++){
        if(lines.at(i)->IsClose(coords)){
            return lines.at(i);
        }
    }
    return nullptr;
}


void LineCollection::Draw() {
    Object::Draw(GL_LINES,vec3(0,1,1));
}

void LineCollection::UpdateLines() {
    Object::clearVtxs();
    for(size_t i = 0; i < lines.size(); i++){
        vec4 ends = lines.at(i)->generateEnds();
        Object::AddVtx(vec2(ends.x,ends.y));
        Object::AddVtx(vec2(ends.z,ends.w));
    }
    Object::Update();
}
