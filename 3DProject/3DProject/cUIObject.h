#pragma once

enum eButtonTag
{
	E_TAG_CLOSE,
	E_TAG_MOVE,
	E_TAG_ITEM1,
	E_TAG_ITEM2,
	E_TAG_ITEM3,
	E_TAG_NONE,
};

class cUIObject : public cObject
{
protected:
	cUIObject*		m_pParent;
	D3DXMATRIXA16	m_matWorld;
	int				m_nWidth;
	int				m_nHeight;

	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE(std::vector<cUIObject*>, m_vecChild, Child);
	SYNTHESIZE(RECT, m_Rc, Rc);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(eButtonTag, m_eTag, ButtonTag);

public:
	cUIObject();
	~cUIObject();

	virtual void SetWorld(D3DXMATRIXA16* world) { m_matWorld = *world; }
	virtual void SetSize(int width, int height);
	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void UpdateWorldTM();
	virtual void UpdateChildren();
	virtual void Destroy();
};

