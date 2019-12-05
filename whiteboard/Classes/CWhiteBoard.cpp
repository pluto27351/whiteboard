#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CWhiteBoard.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CWhiteBoard::createScene()
{
	auto scene = Scene::create();

	auto layer = CWhiteBoard::create();

	scene->addChild(layer);

	return scene;
}

bool CWhiteBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("whiteboard.plist");
	auto rootNode = CSLoader::createNode("white_board.csb");
	addChild(rootNode);

	_handDrawing = CDrawingPanel::create();
	_handDrawing->initDrawingPanel(*rootNode, *this);
	_handDrawing->retain();


	_listener1 = EventListenerTouchAllAtOnce::create();
	_listener1->onTouchesBegan = CC_CALLBACK_2(CWhiteBoard::onTouchesBegan, this);
	_listener1->onTouchesMoved = CC_CALLBACK_2(CWhiteBoard::onTouchesMoved, this);
	_listener1->onTouchesEnded = CC_CALLBACK_2(CWhiteBoard::onTouchesEnded, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(CWhiteBoard::doStep));

	return true;
}


void CWhiteBoard::doStep(float dt)  // OnFrameMove
{


}


void CWhiteBoard::onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event) {
  //  _toolMode = _handDrawing->getMode();
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();

		_handDrawing->touchesBegin(touchLoc);
		//if (touchOnEmpty && _toolMode == HAND_MODE) {
		//	_handDrawing->changeToBlackPen();
		//}
	}
}

void CWhiteBoard::onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
		Point preTouchLoc = touch->getPreviousLocation();

		_handDrawing->touchesMoved(touchLoc, preTouchLoc);

	}
}

void  CWhiteBoard::onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
			
		_handDrawing->touchesEnded(touchLoc);
	}
}

CWhiteBoard::~CWhiteBoard()
{
	_handDrawing->release();
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("whiteboard.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();


}
