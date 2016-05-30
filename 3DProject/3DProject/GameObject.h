#pragma once
#include "IAction.h"
#include "ICollider.h"

class GameObject : 
	public IActionDelegate,
	public ICollisionDelegate
{
public:
	GameObject( const std::string& objName );
	virtual ~GameObject( );

	virtual void Update( );
	virtual void Render( );

public:
	/*
		Transform
	*/
	// Position
	void SetPosition( const D3DXVECTOR3& pos );
	void Move( const D3DXVECTOR3& pos );
	const D3DXVECTOR3& GetPosition( ) const;

	// Roatation
	void SetAngle( const D3DXVECTOR3& rot );
	void Rotate( const D3DXVECTOR3& rot );
	const D3DXVECTOR3& GetAngle( ) const;
	
	// Scale
	void SetScale( const D3DXVECTOR3& scale );
	void Scale( const D3DXVECTOR3& scale );
	const D3DXVECTOR3& GetScale( ) const;
	
	/*
		State & Component
	*/
	void SetActive( bool isActive );
	bool IsActive( ) const;
	
	// Collider
	void SetCollider( class ICollider* collider );
	const std::unique_ptr<ICollider>& GetCollider( );
	
	// Controller
	void SetController( class IController* controller );
	const std::unique_ptr<IController>& GetController( );

	// Action
	void SetAction( class IAction* action );
	template <typename T> T* GetAction( )
	{
		return reinterpret_cast<T*>( m_actionMap[T::GetIdentifierStatic()] );
	}
	
	const std::string& GetName( ) const;
	const D3DXMATRIXA16 GetWorld( ) const;

private:
	void UpdateWorld( );

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_angle;
	D3DXVECTOR3 m_scale;
	D3DXMATRIXA16 m_matWorld;
	std::string m_objName;
	std::unique_ptr<class ICollider> m_collider;
	std::unique_ptr<class IController> m_controller;
	bool m_isActive;
	std::map<std::uintptr_t, class IAction*> m_actionMap;
};

inline void GameObject::SetPosition( const D3DXVECTOR3& pos )
{
	m_pos = pos;
	m_matWorld._41 = pos.x;
	m_matWorld._42 = pos.y;
	m_matWorld._43 = pos.z;
}

inline void GameObject::Move( const D3DXVECTOR3& pos )
{
	m_pos += pos;
	m_matWorld._41 += pos.x;
	m_matWorld._42 += pos.y;
	m_matWorld._43 += pos.z;
}

inline void GameObject::SetAngle( const D3DXVECTOR3& rot )
{
	m_angle = rot;
	this->UpdateWorld( );
}

inline void GameObject::Rotate( const D3DXVECTOR3& rot )
{
	m_angle += rot;
	this->UpdateWorld( );
}

inline void GameObject::SetScale( const D3DXVECTOR3& scale )
{
	m_scale = scale;
	this->UpdateWorld( );
}

inline void GameObject::Scale( const D3DXVECTOR3& scale )
{
	m_scale += scale;
	this->UpdateWorld( );
}

inline void GameObject::SetActive( bool isActive )
{
	m_isActive = isActive;
}

inline const D3DXVECTOR3& GameObject::GetPosition( ) const
{
	return m_pos;
}

inline const D3DXVECTOR3& GameObject::GetAngle( ) const
{
	return m_angle;
}

inline const D3DXVECTOR3& GameObject::GetScale( ) const
{
	return m_scale;
}

inline const std::string& GameObject::GetName( ) const
{
	return m_objName;
}

inline const D3DXMATRIXA16 GameObject::GetWorld( ) const
{
	return m_matWorld;
}

inline const std::unique_ptr<IController>& GameObject::GetController( )
{
	return m_controller;
}

inline bool GameObject::IsActive( ) const
{
	return m_isActive;
}

inline void GameObject::UpdateWorld( )
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling( &matScale, m_scale.x, m_scale.y, m_scale.z );
	
	D3DXMATRIXA16 matRot, matRotX, matRotY, matRotZ;
	D3DXMatrixRotationX( &matRotX, m_angle.x );
	D3DXMatrixRotationY( &matRotY, m_angle.y );
	D3DXMatrixRotationZ( &matRotZ, m_angle.z );
	matRot = matRotX * matRotY * matRotZ;

	D3DXMATRIXA16 matTrans;
	D3DXMatrixTranslation( &matTrans, m_pos.x, m_pos.y, m_pos.z );

	m_matWorld = matScale * matRot * matTrans;
}
