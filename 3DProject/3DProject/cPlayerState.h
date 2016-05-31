#pragma once
#include "cFSM.h"

class cPlayerIdleState :
	public iFSMState
{
public:
	cPlayerIdleState( class cGameObject* owner );
	virtual ~cPlayerIdleState( );

	virtual void OnBeginState( ) override;
	virtual void OnDoingState( ) override;
	virtual void OnEndState( ) override;
	virtual void OnDoingStateRender( ) override;

private:
	
};
