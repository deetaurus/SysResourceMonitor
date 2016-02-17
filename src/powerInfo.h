#ifndef POWERINFO_H
#define POWERINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct powerStat    {
    char *timeInfo;
    float powerusage;
};

struct powerStat* measurePower();

#endif // POWERINFO_H
