#pragma once

#include <Vector>
#include "cocos2d.h"
#include "common_tool/CButton.h"
#include "common_tool/CSwitch.h"

#define color_red Color3B(197,95,80)
#define color_blue Color3B(52,116,233)
#define color_black Color3B(84,84,84)
#define INTERFACE_LEVEL 1
#define WHITEBOARD_LEVEL 0

using namespace std;
using namespace cocos2d;

//enum tool { redpen, blackpen, bluepen, eraser };
enum color { black, blue, red };
enum mode { PEN_MODE, ERASER_MODE };

class CDrawingPanel : public Ref
{
protected:
	RenderTexture *_pWhiteBoard;
	Sprite* _pPenBrush;
	Sprite* _pEraserBrush;

	Vector <Sprite*> _penBrushList;
	Vector <Sprite*> _eraserBrushList;

	Color3B _lineColor, _defaultColor[3];
	int     _toolMode;
	float	_brushSize;

	static CDrawingPanel* _pHandDrawing;

public:
	static CDrawingPanel *create();		// �إߪ��󪺹���
	static CDrawingPanel *getInstance();	// ���o CDrawingPanel ������
	void   initDrawingPanel(Node &rootNode, cocos2d::Layer &parent);	// �]�w��l���e

	void setLineColor(Color3B color);
	void drawing(Point &pt);
	void clearWhiteBoard();	// �M���Ҧ�ø�s�b�e���W���u��
	void SetPen(int colorNum);
	void setMode(int mode) { _toolMode = mode; }
	void setBrushSize(float s) { _brushSize = s; }
	Color3B getColor() { return (_lineColor); }

	bool touchesBegin(Point inPt);
	bool touchesMoved(Point inPt, Point inPrePt);
	bool touchesEnded(Point inPt);
	void doStep(float dt);

	CDrawingPanel();
	~CDrawingPanel();
};
