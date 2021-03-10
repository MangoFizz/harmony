// SPDX-License-Identifier: GPL-3.0-only

#ifndef SOLOUD_ERROR_H
#define SOLOUD_ERROR_H

namespace SoLoud
{
	enum SOLOUD_ERRORS
	{
		SO_NO_ERROR       = 0, // No error
		INVALID_PARAMETER = 1, // Some parameter is invalid
		FILE_NOT_FOUND    = 2, // File not found
		FILE_LOAD_FAILED  = 3, // File found, but could not be loaded
		DLL_NOT_FOUND     = 4, // DLL not found, or wrong DLL
		OUT_OF_MEMORY     = 5, // Out of memory
		NOT_IMPLEMENTED   = 6, // Feature not implemented
		UNKNOWN_ERROR     = 7  // Other error
	};
};
#endif