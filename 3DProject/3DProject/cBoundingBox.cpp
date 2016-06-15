#include "stdafx.h"
#include "cBoundingBox.h"
#include "cGameObject.h"
#include "Console.h"

cBoundingBox::cBoundingBox(
	const D3DXVECTOR3& vMin,
	const D3DXVECTOR3& vMax ) : 

	m_bWireDraw(false),
	m_vMin( vMin ),
	m_vMax( vMax ),
	m_vertices( 8 ),
	m_indices( 36 )
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);

	this->SetupVertexAndIndex( );
}

cBoundingBox::~cBoundingBox()
{
}

void cBoundingBox::Update( )
{
	//m_matWorldTM = m_matLocalTM * m_matWorldTM;

	//m_vMin = D3DXVECTOR3( m_matWorldTM._41, m_matWorldTM._42, m_matWorldTM._43 );
	//m_vMax = m_vMin + m_vChange;
}

void cBoundingBox::Render()
{
	if ( m_isDebugRender )
	{
		this->PreRender( );
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			8,
			12,
			&m_indices[0],
			D3DFORMAT::D3DFMT_INDEX32,
			&m_vertices[0],
			sizeof( ST_PC_VERTEX )
		);

		this->PostRender( );
	}
}

void cBoundingBox::SetupVertexAndIndex( )
{	
	const DWORD m_color = 0xffffff;
	const float m_interval = 0.1f;

	// vertices of a unit cube
	m_vertices[0] = {{ m_vMin.x-m_interval, m_vMin.y-m_interval, m_vMin.z-m_interval}, m_color };
	m_vertices[1] = {{ m_vMin.x-m_interval, m_vMax.y+m_interval, m_vMin.z-m_interval}, m_color };
	m_vertices[2] = {{ m_vMax.x+m_interval, m_vMax.y+m_interval, m_vMin.z-m_interval}, m_color };
	m_vertices[3] = {{ m_vMax.x+m_interval, m_vMin.y-m_interval, m_vMin.z-m_interval}, m_color };
	m_vertices[4] = {{ m_vMin.x-m_interval, m_vMin.y-m_interval, m_vMax.z+m_interval}, m_color };
	m_vertices[5] = {{ m_vMin.x-m_interval, m_vMax.y+m_interval, m_vMax.z+m_interval}, m_color };
	m_vertices[6] = {{ m_vMax.x+m_interval, m_vMax.y+m_interval, m_vMax.z+m_interval}, m_color };
	m_vertices[7] = {{ m_vMax.x+m_interval, m_vMin.y-m_interval, m_vMax.z+m_interval}, m_color };

	// front side
	m_indices[0] = 0; m_indices[1] = 1; m_indices[2] = 2;
	m_indices[3] = 0; m_indices[4] = 2; m_indices[5] = 3;
	// back side
	m_indices[6] = 4; m_indices[7] = 6; m_indices[8] = 5;
	m_indices[9] = 4; m_indices[10] = 7; m_indices[11] = 6;
	// left side
	m_indices[12] = 4; m_indices[13] = 5; m_indices[14] = 1;
	m_indices[15] = 4; m_indices[16] = 1; m_indices[17] = 0;
	// right side
	m_indices[18] = 3; m_indices[19] = 2; m_indices[20] = 6;
	m_indices[21] = 3; m_indices[22] = 6; m_indices[23] = 7;
	// top
	m_indices[24] = 1; m_indices[25] = 5; m_indices[26] = 6;
	m_indices[27] = 1; m_indices[28] = 6; m_indices[29] = 2;
	// bottom
	m_indices[30] = 4; m_indices[31] = 0; m_indices[32] = 3;
	m_indices[33] = 4; m_indices[34] = 3; m_indices[35] = 7;
}