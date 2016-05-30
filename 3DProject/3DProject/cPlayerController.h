#pragma once
#include "IController.h"

class cPlayerController : public IController
{
public:
	cPlayerController( class GameObject* owner );
	virtual ~cPlayerController( );

public:
	virtual void Update( ) override;

private:
	D3DXVECTOR3 m_dirVec;
};

