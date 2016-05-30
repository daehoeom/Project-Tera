#pragma once
#include "cFSM.h"

class cPlayerIdleState :
	public iFSMState
{
public:
	cPlayerIdleState( class GameObject* owner );
	virtual ~cPlayerIdleState( );

	virtual void OnBeginState( );
	virtual void OnEndState( );
	virtual void OnDoingState( );
};

