/*                                                                   Wildcard Matching Module
                                 WILDCARD MATCHING MODULE
                                             
 */
/*
**      (c) COPYRIGHT MIT 1995.
**      Please first read the full copyright statement in the file COPYRIGH.
*/
/*

 */
/*
 * Author:
 *      Ari Luotonen, CERN, April 1994,
 *
 * This interface contains the following functions:
 *
 *      HTPattern_new(str)
 *              returns an internal representation (HTPattern *) for
 *              a given a string.  This can be used when later comparing
 *              actual strings against templates.
 *              Asterisk * means any character.
 *              Any character can be escaped by preceding it with a
 *              backslash; at least * and \ must be escaped when they
 *              should be taken literally, but all other escapes are
 *              also understood.
 *
 *      HTPattern_free(pat)
 *              frees the memory taken up by the pattern pat.
 *
 *      HTPattern_match(pat,eqv,act)
 *              matches the actual string act against pattern pat.
 *              If the pattern eqv is non-NULL the result returned
 *              will be a new string where the string is mapped to
 *              pattern eqv.  If eqv is NULL, a copy of the actual
 *              string is returned.
 *              If act doesn't match the pattern NULL is returned.
 *              NOTE: /~ in the beginning must be explicitly matched.
 *
 *      HTPattern_firstWild(pat,act)
 *              takes a pattern and a string matching that pattern,
 *              and returns a pointer inside the string to the first
 *              character matched by the first wildcard in pattern.
 *              IMPORTANT: string really has to match the pattern,
 *              i.e. it must have HTPattern_match()'ed before.
 *
 *      HTPattern_url_match(pat,url)
 *              takes a pattern and a URL-escaped URL, and matches
 *              an unescaped version of URL against the pattern;
 *              returns YES on match, NO on mismatch.
 *
 *      The datatype HTPattern should be treated as an abstract datatype.
 */

#ifndef HTWILD_H
#define HTWILD_H

#include "HTUtils.h"

typedef struct _HTPattern {
    BOOL                wild;   /* If wildcard before this text */
    char *              text;   /* Required text after wildcard */
    struct _HTPattern * next;   /* Next required text portion */
} HTPattern;

PUBLIC HTPattern * HTPattern_new PARAMS((CONST char * str));
PUBLIC void        HTPattern_free PARAMS((HTPattern * pat));
PUBLIC char *      HTPattern_match PARAMS((HTPattern *  pat,
                                           HTPattern *  eqv,
                                           CONST char * act));
PUBLIC char *      HTPattern_firstWild PARAMS((HTPattern * pat,
                                               char *      act));
PUBLIC BOOL HTPattern_url_match PARAMS((HTPattern *     pat,
                                        CONST char *    url));

#endif /* HTWILD_H */

/*

   End of declaration module  */
