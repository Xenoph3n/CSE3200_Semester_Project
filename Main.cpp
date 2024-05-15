#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <vector>

#include "Shader.h"
#include "aCamera.h"
#include "aModel.h"
#include "Mesh.h"
#include "Texture.h"
#include "Circle.h"
#include "Building.h"
#include "Grass.h"
#include "Shadow.h"
#include <math.h>
#include <iostream>
#include "Collision.h"
#include "WorldBoundary.h"
#include "CubeMap.h"
#include "Animation.h"
#include "Animator.h"
#include "Bone.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
glm::vec3 processInput(GLFWwindow *window, glm::vec3 player_position, glm::vec3 direction);
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

float skyBoxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
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

    Shader ourShader("./model.vert", "./model.frag");
    Shader planeShader("./plane.vert", "./plane.frag");

    Shader lightShader("./light.vert", "./light.frag");
    Shader shinyShader("./shiny.vert", "./shiny.frag");
    Shader defaultShader("./default.vert", "./default.frag");
    Shader grassShader("./grass.vert", "./grass.frag");
    Shader shadowShader("./shadow.vert", "./shadow.frag");
    Shader depthShader("./dept.vert", "./dept.frag");
    Shader debugShader("./debug.vert", "./debug.frag");
    Shader playerShader("./player.vert", "./player.frag");
    Shader skyBoxShader("./skybox.vert", "./skybox.frag");
    Shader animationShader("./animation.vert", "./animation.frag");

    GLuint tex_id_1;
    GLuint text_id_2;

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
    
    Mesh grass(verts, ind, tex, true, true, grass_renderer.models);
    
    Mesh ground(verts, ind, tex, false);

    aModel mega_cube("./stadium/crow/scene.gltf", false);
    
    aModel test("./stadium/blue_1/bottom_green.obj", false);

    aModel player("./models/crow/scene.gltf", false);
    test.position = glm::vec3(0.0f,-40.0f, 80.0f);
    player.position = glm::vec3(0.0f, 0.0f, 0.0f);

    Mesh light(cubeVerts, cubeInd, tex, false); 
    Mesh plane(circle.vertices, circle.indices, dirt, true);

    Building render;
    render.get_file_list("./stadium/blue_2");
    Building blue_2;
    blue_2.get_file_list("./stadium/blue_1");
    Building blue_3;
    blue_3.get_file_list("./stadium/blue_3");
    Building orange;
    orange.get_file_list("./stadium/orange");
    Building green;
    green.get_file_list("./stadium/green");
    Building red_1;
    red_1.get_file_list("./stadium/red");
    Building yellow;
    yellow.get_file_list("./stadium/yellow");
    Building purple;
    purple.get_file_list("./stadium/purple");
    // std::cout << glGetString(GL_VENDOR) << "\n";
    // std::cout << glGetString(GL_RENDERER) << "\n";
    
    render.render(shadowShader, 
                camera, 
                SCR_WIDTH, 
                SCR_HEIGHT,
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(circle.vertices[0].position.x, -34.0f, circle.vertices[0].position.z),
                0.0f
                );
           
    blue_2.render(  shadowShader, 
            camera, 
            SCR_WIDTH, 
            SCR_HEIGHT,
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(circle.vertices[4].position.x - 190.0f, -34.0f, circle.vertices[4].position.z - 100.0f),
            280.0f
            );

    blue_3.render(  shadowShader, 
        camera, 
        SCR_WIDTH, 
        SCR_HEIGHT,
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(circle.vertices[2].position.x - 150.0f, -34.0f, circle.vertices[2].position.z - 300.0f),
        260.0f
        );
    
    orange.render(  shadowShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(200.0f + circle.vertices[0].position.x, -31.0f, 0.0f + circle.vertices[0].position.z - 400.0f),
                    0.0f
                    );

     
    green.render(   shadowShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(circle.vertices[8].position.x + 200.0f, -43.0f, 0.0f + circle.vertices[8].position.z - 100.0f), 
                    60.0f
                    );
    
     
    red_1.render(     shadowShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f), 
                    0.0f
                    );
    
    
     
    yellow.render(  shadowShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f), 
                    0.0f
                    );

    
     
    purple.render(  shadowShader, 
                    camera, 
                    SCR_WIDTH, 
                    SCR_HEIGHT,
                    glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f), 
                    0.0f
                    );
    Shadow shadow;  
    shadow.createDepthMap(shadowShader);

    glm::vec3 lightPos(-20.0f, 70.0f, 0.0f);
    glm::mat4 playerModel = glm::mat4(1.0f);
    glm::mat4 testingModel = glm::mat4(1.0f);
    
    testingModel = glm::translate(testingModel, test.position);

    AABB aabb = player.collision.calculateBoundingBox();
    AABB backupAABB = aabb;

    AABB testAABB = test.collision.calculateBoundingBox();
    AABB testAABBBackup = testAABB;

    AABB circleAABB = circle.collision.calculateBoundingBox();
    
    planeShader.printVec3("Player aabb", testAABB.position);
    planeShader.printVec3("Test aabb", aabb.position);

    WorldBoundary world_boundary;
    world_boundary.vertices = circle.vertices;
    world_boundary.y_offset = 50.0f;
    world_boundary.z_offset = 5.0f;

    world_boundary.calculateWorldAABBs();

    CubeMap cubemap;

    // cubemap.setUp(skyBoxVertices);

    glGenVertexArrays(1, &cubemap.vao);
    glGenBuffers(1, &cubemap.vbo);
    glBindVertexArray(cubemap.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cubemap.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    std::vector<std::string> faces
    {
        "./textures/skybox/right.jpg",
        "./textures/skybox/left.jpg",
        "./textures/skybox/top.jpg",
        "./textures/skybox/bottom.jpg",
        "./textures/skybox/front.jpg",
        "./textures/skybox/back.jpg"
    };

    
    cubemap.loadCubeMap(faces);

    skyBoxShader.Activate();
    skyBoxShader.setInt("skybox", 0);
    
    aModel animatedModel("./vampire/dancing_vampire.dae", false);
    Animation animation("./vampire/dancing_vampire.dae", &animatedModel);
    Animator animator(&animation);
    
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        // shadowShader.printVec3(camera.Position);
        // camera.Position = glm::vec3(0.0f, 0.0f, 10.0f);

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
              
        render.draw(    depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[3].position.x - 200.0f, -34.0f, circle.vertices[3].position.z - 200.0f),
                        270.0f
                        );
        
        blue_2.draw(   depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[4].position.x - 190.0f, -34.0f, circle.vertices[4].position.z - 100.0f),
                        280.0f
                        );

        blue_3.draw(   depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[2].position.x - 150.0f, -34.0f, circle.vertices[2].position.z - 300.0f),
                        260.0f
                        );
                        
        orange.draw(    depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[0].position.x, -31.0f, circle.vertices[0].position.z),
                        0.0f);
        
        
        green.draw(     depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[8].position.x + 200.0f, -43.0f, 0.0f + circle.vertices[8].position.z - 110.0f),
                        50.0f);

                
        
        red_1.draw(     depthShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        0.0f);
            
        depthShader.setMat4("projection", projection);
        depthShader.setMat4("view", view);

        glm::mat4 testModel = glm::mat4(1.0f);
        depthShader.setMat4("model", glm::translate(testModel, glm::vec3(0.0f, -50.0f, 0.0f)));
        depthShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        plane.Draw(depthShader);

        shadow.unBindFrameBuffer();

        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClearColor(0.05f, 0.05f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

        shadow.setUpShadowShader(
            shadowShader,
            camera,
            lightPos,
            projection,
            view
        );

        shadowShader.Activate();
        shadowShader.setMat4("model",glm::mat4(1.0f));

        render.draw(    shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[3].position.x - 200.0f, -34.0f, circle.vertices[3].position.z - 200.0f),
                        270.0f
                        );

        
        blue_2.draw(   shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[4].position.x - 190.0f, -34.0f, circle.vertices[4].position.z - 100.0f),
                        280.0f
                        );

        blue_3.draw(   shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[2].position.x - 150.0f, -34.0f, circle.vertices[2].position.z - 300.0f),
                        260.0f
                        );
                        
        orange.draw(    shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(200.0f + circle.vertices[0].position.x, -31.0f, 0.0f + circle.vertices[0].position.z - 400.0f),
                        180.0f);
        
        
        green.draw(     shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[8].position.x + 200.0f, -43.0f, 0.0f + circle.vertices[8].position.z - 110.0f),
                        50.0f);

        shadowShader.Activate();
        glm::mat4 red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shadowShader.setMat4("model", red_model);
        
        red_1.draw(     shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[11].position.x + 110.0f, circle.vertices[11].position.z - 365.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));

        
        shadowShader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shadowShader.setMat4("model", red_model);
        
        red_1.draw(     shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[0].position.x - 5.0f, circle.vertices[0].position.z - 390.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));


        
        shadowShader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shadowShader.setMat4("model", red_model);
        
        red_1.draw(     shadowShader, 
                        camera, 
                        SCR_WIDTH, 
                        SCR_HEIGHT, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[0].position.x - 20.0f, circle.vertices[0].position.z - 390.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));

        // purple.draw(     shadowShader, 
        //         camera, 
        //         SCR_WIDTH, 
        //         SCR_HEIGHT, 
        //         glm::mat4(1.0f), 
        //         glm::vec3(1.0f, 1.0f, 1.0f), 
        //         glm::vec3(0.0f, 0.0f ,0.0f),
        //         0.0f
        //     );

        
        shadowShader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shadowShader.setMat4("model", red_model);
        

        yellow.draw(     shadowShader, 
                camera, 
                SCR_WIDTH, 
                SCR_HEIGHT, 
                red_model, 
                glm::vec3(1.5f, 1.5f, 1.5f), 
                glm::vec3(circle.vertices[0].position.x - 20.0f, circle.vertices[0].position.z - 60.0f, -30.0f),
                -90.0f,
                glm::vec3(1.0f, 0.0f, 0.0f)
            );

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
        
        glm::vec3 translation_offset = processInput(window, player.position, camera.Front);

        player.apply_gravity = true;

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
        
        if (player.collision.CheckCollision(aabb, testAABB) || player.collision.CheckMassCollision(aabb, world_boundary.aabbs)) {
            move = false;
            gravity =  glm::vec3(0.0f, 0.0f, 0.0f);
            translation_offset =  glm::vec3(0.0f, 0.0f, 0.0f);
        }
        else {
            move = true;
        }

        if (move) {
            player.position = future_position;
            camera.Position = player.position + glm::vec3(-40.0f * camera.Front.x, 40.0f, -40.0f * camera.Front.z); 
        }
        
        playerModel = glm::translate(playerModel, translation_offset + gravity);

        playerShader.Activate();
        playerShader.setMat4("projection", projection);
        playerShader.setMat4("view", view);
        playerShader.setMat4("model", playerModel);
        // playerModel = glm::scale(playerModel, glm::vec3(0.5f,0.5f, 0.5f));
        player.Draw(playerShader);
        playerShader.setMat4("model", glm::mat4(1.0f));
        player.collision.generateBoundingBoxMesh(aabb, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)).Draw(playerShader);

        // for (AABB world_aabb : world_boundary.aabbs) {
        //     player.collision.generateBoundingBoxMesh(world_aabb, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)).Draw(playerShader);
        // }

        shadowShader.Activate();
        shadowShader.setMat4("projection", projection);
        shadowShader.setMat4("view", view);
        
        testModel = glm::mat4(1.0f); 
        testModel = glm::translate(testModel, glm::vec3(0.0f, 0.0f, 0.0f));
        shadowShader.setMat4("model", glm::translate(testModel, glm::vec3(0.0f, -50.0f, 0.0f)));
        shadowShader.setVec4("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
        // circle.collision.generateBoundingBoxMesh(circleAABB, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)).Draw(shadowShader);
        plane.Draw(shadowShader);

        shadowShader.Activate();
        test.apply_gravity = false;
        testingModel = glm::translate(testingModel, test.ApplyGravity());
        shadowShader.setMat4("projection", projection);
        shadowShader.setMat4("view", view);
        shadowShader.setMat4("model", testingModel);
        test.Draw(shadowShader);

        shadowShader.setMat4("model", glm::mat4(1.0f));
        test.collision.generateBoundingBoxMesh(testAABB, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)).Draw(shadowShader);

        grassShader.Activate();
        grassShader.setMat4("projection", projection);
        grassShader.setMat4("view", view);
        grass.Draw(grassShader, false, true, grass_renderer.models);


        animator.UpdateAnimation(deltaTime);
        animationShader.Activate();
        auto transforms = animator.GetFinalBoneMatrices();

		for (int i = 0; i < transforms.size(); ++i)
			animationShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

		glm::mat4 animated_model = glm::mat4(1.0f);
		animated_model = glm::translate(animated_model, glm::vec3(0.0f, -30.0f, 0.0f)); // translate it down so it's at the center of the scene
		animated_model = glm::scale(animated_model, glm::vec3(1.0f, 1.0f, 1.0f));	
        animationShader.setMat4("projection", projection);
        animationShader.setMat4("view", view);
		animationShader.setMat4("model", animated_model);
		animatedModel.Draw(animationShader);

        
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

