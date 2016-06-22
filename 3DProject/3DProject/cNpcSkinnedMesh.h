#pragma once

#include "cAllocateHierarchy.h"

struct ST_BONE;

class cNpcSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;

	D3DXMATRIX					m_matNeckTM;
	D3DXMATRIX					m_matHairTM;
	D3DXMATRIX					m_matTailTM;
	D3DXMATRIX					m_matWeaponHandTM;
	D3DXMATRIX					m_matLocal;
	D3DXMATRIX					m_matWorld;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	bool						m_isBleding;
	float						m_fPassedBlendTime;
	float						m_fBlendTime;

	LPDIRECT3DTEXTURE9			m_pTex;

public:
	cNpcSkinnedMesh(char* szFolder, char* szFilename);
	~cNpcSkinnedMesh();

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // 테스트용
	void GetNeckWorld(D3DXFRAME* pFrame, D3DXMATRIX* pParentTM);

	void SetSpecTex(LPDIRECT3DTEXTURE9 tex) { m_pTex = tex; }
	LPDIRECT3DTEXTURE9 GetSpecTex() { return m_pTex; }

	void SetNeckTM(D3DXMATRIX* neck) { m_matNeckTM = *neck; }
	D3DXMATRIX GetNeckTM() { return m_matNeckTM; }

	void SetHairTM(D3DXMATRIX* hair) { m_matHairTM = *hair; }
	D3DXMATRIX GetHairTM() { return m_matHairTM; }

	void SetTailTM(D3DXMATRIX* tail) { m_matTailTM = *tail; }
	D3DXMATRIX GetTailTM() { return m_matTailTM; }

	void SetWeaponTM(D3DXMATRIX* tail) { m_matWeaponHandTM = *tail; }
	D3DXMATRIX GetWeaponTM() { return m_matWeaponHandTM; }

	void SetLocal(D3DXMATRIX* local) { m_matLocal = *local; }
	D3DXMATRIX GetLocal() { return m_matLocal; }

	void SetWorld(D3DXMATRIX* World) { m_matLocal = *World; }
	D3DXMATRIX GetWorld() { return m_matWorld; }

	DOUBLE GetAniTrackPeriod(int nIndex);

private:
	cNpcSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

