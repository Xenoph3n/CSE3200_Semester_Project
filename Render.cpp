#include "Render.h"

void Render::initialize(aCamera& camera, Shader& shader, int screen_width, int screen_height) {
    render.get_file_list("./stadium/blue_2");
    blue_2.get_file_list("./stadium/blue_1");
    blue_3.get_file_list("./stadium/blue_3");
    orange.get_file_list("./stadium/orange");
    green.get_file_list("./stadium/green");
    red.get_file_list("./stadium/red");
    yellow.get_file_list("./stadium/yellow");
    purple.get_file_list("./stadium/purple");
    
    render.render(shader, camera, screen_width, screen_height);           
    blue_2.render(  shader, camera, screen_width, screen_height);
    blue_3.render(  shader, camera, screen_width, screen_height);
    orange.render(  shader, camera, screen_width, screen_height);
    green.render(   shader, camera, screen_width, screen_height );
    red.render(     shader, camera, screen_width, screen_height);
    yellow.render(  shader, camera, screen_width, screen_height);
    purple.render(  shader, camera, screen_width, screen_height);

    animated_model_0 = aModel("./animations/wave.dae", false);
    animation_0 =  Animation("./animations/wave.dae", &animated_model_0);
    animator_0 = Animator(&animation_0);
    
    animated_model_1 = aModel("./animations/dance.dae", false);
    animation_1 =  Animation("./animations/dance.dae", &animated_model_1);
    animator_1 = Animator(&animation_1);

    animated_model_2 = aModel("./animations/jump.dae", false);
    animation_2 =  Animation("./animations/jump.dae", &animated_model_0);
    animator_2 = Animator(&animation_2);
    
}

void Render::drawBuildings(aCamera& camera, Shader& shader, Circle& circle, int screen_width, int screen_height, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
        shader.Activate();
        shader.setMat4("model",glm::mat4(1.0f));

        render.draw(    shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[3].position.x - 200.0f, -34.0f, circle.vertices[3].position.z - 200.0f),
                        270.0f
                        );

        blue_2.draw(   shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[4].position.x - 190.0f, -34.0f, circle.vertices[4].position.z - 100.0f),
                        280.0f
                        );

        blue_3.draw(   shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[2].position.x - 150.0f, -34.0f, circle.vertices[2].position.z - 300.0f),
                        260.0f
                        );
                        
        orange.draw(    shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(200.0f + circle.vertices[0].position.x, -31.0f, 0.0f + circle.vertices[0].position.z - 400.0f),
                        180.0f);
        
        
        green.draw(     shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        glm::mat4(1.0f), 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[8].position.x + 200.0f, -43.0f, 0.0f + circle.vertices[8].position.z - 110.0f),
                        50.0f);

        shader.Activate();
        glm::mat4 red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", red_model);
        
        red.draw(     shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[11].position.x + 110.0f, circle.vertices[11].position.z - 365.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));

        
        shader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", red_model);
        
        red.draw(     shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[0].position.x - 5.0f, circle.vertices[0].position.z - 390.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));


        
        shader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", red_model);
        
        red.draw(     shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        red_model, 
                        glm::vec3(1.2f, 1.0f, 1.0f), 
                        glm::vec3(circle.vertices[0].position.x - 20.0f, circle.vertices[0].position.z - 390.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f));

        shader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", red_model);
        
        yellow.draw(     shader, 
                camera, 
                screen_width, 
                screen_height, 
                red_model, 
                glm::vec3(1.5f, 1.5f, 1.5f), 
                glm::vec3(circle.vertices[0].position.x - 20.0f, circle.vertices[0].position.z - 60.0f, -30.0f),
                -90.0f,
                glm::vec3(1.0f, 0.0f, 0.0f)
        );
        
        shader.Activate();
        red_model = glm::mat4(1.0f);
        red_model = glm::rotate(red_model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("model", red_model);

        purple.draw(    shader, 
                        camera, 
                        screen_width, 
                        screen_height, 
                        red_model, 
                        glm::vec3(1.0f, 1.0f, 1.0f), 
                        glm::vec3(0.0f, 200.0f, -45.0f),
                        -90.0f,
                        glm::vec3(1.0f, 0.0f, 0.0f)    
            );

}

void Render::drawAnimations(aCamera& camera, 
                            Shader& shader, 
                            Circle& circle, 
                            int screen_width, 
                            int screen_height, 
                            glm::mat4 model, 
                            glm::mat4 view, 
                            glm::mat4 projection,
                            float deltaTime
                            ) 
{
     

        shader.Activate();
        auto transforms = animator_0.GetFinalBoneMatrices();

		glm::mat4 animated_model = glm::mat4(1.0f);
        
        // right of orange
        glm::vec3 base_position = glm::vec3(circle.vertices[0].position.x - 40.0f, -40.0f, circle.vertices[0].position.z - 10.0f);
        glm::vec3 pos = glm::vec3(circle.vertices[0].position.x - 40.0f, base_position.y, circle.vertices[0].position.z - 10.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        animator_0.UpdateAnimation(deltaTime);
        animator_1.UpdateAnimation(deltaTime);
        animator_2.UpdateAnimation(deltaTime);


        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 12; i++) {

                animated_model = glm::mat4(1.0f);
                animated_model = glm::translate(animated_model, base_position); // translate it down so it's at the center of the scene
                animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));	
                animated_model = glm::rotate(animated_model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.setMat4("model", animated_model);
                
                if (animation_state_matrix[x][i] == 0) {
                   
                    transforms = animator_0.GetFinalBoneMatrices();
                    
                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                    animated_model_0.Draw(shader);
                } 

                if (animation_state_matrix[x][i] == 1) {
               
                    transforms = animator_1.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_1.Draw(shader);
                } 


                if (animation_state_matrix[x][i] == 2) {                    

                    transforms = animator_2.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_2.Draw(shader);
                } 

                base_position = glm::vec3(base_position.x - 10.0f, base_position.y, base_position.z - 8.5f);
            }
            base_position = glm::vec3(pos.x - 5.0f, pos.y + 10.0f, pos.z + 5.0f);
            pos = base_position;
        } 

        // left of orange
        base_position = glm::vec3(circle.vertices[0].position.x + 60.0f, -40.0f, circle.vertices[0].position.z - 25.0f);
        pos = glm::vec3(circle.vertices[0].position.x + 60.0f, -40.0f, circle.vertices[0].position.z - 25.0f);
        
        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 12; i++) {        
                animated_model = glm::mat4(1.0f);
                animated_model = glm::translate(animated_model, base_position);
                animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));
                animated_model = glm::rotate(animated_model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.setMat4("model", animated_model);
                  
                if (animation_state_matrix[x][i] == 0) {
                    
                    transforms = animator_0.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                    animated_model_0.Draw(shader);
                } 

                if (animation_state_matrix[x][i] == 1) {
                   
                    transforms = animator_1.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_1.Draw(shader);
                } 


                if (animation_state_matrix[x][i] == 2) {
                   
                    transforms = animator_2.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_2.Draw(shader);
                } 
                base_position = glm::vec3(base_position.x + 10.0f, base_position.y, base_position.z - 8.5f);
            }
            base_position = glm::vec3(pos.x + 5.0f, pos.y + 10.0f, pos.z + 5.0f);
            pos = base_position;
        } 

        base_position = glm::vec3(circle.vertices[4].position.x - 15.0f, -40.0f, circle.vertices[4].position.z - 5.0f);
        pos = glm::vec3(circle.vertices[4].position.x - 15.0f, -40.0f, circle.vertices[4].position.z - 5.0f);
        
        // stand next to scoreboard
        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 12; i++) {        
                animated_model = glm::mat4(1.0f);
                animated_model = glm::translate(animated_model, base_position);
                animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));
                animated_model = glm::rotate(animated_model, glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.setMat4("model", animated_model);
                  
                if (animation_state_matrix[x][i] == 0) {
                    
                    transforms = animator_0.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                    animated_model_0.Draw(shader);
                } 

                if (animation_state_matrix[x][i] == 1) {
                   
                    transforms = animator_1.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_1.Draw(shader);
                } 


                if (animation_state_matrix[x][i] == 2) {
                   
                    transforms = animator_2.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_2.Draw(shader);
                } 
                base_position = glm::vec3(base_position.x - 11.0f, base_position.y, base_position.z - 6.0f);
            }
            base_position = glm::vec3(pos.x + 3.0f, pos.y + 10.0f, pos.z - 5.0f);
            pos = base_position;
        } 

        base_position = glm::vec3(circle.vertices[8].position.x + 7.0f, -40.0f, circle.vertices[8].position.z + 6.0f);
        pos = glm::vec3(circle.vertices[8].position.x + 7.0f, -40.0f, circle.vertices[8].position.z + 6.0f);

        // grass stand
        for (int x = 0; x < 4; x++) {
         for (int i = 0; i < 12; i++) {        
                animated_model = glm::mat4(1.0f);
                animated_model = glm::translate(animated_model, base_position);
                animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));
                animated_model = glm::rotate(animated_model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.setMat4("model", animated_model);
                  
                if (animation_state_matrix[x][i] == 0) {
                    
                    transforms = animator_0.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                    animated_model_0.Draw(shader);
                } 

                if (animation_state_matrix[x][i] == 1) {
                   
                    transforms = animator_1.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_1.Draw(shader);
                } 


                if (animation_state_matrix[x][i] == 2) {
                   
                    transforms = animator_2.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    animated_model_2.Draw(shader);
                } 
                base_position = glm::vec3(base_position.x + 7.0f, base_position.y, base_position.z - 8.5f);
            }
             base_position = glm::vec3(pos.x - 8.5f, pos.y + 2.0f, pos.z - 7.5f);
            pos = base_position;
        }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
glm::vec3 Render::processInput(aCamera& camera, GLFWwindow *window, glm::vec3 player_position, glm::vec3 direction)
{
    glm::vec3 translation_offset = glm::vec3(0.0f, 0.0f, 0.0f);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        translation_offset = glm::vec3(1.0f, 0.0f, 1.0f) * direction;
        move = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        translation_offset = glm::vec3(1.0f, 0.0f, 1.0f) * -direction;
        move = true;
    }
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        translation_offset = glm::vec3(0.0f, 20.0f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 12; j++) {
                animation_state_matrix[i][j] = animation_state_matrix[i][j] + 1 < 3 ? animation_state_matrix[i][j] + 1 : 0;
            }
        }
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    {
        spot_light_on = !spot_light_on;
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        move = false;
    }

    if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
    {
        move = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.first_clickz = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        camera.first_clickz = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    return translation_offset;
}

