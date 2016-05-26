#pragma once

class IController
{
public:
	IController( class GameObject* owner );
	virtual ~IController( ) = 0;

public:
	virtual void Update( float tickTime ) = 0;

public:
	void SetOwner( class GameObject* owner );
	class GameObject* GetOwner( );

private:
	class GameObject* m_owner;
};

