#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CWhiteBoard.h"

#define CENTER_POS Vec2(1024,768)

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

	setButton(*rootNode);

	_handDrawing = CDrawingPanel::create();
	_handDrawing->initDrawingPanel(*rootNode, *this);
	_handDrawing->retain();

	switchButton(BK_PEN);


	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(CWhiteBoard::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(CWhiteBoard::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(CWhiteBoard::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(CWhiteBoard::doStep));

	return true;
}

void CWhiteBoard::setButton(Node &rootNode) {
	Sprite *pBtn = (Sprite *)rootNode.getChildByName("pen_red");
	Point pt = pBtn->getPosition();
	auto s = pBtn->getScale();
	_toolBtn[R_PEN].setButtonInfo("tool_red.png", "tool_red_click.png", *this, pt, INTERFACE_LEVEL);
	_toolBtn[R_PEN].setScale(s);
	rootNode.removeChildByName("pen_red");

	pBtn = (Sprite *)rootNode.getChildByName("pen_black");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[BK_PEN].setButtonInfo("tool_black.png", "tool_black_click.png", *this, pt, INTERFACE_LEVEL);
	_toolBtn[BK_PEN].setScale(s);
	rootNode.removeChildByName("pen_black");

	pBtn = (Sprite *)rootNode.getChildByName("pen_blue");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[BL_PEN].setButtonInfo("tool_blue.png", "tool_blue_click.png", *this, pt, INTERFACE_LEVEL);
	_toolBtn[BL_PEN].setScale(s);
	rootNode.removeChildByName("pen_blue");

	pBtn = (Sprite *)rootNode.getChildByName("eraser");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[ERASER].setButtonInfo("tool_eraser.png", "tool_eraser_click.png", *this, pt, INTERFACE_LEVEL);
	_toolBtn[ERASER].setScale(s);
	rootNode.removeChildByName("erease");

	// 設定清楚螢幕所有手繪圖型的按鈕
	pBtn = (Sprite *)rootNode.getChildByName("clear");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_clearAllBtn.setButtonInfo("tool_reset.png", "tool_reset_click.png", *this, pt, INTERFACE_LEVEL);
	_clearAllBtn.setScale(s);
	rootNode.removeChildByName("clear");

	_brushSize = (Slider*)rootNode.getChildByName("size_bar");
	_brushSize->addEventListener(CC_CALLBACK_2(CWhiteBoard::brushChange, this));
	_brushSizeText = (Text *)rootNode.getChildByName("size_text");
	_sceneBar = (Slider*)rootNode.getChildByName("selectbox");
	_sceneBar->addEventListener(CC_CALLBACK_2(CWhiteBoard::sceneChange, this));

	_eraserPic = (Sprite *)Sprite::createWithSpriteFrameName("eraser_line.png");
	_eraserPic->setPosition(CENTER_POS);
	_eraserPic->setScale(0.3f);
	_eraserPic->setVisible(false);
	addChild(_eraserPic, INTERFACE_LEVEL); 

	_penPic = (Sprite *)Sprite::createWithSpriteFrameName("brush.png");
	_penPic->setPosition(CENTER_POS);
	_penPic->setScale(0.3f);
	_penPic->setVisible(false);
	addChild(_penPic, INTERFACE_LEVEL);
}


void CWhiteBoard::doStep(float dt)  // OnFrameMove
{


}

void CWhiteBoard::switchButton(int num) {
	for (int i = 0; i < 4; i++) {
		_toolBtn[i].setStatus(false);
	}
	_toolBtn[num].setStatus(true);

	if (num == ERASER) {
		_toolMode = ERASER_MODE;
	}
	else {
		_handDrawing->SetPen(num);
		_toolMode = PEN_MODE;
		_penPic->setColor(_handDrawing->getColor());
	}
	_handDrawing->setMode(_toolMode);
}



bool CWhiteBoard::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
	Point touchLoc = pTouch->getLocation();

	for (int i = 0; i < 4; i++) {
		_toolBtn[i].touchesBegin(touchLoc);
	}
	_clearAllBtn.touchesBegin(touchLoc);

	_handDrawing->touchesBegin(touchLoc);
		//if (touchOnEmpty && _toolMode == HAND_MODE) {
		//	_handDrawing->changeToBlackPen();
		//}
	
	return true;
}

void CWhiteBoard::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	Point touchLoc = pTouch->getLocation();
	Point preTouchLoc = pTouch->getPreviousLocation();

	for (int i = 0; i < 4; i++) {
		_toolBtn[i].touchesMoved(touchLoc);
	}
	_clearAllBtn.touchesMoved(touchLoc);

	_handDrawing->touchesMoved(touchLoc, preTouchLoc);

}

void  CWhiteBoard::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	Point touchLoc = pTouch->getLocation();

	for (int i = 0; i < 4; i++) {
		if (_toolBtn[i].touchesEnded(touchLoc)) {
			switchButton(i);
		}
	}

	if (_clearAllBtn.touchesEnded(touchLoc)) {
		_handDrawing->clearWhiteBoard();
	}

	_handDrawing->touchesEnded(touchLoc);
	
}


void CWhiteBoard::brushChange(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		percent = (percent / 10) * 10;
		if (percent == 0)percent = 1;
		_brushSize->setPercent(percent);
		_brushSizeText->setString(StringUtils::format("%d", percent));

		float size = percent / 100.0f;
		_handDrawing->setBrushSize(size);
		if (_toolMode == ERASER_MODE)_eraserPic->setScale(size);
		else _penPic->setScale(size);
	}
	else if (type == Slider::EventType::ON_SLIDEBALL_DOWN) {
		if(_toolMode == ERASER_MODE)_eraserPic->setVisible(true);
		else _penPic->setVisible(true);
	}
	else if (type == Slider::EventType::ON_SLIDEBALL_UP) {
		if (_toolMode == ERASER_MODE)_eraserPic->setVisible(false);
		else _penPic->setVisible(false);
	}

}
void CWhiteBoard::sceneChange(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {

}

CWhiteBoard::~CWhiteBoard()
{
	_handDrawing->release();
	this->unscheduleAllCallbacks();
	this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("whiteboard.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();


}
