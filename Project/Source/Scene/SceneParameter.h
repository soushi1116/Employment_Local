#pragma once

enum SceneState
{
	INIT,
	LOAD,
	START,
	LOOP,
	FIN,
	SCENE_STATE_MAX,
	SCENE_STATE_NONE = -1
};

enum SceneType
{
	TITLE,
	HOME,
	MISSION_SELECT,
	BATTLE,
	RESULT,
	SCENE_TYPE_NONE = -1
};