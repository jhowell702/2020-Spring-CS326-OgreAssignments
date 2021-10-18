#include <Aspect.h>

#include <Entity381.h>

Physics::Physics(){

}

Physics::Physics(Entity381* ent){
	ent381 = ent;
}

void Physics::Tick(float dt){

		std::cout << "Testing 1" << std::endl;

		int des = ent381->getDesiredSpeed();
		int speed = ent381->getSpeed();
		int accel = ent381->getAcel();

		if(speed < des){
			speed += accel * dt;
			if(speed > des){
				std::cout << "Exceeding desired speed, setting to desired of:" << des << std::endl;
				speed = des;
			}

		}else if(speed > des){
			speed -= accel * dt;
			if(speed < 0){
				std:: cout << "setting to 0" << std::endl;
				speed = 0;
			}
		}

		std::cout << "Testing 2" << std::endl;

		Ogre::Degree head = ent381->getHeading();
		Ogre::Degree desHead = ent381->getDesiredHeading();
		Ogre::Degree tR = ent381->getTurnRate();

		if(head < desHead){

			head += tR;
			if(head > desHead){
				head = desHead;
			}

		}else if(head > desHead){
			head -= tR;
			if(head < desHead){
				head = desHead;
			}
		}

		std::cout << "Testing 3" << std::endl;

		ent381->setHeading(head);
		ent381->setSpeed(speed);

		Ogre::Vector3 newPos = Ogre::Vector3::ZERO;

		newPos.x += speed * Ogre::Math::Cos(ent381->getHeading());

		newPos.z += speed * Ogre::Math::Sin(ent381->getHeading());

		std::cout << "Testing 4" << std::endl;

		ent381->setVelocity(newPos);
		ent381->updatePosition(dt);
}

void Renderer::Tick(float dt){
	ent381->getNode()->setOrientation(Ogre::Quaternion(-(ent381->getHeading()),Ogre::Vector3(0,1,0)));
	ent381->getNode()->setPosition(ent381->getPos());
}

Physics::~Physics(){

}

Renderer::~Renderer(){

}

Renderer::Renderer(){

}

Renderer::Renderer(Entity381* ent){
	ent381 = ent;
}
