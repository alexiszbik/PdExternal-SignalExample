//
//  example_sig_tilde.c
//
//
//  Created by Chris Penny on 2/23/15.
//  Copyright (c) 2015 Comp150. All rights reserved.
//

#include "m_pd.h"


static t_class *example_sig_tilde_class;

typedef struct _example_sig_tilde {
    t_object x_obj;
    
    t_float f;    
    
    // Outlets
    t_outlet *x_outL;
    t_outlet *x_outR;
    
} t_example_sig_tilde;


// Constructor Method
void *example_sig_tilde_new(void)
{
    // Get new instance
    t_example_sig_tilde *instance = (t_example_sig_tilde *)pd_new(example_sig_tilde_class);

    // Spawn outlets
    instance->x_outL = outlet_new(&instance->x_obj, &s_signal);
    instance->x_outR = outlet_new(&instance->x_obj, &s_signal);
    
    // Return initialized instance
    return (void *)instance;
}

// Destructor Method
void example_sig_tilde_free(t_example_sig_tilde *instance)
{

    // Free Outlets
    outlet_free(instance->x_outL);
    outlet_free(instance->x_outR);
}

// DSP Computation
t_int *example_sig_tilde_perform(t_int *input)
{
    // Get class instance
    t_example_sig_tilde *x = (t_example_sig_tilde *)(input[1]);
    
    // Get outlet pointers
    t_sample *outL = (t_sample *)(input[2]);
    t_sample *outR = (t_sample *)(input[3]);
    t_int length = (t_int)(input[4]);
    
    for(t_int i = 0; i < length; i++) {
        outL[i] = 14;
        outR[i] = 28;
    }
    
    return input + 5;
}

// Declare dsp function for Pd
void example_sig_tilde_dsp(t_example_sig_tilde *instance, t_signal **sp)
{
    dsp_add(
            example_sig_tilde_perform,
            4,
            instance,
            sp[0]->s_vec,
            sp[1]->s_vec,
            sp[0]->s_n);
}

// Extra Method
void example_sig_tilde_info(t_example_sig_tilde *instance)
{
    post("example_sig_tilde version 0.0");
}

// Setup class for use
void example_sig_tilde_setup(void)
{
    example_sig_tilde_class = class_new(gensym("example_sig_tilde"),
                                       (t_newmethod)example_sig_tilde_new,
                                       0,
                                       sizeof(t_example_sig_tilde),
                                       CLASS_DEFAULT,
                                       0);
    
    class_addmethod(example_sig_tilde_class, (t_method)example_sig_tilde_dsp, gensym("dsp"), 0);
    class_addmethod(example_sig_tilde_class, (t_method)example_sig_tilde_info, gensym("info"), 0);
}

