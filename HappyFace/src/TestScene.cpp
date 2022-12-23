#include "TestScene.h"

TestScene::TestScene()
{
	Model backpack("resources/objects/backpack/backpack.obj");

	backpack.translate({ 1.0f, 1.0f, 0.0f });
	backpack.scale({ 1.0f, 1.0f, 1.0f });
	backpack.rotate(0.0f, { 1.0f, 0.0f, 0.0f });

	addModel(backpack);
	//addShader("modelShader", modelShader);
}
