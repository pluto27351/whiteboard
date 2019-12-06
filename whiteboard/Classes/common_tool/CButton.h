#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class CButton
{
private:
	cocos2d::Sprite *_normalPic;
	cocos2d::Sprite *_touchedPic;
	cocos2d::Sprite *_enablePic = NULL;
	cocos2d::Size  _BtnSize;
	cocos2d::Point _BtnLoc;
	cocos2d::Rect  _BtnRect;
	
	float _fScale, _ftouchedScale;	// �Ϥ��Y�񪺤j�p
	bool _bTouched; // �O�_�Q���U
	bool _bEnabled; // �O�_���@��
	bool _bVisible; // �O�_���

public:
	~CButton() {};
	void setButtonInfo(const char *normalImg, const char *touchedImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	void setButtonInfo(const char *normalImg, const char *touchedImg, const char *enableImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);

	void setVisible(bool bVis);
	void setTouched();	// �]�w�o�ӫ��s�ثe�O������A
	void setEnabled(bool bEnable);
	void setPosition(Vec2 locPt);
	void setScale(float fscale);
	void setRotate(float frot);
	void setTouchScale(float s);
	void setZ(int i);
};


#endif
