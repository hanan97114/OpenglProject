#pragma once

class CObjModel;

class CFootBoard
{
	static CObjModel* m_obj;
	static CObjModel* m_Light_obj;

	//c++은 static storage duration 가진 객체는
	//0을 보장합니다.
	//표준은 전역, 정적변수는 0으로 초기화함을 명시합니다.
	//static bool isInitModel;

	int m_Side{ -2 }; //-2는 존재하지 않음

	CVector3D<> m_Position			{ 0, -5, 0 };
	bool IsLast						{ false };
	bool IsLightDisappear			{ false };

	float		m_TextureAlpha		{1.f};
	const float m_DropAlphaUnit		{ 0.3f };
	//float		m_LightAlpha{ 0.5f };

	GLfloat m_Translate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	GLfloat m_Scale_Matrix[16] =
	{
		0.3f, 0, 0, 0,
		0, 0.3f, 0, 0,
		0, 0, 0.3f, 0,
		0, 0, 0, 1.f
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//움직임
	float DisappearTime{ 0.f };
	bool IsDisappear{ false };
	
private:
	//내부함수
	void Disappear();
	void RenderModel();

public:
	CFootBoard();
	~CFootBoard();
	static void InitModel();
	static void DeleteModel();
	void InitPosition(const int& x, const int & y, const int& z);
	void InitPosition(const CVector3D<>& rhs);
	void InitPosition(CVector3D<>&& rhs);
	void IsLight();
	void IsNotLight();
	void LightDisappear();

	void Render();
	void Update();

	const CVector3D<> Get_Pos() const noexcept { return m_Position; }
	const bool GetDisappear() const { return IsDisappear; }
	void Disappear_True() { IsDisappear = true; }
	const int GetSide() const noexcept { return m_Side; }

};



