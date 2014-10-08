#include "EventListener.h"

EventListener::EventListener(void):
	node(NULL),
	FrameListener(NULL){
}

EventListener::EventListener(Ogre::SceneNode *_sceneNode,
	Ogre::RenderWindow *_window):
	node(_sceneNode),
	FrameListener(NULL){

	size_t windowHnd = 0;
	std::stringstream windowHndStr;
	_window->getCustomAttribute("WINDOW", &windowHnd);

	windowHndStr << windowHnd;

	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

}

EventListener::~EventListener(void){
	if(FrameListener){
		delete FrameListener;
	}
}

double trans_sin = 0;
bool EventListener::frameStarted(const Ogre::FrameEvent &evt){
	//node->translate(Ogre::Vector3(0.1,0,0));
	//node->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
	//node->yaw(Ogre::Degree(90),Ogre::Node::TS_LOCAL);
	//node->translate(Ogre::Vector3(0, 0, -15), Ogre::Node::TS_LOCAL);

	node->setPosition(Ogre::Vector3(0, 0, 0));
	node->yaw(Ogre::Degree(100 * evt.timeSinceLastFrame));
	node->translate(Ogre::Vector3(0, 0, 15), Ogre::Node::TS_LOCAL);

	//std::cout << "y" << evt.timeSinceLastFrame << std::endl;
	trans_sin += evt.timeSinceLastFrame;
	node->translate(Ogre::Vector3(std::sin(trans_sin), 0, 0), Ogre::Node::TS_WORLD);

	return true;
}
