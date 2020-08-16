#ifndef __AFPRINTF_H__
#define __AFPRINTF_H__

#include <stdio.h>

#ifdef __cplusplus 
extern "C" {
#endif

typedef void(*print_handler)(FILE*, void*);
/**
 * \brief fprintf with custom type support
 * \param [in] f     File pointer
 * \param [in] fmt   Format string
 * \param [in] vargs Valuest to print
 *
 * Advanced fprintf can print any custom structure using substitution formatter "%Y" and callback
 * function to print custom structure to the FILE*.
 *
 * Example:
 * fprintf("My struct: %Y", FORMAT_MYSTRUCT(&mystruct))
 *
 * See example.c for more details */
void afprintf(FILE* f, const char* fmt, ...);


#ifdef __cplusplus
};
#endif

#endif
