#ifndef GfxMgr_H
#define GfxMgr_H

#include <Engine.h>
#include <Mgr.h>

#include <Entity381.h>

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class GfxMgr
  : public Ogre::WindowEventListener,
    public Ogre::FrameListener,
	Mgr
{
public:
  GfxMgr(Engine* eng);
  ~GfxMgr();

  void Init(){};
  void LoadLevel(){};
  void Stop(){};
  void Tick(float dt);

  Ogre::SceneManager* getSceneMgr(){return mSceneMgr;};

  bool go();

  Engine* engine;

  virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

  virtual void windowResized(Ogre::RenderWindow* rw);
  virtual void windowClosed(Ogre::RenderWindow* rw);

  Ogre::Root* mRoot;
  Ogre::String mResourcesCfg;
  Ogre::String mPluginsCfg;
  Ogre::RenderWindow* mWindow;
  Ogre::SceneManager* mSceneMgr;
  Ogre::Camera* mCamera;

  Ogre::SceneNode* cameraNode;
  OIS::InputManager* mInputMgr;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;

};

#endif
