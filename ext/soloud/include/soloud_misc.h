// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_MISC_H
#define SOLOUD_MISC_H

#include "soloud.h"

namespace SoLoud
{
	namespace Misc
	{
		// Generate a waveform.
		float generateWaveform(int aWaveform, float p);

		// WELL512 random
		class Prg
		{
		public:
			// random generator
			Prg();
			unsigned int mState[16];
			unsigned int mIndex;
			unsigned int rand();
			float rand_float();
			void srand(int aSeed);
		};

	};
};

#endif