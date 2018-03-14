#include "pch.h"
#include "FootBoard.h"
#include "JumpProperty.h"
#include "FootBoardManager.h"

FootBoardManger::FootBoardManger()
{
	//Test
	m_boardNum = 100;
	//Test
	InitFootBoardModel();
	m_pFootBoard = new CFootBoard[m_boardNum];
}

FootBoardManger::~FootBoardManger()
{
	delete[] m_pFootBoard;
}

void FootBoardManger::Initialize()
{
	if (!m_pFootBoard) return;

	JumpProperty::Initialize();
	
	m_pFootBoard[0].InitPosition(CVector3D<>(0, -5, 0));

	//맨 첫번째는 이동하지 않으므로 1부터 시작
	srand(time(NULL));
	for (int x = 1; x < m_boardNum - 1; ++x) {
		int nowSide = k_side[rand() % 3];

		//왼쪽발판 다음에서 오른쪽 발판이 생성되는 경우
		bool Is_Left_to_Right = (prev_Side == k_left) && (nowSide == k_right);
		if (Is_Left_to_Right) {
			nowSide = k_front;
		}

		//오른쪽발판 다음에서 왼쪽 발판이 생성되는 경우
		bool Is_Right_to_Left = (prev_Side == k_right) && (nowSide == k_left);
		if (Is_Right_to_Left) {
			nowSide = k_front;
		}

		float tranlateX = Road_Distance_X * nowSide;
		float tranlateZ = -x * JumpProperty::Get_JumpReach();
		m_pFootBoard[x].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));

		prev_Side = nowSide;
	}
	//마지막은 반드시 가운데
	float tranlateX = 0;
	float tranlateZ = -(m_boardNum - 1) * JumpProperty::Get_JumpReach();
	m_pFootBoard[m_boardNum - 1].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));
	m_pFootBoard[m_boardNum - 1].IsLight();
}

void FootBoardManger::InitFootBoardModel()
{
	CFootBoard::InitModel();
}

//전부 렌더합니다.
void FootBoardManger::TestRender()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int x = 0; x < m_boardNum; ++x) {
		m_pFootBoard[x].Render();
	}

	glDisable(GL_BLEND);
}

void FootBoardManger::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//플레이어 위치 기준으로 다섯개까지 렌더한다.
	//int MaxNum = min(m_boardNum - 1, m_PlayerBoardIndex + 5);
	for (int x = m_DisappearingBoardIndex; x < m_DisappearingBoardIndex + 7; ++x) {
		m_pFootBoard[x].Render();
	}
	m_pFootBoard[m_boardNum - 1].Render();
	glDisable(GL_BLEND);
}

void FootBoardManger::Update()
{
	m_pFootBoard[m_DisappearingBoardIndex].Update();
}

const CVector3D<> FootBoardManger::Get_LastPos() const noexcept
{
	return m_pFootBoard[m_boardNum - 1].Get_Pos();
}

const CVector3D<> FootBoardManger::Get_FirstPos() const noexcept
{
	return m_pFootBoard[0].Get_Pos();
}

const bool FootBoardManger::IsOutRange() const
{
	return (m_DisappearingBoardIndex < 0 || m_DisappearingBoardIndex >= m_boardNum);
}

const bool FootBoardManger::CheckSide(const int & side)
{
	return false;
}
