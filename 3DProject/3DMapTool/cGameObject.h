#pragma once

enum ObjectIdenfier
{
	kLight,
	kCamera,
	kObj,
	kX,
	kRaw,
	kPickTile,
	kUnknown,
};

class cGameObject
{
public:
	explicit cGameObject( const std::wstring& objName );
	virtual ~cGameObject( );

	virtual void Update( );
	virtual void Render( );

public:
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
	
	void SetName( const std::wstring& objName );

	/*
		State & Component
	*/
	void SetSelected( bool isSelected );
	bool IsSelected( ) const;
	virtual void SetActive( bool isActive );
	bool IsActive( ) const;
	
	const std::wstring& GetName( ) const;
	const D3DXMATRIXA16& GetWorld( ) const;

	virtual ObjectIdenfier GetIdenfier( ) const = 0;

private:
	void UpdateWorld( );
	bool IsSameWithSelectedItemInHierarchy( );

private:
	bool m_isSelected;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_angle;
	D3DXVECTOR3 m_scale;
	D3DXMATRIXA16 m_matWorld;
	std::wstring m_objName;
	bool m_isActive;
};

inline void cGameObject::SetPosition( const D3DXVECTOR3& pos )
{
	m_pos = pos;
	m_matWorld._41 = pos.x;
	m_matWorld._42 = pos.y;
	m_matWorld._43 = pos.z;

	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetPositionData( m_pos );
	}
}

inline void cGameObject::Move( const D3DXVECTOR3& pos )
{
	m_pos += pos;
	m_matWorld._41 += pos.x;
	m_matWorld._42 += pos.y;
	m_matWorld._43 += pos.z;
	
	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetPositionData( m_pos );
	}
}

inline void cGameObject::SetAngle( const D3DXVECTOR3& rot )
{
	m_angle = rot;
	this->UpdateWorld( );
	
	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetRotationData( m_angle );
	}
}

inline void cGameObject::Rotate( const D3DXVECTOR3& rot )
{
	m_angle += rot;
	this->UpdateWorld( );

	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetRotationData( m_angle );
	}
}

inline void cGameObject::SetScale( const D3DXVECTOR3& scale )
{
	m_scale = scale;
	this->UpdateWorld( );

	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetScaleData( m_scale );
	}
}

inline void cGameObject::Scale( const D3DXVECTOR3& scale )
{
	m_scale += scale;
	this->UpdateWorld( );
	
	if ( IsSameWithSelectedItemInHierarchy() )
	{
		g_inspectorWnd->SetScaleData( m_scale );
	}
}

inline void cGameObject::SetSelected( bool isSelected )
{
	m_isSelected = isSelected;
}

inline bool cGameObject::IsSelected( ) const
{
	return m_isSelected;
}

inline void cGameObject::SetActive( bool isActive )
{
	m_isActive = isActive;
}

inline const D3DXVECTOR3& cGameObject::GetPosition( ) const
{
	return m_pos;
}

inline const D3DXVECTOR3& cGameObject::GetAngle( ) const
{
	return m_angle;
}

inline const D3DXVECTOR3& cGameObject::GetScale( ) const
{
	return m_scale;
}

inline void cGameObject::SetName( 
	const std::wstring& objName )
{
	m_objName = objName;
}

inline const std::wstring& cGameObject::GetName( ) const
{
	return m_objName;
}

inline const D3DXMATRIXA16& cGameObject::GetWorld( ) const
{
	return m_matWorld;
}

inline bool cGameObject::IsActive( ) const
{
	return m_isActive;
}

inline void cGameObject::UpdateWorld( )
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

inline bool cGameObject::IsSameWithSelectedItemInHierarchy( )
{
	if ( g_hierarchyWnd->GetSelectedItemIndex( ) != -1 )
	{
		wchar_t selectedItemText[256] {0};
		g_hierarchyWnd->GetSelectedItemText(
			selectedItemText, 256 );

		if ( !std::wcscmp( selectedItemText,
			this->GetName( ).c_str( ) ) )
		{
			return true;
		}
	}
	
	return false;

	return false;
}
