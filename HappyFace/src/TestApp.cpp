#include "HappyFace/HappyFace.h"

#include "HappyFace/Processing/Multiplication.h"

class TestScene : public Happy::Scene
{
public:
	TestScene()
	{
		modelShader[1] = "resources/shaders/processing/multiply.fs.glsl";
		addShader("modelShader", modelShader);

		auto& shader = getShader("modelShader");

		Model backpack("resources/objects/backpack/backpack.obj", [&]() {
			// multiply.apply(shader);
			shader.setVec4("mul_value", { 1.0f, 1.0f, 1.0f, 1.0f });
		});
		
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
