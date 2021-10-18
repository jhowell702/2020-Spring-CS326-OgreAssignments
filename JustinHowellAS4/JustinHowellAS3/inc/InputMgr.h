#include <Mgr.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>

class GfxMgr;

class InputMgr : Mgr{
public:
	InputMgr(Engine* eng);
	~InputMgr();

	void Init();
	void Stop();
	void LoadLevel();
	void Tick(float dt);

	Engine* engine;

	  OIS::InputManager* mInputMgr;
	  OIS::Keyboard* mKeyboard;
	  OIS::Mouse* mMouse;

};
