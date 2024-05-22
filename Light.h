#ifndef LIGHT_H
#define LIGHT_H

#include "aModel.h"
#include <glm/glm.hpp>

class Light {

    public:
        aModel stadium_light;
        glm::vec3 lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 spotlightDirection = glm::vec3(0.0f, -1.0f, -1.0f);

        glm::vec3 position = glm::vec3(0.0f, -50.0f, 0.0f);
        float rotation = 0.0f;
        
        bool spotLightOn = true;

        Light();
        void draw(Shader &shader, glm::mat4 view, glm::mat4 projection);
};
#endif