// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_FILTER_H
#define SOLOUD_FILTER_H

#include "soloud.h"

namespace SoLoud
{
	class Fader;

	class FilterInstance
	{
	public:
		unsigned int mNumParams;
		unsigned int mParamChanged;
		float *mParam;
		Fader *mParamFader;
		

		FilterInstance();
		virtual result initParams(int aNumParams);
		virtual void updateParams(time aTime);
		virtual void filter(float *aBuffer, unsigned int aSamples, unsigned int aBufferSize, unsigned int aChannels, float aSamplerate, time aTime);
		virtual void filterChannel(float *aBuffer, unsigned int aSamples, float aSamplerate, time aTime, unsigned int aChannel, unsigned int aChannels);
		virtual float getFilterParameter(unsigned int aAttributeId);
		virtual void setFilterParameter(unsigned int aAttributeId, float aValue);
		virtual void fadeFilterParameter(unsigned int aAttributeId, float aTo, time aTime, time aStartTime);
		virtual void oscillateFilterParameter(unsigned int aAttributeId, float aFrom, float aTo, time aTime, time aStartTime);
		virtual ~FilterInstance();
	};

	class Filter
	{
	public:
		enum PARAMTYPE
		{
			FLOAT_PARAM = 0,
			INT_PARAM,
			BOOL_PARAM
		};
		Filter();
		virtual int getParamCount();
		virtual const char* getParamName(unsigned int aParamIndex);
		virtual unsigned int getParamType(unsigned int aParamIndex);
		virtual float getParamMax(unsigned int aParamIndex);
		virtual float getParamMin(unsigned int aParamIndex);

		virtual FilterInstance *createInstance() = 0;
		virtual ~Filter();
	};
};

#endif
