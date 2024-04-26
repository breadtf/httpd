/*                                                            Error message module for libwww
                       REPORTING ERRORS AND MESSAGES TO THE CLIENT
                                             
   This module maintaines a list of error messages that might occur during load of a
   requested URL. The error list is put out to standard output by a simple function that
   easily can be overwritten by a smart server or client. The module is a part of the CERN
   Common WWW Library.
   
   _Note: _At the moment, HTErrorMsg() is called, if the flag HTRequest->error_block is
   set to YES, then a stream has been put up or taken down in the library and therefore it
   is _VERY_ unsafe to put anything more to the stream.
   
 */
#ifndef HTERROR_H
#define HTERROR_H
#include "HTAccess.h"
/*

DATA STRUCTURES

   The basic data structure is HTErrorInfo, but in addition the following types are used:
   
  Error Numbers
  
   _Note: _All non-HTTP error codes have index numbers > HTERR_HTTP_CODES, and they will
   not be shown in the error-message generated.
   
 */
typedef enum _HTErrorElement {
        HTERR_OK = 0,                                           /* 200 */
        HTERR_CREATED,                                          /* 201 */
        HTERR_ACCEPTED,                                         /* 202 */
        HTERR_PARTIAL,                                          /* 203 */
        HTERR_NO_RESPONSE,                                      /* 204 */
        HTERR_MOVED,                                            /* 301 */
        HTERR_FOUND,                                            /* 302 */
        HTERR_METHOD,                                           /* 303 */
        HTERR_NOT_MODIFIED,                                     /* 304 */
        HTERR_BAD_REQUEST,                                      /* 400 */
        HTERR_UNAUTHORIZED,                                     /* 401 */
        HTERR_PAYMENT_REQUIRED,                                 /* 402 */
        HTERR_FORBIDDEN,                                        /* 403 */
        HTERR_NOT_FOUND,                                        /* 404 */
        HTERR_INTERNAL,                                         /* 500 */
        HTERR_NOT_IMPLEMENTED,                                  /* 501 */
        HTERR_HTTP_CODES_END,    /* Put all non-HTTP status codes after this */
        HTERR_NO_REMOTE_HOST,
        HTERR_NO_HOST,
        HTERR_FTP_SERVER,
        HTERR_FTP_NO_RESPONSE,
        HTERR_TIME_OUT,
        HTERR_GOPHER_SERVER,
        HTERR_INTERRUPTED,
        HTERR_CON_INTR,
        HTERR_CSO_SERVER,
        HTERR_BAD_REPLY,                                        /* HTTP */
        HTERR_NEWS_SERVER,
        HTERR_FILE_TO_FTP,
        HTERR_MAX_REDIRECT,
        HTERR_WAIS_OVERFLOW,
        HTERR_WAIS_MODULE,
        HTERR_WAIS_NO_CONNECT,
        HTERR_SYSTEM,
        HTERR_ELEMENTS                      /* This MUST be the last element */
} HTErrorElement;

typedef enum _HTErrSeverity {
    ERR_FATAL             = 0x1,
    ERR_NON_FATAL         = 0x2,
    ERR_WARNING           = 0x4,
    ERR_INFO              = 0x8
} HTErrSeverity;

typedef struct _HTErrorInfo {
    int                 handle;         /* Unique number in this stack */
    HTErrorElement      element;        /* Index number into HTErrorMsgInfo */
    HTErrSeverity       severity;       /* A la VMS */
    BOOL                ignore;         /* YES if msg should not go to user */
    void *              par;            /* Explanation, e.g. filename  */
    unsigned int        par_length;     /* For copying by generic routine */
    char *              where;          /* Which function */
} HTErrorInfo;
/*

CONTROLING GLOBALS

   This variable dictates which errors should be put out when generating the message to
   the user. The first four enumerations make it possible to see `everything as bad or
   worse than' this level, e.g. HT_ERR_SHOW_NON_FATAL shows messages of type
   HT_ERR_SHOW_NON_FATAL and HT_ERR_SHOW_FATAL.
   
   _Note:_ The default value is made so that it only puts a message to stderrif a `real'
   error has occurred. If a separate widget is available for information and error
   messages then probably HT_ERR_SHOW_DETAILED would be more appropriate.
   
 */
typedef enum _HTErrorShow {
    HT_ERR_SHOW_FATAL     = 0x1,
    HT_ERR_SHOW_NON_FATAL = 0x3,
    HT_ERR_SHOW_WARNING   = 0x7,
    HT_ERR_SHOW_INFO      = 0xF,
    HT_ERR_SHOW_PARS      = 0x10,
    HT_ERR_SHOW_LOCATION  = 0x20,
    HT_ERR_SHOW_IGNORE    = 0x40,
    HT_ERR_SHOW_FIRST     = 0x80,
    HT_ERR_SHOW_LINKS     = 0x100,
    HT_ERR_SHOW_DEFAULT   = 0x13,
    HT_ERR_SHOW_DETAILED  = 0x1F,
    HT_ERR_SHOW_DEBUG     = 0x7F
} HTErrorShow;

extern unsigned int HTErrorShowMask;
/*

   This is the table containing the actual error-messages and links for more information:
   
 */
typedef struct _HTErrorMsgInfo {
    int         code;                   /* Error number */
    char *      msg;                    /* Short explanation */
    char *      url;                    /* Explaning URL */
} HTErrorMsgInfo;

extern HTErrorMsgInfo error_info[];
/*

PUBLIC ERROR FUNCTIONS

  Add an Error Message
  
   This function adds an error message to the error_stack list in the HTRequest structure.
   It always returns a negative value.
   
 */
extern int HTErrorAdd PARAMS((  HTRequest *     request,
                                HTErrSeverity   severity,
                                BOOL            ignore,
                                int             element,
                                void *          par,
                                unsigned int    par_length,
                                char *          where));
/*

  Add a System Error Message
  
   This function adds an error from a system call that initializes errno or equivalent and
   adds it to the error_stack list in the HTRequest structure. It always returns a
   negative value.
   
 */
extern int HTErrorSysAdd PARAMS(( HTRequest *   request,
                                  HTErrSeverity severity,
                                  BOOL          ignore,
                                  char *        syscall));
/*

  Ignoring an Error Message
  
   If an error message is not to be send to the user, e.g., output to the stream, then the
   ignore flag must be turn on. Theese functions turns it on for the latest error appended
   to the list or an arbitrary error refered to by its handle.
   
 */
extern void HTErrorIgnore PARAMS((HTRequest * request, int handle));
extern void HTErrorIgnoreLast PARAMS((HTRequest * request));
/*

  Handling Prefix for Links in Error Message
  
   Two functions handle the URL prefix of the links inside the error message. They are
   quite obvious:
   
 */
PUBLIC void HTErrorSetPrefix PARAMS((char *path));
PUBLIC CONST char *HTErrorGetPrefix NOPARAMS;
/*

  Generating an Error Message (default to standard error)
  
   This function outputs the content of the error_stack to standard output (used in Line
   Mode Browser), but smart clients and servers might overwrite this function so that the
   error messages can be handled to the user in a nice way. That is the reason for putting
   the actual implementation in HTErrorMsg.c, that can be overwritten by clients and
   servers apart from Line Mode Browser.
   
   _Note: _If a stream hasbeen put up (and maybe taken down again) inside the Library,
   then request->error_block has been set to YES. This indicates that it is NOT possible
   any more to use the stream as output for the message.
   
 */
PUBLIC void HTErrorMsg    PARAMS((HTRequest * request));
/*

  Find an Error URL
  
 */
extern char * HTError_findUrl (int code);
extern BOOL HTError_addUrl (int code, CONST char * url);
extern BOOL HTError_deleteUrl (int code);
/*

  Freeing an Error List
  
   This is normally done when the HTRequest structure is freed but it might be done at any
   other time in order to ignore a whole series of errors.
   
 */
PUBLIC void HTErrorFree   PARAMS((HTRequest * request));
/*

 */
#endif
/*

   end */
