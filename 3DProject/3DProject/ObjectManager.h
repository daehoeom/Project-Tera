// Copyright 2014 Jun-ho Cha

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "GameObject.h"


class ObjectManager final
{
	using ObjectMap = std::unordered_map<std::string, GameObject*>;
	
public:
	using iterator = ObjectMap::iterator;
	using const_iterator = ObjectMap::const_iterator;

public:
	SINGLETONE( ObjectManager )

	void Update( float fElapsedTime );
	void Render( );

	void AddObject( GameObject* pObject );
	GameObject* FindObject( const std::string& key );
	void DeleteObject( const std::string& key );

	iterator begin( ) { return m_objMap.begin( ); }
	iterator end( ) { return m_objMap.end( ); }

private:
	ObjectMap m_objMap;
};
