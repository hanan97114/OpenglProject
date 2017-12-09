#include "pch.h"
#include "SceneManager.h"
#include "Mediator.h"
#include "Player.h"
#include "Moon.h"
#include "Earth.h"
#include "Camera.h"
#include "Skybox.h"
#include "Road.h"
#include "TextureStorage.h"
#include "GameScene.h"

void CGameScene::RenderBack()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -100.f, 100);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(LIGHTRGB[0], LIGHTRGB[1], LIGHTRGB[2]);
	glBindTexture(GL_TEXTURE_2D, m_BackgroundTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3d(Left, Top, 0);
	glTexCoord2f(1.f, 1.f);
	glVertex3d(Right, Top, 0);
	glTexCoord2f(1.f, 0.f);
	glVertex3d(Right, Bottom, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex3d(Left, Bottom, 0);
	glEnd();

	glClear(GL_DEPTH_BUFFER_BIT);
}

CGameScene::CGameScene(CSceneManager* const changer)
{
	m_pSceneManager = changer;
	m_pMediator = new CMediator(m_pSceneManager);

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap("Background.bmp", m_BackgroundTextureID);


	m_Camera = new CCamera(m_pMediator);
	m_Player = new CPlayer(m_pMediator);
	double distance = m_Player->Get_JumpReach();
	m_Road = new CRoad(distance, m_pMediator);
	int LastZ = m_Road->GetLastPos()[2];
	m_Skybox = new CSkybox(LastZ);

	m_pMediator->SetPlayer(m_Player);
	m_pMediator->SetRoad(m_Road);
	m_pMediator->SetCamera(m_Camera);

	GLdouble DownY = 60;
	CVector3D<> MoonPos = m_Road->GetLastPos();
	m_Moon = new CMoon(CVector3D<>(MoonPos[0] , MoonPos[1]- DownY, MoonPos[2]));

	CVector3D<> EarthPos = m_Road->GetFirstPos();
	m_Earth = new CEarth(m_pMediator);
	m_Earth->SetPos(CVector3D<>(EarthPos[0], EarthPos[1] - DownY + 10, EarthPos[2]));

	Initialize();

	//임시로 쓰이는 라이트값
	GLfloat gray[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat ambient[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat lightPos[] = { 0, 30, -30, 0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//임시로 쓰이는 라이트값
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

CGameScene::~CGameScene()
{
	delete m_Player;
	m_Player = nullptr;

	delete m_Moon;
	m_Moon = nullptr;
	
	delete m_Earth;
	m_Earth = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	delete m_Road;
	m_Road = nullptr;

	delete m_pMediator;
	m_pMediator = nullptr;

	delete m_Skybox;
	m_Skybox = nullptr;
}

void CGameScene::Initialize()
{
	m_pMediator->Init_GameScene();
	Start = false;
}


void CGameScene::Render()
{
	//반드시 스카이박스는 맨 처음에 렌더
	RenderBack();
	m_Camera->LookAt();

	m_Skybox->Render();

	m_Road->Render();

	m_Player->Render();
	//m_Earth->Render();
	//m_Moon->Render();
	
}

void CGameScene::Update()
{
	m_Camera->Update();
	m_Skybox->Update();

	if (!Start) return;

	m_Player->Update();

	m_Road->Update();

	m_Earth->Update();
	m_Moon->Update();
}

void CGameScene::Reshape(const int& w, const int& h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();
	
	glMatrixMode(GL_MODELVIEW);
}

void CGameScene::Timer(const int& value)
{
	Update();
	
	glutPostRedisplay();
}

void CGameScene::Keyboard(const unsigned char& key, const int& x, const int& y)
{
	if (nullptr != m_Player) {
		//m_Player->Keyboard(key, x, y);
	}

	if (key == '=' || key == '+') {
		m_Camera->zoom(0.8f);
	}
	if (key == '-' || key == '_') {
		m_Camera->zoom(1.2f);
	}

	if (key == 'd' || key =='D') {
		m_Camera->Rotate(10, 0);
	}
	if (key == 'a' || key == 'A') {
		m_Camera->Rotate(-10, 0);
	}
	if (key == 's' || key =='S') {
		m_Camera->Rotate(0, -10);
	}
	if (key == 'w' || key =='W') {
		m_Camera->Rotate(0, 10);
	}

	m_Camera->LookAt();
}

void CGameScene::SpecialKeys(const int& key, const int& x, const int& y)
{
	if (!Start) {
		Start = true;
	}

	m_Player->SpecialKeys(key, x, y);
}
