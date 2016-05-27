#pragma once

class cBoundingBox;
class cBoundingSphere;

class cCollision
{
public:
	cCollision();
	~cCollision();

	static bool IsSphereToSphere(
		cBoundingSphere& s1, cBoundingSphere& s2);

	static bool IsBoxToSphere(
		cBoundingBox& box, cBoundingSphere& s);

	static bool IsBoxToBox(
		cBoundingBox& box1, cBoundingBox& box2);
};

