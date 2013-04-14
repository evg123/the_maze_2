#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../common.hpp"
#include "model.hpp"

class Player : public Model {
	
public:
	double look_speed_;
    
private:

public:
    Player();
	void updateModelMatrix();
    
private:
	
	
};

#endif

