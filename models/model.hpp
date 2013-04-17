#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include "../common.hpp"
#include "../sphere.hpp"

class Model {
	
public:
	void* vbo_pos_;
	int vbo_count_;
    void* ebo_pos_;
	int ebo_count_;
	glm::mat4 model_matrix_;
    Sphere pos_;
    float xFacing_;
    float yFacing_;
    MOVE_DIR move_dir_;
    MOVE_DIR strafe_dir_;
    int speed_;
    float rot_speed_;
    MOVE_DIR rot_dir_;
    float radsToDegrees(float radians) { return (radians * 180) / M_PI; };
    
protected:
	float gl_x_pos() { return pos_.x_ / 1000.0f; };
	float gl_y_pos() { return pos_.y_ / 1000.0f; };
    float gl_z_pos() { return pos_.z_ / 1000.0f; };
    float scale_;

public:
    Model();
	void updateModelMatrix();
    void move(double delta, std::vector<Model*> walls);
    void update(double delta);
    float getScale() { return scale_; };
    void setScale(float scale) { scale_ = scale; pos_.radius_*=scale; };
	
private:
	
	
};

#endif

