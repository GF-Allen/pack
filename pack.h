//pack.h
//By AlenBeyond
//library for pack and unpack c functions

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define TOLONGLONG(a, b, c, d, e, f, g, h) ((h << 56) + (g << 48) + (f << 40) + (e << 32) + (d << 24) + (c << 16) + (b << 8) + (a))
#define TOINT(a, b, c, d) ((d << 24) + (c << 16) + (b << 8) + (a))
#define TOSHORT(a, b) ((b << 8) + (a))

unsigned char *pack(unsigned char *a, ...);

unsigned char *append(unsigned char* ret,int pos,unsigned char *a, ...);

int unpack(unsigned char *a, unsigned char *data, ...);

int catInt(int pos, int endian, unsigned char *ret, int src);

int catLong(int pos, int endian, unsigned char *ret, long long src);

int catChar(int pos, unsigned char *ret, int src);

int catShort(int pos, int endian, unsigned char *ret, int src);
