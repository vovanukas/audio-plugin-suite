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
	Delay m_delay_6;
	Delay m_delay_5;
	Delta __m_delta_23;
	Delta __m_delta_26;
	Delta __m_delta_17;
	Delta __m_delta_20;
	Phasor __m_phasor_16;
	Phasor __m_phasor_15;
	Sah __m_sah_12;
	Sah __m_sah_18;
	Sah __m_sah_19;
	Sah __m_sah_28;
	Sah __m_sah_21;
	Sah __m_sah_25;
	Sah __m_sah_27;
	Sah __m_sah_24;
	Sah __m_sah_22;
	Sah __m_sah_14;
	SineCycle __m_cycle_13;
	SineCycle __m_cycle_11;
	SineData __sinedata;
	int vectorsize;
	int __exception;
	t_sample m_listener_distance_to_object_path_8;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_side_10;
	t_sample m_gaindB_9;
	t_sample m_history_2;
	t_sample samples_to_seconds;
	t_sample m_history_3;
	t_sample m_object_distance_on_path_7;
	t_sample m_history_4;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_delay_5.reset("m_delay_5", ((int)88200));
		m_delay_6.reset("m_delay_6", samplerate);
		m_object_distance_on_path_7 = ((int)0);
		m_listener_distance_to_object_path_8 = ((int)15);
		m_gaindB_9 = ((int)1);
		m_side_10 = ((int)0);
		__m_cycle_11.reset(samplerate, 0);
		__m_sah_12.reset(0);
		__m_cycle_13.reset(samplerate, 0);
		__m_sah_14.reset(0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_15.reset(0);
		__m_phasor_16.reset(0);
		__m_delta_17.reset(0);
		__m_sah_18.reset(0);
		__m_sah_19.reset(0);
		__m_delta_20.reset(0);
		__m_sah_21.reset(0);
		__m_sah_22.reset(0);
		__m_delta_23.reset(0);
		__m_sah_24.reset(0);
		__m_sah_25.reset(0);
		__m_delta_26.reset(0);
		__m_sah_27.reset(0);
		__m_sah_28.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample dbtoa_23 = dbtoa(m_gaindB_9);
		samples_to_seconds = (1 / samplerate);
		t_sample mstosamps_104 = (((int)100) * (samplerate * 0.001));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			__m_cycle_11.freq(((int)10));
			t_sample cycle_117 = __m_cycle_11(__sinedata);
			t_sample cycleindex_118 = __m_cycle_11.phase();
			t_sample sah_119 = __m_sah_12(m_object_distance_on_path_7, cycle_117, ((t_sample)0.5));
			__m_cycle_13.freq(((int)10));
			t_sample cycle_24 = __m_cycle_13(__sinedata);
			t_sample cycleindex_25 = __m_cycle_13.phase();
			t_sample sah_26 = __m_sah_14(m_side_10, cycle_24, ((t_sample)0.5));
			int eq_27 = (sah_26 == ((int)0));
			t_sample sub_198 = (sah_119 - ((int)-100));
			t_sample scale_195 = ((safepow((sub_198 * ((t_sample)0.005)), ((int)1)) * ((t_sample)-0.5)) + ((t_sample)1.25));
			t_sample scale_38 = scale_195;
			t_sample sub_202 = (sah_119 - ((int)100));
			t_sample scale_199 = ((safepow((sub_202 * ((t_sample)-0.005)), ((int)1)) * ((t_sample)-0.5)) + ((t_sample)1.25));
			t_sample scale_32 = scale_199;
			t_sample switch_33 = (eq_27 ? scale_38 : scale_32);
			t_sample gen_39 = switch_33;
			t_sample out3 = gen_39;
			t_sample cartopol_203 = sqrt(((m_listener_distance_to_object_path_8 * m_listener_distance_to_object_path_8) + (sah_119 * sah_119)));
			t_sample cartopol_204 = atan2(sah_119, m_listener_distance_to_object_path_8);
			t_sample degrees_130 = (cartopol_204 * 57.295779513082);
			t_sample sub_208 = (degrees_130 - ((int)-90));
			t_sample scale_205 = ((safepow((sub_208 * ((t_sample)0.0055555555555556)), ((int)1)) * ((int)-1)) + ((int)1));
			t_sample sub_212 = (degrees_130 - ((int)-90));
			t_sample scale_209 = ((safepow((sub_212 * ((t_sample)0.0055555555555556)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample rdiv_157 = safediv(m_listener_distance_to_object_path_8, cartopol_203);
			t_sample div_155 = (cartopol_203 * ((t_sample)2.938669957977));
			t_sample mul_131 = (in1 * ((t_sample)0.9));
			t_sample phasor_153 = __m_phasor_15(div_155, samples_to_seconds);
			t_sample add_152 = (phasor_153 + ((int)0));
			t_sample mod_151 = safemod(add_152, ((int)1));
			t_sample mstosamps_137 = (mod_151 * (samplerate * 0.001));
			t_sample sub_150 = (mod_151 - ((t_sample)0.5));
			t_sample mul_149 = (sub_150 * ((t_sample)3.1415926535898));
			t_sample cos_148 = cos(mul_149);
			t_sample add_145 = (phasor_153 + ((t_sample)0.5));
			t_sample mod_144 = safemod(add_145, ((int)1));
			t_sample mstosamps_136 = (mod_144 * (samplerate * 0.001));
			t_sample tap_140 = m_delay_6.read_linear(mstosamps_137);
			t_sample tap_141 = m_delay_6.read_linear(mstosamps_136);
			t_sample mul_147 = (tap_140 * cos_148);
			t_sample sub_143 = (mod_144 - ((t_sample)0.5));
			t_sample mul_138 = (sub_143 * ((t_sample)3.1415926535898));
			t_sample cos_142 = cos(mul_138);
			t_sample mul_146 = (tap_141 * cos_142);
			t_sample gen_154 = (mul_146 + mul_147);
			t_sample noise_42 = noise();
			t_sample abs_59 = fabs(noise_42);
			t_sample mul_68 = (abs_59 * ((int)0));
			t_sample noise_43 = noise();
			t_sample abs_60 = fabs(noise_43);
			t_sample mul_71 = (abs_60 * ((int)0));
			t_sample noise_40 = noise();
			t_sample abs_57 = fabs(noise_40);
			t_sample mul_62 = (abs_57 * ((int)0));
			t_sample noise_41 = noise();
			t_sample abs_58 = fabs(noise_41);
			t_sample mul_65 = (abs_58 * ((int)0));
			t_sample rsub_91 = (((int)1) - gen_39);
			t_sample mul_90 = (rsub_91 * ((int)1000));
			t_sample div_89 = (mul_90 * ((t_sample)0.01));
			t_sample phasor_110 = __m_phasor_16(div_89, samples_to_seconds);
			t_sample add_103 = ((m_history_4 + phasor_110) + ((t_sample)0.25));
			t_sample mod_102 = safemod(add_103, ((int)1));
			t_sample delta_70 = __m_delta_17(mod_102);
			t_sample sah_48 = __m_sah_18(mul_68, delta_70, ((int)0));
			t_sample sah_69 = __m_sah_19(mstosamps_104, delta_70, ((int)0));
			t_sample mul_55 = (sah_69 * mod_102);
			t_sample sub_101 = (mod_102 - ((t_sample)0.5));
			t_sample mul_100 = (sub_101 * ((t_sample)3.1415926535898));
			t_sample cos_99 = cos(mul_100);
			t_sample mul_75 = (cos_99 * cos_99);
			t_sample add_109 = ((m_history_3 + phasor_110) + ((int)0));
			t_sample mod_108 = safemod(add_109, ((int)1));
			t_sample delta_51 = __m_delta_20(mod_108);
			t_sample sah_50 = __m_sah_21(mul_71, delta_51, ((int)0));
			t_sample sah_72 = __m_sah_22(mstosamps_104, delta_51, ((int)0));
			t_sample mul_56 = (sah_72 * mod_108);
			t_sample sub_107 = (mod_108 - ((t_sample)0.5));
			t_sample mul_106 = (sub_107 * ((t_sample)3.1415926535898));
			t_sample cos_105 = cos(mul_106);
			t_sample mul_76 = (cos_105 * cos_105);
			t_sample add_82 = ((m_history_2 + phasor_110) + ((t_sample)0.75));
			t_sample mod_81 = safemod(add_82, ((int)1));
			t_sample delta_64 = __m_delta_23(mod_81);
			t_sample sah_44 = __m_sah_24(mul_62, delta_64, ((int)0));
			t_sample sah_63 = __m_sah_25(mstosamps_104, delta_64, ((int)0));
			t_sample mul_53 = (sah_63 * mod_81);
			t_sample sub_80 = (mod_81 - ((t_sample)0.5));
			t_sample mul_79 = (sub_80 * ((t_sample)3.1415926535898));
			t_sample cos_78 = cos(mul_79);
			t_sample mul_73 = (cos_78 * cos_78);
			t_sample add_88 = ((m_history_1 + phasor_110) + ((t_sample)0.5));
			t_sample mod_87 = safemod(add_88, ((int)1));
			t_sample delta_67 = __m_delta_26(mod_87);
			t_sample sah_46 = __m_sah_27(mul_65, delta_67, ((int)0));
			t_sample sah_66 = __m_sah_28(mstosamps_104, delta_67, ((int)0));
			t_sample mul_54 = (sah_66 * mod_87);
			t_sample tap_95 = m_delay_5.read_linear(mul_56);
			t_sample tap_96 = m_delay_5.read_linear(mul_55);
			t_sample tap_97 = m_delay_5.read_linear(mul_54);
			t_sample tap_98 = m_delay_5.read_linear(mul_53);
			t_sample mul_93 = (tap_95 * mul_76);
			t_sample mul_92 = (tap_96 * mul_75);
			t_sample mul_77 = (tap_98 * mul_73);
			t_sample gen_116 = (mul_77 + mul_92);
			t_sample sub_86 = (mod_87 - ((t_sample)0.5));
			t_sample mul_85 = (sub_86 * ((t_sample)3.1415926535898));
			t_sample cos_84 = cos(mul_85);
			t_sample mul_74 = (cos_84 * cos_84);
			t_sample mul_83 = (tap_97 * mul_74);
			t_sample gen_115 = (mul_83 + mul_93);
			t_sample history_49_next_111 = fixdenorm(sah_48);
			t_sample history_52_next_112 = fixdenorm(sah_50);
			t_sample history_45_next_113 = fixdenorm(sah_44);
			t_sample history_47_next_114 = fixdenorm(sah_46);
			t_sample mul_135 = (rdiv_157 * (gen_115 + gen_116));
			t_sample mul_134 = (mul_135 * (4 * 3.1415926535898));
			t_sample mul_133 = (mul_134 * scale_205);
			t_sample mul_22 = (mul_133 * dbtoa_23);
			t_sample out1 = mul_22;
			t_sample mul_132 = (mul_134 * scale_209);
			t_sample mul_21 = (mul_132 * dbtoa_23);
			t_sample out2 = mul_21;
			m_delay_6.write(mul_131);
			m_delay_5.write(gen_154);
			m_history_1 = history_47_next_114;
			m_history_2 = history_45_next_113;
			m_history_3 = history_52_next_112;
			m_history_4 = history_49_next_111;
			m_delay_5.step();
			m_delay_6.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_object_distance_on_path(t_param _value) {
		m_object_distance_on_path_7 = (_value < -100 ? -100 : (_value > 100 ? 100 : _value));
	};
	inline void set_listener_distance_to_object_path(t_param _value) {
		m_listener_distance_to_object_path_8 = (_value < 1 ? 1 : (_value > 50 ? 50 : _value));
	};
	inline void set_gaindB(t_param _value) {
		m_gaindB_9 = (_value < -96 ? -96 : (_value > 30 ? 30 : _value));
	};
	inline void set_side(t_param _value) {
		m_side_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3" };

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
		case 0: self->set_gaindB(value); break;
		case 1: self->set_listener_distance_to_object_path(value); break;
		case 2: self->set_object_distance_on_path(value); break;
		case 3: self->set_side(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_gaindB_9; break;
		case 1: *value = self->m_listener_distance_to_object_path_8; break;
		case 2: *value = self->m_object_distance_on_path_7; break;
		case 3: *value = self->m_side_10; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_gaindB_9")
	pi = self->__commonstate.params + 0;
	pi->name = "gaindB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gaindB_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -96;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_listener_distance_to_object_path_8")
	pi = self->__commonstate.params + 1;
	pi->name = "listener_distance_to_object_path";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_listener_distance_to_object_path_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_object_distance_on_path_7")
	pi = self->__commonstate.params + 2;
	pi->name = "object_distance_on_path";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_object_distance_on_path_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -100;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_side_10")
	pi = self->__commonstate.params + 3;
	pi->name = "side";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_side_10;
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
