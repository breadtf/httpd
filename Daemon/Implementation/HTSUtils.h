/*                                                                    UTILITIES FOR W3C httpd
                                 UTILITIES FOR W3C HTTPD
                                             
 */
/*
**      (c) COPYRIGHT MIT 1995.
**      Please first read the full copyright statement in the file COPYRIGH.
*/
/*

 */
/*
 *
 * Author:
 *      AL      Ari Luotonen, CERN, 1994,
 *
 */

#ifndef HTSUTILS_H
#define HTSUTILS_H

#include "HTUtils.h"

#ifdef VMS
#define __TYPES
#include <types.h>
#include <time.h>
#define __TIME
#else /* not VMS */
#include <sys/types.h>

#ifdef ISC3    /* Lauren */
#define _SYSV3
#include <time.h>
#else
#include <sys/time.h>
#endif

#endif /* not VMS */

extern char * month_names[];            /* 3-letter month abbreviations */


/*
 * Does a string represent an integer
 */
PUBLIC BOOL HTIsNumber PARAMS((CONST char * s));

/*
 * Parse string representing date and time (in HTTP headers) into time_t
 */
PUBLIC time_t parse_http_time PARAMS((char * str));

/*
 * Convert time_t into a HTTP time string
 */
PUBLIC char * http_time PARAMS((time_t * t));

/*
 * parse_time(str,def,ret) parses a verbatim time specification in str
 * and places resulting time_t into *ret.  Time can be specified e.g.
 *      1 year 3 months 2 weeks 4 days 5 hours 7 mins 2 sec
 * or:  12:30:15
 * If just a plain number is given it is multiplied by def (result is
 * in seconds).
 */
PUBLIC BOOL parse_time PARAMS((char *   str,
                               int      def,
                               time_t * ret));

/*
 * Convert time_t into a verbose human-readable form (inverse to parse_time())
 */
PUBLIC char * make_time_spec PARAMS((time_t * t));

/*
 * Parses verbatim byte count in configuration file into a single integer.
 * Byte count is a number followed by B (byte), K (kilo), M (mega), G (giga).
 * If no letter is specified def is used.
 */
PUBLIC int parse_bytes PARAMS((char *   str,
                               char     def));

/*
 * Returns a HTTP reason line corresponding to given HTTP status code.
 */
PUBLIC char * get_http_reason PARAMS((int status_code));

#endif /* !HTSUTILS_H */

/*

   End of declaration module  */
