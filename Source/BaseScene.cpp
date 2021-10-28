#include "BaseScene.h"
#include "GameObject.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}