#ifndef __Aspect_h_
#define __Aspect_h_

//#include "Entity381.h"
#include "As3.h"

class Entity381;

class Aspect{
public:
	Aspect(){};
	Entity381* entity;
	virtual void Tick(float dt) = 0;
	virtual ~Aspect(){};

};


class Physics : public Aspect{
public:
	Physics();
	Physics(Entity381* ent);
	void Tick(float dt);

};

Physics::Physics(){

}


Physics::Physics(Entity381* ent){
	entity = ent;
}

class Renderable : public Aspect{

public:
	Renderable();
	Renderable(Entity381* ent);
	void Tick(float dt);
};

Renderable::Renderable(){

}

Renderable::Renderable(Entity381* ent){
	entity = ent;
}



#endif // #ifndef __Aspect_h_
