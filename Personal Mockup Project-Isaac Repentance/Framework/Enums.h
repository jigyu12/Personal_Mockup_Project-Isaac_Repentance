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