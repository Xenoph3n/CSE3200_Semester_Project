#ifndef SHADOW_H
#define SHADOW_H

#include "Shader.h"
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "aCamera.h"

class Shadow {
    public:
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        unsigned int depthMapFBO;
        unsigned int depthMap;

        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;

        float near_plane = 1.0f;
        float far_plane = 500.0f;
    
        void createDepthMap(Shader &shader);
        void setUpDepthMap(
            glm::vec3 light_pos,
            Shader &shader,
            glm::vec4 frustrumArea = glm::vec4(-200.0f, 200.0f, -200.0f, 200.0f)
        );
        void unBindFrameBuffer();
        void debug(Shader &shader, bool render);
        void setUpShadowShader(
            Shader &shader, 
            aCamera &camera, 
            glm::vec3 light_pos, 
            glm::mat4 projection, 
            glm::mat4 view);
    private:
        void renderQuad();
};

#endif