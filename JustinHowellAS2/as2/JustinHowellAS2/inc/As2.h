/*
-----------------------------------------------------------------------------
Filename:    As2.h
-----------------------------------------------------------------------------

	  	  Code used by Justin Howell
	  Email: justinhowell@nevada.unr.edu
-----------------------------------------------------------------------------
*/
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

class Entity381{
public:
	Entity381();
	void Tick(float dt){
			position += velocity * dt;
			ogreSceneNode->setPosition(position);
			ogreSceneNode->yaw(Ogre::Degree(.5));
		};

	Ogre::Vector3 getPos(){return position;};
	void setPos(Ogre::Vector3 pos){position = pos;};

	void setId(int id){entityId = id;};

	void setName(Ogre::String name){entityName = name;};

	void setVelocity(Ogre::Vector3 vel){velocity = vel;};

	Ogre::Vector3 getVelocity(){return velocity;};

	void setAAABstate(bool state){AAABstate = state;};

	void switchAAABstate();

	void setNodePtr(Ogre::SceneNode* ptr){ogreSceneNode = ptr;};

	Ogre::SceneNode* getNode(){return ogreSceneNode;};

	void setOgreEntity(Ogre::Entity* ptr){ogreEntity = ptr;};

	void updateVelocity(Ogre::Vector3 dt){
		velocity.x += dt.x;
		velocity.y += dt.y;
		velocity.z += dt.z;
	};

private:
	int entityId;
	Ogre::String entityName;
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	Ogre::SceneNode* ogreSceneNode;
	Ogre::Entity* ogreEntity;

	bool AAABstate;

};

class CubeEntity381 : public Entity381{

public:
	CubeEntity381(){type = "cube";};
private:
	Ogre::String type;

};

class SphereEntity381 : public Entity381{

public:
	SphereEntity381(){type = "sphere";};
private:
	Ogre::String type;
};

class EntityMgr{

public:
	EntityMgr();
	EntityMgr(int numEnt, Ogre::SceneManager*);
	Entity381* CreateEntityofTypeAtPosition(Ogre::String type, Ogre::Vector3 pos);
	Entity381* getCurrEntity(){return entList[currEntity];};
	void Tick(float dt){
		for(int i = 0; i < entListSize; i++){
			entList[i]->Tick(dt);
		};
	};
	void tabSelection();

protected:
	Ogre::SceneManager* currSceneMgr;

private:
	Entity381** entList;
	int currEntity;
	int entListSize;
	int entID;

};



class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

	//virtual void createCamera();
	virtual void createViewports();

private:
	  bool processUnbufferedInput(const Ogre::FrameEvent& fe);

	  int groundHeight;
	  Ogre::Vector3 cubeVec;
	  Ogre::SceneNode* cubeNode;
	  Ogre::SceneNode* cameraNode;
	  EntityMgr* entMgr;

};





#endif // #ifndef __TutorialApplication_h_
