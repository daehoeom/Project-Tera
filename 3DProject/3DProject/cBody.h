#pragma once
class cAllocateHierarchy;
struct ST_BONE_MESH;

class cBody
{

public:
	cBody();
	~cBody();
	void Setup(char* FolderName, char* FileName);
	void Update();
	void Render();
	void RecursiveFrameRender(D3DXFRAME* pParent, D3DXMATRIX* pParentWorldTM);
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIX* pmatParent);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
	void GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);
	void SetAnimationIndex(int nIndex);
	LPD3DXFRAME& GetFrameRoot();
	DOUBLE GetAniTrackPeriod(int nIndex);

	void SetNeckTM(D3DXMATRIX* neck) { m_matNeckTM = *neck; }
	D3DXMATRIX GetNeckTM() { return m_matNeckTM; }

	void SetHairTM(D3DXMATRIX* hair) { m_matHairTM = *hair; }
	D3DXMATRIX GetHairTM() { return m_matHairTM; }

	void SetTailTM(D3DXMATRIX* tail) { m_matTailTM = *tail; }
	D3DXMATRIX GetTailTM() { return m_matTailTM; }

	void SetWeaponBack(D3DXMATRIX* weaponBack) { m_matWeaponBackTM = *weaponBack; }
	D3DXMATRIX GetWeaponBack() { return m_matWeaponBackTM; }

	void SetWeaponHand(D3DXMATRIX* weaponHand) { m_matWeaponHandTM = *weaponHand; }
	D3DXMATRIX GetWeaponHand() { return m_matWeaponHandTM; }

	void SetWorld(D3DXMATRIX* world) { m_matWorld = *world; }
	D3DXMATRIX GetWorld() { return m_matWorld; }

	void SetBlend(bool check) { m_bCheckBlend = check;}
	bool GetBlend() { return m_bCheckBlend; }

private:
	//X파일
	cAllocateHierarchy*			m_pAlloc;
	LPD3DXFRAME					m_pFrameRoot;
	LPD3DXFRAME					m_pFrameRootOrigin;

	//string						
	std::string					m_sPath;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;

	LPD3DXMESH					m_pMesh;
	LPD3DXBUFFER				m_pBuffer;
	std::vector<LPDIRECT3DTEXTURE9>	m_vecTexture;
	float						m_ft;

	D3DXMATRIX					m_matNeckTM;
	D3DXMATRIX					m_matHairTM;
	D3DXMATRIX					m_matTailTM;

	D3DXMATRIX					m_matWeaponBackTM;
	D3DXMATRIX					m_matWeaponHandTM;

	D3DXMATRIX					m_matWorld;

	//보간
	bool						m_bIsBlend;
	float						m_fPassedBlendTime;
	float						m_fBlendTime;
	bool						m_bCheckBlend;
};

