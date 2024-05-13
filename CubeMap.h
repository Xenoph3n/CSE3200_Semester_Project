#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include <vector>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

 
class CubeMap
{
    public:
        unsigned int vao;
        unsigned int vbo;
        unsigned int texture_id;
        void setUp(std::vector<float> vertices);
        void loadCubeMap(std::vector<std::string> faces);
        void bind();
        void unbind();
        void bindTexture();
        void draw();
};



#endif
