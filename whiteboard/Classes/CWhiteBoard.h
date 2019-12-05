#pragma once
#include "cocos2d.h"
#include "CDrawingPanel.h"
#include "common_tool/CButton.h"

class CWhiteBoard : public cocos2d::Layer
{
public:
    ~CWhiteBoard();
    
	CDrawingPanel *_handDrawing;    // 工具區(手.筆.擦)
    CButton _menuBtn;

    int _toolMode;        //  模式 筆．擦布．手

    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void doStep(float dt);
    
    cocos2d::EventListenerTouchAllAtOnce *_listener1;
    void onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    void OnTouchesCancelled(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CWhiteBoard);
};
