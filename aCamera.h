#ifndef A_CAMERA_H
#define A_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class aCamera {
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        bool first_clickz = false;

        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        aCamera(
            glm::vec3 position,
            glm::vec3 up, 
            float yaw,
            float pitch
        );
        // aCamera(
        //     float posX, 
        //     float posY, 
        //     float posZ, 
        //     float upX, 
        //     float upY, 
        //     float upZ, 
        //     float yaw, 
        //     float pitch
        // ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
        //     MovementSpeed(SPEED), 
        //     MouseSensitivity(SENSITIVITY), 
        //     Zoom(ZOOM);

        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
        
        void ProcessMouseScroll(float yoffset);

    private:
        void updateCameraVectors();

};

#endif