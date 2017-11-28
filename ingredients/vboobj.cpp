#include "vboobj.h"

#include "cookbookogl.h"
#include "glutils.h"

#include <cstdio>
#include <iostream>

#include <glm/glm.hpp>

using glm::vec3;

double pointToLineDistance(vec3 x0, vec3 x1, vec3 x2)
{
    double d, num, denum;
    
    num = glm::length(glm::cross(x2 - x1, x1 - x0));
    denum = glm::length(x2 - x1);
    
    d = num / denum;
    
    return d;
}

VBOObj::VBOObj(std::string inputfile)
{
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
    
    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }
    
    if (!ret) {
        exit(1);
    }
    
    // вершины
    //float *vertices = new float[];
    
    // нормали
    //float *normals = new float[];
    
    
    
    // цикл по всем объектам
    for (size_t s = 0; s < shapes.size(); s++)
    {
        // цикл по всем граням (полигонам)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];
            
            // цикл по всем вершинам
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                //tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                //tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
                // Optional: vertex colors
                // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
                // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
                // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
            }
            index_offset += fv;
            
            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }
    
    
    float side = 1.0f;
    float side2 = side / 2.0f;

    /*float v[24*3] = {
        // Front
       -side2, -side2, side2,
        side2, -side2, side2,
        side2,  side2, side2,
       -side2,  side2, side2,
       // Right
        side2, -side2, side2,
        side2, -side2, -side2,
        side2,  side2, -side2,
        side2,  side2, side2,
       // Back
       -side2, -side2, -side2,
       -side2,  side2, -side2,
        side2,  side2, -side2,
        side2, -side2, -side2,
       // Left
       -side2, -side2, side2,
       -side2,  side2, side2,
       -side2,  side2, -side2,
       -side2, -side2, -side2,
       // Bottom
       -side2, -side2, side2,
       -side2, -side2, -side2,
        side2, -side2, -side2,
        side2, -side2, side2,
       // Top
       -side2,  side2, side2,
        side2,  side2, side2,
        side2,  side2, -side2,
       -side2,  side2, -side2
    };

    float n[24*3] = {
        // Front
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        // Right
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // Back
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // Left
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // Bottom
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        // Top
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
     */

    float tex[24*2] = {
        // Front
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Right
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Back
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Left
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Bottom
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // Top
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    /*GLuint el[] = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };*/
    
    // создаём новый список вершин, в котором у каждого треугольника свои вершины
    int vertices_count = shapes[0].mesh.num_face_vertices.size() * 3 * 3;
    float *vertices = new float[vertices_count];
    
    // создаём массив нормалей вершин
    float *normals = new float[vertices_count];
    
    // создаём массив цветов вершин
    float *colors = new float[vertices_count];
    
    size_t indices_size = shapes[0].mesh.indices.size();
    GLuint *indices = new GLuint[indices_size];
    
    // цикл по всем вершинам
    for(size_t j = 0; j < indices_size; j++)
    {
        size_t vertex_index = shapes[0].mesh.indices[j].vertex_index;
        size_t normal_index = shapes[0].mesh.indices[j].normal_index;
        indices[j] = vertex_index;
        
        // копируем вершины
        vertices[3 * j + 0] = attrib.vertices[3 * vertex_index + 0];
        vertices[3 * j + 1] = attrib.vertices[3 * vertex_index + 1];
        vertices[3 * j + 2] = attrib.vertices[3 * vertex_index + 2];
        
        // копируем нормали в порядке следования вершин
        normals[3 * j + 0] = attrib.normals[3 * normal_index + 0];
        normals[3 * j + 1] = attrib.normals[3 * normal_index + 1];
        normals[3 * j + 2] = attrib.normals[3 * normal_index + 2];
        
        indices[j] = j;
    }
    
    // цикл по тройкам вершинам (треугольникам)
    for(size_t j = 0; j < indices_size; j+=3)
    {
        // индексы трёх вершин треугольника
        size_t a_index = j + 0;
        size_t b_index = j + 1;
        size_t c_index = j + 2;
        
        // получаем координаты 3 вершин треугольника
        vec3 a, b, c;
        a.x = vertices[3 * a_index + 0];
        a.y = vertices[3 * a_index + 1];
        a.z = vertices[3 * a_index + 2];
        
        b.x = vertices[3 * b_index + 0];
        b.y = vertices[3 * b_index + 1];
        b.z = vertices[3 * b_index + 2];
        
        c.x = vertices[3 * c_index + 0];
        c.y = vertices[3 * c_index + 1];
        c.z = vertices[3 * c_index + 2];
        
        // вычисляем высоты треугольников
        double ha, hb, hc;
        
        ha = pointToLineDistance(a, b, c);
        hb = pointToLineDistance(b, c, a);
        hc = pointToLineDistance(c, a, b);
        
        // заполняем псевдо-цвета (высоты) вершин
        
        // вершина a
        colors[3 * a_index + 0] = ha;
        colors[3 * a_index + 1] = 0.0;
        colors[3 * a_index + 2] = 0.0;
        
        // вершина b
        colors[3 * b_index + 0] = 0.0;
        colors[3 * b_index + 1] = hb;
        colors[3 * b_index + 2] = 0.0;
        
        // вершина c
        colors[3 * c_index + 0] = 0.0;
        colors[3 * c_index + 1] = 0.0;
        colors[3 * c_index + 2] = hc;
    }

    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);

    unsigned int handle[4];
    glGenBuffers(4, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), normals, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // Vertex normal

    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // texture coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void VBOObj::render()
{
    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
