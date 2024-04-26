/*                                                            CACHE MANAGER FOR GATEWAY HTTPD
                             CACHE MANAGER FOR GATEWAY HTTPD
                                             
 */
/*
**      (c) COPYRIGHT MIT 1995.
**      Please first read the full copyright statement in the file COPYRIGH.
*/
/*

 */
/*
** AUTHORS:
**      AL      Ari Luotonen    luotonen@dxcern.cern.ch
**
*/

#ifndef HTCACHE_H
#define HTCACHE_H

#define CACHE_INFO      ".cache_info"
#define INDEX_FILE      ".cache_dirindex"
#define WELCOME_FILE    ".cache_welcome"
#define TMP_SUFFIX      ".cache_tmp"
#define LOCK_SUFFIX     ".cache_lock"
#define INFO_LINE_LEN   256

#include "HTUtils.h"
#include "HTStream.h"

typedef enum _HTCacheTask {
    CACHE_NO = 0,
    CACHE_FOUND,
    CACHE_IF_MODIFIED,
    CACHE_CREATE
} HTCacheTask;

/*
**      Look up a cache filename for url
**
** On entry:
**      url     for which we need the cache.
**      cfn     must point to valid char* storage.
**
** On exit:
**      returns CACHE_NO        if cache file doesn't exist nor should
**                              it be created.
**
**              CACHE_FOUND     if cache file exists, and *cfn the name of
**                              the file from which document can be read.
**
**              CACHE_IF_MODIFIED if cache file exists but may be out of date.
**                              Caller should do a conditional GET with
**                              If-Modified-Since header, *if_ms is the date.
**                              *cfn is the cache file name and *cf is an
**                              open lockfile to which document should be
**                              written if it has expired.  After that
**                              one of functions cache_not_modified(),
**                              cache_created() or cache_cancel() should
**                              be called.
**
**              CACHE_CREATE    if cache file didn't exist but should be
**                              created.  *cfn is the cache file name and
**                              *cf is an open lock file to write the document
**                              to.  After this either cache_created() or
**                              cache_cancel() should be called.
*/
PUBLIC HTCacheTask cache_lookup PARAMS((char *          url,
                                        char **         cfn,
                                        FILE **         cf,
                                        time_t *        if_ms,
                                        time_t *        expires));

PUBLIC HTStream * HTProxyCache PARAMS((HTStream *       output_stream,
                                       FILE *           cf,
                                       char *           cfn,
                                       char *           url,
                                       time_t           if_ms));

PUBLIC void gc NOPARAMS;

PUBLIC int HTExitStatusToKilos PARAMS((int status));
PUBLIC int HTBytesToExitStatus PARAMS((long bytes));

PUBLIC void HTLoadCacheToStream PARAMS((FILE *          fp,
                                        HTStream *      sink,
                                        time_t          expires));

PUBLIC FILE * HTCacheInfo_open PARAMS((char * dirname,
                                       char * mode));

PUBLIC FILE * HTCacheInfo_openFor PARAMS((char * filename,
                                          char * mode));

PUBLIC void HTCacheInfo_remove PARAMS((char * dirname));

PUBLIC BOOL HTCacheInfo_next PARAMS((FILE *     fp,
                                     char **    filename_p,
                                     time_t *   load_delay,
                                     time_t *   last_checked,
                                     time_t *   expires,
                                     time_t *   max_unused,
                                     time_t *   last_modified));

PUBLIC BOOL HTCacheInfo_for PARAMS((char *      filename,
                                    time_t *    load_delay,
                                    time_t *    last_checked,
                                    time_t *    expires,
                                    time_t *    max_unused,
                                    time_t *    last_modified));

PUBLIC void HTCacheInfo_writeEntry PARAMS((FILE *       fp,
                                           char *       filename,
                                           time_t       load_delay,
                                           time_t       last_checked,
                                           time_t       expires,
                                           time_t       max_unused,
                                           time_t       last_modified));

PUBLIC BOOL HTCacheInfo_writeEntryFor PARAMS((char *    filename,
                                              time_t    delay,
                                              time_t    last_chk,
                                              time_t    exp,
                                              time_t    max_unused,
                                              time_t    lm));

#endif

/*

   End of declaration module  */
