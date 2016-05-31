#include "stdafx.h"
#include "cCollision.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

#include "cGameObject.h"


bool cCollision::IsSphereToSphere(
	const cBoundingSphere& s1, 
	const cBoundingSphere& s2)
{
	bool result = false;

	D3DXVECTOR3 dv = s1.GetOwner( )->GetPosition() - s2.GetOwner( )->GetPosition();
	float dist = D3DXVec3LengthSq( &dv );

	float rSum = (s1.GetRadius() + s2.GetRadius()) * 
				 (s1.GetRadius() + s2.GetRadius());

	if (dist <= rSum)
	{
		result = true;
	}

	return result;
}

bool cCollision::IsSphereToBox(
	const cBoundingSphere& s,
	const cBoundingBox& box )
{
	float distance = 0.f;
	float diff = 0.f;

	if (s.GetOwner( )->GetPosition().x < box.GetMinimum().x)
	{
		diff = box.GetMinimum().x - s.GetOwner( )->GetPosition().x;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().x > box.GetMaximum().x)
	{
		diff = s.GetOwner( )->GetPosition().x - box.GetMaximum().x;
		distance += (diff * diff);
	}

	if (s.GetOwner( )->GetPosition().y < box.GetMinimum().y)
	{
		diff = box.GetMinimum().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().y > box.GetMaximum().y)
	{
		diff = s.GetOwner( )->GetPosition().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	if (s.GetOwner( )->GetPosition().z < box.GetMinimum().z)
	{
		diff = box.GetMinimum().z - s.GetOwner( )->GetPosition().z;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().z > box.GetMaximum().z)
	{
		diff = s.GetOwner( )->GetPosition().z - box.GetMaximum().z;
		distance += (diff * diff);
	}

	bool result = true;

	if (distance > (s.GetRadius() * s.GetRadius()))
	{
		return false;
	}
}

bool cCollision::IsBoxToSphere(
	const cBoundingBox& box, 
	const cBoundingSphere& s)
{
	float distance = 0.f;
	float diff = 0.f;

	if (s.GetOwner( )->GetPosition().x < box.GetMinimum().x)
	{
		diff = box.GetMinimum().x - s.GetOwner( )->GetPosition().x;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().x > box.GetMaximum().x)
	{
		diff = s.GetOwner( )->GetPosition().x - box.GetMaximum().x;
		distance += (diff * diff);
	}

	if (s.GetOwner( )->GetPosition().y < box.GetMinimum().y)
	{
		diff = box.GetMinimum().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().y > box.GetMaximum().y)
	{
		diff = s.GetOwner( )->GetPosition().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	if (s.GetOwner( )->GetPosition().z < box.GetMinimum().z)
	{
		diff = box.GetMinimum().z - s.GetOwner( )->GetPosition().z;
		distance += (diff * diff);
	}

	else if (s.GetOwner( )->GetPosition().z > box.GetMaximum().z)
	{
		diff = s.GetOwner( )->GetPosition().z - box.GetMaximum().z;
		distance += (diff * diff);
	}

	bool result = true;

	if (distance > (s.GetRadius() * s.GetRadius()))
	{
		return false;
	}
}

bool cCollision::IsBoxToBox(
	const cBoundingBox& box1, 
	const cBoundingBox& box2)
{
	box1.GetOwner( );


	if (box1.GetMaximum().x < box2.GetMinimum().x ||
		box1.GetMinimum().x > box2.GetMaximum().x)
		return false;

	if (box1.GetMaximum().y < box2.GetMinimum().y ||
		box1.GetMinimum().y > box2.GetMaximum().y)
		return false;

	if (box1.GetMaximum().z < box2.GetMinimum().z ||
		box1.GetMinimum().z > box2.GetMaximum().z)
		return false;

	return true;
}
