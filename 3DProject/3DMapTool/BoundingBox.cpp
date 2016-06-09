#include "stdafx.h"
#include "BoundingBox.h"

#include "cDeviceManager.h"


BoundingBox::BoundingBox( 
	const D3DXVECTOR3& min, 
	const D3DXVECTOR3& max ):
	m_min( min ),
	m_max( max ),
	m_vertices( 8 ),
	m_indices( 36 )
{
	DWORD color = 0xffffff;
	const float interval = 0.1f;

	// vertices of a unit cube
	m_vertices[0] = {{ min.x-interval, min.y-interval, min.z-interval}, color };
	m_vertices[1] = {{ min.x-interval, max.y+interval, min.z-interval}, color };
	m_vertices[2] = {{ max.x+interval, max.y+interval, min.z-interval}, color };
	m_vertices[3] = {{ max.x+interval, min.y-interval, min.z-interval}, color };
	m_vertices[4] = {{ min.x-interval, min.y-interval, max.z+interval}, color };
	m_vertices[5] = {{ min.x-interval, max.y+interval, max.z+interval}, color };
	m_vertices[6] = {{ max.x+interval, max.y+interval, max.z+interval}, color };
	m_vertices[7] = {{ max.x+interval, min.y-interval, max.z+interval}, color };

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

BoundingBox::~BoundingBox( )
{
}

void BoundingBox::Update( )
{
}

void BoundingBox::Render( )
{
	g_pD3DDevice->SetTexture( 0, nullptr );
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	g_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME );
	g_pD3DDevice->SetFVF( ST_PC_VERTEX::FVF );

	g_pD3DDevice->DrawIndexedPrimitiveUP(
		D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
		0,
		8,
		12,
		&m_indices[0],
		D3DFORMAT::D3DFMT_INDEX32,
		&m_vertices[0],
		sizeof( ST_PC_VERTEX )
	);

	g_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID );
	g_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}