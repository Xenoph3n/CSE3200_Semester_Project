#ifndef RENDER_H
#define RENDER_H

#include "Building.h"
#include "aCamera.h"
#include "Circle.h"
#include "Animator.h"
#include "Animation.h"
#include "Light.h"
#include "aModel.h"
#include <GLFW/glfw3.h>
#include <math.h>


class Render {
    public:
        Building render;
        Building blue_2;
        Building blue_3;
        Building orange;
        Building green;
        Building red;
        Building yellow;
        Building purple;

        aModel animated_model_0;
        aModel animated_model_1;
        aModel animated_model_2;

        Animation animation_0;
        Animation animation_1;
        Animation animation_2;

        Animator animator_0;
        Animator animator_1;
        Animator animator_2;

        Light stadium_light_0;
        Light stadium_light_1;
        Light stadium_light_2;
        Light stadium_light_3;

        bool move = false;
        bool spot_light_on = true;

        int animation_state_matrix[4][12] = {
          {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 2, 0, 0, 2, 0, 1, 0, 0, 2, 0},
          {0, 1, 0, 0, 1, 0, 0, 0, 2, 0, 0, 2},
          {0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0}
        };

        void initialize(aCamera& camera, Shader& shader, int screen_width, int screen_height);
        void drawBuildings(aCamera& camera, Shader &shader, Circle& circle, int screen_width, int screen_height, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
        void drawAnimations(aCamera& camera, Shader &shader, Circle& circle, int screen_width, int screen_height, glm::mat4 model, glm::mat4 view, glm::mat4 projection, float deltaTime);
        void drawEntities(aCamera& camera, Shader &shader, Circle& circle, int screen_width, int screen_height, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
        void drawLights(aCamera& camera, Shader &shader, Circle& circle, int screen_width, int screen_height, glm::mat4 model, glm::mat4 view, glm::mat4 projection);

        glm::vec3 processInput(aCamera &camera, GLFWwindow *window, glm::vec3 player_position, glm::vec3 direction);
};
#endif