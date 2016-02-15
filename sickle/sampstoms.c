/* Copyright (c) 2003 krzYszcz, and others.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

#include "m_pd.h"
#include "sickle/sic.h"
#include "shared.h"
#define KILOS 1000.

typedef struct _sampstoms
{
    t_sic      x_sic;
    t_float    x_rcpksr;
    t_outlet  *x_floatout;
    t_float    x_millisecs;
    t_clock   *x_clock;
} t_sampstoms;

static t_class *sampstoms_class;

static void sampstoms_tick(t_sampstoms *x)
{
    outlet_float(x->x_floatout, x->x_millisecs);
}

/*static void sampstoms_float(t_sampstoms *x, t_float f)
{
    outlet_float(x->x_floatout, f * x->x_rcpksr);
} */

static t_int *sampstoms_perform(t_int *w)
{
    t_sampstoms *x = (t_sampstoms *)(w[1]);
    int nblock = (int)(w[2]);
    t_float *in = (t_float *)(w[3]);
    t_float *out = (t_float *)(w[4]);
    t_float rcpksr = x->x_rcpksr;
    t_float ms;
    while (nblock--) {
        ms = *in++ * rcpksr;
        *out++ = ms;
    }
    x->x_millisecs = ms;
    clock_delay(x->x_clock, 0);
    return (w + 5);
}

static void sampstoms_dsp(t_sampstoms *x, t_signal **sp)
{
    x->x_rcpksr = KILOS / sp[0]->s_sr;
    dsp_add(sampstoms_perform, 4, x,
	    sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec);
}

static void sampstoms_free(t_sampstoms *x)
{
    if (x->x_clock) clock_free(x->x_clock);
}

static void *sampstoms_new(void)
{
    t_sampstoms *x = (t_sampstoms *)pd_new(sampstoms_class);
    x->x_rcpksr = KILOS / sys_getsr();  /* LATER rethink */
    outlet_new((t_object *)x, &s_signal);
    x->x_floatout = outlet_new((t_object *)x, &s_float);
    x->x_clock = clock_new(x, (t_method)sampstoms_tick);
    return (x);
}

void sampstoms_tilde_setup(void)
{
    sampstoms_class = class_new(gensym("sampstoms~"),
				(t_newmethod)sampstoms_new, 
                                (t_method)sampstoms_free,
				sizeof(t_sampstoms), 0, 0);
    sic_setup(sampstoms_class, sampstoms_dsp, SIC_FLOATTOSIGNAL);
    int major, minor, bugfix;
    sys_getversion(&major, &minor, &bugfix);
    if (major > 0 || minor > 42) 
        logpost(NULL, 4, "this is cyclone/sampstoms~ %s, %dth %s build",
            CYCLONE_VERSION, CYCLONE_BUILD, CYCLONE_RELEASE);}
