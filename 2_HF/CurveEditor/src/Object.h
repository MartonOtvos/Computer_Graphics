#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H


#include <vector>
#include "framework.h"

using namespace std;

class Object {
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int shaderProgram;
protected:
    vector<vec2> vertices;
public:
    explicit Object(unsigned int shader);
    void Update();
    void AddVtx(vec2 vtx);

    [[maybe_unused]] void clearVtxs();
    virtual void Draw(int primitive, vec3 color);
};


#endif //GRAPHICS_OBJECT_H
