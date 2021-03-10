// SPDX-License-Identifier: GPL-3.0-only

#include "soloud.h"

namespace SoLoud
{
	Fader::Fader()
	{
		mCurrent = mFrom = mTo = mDelta = 0;
		mTime = mStartTime = mEndTime = 0;
		mActive = 0;
	}

	void Fader::set(float aFrom, float aTo, double aTime, double aStartTime)
	{
		mCurrent = mFrom;
		mFrom = aFrom;
		mTo = aTo;
		mTime = aTime;
		mStartTime = aStartTime;
		mDelta = aTo - aFrom;
		mEndTime = mStartTime + mTime;
		mActive = 1;
	}

	void Fader::setLFO(float aFrom, float aTo, double aTime, double aStartTime)
	{
		mActive = 2;
		mCurrent = 0;
		mFrom = aFrom;
		mTo = aTo;
		mTime = aTime;
		mDelta = (aTo - aFrom) / 2;
		if (mDelta < 0) mDelta = -mDelta;
		mStartTime = aStartTime;
		mEndTime = (float)M_PI * 2 / mTime;
	}

	float Fader::get(double aCurrentTime)
	{
		if (mActive == 2)
		{
			// LFO mode
			if (mStartTime > aCurrentTime)
			{
				// Time rolled over.
				mStartTime = aCurrentTime;
			}
			double t = aCurrentTime - mStartTime;
			return (float)(sin(t * mEndTime) * mDelta + (mFrom + mDelta));
			
		}
		if (mStartTime > aCurrentTime)
		{
			// Time rolled over.
			// Figure out where we were..
			float p = (mCurrent - mFrom) / mDelta; // 0..1
			mFrom = mCurrent;
			mStartTime = aCurrentTime;
			mTime = mTime * (1 - p); // time left
			mDelta = mTo - mFrom;
			mEndTime = mStartTime + mTime;
		}
		if (aCurrentTime > mEndTime)
		{
			mActive = -1;
			return mTo;
		}
		mCurrent = (float)(mFrom + mDelta * ((aCurrentTime - mStartTime) / mTime));
		return mCurrent;
	}
};
