#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Added for timestamp

typedef struct logger
{
    int printEnabled;
    FILE* logfile;
    char* filename;

} Logger;

void setFile(Logger* logger, char* filename) {
    if (logger->logfile != NULL) {
        fclose(logger->logfile);
        free(logger->filename);
    }

    logger->filename = strdup(filename);
    logger->logfile = fopen(logger->filename, "a");
}

void logToFile(Logger logger, char* stringToLog) {
    if (logger.logfile != NULL) {
        time_t rawtime;
        struct tm* timeinfo;
        char timestamp[30]; // Room for timestamp like "[HH:MM:SS] "

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(timestamp, sizeof(timestamp), "[%F %H:%M:%S]", timeinfo);


        fprintf(logger.logfile, "%s %s \n",timestamp, stringToLog);

        if(logger.printEnabled){
            printf("%s %s\n",timestamp, stringToLog);
        }

        fflush(logger.logfile);
    }
}

