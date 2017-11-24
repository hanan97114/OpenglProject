#pragma once
#include "Colleague.h"

class CFootBoard;
class CMediator;

class CRoad : public CColleague
{
	const int k_side[3] = { k_left, k_front, k_right };
	CFootBoard* m_pFootBoard;
	int m_boardNum{ 100 };
	int m_PlayerPosNum{ 0 };
	int m_DisappearBoardNum{ 0 };

	CMediator* m_Mediator{ nullptr };

	bool isPlayerDead{ false };

private:
	void InitFootBoardModel();
	void InitFootBoardPos(const GLdouble& distance);

public:
	CRoad(const GLdouble& distance, CMediator*& mediator);
	~CRoad();

	void Render();
	void Update();

	//Mediator
	virtual void Player_JumpFinish();
	virtual void Player_Dead();
	virtual void Road_playerBoard_Disapper();
};

