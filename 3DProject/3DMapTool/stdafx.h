// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN     // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows dependent 헤더 파일:
#define NOMINMAX
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <CommCtrl.h>
#include <shellapi.h>

// C++ 런타임 헤더 파일입니다.
#include <cstdlib>
#include <memory>
#include <string>
#include <set>
#include <unordered_map>
#include <map>
#include <initializer_list>
#include <array>
#include <cstdint>
#include <vector>
#include <cassert>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "MainSurfaceWindow.h"
#include "InspectorWindow.h"
#include "HierarchyWindow.h"


// CommCtrl
#pragma comment( lib, "uxtheme" )
#pragma comment( lib, "comctl32" )

// D3DX
#pragma comment( lib, "d3d9.lib")
#ifdef _DEBUG
#	pragma comment( lib, "d3dx9d.lib")
#else
#	pragma comment( lib, "d3dx9.lib")
#endif

#define EPSILON 0.0001f
#define SAFE_RELEASE(p) {if (p) { (p)->Release(); (p) = NULL; }}
#define SAFE_ADD_REF(p) {if (p) { (p)->AddRef(); }}
#define SAFE_DELETE(p) {if (p) { delete (p); (p) = NULL; }}
#define SAFE_DELETE_ARRAY(p) {if (p) { delete [] (p); (p) = NULL; }}


#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(const varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}

enum
{
	MainWindowWidth = 800,
	MainWindowHeight = 800,

	HierarchyWindowWidth = 200,
	HierarchyWindowHeight = MainWindowHeight,

	InspectorWindowWidth = HierarchyWindowWidth,
	InspectorWindowHeight = MainWindowHeight/2,
};

extern std::unique_ptr<MainSurfaceWindow> g_mainSurfaceWnd;
extern std::unique_ptr<InspectorWindow> g_inspectorWnd;
extern std::unique_ptr<HierarchyWindow> g_hierarchyWnd;

struct ST_SPHERE
{
	D3DXVECTOR3 position;
	float radius;
};

struct ST_RAY
{
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
};

struct ST_PC_VERTEX
{
	//float x, y, z;
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX() {}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c)
		: p(_p)
		, c(_c)
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct ST_RHWC_VERTEX
{
	//float x, y, z;
	D3DXVECTOR4 p;
	D3DCOLOR	c;

	ST_RHWC_VERTEX() {}
	ST_RHWC_VERTEX(D3DXVECTOR4 _p, D3DCOLOR _c)
		: p(_p)
		, c(_c)
	{
	}

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE, };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };

	ST_PT_VERTEX() { }
	ST_PT_VERTEX(D3DXVECTOR3 _v, D3DXVECTOR2 _t)
		:p(_v), t(_t)
	{}
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	ST_PN_VERTEX() {}
	ST_PN_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n)
		: p(_p)
		, n(_n)
	{
	}
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL, };
};

struct ST_PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;
	D3DXVECTOR2 t;

	ST_PCT_VERTEX() {}
	ST_PCT_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c, D3DXVECTOR2 _t)
		: p(_p)
		, c(_c)
		, t(_t)
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1, };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	ST_PNT_VERTEX() {}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		: p(_p)
		, n(_n)
		, t(_t)
	{
	}
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct ST_POS_SAMPLE
{
	int				nKeyFrame;
	D3DXVECTOR3		v;
};

struct ST_ROT_SAMPLE
{
	int				nKeyFrame;
	D3DXQUATERNION	q;
};

struct ST_SIZE
{
	float fWidth;
	float fHeight;

	ST_SIZE() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZE(float w, float h) : fWidth(w), fHeight(h) {}
};

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
	std::vector<D3DMATERIAL9>		vecMaterial;

	DWORD							dwNumSubset;			
	LPD3DXMESH						pOrigMesh;				//원본메쉬
	D3DXMATRIX**					ppBoneMatrixPtrs;		//이 메쉬에 영향을 주는 프레임'들'의 월드매트릭스 포인터 계열
	D3DXMATRIX*						pBoneOffsetMatrices;	//원본 메수를 로컬스페이스로 보내는 매트릭스들
	D3DXMATRIX*						pCurrentBoneMatrices;	//각 본의 계산된 월드매트릭스
};
