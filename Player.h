#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "aModel.h"
#include "Animation.h"
#include "Animator.h"
#include "Collision.h"

class Player {
    public: 
        bool apply_gravity = true;    
        bool move = false;
        bool moving = false;
        float gravity = 9.8f;
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

        aModel player;
        aModel player_object;
        Animation walk_animation;
        Animation idle_animation;
        Animation jump_animation;
        Animator player_animator;
        aCamera camera;
        
        glm::mat4 model = glm::mat4(1.0f);
        AABB aabb;
    
        Player();
        void Draw(  Shader &shader, 
                    aCamera &aCamera, 
                    glm::vec3 translation, 
                    AABB circle_aabb, 
                    std::vector<AABB> world_boundary_aabbs,
                    glm::mat4 projection,
                    glm::mat4 view,
                    float delta_time
                );
};
#endif