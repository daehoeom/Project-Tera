#pragma once
#include "Singleton.h"

/*
	HOW TO USE?

	Log( L"zz" );
	Log( L"³ª¤·s¤¤", "TKD", 2342 );
*/


class TLogger :
	public TSingleton<TLogger>
{
public:
	HANDLE GetStdOutputHandle( ) const { return m_stdOutputHandle; }

protected:
	TLogger( )  :
		m_stdOutputHandle( InitMe( )) {}
	virtual ~TLogger( ) {}

private:
	HANDLE InitMe( )
	{
		if ( AllocConsole( ) == FALSE )
		{
			MessageBox( GetFocus( ),
				L"Failed to invoke AllocConsole.",
				L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION
			);
			return nullptr;
		}

		return GetStdHandle( STD_OUTPUT_HANDLE );
	}

private:
	const HANDLE m_stdOutputHandle;
};

inline void Log( )
{
}

template <typename _Ty>
void Log( const _Ty& str )
{
	Log( std::to_wstring( str ).c_str( ));
}

inline void Log( const wchar_t* str )
{
	WriteConsoleW(
		TLogger::Get( )->GetStdOutputHandle( ),
		str,
		std::wcslen( str ),
		nullptr,
		nullptr
	);
}

inline void Log( const char* str )
{
	WriteConsoleA(
		TLogger::Get( )->GetStdOutputHandle( ),
		str,
		std::strlen( str ),
		nullptr,
		nullptr
	);
}

template <typename Arg, typename ...Args>
void Log( const Arg& arg, const Args&... args )
{
#if defined( DEBUG ) || defined( _DEBUG )
	Log( arg );
	Log( args... );
#endif
}