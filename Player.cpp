#include "Player.h"

Player::Player() {
    player =    aModel("./animations/player_walking.dae", false);
    player_object = aModel("./animations/guy_object.obj", false);
    walk_animation = Animation("./animations/player_walking.dae", &player);
    idle_animation = Animation("./animations/player_idle.dae", &player);
    jump_animation = Animation("./animations/player_jump.dae", &player);
    player_animator = Animator(&walk_animation);

    aabb = player_object.collision.calculateBoundingBox();
}

void Player::Draw(
    Shader &shader,
    aCamera &camera,
    glm::vec3 translation, 
    AABB circle_aabb,
    std::vector<AABB> world_boundary_aabbs,
    glm::mat4 projection,
    glm::mat4 view,
    float delta_time
) {
    
    glm::vec3 translation_offset = translation; 
    glm::vec3 instantaneus_velocity = player.ApplyGravity();
    glm::vec3 future_position = position + translation_offset + instantaneus_velocity;

    aabb.position += future_position;
    
    if (glm::vec3(position.x, 0.0f, position.z) == glm::vec3(future_position.x, 0.0f, future_position.z)) {
        moving = false;
    } else {
        moving = true;
    }
    // check collision if on ground
    if (player.collision.CheckCollision(aabb, circle_aabb))
    {
        move = true;
        instantaneus_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        future_position = position + translation_offset;
    }

    if (player.collision.CheckMassCollision(aabb, world_boundary_aabbs))
    {
        move = false;
        instantaneus_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        translation_offset = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    else
    {
        move = true;
    }

    if (move)
    {
        position = future_position;
        camera.Position = position + glm::vec3(-40.0f * camera.Front.x, 40.0f, -40.0f * camera.Front.z);
    }

    // play the currect animation
    if (moving && move) {
        player_animator.SetNewAnimation(&walk_animation);
    }

    if (!move || !moving) {
        player_animator.SetNewAnimation(&idle_animation);
    }

    if (position.y > -35.0f) {
        player_animator.SetNewAnimation(&jump_animation);
    }

    player_animator.UpdateAnimation(delta_time);

    auto transforms = player_animator.GetFinalBoneMatrices();
    shader.Activate();

    for (int i = 0; i < transforms.size(); ++i)
        shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

    model = glm::translate(model, translation_offset + instantaneus_velocity);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
    shader.setVec4("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setVec3("camPos", camera.Position);

    player.Draw(shader);

    shader.setMat4("model", glm::mat4(1.0f));
    model = glm::rotate(model, glm::radians(camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}