//
// Created by Marci on 5/27/2024.
//

#ifndef GRAPHICS_LINECOLLECTION_H
#define GRAPHICS_LINECOLLECTION_H

#include "Object.h"
#include "Line.h"

using namespace std;

class LineCollection : Object{
    vector<Line*> lines;

public:
    LineCollection(unsigned int shader);
    void CreateLine(vec2 coords1, vec2 coords2);
    Line* FindLine(vec2 coords);
    void UpdateLines();
    void Draw();
};


#endif //GRAPHICS_LINECOLLECTION_H
