/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/

	  Code used by Justin Howell
	  Email: justinhowell@nevada.unr.edu

-----------------------------------------------------------------------------
*/

#include <As1.h>

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
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

	  Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("ninja.mesh");
	  Ogre::SceneNode* ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
	  ninjaNode->attachObject(ninjaEntity);

	  Ogre::Entity* cubeEntity = mSceneMgr->createEntity("cube.mesh");
	  cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CubeNode");
	  cubeEntity->setMaterialName("Examples/Rockwall");
	  cubeNode->attachObject(cubeEntity);

	  cubeNode->showBoundingBox(true);

	  cubeNode->setPosition(-100,0,0);


	  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	  	Ogre::MeshManager::getSingleton().createPlane(
	  	  "ground",
	  	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  	  plane,
	  	  1000, 1000, 20, 20,
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
	static bool cubeUpLF = false;
	static bool cubeDownLF = false;
	static bool cubeForLF = false;
	static bool cubeBackLF = false;
	static bool cubeLeftLF = false;
	static bool cubeRightLF = false;
	//static bool cubeStopLF = false;
	//static Ogre::Real toggleTimer = 0.0;
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 50;

	bool cubeUp = mKeyboard->isKeyDown(OIS::KC_U);
	bool cubeDown = mKeyboard->isKeyDown(OIS::KC_O);
	bool cubeFor = mKeyboard->isKeyDown(OIS::KC_I);
	bool cubeBack = mKeyboard->isKeyDown(OIS::KC_K);
	bool cubeLeft = mKeyboard->isKeyDown(OIS::KC_L);
	bool cubeRight = mKeyboard->isKeyDown(OIS::KC_J);
	bool cubeStop = mKeyboard->isKeyDown(OIS::KC_SPACE);

	if(cubeUp && !cubeUpLF){
		cubeVec.y += move;
	}

	if ( cubeDown && !cubeDownLF){
		cubeVec.y -= move;
	}

	if ( cubeFor && !cubeForLF){
		cubeVec.z -= move;
	}

	if ( cubeBack && !cubeBackLF){
		cubeVec.z += move;
	}

	if ( cubeLeft && !cubeLeftLF){
		cubeVec.x += move;
	}

	if ( cubeRight && !cubeRightLF){
		cubeVec.x -= move;
	}

	if ( cubeStop){
		cubeVec.x = 0;
		cubeVec.y = 0;
		cubeVec.z = 0;
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

	if (mKeyboard->isKeyDown(OIS::KC_A))
	{
	    dirVec.x -= move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_D))
	{
	    dirVec.x += move;
	}

	if (mKeyboard->isKeyDown(OIS::KC_Q)){
		mShutDown = true;
	}

	cubeUpLF = cubeUp;
	cubeDownLF = cubeDown;
	cubeForLF = cubeFor;
	cubeBackLF = cubeBack;
	cubeLeftLF = cubeLeft;
	cubeRightLF = cubeRight;

	mSceneMgr->getSceneNode("CubeNode")->translate(
			cubeVec * fe.timeSinceLastFrame,
			Ogre::Node::TS_WORLD);

	mCamera->setPosition(mCamera->getPosition() + dirVec);

	cubeNode->yaw(Ogre::Degree(1));
	cubeNode->pitch(Ogre::Degree(1));
	cubeNode->roll(Ogre::Degree(1));

  return true;
}


void TutorialApplication::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0, 300, 500));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void TutorialApplication::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) /
	  Ogre::Real(vp->getActualHeight()));

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
