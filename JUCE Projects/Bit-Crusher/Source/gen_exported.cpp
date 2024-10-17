#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Sah __m_sah_5;
	Sah __m_sah_16;
	Sah __m_sah_9;
	Sah __m_sah_7;
	SineCycle __m_cycle_4;
	SineCycle __m_cycle_8;
	SineCycle __m_cycle_6;
	SineCycle __m_cycle_15;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample __m_latch_14;
	t_sample m_degradation_2;
	t_sample m_mix_3;
	t_sample __m_carry_12;
	t_sample samplerate;
	t_sample __m_count_10;
	t_sample m_mode_1;
	t_sample __m_latch_17;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_mode_1 = ((int)1);
		m_degradation_2 = ((int)1);
		m_mix_3 = ((t_sample)0.5);
		__m_cycle_4.reset(samplerate, 0);
		__m_sah_5.reset(0);
		__m_cycle_6.reset(samplerate, 0);
		__m_sah_7.reset(0);
		__m_cycle_8.reset(samplerate, 0);
		__m_sah_9.reset(0);
		__m_count_10 = 0;
		__m_carry_12 = 0;
		__m_latch_14 = 0;
		__m_cycle_15.reset(samplerate, 0);
		__m_sah_16.reset(0);
		__m_latch_17 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			__m_cycle_4.freq(((int)10));
			t_sample cycle_309 = __m_cycle_4(__sinedata);
			t_sample cycleindex_310 = __m_cycle_4.phase();
			t_sample sah_311 = __m_sah_5(m_mix_3, cycle_309, ((t_sample)0.5));
			__m_cycle_6.freq(((int)10));
			t_sample cycle_306 = __m_cycle_6(__sinedata);
			t_sample cycleindex_307 = __m_cycle_6.phase();
			t_sample sah_308 = __m_sah_7(m_mode_1, cycle_306, ((t_sample)0.5));
			__m_cycle_8.freq(((int)10));
			t_sample cycle_303 = __m_cycle_8(__sinedata);
			t_sample cycleindex_304 = __m_cycle_8.phase();
			t_sample sah_305 = __m_sah_9(m_degradation_2, cycle_303, ((t_sample)0.5));
			__m_count_10 = (((int)0) ? 0 : (fixdenorm(__m_count_10 + ((int)1))));
			int carry_11 = 0;
			if ((((int)0) != 0)) {
				__m_count_10 = 0;
				__m_carry_12 = 0;
				
			} else if (((sah_305 > 0) && (__m_count_10 >= sah_305))) {
				int wraps_13 = (__m_count_10 / sah_305);
				__m_carry_12 = (__m_carry_12 + wraps_13);
				__m_count_10 = (__m_count_10 - (wraps_13 * sah_305));
				carry_11 = 1;
				
			};
			int counter_289 = __m_count_10;
			int counter_290 = carry_11;
			int counter_291 = __m_carry_12;
			__m_latch_14 = ((counter_290 != 0) ? in1 : __m_latch_14);
			t_sample latch_292 = __m_latch_14;
			__m_cycle_15.freq(((int)10));
			t_sample cycle_300 = __m_cycle_15(__sinedata);
			t_sample cycleindex_301 = __m_cycle_15.phase();
			t_sample sah_302 = __m_sah_16(m_degradation_2, cycle_300, ((t_sample)0.5));
			t_sample sub_284 = (sah_302 - ((int)33));
			t_sample mul_283 = (sub_284 * (-1));
			t_sample mul_287 = (mul_283 * in1);
			t_sample ceil_298 = ceil(mul_287);
			t_sample div_286 = safediv(ceil_298, mul_283);
			t_sample add_296 = (mul_287 + ((t_sample)0.5));
			t_sample floor_297 = floor(add_296);
			t_sample sub_295 = (floor_297 - ((t_sample)0.5));
			t_sample div_285 = safediv(sub_295, mul_283);
			t_sample mix_312 = (div_286 + (((t_sample)0.5) * (div_285 - div_286)));
			__m_latch_17 = ((in1 != 0) ? mix_312 : __m_latch_17);
			t_sample latch_281 = __m_latch_17;
			t_sample choice_18 = int(sah_308);
			t_sample selector_282 = ((choice_18 >= 2) ? latch_292 : ((choice_18 >= 1) ? latch_281 : 0));
			t_sample mix_313 = (in1 + (sah_311 * (selector_282 - in1)));
			t_sample out1 = mix_313;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_mode(t_param _value) {
		m_mode_1 = (_value < 1 ? 1 : (_value > 2 ? 2 : _value));
	};
	inline void set_degradation(t_param _value) {
		m_degradation_2 = (_value < 0 ? 0 : (_value > 32 ? 32 : _value));
	};
	inline void set_mix(t_param _value) {
		m_mix_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 1;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_degradation(value); break;
		case 1: self->set_mix(value); break;
		case 2: self->set_mode(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_degradation_2; break;
		case 1: *value = self->m_mix_3; break;
		case 2: *value = self->m_mode_1; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_degradation_2")
	pi = self->__commonstate.params + 0;
	pi->name = "degradation";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_degradation_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 32;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_mix_3")
	pi = self->__commonstate.params + 1;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_mode_1")
	pi = self->__commonstate.params + 2;
	pi->name = "mode";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mode_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
