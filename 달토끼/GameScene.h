#pragma once
#include "Scene.h"

class CPlayer;
class CMoon;
class CEarth;
class CRoad;
class CMediator;
class CCamera;

class CGameScene :
	public CScene
{
	CPlayer * m_Player{ nullptr };
	CMoon * m_Moon{ nullptr };
	CEarth * m_Earth{ nullptr };
	CCamera* m_Camera{ nullptr };
	CRoad * m_Road{ nullptr };

	CMediator * m_Mediator{ nullptr };

	bool Start{ false };

public:
	CGameScene();
	virtual ~CGameScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Update();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};

