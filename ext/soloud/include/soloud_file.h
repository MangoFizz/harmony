// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_FILE_H
#define SOLOUD_FILE_H

#include <stdio.h>
#include "soloud.h"

typedef void* Soloud_Filehack;

namespace SoLoud
{
	class File
	{
	public:
		virtual ~File() {}
		unsigned int read8();
		unsigned int read16();
		unsigned int read32();
		virtual int eof() = 0;
		virtual unsigned int read(unsigned char *aDst, unsigned int aBytes) = 0;
		virtual unsigned int length() = 0;
		virtual void seek(int aOffset) = 0;
		virtual unsigned int pos() = 0;
		virtual FILE * getFilePtr() { return 0; }
		virtual const unsigned char * getMemPtr() { return 0; }
	};

	class DiskFile : public File
	{
	public:
		FILE *mFileHandle;

		virtual int eof();
		virtual unsigned int read(unsigned char *aDst, unsigned int aBytes);
		virtual unsigned int length();
		virtual void seek(int aOffset);
		virtual unsigned int pos();
		virtual ~DiskFile();
		DiskFile();
		DiskFile(FILE *fp);
		result open(const char *aFilename);
		virtual FILE * getFilePtr();
	};

	class MemoryFile : public File
	{
	public:
		const unsigned char *mDataPtr;
		unsigned int mDataLength;
		unsigned int mOffset;
		bool mDataOwned;

		virtual int eof();
		virtual unsigned int read(unsigned char *aDst, unsigned int aBytes);
		virtual unsigned int length();
		virtual void seek(int aOffset);
		virtual unsigned int pos();
		virtual const unsigned char * getMemPtr();
		virtual ~MemoryFile();
		MemoryFile();
		result openMem(const unsigned char *aData, unsigned int aDataLength, bool aCopy=false, bool aTakeOwnership=true);
		result openToMem(const char *aFilename);
		result openFileToMem(File *aFile);
	};
};

#endif
