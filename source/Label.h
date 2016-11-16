#if !defined(_LABEL_H)
#define _LABEL_H
#include <stdio.h>
#include "Iw2DSceneGraph.h"
#include "IwGx.h"

class Label {
private:
	CIwFMat2D _mat;
	float m00;
	float m11;
public:
	float m_X;
	float m_Y;
	float m_W;
	float m_H;
	float scale;
	bool isVisible = true;
	char text[120];
	CIw2DFontAlign horizontalAlignment = IW_2D_FONT_ALIGN_CENTRE;
	CIw2DFontAlign verticalAlignment = IW_2D_FONT_ALIGN_CENTRE;
	CIw2DFont *font;

	Label();
	~Label();

	void Render();

	void SetText(char*);
};

#endif