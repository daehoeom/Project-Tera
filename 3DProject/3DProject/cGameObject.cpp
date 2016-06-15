#include "stdafx.h"
#include "cGameObject.h"

#include "cGameObjectManager.h"
#include "ICollider.h"


cGameObject::cGameObject( ) :
	m_isActive( true ),
	m_pos( 0.f, 0.f, 0.f ),
	m_angle( 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_matWorld );
}

cGameObject::~cGameObject( )
{
}

void cGameObject::Render( )
{
}

void cGameObject::Update( )
{
}

void cGameObject::SetName(
	const std::string& newObjName )
{
	// 처음으로 생성된 object가 아닌 경우
	if ( !m_objName.empty( ))
	{
		// 기존 오브젝트 맵의 key를 새로운 key로 변경하는 
		// 처리가 추가됩니다.

		cGameObject* object = 
			cGameObjectManager::Get( )->FindObject( m_objName );
		if ( object )
		{
			// 기존의 key를 erase한 뒤
			cGameObjectManager::Get( )->EraseObject( 
				m_objName );

			// 새로운 key로 object를 등록합니다.
			cGameObjectManager::Get( )->AddObject(
				newObjName, this
			);
		}
	}

	m_objName = newObjName;
}