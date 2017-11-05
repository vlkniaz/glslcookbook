#ifndef VBOOBJ_H
#define VBOOBJ_H

#include "tiny_obj_loader.h"

class VBOObj
{

private:
    unsigned int vaoHandle;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

public:
    VBOObj(std::string inputfile = "bunny2.obj");

    void render();
};

#endif // VBOOBJ_H
