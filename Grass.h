#ifndef GRASS_H
#define GRASS_H

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"

class Grass {
    public:

        void DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model);
        void DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model);
};
#endif