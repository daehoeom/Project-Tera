#pragma once

class cGroup;
class cMtlTex;

class Parser
{
public:
	Parser( const char* lexTarget ) :
		m_lexTarget( lexTarget ),
		m_length( std::strlen( lexTarget )),
		m_readIndex( 0 )
	{
	}

	const char* Get( ) const
	{
		return m_outText;
	}

	bool Eof( ) const
	{
		return ( m_lexTarget[m_readIndex] == '\0' );
	}

	bool Parse( )
	{
		if ( Eof( ) )
		{
			return false;
		}

		// TODO:
		// Not perfect because string space ( e.g. " MY NAME IS " )
		// But useless now. so, modify it later

		int currIndex = m_readIndex;
		int writeIndex = 0;
		bool findFirstSpace = false;
		while ( true )
		{
			if ( findFirstSpace )
			{
				m_outText[writeIndex++] = m_lexTarget[currIndex];

				if ( m_lexTarget[currIndex] == ' ' ||
						m_lexTarget[currIndex] == '\0' )
				{
					m_outText[writeIndex-1] = '\0';
					m_readIndex = currIndex++;
					return true;
				}

				++currIndex;
			}
			else
			{
				if ( m_lexTarget[currIndex++] == ' ' )
				{
					findFirstSpace = true;
				}
			}
		}


	}

private:
	const int32_t m_length;
	int32_t m_readIndex;
	const char* m_lexTarget;
	char m_outText[1000];
};


class cObjLoader
{
public:
	cObjLoader(void);
	~cObjLoader(void);

	void Load(IN const char* szFullPath,
		OUT std::vector<cGroup*>& vecGroup,
		IN D3DXMATRIXA16* mat = NULL);

	LPD3DXMESH Load(IN const char* szFullPath,
		OUT std::vector<cMtlTex*>& vecMtlTex,
		IN D3DXMATRIXA16* mat = NULL);

	void LoadMtlLib(const char* szFullPath);

	const D3DXVECTOR3& GetMinVector( ) const;
	const D3DXVECTOR3& GetMaxVector( ) const;

private:
	int32_t GetItemCountInF( const char* line );

private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
};

inline const D3DXVECTOR3& cObjLoader::GetMinVector( ) const
{
	return m_vMin;
}

inline const D3DXVECTOR3& cObjLoader::GetMaxVector( ) const
{
	return m_vMax;
}

inline int32_t cObjLoader::GetItemCountInF( const char * line )
{
	int retSpace = 0;
	int length = std::strlen( line );
	for ( int i = 0; i < length; ++i )
	{
		if ( line[i] == ' ' )
		{
			++retSpace;
		}
	}

	return retSpace;
}
