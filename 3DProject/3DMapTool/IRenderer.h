#pragma once


class IRenderer
{
public:
	IRenderer( );
	virtual ~IRenderer( ) = 0;

	virtual void Render( ) = 0;

public:
	void SetOwner( class IRenderable* );
	class IRenderable* GetOwner( );

private:
	class IRenderable* m_owner;
};

inline void IRenderer::SetOwner( 
	IRenderable* owner )
{
	m_owner = owner;
}

inline IRenderable* IRenderer::GetOwner( )
{
	return m_owner;
}
