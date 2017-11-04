#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include "scene.h"
#include "glslprogram.h"
#include "vboplane.h"
#include "vbocube.h"
#include "vboobj.h"
#include "vboteapot.h"

// OpenGL headers
#include "cookbookogl.h"

#include <glm/glm.hpp>
using glm::mat4;

class SceneObj : public Scene
{
private:
    GLSLProgram prog;

    int width, height;
    VBOTeapot *teapot;
    VBOObj *object;

    mat4 model;
    mat4 view;
    mat4 projection;
    float angle, tPrev, rotSpeed;

    void setMatrices();
    void compileAndLinkShader();

public:
    SceneObj();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEOBJ_H
