#ifndef GRASS_H
#define GRASS_H

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <random>
#include <iostream>
#include <vector>
#include <math.h>

struct GridOrientation {
    int s1;
    int s2;
    int s3;
};

class Grass {
    public:
        glm::vec4 pitch_bounds = glm::vec4(-40.0f, -20.0f, 40.0f, 20.0f);
        glm::vec3 position = glm::vec3(0.0f, -49.0f, 0.0f);
        std::vector<glm::mat4> models;
        float offset = 0.0f;

        int n = 200;

        std::vector<GridOrientation> orientations;
        void DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model, int index);
        void DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model);
        void setUpModels(Shader &shader);
        void generateRandomNumbers(int m, int n);
        int getRandomNumber(int start, int stop);
        double getRandomFloat();
};
#endif