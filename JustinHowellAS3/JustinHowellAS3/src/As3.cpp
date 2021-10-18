/*
-----------------------------------------------------------------------------
Filename:    As2.cpp
-----------------------------------------------------------------------------

	  Code used by Justin Howell
	  Email: justinhowell@nevada.unr.edu

-----------------------------------------------------------------------------
*/

#include <As3.h>

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
	groundHeight = -50;
	cubeVec = Ogre::Vector3::ZERO;
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));

	  Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	  pointLight->setType(Ogre::Light::LT_POINT);
	  pointLight->setPosition(250, 150, 250);
	  pointLight->setDiffuseColour(Ogre::ColourValue::White);
	  pointLight->setSpecularColour(Ogre::ColourValue::White);

		Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
				  "CamNode1", Ogre::Vector3(0, 300, 500));
		//node->yaw(Ogre::Degree(90));
		cameraNode = node;
		node->attachObject(mCamera);

	  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  	Ogre::MeshManager::getSingleton().createPlane(
	  	  "ground",
	  	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	  plane,
	  	  10000, 10000, 20, 20,
	  	  true,
	  	  1, 5, 5,
	  	  Ogre::Vector3::UNIT_Z);

	  	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	  	//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	  	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  	groundNode->attachObject(groundEntity);
	  	groundNode->setPosition(0,groundHeight,0);

	  	groundEntity->setMaterialName("OceanHLSL_GLSL");
	  	mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");

	  	//Destroyer* shipTester = new Destroyer(mSceneMgr,1);

	    entMgr = new EntityMgr(5, mSceneMgr);
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  bool ret = BaseApplication::frameRenderingQueued(fe);

  if(!processUnbufferedInput(fe))
    return false;

  entMgr->Tick(fe.timeSinceLastFrame);

  return ret;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	static bool objUpLF = false;
	static bool objDownLF = false;
	static bool objForLF = false;
	static bool objBackLF = false;
	static bool objLeftLF = false;
	static bool objRightLF = false;
	static bool tabLF = false;
	//static bool cubeStopLF = false;
	//static Ogre::Real toggleTimer = 0.0;
	static Ogre::Real move = 10;

	int speedControl = 10;
	Ogre::Degree headingControl = Ogre::Degree(10);

	cubeVec = Ogre::Vector3::ZERO;


	bool objUp = mKeyboard->isKeyDown(OIS::KC_U);
	bool objDown = mKeyboard->isKeyDown(OIS::KC_O);
	bool objFor = mKeyboard->isKeyDown(OIS::KC_I);
	bool objBack = mKeyboard->isKeyDown(OIS::KC_K);
	bool objLeft = mKeyboard->isKeyDown(OIS::KC_L);
	bool objRight = mKeyboard->isKeyDown(OIS::KC_J);
	bool objStop = mKeyboard->isKeyDown(OIS::KC_SPACE);
	bool tabSelect = mKeyboard->isKeyDown(OIS::KC_TAB);

	if(objUp && !objUpLF){
		cubeVec.y += move;
	}

	if ( objDown && !objDownLF){
		cubeVec.y -= move;
	}

	if ( objFor && !objForLF){
		entMgr->getCurrEntity()->updateDesiredSpeed(speedControl);
	}

	if ( objBack && !objBackLF){
		entMgr->getCurrEntity()->updateDesiredSpeed(-speedControl);
	}

	if ( objLeft && !objLeftLF){
		entMgr->getCurrEntity()->updateDesiredHeading(headingControl);
	}

	if ( objRight && !objRightLF){
		entMgr->getCurrEntity()->updateDesiredHeading(-headingControl);
	}

	if ( tabSelect && !tabLF){
		entMgr->tabSelection();
	}

	if ( objStop){
		entMgr->getCurrEntity()->setVelocity(Ogre::Vector3::ZERO);
	}

	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (mKeyboard->isKeyDown(OIS::KC_W) && !(mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
	  dirVec.z -= move;

	if (mKeyboard->isKeyDown(OIS::KC_S) && !(mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
	  dirVec.z += move;

	if (mKeyboard->isKeyDown(OIS::KC_E))
	  dirVec.y += move;
	if (mKeyboard->isKeyDown(OIS::KC_F))
	  dirVec.y -= move;

	if (mKeyboard->isKeyDown(OIS::KC_A) && !(mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
	{
	    dirVec.x -= move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_D) && !(mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
	{
	    dirVec.x += move;
	}

	if(mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_A)){
		mCamera->yaw(Ogre::Degree(.5));	}

	if(mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_D)){
		mCamera->yaw(Ogre::Degree(-.5));
	}

	if(mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_W)){
		mCamera->pitch(Ogre::Degree(.5));
	}

	if(mKeyboard->isKeyDown(OIS::KC_LSHIFT) && mKeyboard->isKeyDown(OIS::KC_S)){
		mCamera->pitch(Ogre::Degree(-.5));
	}

	if (mKeyboard->isKeyDown(OIS::KC_Q)){
		mShutDown = true;
	}

	objUpLF = objUp;
	objDownLF = objDown;
	objForLF = objFor;
	objBackLF = objBack;
	objLeftLF = objLeft;
	objRightLF = objRight;
	tabLF = tabSelect;


	cameraNode->setPosition(cameraNode->getPosition() + dirVec);


  return true;
}


void TutorialApplication::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) /
	  Ogre::Real(vp->getActualHeight()));

}

Entity381::Entity381(){

}


EntityMgr::EntityMgr(int numEnt, Ogre::SceneManager* sMgr){

	currEntity = 0;
	entListSize = numEnt;
	currSceneMgr = sMgr;
	entID = 0;


	entList = new Entity381*[entListSize];

	entList[0] = CreateEntityofTypeAtPosition(destroyer,0);

	entList[1] = CreateEntityofTypeAtPosition(carrier,1);
	entList[1]->getNode()->setPosition(0,0,50);
	entList[1]->setPos(0,0,50);

	entList[2] = CreateEntityofTypeAtPosition(speedboat,2);
	entList[2]->getNode()->setPosition(0,0,100);
	entList[2]->setPos(0,0,100);

	entList[3] = CreateEntityofTypeAtPosition(frigate,3);
	entList[3]->getNode()->setPosition(0,0,150);
	entList[3]->setPos(0,0,150);

	entList[4] = CreateEntityofTypeAtPosition(alien,4);
	entList[4]->getNode()->setPosition(0,0,200);
	entList[4]->setPos(0,0,200);

	entList[currEntity]->switchAAABstate();

}

void EntityMgr::tabSelection(){

	entList[currEntity]->switchAAABstate();

	if(currEntity < 4){ //if curr entity is not 9 then
		currEntity++;
	}else{ //if currEntity is 9 then
		currEntity = 0;
	}

	entList[currEntity]->switchAAABstate();

}

void Entity381::switchAAABstate(){

	if(AAABstate == true){
		std::cout << "AAABstate is true, setting to false" << std::endl;
		AAABstate = false;
		std::cout << "Calling scene node" << std::endl;
		ogreSceneNode->showBoundingBox(false);
		std::cout << "Call succesful" << std::endl;
	}else{
		std::cout << "AAABstate is false, setting to true" << std::endl;
		AAABstate = true;
		std::cout << "Calling scene node" << std::endl;
		ogreSceneNode->showBoundingBox(true);
		std::cout << "Call succesful" << std::endl;
	}

}

Entity381* EntityMgr::CreateEntityofTypeAtPosition(shipType type, int id){


	switch(type){

	case destroyer:{
		Destroyer* des = new Destroyer(currSceneMgr,id);
		return des;
		break;
	}
	case carrier:{
		Carrier* car = new Carrier(currSceneMgr,id);
		return car;
		break;
	}
	case frigate:{
		Frigate* frig = new Frigate(currSceneMgr,id);
		return frig;
		break;
	}
	case speedboat:{
		Speedboat* sped = new Speedboat(currSceneMgr,id);
		return sped;
		break;
	}
	case alien:{
		Alien* alien= new Alien(currSceneMgr,id);
		return alien;
		break;
	}
	}

}

void Physics::Tick(float dt){
	int des = entity->getDesiredSpeed();
	int speed = entity->getSpeed();
	int accel = entity->getAcel();

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

	Ogre::Degree head = entity->getHeading();
	Ogre::Degree desHead = entity->getDesiredHeading();
	Ogre::Degree tR = entity->getTurnRate();

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

	entity->setHeading(head);
	entity->setSpeed(speed);

	Ogre::Vector3 newPos = Ogre::Vector3::ZERO;

	newPos.x += speed * Ogre::Math::Cos(entity->getHeading());

	newPos.z += speed * Ogre::Math::Sin(entity->getHeading());

	entity->setVelocity(newPos);
	entity->updatePosition(dt);

}

void Renderable::Tick(float dt){
	entity->getNode()->setOrientation(Ogre::Quaternion(-(entity->getHeading()),Ogre::Vector3(0,1,0)));
	entity->getNode()->setPosition(entity->getPos());
}

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include "macUtils.h"
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
		int main(int argc, char *argv[])
#endif
		{
			// Create application object
			TutorialApplication app;

			try {
				app.go();
			} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
				std::cerr << "An exception has occurred: " <<
					e.getFullDescription().c_str() << std::endl;
#endif
			}

			return 0;
		}

#ifdef __cplusplus
	}
#endif
