#pragma once
#include "cGameObject.h"

class TerrainObject : public cGameObject
{
public:
	TerrainObject(
		const std::wstring& objName,
		int row,
		int col,
		float interval,
		_In_ const char* rowPath,
		_In_ const char* texPath
	);
	virtual ~TerrainObject( );

	virtual void Update( ) override;
	virtual void Render( ) override;

public:
	int GetCol( ) const { return m_col; }
	int GetRow( ) const { return m_row; }
	int GetInterval( ) const { return m_interval; }
	const auto& GetHeightRepo( ) const { return m_heightRepo; }
	const auto& GetVertexRepo( ) const { return m_vertexRepo; }

private:
	void InitMesh( );

	void InitVertexBuffer(
		int row,
		int col,
		float interval,
		const std::vector<float>& heightInfo
	);

	void InitIndexBuffer(
		int row,
		int col,
		float interval
	);

	void InitTexture( const char* texPath );

private:
	const int m_numSubset;
	const int m_col;
	const int m_row;
	const float m_interval;
	const int m_numVertices;
	const int m_numTriangles;
	ID3DXMesh* m_mesh;
	IDirect3DTexture9* m_texture;
	std::vector<ST_PNT_VERTEX> m_vertexRepo;
	std::vector<float> m_heightRepo;
};
//
//inline float CalculateHeight(
//	_In_ const Terrain& terrain,
//	_In_ const GameObject& object )
//{
//	float xCell, zCell;
//	MoveControlPointerToZero( terrain, object, &xCell, &zCell );
//               
//
//	//	v0----v1
//	//	|	   |
//	//	|	   |
//	//	v2----v3
//	const auto& v0 = terrain.GetVertexRepo()[zCell*terrain.GetCol( )+xCell].p;
//	const auto& v1 = terrain.GetVertexRepo()[zCell*terrain.GetCol( )+(xCell+1)].p;
//	const auto& v2 = terrain.GetVertexRepo()[(zCell+1)*terrain.GetCol( )+xCell].p;
//	const auto& v3 = terrain.GetVertexRepo()[(zCell+1)*terrain.GetCol( )+(xCell+1)].p;
//
//	float dx = std::abs( object.GetPosition( ).x - v0.x );
//	float dz = std::abs( object.GetPosition( ).z - v0.z );
//
//	float height = 0.f;
//	bool isUpTriangle = dz + dx < 1.f;
//	if ( isUpTriangle )
//	{
//		//	v0--A--v1
//		//	|		|
//		//	B		|
//		//	|	    |
//		//	v2-----v3
//
//
//		float A = v1.y-v0.y;
//		float B = v2.y-v0.y;
//
//		float uy = Lerp( 0.f, A, dx );
//		float vy = Lerp( 0.f, B, dz );
//
//		height = v0.y + uy + vy;
//	}
//	else
//	{
//		//	v0-----v1
//		//	|		|
//		//	|		D
//		//	|	    |
//		//	v2--C--v3
//
//		float C = v2.y-v3.y;
//		float D = v1.y-v3.y;
//
//		float uy = Lerp( 0.f, C, 1.f-dx );
//		float vy = Lerp( 0.f, D, 1.f-dz );
//
//		height = v3.y + uy + vy;
//	}
//
//	return height;
//}
