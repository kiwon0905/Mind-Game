#pragma once
#include <stack>
#include <memory>
#include <vector>
#include "GameState.h"

class Application;

class GameStateStack
{
public:

	void pop();
	void push(GameState * g);
	void clear();
	bool isEmpty();
	
	void update(Application & app);
	void handleEvent(Application & app);
	void draw(Application & app);
	void applyChanges(Application & app);
private:
	struct Change
	{
		enum Action
		{
			Pop,
			Push,
			Clear
		} action;
		GameState * g;
		Change(Action action, GameState * g = nullptr);
	};
	std::stack<std::unique_ptr<GameState>> m_states;
	std::vector<Change> mChanges;
};