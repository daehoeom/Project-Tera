#include "stdafx.h"
#include "cCollisionManager.h"
#include "cCollision.h"
#include "cBoundingBox.h"
#include "Console.h"
#include "cBoundingSphere.h"
#include "ICollider.h"
#include "cCollisionObject.h"


cCollisionManager::cCollisionManager( )
{
}

cCollisionManager::~cCollisionManager( )
{
}

void cCollisionManager::Update( )
{
	for ( auto& elemOp1 : m_collisionMap )
	{
		if ( elemOp1.second->GetColliderRepo( ).size( ) == 0 )
		{
			continue;
		}
		
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
			// op1Collider가 elemOp2가 가진 콜라이더들( op2Collider )와 충돌했는지 알아내자.
			bool isCollisedAtLeastOnce = false;
			for ( int op1ColliderIndex = 0; 
				op1ColliderIndex < elemOp1.second->GetColliderRepo( ).size( );
				  ++op1ColliderIndex )
			{
				// op1 콜라이더 선택
				auto& op1Collider = elemOp1.second->GetColliderRepo()[op1ColliderIndex];
				
				for ( int op2ColliderIndex = 0;
					op2ColliderIndex < elemOp2.second->GetColliderRepo().size( );
					++op2ColliderIndex )
				{
					// op2 콜라이더 선택
					auto& op2Collider = 
						elemOp2.second->GetColliderRepo( )[op2ColliderIndex];

					eColliderType op1CollType =
						op1Collider->GetColliderType( );
					eColliderType op2CollType =
						op2Collider->GetColliderType( );

					bool isCollised = false;

					// TODO : Optimize here
					// 타입에 맞게 충돌 체크를 시작한다.
					if ( op1CollType == eColliderType::kBox &&
						op2CollType == eColliderType::kBox )
					{
						isCollised = cCollision::IsBoxToBox(
							static_cast<const cBoundingBox&>(
								*op1Collider ),
							static_cast<const cBoundingBox&>(
								*op2Collider )
						);
					}
					else if ( op1CollType == eColliderType::kSphere &&
						op2CollType == eColliderType::kSphere )
					{
						isCollised = cCollision::IsSphereToSphere(
							static_cast<const cBoundingSphere&>(
								*op1Collider ),
							static_cast<const cBoundingSphere&>(
								*op2Collider )
						);
					}
					else if ( op1CollType == eColliderType::kBox &&
						op2CollType == eColliderType::kSphere )
					{
						isCollised = cCollision::IsBoxToSphere(
							static_cast<const cBoundingBox&>(
								*op1Collider ),
							static_cast<const cBoundingSphere&>(
								*op2Collider )
						);
					}
					else if ( op1CollType == eColliderType::kSphere &&
						op2CollType == eColliderType::kBox )
					{
						isCollised = cCollision::IsBoxToSphere(
							static_cast<const cBoundingBox&>(
								*op1Collider ),
							static_cast<const cBoundingSphere&>(
								*op2Collider )
						);

						if ( isCollised )
						{
							int n = 3;
						}
					}

					// A,B 두 물체가 충돌했는가?
					if ( isCollised )
					{
						isCollisedAtLeastOnce = true;
						break;
					}
				}


				// 그럼 이제 op1이 모든 충돌체에 대해서 하나라도 충돌중인지
				// 아닌지에 대한 플래그가 남는다. ( isCollisedAtLeastOnce )
				// op1Collider가 elemOp2의 콜라이더들 중 하나라도 충돌중인가?
				if ( isCollisedAtLeastOnce )
				{
					// A 충돌체가 과거 collised 상태가 아니었는가?
					if ( !elemOp1.second->GetCollision( op1ColliderIndex ))
					{
						if ( elemOp1.second->GetName( ) == "Player" )
						{
							int n = 3;
						}

						// A를 충돌상태로 전환하자.
						elemOp1.second->SetCollision( op1ColliderIndex, true );
						// 그럼 A의 충돌 시작 함수를 호출한다.
						elemOp1.second->OnCollisionEnter( op1ColliderIndex, elemOp2.second );
					}
					// A에게 과거 충돌 사례가 있었는데 지금도 충돌중이다
					else
					{
						if ( elemOp1.second->GetName( ) == "Player" )
						{
							int n = 3;
						}

						elemOp1.second->OnCollisionStay( op1ColliderIndex,
							elemOp2.second );
					}

				}
				// A,B 두 물체가 충돌하지 않았는가?
				else
				{
					// A 충돌체가 과거 collised 상태였는가?
					if ( elemOp1.second->GetCollision( op1ColliderIndex ) )
					{
						if ( elemOp1.second->GetName( ) == "Player" )
						{
							int n = 3;
						}

						// A를 충돌끝난상태로 전환하자.
						elemOp1.second->SetCollision( op1ColliderIndex,
							false );
						// 그럼 A의 충돌 시작 함수를 호출한다.
						elemOp1.second->OnCollisionEnd( op1ColliderIndex,
							elemOp2.second );
					}
				}

			}
		}
	
	}
}

void cCollisionManager::AddObject(
	cCollisionObject* target )
{
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
	const uintptr_t key =
		reinterpret_cast<uintptr_t>( target );
	m_collisionMap.erase( key );
}
