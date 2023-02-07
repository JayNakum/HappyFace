#include "HappyFace/HappyFace.h"

class TestScene : public Happy::Scene
{
public:
	TestScene()
	{
		Model backpack("resources/objects/backpack/backpack.obj");
		addModel(backpack);
	}
};

class TestApp : public Happy::Application
{
public:
	TestApp()
	{
		loadScene(new TestScene());
	}
};

Happy::Application* createApplication()
{
	return new TestApp();
}
