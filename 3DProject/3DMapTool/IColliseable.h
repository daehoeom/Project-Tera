#pragma once
#include "IRenderable.h"
#include "ICollider.h"

class IColliseable :
	public IRenderable
{
public:
	explicit IColliseable( const std::wstring& objName,
		 ICollider* collider = nullptr );
	virtual ~IColliseable( );

	virtual void Update( ) override;
	virtual void Render( ) override;
	
	void SetDebugRender( bool isDebugRender );
	void SetCollider( ICollider* collider );
	ICollider* GetCollider( );
	const ICollider* GetCollider( ) const;

private:
	bool m_isDebugRender;
	ICollider* m_collider;
};