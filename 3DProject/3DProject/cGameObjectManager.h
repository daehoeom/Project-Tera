/*
cGameObjectManager는
등록된 오브젝트의

Update
Render
Delete를 자동으로 호출해준다.

사용 방법은

cGameObjectManager::AddObject( new SomeObject( ... ));

AddObject는 추가된 객체의 포인터를 반환해서
이 객체 포인터를 따로 사용하고 싶다면 따로 저장해서 쓰면 된다.

( 원래의 사용 의도는 일단 이렇게. )

*/

#pragma once
#include "Singleton.h"
#include "cGameObject.h"

class cGameObject;
class cGameObjectManager : 
	public TSingleton<cGameObjectManager>
{
	using ObjectMap = std::unordered_map<std::string, cGameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( );
	void Render( );

public:
	template <class _ObjectTy>
	_ObjectTy* AddObject( const std::string& name, _ObjectTy* obj );

	cGameObject* FindObject( const std::string& key );
	void EraseObject( const std::string& key );
	
	// 모든 등록된 오브젝트를 파괴합니다.
	void ResetAllObject( );

	iterator begin( );
	iterator end( );

protected:
	cGameObjectManager();
	virtual ~cGameObjectManager();

private:
	ObjectMap m_objMap;
};

template<class _ObjectTy>
inline _ObjectTy* cGameObjectManager::AddObject( 
	const std::string& name, 
	_ObjectTy* obj )
{
	obj->SetName( name );
	m_objMap.insert( std::make_pair( name, obj ));

	return obj;
}

inline cGameObject* cGameObjectManager::FindObject(
	const std::string& key )
{
	return m_objMap[key];
}

inline void cGameObjectManager::EraseObject(
	const std::string& key )
{
	m_objMap.erase( key );
}

inline cGameObjectManager::iterator cGameObjectManager::begin()
{
	return m_objMap.begin( );
}

inline cGameObjectManager::iterator cGameObjectManager::end()
{
	return m_objMap.end( );
}