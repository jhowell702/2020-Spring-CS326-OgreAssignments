/*
-----------------------------------------------------------------------------
Filename:    As2.cpp
-----------------------------------------------------------------------------

	  Code used by Justin Howell
	  Email: justinhowell@nevada.unr.edu

-----------------------------------------------------------------------------
*/

#include <As2.h>

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


	  entMgr = new EntityMgr(10, mSceneMgr);
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  bool ret = BaseApplication::frameRenderingQueued(fe);

  if(!processUnbufferedInput(fe))
    return false;

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

	cubeVec = Ogre::Vector3::ZERO;


	bool objUp = mKeyboard->isKeyDown(OIS::KC_NUMPAD9);
	bool objDown = mKeyboard->isKeyDown(OIS::KC_NUMPAD3);
	bool objFor = mKeyboard->isKeyDown(OIS::KC_NUMPAD8);
	bool objBack = mKeyboard->isKeyDown(OIS::KC_NUMPAD2);
	bool objLeft = mKeyboard->isKeyDown(OIS::KC_NUMPAD4);
	bool objRight = mKeyboard->isKeyDown(OIS::KC_NUMPAD6);
	bool objStop = mKeyboard->isKeyDown(OIS::KC_SPACE);
	bool tabSelect = mKeyboard->isKeyDown(OIS::KC_TAB);

	if(objUp && !objUpLF){
		cubeVec.y += move;
	}

	if ( objDown && !objDownLF){
		cubeVec.y -= move;
	}

	if ( objFor && !objForLF){
		cubeVec.z -= move;
	}

	if ( objBack && !objBackLF){
		cubeVec.z += move;
	}

	if ( objLeft && !objLeftLF){
		cubeVec.x -= move;
	}

	if ( objRight && !objRightLF){
		cubeVec.x += move;
	}

	if ( tabSelect && !tabLF){
		entMgr->tabSelection();
	}

	if ( objStop){
		entMgr->getCurrEntity()->setVelocity(Ogre::Vector3::ZERO);
	}

	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (mKeyboard->isKeyDown(OIS::KC_W))
	  dirVec.z -= move;

	if (mKeyboard->isKeyDown(OIS::KC_S))
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

	entMgr->getCurrEntity()->updateVelocity(cubeVec);


	entMgr->Tick(fe.timeSinceLastFrame);


	cameraNode->setPosition(cameraNode->getPosition() + dirVec);


  return true;
}


//void TutorialApplication::createCamera()
//{
	//mCamera = mSceneMgr->createCamera("PlayerCam");
	//mCamera->setPosition(Ogre::Vector3(0, 300, 500));
	//mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	//mCamera->setNearClipDistance(5);

	//mCameraMan = new OgreBites::SdkCameraMan(mCamera);
//}

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
	for(int i = 0; i < entListSize; i++){
		Ogre::Vector3 position = Ogre::Vector3::ZERO;

		if(i < 5){
			position.x += i * 200;
			entList[i] = CreateEntityofTypeAtPosition("cube", position);
		}
		else{
			position.y += 200;
			position.x += i%5 * 200;
			entList[i] = CreateEntityofTypeAtPosition("sphere", position);
		}
	}

	std::cout << "Turning on bounding box" << std::endl;
	entList[currEntity]->switchAAABstate();

}

void EntityMgr::tabSelection(){

	entList[currEntity]->switchAAABstate();

	if(currEntity < 9){ //if curr entity is not 9 then
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

Entity381* EntityMgr::CreateEntityofTypeAtPosition(Ogre::String type, Ogre::Vector3 pos){

	std::cout << "Creating Entity!" << std::endl;

	if(Ogre::StringUtil::match(type, "cube")){

		CubeEntity381 *cubePtr = new CubeEntity381();
		cubePtr->setPos(pos);
		cubePtr->setId(entID);
		cubePtr->setVelocity(Ogre::Vector3::ZERO);
		cubePtr->setAAABstate(false);

		Ogre::String number = Ogre::StringConverter::toString(entID);

		std::cout << number << std::endl;

		cubePtr->setName("CubeNode" + number);
		Ogre::Entity* cubeEntity = currSceneMgr->createEntity("cube.mesh");
		Ogre::SceneNode* cubeNode = currSceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode" + number);
		cubeEntity->setMaterialName("Examples/Rockwall");
		cubeNode->attachObject(cubeEntity);

		cubePtr->setNodePtr(cubeNode);
		cubePtr->setOgreEntity(cubeEntity);

		cubeNode->setPosition(pos);

		entID++;

		std::cout << "Returning cubePtr" << std::endl;
		return cubePtr;
	}
	else{
		SphereEntity381 *spherePtr = new SphereEntity381();
		spherePtr->setPos(pos);
		spherePtr->setId(entID);
		spherePtr->setVelocity(Ogre::Vector3::ZERO);
		spherePtr->setAAABstate(false);


		Ogre::String number = Ogre::StringConverter::toString(entID);

		spherePtr->setName("SphereNode" + number);

		Ogre::Entity* sphereEntity = currSceneMgr->createEntity("sphere.mesh");
		Ogre::SceneNode* sphereNode = currSceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode" + number);
		sphereEntity->setMaterialName("Examples/Rockwall");
		sphereNode->attachObject(sphereEntity);

		spherePtr->setNodePtr(sphereNode);
		spherePtr->setOgreEntity(sphereEntity);

		sphereNode->setPosition(pos);
		sphereNode->setScale(.9,.9,.9);

		entID++;
		return spherePtr;
	}
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
