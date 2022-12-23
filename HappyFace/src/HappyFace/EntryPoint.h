#pragma once

extern Application* createApplication();

int main()
{
	auto engine = createApplication();
	engine->go();
	delete engine;
}