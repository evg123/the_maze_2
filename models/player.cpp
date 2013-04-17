#include "player.hpp"

Player::Player() 
    : Model() {
    look_speed_ = 0.05;
    pos_.radius_ = 800;
}

void Player::updateModelMatrix() {
	
    glm::vec3 position = glm::vec3(gl_x_pos(), 0.0f, gl_y_pos());
    glm::vec3 front_dir = glm::vec3(cos(xFacing_)*cos(yFacing_), sin(yFacing_), sin(xFacing_)*cos(yFacing_));
    glm::vec3 right_dir = glm::vec3(cos(xFacing_ - M_PI/2), 0.0f, sin(xFacing_ - M_PI/2));
    glm::vec3 up = glm::cross(front_dir, right_dir);
    model_matrix_ = glm::lookAt(position, position+front_dir, up);
}
