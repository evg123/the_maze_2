#ifndef THE_MAZE_HPP
#define THE_MAZE_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <fstream>
#include <streambuf>
#include <vector>

#include "common.hpp"
#include "gli/gli.hpp"
#include "gli/gtx/gl_texture2d.hpp"
#include "models/model.hpp"
#include "models/player.hpp"
#include "models/surface.hpp"
#include "models/wall_segment.hpp"
#include "models/projectile.hpp"

class TheMaze2 {

public:
	glm::mat4 proj_matrix_;
    Player player_;
	std::vector<Model*> walls_;
    std::vector<Surface*> surfaces_;
    std::vector<Projectile*> projectiles_;
	std::vector<glm::vec3> light_positions_ws_;
    
private:
	GLuint vbo_;
    GLuint ebo_;
	GLuint vao_;
	GLuint shader_prog_;
    
    int window_width_;
    int window_height_;
	GLint position_attr_;
    GLint normal_attr_;
	GLint text_coord_attr_;
    GLint color_attr_;
	GLint proj_uni_;
	GLint view_uni_;
	GLint vert_model_uni_;
    GLint norm_model_uni_;
	GLint light_pos_cs_uni_;
    GLint light_count_uni_;
    GLint text_samp_uni_;
    
    GLint wall_text_;
	
public:
    static TheMaze2& getInstance() {
        static TheMaze2 maze;
        return maze;
    }
	void render();
    void initGl();
	void initVbo();
	void initVao();
	void initShaders();
	void initAttributes();
    void initTextures();
    void handleMovement(double delta);
    static void handleKeyInput(int key, int action);
    static void handleMouseButtonInput(int button, int action);
    static void handleWindowResize(int width, int height);
	void addWall(int xPos, int yPos, int zPos);
    void addWalls(int xPos, int yPos, int zPos, int xOff, int yOff);
    void addSurface(int xPos, int yPos, int zPos);
    void addProjectile(int xPos, int yPos, int zPos, float xFacing, float yFacing);
    void addLight(float xPos, float yPos, float zPos);
    void handleMouseInput(double time_delta);
    
private:
	TheMaze2();
    TheMaze2(TheMaze2 const&);
    void operator=(TheMaze2 const&);
    GLuint shaderFromFile(std::string filename, GLenum type);
    
};

#endif
