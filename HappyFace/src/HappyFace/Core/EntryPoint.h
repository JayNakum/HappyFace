#pragma once

extern Happy::Application* createApplication();

int main()
{
	auto engine = createApplication();
	engine->go();
	delete engine;
}