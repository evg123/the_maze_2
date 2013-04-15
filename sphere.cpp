#include "sphere.hpp"

Sphere::Sphere() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
    radius_ = 1;
}

Sphere::Sphere(int x, int y, int z, int radius) {
    x_ = x;
    y_ = y;
    z_ = z;
    radius_ = radius;
}

float Sphere::collidesWith(Sphere other, int xOff, int yOff, int zOff) {
    // only do collision in x-y space for now.
    other.z_ = z_;
    Sphere new_pos(x_, y_, other.z_, radius_);
    new_pos.offset(xOff, yOff, zOff);
    int new_dist = new_pos.distance(other);
    if (new_dist < (radius_+other.radius_)) {
        int old_dist = distance(other);
        int final_dist = radius_ + other.radius_;
        float dist_scale = old_dist / final_dist;
        return dist_scale;
    }
    return 1.0f;
}

float Sphere::distance(Sphere other) {
    long int dx = other.x_ - x_;
    long int dy = other.y_ - y_;
    long int dz = other.z_ - z_;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

void Sphere::offset(int xOff, int yOff, int zOff) {
    x_ += xOff;
    y_ += yOff;
    z_ += zOff;
}
