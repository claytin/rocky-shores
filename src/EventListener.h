#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneNode.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class EventListener: public Ogre::FrameListener{

public:
	EventListener(void);
	EventListener(Ogre::SceneNode *_sceneNode, Ogre::RenderWindow *window);
	~EventListener(void);

	bool frameStarted(const Ogre::FrameEvent &evt);

private:
	Ogre::SceneNode *node;
	Ogre::FrameListener *FrameListener;
};

#endif
