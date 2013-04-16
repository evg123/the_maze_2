#include "projectile.hpp"

GLfloat Projectile::verts_[] = {
	// position(3) normal(3), texture(2) color(3)
	 0.0f,  0.0f, -2.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  0.3f, 0.0f, 0.0f, 
	-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  0.3f, 0.0f, 0.0f, 
	 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  0.3f, 0.0f, 0.0f, 
     
     0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  0.3f, 0.0f, 0.0f, 
	 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  0.3f, 0.0f, 0.0f, 
    -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  0.3f, 0.0f, 0.0f, 
     
     0.0f,  0.0f, -2.0f,  0.4f, -0.4f,  0.0f,  0.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
	 0.5f,  0.5f,  0.0f,  0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
	 0.0f, -0.5f,  0.0f,  0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
     
     0.0f,  0.0f,  2.0f,  0.4f, -0.4f,  0.0f,  0.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
	 0.0f, -0.5f,  0.0f,  0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
     0.5f,  0.5f,  0.0f,  0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.3f, 0.0f, 
     
     0.0f,  0.0f, -2.0f, -0.4f, -0.4f,  0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.3f, 
	 0.0f, -0.5f,  0.0f, -0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 0.3f, 
    -0.5f,  0.5f,  0.0f, -0.4f, -0.4f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.3f, 
     
     0.0f,  0.0f,  2.0f, -0.4f, -0.4f,  0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.3f, 
    -0.5f,  0.5f,  0.0f, -0.4f, -0.4f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.3f, 
     0.0f, -0.5f,  0.0f, -0.4f, -0.4f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 0.3f, 
};

GLushort Projectile::elems_[] = {
	 0,  1,  2, 
     3,  4,  5, 
     6,  7,  8, 
     9, 10, 11, 
    12, 13, 14, 
    15, 16, 17,     
};

Projectile::Projectile() 
	: Model() {
	vbo_pos_ = (void*)(PROJECTILE_VBO_POS);
	vbo_count_ = PROJECTILE_VBO_COUNT;
    ebo_pos_ = (void*)(PROJECTILE_EBO_POS);
	ebo_count_ = PROJECTILE_EBO_COUNT;
    pos_.radius_ = 500;
}

Projectile::Projectile(int xPos, int yPos, int zPos, float xFacing, float yFacing) 
	: Model() {
	vbo_pos_ = (void*)(PROJECTILE_VBO_POS);
	vbo_count_ = PROJECTILE_VBO_COUNT;
    ebo_pos_ = (void*)(PROJECTILE_EBO_POS);
	ebo_count_ = PROJECTILE_EBO_COUNT;
    pos_.radius_ = 500;
    pos_.x_ = xPos;
    pos_.y_ = yPos;
    pos_.z_ = zPos;
    xFacing_ = xFacing;
    yFacing_ = yFacing;
}
