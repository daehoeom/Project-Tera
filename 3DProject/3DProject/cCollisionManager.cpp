#include "stdafx.h"
#include "cCollisionManager.h"
#include "cCollision.h"
#include "cBoundingBox.h"
#include "Console.h"
#include "cBoundingSphere.h"
#include "ICollider.h"
#include "cCollisionObject.h"


cCollisionManager::cCollisionManager( ) :
	m_isAutoUpdatable( false )
{
}

cCollisionManager::~cCollisionManager( )
{
}

void cCollisionManager::Update( )
{
	if ( !m_isAutoUpdatable )
	{
		return;
	}

	for ( auto& elemOp1 : m_collisionMap )
	{
		if ( elemOp1.second->GetColliderRepo( ).size( ) == 0 )
		{
			continue;
		}
		
		bool isCollisedAtLeastOnce = false;
		cCollisionObject* op1sCollidedObject = nullptr;

		for ( auto& elemOp2 : m_collisionMap )
		{
			// Compare target is same as elemOp1?
			// Or elemOp2 has no collider? 
			if ( elemOp1 == elemOp2 ||
				 elemOp2.second->GetColliderRepo( ).size( ) == 0 )
			{
				continue;
			}

			// Then, elemOp1 and elemOp2 is different with,
			// And both have colliders.
			// op1Collider가 elemOp2가 가진 콜라이더( op2Collider )와 충돌했는지 알아내자.
			// op1 콜라이더 선택
			auto& op1Collider = elemOp1.second->GetColliderRepo()
				[0];
			// op2 콜라이더 선택
			auto& op2Collider = 
				elemOp2.second->GetColliderRepo( )[0];

			eColliderType op1CollType =
				op1Collider->GetColliderType( );
			eColliderType op2CollType =
				op2Collider->GetColliderType( );

			bool isCollided = false;

			// TODO : Optimize here
			// 타입에 맞게 충돌 체크를 시작한다.
			if ( op1CollType == eColliderType::kBox &&
				op2CollType == eColliderType::kBox )
			{
				isCollided = cCollision::IsBoxToBox(
					static_cast<const cBoundingBox&>(
						*op1Collider ),
					static_cast<const cBoundingBox&>(
						*op2Collider )
				);
			}
			else if ( op1CollType == eColliderType::kSphere &&
				op2CollType == eColliderType::kSphere )
			{
				isCollided = cCollision::IsSphereToSphere(
					static_cast<const cBoundingSphere&>(
						*op1Collider ),
					static_cast<const cBoundingSphere&>(
						*op2Collider )
				);
			}
			else if ( op1CollType == eColliderType::kBox &&
				op2CollType == eColliderType::kSphere )
			{
				isCollided = cCollision::IsBoxToSphere(
					static_cast<const cBoundingBox&>(
						*op1Collider ),
					static_cast<const cBoundingSphere&>(
						*op2Collider )
				);
			}
			else if ( op1CollType == eColliderType::kSphere &&
				op2CollType == eColliderType::kBox )
			{
				isCollided = cCollision::IsSphereToBox(
					static_cast<const cBoundingSphere&>(
						*op1Collider ),
					static_cast<const cBoundingBox&>(
						*op2Collider )
				);
			}

			if ( isCollided )
			{
				isCollisedAtLeastOnce = true;
				op1sCollidedObject = elemOp2.second;
				break;
			}
		}

		// elemOp1과 elemOp2이 충돌중인가?
		if ( isCollisedAtLeastOnce )
		{
			// A 충돌체가 과거 collised 상태가 아니었는가?
			if ( !elemOp1.second->GetCollision( 0 ) )
			{
				// A를 충돌상태로 전환하자.
				elemOp1.second->SetCollision( 0, true );
				// 그럼 A의 충돌 시작 함수를 호출한다.
				elemOp1.second->OnCollisionEnter( 0, 
					op1sCollidedObject );
			}
			// A에게 과거 충돌 사례가 있었는데 지금도 충돌중이다
			else
			{
				elemOp1.second->OnCollisionStay( 0,
					op1sCollidedObject );
			}

		}
		// A,B 두 물체가 충돌하지 않았는가?
		else
		{
			// A 충돌체가 과거 collised 상태였는가?
			if ( elemOp1.second->GetCollision( 0 ) )
			{
				// A를 충돌끝난상태로 전환하자.
				elemOp1.second->SetCollision( 0,
					false );
				// 그럼 A의 충돌 시작 함수를 호출한다.
				elemOp1.second->OnCollisionEnd( 0,
					op1sCollidedObject );
			}
		}
	}
}

void cCollisionManager::AddObject(
	cCollisionObject* target )
{
	std::unique_lock<std::mutex> m_lock( m_mutex );

	const uintptr_t key =
		reinterpret_cast<uintptr_t>( target );

	auto iter = m_collisionMap.find( key );
	if ( iter == m_collisionMap.end( ) )
	{
		m_collisionMap[key] = target;
	}
}

void cCollisionManager::EraseObject( 
	cCollisionObject* target )
{
	if ( target )
	{
		const uintptr_t key =
			reinterpret_cast<uintptr_t>( target );
		
		m_collisionMap.erase( key );
	}
}

void cCollisionManager::ClearAllObject( )
{
	m_collisionMap.clear( );
}
