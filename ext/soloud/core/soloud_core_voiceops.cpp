// SPDX-License-Identifier: GPL-3.0-only

#include "soloud.h"

// Direct voice operations (no mutexes - called from other functions)

namespace SoLoud
{
	result Soloud::setVoiceRelativePlaySpeed_internal(unsigned int aVoice, float aSpeed)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		if (aSpeed <= 0.0f)
		{
			return INVALID_PARAMETER;
		}

		if (mVoice[aVoice])
		{
			mVoice[aVoice]->mSetRelativePlaySpeed = aSpeed;
			updateVoiceRelativePlaySpeed_internal(aVoice);
		}

		return 0;
	}

	void Soloud::setVoicePause_internal(unsigned int aVoice, int aPause)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		mActiveVoiceDirty = true;
		if (mVoice[aVoice])
		{
			mVoice[aVoice]->mPauseScheduler.mActive = 0;

			if (aPause)
			{
				mVoice[aVoice]->mFlags |= AudioSourceInstance::PAUSED;
			}
			else
			{
				mVoice[aVoice]->mFlags &= ~AudioSourceInstance::PAUSED;
			}
		}
	}

	void Soloud::setVoicePan_internal(unsigned int aVoice, float aPan)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		if (mVoice[aVoice])
		{
			mVoice[aVoice]->mPan = aPan;
			float l = (float)cos((aPan + 1) * M_PI / 4);
			float r = (float)sin((aPan + 1) * M_PI / 4);
			mVoice[aVoice]->mChannelVolume[0] = l;
			mVoice[aVoice]->mChannelVolume[1] = r;
			if (mVoice[aVoice]->mChannels == 4)
			{
				mVoice[aVoice]->mChannelVolume[2] = l;
				mVoice[aVoice]->mChannelVolume[3] = r;
			}
			if (mVoice[aVoice]->mChannels == 6)
			{
				mVoice[aVoice]->mChannelVolume[2] = 1.0f / (float)sqrt(2.0f);
				mVoice[aVoice]->mChannelVolume[3] = 1;
				mVoice[aVoice]->mChannelVolume[4] = l;
				mVoice[aVoice]->mChannelVolume[5] = r;
			}
			if (mVoice[aVoice]->mChannels == 8)
			{
				mVoice[aVoice]->mChannelVolume[2] = 1.0f / (float)sqrt(2.0f);
				mVoice[aVoice]->mChannelVolume[3] = 1;
				mVoice[aVoice]->mChannelVolume[4] = l;
				mVoice[aVoice]->mChannelVolume[5] = r;
				mVoice[aVoice]->mChannelVolume[6] = l;
				mVoice[aVoice]->mChannelVolume[7] = r;
			}
		}
	}

	void Soloud::setVoiceVolume_internal(unsigned int aVoice, float aVolume)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		mActiveVoiceDirty = true;
		if (mVoice[aVoice])
		{
			mVoice[aVoice]->mSetVolume = aVolume;
			updateVoiceVolume_internal(aVoice);
		}
	}

	void Soloud::stopVoice_internal(unsigned int aVoice)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		mActiveVoiceDirty = true;
		if (mVoice[aVoice])
		{
			// Delete via temporary variable to avoid recursion
			AudioSourceInstance * v = mVoice[aVoice];
			mVoice[aVoice] = 0;

			unsigned int i;
			for (i = 0; i < mMaxActiveVoices; i++)
			{
				if (mResampleDataOwner[i] == v)
				{
					mResampleDataOwner[i] = NULL;
				}
			}

			delete v;
		}
	}

	void Soloud::updateVoiceRelativePlaySpeed_internal(unsigned int aVoice)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		mVoice[aVoice]->mOverallRelativePlaySpeed = m3dData[aVoice].mDopplerValue * mVoice[aVoice]->mSetRelativePlaySpeed;
		mVoice[aVoice]->mSamplerate = mVoice[aVoice]->mBaseSamplerate * mVoice[aVoice]->mOverallRelativePlaySpeed;
	}

	void Soloud::updateVoiceVolume_internal(unsigned int aVoice)
	{
		SOLOUD_ASSERT(aVoice < VOICE_COUNT);
		SOLOUD_ASSERT(mInsideAudioThreadMutex);
		mVoice[aVoice]->mOverallVolume = mVoice[aVoice]->mSetVolume * m3dData[aVoice].m3dVolume;
		if (mVoice[aVoice]->mFlags & AudioSourceInstance::PAUSED)
		{
			int i;
			for (i = 0; i < MAX_CHANNELS; i++)
			{
				mVoice[aVoice]->mCurrentChannelVolume[i] = mVoice[aVoice]->mChannelVolume[i] * mVoice[aVoice]->mOverallVolume;
			}
		}
	}
}
