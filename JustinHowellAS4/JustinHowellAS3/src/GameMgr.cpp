#include <Engine.h>
#include <GameMgr.h>
#include <EntityMgr.h>
#include <InputMgr.h>

#include <OgreMeshManager.h>


GameMgr::GameMgr(Engine* eng): Mgr(eng){
	engine = eng;
}

GameMgr::~GameMgr(){

}

void GameMgr::Init(){
	engine->entityMgr->scnMgr = engine->gfxMgr->getSceneMgr();
	engine->entityMgr->entList = new Entity381*[5];
	entMgr = engine->entityMgr;
	inpMgr = engine->inputMgr;
	//entMgr.scnMgr = engine->gfxMgr->getSceneMgr();
}

void GameMgr::LoadLevel(){
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

		  	Ogre::MeshManager::getSingleton().createPlane(
		  	  "ground",
		  	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		  	  plane,
		  	  10000, 10000, 20, 20,
		  	  true,
		  	  1, 5, 5,
		  	  Ogre::Vector3::UNIT_Z);

		  	Ogre::Entity* groundEntity = engine->entityMgr->scnMgr->createEntity("ground");
		  	engine->entityMgr->terrain = engine->entityMgr->scnMgr->getRootSceneNode()->createChildSceneNode();
		  	engine->entityMgr->terrain->attachObject(groundEntity);
		  	engine->entityMgr->terrain->setPosition(0, -500, 0);

		  	groundEntity->setMaterialName("OceanHLSL_GLSL");

		  	engine->entityMgr->scnMgr->setSkyBox(true, "Examples/MorningSkyBox");

		  	engine->entityMgr->scnMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
		  	Ogre::Light* light = engine->entityMgr->scnMgr->createLight("MainLight");
		  	light->setPosition(20, 80, 50);

		  	loadShips();
}

void GameMgr::loadShips(){
	Ogre::SceneManager* scn = engine->entityMgr->scnMgr;

	engine->entityMgr->entList[0] =  new Destroyer(scn, 0);
	engine->entityMgr->entList[0]->setPos(0, -500, 0);

	engine->entityMgr->entList[1] =  new Carrier(scn, 1);
	engine->entityMgr->entList[1]->setPos(0, -500, 100);

	engine->entityMgr->entList[2] =  new Frigate(scn, 2);
	engine->entityMgr->entList[2]->setPos(0, -500, 200);

	engine->entityMgr->entList[3] =  new Speedboat(scn, 3);
	engine->entityMgr->entList[3]->setPos(0, -500, 300);

	engine->entityMgr->entList[4] =  new Alien(scn, 4);
	engine->entityMgr->entList[4]->setPos(0, -500, 400);

	engine->entityMgr->entList[0]->switchAAABstate();

}

void GameMgr::Stop(){

}

void GameMgr::Tick(float dt){

	Input();

}

void GameMgr::Input(){
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

		Ogre::Vector3 cubeVec = Ogre::Vector3::ZERO;


		bool objUp = inpMgr->mKeyboard->isKeyDown(OIS::KC_U);
		bool objDown = inpMgr->mKeyboard->isKeyDown(OIS::KC_O);
		bool objFor = inpMgr->mKeyboard->isKeyDown(OIS::KC_I);
		bool objBack = inpMgr->mKeyboard->isKeyDown(OIS::KC_K);
		bool objLeft = inpMgr->mKeyboard->isKeyDown(OIS::KC_L);
		bool objRight = inpMgr->mKeyboard->isKeyDown(OIS::KC_J);
		bool objStop = inpMgr->mKeyboard->isKeyDown(OIS::KC_SPACE);
		bool tabSelect = inpMgr->mKeyboard->isKeyDown(OIS::KC_TAB);

		if(objUp && !objUpLF){
			cubeVec.y += move;
		}

		if ( objDown && !objDownLF){
			cubeVec.y -= move;
		}

		if ( objFor && !objForLF){
			entMgr->entList[entMgr->currEntity]->updateDesiredSpeed(speedControl);
		}

		if ( objBack && !objBackLF){
			entMgr->entList[entMgr->currEntity]->updateDesiredSpeed(-speedControl);
		}

		if ( objLeft && !objLeftLF){
			entMgr->entList[entMgr->currEntity]->updateDesiredHeading(headingControl);
		}

		if ( objRight && !objRightLF){
			entMgr->entList[entMgr->currEntity]->updateDesiredHeading(-headingControl);
		}

		if ( tabSelect && !tabLF){
			entMgr->tabSelection();
		}

		if ( objStop){
			entMgr->entList[entMgr->currEntity]->setVelocity(Ogre::Vector3::ZERO);
			entMgr->entList[entMgr->currEntity]->setDesiredSpeed(0);
		}

		Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_W) && !(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
		  dirVec.z -= move;

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_S) && !(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
		  dirVec.z += move;

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_E))
		  dirVec.y += move;
		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_F))
		  dirVec.y -= move;

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_A) && !(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
		{
		    dirVec.x -= move;
		}

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_D) && !(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT)))
		{
		    dirVec.x += move;
		}

		if(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT) && inpMgr->mKeyboard->isKeyDown(OIS::KC_A)){
			engine->gfxMgr->mCamera->yaw(Ogre::Degree(.5));	}

		if(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT) && inpMgr->mKeyboard->isKeyDown(OIS::KC_D)){
			engine->gfxMgr->mCamera->yaw(Ogre::Degree(-.5));
		}

		if(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT) && inpMgr->mKeyboard->isKeyDown(OIS::KC_W)){
			engine->gfxMgr->mCamera->pitch(Ogre::Degree(.5));
		}

		if(inpMgr->mKeyboard->isKeyDown(OIS::KC_LSHIFT) && inpMgr->mKeyboard->isKeyDown(OIS::KC_S)){
			engine->gfxMgr->mCamera->pitch(Ogre::Degree(-.5));
		}

		if (inpMgr->mKeyboard->isKeyDown(OIS::KC_Q)){
			engine->keepRunning = false;
		}

		objUpLF = objUp;
		objDownLF = objDown;
		objForLF = objFor;
		objBackLF = objBack;
		objLeftLF = objLeft;
		objRightLF = objRight;
		tabLF = tabSelect;


		engine->gfxMgr->cameraNode->setPosition(engine->gfxMgr->cameraNode->getPosition() + dirVec);
}
