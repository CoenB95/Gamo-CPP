#pragma once

#include "include/groups/gameobjectgroup.h"

using namespace std;

class GameObjectGroup;

class DespawnComponent : public GameObjectComponent {
private:
	GameObjectGroup* parentGroup;
	float secondsLeft;

public:
	DespawnComponent(GameObjectGroup* parentGroup, float timeInSeconds, string tag = "");

	void onUpdate(float elapsedSeconds);
};