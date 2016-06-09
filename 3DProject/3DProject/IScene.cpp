#include "stdafx.h"
#include "IScene.h"

#include "TXMLReader.h"
#include "ObjObject.h"
#include "cBoundingBox.h"

IScene::IScene( const std::string& xmlPath )
{
	this->ReadXML( xmlPath );
}

IScene::~IScene( )
{
}

void IScene::ReadXML( const std::string& xmlPath )
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
		
	cGameObject* newObject = nullptr;
	std::string objName;
	D3DXVECTOR3 pos{0,0,0}, rot{0,0,0}, scale{0,0,0};
	ICollider* collider = nullptr;
	//ObjectIdenfier objID = ObjectIdenfier::kUnknown;
	std::string modelPath;

	for ( const auto& xmlNodeElem : xmlReader )
	{
		if ( !strcmp( "End", xmlNodeElem->Value( )))
		{
			//switch ( objID )
			//{
			//case ObjectIdenfier::kObj:
			//	++m_createCount;
				newObject = new ObjObject( objName, modelPath, collider );
			//	break;
			//case ObjectIdenfier::kX:
			//	break;
			//}
				
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
		/*else if ( !strcmp( "Type", xmlNodeElem->Value( )))
		{
			if ( !strcmp( xmlNodeElem->FirstChild( )->Value(), 
				"obj" ))
			{
				objID = ObjectIdenfier::kObj;
			}
			else if ( !strcmp( xmlNodeElem->FirstChild( )->Value(),
				"x" ))
			{
				objID = ObjectIdenfier::kX;
			}
		}*/
		else if ( !strcmp( "ModelPath", xmlNodeElem->Value( ) ) )
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
					{ minXAttr->FloatValue( ), 
					  minYAttr->FloatValue( ), 
					  minZAttr->FloatValue( )}, 
					{ maxXAttr->FloatValue( ), 
					  maxYAttr->FloatValue( ), 
					  maxZAttr->FloatValue( )});
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
		else if ( !strcmp( "Rotation", xmlNodeElem->Value( ) ) )
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
