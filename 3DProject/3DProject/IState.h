#pragma once

template <class name>
class IState
{
public:

	virtual void Enter(name*) = 0;
	virtual void Execute(name*) = 0;
	virtual void Exit(name*) = 0; 
};

