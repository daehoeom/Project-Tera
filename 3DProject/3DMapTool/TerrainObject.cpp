#include "stdafx.h"
#include "TerrainObject.h"

#include "IO.h"
#include "cDeviceManager.h"


TerrainObject::TerrainObject(
	const std::wstring& objName,
	int row, int col, float interval,
	_In_ const char* rowPath,
	_In_ const char* texPath ) :
	cGameObject( objName ),
	m_row( row ),
	m_col( col ),
	m_numSubset( 1 ),
	m_interval( interval ),
	m_numVertices( row*col ),
	m_numTriangles(( row-1 )*( col-1 )*2 ),
	m_heightRepo( ReadRAW( rowPath ))
{
	for ( int i = 0; i < m_heightRepo.size( ); ++i )
	{
		m_heightRepo[i] *= 0.2f;
	}

	this->InitMesh( );
	this->InitVertexBuffer( row, col, interval, m_heightRepo );
	this->InitIndexBuffer( row, col, interval );
	this->InitTexture( texPath );


}

TerrainObject::~TerrainObject( )
{
}

void TerrainObject::Update( float tickTime )
{
}

void TerrainObject::Render( )
{
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, TRUE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_FILLMODE, D3DFILL_SOLID );
	
	GetD3dDevice( )->SetTransform( D3DTS_WORLD, &this->GetWorld());
	
	for ( int i = 0; i < m_numSubset; i++ )
	{
		GetD3dDevice()->SetTexture( 0, this->GetTexture( i ));
		m_mesh->DrawSubset( i );
	}


	/*
	GetD3dDevice( )->SetTexture( 0, this->GetTexture( ));
	GetD3dDevice( )->SetFVF( ST_PNT_VERTEX::FVF );
	GetD3dDevice( )->SetStreamSource( 0, this->GetVertexBuffer( ), 0, sizeof( ST_PNT_VERTEX ));
	GetD3dDevice( )->SetIndices( this->GetIndexBuffer( ));

	GetD3dDevice( )->DrawIndexedPrimitive(
		D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
		0,
		0,
		m_numVertices,
		0,
		m_numTriangles
	);

	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_FILLMODE, D3DFILL_SOLID );
*/

}

void TerrainObject::InitMesh( )
{
	HRESULT hr = D3DXCreateMeshFVF(
		m_numTriangles,
		m_numVertices,
		D3DXMESH_DYNAMIC | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		GetD3dDevice( ),
		&m_mesh
	);

	if ( FAILED( hr ))
	{
		MessageBox(
			GetFocus( ),
			L"Failed to invoke D3DXCreateMeshFVF.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION 
		);
	}
}

void TerrainObject::InitVertexBuffer( int row, int col, float interval, const std::vector<float>& heightInfo )
{
	IDirect3DVertexBuffer9* vb = nullptr;
	m_mesh->GetVertexBuffer( &vb );
	
	this->SetVertexBuffer( vb );
	
	
	// Assemble
	ST_PNT_VERTEX* vertices = nullptr;
	m_mesh->LockVertexBuffer( 0, reinterpret_cast<void**>( &vertices ));

	m_vertexRepo.resize( m_numVertices );

	float startX = -( static_cast<float>( col-1 )/2.f ) * interval;
	float startZ = ( static_cast<float>( row-1 )/2.f ) * interval;

	int fillIndex = 0;
	for ( int z = 0 ; z < row; ++z )
	{
		for ( int x = 0; x < col; ++x )
		{
			const float u = x * ( 1.f/( col-1 ));
			const float v = z * ( 1.f/( row-1 ));


			// Vertex
			vertices[fillIndex].p = {
				startX + x*interval,
				heightInfo[z*col+x],
				startZ - z*interval
			};


			// Normal
			vertices[fillIndex].n = { 0.f, 1.f, 0.f };

			// TexCoord
			vertices[fillIndex].t = { u, v };

			++fillIndex;
		}
	}

	// Fill the normals
	int rowCell = this->GetRow( ) - 1;
	int colCell = this->GetCol( ) - 1;


	for ( int z = 1; z < rowCell; ++z )
	{
		for ( int x = 1; x < colCell; ++x )
		{
			// Left to right
			const auto& v1 = vertices[z*this->GetCol( )+(x-1)];
			const auto& v2 = vertices[z*this->GetCol( )+(x+1)];
			const auto A = ( v2.p - v1.p );
			
			// Down to up
			const auto& v3 = vertices[(z+1)*this->GetCol( )+x];
			const auto& v4 = vertices[(z-1)*this->GetCol( )+x];
			const auto B = ( v4.p - v3.p );


			D3DXVECTOR3 cross;
			D3DXVec3Cross( &cross, &A, &B );

			D3DXVECTOR3 crossNormal;
			D3DXVec3Normalize( &crossNormal, &cross );

			vertices[z*this->GetCol( )+x].n = crossNormal;
		}
	}


	memcpy( &m_vertexRepo[0], vertices, m_numVertices*sizeof( ST_PNT_VERTEX ));
	m_mesh->UnlockVertexBuffer( );
}

void TerrainObject::InitIndexBuffer( int row, int col, float interval )
{
	IDirect3DIndexBuffer9* ib = nullptr;
	m_mesh->GetIndexBuffer( &ib );
	
	this->SetIndexBuffer( ib );
	

	// Assemble
	DWORD* indices = nullptr;
	m_mesh->LockIndexBuffer( 0, reinterpret_cast<void**>( &indices ));

	int fillIndex = 0;
	for ( int z = 0; z < ( row-1 ); ++z )
	{
		for ( int x = 0; x < ( col-1 ); ++x )
		{
			indices[fillIndex++] = z*col+x;
			indices[fillIndex++] = z*col +( x+1 );
			indices[fillIndex++] = ( z+1 )*col + x;

			indices[fillIndex++] = ( z+1 )*col + x;
			indices[fillIndex++] = z*col +( x+1 );
			indices[fillIndex++] = ( z+1 )*col +( x+1 );
		}
	}

	m_mesh->UnlockIndexBuffer( );


	/*
		Attribute buffer
	*/
	DWORD* attributeBuffer = 0;
	m_mesh->LockAttributeBuffer( 0, &attributeBuffer );

	for ( int i = 0; i < m_numTriangles; i++ )
	{
		attributeBuffer[i] = 0;
	}

	m_mesh->UnlockAttributeBuffer( );


	// Adjency buffer
	std::vector<DWORD> adjacencyBuffer( m_mesh->GetNumFaces( ) * 3 );
	m_mesh->GenerateAdjacency( 0.0f, &adjacencyBuffer[0] );

	m_mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT,
		&adjacencyBuffer[0],
		0,
		0,
		0
	);
}

void TerrainObject::InitTexture( const char* texPath )
{
	IDirect3DTexture9* texture;
	HRESULT hr = D3DXCreateTextureFromFileA( GetD3dDevice( ),
		texPath, &texture );
	if ( FAILED( hr ))
	{
		MessageBox( GetFocus( ), L"Failed to invoke D3DXCreateTextureFromFile.", 
			L"WARNING!", MB_OK | MB_ICONEXCLAMATION );
	}

	this->SetTexture( texture );
}
