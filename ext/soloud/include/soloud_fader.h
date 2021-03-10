// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_FADER_H
#define SOLOUD_FADER_H

#include "soloud.h"

namespace SoLoud
{
	// Helper class to process faders
	class Fader
	{
	public:
		// Value to fade from
		float mFrom;
		// Value to fade to
		float mTo;
		// Delta between from and to
		float mDelta;
		// Total time to fade
		time mTime;
		// Time fading started
		time mStartTime;
		// Time fading will end
		time mEndTime;
		// Current value. Used in case time rolls over.
		float mCurrent;
		// Active flag; 0 means disabled, 1 is active, 2 is LFO, -1 means was active, but stopped
		int mActive;
		// Ctor
		Fader();
		// Set up LFO
		void setLFO(float aFrom, float aTo, time aTime, time aStartTime);
		// Set up fader
		void set(float aFrom, float aTo, time aTime, time aStartTime);
		// Get the current fading value
		float get(time aCurrentTime);
	}; 
};

#endif 