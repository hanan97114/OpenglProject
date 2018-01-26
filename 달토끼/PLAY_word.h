#pragma once
#include "Observer.h"

class CObjModel;
class CMatrix;

class CPLAY_word
	: public Observer
{
	CVector3D<> m_Position;
	CObjModel* m_model{ nullptr };
	CMatrix* m_matrix{ nullptr };

	float NowSize{ 1.f };
	
	float BeginSize	{ 1.1f };
	float EndSize	{ 1.3f };
	float SizeTime{ 0.f };

	bool IsSelected{ false };
	bool IsGameStart{ false };
public:
	CPLAY_word(const CVector3D<>& Pos);
	~CPLAY_word();
	

	void Scale(const float& NowSize);
	void Selected() { IsSelected = true; }
	void NotSelected();
	const CVector3D<>& Get_Pos() const noexcept { return m_Position; }

	virtual void Render();
	virtual void Update();

	//메인화면
	virtual void Init_MainScene();
	virtual void Cursor_PLAY() { Selected(); };
	virtual void Cursor_EXIT() { NotSelected(); };
	virtual void GameStart();
	
	//게임화면
	virtual void Init_GameScene() {};
	virtual void Player_JumpStart() {};
	virtual void Player_Jumping() {};
	virtual void Player_JumpFinish() {};
	virtual void Player_Dead() {};
};

