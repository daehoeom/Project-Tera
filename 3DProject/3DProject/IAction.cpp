#include "stdafx.h"
#include "IAction.h"



IAction::IAction( ) :
	m_isActive( false ),
	m_owner( nullptr ),
	m_actionDelegate( nullptr )
{
}


IAction::~IAction( )
{
}

void IAction::Start( )
{
	this->m_actionDelegate->OnActionStart( this );
	this->SetActive( true );
}

void IAction::Update( float tickTime )
{
}

void IAction::SetOwner( GameObject * owner )
{
	m_owner = owner;
}

GameObject * IAction::GetOwner( )
{
	return m_owner;
}

void IAction::SetActive( bool isActive )
{
	m_isActive = isActive;
}

bool IAction::IsActive( ) const
{
	return m_isActive;
}

void IAction::SetDelegate( IActionDelegate* actionDelegate )
{
	m_actionDelegate = actionDelegate;
}

IActionDelegate * IAction::GetDelegate( )
{
	return m_actionDelegate;
}
