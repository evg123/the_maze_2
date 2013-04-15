#include "surface.hpp"

GLfloat Surface::verts_[] = {
	// position(3) normal(3), texture(2) color(3)
	-0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
     
};

GLushort Surface::elems_[] = {
	 2,  1,  0, 
     1,  2,  3, 
     
};

Surface::Surface() 
	: Model() {
    setScale(1000.0f);
	vbo_pos_ = (void*)(SURFACE_VBO_POS*sizeof(GLfloat));
	vbo_count_ = SURFACE_VBO_COUNT;
    ebo_pos_ = (void*)(SURFACE_EBO_POS*sizeof(GLushort));
	ebo_count_ = SURFACE_EBO_COUNT;
}
