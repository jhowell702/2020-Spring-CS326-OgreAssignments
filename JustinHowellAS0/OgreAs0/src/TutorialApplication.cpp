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

#include "TutorialApplication.h"

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
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("robot.mesh");
	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
	mCamera->setPosition(0, 47, 222);

	ogreNode->setPosition(0,0,0);
	ogreNode->showBoundingBox(true);

	Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("robot.mesh");

	Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(
	  Ogre::Vector3(84, 48, 0));
	ogreNode2->attachObject(ogreEntity2);

	ogreNode2->setPosition(-100,0,0);
	ogreNode2->yaw(Ogre::Degree(90));
	ogreNode2->showBoundingBox(true);

	Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("robot.mesh");

	Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode3->setPosition(0, 100, 0);
	ogreNode3->setScale(2, 1, 2);
	ogreNode3->yaw(Ogre::Degree(180));
	ogreNode3->attachObject(ogreEntity3);

	ogreNode3->showBoundingBox(true);

	Ogre::Entity* ogreEntity4 = mSceneMgr->createEntity("robot.mesh");

	Ogre::SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode4->setPosition(100, 0, 0);
	ogreNode4->yaw(Ogre::Degree(-90));
	ogreNode4->attachObject(ogreEntity4);

	ogreNode4->showBoundingBox(true);

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
