#pragma once
#include "IAction.h"

class GameObject : 
	public IActionDelegate
{
public:
	GameObject( const std::string& objName );
	virtual ~GameObject( );

	virtual void Update( float tickTime );

public:
	void SetPosition( const D3DXVECTOR3& pos );
	void Move( const D3DXVECTOR3& pos );
	void SetAngle( const D3DXVECTOR3& rot );
	void Rotate( const D3DXVECTOR3& rot );
	void SetScale( const D3DXVECTOR3& scale );
	void Scale( const D3DXVECTOR3& scale );
	void SetActive( bool isActive );
	void SetAction( class IAction* action );
	void SetController( class IController* controller );

	const D3DXVECTOR3& GetPosition( ) const;
	const D3DXVECTOR3& GetAngle( ) const;
	const D3DXVECTOR3& GetScale( ) const;
	const std::string& GetName( ) const;
	class IController* GetController( );
	bool IsActive( ) const;
	
	template <typename T> T* GetAction( )
	{
		return reinterpret_cast<T*>( m_actionMap[T::GetIdentifierStatic()] );
	}

private:
	std::map<unsigned int, class IAction*> m_actionMap;
	class IController* m_controller;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_angle;
	D3DXVECTOR3 m_scale;
	std::string m_objName;
	bool m_isActive;
};

inline void GameObject::SetPosition( const D3DXVECTOR3& pos )
{
	m_pos = pos;
}

inline void GameObject::Move( const D3DXVECTOR3& pos )
{
	m_pos += pos;
}

inline void GameObject::SetAngle( const D3DXVECTOR3& rot )
{
	m_angle = rot;
}

inline void GameObject::Rotate( const D3DXVECTOR3& rot )
{
	m_angle += rot;
}

inline void GameObject::SetScale( const D3DXVECTOR3& scale )
{
	m_scale = scale;
}

inline void GameObject::Scale( const D3DXVECTOR3& scale )
{
	m_scale += scale;
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

inline const std::string & GameObject::GetName( ) const
{
	return m_objName;
}

inline IController * GameObject::GetController( )
{
	return m_controller;
}

inline bool GameObject::IsActive( ) const
{
	return m_isActive;
}
