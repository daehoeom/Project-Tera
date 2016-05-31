#pragma once

class cBoundingBox;
class cBoundingSphere;

class cCollision
{
public:
	cCollision() = delete;
	~cCollision() = delete;

	static bool IsSphereToSphere(
		const cBoundingSphere& s1, 
		const cBoundingSphere& s2);

	static bool IsBoxToSphere(
		const cBoundingBox& box, 
		const cBoundingSphere& s);

	static bool IsSphereToBox(
		const cBoundingSphere& s,
		const cBoundingBox& box );


	static bool IsBoxToBox(
		const cBoundingBox& box1, 
		const cBoundingBox& box2);
};

