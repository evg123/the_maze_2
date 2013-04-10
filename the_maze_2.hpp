#ifndef THE_MAZE_HPP
#define THE_MAZE_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <fstream>
#include <streambuf>
#include <vector>

#include "common.hpp"
#include "model.hpp"
#include "models/player.hpp"
#include "models/wall_segment.hpp"


class TheMaze2 {

public:
    static TheMaze2& getInstance() {
        static TheMaze2 maze;
        return maze;
    }
	glm::mat4 proj_matrix_;
    Player player_;
	std::vector<WallSegment> walls_;
	glm::vec3 light_pos_ws_;
    
private:
	GLuint vbo_;
    GLuint ebo_;
	GLuint vao_;
	GLuint shader_prog_;
    
	GLint position_attr_;
    GLint normal_attr_;
	GLint text_coord_attr_;
    GLint color_attr_;
	GLint proj_uni_;
	GLint view_uni_;
	GLint vert_model_uni_;
    GLint norm_model_uni_;
	GLint light_pos_cs_uni_;
	
public:
	void render();
    void initGl();
	void initVbo();
	void initVao();
	void initShaders();
	void initAttributes();
    void handleMovement(double delta);
    static void handleKeyInput(int key, int action);
	
private:
	TheMaze2() {};
    TheMaze2(TheMaze2 const&);
    void operator=(TheMaze2 const&);
    GLuint shaderFromFile(std::string filename, GLenum type);
    
	
};

#endif
