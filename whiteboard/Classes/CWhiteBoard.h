#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CDrawingPanel.h"
#include "common_tool/CButton.h"


enum tool { BK_PEN,BL_PEN,R_PEN,ERASER };
using namespace ui;

class CWhiteBoard : public cocos2d::Layer
{
private:
	CDrawingPanel *_handDrawing;
	CButton _clearAllBtn;
	CSwitch _toolBtn[4];
	Slider _brushSize, _sceneNum;

	int _toolMode;

public:
    ~CWhiteBoard();
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void doStep(float dt);

	void setButton(Node &rootNode);
	void switchButton(int num);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 
   
    
    // implement the "static create()" method manually
    CREATE_FUNC(CWhiteBoard);
};
