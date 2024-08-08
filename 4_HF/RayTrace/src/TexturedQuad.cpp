//
// Created by Marci on 6/1/2024.
//

#include "TexturedQuad.h"

TexturedQuad::TexturedQuad(unsigned int shader) : shaderProgram(shader) {
    glCreateVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glCreateBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    vertices[0] = {-1,-1};
    vertices[1] = {-1,1};
    vertices[2] = {1,1};
    vertices[3] = {1,-1};

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec2), vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    uvs[0] = {0,0};
    uvs[1] = {0,1};
    uvs[2] = {1,1};
    uvs[3] = {1,0};

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec2), uvs, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
}

void TexturedQuad::Draw(vector<vec4> image) {


    mat4 MVP = RotationMatrix(0,1);

    unsigned int location = glGetUniformLocation(shaderProgram,"MVP");
    glUniformMatrix4fv(location, 1, GL_TRUE, &MVP[0][0]);

    int sampler = 0;
    location = glGetUniformLocation(shaderProgram,"samplerUnit");
    glUniform1i(location,sampler);

    glActiveTexture(GL_TEXTURE0 + sampler);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, &image[0]);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLE_FAN,0,4);

}
