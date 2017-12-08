#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "PLAY_word.h"


CPLAY_word::CPLAY_word(const CVector3D<>& pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj("PLAYWORD.obj");
	m_model->LoadTexture("PLAYWORD.bmp");

	m_Position = pos;
	m_matrix = new CMatrix;
	m_matrix->Set_Translate(m_Position);
}


CPLAY_word::~CPLAY_word()
{
	delete m_model;
	delete m_matrix;
}

void CPLAY_word::Render()
{
	glPushMatrix();
	m_matrix->MultiMatrix();
	m_model->Render();
	glPopMatrix();
}

void CPLAY_word::Update()
{
	if (IsGameStart) {
		//내려간다
		m_matrix->Calu_Rotate(5, 0, 1, 0);
	}
	if (!IsSelected) return;

	if (SizeTime >= 1.f) {
		SizeTime = 0.f;
		float temp = BeginSize;
		BeginSize = EndSize;
		EndSize = temp;
	}

	SizeTime += 0.03f;
	NowSize = Interpolation(BeginSize, EndSize, SizeTime);

	m_matrix->Set_Scale(NowSize);
}

void CPLAY_word::Init_MainScene()
{
	m_matrix->Set_Translate(m_Position);
	m_matrix->ResetRotate();
	IsGameStart = false;
}

void CPLAY_word::GameStart()
{
	//회전 한바퀴
	IsGameStart = true;
}

void CPLAY_word::Scale(const float & NowSize)
{
	m_matrix->Calu_Scale(NowSize);
}

void CPLAY_word::NotSelected()
{
	IsSelected = false;
	NowSize = 1.f;
	SizeTime = 0.f;
	BeginSize = 1.1f;
	EndSize = 1.3f;
	m_matrix->ResetScale();
}
