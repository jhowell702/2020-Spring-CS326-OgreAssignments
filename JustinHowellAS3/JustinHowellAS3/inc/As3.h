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
#include "Entity381.h"



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
	Entity381* CreateEntityofTypeAtPosition(shipType type, int id);
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
