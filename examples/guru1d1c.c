// this is all you must include for the finufft lib...
#include <finufft.h>

// specific to this example...
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

int main(int argc, char* argv[])
/* Example calling guru interface to FINUFFT library from C, using
   C complex type, with a math check. Barnett 6/22/20.

   Compile on linux with:
   gcc-7 -fopenmp guru1d1c.c -I../include ../lib-static/libfinufft.a -o guru1d1c  -lfftw3 -lfftw3_omp -lm -lstdc++

   Or if you have built a single-core library, remove -fopenmp and -lfftw3_omp

   Usage: ./guru1d1c.  See also: guru1d1
*/
{
  int M = 1e6;            // number of nonuniform points
  int N = 1e6;            // number of modes
  double tol = 1e-9;      // desired accuracy

  int type = 1, dim = 1;     // 1d1
  BIGINT Ns[3];              // guru describes mode array by vector [N1,N2..]
  int ntransf = 1;           // we want to do a single transform at a time
  BIGINT j,m,nout;
  int ier;
  double *x,err,Fmax,aF;
  double complex *c,*F,Ftest;

  nufft_opts* popts;         // pointer to opts struct
  finufft_plan* pplan;       // pointer to (also C-compatible) plan struct
  pplan = (finufft_plan *)malloc(sizeof(finufft_plan));     // allocate it
  Ns[0] = N;                 // mode numbers for plan
  int changeopts = 0;        // do you want to try changing opts? 0 or 1
  if (changeopts) {          // demo how to change options away from defaults..
    popts = (nufft_opts *)malloc(sizeof(nufft_opts));         // allocate it
    finufft_default_opts(popts);
    popts->debug = 1;        // example options change
    finufft_makeplan(type, dim, Ns, +1, ntransf, tol, pplan, popts);
  } else                     // or, NULL here means use default opts...
    finufft_makeplan(type, dim, Ns, +1, ntransf, tol, pplan, NULL);
  
  // generate some random nonuniform points
  x = (double *)malloc(sizeof(double)*M);
  for (j=0; j<M; ++j)
    x[j] = M_PI*(2*((double)rand()/RAND_MAX)-1);  // uniform random in [-pi,pi)
  finufft_setpts(pplan, M, x, NULL, NULL, 0, NULL, NULL, NULL);
  
  // generate some complex strengths
  c = (double complex*)malloc(sizeof(double complex)*M);
  for (j=0; j<M; ++j)
    c[j] = 2*((double)rand()/RAND_MAX)-1 + I*(2*((double)rand()/RAND_MAX)-1);

  // alloc output array for the Fourier modes, then do the transform
  F = (double complex*)malloc(sizeof(double complex)*N);
  ier = finufft_exec(pplan, c, F);

  // for fun, do another with same NU pts (no re-sorting), but new strengths...
  for (j=0; j<M; ++j)
    c[j] = 2*((double)rand()/RAND_MAX)-1 + I*(2*((double)rand()/RAND_MAX)-1);
  ier = finufft_exec(pplan, c, F);

  finufft_destroy(pplan);    // done with transforms of this size

  // rest is math checking and reporting...
  int n = 142519;   // check the answer just for this mode
  Ftest = (0.0,0.0);
  for (j=0; j<M; ++j)
    Ftest += c[j] * cexp(I*(double)n*x[j]);
  nout = n+N/2;            // index in output array for freq mode n
  Fmax = 0.0;              // compute inf norm of F
  for (m=0; m<N; ++m) {
    aF = cabs(F[m]);
    if (aF>Fmax) Fmax=aF;
  }
  err = cabs(F[nout] - Ftest)/Fmax;
  printf("guru C-interface 1D type-1 NUFFT done. ier=%d, err in F[%d] rel to max(F) is %.3g\n",ier,n,err);

  free(x); free(c); free(F); free(popts); free(pplan);
  return ier>1;
}
