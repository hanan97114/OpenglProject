#include "pch.h"
#include "SceneManager.h"
#include "ObjModel.h"
#include "RotateMatrix.h"
#include "Moon.h"

CObjModel* CMoon::m_Moon = nullptr;

void CMoon::InitModel()
{
	if (m_Moon != nullptr) return;
	m_Moon = new CObjModel;
	m_Moon->LoadObj(".\\OBJModel\\Moon.obj");
	m_Moon->LoadTexture(".\\Texture\\Moon.bmp");
}

void CMoon::DeleteModel()
{
	if (m_Moon == nullptr) return;

	delete m_Moon;
	m_Moon = nullptr;
}


CMoon::CMoon(CMediator *& mediator)
{
	InitModel();

	m_pMediator = mediator;

	m_Matrix = new RotateMatrix;
}

CMoon::~CMoon()
{
	DeleteModel();
	delete m_Matrix;
}

void CMoon::Initialize()
{

}

void CMoon::SetPos(const CVector3D<>& rhs)
{
	m_Position = rhs;
	//m_Matrix->Set_Translate(rhs);
	//m_Matrix->Set_Scale(0.7);
}

void CMoon::SetPos(CVector3D<>&& rhs)
{
	m_Position = rhs;
	//m_Matrix->Set_Translate(rhs);
	//m_Matrix->Set_Scale(0.7);
}

void CMoon::Update()
{
	if (IsGameStart) {
		m_Matrix->Calu_Rotate(6, 0, 1, 0);
		m_Position.y += 5;

		if (m_Position.y > 400) {
			CSceneManager::GetInstance()->ChangeToGame();
		}

		return;
	}

	Float();
	m_Moon->Rotate(1, 0, 1, 0);
}

void CMoon::Render()
{
	if (m_Moon == nullptr) return;

	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_Matrix->Rotate();
	glScalef(m_Scale, m_Scale, m_Scale);
	m_Moon->Render();
	glPopMatrix();
}

void CMoon::Float()
{
	if (!IsFloat) return;

	m_Time += 0.02f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_BeginY = m_EndY;
		m_EndY = -m_EndY;
	}

	GLdouble MoveY = Interpolation(m_BeginY, m_EndY, m_Time);
	//m_Matrix->Calu_Tranlate(CVector3D<>(0, MoveY, 0));
	m_Position.y += MoveY;
}

void CMoon::Init_MainScene()
{
	SetPos(CVector3D<>(100, 0, 0));
	m_Matrix->ResetRotate();
	IsFloat = true;
	IsGameStart = false;
	m_Scale = 0.7f;
}

void CMoon::Init_GameScene()
{
	m_Matrix->ResetRotate();
	IsFloat = false;
	IsGameStart = false;
	m_Scale = 1.5f;
}

void CMoon::GameStart()
{
	IsGameStart = true;
}
