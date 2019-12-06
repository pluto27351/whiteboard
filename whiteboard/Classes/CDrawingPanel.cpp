#include "CDrawingPanel.h"

CDrawingPanel* CDrawingPanel::_pHandDrawing = nullptr;

CDrawingPanel::~CDrawingPanel() {
	_penBrushList.clear();
	_eraserBrushList.clear();
	_pHandDrawing = nullptr;
}

CDrawingPanel *CDrawingPanel::create()
{ // 建立物件的實體

	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawingPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	else return _pHandDrawing;
}

CDrawingPanel *CDrawingPanel::getInstance()
{
	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawingPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	return _pHandDrawing;
}


void  CDrawingPanel::initDrawingPanel(Node &rootNode, cocos2d::Layer &parent)	// 設定初始內容
{
	
	_lineColor = _defaultColor[black] = color_black;
	_defaultColor[blue] = color_blue;
	_defaultColor[red] = color_red;

	_toolMode = PEN_MODE;
	_brushSize = 0.3f;

	// 建立白板
	Size size = rootNode.getContentSize();
	_pWhiteBoard = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
	_pWhiteBoard->retain();
	_pWhiteBoard->setPosition(Vec2(size.width / 2, size.height / 2));
	parent.addChild(_pWhiteBoard, WHITEBOARD_LEVEL);

	_pPenBrush = (Sprite *)Sprite::createWithSpriteFrameName("brush.png");
	_pPenBrush->retain();
	_pPenBrush->setColor(_lineColor);

	_pEraserBrush = (Sprite *)Sprite::createWithSpriteFrameName("eraser_brush.png");
	_pEraserBrush->retain();

}



void CDrawingPanel::doStep(float dt)
{

}


CDrawingPanel::CDrawingPanel()
{

}


void CDrawingPanel::drawing(Point &pt)
{


}


void CDrawingPanel::clearWhiteBoard()
{
	_pWhiteBoard->clear(0, 0, 0, 0);
}

void CDrawingPanel::setLineColor(Color3B color)
{
	_lineColor = color;
}


bool CDrawingPanel::touchesBegin(cocos2d::Point inPt)
{
	return(false);
}

bool CDrawingPanel::touchesMoved(Point inPt, Point inPrePt)
{
	bool bBtnOn = false;

	// 產生手繪線
	if (!bBtnOn) {
		_pWhiteBoard->begin();
		float distance = inPt.getDistance(inPrePt);
		if (distance > 1) {
			if (_toolMode == PEN_MODE) {
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("brush.png");;
					sprite->setColor(_lineColor);
					sprite->setScale(_brushSize);
					_penBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_penBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_penBrushList.at(i)->visit();
				}
			}
			else if (_toolMode == ERASER_MODE) {
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("eraser_brush.png");
					sprite->setColor(Color3B(250, 250, 250));
					BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
					sprite->setBlendFunc(blendFunc);
					sprite->setScale(_brushSize);
					_eraserBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_eraserBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_eraserBrushList.at(i)->visit();
				}
			}
		}
		_pWhiteBoard->end();
		if (!_penBrushList.empty()) _penBrushList.clear();
		if (!_eraserBrushList.empty()) _eraserBrushList.clear();
	}
	return(true);
}

bool CDrawingPanel::touchesEnded(cocos2d::Point inPt) //只有清除按鈕回傳true
{
	return(false);
}



void CDrawingPanel::SetPen(int colorNum) {
	_lineColor = _defaultColor[colorNum];
	_pPenBrush->setColor(_lineColor);

}

