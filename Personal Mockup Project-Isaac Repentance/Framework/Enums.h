#pragma once

enum class Axis
{
	None = -1,

	HorizontalMove,
	VerticalMove,
	HorizontalAttack,
	VerticalAttack,

	AxisCount
};

/// <summary>
/// TopLeft, MiddleCenter, BottomRight etc....
/// </summary>
enum class Origins
{
	None = -1,

	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,

	Custom,

	Count
};

enum class SortingLayers
{
	None = -1,

	Background,
	Foreground,
	UI,

	Count
};

/// <summary>
/// DevScenes must be removed in the game release version.
/// </summary>
enum class SceneIds
{
	None = -1,
	
	SceneDev1,
	SceneDev2,

	SceneMainTitle,
	SceneFloor1,
	SceneBoss1,

	Count
};

enum class AnimationLoopTypes
{
	None = -1,

	Single,
	Loop,

	Count
};