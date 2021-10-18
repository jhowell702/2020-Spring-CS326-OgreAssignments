#include <Entity381.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>


#include <Aspect.h>

Entity381::Entity381()
{
}

Entity381::~Entity381(){

}

void Entity381::initNode(Ogre::SceneManager* scMgr, Ogre::Entity* entity){


	Ogre::SceneNode* node = scMgr->getRootSceneNode()->createChildSceneNode(entityName);
	//entity->setMaterialName("Examples/Rockwall");
	node->attachObject(entity);

	setNodePtr(node);
	setOgreEntity(entity);
}

void Entity381::initAspects(){
	physicsAspect = new Physics(this);
	renderAspect = new Renderer(this);
}

void Entity381::switchAAABstate(){

	if(AAABstate == true){
		AAABstate = false;
		ogreSceneNode->showBoundingBox(false);
	}else{
		AAABstate = true;
		ogreSceneNode->showBoundingBox(true);
	}

}

void Entity381::Tick(float dt){
	std::cout << "Calling tick for object" << std::endl;
	physicsAspect->Tick(dt);
	renderAspect->Tick(dt);
}
