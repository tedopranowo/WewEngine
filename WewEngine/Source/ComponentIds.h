#pragma once

// Cool thing about an anonymous enum inside of a namespace
// is that you can use these enum values as indices into arrays
// example: ComponentIds[SquareRenderer].asdfjasflsdj
namespace ComponentIds
{
	enum
	{
		SquareRenderer = 0,
		Component_COUNT
	};
}