#include <Mgr.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

class Engine;
class EntityMgr;
class InputMgr;

class GameMgr : Mgr{

public:
	GameMgr(Engine* eng);
	~GameMgr();

	void Init();
	void Tick(float dt);
	void LoadLevel();
	void Stop();

	void Input();

	Engine* engine;

	void loadShips();

	EntityMgr* entMgr;
	InputMgr* inpMgr;

};
