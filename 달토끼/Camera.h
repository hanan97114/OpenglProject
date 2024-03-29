#pragma once
#include "PlayerObserver.h"

class CMediator;
class CPlayer;

class CCamera 
	: public PlayerObserver
{
	CVector3D<> m_at{ 0.f, 0.f, 0.f };
	CVector3D<> m_up{ 0.f, 1.f,0.f };

	float m_distance{ 0 };

	//각도
	float m_vertical{ 0 };
	float m_horizontal{ 0 };

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

	const double PI{ 3.141592 };
	
	//Camera Animation
	CMediator* m_pMediator{ nullptr };

	//bool isPlayerDead{ false };
	bool isGameClear{ false };
	bool isAnimate{ false };
	bool isMapCamera{ false };

	float Rotatedegree{ 0 };

private:
	void Animation_GameClear();

public:
	// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.
	CCamera();

	~CCamera() = default;

	void IsMapCamera() { isMapCamera = true; }
	void Initialize(const CVector3D<> & pos, float distance, float zNear, float zFar, float fov);
	//void Initialize(CVector3D<> && pos, float distance, float zNear, float zFar, float fov);

	void SetAspect(float aspect) { m_aspect = aspect; }
	CVector3D<> GetPosition()	const { return m_at; }

	void SetPosition(const CVector3D<>& at);
	void SetPosition(CVector3D<>&& at)	noexcept;
	void Move(const CVector3D<>& at)	noexcept;
	void Move(CVector3D<>&& at)		noexcept;

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }
	
	void zoom(float per) { m_distance = m_distance * per; }

	void Rotate(float v, float h);
	void Rotate(int degree_v, int degree_h);
	const float GetVertical() const noexcept { return m_vertical; }
	const float GetHorizon() const noexcept { return m_horizontal; }

	void LookAt() const;

	CVector3D<> GetLookVector() const;

	CVector3D<> eye() const;


	void Update();

	//////////////////////////////////Receive
	virtual void Receive_PlayerWaitCamera(CPlayer* player) override;
	virtual void Receive_PlayerJumpFinish(CPlayer* player) override {};
	virtual void Receive_PlayerJumping(CPlayer* player) override;
	virtual void Receive_PlayerAutoWaiting(CPlayer* player) override {};
	//////////////////////////////////Receive
	
	void Init_FistPerspective();
	void Init_ThirdPerspective();
	virtual void Init_MainScene();
	virtual void Init_GameOver();
	virtual void Init_GameClear();

	virtual void Init_GameScene();
	virtual void Player_Dead(const float& rotatedegree);
	
	virtual void Player_Clear(const float& rotatedegree);
};
