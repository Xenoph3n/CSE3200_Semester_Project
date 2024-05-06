#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "headers/shaders.h"
// #include "headers/aCamera.h"
// #include "headers/aModel.h"
// #include "headers/mesh.h"
// #include "./headers/FBO.h"

#include "Shader.h"
#include "aCamera.h"
#include "aModel.h"
#include "Mesh.h"
#include "Texture.h"
#include "Circle.h"
#include "Render.h"
#include "Grass.h"
#include "Shadow.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void renderQuad();



float rectangleVertices[] =
{
	// Coords    // texCoords
	 0.5f, -1.0f, -1.0f, 1.0f, 0.0f,
	0.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	0.0f,  -0.5f, -0.5f, 0.0f, 1.0f,

	 0.5f,  -0.5f, 1.0f, 1.0f, 1.0f,
	 0.5f, -1.0f,  1.0f, 1.0f, 0.0f,
	-0.0f,  -0.5f, 1.0f, 0.0f, 1.0f
};


float rectangleVertices2[] =
{
	// Coords    // texCoords
	 0.5f - 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	0.0f - 1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	0.0f - 1.0f, -0.5f, 0.0f, 0.0f, 1.0f,

	 0.5f - 1.0f,  -0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f - 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.0f - 1.0f,  -0.5f, 0.0f, 0.0f, 1.0f
};

Vertex miniSreenVertices[] = {
	Vertex{glm::vec3(-0.5f, 0.5f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 0.5f, 0.5f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

Vertex quadVertices[] = {
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};


// Vertices coordinates
Vertex cubeVertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint cubeIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
aCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool move = true;

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

    // stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("./model.vert", "./model.frag");
    Shader planeShader("./plane.vert", "./plane.frag");
    Shader playerShader("./player.vert", "./player.frag");

    Shader lightShader("./light.vert", "./light.frag");
    Shader shinyShader("./shiny.vert", "./shiny.frag");
    Shader defaultShader("./default.vert", "./default.frag");
    Shader grassShader("./grass.vert", "./grass.frag");
    Shader shadowShader("./shadow.vert", "./shadow.frag");
    Shader depthShader("./dept.vert", "./dept.frag");
    Shader debugShader("./debug.vert", "./debug.frag");

    GLuint tex_id_1;
    GLuint text_id_2;

    Texture textures[]
	{
		Texture("./stadium/single/grass.png", "diffuse", 0, tex_id_1)
	};;

	std::vector <Vertex> verts(miniSreenVertices, miniSreenVertices + sizeof(miniSreenVertices) / sizeof(Vertex));
    std::vector <Vertex> vertz(quadVertices, quadVertices + sizeof(quadVertices) / sizeof(Vertex));
    std::vector <Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    Mesh grass(verts, ind, tex, true);
    Grass grass_renderer;

	// Mesh mesh(verts, ind, tex);
    Mesh ground(verts, ind, tex, false);
    // Mesh quad(vertz, ind, tex);
    // Mesh cube(cubeVerts, cubeInd, tex);

    aModel mega_cube("./stadium/blue_1/mid_section.obj", false);
    aModel player("./models/crow/scene.gltf", false);
    aModel test("./stadium/blue_1/mid_section.obj", false);

    Mesh light(cubeVerts, cubeInd, tex, false);

    Circle circle;
    circle.calculate(glm::vec3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    Mesh plane(circle.vertices, circle.indices, tex, true);

    Render render;
    render.get_file_list("./stadium/blue_1");

    Render render2;
    render2.get_file_list("./stadium/blue_2");

    Render render3;
    render3.get_file_list("./stadium/blue_3");

    std::cout << glGetString(GL_VENDOR) << "\n";

    std::cout << glGetString(GL_RENDERER) << "\n";
    
    shinyShader.Activate();
    
    render.render(  shinyShader, 
                camera, 
                SCR_WIDTH, 
                SCR_HEIGHT,
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(0.0f, 0.0f, -50.0f)   
                );

    ourShader.Activate();

    render2.render(  ourShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(50.0f, 0.0f, -50.0f)   
                        );

    render3.render(  ourShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(110.0f, 0.0f, -50.0f)   
                    );
    
    Shadow shadow;
    shadow.createDepthMap(shadowShader);
    // const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    // unsigned int depthMapFBO;
    // glGenFramebuffers(1, &depthMapFBO);

    // unsigned int depthMap;
    // glGenTextures(1, &depthMap);
    // glBindTexture(GL_TEXTURE_2D, depthMap);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // // attach depth texture as FBO's depth buffer
    // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    // glDrawBuffer(GL_NONE);
    // glReadBuffer(GL_NONE);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // shadowShader.Activate();
    // shadowShader.setInt("texture_diffuse1", 0);
    // shadowShader.setInt("shadowMap", 1);

    glm::vec3 lightPos(-20.0f, 70.0f, 0.0f);

    glm::mat4 playerModel = glm::mat4(1.0f);
    AABB aabb = player.calculateBoundingBox();
    AABB backupAABB = aabb;
    std::cout << player.left_most_point << "\n";
    std::cout << player.right_most_point << "\n";

    std::cout << player.top_most_point << "\n";
    std::cout << player.bottom_most_point << "\n";

    std::cout << player.front_most_point << "\n";
    std::cout << player.back_most_point << "\n";

    std::cout << "AABB Position (" << aabb.position.x << "," << aabb.position.y << "," << aabb.position.z << ") \n";
    std::cout << "AABB Size (" << aabb.size.x << "," << aabb.size.y << "," << aabb.size.z << ") \n";

    AABB megaCubeAABB = mega_cube.calculateBoundingBox();
    std::cout << mega_cube.left_most_point << "\n";
    std::cout << mega_cube.right_most_point << "\n";

    std::cout << mega_cube.top_most_point << "\n";
    std::cout << mega_cube.bottom_most_point << "\n";

    std::cout << mega_cube.front_most_point << "\n";
    std::cout << mega_cube.back_most_point << "\n";

    std::cout << "AABB Mega cube Position (" << megaCubeAABB.position.x << "," << megaCubeAABB.position.y << "," << megaCubeAABB.position.z << ") \n";
    std::cout << "AABB Mega cube Size (" << megaCubeAABB.size.x << "," << megaCubeAABB.size.y << "," << megaCubeAABB.size.z << ") \n";

    // std::cout << "Player Position (" << new_position.x << new_position.y << new_position.z << ") \n";

    AABB testAABB = test.calculateBoundingBox();
    AABB backupTestAABB = testAABB;

    glm::mat4 mod = glm::rotate(playerModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    playerModel = mod;
    glm::vec3 previousCamPosition = camera.Position;
    bool check = true;

    // -----------
    while (!glfwWindowShouldClose(window))
    {


        // glDisable(GL_CLIP_DISTANCE0);
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. render depth of scene to texture (from light's perspective)
        // --------------------------------------------------------------
        // glm::mat4 lightProjection, lightView;
        // glm::mat4 lightSpaceMatrix;
        // float near_plane = 1.0f, far_plane = 500.0f;
        // //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        // lightProjection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, near_plane, far_plane);
        // lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        // lightSpaceMatrix = lightProjection * lightView;
        // // render scene from light's point of view
        // depthShader.Activate();
        // depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        
        // glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        // glClear(GL_DEPTH_BUFFER_BIT);

        shadow.setUpDepthMap(lightPos, depthShader);
        
        depthShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,0.0f,5.0f)));
        // render sceneL
        render.draw(depthShader, camera, shadow.SHADOW_WIDTH, shadow.SHADOW_HEIGHT, glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        // plane.Draw(depthShader);
        depthShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,-50.0f,10.0f)));

        mega_cube.Draw(depthShader);

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        shadow.unBindFrameBuffer();

        // /* --------------------------------------  ---------------------------------------- */

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.05f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 2000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

        shadow.setUpShadowShader(
            shadowShader,
            camera,
            lightPos,
            projection,
            view
        );
        
        shadowShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,-50.0f,10.0f)));
        mega_cube.Draw(shadowShader);

        shadowShader.Activate();
        shadowShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,0.0f,5.0f)));
        render.draw(shadowShader, camera, SCR_WIDTH, SCR_HEIGHT, glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        ourShader.Activate();
        render3.draw(ourShader, camera, SCR_WIDTH, SCR_HEIGHT,  glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(110.0f, 0.0f, 0.0f));

        if (move) {
            glm::vec3 new_position = glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
            aabb.position += glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
            // aabb.position = aabb.position * 0.5f;

            playerModel = glm::translate(playerModel, new_position);
            playerModel = glm::translate(playerModel, glm::vec3(0.0f, -10.0f, 0.0f));
            //playerModel =  glm::rotate(playerModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            // playerModel = glm::scale(playerModel, glm::vec3(0.5f,0.5f, 0.5f);
            playerShader.setMat4("model", playerModel);
            std::cout << player.CheckCollision(aabb, testAABB) << "\n";
            previousCamPosition = camera.Position;
        }

        player.Draw(playerShader);
        playerShader.setMat4("model", glm::mat4(1.0f));
        player.generateBoundingBoxMesh(aabb, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)).Draw(playerShader);

        planeShader.Activate();
        planeShader.setMat4("projection", projection);
        planeShader.setMat4("view", view);
        glm::mat4 testModel = glm::mat4(1.0f);
        // testModel = glm::translate(testModel, glm::vec3(0.0f, 0.0f, 0.0f));
        // testModel = glm::scale(testModel, glm::vec3(0.1f, 0.1f, 0.1f));
        planeShader.setMat4("model", glm::translate(testModel, glm::vec3(0.0f, 0.0f, 0.0f)));

        // planeShader.setMat4("model", glm::scale(playerModel, glm::vec3(0.5f, 0.5f, 0.5f)));
        planeShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        //test.generateBoundingBoxMesh(testAABB, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)).Draw(planeShader);
   
        //test.Draw(planeShader);
        shadow.debug(debugShader, false);
     

        // DEBUG CODE FOR AABB
        if (move) {
            playerModel = glm::mat4(1.0f);
            aabb.position = backupAABB.position;
            testAABB.position = backupTestAABB.position;
            check = true;
        } else if (!move) {
            if (check) {
                aabb.position += glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
                aabb.position = aabb.position * 0.5f;
                check = false;
            }
        }
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
   
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
      
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
     
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed += 1.0f;
    }
 
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed -= 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        move = false;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
        move = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.first_clickz = true;
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera.first_clickz = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

 
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
        
        // grassShader.Activate();
        // grassShader.setMat4("projection", projection);
        // grassShader.setMat4("view", view);
        // grass_renderer.DrawGrid(
        //     grass, 
        //     grassShader,
        //     glm::vec3(0.0f, 20.0f, 0.0f),
        //     model
        // );

        // std::cout << "Camera Front (" << camera.Front.x << camera.Front.y << camera.Front.z << ") \n";
        //     std::cout << "Player Size (" << aabb.size.x << "," << aabb.size.y << "," << aabb.size.z << ") \n";
        //     std::cout << "Test Size (" << testAABB.size.x << "," << testAABB.size.y << "," << testAABB.size.z << ") \n";

        //     std::cout << "Player Position (" << aabb.position.x << "," << aabb.position.y << "," << aabb.position.z << ") \n";
        //     std::cout << "Test Position (" << testAABB.position.x << "," << testAABB.position.y << "," << testAABB.position.z << ") \n";


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