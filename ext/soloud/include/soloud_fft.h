// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_FFT_H
#define SOLOUD_FFT_H

#include "soloud.h"

namespace SoLoud
{
	namespace FFT
	{
		// Perform 1024 unit FFT. Buffer must have 1024 floats, and will be overwritten
		void fft1024(float *aBuffer);

		// Perform 256 unit FFT. Buffer must have 256 floats, and will be overwritten
		void fft256(float *aBuffer);
		
		// Perform 256 unit IFFT. Buffer must have 256 floats, and will be overwritten
		void ifft256(float *aBuffer);

		// Generic (slower) power of two FFT. Buffer is overwritten.
		void fft(float *aBuffer, unsigned int aBufferLength);

		// Generic (slower) power of two IFFT. Buffer is overwritten.
		void ifft(float *aBuffer, unsigned int aBufferLength);
	};
};

#endif