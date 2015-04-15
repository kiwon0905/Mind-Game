#include "GameStateStack.h"
#include "GameState.h"


GameStateStack::Change::Change(Action action, GameState * g) :
action(action), 
g(g)
{
}

void GameStateStack::update(Application & app)
{
	m_states.top()->update(app);
}

void GameStateStack::handleEvent(Application & app)
{
	m_states.top()->handleEvent(app);
}

void GameStateStack::draw(Application & app)
{
	m_states.top()->draw(app);
}

void GameStateStack::pop()
{
	mChanges.push_back(Change(Change::Pop));
}

void GameStateStack::push(GameState * g)
{
	mChanges.push_back(Change(Change::Push, g));
}

void GameStateStack::clear()
{
	mChanges.push_back(Change(Change::Clear));
}

bool GameStateStack::isEmpty()
{
	return m_states.empty();
}

void GameStateStack::applyChanges(Application & app)
{
	for (const auto & change : mChanges)
	{
		switch (change.action)
		{
		case Change::Push:
			if (m_states.size() > 0)
				m_states.top()->onObscure(app);
			m_states.push(std::unique_ptr<GameState>(change.g));
			m_states.top()->onEnter(app);
			break;
		case Change::Pop:
				m_states.top()->onExit(app);
				m_states.pop();
				if (m_states.size() > 0)
					m_states.top()->onReveal(app);
			break;
		case Change::Clear:
			while (m_states.size()>1)
			{
				m_states.top()->onExit(app);
				m_states.pop();
				m_states.top()->onReveal(app);
			}
			m_states.top()->onExit(app);
			m_states.pop();
			
			break;
		default:
			break;
		}
	}
	mChanges.clear();
}