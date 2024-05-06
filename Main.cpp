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

bool move = false;

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
    Shader playerShader("./plane.vert", "./plane.frag");

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
    aModel test("./models/crow/scene.gltf", false);

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
    
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shadowShader.Activate();
    shadowShader.setInt("texture_diffuse1", 0);
    shadowShader.setInt("shadowMap", 1);

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

    glm::mat4 mod = glm::rotate(playerModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    playerModel = mod;
    glm::vec3 previousCamPosition = camera.Position;

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
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 500.0f;
        //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
        lightProjection = glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        // render scene from light's point of view
        depthShader.Activate();
        depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        
        depthShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,0.0f,5.0f)));
        // render sceneL
        render.draw(depthShader, camera, SHADOW_WIDTH, SHADOW_HEIGHT, glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        // plane.Draw(depthShader);
        depthShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,-50.0f,10.0f)));

        mega_cube.Draw(depthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // /* --------------------------------------  ---------------------------------------- */

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

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.05f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 2000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene


        // // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene


        shadowShader.Activate();
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        // glm::mat4 view = camera.GetViewMatrix();
        shadowShader.setMat4("projection", projection);
        shadowShader.setMat4("view", view);
        // set light uniforms
        shadowShader.setVec3("viewPos", camera.Position);
        shadowShader.setVec3("lightPos", lightPos);
        shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
        // glActiveTexture(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        // render.draw(shadowShader, camera, SCR_WIDTH, SCR_HEIGHT, glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        shadowShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,0.0f,0.0f)));
      //  mega_cube.Draw(shadowShader);

        // // plane.Draw(shadowShader);
        // ourShader.Activate();
        // render.draw(ourShader, camera, SCR_WIDTH, SCR_HEIGHT, glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -50.0f));

        ourShader.Activate();
        render3.draw(ourShader, camera, SCR_WIDTH, SCR_HEIGHT,  glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(110.0f, 0.0f, -50.0f));
        
        
        grassShader.Activate();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        grass_renderer.DrawGrid(
            grass, 
            grassShader,
            glm::vec3(0.0f, 20.0f, 0.0f),
            model
        );

        // x++;

        // if (x == circle.vertices.size() - 1) {
        //     x = 0;
        // }
        // ourShader.Activate();
        
        // ourShader.setMat4("projection", projection);
        // ourShader.setMat4("view", view);
        // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        // shadowShader.setMat4("model", glm::translate(model, glm::vec3(0.0f,-20.0f,0.0f)));
        // ourShader.setVec4("lightColor", lightColor);
       
        // glActiveTexture(GL_TEXTURE0);

        
        playerShader.Activate();
        playerShader.setMat4("projection", projection);
        playerShader.setMat4("view", view);
        // playerShader.setMat4("model", glm::translate(model, lightPos));
        // playerShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        ground.Draw(playerShader);

        // playerModel = glm::scale(playerModel, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        // playerShader.setMat4("model", glm::scale(playerModel, glm::vec3(0.5f, 0.5f, 0.5f)));
        playerShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));

        // if (playerModel == glm::mat4(1.0f)) {
        //     playerModel = glm::translate(playerModel, camera.Position + glm::vec3(0.0f, -5.0f, -10.0f));
        // }

        // if (move) {
            glm::vec3 new_position = glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
            aabb.position += glm::vec3(20.0f, 20.0f, 20.0f) * camera.Front + camera.Position + glm::vec3(0.0f, -10.0f, 0.0f);
            aabb.position = aabb.position * 0.5f;
            // std::cout << "AABB Position (" << aabb.position.x << "," << aabb.position.y << "," << aabb.position.z << ") \n";


            playerModel = glm::translate(playerModel, new_position);
            // playerModel = glm::translate(playerModel, glm::vec3(0.0f, -10.0f, 0.0f));
            playerModel =  glm::rotate(playerModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            playerShader.setMat4("model", glm::scale(playerModel, glm::vec3(0.5f,0.5f, 0.5f)));
            testAABB.position =  testAABB.position * 0.1f;
            std::cout << player.CheckCollision(aabb, testAABB) << "\n";
            // previousCamPosition = camera.Position;

            // std::cout << "Camera Front (" << camera.Front.x << camera.Front.y << camera.Front.z << ") \n";
            // std::cout << "Camera Position (" << camera.Position.x << camera.Position.y << camera.Position.z << ") \n";
            // std::cout << "Player Position (" << new_position.x << new_position.y << new_position.z << ") \n";

        // }

    
     
        // std::cout << camera.Position.x << "," << camera.Position.y << "," << camera.Position.z << "\n";        
        player.Draw(playerShader);

        planeShader.Activate();
        planeShader.setMat4("projection", projection);
        planeShader.setMat4("view", view);
        glm::mat4 testModel = glm::mat4(1.0f);
        testModel = glm::translate(testModel, glm::vec3(0.0f, 0.0f, 0.0f));
        testModel = glm::scale(testModel, glm::vec3(0.1f, 0.1f, 0.1f));
        planeShader.setMat4("model", testModel);
        // planeShader.setMat4("model", glm::translate(model, lightPos));
        // planeShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        // ground.Draw(planeShader);

        // playerModel = glm::scale(playerModel, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        // planeShader.setMat4("model", glm::scale(playerModel, glm::vec3(0.5f, 0.5f, 0.5f)));
        planeShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        test.Draw(planeShader);

        debugShader.Activate();
        debugShader.setFloat("near_plane", near_plane);
        debugShader.setFloat("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        // renderQuad();

        playerModel = glm::mat4(1.0f);
        aabb.position = backupAABB.position;
        testAABB.position = backupAABB.position;
        move = false;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // move = true;
        glfwSetWindowShouldClose(window, true);

    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        move = true;

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        move = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
        move = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
        move = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
        move = true;
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed += 1.0f;
        move = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed -= 1.0f;
        // move = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.first_clickz = true;
        // move = true;
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera.first_clickz = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // move = true;
    }

  
    // std::cout << "Movement: " << move;

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