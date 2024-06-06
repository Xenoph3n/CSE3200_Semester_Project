#include <iostream>
#include <glm/glm.hpp>
#include <stdlib.h>

class Util {
    public: 
        static inline void PrintVec3(std::string name, glm::vec3 vector) {
	        std::cout << name << "( x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z << ")" << std::endl;
	    }

        static inline void Print(std::string name, int value) {
	        std::cout << name << ":" << value << std::endl;
	    }
};