#include "stdafx.h"
#include "cFSM.h"


cFSM::cFSM( ):
	m_curState( NULL ),
	m_nextState( NULL ),
	m_currStateType( eFSMState::kNone )
{
}

cFSM::~cFSM( )
{
}

void cFSM::AddState( eFSMState stateCategory, iFSMState* stateImpl )
{
	auto iter = m_mapState.find( stateCategory );
	if ( iter == m_mapState.end( ) )
	{
		m_mapState[stateCategory].reset( stateImpl );
	}
}

void cFSM::Update( )
{
	if ( m_nextState != nullptr )
	{
		if ( m_curState )
		{
			m_curState->OnEndState( );
		}
		m_curState = m_nextState;
		m_nextState->OnBeginState( );
		m_nextState = nullptr;
	}
	
	if ( m_curState )
	{
		m_curState->OnDoingState( );
	}
}

void cFSM::Render( )
{
	if ( m_curState )
	{
		m_curState->OnDoingStateRender( );
	}
}

void cFSM::TranslateState(
	eFSMState newState )
{
	m_currStateType = newState;
	
	auto iter = m_mapState.find( newState );
	if ( iter != m_mapState.end( ) )
	{
		m_nextState = iter->second.get();
	}
}

eFSMState cFSM::GetCurrStateType( ) const
{
	return m_currStateType;
}
