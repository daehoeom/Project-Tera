#pragma once
// 원래는 UI 베이스를 상속받아야 함. 아직 안나왔으므로 패스.

#include "c3DSprite.h"

class cUnitObject;
class cHPGaugeBar :
	public cGameObject
{
public:
	explicit cHPGaugeBar( 
		const char* hpGuagePath,
		const char* hpFramePath );
	virtual ~cHPGaugeBar( );

	virtual void Update( );
	virtual void Render( );

public:
	void SetOwner( cUnitObject* ); // 원래 UI쪽에 있어야함
	cUnitObject* GetOwner( );

private:
	//D3DXVECTOR3 m_myPos; // Final present pos is <ownerPos + m_myPos>
	cUnitObject* m_owner;
	cBillboard3DSprite* m_hpGuage;
	cBillboard3DSprite* m_hpFrame;
	LPD3DXEFFECT m_hpShader;
	LPD3DXEFFECT m_texShader;
};

inline void cHPGaugeBar::SetOwner( 
	cUnitObject* owner )
{
	m_owner = owner;
}

inline cUnitObject* cHPGaugeBar::GetOwner( )
{
	return m_owner;
}