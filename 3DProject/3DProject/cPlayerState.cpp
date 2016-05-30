#include "stdafx.h"
#include "cPlayerState.h"


cPlayerIdleState::cPlayerIdleState( GameObject * owner ) :
	iFSMState( owner )
{
}

cPlayerIdleState::~cPlayerIdleState( )
{
}

void cPlayerIdleState::OnBeginState( )
{
	int n = 3;
}

void cPlayerIdleState::OnEndState( )
{
	int n = 3;
}

void cPlayerIdleState::OnDoingState( )
{
	int n = 3;
}
