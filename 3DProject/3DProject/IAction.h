#pragma once

class GameObject;
class IActionDelegate
{
public:
	virtual void OnActionStart( class IAction* sender ) {}
	virtual void OnActionFinish( class IAction* sender ) {}
};

class IAction
{
protected:
	class action_identifier {};

public:
	IAction( );
	virtual ~IAction( );

	virtual void Start( );
	virtual void Update( float tickTime );

	void SetOwner( GameObject* owner );
	GameObject* GetOwner( );
	void SetActive( bool isActive );
	bool IsActive( ) const;
	
	virtual uintptr_t GetIdentifier( ) const = 0;

public:
	void SetDelegate( IActionDelegate* actionDelegate );
	IActionDelegate* GetDelegate( );

private:
	IActionDelegate* m_actionDelegate;
	GameObject* m_owner;
	bool m_isActive;
};