#include "stdafx.h"
#include "IO.h"

#include <iterator>
#include <fstream>

std::vector<float> ReadRAW( const char* filePath )
{
	std::ifstream ifs( filePath, std::ios_base::binary );
	if ( !ifs )
	{
		MessageBox( GetFocus( ), L"Failed to load raw file",
			L"WARNING!", MB_OK );

		return std::vector<float>();
	}

	
	ifs.seekg( 0, std::ios_base::end );
	int readBufSize = ifs.tellg( );
	ifs.seekg( 0, std::ios_base::beg );


	std::vector<uint8_t> readBuf( readBufSize );
	ifs.read( reinterpret_cast<char*>( &readBuf[0] ), readBuf.size( ));
	ifs.close( );


	std::vector<float> heightRepo( readBufSize );
	for ( int i = 0; i < readBuf.size( ); ++i )
	{
		heightRepo[i] = readBuf[i];
	}

	return heightRepo;
}