#include "HappyFace/HappyFace.h"

class TestScene : public Scene
{
public:
	TestScene()
	{
		Model backpack("resources/objects/backpack/backpack.obj");
		addModel(backpack);
	}
};

class TestApp : public Application
{
public:
	TestApp()
	{
		loadScene(new TestScene());
	}
};

Application* createApplication()
{
	return new TestApp();
}
