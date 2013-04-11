#include "wall_segment.hpp"

GLfloat WallSegment::verts_[] = {
	// position(3) normal(3), texture(2) color(3)
	-0.5f,  5.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	-0.5f, -5.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f,  5.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f, -5.0f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
     
     0.5f,  5.0f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f, -5.0f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f,  5.0f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f, -5.0f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
     
     0.5f,  5.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	 0.5f, -5.0f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
	-0.5f,  5.0f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	-0.5f, -5.0f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
    
    -0.5f,  5.0f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
	-0.5f, -5.0f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
    -0.5f,  5.0f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 
    -0.5f, -5.0f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 
    
};

GLushort WallSegment::elems_[] = {
	 0,  1,  2, 
     3,  2,  1, 
     4,  5,  6, 
     7,  6,  5, 
     8,  9, 10, 
    11, 10,  9, 
    12, 13, 14, 
    15, 14, 13, 
};

WallSegment::WallSegment() 
	: Model() {
	vbo_pos_ = (void*)(WALL_SEGMENT_VBO_POS*sizeof(GLfloat));
	vbo_count_ = WALL_SEGMENT_VERT_COUNT;
    ebo_pos_ = (void*)(WALL_SEGMENT_EBO_POS*sizeof(GLushort));
	ebo_count_ = WALL_SEGMENT_ELEM_COUNT;
}

/*
 * // position(3) texture(2) color(3)
	-0.5f,  5.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
	-0.5f, -5.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
	 0.5f,  5.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
	 0.5f, -5.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
	 0.5f,  5.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
	 0.5f, -5.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
	-0.5f,  5.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
	-0.5f, -5.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
    -0.5f,  5.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
    -0.5f, -5.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
*/
