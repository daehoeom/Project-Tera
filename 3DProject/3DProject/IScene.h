#pragma once

void ReadXML( 
	_In_ const std::string& xmlPath, 
	_Out_ DWORD* loadSuccess,
	std::function<void()> additionWork );

class IScene
{
public:
	virtual void Render( ) = 0;
	virtual void Update( ) = 0;

public:
	IScene( );
	virtual ~IScene( ) = 0;
};
