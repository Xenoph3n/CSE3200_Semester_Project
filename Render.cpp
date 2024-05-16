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
    
    animated_model_1 = aModel("./vampire/dancing_vampire.dae", false);
    animation_1 =  Animation("./vampire/dancing_vampire.dae", &animated_model_1);
    animator_1 = Animator(&animation_1);
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
        animator_0.UpdateAnimation(deltaTime);

        shader.Activate();
        auto transforms = animator_0.GetFinalBoneMatrices();

		glm::mat4 animated_model = glm::mat4(1.0f);
        glm::vec3 base_position = glm::vec3(circle.vertices[0].position.x - 40.0f, -40.0f, circle.vertices[0].position.z - 10.0f);
        glm::vec3 pos = glm::vec3(circle.vertices[0].position.x - 40.0f, base_position.y, circle.vertices[0].position.z - 10.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

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
                    animator_1.UpdateAnimation(deltaTime);
                    animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));	
                    transforms = animator_1.GetFinalBoneMatrices();

                    for (int i = 0; i < transforms.size(); ++i)
                        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    shader.setMat4("model", animated_model);
                    animated_model_1.Draw(shader);
                } 

                base_position = glm::vec3(base_position.x - 10.0f, base_position.y, base_position.z - 8.5f);
            }
            base_position = glm::vec3(pos.x - 5.0f, pos.y + 10.0f, pos.z + 5.0f);
            pos = base_position;
        } 

        base_position = glm::vec3(circle.vertices[0].position.x + 60.0f, -40.0f, circle.vertices[0].position.z - 25.0f);
        pos = glm::vec3(circle.vertices[0].position.x + 60.0f, -40.0f, circle.vertices[0].position.z - 25.0f);
        
        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 12; i++) {        
                animated_model = glm::mat4(1.0f);
                animated_model = glm::translate(animated_model, base_position);
                animated_model = glm::scale(animated_model, glm::vec3(2.0f, 2.0f, 2.0f));
                animated_model = glm::rotate(animated_model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.setMat4("model", animated_model);
                animated_model_0.Draw(shader);
                base_position = glm::vec3(base_position.x + 10.0f, base_position.y, base_position.z - 8.5f);
            }
            base_position = glm::vec3(pos.x + 5.0f, pos.y + 10.0f, pos.z + 5.0f);
            pos = base_position;
        } 
}