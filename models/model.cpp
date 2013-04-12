#include "model.hpp"

Model::Model() {
	xPos_ = 0;
	yPos_ = 0;
    zPos_ = 0;
    facing_ = 0;
    move_dir_ = DIR_NONE;
    speed_ = 5500;
    rot_speed_ = .9;
    rot_dir_ = DIR_NONE;
    scale_ = 1.0f;
}

void Model::updateModelMatrix() {
	
	//model_matrix_ = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
	//model_matrix_ = glm::translate(model_matrix_, glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    
	//model_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(gl_x_pos(), 0.0f, gl_y_pos()));
    //model_matrix_ = glm::rotate(model_matrix_, radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 a = glm::translate(glm::mat4(1.0f), glm::vec3(gl_x_pos(), gl_z_pos(), gl_y_pos()));
    glm::mat4 b = glm::rotate(glm::mat4(1.0f), radsToDegrees(facing_), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 c = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, scale_));
    model_matrix_ = a * b * c;
    
    
	
}

void Model::move(double delta) {
    if (move_dir_ == DIR_FORWARD) {
        float x = cos(facing_);
        float y = sin(facing_);
        xPos_ += delta * cos(facing_) * speed_;
        yPos_ += delta * sin(facing_) * speed_;
    } else if (move_dir_ == DIR_REVERSE) {
        xPos_ -= delta * cos(facing_) * speed_;
        yPos_ -= delta * sin(facing_) * speed_;
    } else if (move_dir_ == DIR_LEFT) {
        float strafe_face = facing_ + M_PI/2;
        xPos_ -= delta * cos(strafe_face) * speed_;
        yPos_ -= delta * sin(strafe_face) * speed_;
    } else if (move_dir_ == DIR_RIGHT) {
        float strafe_face = facing_ - M_PI/2;
        xPos_ -= delta * cos(strafe_face) * speed_;
        yPos_ -= delta * sin(strafe_face) * speed_;
    }
    
    if (rot_dir_ == DIR_LEFT) {
        facing_ -= delta * rot_speed_;
    } else if (rot_dir_ == DIR_RIGHT) {
        facing_ += delta * rot_speed_;
    }
    
    /*
    if (facing_ < 0) {
        float a = floor((-facing_ / (2*M_PI))) * (2*M_PI);
        facing_ += floor((-facing_ / (2*M_PI))) * (2*M_PI);
        float x = radsToDegrees(facing_);
    }
    if (facing_ > 2*M_PI) {
        float b = floor((facing_ / (2*M_PI))) * (2*M_PI);
        facing_ -= floor((facing_ / (2*M_PI))) * (2*M_PI);
        float x = radsToDegrees(facing_);
    }
    
	*/
}
