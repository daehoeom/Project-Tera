// Copyright 2014 Jun-ho Cha

#pragma once
#include "Singleton.h"
#include "cGameObject.h"


class cGameObject;
class cObjectManager : 
	public TSingleton<cObjectManager>
{
	using ObjectMap = std::unordered_map<std::string, cGameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( );

	void AddObject( cGameObject* pObject );
	void EraseObject( const std::string& key );
	cGameObject* FindObject( const std::string& key );

	iterator begin( );
	iterator end( );

protected:
	cObjectManager( );
	virtual ~cObjectManager( );

private:
	ObjectMap m_objMap;
};

inline void cObjectManager::AddObject(
	cGameObject* obj )
{
	m_objMap.insert( std::make_pair( obj->GetName( ), obj ) );
}

inline cGameObject* cObjectManager::FindObject( 
	const std::string& key )
{
	return m_objMap[key];
}

inline void cObjectManager::EraseObject( 
	const std::string& key )
{
	m_objMap.erase( key );
}

inline cObjectManager::iterator cObjectManager::begin( )
{
	return m_objMap.begin( );
}

inline cObjectManager::iterator cObjectManager::end( )
{
	return m_objMap.end( );
}
