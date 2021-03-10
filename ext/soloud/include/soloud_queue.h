// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_QUEUE_H
#define SOLOUD_QUEUE_H

#include "soloud.h"

#define SOLOUD_QUEUE_MAX 32

namespace SoLoud
{
	class Queue;

	class QueueInstance : public AudioSourceInstance
	{
		Queue *mParent;
	public:
		QueueInstance(Queue *aParent);
		virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize);
		virtual bool hasEnded();
		virtual ~QueueInstance();
	};

	class Queue : public AudioSource
	{
	public:
		Queue();
		virtual QueueInstance *createInstance();
		// Play sound through the queue
		result play(AudioSource &aSound);
        // Number of audio sources queued for replay
        unsigned int getQueueCount();
		// Is this audio source currently playing?
		bool isCurrentlyPlaying(AudioSource &aSound);
		// Set params by reading them from an audio source
		result setParamsFromAudioSource(AudioSource &aSound);
		// Set params manually
		result setParams(float aSamplerate, unsigned int aChannels = 2);
		
	public:
	    unsigned int mReadIndex, mWriteIndex, mCount;
	    AudioSourceInstance *mSource[SOLOUD_QUEUE_MAX];
		QueueInstance *mInstance;
		handle mQueueHandle;
		void findQueueHandle();
		
	};
};

#endif