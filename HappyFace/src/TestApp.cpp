#include "HappyFace/HappyFace.h"

class TestScene : public Happy::Scene
{
public:
	TestScene()
	{
		Model backpack("resources/objects/plane/plane.obj");
		backpack.rotate(90.0f, { 0.0f, 1.0f, 0.0f });
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
