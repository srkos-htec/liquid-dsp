//
// fft
//

#include <stdlib.h>
#include <math.h>

#include "fft_internal.h"

void fft_destroy_plan(fftplan _p)
{
    free(_p->twiddle);
    free(_p->index_rev);
    free(_p);
}

fftplan fft_create_plan(unsigned int _n, float complex * _x, float complex * _y, int _dir)
{
    fftplan p = (fftplan) malloc(_n*sizeof(struct fftplan_s));

    p->n = _n;
    p->x = _x;
    p->y = _y;

    if (_dir == FFT_FORWARD)
        p->direction = FFT_FORWARD;
    else
        p->direction = FFT_REVERSE;

    p->twiddle = NULL;
    p->index_rev = NULL;

    p->is_radix2 = false;

    // check to see if _n is radix 2
    unsigned int i, d=0, m=0, t=p->n;
    for (i=0; i<8*sizeof(unsigned int); i++) {
        d += (t & 1);           // count bits, radix-2 if d==1
        if (!m && (t&1)) m = i; // count lagging zeros, effectively log2(n)
        t >>= 1;
    }

    // initialize twiddle factors, etc.
    if (_n <= FFT_SIZE_LUT ) {
        fft_init_lut(p);
    } else if (d==1) {
        // radix-2
        p->is_radix2 = true;
        p->m = m;
        fft_init_radix2(p);
    }

    return p;
}

// initialize twiddle factors using plain look-up table
void fft_init_lut(fftplan _p)
{
    unsigned int k, n, N = _p->n;
    _p->twiddle = (float complex*) malloc(N*N*sizeof(float complex));
    float phi, d = (_p->direction==FFT_FORWARD) ? -1 : 1;
    for (k=0; k<N; k++) {
        for (n=0; n<N; n++) {
            phi = 2*M_PI*d*((float)n)*((float)k) / (float) (N);
            _p->twiddle[k*N + n] = cexpf(_Complex_I*phi);
        }   
    }   
}

void fft_init_radix2(fftplan _p)
{
    _p->index_rev = (unsigned int *) malloc((_p->n)*sizeof(unsigned int));
    unsigned int i;
    for (i=0; i<_p->n; i++)
        _p->index_rev[i] = reverse_index(i,_p->m);

    //for (i=0; i<_p->n; i++)
    //    printf("%3d -> %3d\n", i, _p->index_rev[i]);
}

// reverse _n-bit index _i
unsigned int reverse_index(unsigned int _i, unsigned int _n)
{
    unsigned int j=0, k;
    for (k=0; k<_n; k++) {
        j <<= 1;
        j |= ( _i & 1 );
        _i >>= 1;
    }

    return j;
}

