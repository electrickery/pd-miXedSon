/* Copyright (c) 2003 krzYszcz, and others.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

#include "m_pd.h"
#include "sickle/sic.h"
#define MILLIS 0.001

typedef struct _mstosamps
{
    t_sic      x_sic;
    t_float    x_ksr;
    t_outlet  *x_floatout;
    t_float    x_sampleCount;
    t_clock   *x_clock;
} t_mstosamps;

static t_class *mstosamps_class;

/*static void mstosamps_float(t_mstosamps *x, t_float f)
{
    outlet_float(x->x_floatout, x->x_sampleCount);
} */

static void mstosamps_tick(t_mstosamps *x)
{
//    outlet_float(((t_object *)x)->x_floatout, x->x_sampleCount);
    outlet_float(x->x_floatout, x->x_sampleCount);
}

static t_int *mstosamps_perform(t_int *w)
{
    t_mstosamps *x = (t_mstosamps *)(w[1]);
    int nblock = (int)(w[2]);
    t_float *in = (t_float *)(w[3]);
    t_float *out = (t_float *)(w[4]);
    t_float sc;
    t_float ksr = x->x_ksr;
    while (nblock--) {
        sc = *in++ * ksr;
        *out++ = sc;
    }
    x->x_sampleCount = sc;
    clock_delay(x->x_clock, 0);
    return (w + 5);
}

static void mstosamps_dsp(t_mstosamps *x, t_signal **sp)
{
    x->x_ksr = sp[0]->s_sr * MILLIS;
    dsp_add(mstosamps_perform, 4, x,
	    sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec);
}

static void mstosamps_free(t_mstosamps *x)
{
    if (x->x_clock) clock_free(x->x_clock);
}

static void *mstosamps_new(void)
{
    t_mstosamps *x = (t_mstosamps *)pd_new(mstosamps_class);
    x->x_ksr = sys_getsr() * MILLIS;  /* LATER rethink */
    outlet_new((t_object *)x, &s_signal);
    x->x_floatout = outlet_new((t_object *)x, &s_float);
    x->x_clock = clock_new(x, (t_method)mstosamps_tick);
    return (x);
}

void mstosamps_tilde_setup(void)
{
    mstosamps_class = class_new(gensym("mstosamps~"),
				(t_newmethod)mstosamps_new, 
                                (t_method)mstosamps_free,
				sizeof(t_mstosamps), 0, 0);
//    sic_setup(mstosamps_class, mstosamps_dsp, mstosamps_float);
    sic_setup(mstosamps_class, mstosamps_dsp, 0);
}
