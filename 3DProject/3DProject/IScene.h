#pragma once

class IScene
{
public:
	IScene( const std::string& xmlPath );
	virtual ~IScene( ) = 0;

	virtual void Render( ) = 0;
	virtual void Update( ) = 0;

private:
	void ReadXML( const std::string& xmlPath );
};