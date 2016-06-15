#include "stdafx.h"
#include "TestScene.h"
#include "TXMLReader.h"
#include "cBuildingObject.h"
#include "cBoundingBox.h"	
#include "cPlayer.h"
#include "cBoundingBox.h"
#include "cGameObjectManager.h"
#include "cGroup.h"
#include "cNpcManager.h"
#include "cSkyBox.h"
#include "cArgoniteKallashGuardLeader.h"
#include "cGrid.h"

TestScene::TestScene( 
	const std::string& xmlPath )
{
	/*cGameObjectManager::Get( )->AddObject(
		"Monster1", new cArgoniteKallashGuardLeader 
	);
*/
	//auto* monster2 = cGameObjectManager::Get( )->AddObject( 
	//	"Monster2", new cArgoniteKallashGuardLeader 
	//);
	//monster2->SetPosition({ 0.f, 0.f, -150.f });

	cGameObjectManager::Get( )->AddObject(
		"SkyBox", new cSkyBox
	);

	/*cGameObjectManager::Get()->AddObject(
		"Grid", new cGrid
		);
*/
	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/

	//this->ReadXML( xmlPath );
}

TestScene::~TestScene( )
{
	for ( auto buildObj : m_buildingObjectRepo )
	{
		SAFE_DELETE( buildObj );
	}
}

void TestScene::Render( )
{
	//플레이어 렌더
	if (g_player)
	{
		g_player->Render();
	}

	// 건물 렌더
	for ( auto elem : m_buildingObjectRepo )
	{
		elem->Render( );
	}
}

void TestScene::Update( )
{
	if ( g_player )
	{
		g_player->Update( );
	}

	// 건물 업뎃
	for ( auto elem : m_buildingObjectRepo )
	{
		elem->Update( );
	}
}

void TestScene::ReadXML( const std::string& xmlPath )
{
	// Begin reading XML
	tgon::TXMLReader xmlReader( xmlPath.c_str( ));
	if ( xmlReader.fail( ))
	{
		MessageBox( GetFocus( ),
			"XML 로딩에 실패했습니다.",
			"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}
		
	ICollider* collider = nullptr;
	std::string objName;
	std::string modelPath;
	D3DXVECTOR3 pos{ 0,0,0 }, rot{ 0,0,0 }, scale{ 0,0,0 };

	for ( const auto& xmlNodeElem : xmlReader )
	{
		if ( !strcmp( "End", xmlNodeElem->Value( )))
		{
			//cGameObjectManager::AddObject( )

			cBuildingObject* newObject = new cBuildingObject( 
				modelPath );
			m_buildingObjectRepo.push_back( newObject );

			if ( collider )
			{
				newObject->AddCollider( collider );
			}
			newObject->SetPosition( pos );
			newObject->SetAngle( rot );
			newObject->SetScale( scale );
			newObject->SetName( objName );

			// Reset Items
			newObject = nullptr;
			collider = nullptr;
			objName.clear( );
			modelPath.clear( );
		}
		else if ( !strcmp( "ObjectName", xmlNodeElem->Value( )))
		{
			const char* objCharName = xmlNodeElem->FirstChild( )->Value( );
			objName = objCharName;
		}
		else if ( !strcmp( "ModelPath", xmlNodeElem->Value( )))
		{
			modelPath = xmlNodeElem->FirstChild( )
				->Value( );
		}
		else if ( !strcmp( "BoundingBox", xmlNodeElem->Value( )))
		{
			tinyxml2::XMLElement* elem = xmlNodeElem->ToElement( );
			if ( elem )
			{
				const tinyxml2::XMLAttribute* minXAttr =
					elem->FirstAttribute( );
				const tinyxml2::XMLAttribute* minYAttr =
					minXAttr->Next( );
				const tinyxml2::XMLAttribute* minZAttr =
					minYAttr->Next( );

				const tinyxml2::XMLAttribute* maxXAttr =
					minZAttr->Next( );
				const tinyxml2::XMLAttribute* maxYAttr =
					maxXAttr->Next( );
				const tinyxml2::XMLAttribute* maxZAttr =
					maxYAttr->Next( );

				D3DXMATRIXA16 matScale;
				D3DXMatrixScaling( &matScale, 
					scale.x, 
					scale.y, 
					scale.z );

				D3DXMATRIXA16 matRot, matRotX, matRotY, matRotZ;
				D3DXMatrixRotationX( &matRotX, rot.x );
				D3DXMatrixRotationY( &matRotY, rot.y );
				D3DXMatrixRotationZ( &matRotZ, rot.z );
				matRot = matRotX * matRotY * matRotZ;

				D3DXMATRIXA16 matTrans;
				D3DXMatrixTranslation( &matTrans, pos.x, pos.y, pos.z );

				D3DXMATRIXA16 matWorld = 
					matScale * matRot * matTrans;

				D3DXVECTOR3 min(
					minXAttr->FloatValue( ),
					minYAttr->FloatValue( ),
					minZAttr->FloatValue( )
				);
				D3DXVECTOR3 max(
					maxXAttr->FloatValue( ),
					maxYAttr->FloatValue( ),
					maxZAttr->FloatValue( )
				);
				
				D3DXVec3TransformCoord( &min, &min, &matWorld );
				D3DXVec3TransformCoord( &max, &max, &matWorld );

				collider = new cBoundingBox(
					{ min.x, 
					  min.y, 
					  min.z },
					{ max.x, 
					  max.y, 
					  max.z }
				);
			}
		}
		else if ( !strcmp( "Position", xmlNodeElem->Value( )))
		{
			tinyxml2::XMLElement* elem = xmlNodeElem->ToElement( );
			if ( elem )
			{
				const tinyxml2::XMLAttribute* xAttr = 
					elem->FirstAttribute( );
				const tinyxml2::XMLAttribute* yAttr = 
					xAttr->Next( );
				const tinyxml2::XMLAttribute* zAttr = 
					yAttr->Next( );

				pos = { xAttr->FloatValue( ),
					yAttr->FloatValue( ),
					zAttr->FloatValue( )
				};
			}
			else
			{
				MessageBox( GetFocus( ),
					"알 수 없는 Element 형식입니다.",
					"WARNING!",
					MB_OK | MB_ICONEXCLAMATION
				);
			}
		}
		else if ( !strcmp( "Rotation", xmlNodeElem->Value( )))
		{
			tinyxml2::XMLElement* elem = xmlNodeElem->ToElement( );
			if ( elem )
			{
				const tinyxml2::XMLAttribute* xAttr = 
					elem->FirstAttribute( );
				const tinyxml2::XMLAttribute* yAttr = 
					xAttr->Next( );
				const tinyxml2::XMLAttribute* zAttr = 
					yAttr->Next( );

				rot = { xAttr->FloatValue( ),
					yAttr->FloatValue( ),
					zAttr->FloatValue( )
				};
			}
			else
			{
				MessageBox( GetFocus( ),
					"알 수 없는 Element 형식입니다.",
					"WARNING!",
					MB_OK | MB_ICONEXCLAMATION
				);
			}
		}
		else if ( !strcmp( "Scale", xmlNodeElem->Value( )))
		{
			tinyxml2::XMLElement* elem = xmlNodeElem->ToElement( );
			if ( elem )
			{
				const tinyxml2::XMLAttribute* xAttr =
					elem->FirstAttribute( );
				const tinyxml2::XMLAttribute* yAttr =
					xAttr->Next( );
				const tinyxml2::XMLAttribute* zAttr =
					yAttr->Next( );

				scale = { xAttr->FloatValue( ),
					yAttr->FloatValue( ),
					zAttr->FloatValue( )
				};
			}
			else
			{
				MessageBox( GetFocus( ),
					"알 수 없는 Element 형식입니다.",
					"WARNING!",
					MB_OK | MB_ICONEXCLAMATION
				);
			}
		}
	}
}
