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
	void EraseObject( const std::wstring& key ); // Delete only key
	void DeleteObject( const std::wstring& key ); // Delete from heap
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

inline void cGameObjectManager::EraseObject( 
	const std::wstring& key )
{
	m_objMap.erase( key );
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
	else
	{
		MessageBox( GetFocus( ),
			L"삭제하려는 대상을 찾을 수 없습니다.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}
}

inline void cGameObjectManager::ResetAllObject( )
{
	for ( auto iter = m_objMap.begin( ); 
		iter != m_objMap.end( );) 
	{
		if ( iter->second->GetIdenfier( ) != ObjectIdenfier::kLight &&
			iter->second->GetIdenfier( ) != ObjectIdenfier::kCamera &&
			iter->second->GetIdenfier( ) != ObjectIdenfier::kPickTile )
		{
			SAFE_DELETE( iter->second );
			m_objMap.erase( iter++ );
		}
		else
		{
			++iter;
		}
	}
}

inline cGameObjectManager::iterator cGameObjectManager::begin()
{
	return m_objMap.begin( );
}

inline cGameObjectManager::iterator cGameObjectManager::end()
{
	return m_objMap.end( );
}