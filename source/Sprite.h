#if !defined(_SPRITE_)
#define _SPRITE_

#include "Iw2DSceneGraph.h"

class Sprite {
public:
	float m_X = 0;
	float m_Y = 0;
	float m_W = 0;
	float m_H = 0;
	float m_ScaleX = 1.f;
	float m_ScaleY = 1.f;
	float m_AnchorX = 0.f;
	float m_AnchorY = 0.f;
	bool isVisible = true;

	//Timer settings
	bool timer = false;
	float scale = 1.f;

	CIw2DImage* image;

	Sprite();

	~Sprite();

	void SetImage(CIw2DImage* img);

	CIw2DImage* GetImage();

	void Render();

	bool HitTest(float x, float y);

	void RenderTimer();
};

#endif