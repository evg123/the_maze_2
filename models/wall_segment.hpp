#ifndef WALL_SEGMENT_HPP
#define WALL_SEGMENT_HPP

#include "../common.hpp"
#include "../model.hpp"

#define WALL_SEGMENT_VERT_COUNT 176
#define WALL_SEGMENT_ELEM_COUNT 24

class WallSegment : public Model {

public:
	static GLfloat verts_[WALL_SEGMENT_VERT_COUNT];
    static GLushort elems_[WALL_SEGMENT_ELEM_COUNT];
	
private:
	
	
public:
	WallSegment();
	void render();
	
private:
	
	
};

#endif
