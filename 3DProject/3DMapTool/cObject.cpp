#include "stdafx.h"
#include "cObject.h"

#include "cObjectManager.h"

cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject(void)
{
	g_pObjectManager->RemoveObject(this);
	assert(m_nRefCount == 0 && "이러지 마라..");
}

void cObject::AddRef()
{
	++m_nRefCount;
}

void cObject::Release()
{
	--m_nRefCount;
	if (m_nRefCount <= 0)
	{
		delete this;
	}
}
