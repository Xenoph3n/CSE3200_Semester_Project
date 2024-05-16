#ifndef ANIMATOR_H
#define ANIMATOR_H


#include <glm/glm.hpp>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Animation.h"

class Animator {
  public:
        std::vector<glm::mat4> m_FinalBoneMatrices;
        Animation* m_CurrentAnimation;
        float m_CurrentTime;
        float m_DeltaTime;	
        Animator();
        Animator(Animation* Animation);
        void UpdateAnimation(float dt);
        void PlayAnimation(Animation* pAnimation);
        void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
        std::vector<glm::mat4> GetFinalBoneMatrices();


};  
#endif