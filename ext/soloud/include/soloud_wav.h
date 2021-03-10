// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_WAV_H
#define SOLOUD_WAV_H

#include "soloud.h"

struct stb_vorbis;

namespace SoLoud
{
	class Wav;
	class File;
	class MemoryFile;

	class WavInstance : public AudioSourceInstance
	{
		Wav *mParent;
		unsigned int mOffset;
	public:
		WavInstance(Wav *aParent);
		virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize);
		virtual result rewind();
		virtual bool hasEnded();
	};

	class Wav : public AudioSource
	{
		result loadwav(MemoryFile *aReader);
		result loadogg(MemoryFile *aReader);
		result loadmp3(MemoryFile *aReader);
		result loadflac(MemoryFile *aReader);
		result testAndLoadFile(MemoryFile *aReader);
	public:
		float *mData;
		unsigned int mSampleCount;

		Wav();
		virtual ~Wav();
		result load(const char *aFilename);
		result loadMem(const unsigned char *aMem, unsigned int aLength, bool aCopy = false, bool aTakeOwnership = true);
		result loadFile(File *aFile);
		result loadRawWave8(unsigned char *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1);
		result loadRawWave16(short *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1);
		result loadRawWave(float *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1, bool aCopy = false, bool aTakeOwnership = true);

		virtual AudioSourceInstance *createInstance();
		time getLength();
	};
};

#endif
