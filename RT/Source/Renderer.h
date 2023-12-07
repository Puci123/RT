#pragma once
#include "Texture2D.h"
#include "Scean.h"

namespace Rendere 
{
	
	void Trace(Texture2D* const target, const Scean& scean, int32_t maxDepth, int32_t samplePerPixel);

	void AlphaCorrect(Texture2D* const target);

}
