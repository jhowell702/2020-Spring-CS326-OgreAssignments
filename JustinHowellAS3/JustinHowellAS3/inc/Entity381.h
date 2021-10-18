#ifndef __Entity381_h_
#define __Entity381_h_

#include "Aspect.h"

const int UNIT = 5;

enum shipType{
	destroyer, carrier, speedboat, frigate, alien
};

class Entity381{
public:
	Entity381();

	void Tick(float dt){
			aspectArray[0]->Tick(dt);
			aspectArray[1]->Tick(dt);
		};

	void initNode(Ogre::SceneManager* scMgr, Ogre::Entity* entity);

	void initAspects();

	void zeroVectors(){position = Ogre::Vector3::ZERO;
							velocity = Ogre::Vector3::ZERO;};

	Ogre::Vector3 getPos(){return position;};

	void setPos(Ogre::Vector3 pos){position = pos;};
	void setPos(int x, int y, int z){position.x = x;
										position.y = y;
											position.z = z;};

	void setId(int id){entityId = id;};

	void setName(Ogre::String name){entityName = name;};

	Ogre::String getName(){return meshName;};

	void setVelocity(Ogre::Vector3 vel){velocity = vel;};

	Ogre::Vector3 getVelocity(){return velocity;};

	void setAAABstate(bool state){AAABstate = state;};

	void switchAAABstate();

	void setNodePtr(Ogre::SceneNode* ptr){ogreSceneNode = ptr;};

	Ogre::SceneNode* getNode(){return ogreSceneNode;};

	void setOgreEntity(Ogre::Entity* ptr){ogreEntity = ptr;};

	void setMinSpeed(int min){minSpeed = min;};

	void setMaxSpeed(int max){maxSpeed = max;};

	void setSpeed(int newSpeed){speed = newSpeed;};

	int getSpeed(){return speed;};

	void setHeading(Ogre::Degree newHead){heading = newHead;};

	Ogre::Degree getHeading(){return heading;};

	void setDesiredSpeed(int newSpeed){desiredSpeed = newSpeed;};

	int getDesiredSpeed(){return desiredSpeed;};

	void updateDesiredSpeed(int control){

		std::cout << "Speed before" << desiredSpeed << std::endl;

		desiredSpeed += control * UNIT;
		if(desiredSpeed > maxSpeed){
			std::cout << "Exceeded max speed" << std::endl;
			desiredSpeed = maxSpeed;
		}else if(desiredSpeed < 0){
			desiredSpeed = 0;
		}

		std::cout << "Speed after" << desiredSpeed << std::endl;


	};

	void setDesiredHeading(Ogre::Degree dH){desiredHeading = dH;};

	Ogre::Degree getDesiredHeading(){return desiredHeading;};

	void updateDesiredHeading(Ogre::Degree control){
			desiredHeading += control;

	};

	void setAcceleration(int accel){acceleration = accel;};

	int getAcel(){return acceleration;};

	void setTurningRate(Ogre::Degree turnRate){turningRate = turnRate;};

	Ogre::Degree getTurnRate(){return turningRate;};

	void setMeshName(Ogre::String meshName){this->meshName = meshName;};

	void updateVelocity(Ogre::Vector3 dt){
		velocity.x += dt.x;
		velocity.y += dt.y;
		velocity.z += dt.z;
	};

	void updatePosition(float dt){
		position.x = position.x + velocity.x * dt;
		position.y = position.y + velocity.y * dt;
		position.z = position.z + velocity.z * dt;
	};

private:
	int entityId;
	Ogre::String entityName;

	int minSpeed;
	int maxSpeed;

	int speed;
	Ogre::Degree heading;

	int desiredSpeed;
	Ogre::Degree desiredHeading;

	int acceleration;
	Ogre::Degree turningRate;

	Ogre::String meshName;

	Ogre::Vector3 position;
	Ogre::Vector3 velocity;

	Ogre::SceneNode* ogreSceneNode;
	Ogre::Entity* ogreEntity;

	Aspect** aspectArray;

	bool AAABstate;



};

void Entity381::initNode(Ogre::SceneManager* scMgr, Ogre::Entity* entity){


	Ogre::SceneNode* node = scMgr->getRootSceneNode()->createChildSceneNode(entityName);
	//entity->setMaterialName("Examples/Rockwall");
	node->attachObject(entity);

	setNodePtr(node);
	setOgreEntity(entity);
}


void Entity381::initAspects(){
	aspectArray = new Aspect*[2];
	aspectArray[0] = new Physics(this);
	aspectArray[1] = new Renderable(this);
}

class Destroyer : public Entity381{
public:
	Destroyer(Ogre::SceneManager* scMgr, int id){

		Ogre::String meshName = "ddg51.mesh";

		setMeshName(meshName);

		Ogre::String number = Ogre::StringConverter::toString(id);

		Ogre::String entityName = "destroyer" + number;

		setId(id);

		setMinSpeed(1 * UNIT);
		setMaxSpeed(6 * UNIT);

		setAcceleration(5 * UNIT);
		setTurningRate(Ogre::Degree(2));

		setDesiredSpeed(0);
		setDesiredHeading(Ogre::Degree(0));

		setSpeed(0);
		setHeading(Ogre::Degree(0));

		setAAABstate(false);
		zeroVectors();

		Ogre::Entity* entity = scMgr->createEntity("ddg51.mesh");
		initNode(scMgr, entity);

		initAspects();
					;};

};

class Carrier : public Entity381{
public:
	Carrier(Ogre::SceneManager* scMgr, int id){
			Ogre::String meshName = "cvn68.mesh";

			Ogre::String number = Ogre::StringConverter::toString(id);

			Ogre::String entityName = "carrier" + number;
			setName(entityName);

			setId(id);

			setMinSpeed(1 * UNIT);
			setMaxSpeed(12 * UNIT);

			setAcceleration(4 * UNIT);
			setTurningRate(Ogre::Degree(.5));

			setDesiredSpeed(0);
			setDesiredHeading(Ogre::Degree(0));

			setSpeed(0);
			setHeading(Ogre::Degree(0));
			setAAABstate(false);

			zeroVectors();

			Ogre::Entity* entity = scMgr->createEntity("cvn68.mesh");
			initNode(scMgr, entity);

			initAspects();
						;};
};

class Speedboat : public Entity381{
public:
	Speedboat(Ogre::SceneManager* scMgr, int id){
			Ogre::String meshName = "cigarette.mesh";

			Ogre::String number = Ogre::StringConverter::toString(id);

			Ogre::String entityName = "cigarette" + number;
			setName(entityName);

			setId(id);

			setMinSpeed(1 * UNIT);
			setMaxSpeed(15 * UNIT);

			setAcceleration(5 * UNIT);
			setTurningRate(Ogre::Degree(5));

			setDesiredSpeed(0);
			setDesiredHeading(Ogre::Degree(0));

			setSpeed(0);
			setHeading(Ogre::Degree(0));
			setAAABstate(false);

			zeroVectors();

			Ogre::Entity* entity = scMgr->createEntity("cigarette.mesh");
			initNode(scMgr, entity);

			initAspects();
						;};
};

class Frigate : public Entity381{
public:
	Frigate(Ogre::SceneManager* scMgr, int id){
			Ogre::String meshName = "sleek.mesh";

			Ogre::String number = Ogre::StringConverter::toString(id);

			Ogre::String entityName = "frigate" + number;
			setName(entityName);

			setId(id);

			setMinSpeed(1 * UNIT);
			setMaxSpeed(4 * UNIT);

			setAcceleration(3 * UNIT);
			setTurningRate(Ogre::Degree(.25));

			setDesiredSpeed(0);
			setDesiredHeading(Ogre::Degree(0));

			setSpeed(0);
			setHeading(Ogre::Degree(0));
			setAAABstate(false);

			zeroVectors();

			Ogre::Entity* entity = scMgr->createEntity("sleek.mesh");
			initNode(scMgr, entity);

			initAspects();
						;};
};

class Alien : public Entity381{
public:
	Alien(Ogre::SceneManager* scMgr, int id){
			Ogre::String meshName = "alienship.mesh";

			Ogre::String number = Ogre::StringConverter::toString(id);

			Ogre::String entityName = "Alienship" + number;
			setName(entityName);

			setId(id);

			setMinSpeed(1 * UNIT);
			setMaxSpeed(100 * UNIT);

			setAcceleration(5 * UNIT);
			setTurningRate(Ogre::Degree(10));

			setDesiredSpeed(0);
			setDesiredHeading(Ogre::Degree(0));

			setSpeed(0);
			setHeading(Ogre::Degree(0));
			setAAABstate(false);

			zeroVectors();

			Ogre::Entity* entity = scMgr->createEntity("alienship.mesh");
			initNode(scMgr, entity);

			initAspects();
						;};
};

#endif // #ifndef __TutorialApplication_h_
