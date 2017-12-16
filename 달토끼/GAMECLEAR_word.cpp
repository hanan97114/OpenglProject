#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "GAMECLEAR_word.h"


CGAMECLEAR_word::CGAMECLEAR_word(const CVector3D<>& Pos)
{

	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj("GAMECLEARWORD.obj");
	m_model->LoadTexture("GAMECLEARWORD.bmp");
	
	m_Position = Pos;
	m_matrix = new CMatrix;
	m_matrix->Set_Translate(m_Position);
}

CGAMECLEAR_word::~CGAMECLEAR_word()
{
}

void CGAMECLEAR_word::Render()
{
	glColor3f(LIGHTRGB[0], LIGHTRGB[1], LIGHTRGB[2]);
	glPushMatrix();
	m_matrix->MultiMatrix();
	m_model->Render();
	glPopMatrix();
}

void CGAMECLEAR_word::Update()
{
}
