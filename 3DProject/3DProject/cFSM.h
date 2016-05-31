#pragma once

// Category of state
enum class eFSMState
{
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

	void AddState( eFSMState stateCategory, 
				   iFSMState* stateImpl );
	void TranslateState( eFSMState newState );

private:
	std::map<eFSMState, std::unique_ptr<iFSMState>> m_mapState;

protected:
	iFSMState* m_curState;
	iFSMState* m_nextState;
};