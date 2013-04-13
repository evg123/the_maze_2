#ifndef WALL_SEGMENT_HPP
#define WALL_SEGMENT_HPP

#include "../common.hpp"
#include "model.hpp"

class WallSegment : public Model {

public:
	static GLfloat verts_[WALL_SEGMENT_VBO_COUNT];
    static GLushort elems_[WALL_SEGMENT_EBO_COUNT];
	
private:
	
	
public:
	WallSegment();
	void render();
	
private:
	
	
};

#endif
