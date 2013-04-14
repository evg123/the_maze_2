#include "player.hpp"

Player::Player() 
    : Model() {
	xFacing_ = (3.0f/2.0f)*M_PI;
    yFacing_ = 0;
    look_speed_ = 0.05;
}

void Player::updateModelMatrix() {
	
	//model_matrix_ = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
	//model_matrix_ = glm::translate(model_matrix_, glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    
	//model_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    //model_matrix_ = glm::rotate(model_matrix_, radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //glm::mat4 a = glm::translate(glm::mat4(1.0f), glm::vec3(-gl_x_pos(), 0.0f, -gl_y_pos()));
    //glm::mat4 b = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    //model_matrix_ = a* b;
    
    glm::vec3 position = glm::vec3(gl_x_pos(), 0.0f, gl_y_pos());
    glm::vec3 front_dir = glm::vec3(cos(xFacing_)*cos(yFacing_), sin(yFacing_), sin(xFacing_)*cos(yFacing_));
    glm::vec3 right_dir = glm::vec3(cos(xFacing_ - M_PI/2), 0.0f, sin(xFacing_ - M_PI/2));
    glm::vec3 up = glm::cross(front_dir, right_dir);
    model_matrix_ = glm::lookAt(position, position+front_dir, up);
}
