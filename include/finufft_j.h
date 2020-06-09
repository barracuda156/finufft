#ifndef FINUFFT_J_H
#define FINUFFT_J_H

#include <dataTypes.h>
#include <finufft.h>

#ifdef __cplusplus
extern "C"
{
#endif

// This defines functions used in Julia interface

/* Note our typedefs:
   FLT = double (or float, depending on compilation precision)
   CPX = double complex (or float complex, depending on compilation precision)
   BIGINT = int64
   Make sure you call this library with matching Julia types
*/

// --------------- plan opaque pointer ------------
finufft_plan* finufft_plan_alloc();
void finufft_plan_free(finufft_plan* plan);
int get_type(finufft_plan* plan);
int get_ntransf(finufft_plan* plan);
int get_ndims(finufft_plan* plan);
void get_nmodes(finufft_plan* plan, BIGINT* n_modes);
BIGINT get_nj(finufft_plan* plan);
BIGINT get_nk(finufft_plan* plan);

#ifdef __cplusplus
}
#endif

#endif  // FINUFFT_J_H
