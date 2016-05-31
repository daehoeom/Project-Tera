// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows dependent 헤더 파일:
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>

// C++ 런타임 헤더 파일입니다.
#include <cstdlib>
#include <memory>
#include <string>
#include <map>
#include <initializer_list>
#include <array>
#include <cstdint>
#include <vector>
#include <cassert>

#pragma comment( lib, "d3d9.lib")
#ifdef _DEBUG
#	pragma comment( lib, "d3dx9d.lib")
#else
#	pragma comment( lib, "d3dx9.lib")
#endif


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

enum
{
	MainWindowX = 0, // Not used ( because of middle showing )
	MainWindowY = 0, // Not used ( because of middle showing )
	MainWindowWidth = 800,
	MainWindowHeight = 800,

	HierarchyWindowX = MainWindowWidth, // Follow parent's
	HierarchyWindowY = MainWindowY, // Follow parent's
	HierarchyWindowWidth = HierarchyWindowX+200,
	HierarchyWindowHeight = HierarchyWindowY+(MainWindowHeight/2),	// Follow parent's

	InspectorWindowX = 0,
	InspectorWindowY = 0,
	InspectorWindowWidth = 0,
	InspectorWindowHeight = 0,
};


#define MAINWINDOW_TITLENAME L"3DMapTool"
#define HIERARCHYWINDOW_TITLENAME L"Hierarchy"
#define INSPECTORWINDOW_TITLENAME L"Inspector"


extern HINSTANCE g_instHandle;
extern HWND g_mainWndHandle;		// D3DX Surface window & Menu bar
extern HWND g_hierarchyWndHandle;	// Contains object hierarchy listbox
extern HWND g_inspectorWndHandle;