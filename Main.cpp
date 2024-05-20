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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
glm::vec3 processInput(GLFWwindow *window, glm::vec3 player_position, glm::vec3 direction);
void renderQuad();

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

bool move = true;
bool check = false;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    GLuint tex_id_1;
    GLuint text_id_2;

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

    Texture textures[]
	{
		Texture("./stadium/single/grass.png", "diffuse", 0, tex_id_1)
	};

    Texture dirt_texture[]
	{
		Texture("./textures/dirt.jpg", "diffuse", 0, text_id_2)
	};

	std::vector <Vertex> verts(miniSreenVertices, miniSreenVertices + sizeof(miniSreenVertices) / sizeof(Vertex));
    std::vector <Vertex> vertz(quadVertices, quadVertices + sizeof(quadVertices) / sizeof(Vertex));
    std::vector <Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    std::vector <Texture> dirt(dirt_texture, dirt_texture + sizeof(dirt_texture) / sizeof(Texture));

    Grass grass_renderer;
    glm::vec3 position = glm::vec3(0.0f, -49.0f, 0.0f);
    grass_renderer.setUpModels(grassShader);

    Circle circle;
    circle.calculate(glm::vec3(0.0f, 0.0f, 0.0f), 30.0f, 200.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
    Circle circle_2;
    circle_2.calculate(glm::vec3(0.0f, 0.0f, 0.0f), 30.0f, 250.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    
    Mesh grass(verts, ind, tex, true, true, grass_renderer.models);
    
    Mesh ground(verts, ind, tex, false);

    aModel mega_cube("./stadium/crow/scene.gltf", false);
    aModel test("./stadium/blue_1/bottom_green.obj", false);
  //  aModel player("./models/crow/scene.gltf", false);

    aModel player("./animations/player_walk.dae", false);
    Animation player_walk_animation("./animations/player_walk.dae", &player);
    Animator player_animator(&player_walk_animation);
    
    test.position = glm::vec3(0.0f,-40.0f, 80.0f);
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

   // playerModel = glm::rotate(playerModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    testingModel = glm::translate(testingModel, test.position);

    AABB aabb = player.collision.calculateBoundingBox();
    AABB backupAABB = aabb;

    AABB testAABB = test.collision.calculateBoundingBox();
    AABB testAABBBackup = testAABB;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    cubemap.loadCubeMap(faces);
    cubemap.setUniforms(skyBoxShader);


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
              
        render.drawBuildings(camera, depthShader, circle, SCR_WIDTH, SCR_WIDTH, model, view, projection);

        depthShader.setMat4("projection", projection);
        depthShader.setMat4("view", view);
        depthShader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f)));
        depthShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        plane.Draw(depthShader);

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
            view
        );
        
        shadowShader.Activate();
        // shadowShader.setVec3("lightPosition", lightPos);
        // shadowShader.setVec3("lightColor", glm::vec3(0.5, 0.0, 0.0));
        shadowShader.setVec3("lightPos", lightPos);
        shadowShader.setVec3("viewPos", camera.Position);
        // shadowShader.setMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));

        // test.Draw(shadowShader);

        render.drawBuildings(camera, shadowShader, circle, SCR_WIDTH, SCR_WIDTH, model, view, projection);

        glm::vec3 translation_offset = processInput(window, player.position, camera.Front);
        glm::vec3 gravity = player.ApplyGravity();
        glm::vec3 future_position = player.position + translation_offset + gravity;
        
        aabb.position += future_position;
        testAABB.position += test.position;
        circleAABB.position += glm::vec3(0.0f, -50.0f, 0.0f);

        if  (player.collision.CheckCollisionY(aabb, circleAABB)) {
            move = true;
            gravity = glm::vec3(0.0f, 0.0f, 0.0f);
            future_position = player.position + translation_offset;
        } 
        
        if (player.collision.CheckMassCollision(aabb, world_boundary.aabbs)) {
            move = false;
            gravity =  glm::vec3(0.0f, 0.0f, 0.0f);
            translation_offset =  glm::vec3(0.0f, 0.0f, 0.0f);
        } else {
            move = true;
        }

        if (move) {
            player.position = future_position;
            camera.Position = player.position + glm::vec3(-40.0f * camera.Front.x, 40.0f, -40.0f * camera.Front.z); 
        }

        // Util::PrintVec3("Camera Face", camera.Front);
        // Util::PrintVec3("Camera Position", camera.Position);

        // Util::Print("Camera Y Rotation", camera.Yaw);     

        playerModel = glm::translate(playerModel, translation_offset + gravity);
        playerModel = glm::rotate(playerModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        playerModel = glm::rotate(playerModel, glm::radians(-camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        playerShader.Activate();
        playerShader.setMat4("projection", projection);
        playerShader.setMat4("view", view);
        playerShader.setMat4("model", playerModel);
        playerShader.setVec4("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        playerShader.setVec3("camPos", camera.Position);

        player_animator.UpdateAnimation(deltaTime);
        auto transforms = player_animator.GetFinalBoneMatrices();

        for (int i = 0; i < transforms.size(); ++i)
            playerShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
       // player_animator.Draw(playerShader);
        player.Draw(playerShader);
        
        playerShader.setMat4("model", glm::mat4(1.0f));
        playerModel = glm::rotate(playerModel, glm::radians(camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        playerModel = glm::rotate(playerModel, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        player.collision.generateBoundingBoxMesh(aabb, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)).Draw(playerShader);

        shadowShader.Activate();
        shadowShader.setMat4("projection", projection);
        shadowShader.setMat4("view", view);
        shadowShader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -50.0f, 0.0f)));
        shadowShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        // circle.collision.generateBoundingBoxMesh(circleAABB, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)).Draw(shadowShader);
        // plane.Draw(shadowShader);
        plane_2.Draw(shadowShader);

        grassShader.Activate();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        grass.Draw(grassShader, false, true, grass_renderer.models);

        render.drawAnimations(camera, animationShader, circle, SCR_WIDTH, SCR_HEIGHT, model, view, projection, deltaTime);
        /* SKYBOX */

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

        aabb.position = backupAABB.position;
        aabb.size = backupAABB.size;
        testAABB.position = testAABBBackup.position;
        testAABB.size = testAABBBackup.size;
        circleAABB.position = circle.collision.aabb.position;

        shadow.debug(debugShader, false);

        move = false;
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
glm::vec3 processInput(GLFWwindow *window, glm::vec3 player_position, glm::vec3 direction)
{
    glm::vec3 translation_offset = glm::vec3(0.0f, 0.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        
        // camera.ProcessKeyboard(FORWARD, deltaTime);
        translation_offset = glm::vec3(1.0f, 0.0f, 1.0f) * direction;
        move = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // camera.ProcessKeyboard(BACKWARD, deltaTime);
        translation_offset = glm::vec3(1.0f, 0.0f, 1.0f) * -direction;
        move = true;
        // translation_offset.x -= 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // camera.ProcessKeyboard(LEFT, deltaTime);
    
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
     
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
        translation_offset = glm::vec3(0.0f, 20.0f, 0.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed += 1.0f;
    }
 
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed -= 1.0f;
        check = true;
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        move = false;
    }

    if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS) {
        move = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.first_clickz = true;
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera.first_clickz = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    return translation_offset;

 
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
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
        