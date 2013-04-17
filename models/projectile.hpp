#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../common.hpp"
#include "model.hpp"

class Projectile : public Model {

public:
	static GLfloat verts_[PROJECTILE_VBO_COUNT];
    static GLushort elems_[PROJECTILE_EBO_COUNT];
	
private:
	
	
public:
	Projectile();
    Projectile(int xPos, int yPos, int zPos, float xFacing, float yFacing);
    
private:
	void init();
	
};

#endif
