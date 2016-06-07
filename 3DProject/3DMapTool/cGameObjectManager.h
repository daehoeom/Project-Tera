// Copyright 2014 Jun-ho Cha

#pragma once
#include "Singleton.h"
#include "cGameObject.h"

class cGameObject;
class cGameObjectManager : 
	public TSingleton<cGameObjectManager>
{
	using ObjectMap = std::unordered_map<std::wstring, cGameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	void Update( );
	void Render( );

	void AddObject( cGameObject* pObject );
	void DeleteObject( const std::wstring& key );
	void ResetAllObject( );
	cGameObject* FindObject( const std::wstring& key );

	iterator begin( );
	iterator end( );

protected:
	cGameObjectManager();
	virtual ~cGameObjectManager();

private:
	cGameObject* m_prevSelected;
	ObjectMap m_objMap;
};

inline void cGameObjectManager::AddObject(
	cGameObject* obj )
{
	m_objMap.insert( std::make_pair( obj->GetName( ), obj ) );
}

inline cGameObject* cGameObjectManager::FindObject(
	const std::wstring& key )
{
	return m_objMap[key];
}

inline void cGameObjectManager::DeleteObject(
	const std::wstring& key )
{
	auto iter = m_objMap.find( key );
	if ( iter != m_objMap.end( ) )
	{
		SAFE_DELETE( iter->second );
		m_objMap.erase( key );
	}
}

inline void cGameObjectManager::ResetAllObject( )
{
	map<string, SerialdMsg::SerialFunction_t>::iterator pm_it = port_map.begin( );
	while ( pm_it != port_map.end( ) )
	{
		if ( pm_it->second == delete_this_id )
		{
			port_map.erase( pm_it++ );  // Use iterator.
										// Note the post increment.
										// Increments the iterator but returns the
										// original value for use by erase 
		}
		else
		{
			++pm_it;           // Can use pre-increment in this case
							   // To make sure you have the efficient version
		}
	}

	/*auto iter = m_objMap.begin( );
	while ( iter != m_objMap.end( ) )
	{
		if ( iter->second == delete_this_id )
		{
			pm_it = port_map.erase( pm_it );
		}
		else
		{
			++pm_it;
		}
	}*/
}

inline cGameObjectManager::iterator cGameObjectManager::begin()
{
	return m_objMap.begin( );
}

inline cGameObjectManager::iterator cGameObjectManager::end()
{
	return m_objMap.end( );
}