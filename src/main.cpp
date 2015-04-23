#ifdef _DEBUG
#include <vld/vld.h>
#endif

#include "Application.h"
#include "MenuState.h"

#include <iostream>
int main(int argc, char ** argv)
{
	std::vector<std::string> params(argv, argv + argc);

	Application app(params[0]);
	app.push(new MenuState);
	app.run();
	std::cin.get();
	//std::cin.get();
}