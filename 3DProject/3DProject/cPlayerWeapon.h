#pragma once


class IWeapon :
	public cCollisionObject
{
public:
	IWeapon( const std::string& objName, cGameObject* owner ) :
		m_owner( owner ),
		cCollisionObject( objName )
	{
	}
	virtual ~IWeapon( )
	{
	}

	// TODO:
	// 공격력
	// 플레이어 생명력
	// 방어력..

public:
	void SetOwner( cGameObject* owner )
	{
		m_owner = owner;
	}
	cGameObject* GetOwner( )
	{
		return m_owner;
	}

private:
	cGameObject* m_owner;
};

class cPlayerWeapon :
	public IWeapon
{
public:
	cPlayerWeapon( const D3DXVECTOR3& vPos, 
				   const D3DXMATRIXA16& matLocal,
				   cGameObject* owner );
	virtual ~cPlayerWeapon( );

	virtual void OnCollisionEnter( int colliderIndex, cCollisionObject* rhs ) override;
	virtual void OnCollisionStay( int colliderIndex, cCollisionObject* rhs ) override;
	virtual void OnCollisionEnd( int colliderIndex, cCollisionObject* rhs ) override;
};

