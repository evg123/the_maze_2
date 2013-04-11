#ifndef MODEL_HPP
#define MODEL_HPP

#include "../common.hpp"

class Model {
	
public:
	void* vbo_pos_;
	int vbo_count_;
    void* ebo_pos_;
	int ebo_count_;
	glm::mat4 model_matrix_;
    int xPos_, yPos_;
    float facing_;
    MOVE_DIR move_dir_;
    int speed_;
    float rot_speed_;
    MOVE_DIR rot_dir_;
    float radsToDegrees(float radians) { return (radians * 180) / M_PI; };
    
protected:
	float gl_x_pos() { return xPos_ / 1000.0f; };
	float gl_y_pos() { return yPos_ / 1000.0f; };

public:
    Model();
	void render();
	void updateModelMatrix();
    void move(double delta);
	
private:
	
	
};

#endif

