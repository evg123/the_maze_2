#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "../common.hpp"
#include "model.hpp"

class Surface : public Model {

public:
	static GLfloat verts_[SURFACE_VBO_COUNT];
    static GLushort elems_[SURFACE_EBO_COUNT];
	
private:
	
	
public:
	Surface();
	void render();
	
private:
	
	
};

#endif
