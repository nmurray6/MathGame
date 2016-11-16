#include "Sprite.h"

Sprite::Sprite() {

}

Sprite::~Sprite() {
}

void Sprite::SetImage(CIw2DImage* img) {
	image = img;
}

CIw2DImage* Sprite::GetImage() {
	return image;
}

void Sprite::Render() {
	if (isVisible) {
		if (timer)
			RenderTimer();
		else {
			CIwFVec2* location = new CIwFVec2();
			location->x = (float)m_X - ((float)m_W * m_AnchorX);
			location->y = (float)m_Y - ((float)m_H * m_AnchorY);

			CIwFVec2* size = new CIwFVec2();
			size->x = m_W;
			size->y = m_H;

			Iw2DDrawImage(image, *location, *size);

			delete location;
			delete size;
		}
	}
}

bool Sprite::HitTest(float x, float y) {
	if (isVisible) {
		float px = (float)m_X - ((float)m_W * m_AnchorX);
		float py = (float)m_Y - ((float)m_H * m_AnchorY);
		return (x >= px
			&& x <= px + m_W
			&& y >= py
			&& y <= py + m_H);
	}
	else {
		return false;
	}
}

void Sprite::RenderTimer() {
	if (isVisible) {
		CIwFVec2* location = new CIwFVec2();
		location->x = (float)m_X - ((float)m_W * m_AnchorX);
		location->y = (float)m_Y - ((float)m_H * m_AnchorY);

		CIwFVec2* size = new CIwFVec2();
		size->x = m_W;
		size->y = m_H * scale;

		CIwFVec2* offset = new CIwFVec2();
		offset->x = 0;
		offset->y = 0;

		CIwFVec2* regionSize = new CIwFVec2();
		regionSize->x = image->GetWidth();
		regionSize->y = image->GetHeight() * scale;
		Iw2DDrawImageRegion(image, *location, *size, *offset, *regionSize);

		delete location;
		delete offset;
		delete size;
		delete regionSize;
	}
}