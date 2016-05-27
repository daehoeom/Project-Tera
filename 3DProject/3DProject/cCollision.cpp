#include "stdafx.h"
#include "cCollision.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"


cCollision::cCollision()
{
}


cCollision::~cCollision()
{
}

bool cCollision::IsSphereToSphere(cBoundingSphere& s1, cBoundingSphere& s2)
{
	bool result = false;

	D3DXVECTOR3 dv = s1.GetPosition() - s2.GetPosition();
	float d = D3DXVec3LengthSq(&dv);
	float rSum = (s1.GetRadius() + s2.GetRadius()) * (s1.GetRadius() + s2.GetRadius());

	if (d <= rSum)
	{
		result = true;
	}

	return result;
}

bool cCollision::IsBoxToSphere(cBoundingBox& box, cBoundingSphere& s)
{
	float distance = 0.f;
	float diff = 0.f;

	if (s.GetPosition().x < box.GetMinimum().x)
	{
		diff = box.GetMinimum().x - s.GetPosition().x;
		distance += (diff * diff);
	}

	else if (s.GetPosition().x > box.GetMaximum().x)
	{
		diff = s.GetPosition().x - box.GetMaximum().x;
		distance += (diff * diff);
	}

	if (s.GetPosition().y < box.GetMinimum().y)
	{
		diff = box.GetMinimum().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	else if (s.GetPosition().y > box.GetMaximum().y)
	{
		diff = s.GetPosition().y - box.GetMaximum().y;
		distance += (diff * diff);
	}

	if (s.GetPosition().z < box.GetMinimum().z)
	{
		diff = box.GetMinimum().z - s.GetPosition().z;
		distance += (diff * diff);
	}

	else if (s.GetPosition().z > box.GetMaximum().z)
	{
		diff = s.GetPosition().z - box.GetMaximum().z;
		distance += (diff * diff);
	}

	bool result = true;

	if (distance > (s.GetRadius() * s.GetRadius()))
	{
		return false;
	}
}

bool cCollision::IsBoxToBox(cBoundingBox& box1, cBoundingBox& box2)
{
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
