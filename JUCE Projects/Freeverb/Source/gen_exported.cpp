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
	Delay m_delay_20;
	Delay m_delay_14;
	Delay m_delay_12;
	Delay m_delay_6;
	Delay m_delay_8;
	Delay m_delay_3;
	Delay m_delay_4;
	Delay m_delay_1;
	Delay m_delay_18;
	Delay m_delay_2;
	Delay m_delay_10;
	Delay m_delay_16;
	Sah __m_sah_27;
	Sah __m_sah_29;
	Sah __m_sah_35;
	Sah __m_sah_33;
	Sah __m_sah_31;
	SineCycle __m_cycle_34;
	SineCycle __m_cycle_28;
	SineCycle __m_cycle_32;
	SineCycle __m_cycle_30;
	SineCycle __m_cycle_26;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_7;
	t_sample m_damp_22;
	t_sample m_history_9;
	t_sample m_history_5;
	t_sample samplerate;
	t_sample m_feedback_21;
	t_sample m_history_11;
	t_sample m_history_15;
	t_sample m_feedback_23;
	t_sample m_history_13;
	t_sample m_mix_24;
	t_sample m_history_19;
	t_sample m_spread_25;
	t_sample m_history_17;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)2000));
		m_delay_2.reset("m_delay_2", ((int)2000));
		m_delay_3.reset("m_delay_3", ((int)2000));
		m_delay_4.reset("m_delay_4", ((int)2000));
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)2000));
		m_history_7 = ((int)0);
		m_delay_8.reset("m_delay_8", ((int)2000));
		m_history_9 = ((int)0);
		m_delay_10.reset("m_delay_10", ((int)2000));
		m_history_11 = ((int)0);
		m_delay_12.reset("m_delay_12", ((int)2000));
		m_history_13 = ((int)0);
		m_delay_14.reset("m_delay_14", ((int)2000));
		m_history_15 = ((int)0);
		m_delay_16.reset("m_delay_16", ((int)2000));
		m_history_17 = ((int)0);
		m_delay_18.reset("m_delay_18", ((int)2000));
		m_history_19 = ((int)0);
		m_delay_20.reset("m_delay_20", ((int)2000));
		m_feedback_21 = ((t_sample)0.5);
		m_damp_22 = ((t_sample)0.5);
		m_feedback_23 = ((t_sample)0.9);
		m_mix_24 = ((t_sample)0.5);
		m_spread_25 = ((int)0);
		__m_cycle_26.reset(samplerate, 0);
		__m_sah_27.reset(0);
		__m_cycle_28.reset(samplerate, 0);
		__m_sah_29.reset(0);
		__m_cycle_30.reset(samplerate, 0);
		__m_sah_31.reset(0);
		__m_cycle_32.reset(samplerate, 0);
		__m_sah_33.reset(0);
		__m_cycle_34.reset(samplerate, 0);
		__m_sah_35.reset(0);
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
			__m_cycle_26.freq(((int)10));
			t_sample cycle_1243 = __m_cycle_26(__sinedata);
			t_sample cycleindex_1244 = __m_cycle_26.phase();
			t_sample sah_1245 = __m_sah_27(m_mix_24, cycle_1243, ((t_sample)0.5));
			__m_cycle_28.freq(((int)10));
			t_sample cycle_500 = __m_cycle_28(__sinedata);
			t_sample cycleindex_501 = __m_cycle_28.phase();
			t_sample sah_502 = __m_sah_29(m_feedback_21, cycle_500, ((t_sample)0.5));
			t_sample mul_527 = (sah_502 * ((t_sample)0.5));
			__m_cycle_30.freq(((int)10));
			t_sample cycle_657 = __m_cycle_30(__sinedata);
			t_sample cycleindex_658 = __m_cycle_30.phase();
			t_sample sah_659 = __m_sah_31(m_spread_25, cycle_657, ((t_sample)0.5));
			t_sample spread_493 = sah_659;
			t_sample spread_488 = spread_493;
			t_sample add_503 = (((int)341) + spread_488);
			t_sample spread_489 = spread_493;
			t_sample add_511 = (((int)441) + spread_489);
			t_sample spread_490 = spread_493;
			t_sample add_519 = (((int)556) + spread_490);
			t_sample spread_491 = spread_493;
			t_sample add_528 = (((int)225) + spread_491);
			t_sample mul_1242 = (in1 * ((t_sample)0.015));
			t_sample spread_498 = spread_493;
			t_sample add_644 = (((int)1116) + spread_498);
			t_sample spread_497 = spread_493;
			t_sample add_629 = (((int)1188) + spread_497);
			t_sample spread_499 = spread_493;
			t_sample add_614 = (((int)1277) + spread_499);
			t_sample spread_496 = spread_493;
			t_sample add_599 = (((int)1356) + spread_496);
			t_sample spread_495 = spread_493;
			t_sample add_584 = (((int)1422) + spread_495);
			t_sample spread_494 = spread_493;
			t_sample add_569 = (((int)1491) + spread_494);
			t_sample add_554 = (((int)1557) + spread_493);
			t_sample spread_492 = spread_493;
			t_sample add_539 = (((int)1617) + spread_492);
			__m_cycle_32.freq(((int)10));
			t_sample cycle_660 = __m_cycle_32(__sinedata);
			t_sample cycleindex_661 = __m_cycle_32.phase();
			t_sample sah_662 = __m_sah_33(m_feedback_23, cycle_660, ((t_sample)0.5));
			__m_cycle_34.freq(((int)10));
			t_sample cycle_663 = __m_cycle_34(__sinedata);
			t_sample cycleindex_664 = __m_cycle_34.phase();
			t_sample sah_665 = __m_sah_35(m_damp_22, cycle_663, ((t_sample)0.5));
			t_sample damp_570 = sah_665;
			t_sample tap_578 = m_delay_20.read_linear(add_569);
			t_sample gen_581 = tap_578;
			t_sample mul_576 = (tap_578 * damp_570);
			t_sample rsub_571 = (((int)1) - damp_570);
			t_sample mul_574 = (m_history_19 * rsub_571);
			t_sample add_575 = (mul_576 + mul_574);
			t_sample mul_572 = (add_575 * sah_662);
			t_sample add_579 = (mul_1242 + mul_572);
			t_sample history_573_next_580 = fixdenorm(add_575);
			t_sample damp_645 = damp_570;
			t_sample tap_653 = m_delay_18.read_linear(add_644);
			t_sample gen_656 = tap_653;
			t_sample mul_651 = (tap_653 * damp_645);
			t_sample rsub_646 = (((int)1) - damp_645);
			t_sample mul_649 = (m_history_17 * rsub_646);
			t_sample add_650 = (mul_651 + mul_649);
			t_sample mul_647 = (add_650 * sah_662);
			t_sample add_654 = (mul_1242 + mul_647);
			t_sample history_648_next_655 = fixdenorm(add_650);
			t_sample damp_630 = damp_570;
			t_sample tap_638 = m_delay_16.read_linear(add_629);
			t_sample gen_641 = tap_638;
			t_sample mul_636 = (tap_638 * damp_630);
			t_sample rsub_631 = (((int)1) - damp_630);
			t_sample mul_634 = (m_history_15 * rsub_631);
			t_sample add_635 = (mul_636 + mul_634);
			t_sample mul_632 = (add_635 * sah_662);
			t_sample add_639 = (mul_1242 + mul_632);
			t_sample history_633_next_640 = fixdenorm(add_635);
			t_sample damp_615 = damp_570;
			t_sample tap_623 = m_delay_14.read_linear(add_614);
			t_sample gen_626 = tap_623;
			t_sample mul_621 = (tap_623 * damp_615);
			t_sample rsub_616 = (((int)1) - damp_615);
			t_sample mul_619 = (m_history_13 * rsub_616);
			t_sample add_620 = (mul_621 + mul_619);
			t_sample mul_617 = (add_620 * sah_662);
			t_sample add_624 = (mul_1242 + mul_617);
			t_sample history_618_next_625 = fixdenorm(add_620);
			t_sample damp_600 = damp_570;
			t_sample tap_608 = m_delay_12.read_linear(add_599);
			t_sample gen_611 = tap_608;
			t_sample mul_606 = (tap_608 * damp_600);
			t_sample rsub_601 = (((int)1) - damp_600);
			t_sample mul_604 = (m_history_11 * rsub_601);
			t_sample add_605 = (mul_606 + mul_604);
			t_sample mul_602 = (add_605 * sah_662);
			t_sample add_609 = (mul_1242 + mul_602);
			t_sample history_603_next_610 = fixdenorm(add_605);
			t_sample damp_585 = damp_570;
			t_sample tap_593 = m_delay_10.read_linear(add_584);
			t_sample gen_596 = tap_593;
			t_sample mul_591 = (tap_593 * damp_585);
			t_sample rsub_586 = (((int)1) - damp_585);
			t_sample mul_589 = (m_history_9 * rsub_586);
			t_sample add_590 = (mul_591 + mul_589);
			t_sample mul_587 = (add_590 * sah_662);
			t_sample add_594 = (mul_1242 + mul_587);
			t_sample history_588_next_595 = fixdenorm(add_590);
			t_sample damp_555 = damp_570;
			t_sample tap_563 = m_delay_8.read_linear(add_554);
			t_sample gen_566 = tap_563;
			t_sample mul_561 = (tap_563 * damp_555);
			t_sample rsub_556 = (((int)1) - damp_555);
			t_sample mul_559 = (m_history_7 * rsub_556);
			t_sample add_560 = (mul_561 + mul_559);
			t_sample mul_557 = (add_560 * sah_662);
			t_sample add_564 = (mul_1242 + mul_557);
			t_sample history_558_next_565 = fixdenorm(add_560);
			t_sample damp_540 = damp_570;
			t_sample tap_548 = m_delay_6.read_linear(add_539);
			t_sample gen_551 = tap_548;
			t_sample mul_546 = (tap_548 * damp_540);
			t_sample rsub_541 = (((int)1) - damp_540);
			t_sample mul_544 = (m_history_5 * rsub_541);
			t_sample add_545 = (mul_546 + mul_544);
			t_sample mul_542 = (add_545 * sah_662);
			t_sample add_549 = (mul_1242 + mul_542);
			t_sample history_543_next_550 = fixdenorm(add_545);
			t_sample add_536 = ((((((((gen_551 + gen_566) + gen_581) + gen_596) + gen_611) + gen_626) + gen_641) + gen_656) + ((int)0));
			t_sample tap_534 = m_delay_4.read_linear(add_528);
			t_sample sub_530 = (add_536 - tap_534);
			t_sample mul_532 = (tap_534 * mul_527);
			t_sample add_531 = (add_536 + mul_532);
			t_sample tap_525 = m_delay_3.read_linear(add_519);
			t_sample sub_521 = (sub_530 - tap_525);
			t_sample mul_523 = (tap_525 * mul_527);
			t_sample add_522 = (sub_530 + mul_523);
			t_sample tap_517 = m_delay_2.read_linear(add_511);
			t_sample sub_513 = (sub_521 - tap_517);
			t_sample mul_515 = (tap_517 * mul_527);
			t_sample add_514 = (sub_521 + mul_515);
			t_sample tap_509 = m_delay_1.read_linear(add_503);
			t_sample sub_505 = (sub_513 - tap_509);
			t_sample mul_507 = (tap_509 * mul_527);
			t_sample add_506 = (sub_513 + mul_507);
			t_sample mix_1248 = (in1 + (sah_1245 * (sub_505 - in1)));
			t_sample out1 = mix_1248;
			m_delay_20.write(add_579);
			m_history_19 = history_573_next_580;
			m_delay_18.write(add_654);
			m_history_17 = history_648_next_655;
			m_delay_16.write(add_639);
			m_history_15 = history_633_next_640;
			m_delay_14.write(add_624);
			m_history_13 = history_618_next_625;
			m_delay_12.write(add_609);
			m_history_11 = history_603_next_610;
			m_delay_10.write(add_594);
			m_history_9 = history_588_next_595;
			m_delay_8.write(add_564);
			m_history_7 = history_558_next_565;
			m_delay_6.write(add_549);
			m_history_5 = history_543_next_550;
			m_delay_4.write(add_531);
			m_delay_3.write(add_522);
			m_delay_2.write(add_514);
			m_delay_1.write(add_506);
			m_delay_1.step();
			m_delay_2.step();
			m_delay_3.step();
			m_delay_4.step();
			m_delay_6.step();
			m_delay_8.step();
			m_delay_10.step();
			m_delay_12.step();
			m_delay_14.step();
			m_delay_16.step();
			m_delay_18.step();
			m_delay_20.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			
		};
		return __exception;
		
	};
	inline void set_feedback2(t_param _value) {
		m_feedback_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_damp(t_param _value) {
		m_damp_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_feedback1(t_param _value) {
		m_feedback_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mix(t_param _value) {
		m_mix_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_spread(t_param _value) {
		m_spread_25 = (_value < 0 ? 0 : (_value > 400 ? 400 : _value));
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
int num_params() { return 5; }

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
		case 0: self->set_damp(value); break;
		case 1: self->set_feedback1(value); break;
		case 2: self->set_feedback2(value); break;
		case 3: self->set_mix(value); break;
		case 4: self->set_spread(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damp_22; break;
		case 1: *value = self->m_feedback_23; break;
		case 2: *value = self->m_feedback_21; break;
		case 3: *value = self->m_mix_24; break;
		case 4: *value = self->m_spread_25; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_damp_22")
	pi = self->__commonstate.params + 0;
	pi->name = "damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damp_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_feedback_23")
	pi = self->__commonstate.params + 1;
	pi->name = "feedback1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_feedback_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_feedback_21")
	pi = self->__commonstate.params + 2;
	pi->name = "feedback2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_feedback_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_mix_24")
	pi = self->__commonstate.params + 3;
	pi->name = "mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mix_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_spread_25")
	pi = self->__commonstate.params + 4;
	pi->name = "spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_spread_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 400;
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
