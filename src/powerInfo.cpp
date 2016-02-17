#include "powerInfo.h"

struct powerStat* measurePower()
{
    struct powerStat* powerdata;
    char buff[40];
    FILE *fp;

    powerdata = (struct powerStat*) malloc( sizeof (struct powerStat*));

    //  fetch data from dstat
    fp = popen ("dstat --time --power 1 1 | tail -n +3","r");
    fgets( buff, sizeof(buff), fp);
    powerdata->timeInfo = (char *)malloc( sizeof (char)*30);

    //  Update powerStat object with power data
    strcpy( powerdata->timeInfo, strtok (buff,"|"));
    strcpy( buff, strtok( NULL, "|"));
    powerdata->powerusage = atof(buff);

    return powerdata;
}

