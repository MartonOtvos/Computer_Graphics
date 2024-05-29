//
// Created by Marci on 5/28/2024.
//

#ifndef GRAPHICS_PARAMETRICCURVE_H
#define GRAPHICS_PARAMETRICCURVE_H
using namespace std;
#include "framework.h"

class ParametricCurve {
    unsigned int vao, vbo1, vbo2;
    unsigned int shaderProgram;
    vector<vec2> vertices;

    void UpdateGeometry();
    void UpdateGPU();
    virtual vec2 r(float t) = 0;

protected:
    vector<vec2> cps;
    vector<float> ts;
    float tension;
public:
    ParametricCurve(unsigned int shader);
    void AddControlPoint(vec2 coords);
    void AlterControlPoint(int index, vec2 coords);
    void AlterTension(float d);
    unsigned int PickControlPoint(vec2 coords);

    virtual void Draw(mat4 V, mat4 P);
};


#endif //GRAPHICS_PARAMETRICCURVE_H
