#include <GfxMgr.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
 
GfxMgr::GfxMgr(Engine* eng)
  : Mgr(eng)
{
	mRoot = 0;
	mWindow = 0;
	mSceneMgr = 0;
	mCamera = 0;
	mInputMgr = 0;
	mMouse = 0;
	mKeyboard = 0;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg = Ogre::StringUtil::BLANK;
	engine = eng;
}
 
GfxMgr::~GfxMgr()
{
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
 
  windowClosed(mWindow);
 
  delete mRoot;
}
 
bool GfxMgr::go()
{
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif
 
  mRoot = new Ogre::Root(mPluginsCfg);
 
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);
 
  Ogre::String name, locType;
  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
 
  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;
 
    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;
 
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }
 
  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    return false;
 
  mWindow = mRoot->initialise(true, "GfxMgr Render Window");
 
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
 
  mCamera = mSceneMgr->createCamera("MainCam");
  mCamera->setPosition(0, 0, 80);
  mCamera->lookAt(0, 0, -300);
  mCamera->setNearClipDistance(5);

	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
			  "CamNode1", Ogre::Vector3(0, 300, 500));
	cameraNode = node;
	node->attachObject(mCamera);
 
  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
 
  mCamera->setAspectRatio(
    Ogre::Real(vp->getActualWidth()) /
    Ogre::Real(vp->getActualHeight()));
 
  // OIS
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
 
  OIS::ParamList pl;
  size_t windowHandle = 0;
  std::ostringstream windowHandleStr;
 
  mWindow->getCustomAttribute("WINDOW", &windowHandle);
  windowHandleStr << windowHandle;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
 
  mInputMgr = OIS::InputManager::createInputSystem(pl);
 
  mKeyboard = static_cast<OIS::Keyboard*>(
    mInputMgr->createInputObject(OIS::OISKeyboard, false));
  mMouse = static_cast<OIS::Mouse*>(
    mInputMgr->createInputObject(OIS::OISMouse, false));
 
  windowResized(mWindow);
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
 
  mRoot->addFrameListener(this);
 
  //mRoot->startRendering();

  if(Ogre::Root::getSingletonPtr()->renderOneFrame()){
	  std::cout << "Rendered one frame" << std::endl;
  }
 
  if(mRoot->renderOneFrame()){
	  std::cout << "Rendered second frame" << std::endl;
  }

  return true;
}
 
bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  if (mWindow->isClosed()) return false;
 
  mKeyboard->capture();
  mMouse->capture();

  //std::cout << "Frame rendering queued called" << std::endl;

  //testNode->yaw(Ogre::Degree(5));
 
  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
 
  return true;
}
 
void GfxMgr::windowResized(Ogre::RenderWindow* rw)
{
  int left, top;
  unsigned int width, height, depth;
 
  rw->getMetrics(width, height, depth, left, top);
 
  const OIS::MouseState& ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}
 
void GfxMgr::windowClosed(Ogre::RenderWindow* rw)
{
  if(rw == mWindow)
  {
    if(mInputMgr)
    {
      mInputMgr->destroyInputObject(mMouse);
      mInputMgr->destroyInputObject(mKeyboard);
 
      OIS::InputManager::destroyInputSystem(mInputMgr);
      mInputMgr = 0;
    }
  }
}

void GfxMgr::Tick(float dt){

	//std::cout << "Ticking gfx" << std::endl;
	//  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		//  engine->keepRunning = false;
	  //}

	  Ogre::WindowEventUtilities::messagePump();

	  if(Ogre::Root::getSingletonPtr()->renderOneFrame()){
		 // std::cout << "rendered one frame in gfx loop!" << std::endl;
	  }

}

