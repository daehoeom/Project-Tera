#include "stdafx.h"
#include "cCollisionManager.h"
#include "cCollision.h"
#include "cBoundingBox.h"
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
		// elemOp1 Has no collider?
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
			for ( auto& op1Collider : elemOp1.second->GetColliderRepo( ))
			{
				for ( auto& op2Collider : elemOp2.second->GetColliderRepo( ) )
				{
					eColliderType op1CollType =
						op1Collider->GetColliderType( );
					eColliderType op2CollType =
						op2Collider->GetColliderType( );

					bool isCollised = false;

					// TODO : Optimize here
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
					}

					if ( isCollised )
					{
						elemOp1.second->OnCollisionStay( elemOp2.second );
					}

					else if (!isCollised)
					{
						elemOp1.second->OnNotCollision(elemOp2.second);
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
