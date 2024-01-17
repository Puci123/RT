#pragma once
#include "Texture2D.h"
#include "Scean.h"

namespace Rendere 
{
	
	void Trace(Texture2D& target, Scean& scean, int32_t maxDepth, int32_t samplePerPixel, int32_t start, int32_t numberOfline);


	void AlphaCorrect(Texture2D* const target);

}
