#include "player.hpp"

Player::Player() 
    : Model() {
	
}

void Player::updateModelMatrix() {
	
	//model_matrix_ = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
	//model_matrix_ = glm::translate(model_matrix_, glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    
	//model_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    //model_matrix_ = glm::rotate(model_matrix_, radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //glm::mat4 a = glm::translate(glm::mat4(1.0f), glm::vec3(-gl_x_pos(), 0.0f, -gl_y_pos()));
    //glm::mat4 b = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    //model_matrix_ = a* b;
    
    glm::vec3 direction = glm::vec3(cos(facing_), 0.0f, sin(facing_));
    glm::vec3 position = glm::vec3(gl_x_pos(), 0.0f, gl_y_pos());
    model_matrix_ = glm::lookAt(position, position+direction, glm::vec3(0.0f, 1.0f, 0.0f));
}
