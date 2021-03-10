// SPDX-License-Identifier: GPL-3.0-only

/*
This is a "hack" header to fool third party code to use our File stuff instead
of stdio FILE* stuff.
You can use soloud_file_hack_off.h to undef the stuff defined here.
*/

#ifndef SEEK_SET
#error soloud_file_hack_on must be included after stdio, otherwise the #define hacks will break stdio.
#endif

typedef void* Soloud_Filehack;

#ifdef __cplusplus
extern "C" {
#endif

extern int Soloud_Filehack_fgetc(Soloud_Filehack *f);
extern int Soloud_Filehack_fread(void *dst, int s, int c, Soloud_Filehack *f);
extern int Soloud_Filehack_fseek(Soloud_Filehack *f, int idx, int base);
extern int Soloud_Filehack_ftell(Soloud_Filehack *f);
extern int Soloud_Filehack_fclose(Soloud_Filehack *f);
extern Soloud_Filehack * Soloud_Filehack_fopen(const char *aFilename, char *aMode);
extern int Soloud_Filehack_fopen_s(Soloud_Filehack **f, const char* aFilename, char* aMode);

#ifdef __cplusplus
}
#endif

#define FILE Soloud_Filehack
#define fgetc Soloud_Filehack_fgetc
#define fread Soloud_Filehack_fread
#define fseek Soloud_Filehack_fseek
#define ftell Soloud_Filehack_ftell
#define fclose Soloud_Filehack_fclose
#define fopen Soloud_Filehack_fopen
#define fopen_s Soloud_Filehack_fopen_s
