#ifndef ANIMATION_H
#define ANIMATION_H


#include <glm/glm.hpp>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Bone.h"
#include "aModel.h"


struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation {
    public:
        float m_Duration;
        int m_TicksPerSecond;
        std::vector<Bone> m_Bones;
        AssimpNodeData m_RootNode;
        std::map<std::string, BoneInfo> m_BoneInfoMap;

        Animation(const std::string& animationPath, aModel* model);
        Bone* FindBone(const std::string& name);
        float GetTicksPerSecond();
        float GetDuration();
        const AssimpNodeData& GetRootNode();
        const std::map<std::string,BoneInfo>& GetBoneIDMap();

    private:
        void ReadMissingBones(const aiAnimation* animation, aModel& model);
        void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);

};
#endif