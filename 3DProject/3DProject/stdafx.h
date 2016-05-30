// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C runtime headers are here

// C++ runtime headers are here
#include <memory>
#include <cstdint>
#include <cassert>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <initializer_list>
#include <array>

// Platform dependent headers are here
#include <d3dx9.h>
#include <tchar.h>

#define EPSILON 0.0001f
#define SAFE_RELEASE(p) {if (p) { (p)->Release(); (p) = NULL; }}
#define SAFE_ADD_REF(p) {if (p) { (p)->AddRef(); }}
#define SAFE_DELETE(p) {if (p) { delete (p); (p) = NULL; }}
#define SAFE_DELETE_ARRAY(p) {if (p) { delete [] (p); (p) = NULL; }}

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


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

struct ST_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;
	bool		isPicked;
};

struct ST_SIZE
{
	float fWidth;
	float fHeight;

	ST_SIZE() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZE(float w, float h) : fWidth(w), fHeight(h) {}
};

extern HWND		g_hWnd;

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

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

#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cObjectManager.h"
#include "cKeyManager.h"
#include "cSkinnedMeshManager.h"
#include "Particle.h"
#include "cCamera.h"
#include "cRandomUtil.h"
