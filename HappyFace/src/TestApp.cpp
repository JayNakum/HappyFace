#include "HappyFace/HappyFace.h"

class TestScene : public Happy::Scene
{
public:
	void initModels() override
	{
		auto& shader = getShader("modelShader");
		shader.use();
		shader.setVec4("value", { 1.0f, 1.0f, 1.0f, 1.0f });
		shader.unUse();

		Model backpack("resources/objects/backpack/backpack.obj");
		backpack.translate({ 0.0f, -0.5f, -5.0f });

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
