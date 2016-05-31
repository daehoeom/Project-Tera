// Copyright 2014 Jun-ho Cha

#pragma once
#include "Singleton.h"
#include "cGameObject.h"


class cObjectManager : 
	public TSingleton<cObjectManager>
{
	using ObjectMap = std::unordered_map<std::string, cGameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( );

	void AddObject( class cGameObject* pObject );
	class cGameObject* FindObject( const std::string& key );
	void DeleteObject( const std::string& key );

	iterator begin( );
	iterator end( );

protected:
	cObjectManager( );
	virtual ~cObjectManager( );

private:
	void UpdateCollisionState( );

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

inline void cObjectManager::DeleteObject( 
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
