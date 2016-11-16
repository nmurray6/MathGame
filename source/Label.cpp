#include "Label.h"

Label::Label() {
	m_X = 0.f;
	m_Y = 0.f;
	m_W = 0.f;
	m_H = 0.f;
	scale = 1.f;
	sprintf(text, "%s", "");
	_mat = Iw2DGetTransformMatrix();
}

Label::~Label() {

}

void Label::Render() {
	if (isVisible) {
		Iw2DSetFont(font);

		_mat = Iw2DGetTransformMatrix();


		m00 = _mat.m[0][0];
		m11 = _mat.m[1][1];

		m00 *= scale;
		m11 *= scale;

		_mat.m[0][0] = m00;
		_mat.m[1][1] = m11;

		_mat.SetTrans(CIwFVec2(m_X, m_Y));

		Iw2DSetTransformMatrix(_mat);

		CIwFVec2 topLeft(0, 0);
		CIwFVec2 size(m_W * 1 / scale, m_H * 1 / scale);

		Iw2DDrawString(text, topLeft, size, horizontalAlignment, verticalAlignment);

		Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);
	}
}

void Label::SetText(char* string) {
	sprintf(text, "%s", string);
}