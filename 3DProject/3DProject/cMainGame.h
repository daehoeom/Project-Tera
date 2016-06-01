#pragma once
#include "cBoundingBox.h"
#include "cCollisionObject.h"
#include "cBoundingSphere.h"


class cA :
	public cCollisionObject
{
public:
	cA( ) : 
		cCollisionObject( "cA" )
	{
		this->SetCollider(new cBoundingBox(this, { -5, -5, -5 }, { 5, 5, 5 }));
	}

	virtual ~cA( )
	{
	}

	virtual void OnCollisionStay( cCollisionObject* rhs ) override
	{
		rhs->Move( { 1.f, 0.f, 0.f } );
	}

	virtual void Update( ) override
	{
		__super::Update( );

		if ( cKeyManager::Get( )->isStayKeyDown( 'W' ) )
		{
			D3DXVECTOR3 dirVec( 0, 0, 1 );
			D3DXMATRIXA16 matRotY;
			D3DXMatrixRotationY( &matRotY, this->GetAngle( ).y );
			D3DXVec3TransformNormal( &dirVec, &dirVec, &matRotY );
			this->Move( dirVec );
		}

		if ( cKeyManager::Get()->isStayKeyDown( VK_LEFT ) )
		{
			this->Rotate( { 0, -0.1f, 0 } );
		}

		if ( cKeyManager::Get( )->isStayKeyDown( VK_RIGHT ) )
		{
			this->Rotate( { 0, +0.1f, 0 } );
		}
	}
};

class cB :
	public cCollisionObject
{
public:
	cB( ) : cCollisionObject( "cB" )
	{
		this->SetCollider( new cBoundingSphere( this, 10 ) );
	}
	virtual ~cB( )
	{

	}
};


class cPlayer;
class cGrid;
class cSkyBox;
class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void SetupManagers( );

private:
	cPlayer* m_player;
	cGrid* m_pGrid;
	cSkyBox* m_pSkyBox;
	
	cA a;
	std::vector<cB*> b;
};

