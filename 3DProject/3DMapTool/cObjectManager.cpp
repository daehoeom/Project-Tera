#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
	assert( m_setObject.empty( ) &&
		"생성된 cObject를 상속받은 객체 중 해제되지 않은 객체가 있습니다." );
}
