/******************************************************************************

GHAAS Command Line Library V1.0
Global Hydrologic Archive and Analysis System
Copyright 1994-2016, UNH - CCNY/CUNY

cm.c

bfekete@ccny.cuny.edu

*******************************************************************************/

#ifndef _CM_H
#define _CM_H

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#if defined(__cplusplus)
extern "C" {
#else

#include <stdbool.h>

#endif

typedef enum {
    CMsucceeded = 0, CMfailed = -1
} CMreturn;

#define CMargTest(arg, shortArg, longArg) ((strcmp(arg,shortArg)==0)||(strcmp(arg,longArg)==0))

typedef enum {
    CMmsgSysError = 0, CMmsgAppError = 1, CMmsgUsrError = 2, CMmsgDebug = 3, CMmsgWarning = 4, CMmsgInfo = 5
} CMmsgType;

const char *CMfileName(const char *);

const char *CMfileExtension(const char *);

int CMargShiftLeft(int, char **, int);

int CMoptLookup(const char **, const char *, bool);

void CMoptPrintList(CMmsgType, const char *, const char *[]);

bool CMmsgSetStreamFile(CMmsgType, const char *);

void CMmsgSetStream(CMmsgType, FILE *);

void CMmsgSetStatus(CMmsgType, bool);

int CMmsgPrint(CMmsgType, const char *, ...);

void CMmsgIndent(CMmsgType, bool);

void CMmsgCloseStream(CMmsgType);

void CMmsgCloseAllStreams();

char *CMstrAppend(char *, const char *, const char *);

char *CMstrDuplicate(const char *);

char *CMbufGetLine(char *, int *, FILE *);

char *CMbufTrim(char *);

char *CMbufStripChar(char *, char);

#define CMbufStripDQuotes(buffer) (CMbufStripChar (buffer,'\"'))
#define CMbufStripSQuotes(buffer) (CMbufStripChar (buffer,'\''))

#define CMmathEpsilon 0.01

bool CMmathEqualValues(double, double);

bool CMmathIsInteger(const char *);

#define CMmathMinimum(a, b) (((a) < (b)) ? (a) : (b))
#define CMmathMaximum(a, b) (((a) > (b)) ? (a) : (b))
#define CMyesNoString(cond) (cond ? "yes" : "no")

typedef struct CMthreadData_s {
    size_t    Id;
    pthread_t Thread;
    void *TeamPtr;
    clock_t Time;
} CMthreadData_t, *CMthreadData_p;

typedef struct CMthreadTeam_s {
    CMthreadData_p Threads;
    size_t ThreadNum;
    pthread_mutex_t SMutex, MMutex;
    pthread_cond_t  SCond,  MCond;
    void *JobPtr;
    long long TotTime, ExecTime, ThreadTime, Time;
} CMthreadTeam_t, *CMthreadTeam_p;

CMthreadTeam_p CMthreadTeamInitialize(CMthreadTeam_p, size_t threadNum);

void CMthreadTeamDestroy(CMthreadTeam_p);

size_t CMthreadProcessorNum();

typedef void  (*CMthreadUserExecFunc)(size_t, size_t, void *);

typedef struct CMthreadTask_s {
    size_t Id;
    size_t Travel, Rank;
    struct CMthreadTask_s *Dependent;
} CMthreadTask_t, *CMthreadTask_p;

typedef struct CMthreadTaskGroup_s {
    size_t Start;
    size_t End;
    size_t RankCount;
    size_t TravelCount;
} CMthreadTaskGroup_t, *CMthreadTaskGroup_p;

typedef struct CMthreadJob_s {
    bool Sorted;
    CMthreadTask_p Tasks;
    CMthreadTask_p *SortedTasks;
    CMthreadTaskGroup_p Groups;
    size_t TaskNum;
    size_t GroupNum;
    size_t Group;
    size_t Completed;
    CMthreadUserExecFunc UserFunc;
    void *CommonData;
} CMthreadJob_t, *CMthreadJob_p;

CMthreadJob_p CMthreadJobCreate(size_t, CMthreadUserExecFunc, void *);

void CMthreadJobDestroy(CMthreadJob_p);

CMreturn CMthreadJobExecute(CMthreadTeam_p, CMthreadJob_p);

CMreturn CMthreadJobTaskDependent(CMthreadJob_p, size_t, size_t);

#if defined(__cplusplus)
}
#endif

#endif
