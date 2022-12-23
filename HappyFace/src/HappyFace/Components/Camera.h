#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

static const float YAW = -90.0f;
static const float PITCH = 0.0f;
static const float SPEED = 2.5f;
static const float SENSITIVITY = 0.1f;
static const float ZOOM = 45.0f;

class Camera
{
public:
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    inline glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();

    // // Custom implementation of the LookAt function
    // glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
    // {
    //     // 1. Position = known
    //     // 2. Calculate cameraDirection
    //     glm::vec3 zaxis = glm::normalize(position - target);
    //     // 3. Get positive right axis vector
    //     glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    //     // 4. Calculate camera up vector
    //     glm::vec3 yaxis = glm::cross(zaxis, xaxis);
       
    //     // Create translation and rotation matrix
    //     // In glm we access elements as mat[col][row] due to column-major layout
    //     glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    //     translation[3][0] = -position.x; // Third column, first row
    //     translation[3][1] = -position.y;
    //     translation[3][2] = -position.z;
    //     glm::mat4 rotation = glm::mat4(1.0f);
    //     rotation[0][0] = xaxis.x; // First column, first row
    //     rotation[1][0] = xaxis.y;
    //     rotation[2][0] = xaxis.z;
    //     rotation[0][1] = yaxis.x; // First column, second row
    //     rotation[1][1] = yaxis.y;
    //     rotation[2][1] = yaxis.z;
    //     rotation[0][2] = zaxis.x; // First column, third row
    //     rotation[1][2] = zaxis.y;
    //     rotation[2][2] = zaxis.z;
       
    //     // Return lookAt matrix as combination of translation and rotation matrix
    //     return rotation * translation; // Remember to read from right to left (first translation then rotation)
    // }
};
