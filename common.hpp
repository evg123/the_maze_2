#ifndef COMMON_HPP
#define COMMON_HPP

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define _USE_MATH_DEFINES
#include <math.h>


#define WALL_SEGMENT_VERT_COUNT 176
#define WALL_SEGMENT_ELEM_COUNT 24

#define SURFACE_VERT_COUNT 44
#define SURFACE_ELEM_COUNT 6


#define SURFACE_VBO_POS         0
#define WALL_SEGMENT_VBO_POS    (SURFACE_VBO_POS + sizeof(GLfloat)*SURFACE_VERT_COUNT)

#define SURFACE_EBO_POS         0
#define WALL_SEGMENT_EBO_POS    (SURFACE_EBO_POS + sizeof(GLushort)*SURFACE_ELEM_COUNT)

/*
#define WALL_SEGMENT_VBO_POS    0
#define SURFACE_VBO_POS         (WALL_SEGMENT_VBO_POS + sizeof(GLfloat)*WALL_SEGMENT_VERT_COUNT)

#define WALL_SEGMENT_EBO_POS    0
#define SURFACE_EBO_POS         (WALL_SEGMENT_EBO_POS + sizeof(GLushort)*WALL_SEGMENT_ELEM_COUNT)
*/

enum MOVE_DIR {
    DIR_NONE,
    DIR_FORWARD,
    DIR_REVERSE,
    DIR_LEFT,
    DIR_RIGHT,
};

#endif

