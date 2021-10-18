#include <Mgr.h>
#include <OgreRoot.h>
#include <Engine.h>
#include <GfxMgr.h>

class EntityMgr : Mgr{
public:
	EntityMgr(Engine* eng);
	~EntityMgr();

	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	void tabSelection();

	Ogre::SceneManager* scnMgr;
	Engine* engine;
	GfxMgr* gfxMgr;


	Ogre::SceneNode* skybox;
	Ogre::SceneNode* terrain;

	int currEntity;

	Entity381** entList;
	Ogre::Light light;

};
