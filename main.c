//
// Created by alen on 17/2/13.
//
#include <stdio.h>
#include "pack.h"
int main() {
    char fileName[] = "/Users/alen/test_1.txt";
    unsigned char *pack1 = pack("lliils", -1486719955213,-1486719598184,12154526,-2993418,1486962486107,232);
    FILE *fp;
    remove(fileName);
    fp = fopen(fileName, "a+b");
    fwrite(pack1, 34, 1, fp);
    fclose(fp);
}

