#include "sceneobj.h"

#include <cstdio>
#include <cstdlib>

#include "tgaio.h"

#include "glutils.h"

#include <iostream>
using std::endl;
using std::cerr;

using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

SceneObj::SceneObj() : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>() / 2.0f), mode(0) { }

void SceneObj::initScene()
{
    compileAndLinkShader();

    glEnable(GL_DEPTH_TEST);

    object = new VBOObj();
    
    m_animate = false;

    projection = mat4(1.0f);

    prog.setUniform("Light.Intensity", vec3(1.0f,1.0f,1.0f) );

    // Load cement texture file
    glActiveTexture(GL_TEXTURE0);
    TGAIO::loadTex("../media/texture/cement.tga");

    // Load moss texture file
    glActiveTexture(GL_TEXTURE1);
    TGAIO::loadTex("../media/texture/moss.tga");

#ifdef __APPLE__
  prog.setUniform("BaseTex", 0);
  prog.setUniform("AlphaTex", 1);
#endif

}

void SceneObj::update( float t )
{
    float deltaT = t - tPrev;
    if(tPrev == 0.0f) deltaT = 0.0f;
    tPrev = t;

    if( this->m_animate ) {
	angle += rotSpeed * deltaT;
	if (angle > glm::two_pi<float>()) angle -= glm::two_pi<float>();
    }
}

void SceneObj::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos = vec3(7.0f * cos(angle), 5.0f, 7.0f * sin(angle));
    view = glm::lookAt(cameraPos, vec3(0.0f,-1.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    
    glEnable(GL_CULL_FACE);
    
    if(mode == 1)
    {
        // рисуем обводку объекта
        glCullFace(GL_FRONT);

        prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
        prog.setUniform("Material.Kd", 0.0f, 0.0f, 0.0f);
        prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
        prog.setUniform("Material.Ka", 0.0f, 0.0f, 0.0f);
        prog.setUniform("Material.Shininess", 0.0f);
        
        model = mat4(1.0f);
        model = glm::translate(model, vec3(0.0f,-1.5f,0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f,0.0f,0.0f));
        model = glm::scale(model, vec3(1.05, 1.05, 1.05));
        setMatrices();
        object->render();
    }
    
    // рисуем сам объект
    glCullFace(GL_BACK);
    
    prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.0f, 0.0f, 0.0f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);
    if(mode == 1)
    {
        prog.setUniform("SilhouetteMode", 1.0f);
    }
    else
    {
        prog.setUniform("SilhouetteMode", 0.0f);
    }
    
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f,-1.5f,0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f,0.0f,0.0f));
    setMatrices();
    object->render();
}

void SceneObj::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneObj::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(60.0f), (float)w/h, 0.3f, 100.0f);
}

void SceneObj::compileAndLinkShader()
{
  try {
#ifdef __APPLE__
    prog.compileShader("shader/obj_41.vs");
    prog.compileShader("shader/obj_41.fs");
#else
    prog.compileShader("shader/alphatest.vs");
    prog.compileShader("shader/alphatest.fs");
#endif
    prog.link();
    prog.use();
  } catch(GLSLProgramException & e) {
    cerr << e.what() << endl;
    exit( EXIT_FAILURE );
  }
}
