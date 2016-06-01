#pragma once
class cObject
{
private:
	int m_nRefCount;

public:
	cObject(void);
	virtual ~cObject(void);

	void AddRef();
	void Release();
};

