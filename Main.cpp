#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <vector>
#include <math.h>
#include <iostream>

#include "Shader.h"
#include "aCamera.h"
#include "aModel.h"
#include "Mesh.h"
#include "Texture.h"
#include "Circle.h"
#include "Building.h"
#include "Grass.h"
#include "Shadow.h"
#include "Collision.h"
#include "WorldBoundary.h"
#include "CubeMap.h"
#include "Animation.h"
#include "Animator.h"
#include "Bone.h"
#include "Points.h"
#include "Render.h"
#include "Util.h"
#include "Player.h"
#include "Cricketers.h"
#include "Light.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
aCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    gladLoadGL();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    GLuint tex_id_1 = 0;
    GLuint text_id_2 = 1;

    Shader ourShader("./model.vert", "./model.frag");
    Shader planeShader("./plane.vert", "./plane.frag");
    Shader lightShader("./light.vert", "./light.frag");
    Shader shinyShader("./shiny.vert", "./shiny.frag");
    Shader defaultShader("./default.vert", "./default.frag");
    Shader grassShader("./grass.vert", "./grass.frag");
    Shader shadowShader("./shadow.vert", "./shadow.frag");
    Shader depthShader("./dept.vert", "./dept.frag");
    Shader debugShader("./debug.vert", "./debug.frag");
    Shader playerShader("./animation.vert", "./animation.frag");
    Shader skyBoxShader("./skybox.vert", "./skybox.frag");
    Shader animationShader("./animation.vert", "./animation.frag");
    Shader stadiumShader("./stadium_light.vert", "./stadium_light.frag");

    Texture textures[]{
        Texture("./stadium/single/grass.png", "diffuse", 0, tex_id_1)};

    Texture dirt_texture[]{
        Texture("./textures/dirt.jpg", "diffuse", 0, text_id_2)};

    std::vector<Vertex> verts(miniSreenVertices, miniSreenVertices + sizeof(miniSreenVertices) / sizeof(Vertex));
    std::vector<Vertex> vertz(quadVertices, quadVertices + sizeof(quadVertices) / sizeof(Vertex));
    std::vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    std::vector<Texture> dirt(dirt_texture, dirt_texture + sizeof(dirt_texture) / sizeof(Texture));

    Grass grass_renderer;
    glm::vec3 position = glm::vec3(0.0f, -49.0f, 0.0f);
    grass_renderer.setUpModels(grassShader);

    Circle circle;
    circle.calculate(glm::vec3(0.0f, 0.0f, 0.0f), 30.0f, 200.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    Circle circle_2;
    circle_2.calculate(glm::vec3(0.0f, 0.0f, 0.0f), 30.0f, 250.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    Mesh grass(verts, ind, tex, true, true, grass_renderer.models);

    Mesh ground(verts, ind, tex, false);

    Player player;
    player.position = glm::vec3(0.0f, 0.0f, 0.0f);

    Mesh light(cubeVerts, cubeInd, tex, false);
    Mesh plane(circle.vertices, circle.indices, dirt, true);
    Mesh plane_2(circle_2.vertices, circle_2.indices, dirt, true);

    Render render;
    render.initialize(camera, shadowShader, SCR_WIDTH, SCR_HEIGHT);

    Shadow shadow;
    shadow.createDepthMap(shadowShader);

    glm::vec3 lightPos(-20.0f, 70.0f, 0.0f);
    glm::mat4 playerModel = glm::mat4(1.0f);
    glm::mat4 testingModel = glm::mat4(1.0f);

    AABB backupAABB = player.aabb;

    AABB circleAABB = circle.collision.calculateBoundingBox();

    WorldBoundary world_boundary;
    world_boundary.vertices = circle.vertices;
    world_boundary.y_offset = 50.0f;
    world_boundary.z_offset = 5.0f;

    world_boundary.calculateWorldAABBs();

    CubeMap cubemap;

    glGenVertexArrays(1, &cubemap.vao);
    glGenBuffers(1, &cubemap.vbo);
    glBindVertexArray(cubemap.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cubemap.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    cubemap.loadCubeMap(faces);
    cubemap.setUniforms(skyBoxShader);
    
    circleAABB.position += glm::vec3(0.0f, -50.0f, 0.0f);

    Cricketers cricketers;
    cricketers.generate_positions(circle.radius, grass_renderer.pitch_bounds);
    cricketers.get_batter_starting_positions(grass_renderer.pitch_bounds);

    Light stadium_light_0;
    stadium_light_0.position = glm::vec3(circle.vertices[0].position.x, -50.0f, circle.vertices[0].position.z + 30.0f);
    stadium_light_0.rotation = 180.0f;
    Light stadium_light_1;
    stadium_light_1.position = glm::vec3(circle.vertices[3].position.x + 40.0f, -50.0f, circle.vertices[3].position.z);
    stadium_light_1.rotation = -90.0f;

    Light stadium_light_2;
    stadium_light_2.position = glm::vec3(circle.vertices[6].position.x, -50.0f, circle.vertices[6].position.z);
    Light stadium_light_3;
    stadium_light_3.position = glm::vec3(circle.vertices[9].position.x - 40.0f, -50.0f, circle.vertices[9].position.z);
    stadium_light_3.rotation = 90.0f;

    std::vector<glm::vec3> light_positions = {
        glm::vec3(circle.vertices[0].position.x, 100.0f, circle.vertices[0].position.z + 30.0f),
        glm::vec3(circle.vertices[3].position.x + 40.0f, 100.0f, circle.vertices[3].position.z),
        glm::vec3(circle.vertices[6].position.x, 100.0f, circle.vertices[6].position.z),
        glm::vec3(circle.vertices[9].position.x - 40.0f, 100.0f, circle.vertices[9].position.z)
    };

    std::vector<glm::vec3> light_directions = {
        glm::vec3(0.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0, 0.0f)
    };

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shadow.setUpDepthMap(lightPos, depthShader);

        stadium_light_0.draw(depthShader, view, projection);
        stadium_light_1.draw(depthShader, view, projection);
        stadium_light_2.draw(depthShader, view, projection);
        stadium_light_3.draw(depthShader, view, projection);

        render.drawBuildings(camera, depthShader, circle, SCR_WIDTH, SCR_WIDTH, model, view, projection);

        depthShader.setMat4("projection", projection);
        depthShader.setMat4("view", view);
        depthShader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f)));
        depthShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        cricketers.draw(depthShader, view, projection);
        
        plane_2.Draw(depthShader);

        shadow.unBindFrameBuffer();

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.05f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        shadow.setUpShadowShader(
            shadowShader,
            camera,
            lightPos,
            projection,
            view);

        shadowShader.Activate();
        shadowShader.setVec3("lightPos", lightPos);
        shadowShader.setVec3("viewPos", camera.Position);

        for(int i = 0; i < 4; i++) {
            shadowShader.setVec3("light.position[" + std::to_string(i) + "]", light_positions[i]);
            shadowShader.setVec3("light.direction[" + std::to_string(i) + "]", light_directions[i]);
        }

        shadowShader.setVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        shadowShader.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shadowShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shadowShader.setFloat("light.constant", 1.0f);
        shadowShader.setFloat("light.linear", 0.07f);
        shadowShader.setFloat("light.quadratic", 0.017f);
        shadowShader.setFloat("light.outerCutOff", glm::cos(glm::radians(80.5f)));
        shadowShader.setFloat("light.cutOff",   glm::cos(glm::radians(50.5f)));
        shadowShader.setBool("spotlightOn", render.spot_light_on);
        
  
        glm::vec3 translation_offset = render.processInput(camera, window, player.position, camera.Front);
        
        player.Draw(
            playerShader,
            camera,
            translation_offset,
            circleAABB,
            world_boundary.aabbs,
            projection,
            view,
            deltaTime
        );

        stadium_light_0.draw(shadowShader, view, projection);
        stadium_light_1.draw(shadowShader, view, projection);
        stadium_light_2.draw(shadowShader, view, projection);
        stadium_light_3.draw(shadowShader, view, projection);

        render.drawBuildings(camera, shadowShader, circle, SCR_WIDTH, SCR_WIDTH, model, view, projection);

        cricketers.draw(shadowShader, view, projection);
        
        shadowShader.Activate();
        shadowShader.setMat4("projection", projection);
        shadowShader.setMat4("view", view);
        shadowShader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f)));
        plane_2.Draw(shadowShader);

        grassShader.Activate();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        grass.Draw(grassShader, false, true, grass_renderer.models);

        render.drawAnimations(camera, animationShader, circle, SCR_WIDTH, SCR_HEIGHT, model, view, projection, deltaTime);

        glDepthFunc(GL_LEQUAL);
        skyBoxShader.Activate();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyBoxShader.setMat4("view", view);
        skyBoxShader.setMat4("projection", projection);
        cubemap.bind();
        cubemap.bindTexture();
        cubemap.draw();
        cubemap.unbind();
        glDepthFunc(GL_LESS);

        player.aabb.position = backupAABB.position;
        player.aabb.size = backupAABB.size;
      
        shadow.debug(debugShader, false);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// DON'T REMOVE THIS - SHIVESH

// SHINY SHADER STUFF
// // glm::vec3 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

// // lightShader.Activate();

// // lightShader.setMat4("projection", projection);
// // lightShader.setMat4("view", view);
// // lightShader.setMat4("model", glm::translate(model, glm::vec3(-10.0f, 1.0f, 0.0f)));
// // lightShader.setVec4("lightColor", lightColor);
// // lightShader.setVec3("camPosition", camera.Position);

// // light.Draw(lightShader);

// // shinyShader.Activate();
// // shinyShader.setVec3("camPosition", camera.Position);
// // shinyShader.setVec3("light.position", glm::vec3(0.0f,-20.0f,0.0f));
// // shinyShader.setFlknight_texturec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
// // shinyShader.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
// // shinyShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
// // shinyShader.setFloat("light.constant", 1.0f);
// // shinyShader.setFloat("light.linear", 0.07f);
// // shinyShader.setFloat("light.quadratic", 0.017f);

// // // material properties
// // shinyShader.setFloat("material.shininess", 32.0f);

// if (move) {
//     glm::vec3 movement = glm::vec3(20.0f, 20.0f, 20.0f);
//     // glm::vec3 translation_offset = movement * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
//     glm::vec3 translation_offset = movement * camera.Front;
//     AABB old_aabb = aabb;
//     aabb.position *= 0.5f;
//     aabb.size *= 0.5f;
//     aabb.position += glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);

//     playerShader.Activate();

//     if (player.CheckCollision(aabb, testAABB)) {
//         playerShader.setMat4("projection", projection);
//         playerShader.setMat4("view", view);
//         translation_offset = glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
//         playerModel = glm::translate(playerModel, translation_offset);
//         playerModel = glm::scale(playerModel, glm::vec3(0.5f,0.5f, 0.5f));
//         playerShader.setMat4("model", playerModel);
//         camera.collided = true;
//     } else {
//         playerModel = glm::translate(playerModel, translation_offset);
//         // playerModel = glm::translate(playerModel, player.ApplyGravity(translation_offset));
//         playerShader.setMat4("projection", projection);
//         playerShader.setMat4("view", view);
//         playerShader.setMat4("model", playerModel);
//         camera.collided = false;
//     }
// }
