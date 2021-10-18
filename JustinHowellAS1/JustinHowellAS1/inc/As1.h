/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);

protected:
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);

	virtual void createCamera();
	virtual void createViewports();

private:
	  bool processUnbufferedInput(const Ogre::FrameEvent& fe);

	  int groundHeight = -50;
	  Ogre::Vector3 cubeVec = Ogre::Vector3::ZERO;
	  Ogre::SceneNode* cubeNode;

};

#endif // #ifndef __TutorialApplication_h_
