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


TestScene::TestScene( 
	const std::string& xmlPath )
{
	cGameObjectManager::Get( )->AddObject(
		"Monster1", new cArgoniteKallashGuardLeader 
	);

	auto* monster2 = cGameObjectManager::Get( )->AddObject( 
		"Monster2", new cArgoniteKallashGuardLeader 
	);
	monster2->SetPosition({ 0.f, 0.f, -150.f });

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup( );
	/*D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	m_pLoader = new cObjLoader;
	m_pLoader->Load("./Map/Height.obj", m_vecGroup, &mat);*/

	this->ReadXML( xmlPath );
}

TestScene::~TestScene( )
{
	SAFE_DELETE( m_pSkyBox );

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

	if ( m_pSkyBox )
	{
		m_pSkyBox->Render( );
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

	if ( m_pSkyBox )
	{
		m_pSkyBox->Update( );
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

			// Reset Items
			newObject = nullptr;
			collider = nullptr;
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

				collider = new cBoundingBox(
					{ -100.f ,
					  -100.f ,
					  -100.f },
					{ 100.f,
					  100.f,
					  100.f});
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
