#include "pch.h"
#include "RotateMatrix.h"
#include "ObjModel.h"
#include "EXIT_word.h"


CEXIT_word::CEXIT_word(const CVector3D<>& Pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj(".\\OBJModel\\EXITWORD.obj");
	m_model->LoadTexture(".\\Texture\\EXITWORD.bmp");

	m_Position = Pos;
	m_InitPosition = Pos;

	m_matrix = new RotateMatrix;
}

CEXIT_word::~CEXIT_word()
{
	delete m_model;
	delete m_matrix;
}

void CEXIT_word::Render()
{
	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_matrix->Rotate();
	glScalef(NowSize, NowSize, NowSize);
	m_model->Render();
	glPopMatrix();
}

void CEXIT_word::Update()
{
	if (IsGameStart) {
		//��������
		m_Position.y -= 5;
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

}

void CEXIT_word::Scale(const float & Size)
{
	NowSize = Size;
}

void CEXIT_word::NotSelected()
{
	IsSelected = false;
	NowSize = 1.f;
	SizeTime = 0.f;
	BeginSize =  1.1f;
	EndSize = 1.3f;
}

void CEXIT_word::Init_MainScene()
{
	m_Position = m_InitPosition;
	m_matrix->ResetRotate();
	IsGameStart = false;

	IsSelected = false;
	NowSize = 1.f;
	SizeTime = 0.f;
	BeginSize = 1.1f;
	EndSize = 1.3f;
}
