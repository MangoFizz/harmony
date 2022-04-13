# SPDX-License-Identifier: GPL-3.0-only

set(SOLOUD_SOURCE_PATH ext/soloud)

# Core
set(SOLOUD_CORE_PATH ${SOLOUD_SOURCE_PATH}/core)
set(SOLOUD_CORE_SOURCES
	${SOLOUD_CORE_PATH}/soloud.cpp
	${SOLOUD_CORE_PATH}/soloud_audiosource.cpp
	${SOLOUD_CORE_PATH}/soloud_bus.cpp
	${SOLOUD_CORE_PATH}/soloud_core_3d.cpp
	${SOLOUD_CORE_PATH}/soloud_core_basicops.cpp
	${SOLOUD_CORE_PATH}/soloud_core_faderops.cpp
	${SOLOUD_CORE_PATH}/soloud_core_filterops.cpp
	${SOLOUD_CORE_PATH}/soloud_core_getters.cpp
	${SOLOUD_CORE_PATH}/soloud_core_setters.cpp
	${SOLOUD_CORE_PATH}/soloud_core_voicegroup.cpp
	${SOLOUD_CORE_PATH}/soloud_core_voiceops.cpp
	${SOLOUD_CORE_PATH}/soloud_fader.cpp
	${SOLOUD_CORE_PATH}/soloud_fft.cpp
	${SOLOUD_CORE_PATH}/soloud_fft_lut.cpp
	${SOLOUD_CORE_PATH}/soloud_file.cpp
	${SOLOUD_CORE_PATH}/soloud_filter.cpp
	${SOLOUD_CORE_PATH}/soloud_misc.cpp
	${SOLOUD_CORE_PATH}/soloud_queue.cpp
	${SOLOUD_CORE_PATH}/soloud_thread.cpp
)

# Audiosources
set(SOLOUD_AUDIOSOURCES_PATH ${SOLOUD_SOURCE_PATH}/audiosource)
set(SOLOUD_AUDIOSOURCES_SOURCES
	# wav
	${SOLOUD_AUDIOSOURCES_PATH}/wav/dr_impl.cpp
	${SOLOUD_AUDIOSOURCES_PATH}/wav/soloud_wav.cpp
	${SOLOUD_AUDIOSOURCES_PATH}/wav/soloud_wavstream.cpp
	${SOLOUD_AUDIOSOURCES_PATH}/wav/stb_vorbis.c
)

# WASAPI backend
add_definitions (-DWITH_WASAPI)
set(SOLOUD_WASAPI_BACKEND
	${SOLOUD_SOURCE_PATH}/backend/wasapi/soloud_wasapi.cpp
)

add_library(soloud STATIC 
	${SOLOUD_CORE_SOURCES}
	${SOLOUD_AUDIOSOURCES_SOURCES}
	${SOLOUD_WASAPI_BACKEND}
)

# Add include path
target_include_directories(soloud PRIVATE "${SOLOUD_SOURCE_PATH}/include")

# Add compile flags
set_target_properties(soloud PROPERTIES COMPILE_FLAGS "-msse3")
