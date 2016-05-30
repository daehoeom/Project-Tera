// Copyright 2014 Jun-ho Cha

#pragma once
#include "Singleton.h"
#include "GameObject.h"


class cObjectManager : 
	public TSingleton<cObjectManager>
{
	using ObjectMap = std::unordered_map<std::string, GameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( );

	void AddObject( class GameObject* pObject );
	class GameObject* FindObject( const std::string& key );
	void DeleteObject( const std::string& key );

	iterator begin( );
	iterator end( );

protected:
	cObjectManager( );
	virtual ~cObjectManager( );

private:
	ObjectMap m_objMap;
};

inline void cObjectManager::AddObject(
	GameObject* obj )
{
	m_objMap.insert( std::make_pair( obj->GetName( ), obj ) );
}

inline GameObject* cObjectManager::FindObject( const std::string& key )
{
	return m_objMap[key];
}

inline void cObjectManager::DeleteObject( const std::string& key )
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
