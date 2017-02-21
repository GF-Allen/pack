//pack.c
//By: AlenBeyond

/************************************************************************
 * Description:
 *
 * pack.c impliements the libpack library.  This library is used for 
 * packing and unpacking binary data into character arrays in C.  
 * the implimentation requires an encoding string for both pack and 
 * unpack.  The string denotes what each variable is to be packed or
 * unpacked as. At this time only int, short, and char are implemented,
 * however additional functionaliy is easily added.
 *
 * encoding string values:
 *    l     long long (8 bytes)
 *    i     denotes an integer (4 bytes)
 *    s     denotes a short (2 bytes)
 *    c     denotes a char (1 byte)
 *    e     denotes little endian (applied after each instance)
 *    E     denotes big endian (applied after each instance)
 *
 ************************************************************************/

#include "pack.h"

/*************************************************************************
 * pack(unsigned char* a, ...)
 *
 * Parameters:
 *    a:       encoding string
 *    ... :    variables to be encoded
 *
 * Description:
 *    Packs the passed variables into a character array as specified by 
 *    the encoding string.
 *
 *************************************************************************/
unsigned char *pack(unsigned char *a, ...) {
    va_list ap;
    int i = 0;
    int pos = 0;
    unsigned char *ret = NULL;
    int endian = 0;
    int len = strlen((char *) a);
    va_start(ap, a);
    for (i = 0; i < len; i++) {
        switch (a[i]) {
            case 'e':
                //set mode to little endian
                endian = 0;
                break;
            case 'E':
                //set mode to big endian
                endian = 1;
                break;
            case 'i':
                //do int
                ret = (unsigned char *) realloc(ret, pos + 4);
                catInt(pos, endian, ret, va_arg(ap, int));
                pos = pos + 4;
                break;
            case 'l':
                // do long
                ret = (unsigned char *) realloc(ret, pos + 8);
                catLong(pos, endian, ret, va_arg(ap, long long));
                pos = pos + 8;
                break;
            case 's':
                //do short
                ret = (unsigned char *) realloc(ret, pos + 2);
                catShort(pos, endian, ret, va_arg(ap, int));
                pos = pos + 2;
                break;
            case 'c':
                //do char
                ret = (unsigned char *) realloc(ret, pos + 1);
                catChar(pos, ret, va_arg(ap, int));
                pos = pos + 1;
                break;
            case 'h'://字符串

                break;
            default:
                printf("unexpected input type\n");
        }
    }
    va_end(ap);
    return ret;
}

unsigned char *append(unsigned char* ret,int pos,unsigned char *a, ...) {
    va_list ap;
    int i = 0;
    int endian = 0;
    int len = strlen((char *) a);
    va_start(ap, a);
    for (i = 0; i < len; i++) {
        switch (a[i]) {
            case 'e':
                //set mode to little endian
                endian = 0;
                break;
            case 'E':
                //set mode to big endian
                endian = 1;
                break;
            case 'i':
                //do int
                ret = (unsigned char *) realloc(ret, pos + 4);
                catInt(pos, endian, ret, va_arg(ap, int));
                pos = pos + 4;
                break;
            case 'l':
                // do long
                ret = (unsigned char *) realloc(ret, pos + 8);
                catLong(pos, endian, ret, va_arg(ap, long long));
                pos = pos + 8;
                break;
            case 's':
                //do short
                ret = (unsigned char *) realloc(ret, pos + 2);
                catShort(pos, endian, ret, va_arg(ap, int));
                pos = pos + 2;
                break;
            case 'c':
                //do char
                ret = (unsigned char *) realloc(ret, pos + 1);
                catChar(pos, ret, va_arg(ap, int));
                pos = pos + 1;
                break;
            case 'h'://字符串

                break;
            default:
                printf("unexpected input type\n");
        }
    }
    va_end(ap);
    return ret;
}

/*************************************************************************
 * unpack(unsigned char* a, unsigned char* data, ...)
 *
 * Parameters:
 *    a:       encoding string
 *    data:    string of packed data
 *    ... :    pointers to destination variables
 *
 * Description:
 *    Unpacks the passed data string into variable pointers as specified 
 *    by the encoding string.
 *
 *************************************************************************/
int unpack(unsigned char *a, unsigned char *data, ...) {
    va_list ap;
    int i = 0;
    int len = strlen((char *) a);
    int pos = 0;
    int endian = 0;
    int *intarg = NULL;
    long long *longarg = NULL;
    char *charg = NULL;
    short *shortarg = NULL;
    va_start(ap, data);
    for (i = 0; i < len; i++) {
        switch (a[i]) {
            case 'e':
                endian = 0;
                break;
            case 'E':
                endian = 1;
                break;
            case 'i':
                //do int
                intarg = (int *) va_arg(ap, int);
                if (endian == 1) {
                    *intarg = TOINT(data[pos + 3], data[pos + 2], data[pos + 1], data[pos]);
                } else {
                    *intarg = TOINT(data[pos], data[pos + 1], data[pos + 2], data[pos + 3]);
                }
                pos = pos + 4;
                break;
            case 'l':
                longarg = (long long *) va_arg(ap, long long);
                if (endian == 1) {
                    *longarg = TOLONGLONG(data[pos + 7], data[pos + 6], data[pos + 5], data[pos + 4], data[pos + 3],
                                      data[pos + 2], data[pos + 1], data[pos]);
                } else {
                    *longarg = TOLONGLONG(data[pos], data[pos + 1], data[pos + 2], data[pos + 3], data[pos + 4],
                                      data[pos + 5], data[pos + 6], data[pos + 7]);
                }
                pos = pos + 8;
                break;
            case 's':
                //do short
                shortarg = (short *) va_arg(ap, int);
                if (endian == 1) {
                    *shortarg = TOSHORT(data[pos + 1], data[pos]);
                } else {
                    *shortarg = TOSHORT(data[pos], data[pos + 1]);
                }
                pos = pos + 2;
                break;
            case 'c':
                //do char
                charg = (char *) va_arg(ap, int);
                *charg = data[pos];
                pos = pos + 1;
                break;
            default:
                printf("unknown encoding type\n");
                return 1;
                break;
        }
    }
    va_end(ap);
    return 0;
}

int catInt(int pos, int endian, unsigned char *ret, int src) {
    if (endian == 1) {
        //big endian MSB first
        ret[pos] = (unsigned char) (src >> 24);
        ret[pos + 1] = (unsigned char) (src >> 16);
        ret[pos + 2] = (unsigned char) (src >> 8);
        ret[pos + 3] = (unsigned char) (src);
    } else {
        //little endian LSB first
        ret[pos + 3] = (unsigned char) (src >> 24);
        ret[pos + 2] = (unsigned char) (src >> 16);
        ret[pos + 1] = (unsigned char) (src >> 8);
        ret[pos] = (unsigned char) (src);
    }
    return 1;
}

int catLong(int pos, int endian, unsigned char *ret, long long src) {
    if (endian == 1) {
        //big endian MSB first
        ret[pos] = (unsigned char) (src >> 56);
        ret[pos + 1] = (unsigned char) (src >> 48);
        ret[pos + 2] = (unsigned char) (src >> 40);
        ret[pos + 3] = (unsigned char) (src >> 32);
        ret[pos + 4] = (unsigned char) (src >> 24);
        ret[pos + 5] = (unsigned char) (src >> 16);
        ret[pos + 6] = (unsigned char) (src >> 8);
        ret[pos + 7] = (unsigned char) (src);
    } else {
        //little endian LSB first
        ret[pos + 7] = (unsigned char) (src >> 56);
        ret[pos + 6] = (unsigned char) (src >> 48);
        ret[pos + 5] = (unsigned char) (src >> 40);
        ret[pos + 4] = (unsigned char) (src >> 32);
        ret[pos + 3] = (unsigned char) (src >> 24);
        ret[pos + 2] = (unsigned char) (src >> 16);
        ret[pos + 1] = (unsigned char) (src >> 8);
        ret[pos] = (unsigned char) (src);
    }
    return 1;
}

int catShort(int pos, int endian, unsigned char *ret, int src) {
    if (endian == 1) {
        //big endian MSB first
        ret[pos] = (unsigned char) (src >> 8);
        ret[pos + 1] = (unsigned char) (src);
    } else {
        //little endian LSB first
        ret[pos + 1] = (unsigned char) (src >> 8);
        ret[pos] = (unsigned char) (src);
    }
    return 1;
}

int catChar(int pos, unsigned char *ret, int src) {
    ret[pos] = (unsigned char) src;
    return 1;
}
