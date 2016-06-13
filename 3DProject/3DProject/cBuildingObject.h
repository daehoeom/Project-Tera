#pragma once

class cGroup;
class cBuildingObject :
	public cCollisionObject
{
public:
	explicit cBuildingObject( const std::string& name,
							  const std::string& objFilePath );
	virtual ~cBuildingObject( );

public:
	virtual void Render( ) override;
	virtual void Update( ) override;

	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs );
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs );

private:
	std::vector<cGroup*> m_groupRepo;
};

