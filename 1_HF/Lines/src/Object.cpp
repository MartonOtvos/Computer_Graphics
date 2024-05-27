#include "Object.h"



Object::Object(unsigned int shader) : shaderProgram(shader), vertices() {

    glCreateVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glCreateBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
}

void Object::Update() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Object::AddVtx(vec2 vtx) {
    vertices.push_back(vtx);
    Update();
}

void Object::clearVtxs() {
    vertices.clear();
    Update();
}

void Object::Draw(int primitive, vec3 color) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    int location = glGetUniformLocation(shaderProgram,"color");
    glUniform3f(location,color.x,color.y,color.z);

    location = glGetUniformLocation(shaderProgram,"MVP");

    float MVP[4][4] = {{1, 0, 0, 0},
                       {0, 1, 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}};

    glUniformMatrix4fv(location,1,GL_TRUE,&MVP[0][0]);

    glDrawArrays(primitive,0,vertices.size());
}
