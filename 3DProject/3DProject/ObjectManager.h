// Copyright 2014 Jun-ho Cha

#pragma once
#include "Singleton.h"
#include "GameObject.h"


class ObjectManager : 
	public TSingleton<ObjectManager>
{
	using ObjectMap = std::unordered_map<std::string, GameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( float fElapsedTime );

	void AddObject( class GameObject* pObject );
	class GameObject* FindObject( const std::string& key );
	void DeleteObject( const std::string& key );

	iterator begin( );
	iterator end( );

protected:
	ObjectManager( );
	virtual ~ObjectManager( );

private:
	ObjectMap m_objMap;
};

inline void ObjectManager::AddObject(
	GameObject* obj )
{
	m_objMap.insert( std::make_pair( obj->GetName( ), obj ) );
}

inline GameObject* ObjectManager::FindObject( const std::string& key )
{
	return m_objMap[key];
}

inline void ObjectManager::DeleteObject( const std::string& key )
{
	m_objMap.erase( key );
}

inline ObjectManager::iterator ObjectManager::begin( )
{
	return m_objMap.begin( );
}

inline ObjectManager::iterator ObjectManager::end( )
{
	return m_objMap.end( );
}
