#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CSwitch
{
private:
	cocos2d::Sprite *_normalPic;
	cocos2d::Sprite *_selectedPic;
	cocos2d::Sprite *_enablePic;
	cocos2d::Size  _BtnSize;
	cocos2d::Point _BtnLoc;
	cocos2d::Rect  _BtnRect;

	float _fScale, _ftouchedScale;	// �Ϥ��Y�񪺤j�p
	bool _bTouched; // �O�_�Q���U
	bool _bEnabled; // �O�_���@��
	bool _bVisible; // �O�_���
	bool _bStatus;

public:
	~CSwitch() {};
	void setButtonInfo(const char *normalImg, const char *selectImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	void setButtonInfo(const char *normalImg, const char *selectImg, const char *enableImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);
	void setVisible(bool bVis);
	void setStatus(bool status);	// �]�w�o�ӫ��s�ثe�O������A
	void setEnabled(bool bEnable);
	void setPosition(Vec2 locPt);
	Point getPosition() { return _BtnLoc; }
	void setScale(float fscale);
	void setTouchScale(float s);

};

