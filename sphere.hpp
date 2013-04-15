#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "common.hpp"

class Sphere {

public:
	int x_, y_, z_;
    int radius_;
    
private:
	
	
public:
    Sphere();
    Sphere(int x, int y, int z, int radius);
    float collidesWith(Sphere other, int xOff, int yOff, int zOff);
    float distance(Sphere other);
    void offset(int xOff, int yOff, int zOff);
    
private:
	
	
};

#endif
