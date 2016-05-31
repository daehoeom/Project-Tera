#pragma once

// Category of state
enum class eFSMState
{
	kNone,
	kIdle,
	kDie,
	kMove,
	kAttack,
};

// Abstracted implementation of state
class iFSMState
{
public:
	iFSMState( class cGameObject* owner ) :
		m_owner( owner ) {}
	virtual ~iFSMState( ) {}

	virtual void OnBeginState( ) = 0;
	virtual void OnEndState( ) = 0;
	virtual void OnDoingState( ) = 0;
	virtual void OnDoingStateRender( ) = 0;

protected:
	class cGameObject* GetOwner( ) { return m_owner; }

private:
	class cGameObject* m_owner;
};

class cFSM
{
public:
	cFSM( );
	virtual ~cFSM( );

	virtual void Update( );
	virtual void Render( );

	void AddState( eFSMState stateCategory, 
				   iFSMState* stateImpl );
	
	void TranslateState( eFSMState newState );

	eFSMState GetCurrStateType( ) const;

private:
	std::map<eFSMState, std::unique_ptr<iFSMState>> m_mapState;

protected:
	eFSMState m_currStateType;
	iFSMState* m_curState;
	iFSMState* m_nextState;
};