#ifndef LOGGER_H_
#define LOGGER_H_

void setLogfile(char * fname);
int logger(const char * format, ...);
int logsuccess(const char * format, ...);
int logalert(const char * format, ...);
int logwarn(const char * format, ...);
void logbroke(const char * format, ...);
void closeLogger();

#endif