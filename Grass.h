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

struct GridOrientation {
    int s1;
    int s2;
    int s3;
};

class Grass {
    public:
        std::vector<GridOrientation> orientations;
        void DrawSingle(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model, int index);
        void DrawGrid(Mesh grass, Shader &shader, glm::vec3 position, glm::mat4 model);
        void generateRandomNumbers(int m, int n);
        int getRandomNumber(int start, int stop);
        double getRandomFloat();
};
#endif