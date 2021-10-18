
#include <EntityMgr.h>

EntityMgr::EntityMgr(Engine* eng) : Mgr(eng){
	engine = eng;
	skybox = 0;
	terrain = 0;
	entList = 0;
	scnMgr = 0;
}


EntityMgr::~EntityMgr(){

}


void EntityMgr::Init(){

}

void EntityMgr::LoadLevel(){

}

void EntityMgr::Stop(){

}

void EntityMgr::Tick(float dt){
	for(int i = 0; i < 5; i++){
		std::cout << "Testing Ticker!" << std::endl;
		entList[i]->Tick(dt);
	};
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
