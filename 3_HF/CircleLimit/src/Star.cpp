//
// Created by Marci on 5/30/2024.
//

#include "Star.h"

Star::Star(unsigned int shader) : shaderProgram(shader) {
    glCreateVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glCreateBuffers(2,vbo);

    vertices = {
            {0.0f, 0.0f},
            {0.0f, -schlank/75.0f},
            {-40.0f/75.0f, -40.0f/75.0f},
            {-schlank/75.0f, 0.0f},
            {-40.0f/75.0f, 40.0f/75.0f},
            {0.0f, schlank/75.0f},
            {40.0f/75.0f, 40.0f/75.0f},
            {schlank/75.0f, 0.0f},
            {40.0f/75.0f, -40.0f/75.0f},
            {0.0f, -schlank/75.0f}
    };

    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    uvs.emplace_back(0.5,0.5);
    uvs.emplace_back(0.5,0);
    uvs.emplace_back(0,0);
    uvs.emplace_back(0,0.5);
    uvs.emplace_back(0,1);
    uvs.emplace_back(0.5,1);
    uvs.emplace_back(1,1);
    uvs.emplace_back(1,0.5);
    uvs.emplace_back(1,0);
    uvs.emplace_back(0.5,0);

    glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    textureGenerator = new ProceduralCircleLimitTexture();
    vector<vec4> image = textureGenerator->renderToTexture(resolution);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolution, resolution, 0, GL_RGBA, GL_FLOAT, &image[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

}

void Star::AlterTextureSamplingMode(unsigned int mode) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,mode);
}

void Star::AlterTextureResolution(int d) {
    resolution += d;
    vector<vec4> image = textureGenerator->renderToTexture(resolution);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolution, resolution, 0, GL_RGBA, GL_FLOAT, &image[0]);
}

void Star::AlterSchlank(int d) {
    schlank += d;

    vertices = {
            {0.0f, 0.0f},
            {0.0f, -schlank/75.0f},
            {-40.0f/75.0f, -40.0f/75.0f},
            {-schlank/75.0f, 0.0f},
            {-40.0f/75.0f, 40.0f/75.0f},
            {0.0f, schlank/75.0f},
            {40.0f/75.0f, 40.0f/75.0f},
            {schlank/75.0f, 0.0f},
            {40.0f/75.0f, -40.0f/75.0f},
            {0.0f, -schlank/75.0f}
    };

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
}

void Star::Draw() {
    unsigned int location = glGetUniformLocation(shaderProgram,"MVP");

    mat4 MVP =  RotationMatrix(phi,vec3(0,0,1)) * TranslateMatrix(pos);

    glUniformMatrix4fv(location, 1, GL_TRUE, &MVP[0][0]);

    int sampler = 0;
    location = glGetUniformLocation(shaderProgram,"samplerUnit");
    glUniform1i(location,sampler);

    glActiveTexture(GL_TEXTURE0 + sampler);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLE_FAN,0,vertices.size());
}

void Star::Animate(float dt) {
    //Rotation
    float v = 360.0f/5.0f;
    float s = v * dt;
    phi += s * (M_PI / 180.0f);
    phi = fmod(phi,2*M_PI);
    
    //Orbit
    v = 360.0f/10.0f;
    s = v * dt;
    theta += s * (M_PI / 180.0f);
    theta = fmod(theta,2*M_PI);
    pos.x = 0.4f * cosf(theta);
    pos.y = 0.4f * sinf(theta);
}
