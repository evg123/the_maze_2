#include "model.hpp"

Model::Model() {
	
    xFacing_ = (3.0f/2.0f)*M_PI;
    yFacing_ = 0;
    move_dir_ = DIR_NONE;
    strafe_dir_ = DIR_NONE;
    speed_ = 7500;
    rot_speed_ = .9;
    rot_dir_ = DIR_NONE;
    setScale(1.0f);
}

void Model::updateModelMatrix() {
    
    model_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(gl_x_pos(), gl_z_pos(), gl_y_pos()));
    model_matrix_ = glm::rotate(model_matrix_, radsToDegrees(-xFacing_+(3.0f/2.0f)*M_PI), glm::vec3(0.0f, 1.0f, 0.0f));
    model_matrix_ = glm::scale(model_matrix_, glm::vec3(getScale(), getScale(), getScale()));
    
}

void Model::update(double delta) {
    
    if (xFacing_ < 0) {
        xFacing_ += floor((-xFacing_ / (2*M_PI))) * (2*M_PI);
    } else if (xFacing_ > 2*M_PI) {
        xFacing_ -= floor((xFacing_ / (2*M_PI))) * (2*M_PI);
    }
    
    if (yFacing_ > M_PI/2) {
        yFacing_ = M_PI/2;
    } else if (yFacing_ < -M_PI/2) {
        yFacing_ = -M_PI/2;
    }
    
}

void Model::move(double delta, std::vector<Model*> walls) {
    int xOff = 0;
    int yOff = 0;
    if (move_dir_ == DIR_FORWARD) {
        xOff += delta * cos(xFacing_) * speed_;
        yOff += delta * sin(xFacing_) * speed_;
    } else if (move_dir_ == DIR_REVERSE) {
        xOff -= delta * cos(xFacing_) * speed_;
        yOff -= delta * sin(xFacing_) * speed_;
    }
    
    if (strafe_dir_ == DIR_LEFT) {
        float strafe_face = xFacing_ + M_PI/2;
        xOff -= delta * cos(strafe_face) * speed_;
        yOff -= delta * sin(strafe_face) * speed_;
    } else if (strafe_dir_ == DIR_RIGHT) {
        float strafe_face = xFacing_ - M_PI/2;
        xOff -= delta * cos(strafe_face) * speed_;
        yOff -= delta * sin(strafe_face) * speed_;
    }
    
    float final_scale = 1.0f;
    for (Model *ws : walls) {
        float dist_scale = pos_.collidesWith(ws->pos_, xOff, yOff, 0);
        if (dist_scale < final_scale) {
            final_scale = dist_scale;
        }
    }
    pos_.offset(xOff*final_scale, yOff*final_scale, 0);
    
    if (rot_dir_ == DIR_LEFT) {
        xFacing_ -= delta * rot_speed_;
    } else if (rot_dir_ == DIR_RIGHT) {
        xFacing_ += delta * rot_speed_;
    }
    
}
