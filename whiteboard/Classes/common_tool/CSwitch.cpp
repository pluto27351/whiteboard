#include "CSwitch.h"

USING_NS_CC;

void CSwitch::setButtonInfo(const char *normalImg, const char *selectedImg, Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_selectedPic = (Sprite *)Sprite::createWithSpriteFrameName(selectedImg);
	_enablePic = NULL;
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_selectedPic->setPosition(_BtnLoc); // �]�w��m
	_selectedPic->setVisible(false);
	_selectedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_selectedPic, level); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h

	// ���o�j�p
	_BtnSize = _normalPic->getContentSize();
	// �]�w�P�_�ϰ�
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;

	_bTouched = false;
	_fScale = 1.0f;	_ftouchedScale = 1.15f;
	_bVisible = _bEnabled = true;
	_bStatus = false;
}

void CSwitch::setButtonInfo(const char *normalImg, const char *selectedImg, const char *enableImg, Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_selectedPic = (Sprite *)Sprite::createWithSpriteFrameName(selectedImg);
	_enablePic = (Sprite *)Sprite::createWithSpriteFrameName(enableImg);
	//_enablePic->setColor(Color3B::RED);
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_selectedPic->setPosition(_BtnLoc); // �]�w��m
	_enablePic->setPosition(_BtnLoc);
	_selectedPic->setVisible(false);
	_selectedPic->setScale(1.15f);
	_enablePic->setVisible(false);
	parent.addChild(_normalPic, level);  // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_selectedPic, level); // �[�J�ثe�� Layer �� 1: Z �b���h���A�V�j�N��b�V�W�h
	parent.addChild(_enablePic, level);

	// ���o�j�p
	_BtnSize = _normalPic->getContentSize();
	// �]�w�P�_�ϰ�
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;

	_bTouched = false;
	_fScale = 1.0f;    _ftouchedScale = 1.15f;
	_bVisible = _bEnabled = true;
	_bStatus = false;
}


bool CSwitch::touchesBegin(cocos2d::Point inPos)
{
	if (_BtnRect.containsPoint(inPos) && _bVisible && _bEnabled)
	{
		_bTouched = true;
		_normalPic->setVisible(_bStatus);
		_selectedPic->setVisible(!_bStatus);
		return(true); // �����b�W��
	}
	return(false);
}

bool CSwitch::touchesMoved(cocos2d::Point inPos)
{
	if (_bTouched) { // �u���Q�����ɭԤ~�B�z
		if (!_BtnRect.containsPoint(inPos)) { // ����Y��m���}���s
			_bTouched = false;
			_normalPic->setVisible(!_bStatus);
			_selectedPic->setVisible(_bStatus);
			return(false);
		}
		else return(true);
	}
	return(false); // �ƫ�A������s�W�N�Q����
}

bool CSwitch::touchesEnded(cocos2d::Point inPos)
{
	if (_bTouched)
	{
		_bTouched = false;
		_bStatus = !_bStatus;
		if (_BtnRect.containsPoint(inPos)) return(true);  // ����Y��m���s�ɡA�٦b�ӫ��s�W
	}
	return false;
}


void CSwitch::setVisible(bool bVisible)
{
	_bVisible = bVisible;
	if (!_bVisible) {
		_normalPic->setVisible(false);
		_selectedPic->setVisible(false);
		if (_enablePic != NULL)_enablePic->setVisible(false);
	}
	else {
		_selectedPic->setVisible(_bStatus);
		if (_enablePic != NULL) {
			_normalPic->setVisible(!_bStatus * _bEnabled);
			_enablePic->setVisible(!_bEnabled);
		}
		else {
			_normalPic->setVisible(!_bStatus);
		}
	}
}

void  CSwitch::setStatus(bool status) {
	_bStatus = status;

	_normalPic->setVisible(!status);
	_selectedPic->setVisible(status);
}


void CSwitch::setEnabled(bool bEnable)
{
	_bEnabled = bEnable;

	if (_bEnabled) {
		_normalPic->setVisible(!_bStatus);
		_selectedPic->setVisible(_bStatus);

		if (_enablePic != NULL) {
			_enablePic->setVisible(false);
		}
		else {
			_normalPic->setColor(Color3B(255, 255, 255));
		}
	}
	else {
		_selectedPic->setVisible(false);
		if (_enablePic != NULL) {
			_normalPic->setVisible(false);
			_enablePic->setVisible(true);
		}
		else {
			_normalPic->setVisible(true);
			_normalPic->setColor(Color3B(50, 50, 50));
		}
	}

}

void CSwitch::setTouchScale(float s) {
	_ftouchedScale = s;
	_selectedPic->setScale(_fScale*_ftouchedScale);
}

void CSwitch::setPosition(Vec2 locPt) {
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // �]�w��m
	_selectedPic->setPosition(_BtnLoc); // �]�w��m
	if (_enablePic != NULL) _enablePic->setPosition(_BtnLoc);

	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
}

void CSwitch::setScale(float fscale)
{
	_fScale = fscale;
	// ���s�]�w�P�_�ϰ�d��
	_BtnRect.size.width *= _fScale;
	_BtnRect.size.height *= _fScale;
	_BtnRect.origin.x = _BtnLoc.x - _BtnRect.size.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnRect.size.height*0.5f;
	_normalPic->setScale(_fScale);
	_selectedPic->setScale(_fScale*_ftouchedScale);
	if (_enablePic != NULL) _enablePic->setScale(_fScale);
}
