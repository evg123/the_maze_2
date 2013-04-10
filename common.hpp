#ifndef COMMON_HPP
#define COMMON_HPP

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define _USE_MATH_DEFINES
#include <math.h>


#define WALL_SEGMENT_VBO_POS 0

#define WALL_SEGMENT_EBO_POS 0

enum MOVE_DIR {
    DIR_NONE,
    DIR_FORWARD,
    DIR_REVERSE,
    DIR_LEFT,
    DIR_RIGHT,
};

#endif

