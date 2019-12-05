#include "CButton.h"

USING_NS_CC;

void CButton::setButtonInfo(const char *normalImg, const char *touchedImg, Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setVisible(false);
	_touchedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_touchedPic, level); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h

	// ���o�j�p
	_BtnSize = _normalPic->getContentSize();
	// �]�w�P�_�ϰ�
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
	_bTouched = false;
	_fScale = 1.0f;	_ftouchedScale = 1.15f;
	_bVisible = _bEnabled = true;
}

void CButton::setButtonInfo(const char *normalImg, const char *touchedImg, const char *enableImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
	_enablePic = (Sprite *)Sprite::createWithSpriteFrameName(enableImg);
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setPosition(_BtnLoc); // �]�w��m
	_enablePic->setPosition(_BtnLoc); // �]�w��m
	_touchedPic->setVisible(false);
	_touchedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_touchedPic, level); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_enablePic, level); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	// ���o�j�p
	_BtnSize = _normalPic->getContentSize();
	// �]�w�P�_�ϰ�
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
	_bTouched = false;
	_fScale = 1.0f;    _ftouchedScale = 1.15f;
	_bVisible = _bEnabled = true;
}


void CButton::setZ(int i)
{
	_normalPic->setZOrder(i);
	_touchedPic->setZOrder(i);
	if (_enablePic != NULL)_enablePic->setZOrder(i);
}

bool CButton::touchesBegin(cocos2d::Point inPos)
{
	if (_BtnRect.containsPoint(inPos) && _bVisible && _bEnabled)
	{
		_bTouched = true;
		_normalPic->setVisible(false);
		_touchedPic->setVisible(true);
		return(true); // �����b�W��
	}
	return(false);
}

bool CButton::touchesMoved(cocos2d::Point inPos)
{
	if (_bTouched) { // �u���Q�����ɭԤ~�B�z
		if (!_BtnRect.containsPoint(inPos)) { // ����Y��m���}���s
			_bTouched = false;
			_normalPic->setVisible(true);
			_touchedPic->setVisible(false);
			return(false);
		}
		else return(true);
	}
	return(false); // �ƫ�A������s�W�N�Q����
}

bool CButton::touchesEnded(cocos2d::Point inPos)
{
	if (_bTouched)
	{
		_bTouched = false;
		_normalPic->setVisible(true);
		_touchedPic->setVisible(false);
		if (_BtnRect.containsPoint(inPos)) return(true);  // ����Y��m���s�ɡA�٦b�ӫ��s�W
	}
	return false;
}

void CButton::setTouched()
{
	_bTouched = true;
	_normalPic->setVisible(false);
	_touchedPic->setVisible(true);
}

void CButton::setVisible(bool bVisible)
{
	_bVisible = bVisible;
	if (_enablePic != NULL) {
		_enablePic->setVisible((!_bEnabled)*_bVisible);
		_normalPic->setVisible(_bEnabled * _bVisible);
	}
	else {
		if (!_bVisible) _normalPic->setVisible(false);
		else _normalPic->setVisible(true);
	}

}


void CButton::setEnabled(bool bEnable)
{
	_bEnabled = bEnable;
	if (_enablePic != NULL) {
		_enablePic->setVisible(!_bEnabled);
		_normalPic->setVisible(_bEnabled);
	}
	else {
		if (_bEnabled) _normalPic->setColor(Color3B(255, 255, 255));
		else _normalPic->setColor(Color3B(50, 50, 50));
	}

}

void CButton::setTouchScale(float s) {
	_ftouchedScale = s;
	_touchedPic->setScale(_fScale*_ftouchedScale);
}

void CButton::setPosition(Vec2 locPt) {
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc);
	_touchedPic->setPosition(_BtnLoc);
	if (_enablePic != NULL)_enablePic->setPosition(_BtnLoc);
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
}

void CButton::setScale(float fscale)
{
	_fScale = fscale;
	// ���s�]�w�P�_�ϰ�d��
	_BtnRect.size.width *= _fScale;
	_BtnRect.size.height *= _fScale;
	_BtnRect.origin.x = _BtnLoc.x - _BtnRect.size.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnRect.size.height*0.5f;
	_normalPic->setScale(_fScale);
	if (_enablePic != NULL)_enablePic->setScale(_fScale);
	_touchedPic->setScale(_fScale*_ftouchedScale);
}

void CButton::setRotate(float rot)
{
	_normalPic->setRotation(rot);
	_touchedPic->setRotation(rot);
	if (_enablePic != NULL)_enablePic->setRotation(rot);
}
