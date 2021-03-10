// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_BUS_H
#define SOLOUD_BUS_H

#include "soloud.h"

namespace SoLoud
{
	class Bus;

	class BusInstance : public AudioSourceInstance
	{
		Bus *mParent;
		unsigned int mScratchSize;
		AlignedFloatBuffer mScratch;
	public:
		// Approximate volume for channels.
		float mVisualizationChannelVolume[MAX_CHANNELS];
		// Mono-mixed wave data for visualization and for visualization FFT input
		float mVisualizationWaveData[256];

		BusInstance(Bus *aParent);
		virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize);
		virtual bool hasEnded();
		virtual ~BusInstance();
	};

	class Bus : public AudioSource
	{
	public:
		Bus();
		virtual BusInstance *createInstance();
		// Set filter. Set to NULL to clear the filter.
		virtual void setFilter(unsigned int aFilterId, Filter *aFilter);
		// Play sound through the bus
		handle play(AudioSource &aSound, float aVolume = 1.0f, float aPan = 0.0f, bool aPaused = 0);
		// Play sound through the bus, delayed in relation to other sounds called via this function.
		handle playClocked(time aSoundTime, AudioSource &aSound, float aVolume = 1.0f, float aPan = 0.0f);
		// Start playing a 3d audio source through the bus
		handle play3d(AudioSource &aSound, float aPosX, float aPosY, float aPosZ, float aVelX = 0.0f, float aVelY = 0.0f, float aVelZ = 0.0f, float aVolume = 1.0f, bool aPaused = 0);
		// Start playing a 3d audio source through the bus, delayed in relation to other sounds called via this function.
		handle play3dClocked(time aSoundTime, AudioSource &aSound, float aPosX, float aPosY, float aPosZ, float aVelX = 0.0f, float aVelY = 0.0f, float aVelZ = 0.0f, float aVolume = 1.0f);
		// Set number of channels for the bus (default 2)
		result setChannels(unsigned int aChannels);
		// Enable or disable visualization data gathering
		void setVisualizationEnable(bool aEnable);
		// Move a live sound to this bus
		void annexSound(handle aVoiceHandle);
		
		// Calculate and get 256 floats of FFT data for visualization. Visualization has to be enabled before use.
		float *calcFFT();

		// Get 256 floats of wave data for visualization. Visualization has to be enabled before use.
		float *getWave();

		// Get approximate volume for output channel for visualization. Visualization has to be enabled before use.
		float getApproximateVolume(unsigned int aChannel);

		// Get number of immediate child voices to this bus
		unsigned int getActiveVoiceCount();

		// Get current the resampler for this bus
		unsigned int getResampler();
		// Set the resampler for this bus
		void setResampler(unsigned int aResampler);
	public:
		BusInstance *mInstance;
		unsigned int mChannelHandle;
		unsigned int mResampler;
		// FFT output data
		float mFFTData[256];
		// Snapshot of wave data for visualization
		float mWaveData[256];
		// Internal: find the bus' channel
		void findBusHandle();
	};
};

#endif