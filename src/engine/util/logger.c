#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define BSHNRM  "\x1B[0m"
#define BSHRED  "\x1B[31m"
#define BSHGRN  "\x1B[32m"
#define BSHYEL  "\x1B[33m"
#define BSHBLU  "\x1B[34m"
#define BSHMAG  "\x1B[35m"
#define BSHCYN  "\x1B[36m"
#define BSHWHT  "\x1B[37m"

char * logfname; 

void setLogfile(char * fname){

    FILE * logFile = fopen(fname, "w+");
    fclose(logFile); 

    int n = strlen(fname);
    logfname = malloc(sizeof(char) * n);
    memcpy(logfname, fname, n);
}

int logger(const char * format, ...){
    va_list arg;
    int done;

    FILE * logFile = fopen(logfname, "a");

    va_start(arg, format);
    done = vfprintf(logFile, format, arg);
    va_end(arg);

    fclose(logFile);

    return done;
}

int logcolor(const char * color, const char * format, ...){
    va_list arg;
    int done;

    fprintf(stdout, "%s", color);
    va_start(arg, format);
    done = vfprintf(stdout, format, arg);
    va_end(arg);
    fprintf(stdout, "%s", color);

    return done;
}

int logsuccess(const char * format, ...){
    va_list arg;
    int done;



    va_start(arg, format);
    done = logcolor(BSHGRN, format, arg);
    va_end(arg);

    return done;
}

int logalert(const char * format, ...){
    va_list arg;
    int done;

    va_start(arg, format);
    done = logcolor(BSHBLU, format, arg);
    va_end(arg);

    return done;
}

int logwarn(const char * format, ...){
    va_list arg;
    int done;

    va_start(arg, format);
    done = logcolor(BSHYEL, format, arg);
    va_end(arg);

    return done;
}

void logbroke(const char * format, ...){
    va_list arg;

    va_start(arg, format);
    logcolor(BSHRED, format, arg);
    va_end(arg);

    exit(EXIT_FAILURE);
}

void closeLogger(){
    // fclose(logFile);
}