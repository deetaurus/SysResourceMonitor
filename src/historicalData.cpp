#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <glib.h>
#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
#include <time.h>

int generateHistoricalData();

void main()
{
    char filename[15];

//  TIME MODULE TO BE ADDED LATER
//    char temp[5];
//    time_t tim = time(NULL);
//    struct tm *now = localtime(&tim);
    pthread_t thread1;

    filename = "date";  // replace it with current date
    strcat( filename, ".his");

    pthread_create( &thread1, NULL, generateHistoricalData, (void*) ("x"));

    // Wait for other threads to exit
    pthread_join( thread1, NULL);

    return EXIT_SUCCESS;
}

int *generateHistoricalData(char *filename)
{
    FILE *fp = fopen( filename,"a");

    glibtop_init();

    glibtop_cpu cpu;
    glibtop_mem memory;

    glibtop_get_cpu (&cpu);
    glibtop_get_mem (&memory);
}

