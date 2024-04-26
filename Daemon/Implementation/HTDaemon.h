/*                                                             Calls back to HTDaemon program
                              CALLS BACK TO HTDAEMON PROGRAM
                                             
 */
/*
**      (c) COPYRIGHT MIT 1995.
**      Please first read the full copyright statement in the file COPYRIGH.
*/
/*

 */
#ifndef HTDAEMON_H
#define HTDAEMON_H

#include "HTSUtils.h"
#include "HTConfig.h"
#include "HTLog.h"


extern BOOL ignore_sigpipes;    /* Should we catch and ignore SIGPIPE   */
extern BOOL sigpipe_caught;     /* If so, have we caught a SIGPIPE      */

extern char *           HTClientProtocol;
extern int              HTServerPort;

extern char *           HTReasonLine;
extern int              HTSoc;
extern char *           HTReqLine;
extern char *           HTReqArg;
extern char *           HTReqArgPath;
extern char *           HTReqArgKeywords;
extern char *           HTReqTranslated;
extern char *           HTReqScript;
extern char *           HTScriptPathInfo;
extern char *           HTScriptPathTrans;
extern char *           HTLocation;
extern char *           HTLastModified;
extern char *           HTExpires;
extern char *           HTMetaFile;
extern char *           HTAuthString;
extern char *           HTWWWAuthenticate;
extern HTAAFailReason   HTReason;
extern char *           HTProxyHeaders;
extern char *           HTUserAgent;
extern char *           HTReferer;
extern time_t           HTIfModifiedSince;

extern char *           remote_ident;

extern long             HTCacheUsage;
extern int              HTChildExitStatus;
extern long             HTCachedBytes;
extern BOOL             proxy_access;
extern BOOL             cache_hit;
extern char *           gc_info_file;
extern time_t           cur_time;

extern BOOL             trace_cache;
extern BOOL             trace_all;
#define VTRACE          if(trace_all)fprintf


typedef struct _HTInStruct {
    BOOL        no_cache_pragma;
} HTInStruct;

typedef struct _HTOutStruct {
    int         status_code;
    int         header_length;
    int         content_length;
    BOOL        http_header_sent;
} HTOutStruct;

extern HTInStruct in;
extern HTOutStruct out;



/*
 *      These routines are used to send back appropriate
 *      protocol header fields preceding a message.
 */
void HTSendError PARAMS((int            soc,
                         int            number,
                         CONST char *   msg));

extern void HTSendHeader PARAMS((int            soc,
                                 HTFormat       rep));

int HTLoadRedirection PARAMS((HTRequest * req));
int HTCallScript PARAMS((HTRequest * req));
int HTRetrieve PARAMS((HTRequest * req));
int HTLoadHead PARAMS((HTRequest * req));
int HTPut PARAMS((HTRequest * req));
int HTAnnotate PARAMS((HTRequest * req));
int HTRequest_computeArgs PARAMS((HTRequest * req));
int HTLoadStrToStream PARAMS((HTStream *        sink,
                              CONST char *      str));
int HTCloseStream PARAMS((HTStream * sink));
int HTCopyBodyToFile PARAMS((HTRequest *        req,
                             FILE *             fp));

void compute_server_env NOPARAMS;

void output_timeout_on NOPARAMS;
void body_timeout_on NOPARAMS;
void script_timeout_on PARAMS((int pid));
void timeout_off NOPARAMS;

#endif
/*

   End of declaration module  */
