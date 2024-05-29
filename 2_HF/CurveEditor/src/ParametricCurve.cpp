//
// Created by Marci on 5/28/2024.
//

#include "ParametricCurve.h"

void ParametricCurve::UpdateGeometry() {
    ts.clear();
    vertices.clear();
    //Populate ts
    for(size_t i = 0; i < cps.size(); i++){
        if(cps.size() != 1){
            float ti = (float) i/((float) cps.size()-1);
            ts.push_back(ti);
        }else{
            ts.push_back(0);
        }
    }
    //Populate vertices
    if(cps.size() > 1){
        float t = 0;
        for(int i = 0; i < 1000; i++){
            if(t > 1) t = 1;
            vertices.push_back(r(t));
            t += (float) 1/999;
        }
    }
    //Upload to GPU
    UpdateGPU();
}

void ParametricCurve::UpdateGPU() {
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo1);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER,vbo2);

    glBufferData(GL_ARRAY_BUFFER, cps.size() * sizeof(vec2), &cps[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

ParametricCurve::ParametricCurve(unsigned int shader) : shaderProgram(shader), tension(0) {
    glCreateVertexArrays(1,&vao);
    glBindVertexArray(vao);

    //Curve Line Strip VBO
    glCreateBuffers(1,&vbo1);
    glBindBuffer(GL_ARRAY_BUFFER,vbo1);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    //Control Point VBO
    glCreateBuffers(1,&vbo2);
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glBufferData(GL_ARRAY_BUFFER, cps.size() * sizeof(vec2), &cps[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void ParametricCurve::AddControlPoint(vec2 coords) {
    cps.push_back(coords);
    UpdateGeometry();
}

void ParametricCurve::AlterControlPoint(int index, vec2 coords) {
    if(index == -1) return;
    cps.at(index) = coords;
    UpdateGeometry();
}

void ParametricCurve::Draw(mat4 V, mat4 P) {


    glBindVertexArray(vao);
    unsigned int location = glGetUniformLocation(shaderProgram,"MVP");
    mat4 M = {1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1};
    mat4 MVP = M * V * P;
    glUniformMatrix4fv(location, 1, GL_TRUE, &MVP[0][0]);

    location = glGetUniformLocation(shaderProgram,"color");

    glUniform3f(location,1,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glDrawArrays(GL_POINTS, 0, cps.size());

    if(cps.size() >= 2){
        glUniform3f(location,1,1,0);

        glBindBuffer(GL_ARRAY_BUFFER,vbo1);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    }


}

void ParametricCurve::AlterTension(float d) {
    tension += d;
    UpdateGeometry();
}

unsigned int ParametricCurve::PickControlPoint(vec2 coords) {
    for(unsigned int i = 0; i < cps.size(); i++){
        if(length(coords-cps.at(i)) < 0.3) return i;
    }
    return -1;
}
