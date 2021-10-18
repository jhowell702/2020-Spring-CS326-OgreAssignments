#include <Engine.h>
#include <InputMgr.h>
#include <GfxMgr.h>


InputMgr::InputMgr(Engine* eng) : Mgr(eng){
	engine = eng;
}

InputMgr::~InputMgr(){

}

void InputMgr::Init(){

	mInputMgr = engine->gfxMgr->mInputMgr;
	mKeyboard = engine->gfxMgr->mKeyboard;
	mMouse = engine->gfxMgr->mMouse;

}

void InputMgr::LoadLevel(){

}

void InputMgr::Stop(){

}

void InputMgr::Tick(float dt){
	  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		  engine->keepRunning = false;
	  }
}
