#include "stdafx.h"
#include "IController.h"


IController::IController( class GameObject* owner ) :
	m_owner( owner )
{
}


IController::~IController( )
{
}

void IController::SetOwner( GameObject * owner )
{
	m_owner = owner;
}

GameObject * IController::GetOwner( )
{
	return m_owner;
}
