/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HXpump_justplant_sfun.h"
#include "c2_HXpump_justplant.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HXpump_justplant_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[37] = { "h", "v_thi", "v_tho", "v_mh",
  "v", "Thi", "mdoth", "c1", "c2", "c3", "c4", "a2", "a3", "a4", "b21", "b31",
  "b32", "b41", "b42", "b43", "K1", "K2", "K3", "K4", "slope", "nargin",
  "nargout", "xin", "hotpar", "coldpar", "wallpar", "pumpar", "input", "simpar",
  "noise", "xout", "yout" };

static const char * c2_b_debug_family_names[32] = { "rhoh", "Vh", "ch", "mdoth",
  "hh", "Thi", "rhoc", "Vc", "cc", "hc", "mdotc", "Tci", "rhow", "Vw", "cw", "A",
  "wp", "wt", "dx1", "dx2", "dx3", "dx4", "nargin", "nargout", "x", "hotpar",
  "coldpar", "wallpar", "pumppar", "input", "noise", "xdot" };

/* Function Declarations */
static void initialize_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void initialize_params_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance);
static void enable_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void disable_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance);
static void set_sim_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void sf_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);
static void initSimStructsc2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance);
static void registerMessagesc2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance);
static void c2_heatexchangerpump(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, real_T c2_x[4], real_T c2_hotpar[6], real_T c2_coldpar[4],
  real_T c2_wallpar[4], real_T c2_pumppar, real_T c2_input[2], real_T c2_noise[6],
  real_T c2_xdot[4]);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_yout, const char_T *c2_identifier, real_T
  c2_y[3]);
static void c2_b_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_xout, const char_T *c2_identifier, real_T
  c2_y[4]);
static void c2_d_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_f_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_g_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[2]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[32]);
static void c2_eml_scalar_eg(SFc2_HXpump_justplantInstanceStruct *chartInstance);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_h_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_i_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_HXpump_justplant, const
  char_T *c2_identifier);
static uint8_T c2_j_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_HXpump_justplantInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_HXpump_justplant = 0U;
}

static void initialize_params_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
}

static void enable_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[4];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[3];
  const mxArray *c2_c_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T (*c2_yout)[3];
  real_T (*c2_xout)[4];
  c2_yout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_xout = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(3), FALSE);
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_u[c2_i0] = (*c2_xout)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 3; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_yout)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_HXpump_justplant;
  c2_c_u = c2_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i2;
  real_T c2_dv1[3];
  int32_T c2_i3;
  real_T (*c2_xout)[4];
  real_T (*c2_yout)[3];
  c2_yout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_xout = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                        "xout", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    (*c2_xout)[c2_i2] = c2_dv0[c2_i2];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "yout",
                      c2_dv1);
  for (c2_i3 = 0; c2_i3 < 3; c2_i3++) {
    (*c2_yout)[c2_i3] = c2_dv1[c2_i3];
  }

  chartInstance->c2_is_active_c2_HXpump_justplant = c2_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
     "is_active_c2_HXpump_justplant");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_HXpump_justplant(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
}

static void sf_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  real_T *c2_pumpar;
  real_T *c2_simpar;
  real_T (*c2_yout)[3];
  real_T (*c2_noise)[6];
  real_T (*c2_input)[2];
  real_T (*c2_wallpar)[4];
  real_T (*c2_coldpar)[4];
  real_T (*c2_hotpar)[6];
  real_T (*c2_xout)[4];
  real_T (*c2_xin)[4];
  c2_yout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_noise = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 7);
  c2_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c2_pumpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c2_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c2_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c2_xout = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_xin = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    _SFD_DATA_RANGE_CHECK((*c2_xin)[c2_i4], 0U);
  }

  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    _SFD_DATA_RANGE_CHECK((*c2_xout)[c2_i5], 1U);
  }

  for (c2_i6 = 0; c2_i6 < 6; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_hotpar)[c2_i6], 2U);
  }

  for (c2_i7 = 0; c2_i7 < 4; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_coldpar)[c2_i7], 3U);
  }

  for (c2_i8 = 0; c2_i8 < 4; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_wallpar)[c2_i8], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_pumpar, 5U);
  for (c2_i9 = 0; c2_i9 < 2; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_input)[c2_i9], 6U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_simpar, 7U);
  for (c2_i10 = 0; c2_i10 < 6; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_noise)[c2_i10], 8U);
  }

  for (c2_i11 = 0; c2_i11 < 3; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*c2_yout)[c2_i11], 9U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_HXpump_justplant(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HXpump_justplantMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_HXpump_justplant(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  int32_T c2_i12;
  real_T c2_xin[4];
  int32_T c2_i13;
  real_T c2_hotpar[6];
  int32_T c2_i14;
  real_T c2_coldpar[4];
  int32_T c2_i15;
  real_T c2_wallpar[4];
  real_T c2_pumpar;
  int32_T c2_i16;
  real_T c2_input[2];
  real_T c2_simpar;
  int32_T c2_i17;
  real_T c2_noise[6];
  uint32_T c2_debug_family_var_map[37];
  real_T c2_h;
  real_T c2_v_thi;
  real_T c2_v_tho;
  real_T c2_v_mh;
  real_T c2_v[3];
  real_T c2_Thi;
  real_T c2_mdoth;
  real_T c2_c1;
  real_T c2_c2;
  real_T c2_c3;
  real_T c2_c4;
  real_T c2_a2;
  real_T c2_a3;
  real_T c2_a4;
  real_T c2_b21;
  real_T c2_b31;
  real_T c2_b32;
  real_T c2_b41;
  real_T c2_b42;
  real_T c2_b43;
  real_T c2_K1[4];
  real_T c2_K2[4];
  real_T c2_K3[4];
  real_T c2_K4[4];
  real_T c2_slope[4];
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 2.0;
  real_T c2_xout[4];
  real_T c2_yout[3];
  int32_T c2_i18;
  real_T c2_b_xin[4];
  int32_T c2_i19;
  real_T c2_b_hotpar[6];
  int32_T c2_i20;
  real_T c2_b_coldpar[4];
  int32_T c2_i21;
  real_T c2_b_wallpar[4];
  int32_T c2_i22;
  real_T c2_b_input[2];
  int32_T c2_i23;
  real_T c2_b_noise[6];
  real_T c2_dv2[4];
  int32_T c2_i24;
  int32_T c2_i25;
  real_T c2_b[4];
  int32_T c2_i26;
  real_T c2_b_b;
  int32_T c2_i27;
  int32_T c2_i28;
  real_T c2_c_xin[4];
  int32_T c2_i29;
  real_T c2_c_hotpar[6];
  int32_T c2_i30;
  real_T c2_c_coldpar[4];
  int32_T c2_i31;
  real_T c2_c_wallpar[4];
  int32_T c2_i32;
  real_T c2_c_input[2];
  int32_T c2_i33;
  real_T c2_c_noise[6];
  real_T c2_dv3[4];
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  real_T c2_c_b;
  int32_T c2_i37;
  int32_T c2_i38;
  real_T c2_d_b[4];
  int32_T c2_i39;
  real_T c2_e_b;
  int32_T c2_i40;
  int32_T c2_i41;
  real_T c2_d_xin[4];
  int32_T c2_i42;
  real_T c2_d_hotpar[6];
  int32_T c2_i43;
  real_T c2_d_coldpar[4];
  int32_T c2_i44;
  real_T c2_d_wallpar[4];
  int32_T c2_i45;
  real_T c2_d_input[2];
  int32_T c2_i46;
  real_T c2_d_noise[6];
  real_T c2_dv4[4];
  int32_T c2_i47;
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_f_b;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_g_b;
  int32_T c2_i53;
  int32_T c2_i54;
  real_T c2_h_b[4];
  real_T c2_i_b;
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_e_xin[4];
  int32_T c2_i57;
  real_T c2_e_hotpar[6];
  int32_T c2_i58;
  real_T c2_e_coldpar[4];
  int32_T c2_i59;
  real_T c2_e_wallpar[4];
  int32_T c2_i60;
  real_T c2_e_input[2];
  int32_T c2_i61;
  real_T c2_e_noise[6];
  real_T c2_dv5[4];
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  int32_T c2_i69;
  real_T c2_j_b[4];
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_i72;
  real_T c2_k_b;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  real_T c2_l_b[3];
  int32_T c2_i76;
  real_T c2_y[3];
  int32_T c2_i77;
  int32_T c2_i78;
  static real_T c2_a[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c2_b_Thi[3];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  real_T *c2_b_pumpar;
  real_T *c2_b_simpar;
  real_T (*c2_b_xout)[4];
  real_T (*c2_b_yout)[3];
  real_T (*c2_f_noise)[6];
  real_T (*c2_f_input)[2];
  real_T (*c2_f_wallpar)[4];
  real_T (*c2_f_coldpar)[4];
  real_T (*c2_f_hotpar)[6];
  real_T (*c2_f_xin)[4];
  c2_b_yout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_f_noise = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 7);
  c2_b_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_f_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_pumpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_f_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c2_f_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c2_f_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_xout = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_f_xin = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_pumpar;
  c2_b_hoistedGlobal = *c2_b_simpar;
  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    c2_xin[c2_i12] = (*c2_f_xin)[c2_i12];
  }

  for (c2_i13 = 0; c2_i13 < 6; c2_i13++) {
    c2_hotpar[c2_i13] = (*c2_f_hotpar)[c2_i13];
  }

  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_coldpar[c2_i14] = (*c2_f_coldpar)[c2_i14];
  }

  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_wallpar[c2_i15] = (*c2_f_wallpar)[c2_i15];
  }

  c2_pumpar = c2_hoistedGlobal;
  for (c2_i16 = 0; c2_i16 < 2; c2_i16++) {
    c2_input[c2_i16] = (*c2_f_input)[c2_i16];
  }

  c2_simpar = c2_b_hoistedGlobal;
  for (c2_i17 = 0; c2_i17 < 6; c2_i17++) {
    c2_noise[c2_i17] = (*c2_f_noise)[c2_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 37U, 37U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h, 0U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_thi, 1U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_tho, 2U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_mh, 3U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_v, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Thi, 5U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mdoth, 6U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c1, 7U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c2, 8U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c3, 9U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c4, 10U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_a2, 11U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_a3, 12U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_a4, 13U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b21, 14U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b31, 15U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b32, 16U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b41, 17U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b42, 18U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b43, 19U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K1, 20U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K2, 21U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K3, 22U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_K4, 23U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_slope, 24U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 25U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 26U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_xin, 27U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_hotpar, 28U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_coldpar, 29U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_wallpar, 30U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_pumpar, 31U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_input, 32U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_simpar, 33U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_noise, 34U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xout, 35U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_yout, 36U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_h = c2_simpar;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_v_thi = c2_noise[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_v_tho = c2_noise[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_v_mh = c2_noise[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  c2_v[0] = c2_v_thi;
  c2_v[1] = c2_v_tho;
  c2_v[2] = c2_v_mh;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_Thi = c2_hotpar[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_mdoth = c2_hotpar[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_c1 = 0.16666666666666666;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_c2 = 0.33333333333333331;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  c2_c3 = 0.33333333333333331;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  c2_c4 = 0.16666666666666666;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_a2 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
  c2_a3 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_a4 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  c2_b21 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_b31 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_b32 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_b41 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_b42 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_b43 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
    c2_b_xin[c2_i18] = c2_xin[c2_i18];
  }

  for (c2_i19 = 0; c2_i19 < 6; c2_i19++) {
    c2_b_hotpar[c2_i19] = c2_hotpar[c2_i19];
  }

  for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
    c2_b_coldpar[c2_i20] = c2_coldpar[c2_i20];
  }

  for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
    c2_b_wallpar[c2_i21] = c2_wallpar[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 2; c2_i22++) {
    c2_b_input[c2_i22] = c2_input[c2_i22];
  }

  for (c2_i23 = 0; c2_i23 < 6; c2_i23++) {
    c2_b_noise[c2_i23] = c2_noise[c2_i23];
  }

  c2_heatexchangerpump(chartInstance, c2_b_xin, c2_b_hotpar, c2_b_coldpar,
                       c2_b_wallpar, c2_pumpar, c2_b_input, c2_b_noise, c2_dv2);
  for (c2_i24 = 0; c2_i24 < 4; c2_i24++) {
    c2_K1[c2_i24] = c2_dv2[c2_i24];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
    c2_b[c2_i25] = c2_K1[c2_i25];
  }

  for (c2_i26 = 0; c2_i26 < 4; c2_i26++) {
    c2_b[c2_i26] *= 0.5;
  }

  c2_b_b = c2_h;
  for (c2_i27 = 0; c2_i27 < 4; c2_i27++) {
    c2_b[c2_i27] *= c2_b_b;
  }

  for (c2_i28 = 0; c2_i28 < 4; c2_i28++) {
    c2_c_xin[c2_i28] = c2_xin[c2_i28] + c2_b[c2_i28];
  }

  for (c2_i29 = 0; c2_i29 < 6; c2_i29++) {
    c2_c_hotpar[c2_i29] = c2_hotpar[c2_i29];
  }

  for (c2_i30 = 0; c2_i30 < 4; c2_i30++) {
    c2_c_coldpar[c2_i30] = c2_coldpar[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
    c2_c_wallpar[c2_i31] = c2_wallpar[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 2; c2_i32++) {
    c2_c_input[c2_i32] = c2_input[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 6; c2_i33++) {
    c2_c_noise[c2_i33] = c2_noise[c2_i33];
  }

  c2_heatexchangerpump(chartInstance, c2_c_xin, c2_c_hotpar, c2_c_coldpar,
                       c2_c_wallpar, c2_pumpar, c2_c_input, c2_c_noise, c2_dv3);
  for (c2_i34 = 0; c2_i34 < 4; c2_i34++) {
    c2_K2[c2_i34] = c2_dv3[c2_i34];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
  for (c2_i35 = 0; c2_i35 < 4; c2_i35++) {
    c2_b[c2_i35] = c2_K1[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 4; c2_i36++) {
    c2_b[c2_i36] *= 0.0;
  }

  c2_c_b = c2_h;
  for (c2_i37 = 0; c2_i37 < 4; c2_i37++) {
    c2_b[c2_i37] *= c2_c_b;
  }

  for (c2_i38 = 0; c2_i38 < 4; c2_i38++) {
    c2_d_b[c2_i38] = c2_K2[c2_i38];
  }

  for (c2_i39 = 0; c2_i39 < 4; c2_i39++) {
    c2_d_b[c2_i39] *= 0.5;
  }

  c2_e_b = c2_h;
  for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
    c2_d_b[c2_i40] *= c2_e_b;
  }

  for (c2_i41 = 0; c2_i41 < 4; c2_i41++) {
    c2_d_xin[c2_i41] = (c2_xin[c2_i41] + c2_b[c2_i41]) + c2_d_b[c2_i41];
  }

  for (c2_i42 = 0; c2_i42 < 6; c2_i42++) {
    c2_d_hotpar[c2_i42] = c2_hotpar[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
    c2_d_coldpar[c2_i43] = c2_coldpar[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 4; c2_i44++) {
    c2_d_wallpar[c2_i44] = c2_wallpar[c2_i44];
  }

  for (c2_i45 = 0; c2_i45 < 2; c2_i45++) {
    c2_d_input[c2_i45] = c2_input[c2_i45];
  }

  for (c2_i46 = 0; c2_i46 < 6; c2_i46++) {
    c2_d_noise[c2_i46] = c2_noise[c2_i46];
  }

  c2_heatexchangerpump(chartInstance, c2_d_xin, c2_d_hotpar, c2_d_coldpar,
                       c2_d_wallpar, c2_pumpar, c2_d_input, c2_d_noise, c2_dv4);
  for (c2_i47 = 0; c2_i47 < 4; c2_i47++) {
    c2_K3[c2_i47] = c2_dv4[c2_i47];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
  for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
    c2_b[c2_i48] = c2_K1[c2_i48];
  }

  for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
    c2_b[c2_i49] *= 0.0;
  }

  c2_f_b = c2_h;
  for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
    c2_b[c2_i50] *= c2_f_b;
  }

  for (c2_i51 = 0; c2_i51 < 4; c2_i51++) {
    c2_d_b[c2_i51] = c2_K2[c2_i51];
  }

  for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
    c2_d_b[c2_i52] *= 0.0;
  }

  c2_g_b = c2_h;
  for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
    c2_d_b[c2_i53] *= c2_g_b;
  }

  for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
    c2_h_b[c2_i54] = c2_K3[c2_i54];
  }

  c2_i_b = c2_h;
  for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
    c2_h_b[c2_i55] *= c2_i_b;
  }

  for (c2_i56 = 0; c2_i56 < 4; c2_i56++) {
    c2_e_xin[c2_i56] = ((c2_xin[c2_i56] + c2_b[c2_i56]) + c2_d_b[c2_i56]) +
      c2_h_b[c2_i56];
  }

  for (c2_i57 = 0; c2_i57 < 6; c2_i57++) {
    c2_e_hotpar[c2_i57] = c2_hotpar[c2_i57];
  }

  for (c2_i58 = 0; c2_i58 < 4; c2_i58++) {
    c2_e_coldpar[c2_i58] = c2_coldpar[c2_i58];
  }

  for (c2_i59 = 0; c2_i59 < 4; c2_i59++) {
    c2_e_wallpar[c2_i59] = c2_wallpar[c2_i59];
  }

  for (c2_i60 = 0; c2_i60 < 2; c2_i60++) {
    c2_e_input[c2_i60] = c2_input[c2_i60];
  }

  for (c2_i61 = 0; c2_i61 < 6; c2_i61++) {
    c2_e_noise[c2_i61] = c2_noise[c2_i61];
  }

  c2_heatexchangerpump(chartInstance, c2_e_xin, c2_e_hotpar, c2_e_coldpar,
                       c2_e_wallpar, c2_pumpar, c2_e_input, c2_e_noise, c2_dv5);
  for (c2_i62 = 0; c2_i62 < 4; c2_i62++) {
    c2_K4[c2_i62] = c2_dv5[c2_i62];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  for (c2_i63 = 0; c2_i63 < 4; c2_i63++) {
    c2_b[c2_i63] = c2_K1[c2_i63];
  }

  for (c2_i64 = 0; c2_i64 < 4; c2_i64++) {
    c2_b[c2_i64] *= 0.16666666666666666;
  }

  for (c2_i65 = 0; c2_i65 < 4; c2_i65++) {
    c2_d_b[c2_i65] = c2_K2[c2_i65];
  }

  for (c2_i66 = 0; c2_i66 < 4; c2_i66++) {
    c2_d_b[c2_i66] *= 0.33333333333333331;
  }

  for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
    c2_h_b[c2_i67] = c2_K3[c2_i67];
  }

  for (c2_i68 = 0; c2_i68 < 4; c2_i68++) {
    c2_h_b[c2_i68] *= 0.33333333333333331;
  }

  for (c2_i69 = 0; c2_i69 < 4; c2_i69++) {
    c2_j_b[c2_i69] = c2_K4[c2_i69];
  }

  for (c2_i70 = 0; c2_i70 < 4; c2_i70++) {
    c2_j_b[c2_i70] *= 0.16666666666666666;
  }

  for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
    c2_slope[c2_i71] = ((c2_b[c2_i71] + c2_d_b[c2_i71]) + c2_h_b[c2_i71]) +
      c2_j_b[c2_i71];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 41);
  for (c2_i72 = 0; c2_i72 < 4; c2_i72++) {
    c2_b[c2_i72] = c2_slope[c2_i72];
  }

  c2_k_b = c2_h;
  for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
    c2_b[c2_i73] *= c2_k_b;
  }

  for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
    c2_xout[c2_i74] = c2_xin[c2_i74] + c2_b[c2_i74];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  for (c2_i75 = 0; c2_i75 < 3; c2_i75++) {
    c2_l_b[c2_i75] = c2_v[c2_i75];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i76 = 0; c2_i76 < 3; c2_i76++) {
    c2_y[c2_i76] = 0.0;
    c2_i77 = 0;
    for (c2_i78 = 0; c2_i78 < 3; c2_i78++) {
      c2_y[c2_i76] += c2_a[c2_i77 + c2_i76] * c2_l_b[c2_i78];
      c2_i77 += 3;
    }
  }

  c2_b_Thi[0] = c2_Thi;
  c2_b_Thi[1] = c2_xin[0];
  c2_b_Thi[2] = c2_mdoth;
  for (c2_i79 = 0; c2_i79 < 3; c2_i79++) {
    c2_yout[c2_i79] = c2_b_Thi[c2_i79] + c2_y[c2_i79];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -42);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i80 = 0; c2_i80 < 4; c2_i80++) {
    (*c2_b_xout)[c2_i80] = c2_xout[c2_i80];
  }

  for (c2_i81 = 0; c2_i81 < 3; c2_i81++) {
    (*c2_b_yout)[c2_i81] = c2_yout[c2_i81];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
}

static void registerMessagesc2_HXpump_justplant
  (SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
}

static void c2_heatexchangerpump(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, real_T c2_x[4], real_T c2_hotpar[6], real_T c2_coldpar[4],
  real_T c2_wallpar[4], real_T c2_pumppar, real_T c2_input[2], real_T c2_noise[6],
  real_T c2_xdot[4])
{
  uint32_T c2_debug_family_var_map[32];
  real_T c2_rhoh;
  real_T c2_Vh;
  real_T c2_ch;
  real_T c2_mdoth;
  real_T c2_hh;
  real_T c2_Thi;
  real_T c2_rhoc;
  real_T c2_Vc;
  real_T c2_cc;
  real_T c2_hc;
  real_T c2_mdotc;
  real_T c2_Tci;
  real_T c2_rhow;
  real_T c2_Vw;
  real_T c2_cw;
  real_T c2_A;
  real_T c2_wp;
  real_T c2_wt;
  real_T c2_dx1;
  real_T c2_dx2;
  real_T c2_dx3;
  real_T c2_dx4;
  real_T c2_nargin = 7.0;
  real_T c2_nargout = 1.0;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_c_a;
  real_T c2_c_b;
  real_T c2_c_y;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_d_y;
  real_T c2_b_A;
  real_T c2_B;
  real_T c2_b_x;
  real_T c2_e_y;
  real_T c2_c_x;
  real_T c2_f_y;
  real_T c2_g_y;
  real_T c2_e_a;
  real_T c2_e_b;
  real_T c2_h_y;
  real_T c2_f_a;
  real_T c2_f_b;
  real_T c2_i_y;
  real_T c2_g_a;
  real_T c2_g_b;
  real_T c2_j_y;
  real_T c2_h_a;
  real_T c2_h_b;
  real_T c2_k_y;
  real_T c2_c_A;
  real_T c2_b_B;
  real_T c2_d_x;
  real_T c2_l_y;
  real_T c2_e_x;
  real_T c2_m_y;
  real_T c2_n_y;
  real_T c2_i_a;
  real_T c2_i_b;
  real_T c2_o_y;
  real_T c2_j_a;
  real_T c2_j_b;
  real_T c2_p_y;
  real_T c2_k_a;
  real_T c2_k_b;
  real_T c2_q_y;
  real_T c2_l_a;
  real_T c2_l_b;
  real_T c2_r_y;
  real_T c2_d_A;
  real_T c2_c_B;
  real_T c2_f_x;
  real_T c2_s_y;
  real_T c2_g_x;
  real_T c2_t_y;
  real_T c2_u_y;
  real_T c2_m_a;
  real_T c2_m_b;
  real_T c2_v_y;
  real_T c2_n_a;
  real_T c2_n_b;
  real_T c2_w_y;
  real_T c2_o_a;
  real_T c2_o_b;
  real_T c2_x_y;
  real_T c2_p_a;
  real_T c2_p_b;
  real_T c2_y_y;
  real_T c2_q_a;
  real_T c2_q_b;
  real_T c2_ab_y;
  real_T c2_e_A;
  real_T c2_d_B;
  real_T c2_h_x;
  real_T c2_bb_y;
  real_T c2_i_x;
  real_T c2_cb_y;
  real_T c2_db_y;
  real_T c2_r_a;
  real_T c2_r_b;
  real_T c2_eb_y;
  real_T c2_s_a;
  real_T c2_s_b;
  real_T c2_fb_y;
  real_T c2_t_a;
  real_T c2_t_b;
  real_T c2_gb_y;
  real_T c2_u_a;
  real_T c2_u_b;
  real_T c2_hb_y;
  real_T c2_f_A;
  real_T c2_e_B;
  real_T c2_j_x;
  real_T c2_ib_y;
  real_T c2_k_x;
  real_T c2_jb_y;
  real_T c2_kb_y;
  real_T c2_v_a;
  real_T c2_v_b;
  real_T c2_lb_y;
  real_T c2_w_a;
  real_T c2_w_b;
  real_T c2_mb_y;
  real_T c2_x_a;
  real_T c2_x_b;
  real_T c2_nb_y;
  real_T c2_y_a;
  real_T c2_y_b;
  real_T c2_ob_y;
  real_T c2_g_A;
  real_T c2_f_B;
  real_T c2_l_x;
  real_T c2_pb_y;
  real_T c2_m_x;
  real_T c2_qb_y;
  real_T c2_rb_y;
  real_T c2_ab_a;
  real_T c2_ab_b;
  real_T c2_sb_y;
  real_T c2_bb_a;
  real_T c2_bb_b;
  real_T c2_tb_y;
  real_T c2_cb_a;
  real_T c2_cb_b;
  real_T c2_ub_y;
  real_T c2_db_a;
  real_T c2_db_b;
  real_T c2_vb_y;
  real_T c2_eb_a;
  real_T c2_eb_b;
  real_T c2_wb_y;
  real_T c2_h_A;
  real_T c2_g_B;
  real_T c2_n_x;
  real_T c2_xb_y;
  real_T c2_o_x;
  real_T c2_yb_y;
  real_T c2_ac_y;
  real_T c2_fb_a;
  real_T c2_fb_b;
  real_T c2_bc_y;
  real_T c2_gb_a;
  real_T c2_gb_b;
  real_T c2_cc_y;
  real_T c2_hb_a;
  real_T c2_hb_b;
  real_T c2_dc_y;
  real_T c2_ib_a;
  real_T c2_ib_b;
  real_T c2_ec_y;
  real_T c2_i_A;
  real_T c2_h_B;
  real_T c2_p_x;
  real_T c2_fc_y;
  real_T c2_q_x;
  real_T c2_gc_y;
  real_T c2_hc_y;
  real_T c2_jb_a;
  real_T c2_jb_b;
  real_T c2_ic_y;
  real_T c2_kb_a;
  real_T c2_kb_b;
  real_T c2_jc_y;
  real_T c2_lb_a;
  real_T c2_lb_b;
  real_T c2_kc_y;
  real_T c2_mb_a;
  real_T c2_mb_b;
  real_T c2_lc_y;
  real_T c2_nb_a;
  real_T c2_nb_b;
  real_T c2_mc_y;
  real_T c2_j_A;
  real_T c2_i_B;
  real_T c2_r_x;
  real_T c2_nc_y;
  real_T c2_s_x;
  real_T c2_oc_y;
  real_T c2_pc_y;
  real_T c2_ob_a;
  real_T c2_ob_b;
  real_T c2_qc_y;
  real_T c2_pb_a;
  real_T c2_pb_b;
  real_T c2_rc_y;
  real_T c2_qb_a;
  real_T c2_qb_b;
  real_T c2_sc_y;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 32U, 32U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rhoh, 0U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Vh, 1U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ch, 2U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mdoth, 3U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_hh, 4U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Thi, 5U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rhoc, 6U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Vc, 7U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cc, 8U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_hc, 9U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mdotc, 10U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Tci, 11U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rhow, 12U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Vw, 13U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cw, 14U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_A, 15U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_wp, 16U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_wt, 17U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dx1, 18U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dx2, 19U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dx3, 20U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dx4, 21U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 22U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 23U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_x, 24U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_hotpar, 25U, c2_c_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_coldpar, 26U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_wallpar, 27U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_pumppar, 28U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_input, 29U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_noise, 30U, c2_c_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xdot, 31U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_rhoh = c2_hotpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_Vh = c2_hotpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_ch = c2_hotpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_mdoth = c2_hotpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_hh = c2_hotpar[4];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_Thi = c2_hotpar[5];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_rhoc = c2_coldpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_Vc = c2_coldpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_cc = c2_coldpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_hc = c2_coldpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 18);
  c2_mdotc = c2_input[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_Tci = c2_input[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 22);
  c2_rhow = c2_wallpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_Vw = c2_wallpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 24);
  c2_cw = c2_wallpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_A = c2_wallpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_wp = c2_pumppar;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_wt = c2_noise[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_a = c2_mdoth;
  c2_b = c2_ch;
  c2_y = c2_a * c2_b;
  c2_b_a = c2_hh;
  c2_b_b = c2_A;
  c2_b_y = c2_b_a * c2_b_b;
  c2_c_a = c2_rhoh;
  c2_c_b = c2_Vh;
  c2_c_y = c2_c_a * c2_c_b;
  c2_d_a = c2_c_y;
  c2_d_b = c2_ch;
  c2_d_y = c2_d_a * c2_d_b;
  c2_b_A = -(c2_y + c2_b_y);
  c2_B = c2_d_y;
  c2_b_x = c2_b_A;
  c2_e_y = c2_B;
  c2_c_x = c2_b_x;
  c2_f_y = c2_e_y;
  c2_g_y = c2_c_x / c2_f_y;
  c2_e_a = c2_g_y;
  c2_e_b = c2_x[0];
  c2_h_y = c2_e_a * c2_e_b;
  c2_f_a = c2_hh;
  c2_f_b = c2_A;
  c2_i_y = c2_f_a * c2_f_b;
  c2_g_a = c2_rhoh;
  c2_g_b = c2_Vh;
  c2_j_y = c2_g_a * c2_g_b;
  c2_h_a = c2_j_y;
  c2_h_b = c2_ch;
  c2_k_y = c2_h_a * c2_h_b;
  c2_c_A = c2_i_y;
  c2_b_B = c2_k_y;
  c2_d_x = c2_c_A;
  c2_l_y = c2_b_B;
  c2_e_x = c2_d_x;
  c2_m_y = c2_l_y;
  c2_n_y = c2_e_x / c2_m_y;
  c2_i_a = c2_n_y;
  c2_i_b = c2_x[2];
  c2_o_y = c2_i_a * c2_i_b;
  c2_j_a = c2_mdoth;
  c2_j_b = c2_ch;
  c2_p_y = c2_j_a * c2_j_b;
  c2_k_a = c2_rhoh;
  c2_k_b = c2_Vh;
  c2_q_y = c2_k_a * c2_k_b;
  c2_l_a = c2_q_y;
  c2_l_b = c2_ch;
  c2_r_y = c2_l_a * c2_l_b;
  c2_d_A = c2_p_y;
  c2_c_B = c2_r_y;
  c2_f_x = c2_d_A;
  c2_s_y = c2_c_B;
  c2_g_x = c2_f_x;
  c2_t_y = c2_s_y;
  c2_u_y = c2_g_x / c2_t_y;
  c2_m_a = c2_u_y;
  c2_m_b = c2_Thi;
  c2_v_y = c2_m_a * c2_m_b;
  c2_dx1 = (c2_h_y + c2_o_y) + c2_v_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_n_a = c2_x[3];
  c2_n_b = c2_cc;
  c2_w_y = c2_n_a * c2_n_b;
  c2_o_a = c2_hc;
  c2_o_b = c2_A;
  c2_x_y = c2_o_a * c2_o_b;
  c2_p_a = c2_rhoc;
  c2_p_b = c2_Vc;
  c2_y_y = c2_p_a * c2_p_b;
  c2_q_a = c2_y_y;
  c2_q_b = c2_cc;
  c2_ab_y = c2_q_a * c2_q_b;
  c2_e_A = -(c2_w_y + c2_x_y);
  c2_d_B = c2_ab_y;
  c2_h_x = c2_e_A;
  c2_bb_y = c2_d_B;
  c2_i_x = c2_h_x;
  c2_cb_y = c2_bb_y;
  c2_db_y = c2_i_x / c2_cb_y;
  c2_r_a = c2_db_y;
  c2_r_b = c2_x[1];
  c2_eb_y = c2_r_a * c2_r_b;
  c2_s_a = c2_hc;
  c2_s_b = c2_A;
  c2_fb_y = c2_s_a * c2_s_b;
  c2_t_a = c2_rhoc;
  c2_t_b = c2_Vc;
  c2_gb_y = c2_t_a * c2_t_b;
  c2_u_a = c2_gb_y;
  c2_u_b = c2_cc;
  c2_hb_y = c2_u_a * c2_u_b;
  c2_f_A = c2_fb_y;
  c2_e_B = c2_hb_y;
  c2_j_x = c2_f_A;
  c2_ib_y = c2_e_B;
  c2_k_x = c2_j_x;
  c2_jb_y = c2_ib_y;
  c2_kb_y = c2_k_x / c2_jb_y;
  c2_v_a = c2_kb_y;
  c2_v_b = c2_x[2];
  c2_lb_y = c2_v_a * c2_v_b;
  c2_w_a = c2_x[3];
  c2_w_b = c2_cc;
  c2_mb_y = c2_w_a * c2_w_b;
  c2_x_a = c2_rhoc;
  c2_x_b = c2_Vc;
  c2_nb_y = c2_x_a * c2_x_b;
  c2_y_a = c2_nb_y;
  c2_y_b = c2_cc;
  c2_ob_y = c2_y_a * c2_y_b;
  c2_g_A = c2_mb_y;
  c2_f_B = c2_ob_y;
  c2_l_x = c2_g_A;
  c2_pb_y = c2_f_B;
  c2_m_x = c2_l_x;
  c2_qb_y = c2_pb_y;
  c2_rb_y = c2_m_x / c2_qb_y;
  c2_ab_a = c2_rb_y;
  c2_ab_b = c2_Tci;
  c2_sb_y = c2_ab_a * c2_ab_b;
  c2_bb_a = c2_sb_y;
  c2_bb_b = 1.0 + c2_wt;
  c2_tb_y = c2_bb_a * c2_bb_b;
  c2_dx2 = (c2_eb_y + c2_lb_y) + c2_tb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 38);
  c2_cb_a = c2_hh;
  c2_cb_b = c2_A;
  c2_ub_y = c2_cb_a * c2_cb_b;
  c2_db_a = c2_rhow;
  c2_db_b = c2_Vw;
  c2_vb_y = c2_db_a * c2_db_b;
  c2_eb_a = c2_vb_y;
  c2_eb_b = c2_cw;
  c2_wb_y = c2_eb_a * c2_eb_b;
  c2_h_A = c2_ub_y;
  c2_g_B = c2_wb_y;
  c2_n_x = c2_h_A;
  c2_xb_y = c2_g_B;
  c2_o_x = c2_n_x;
  c2_yb_y = c2_xb_y;
  c2_ac_y = c2_o_x / c2_yb_y;
  c2_fb_a = c2_ac_y;
  c2_fb_b = c2_x[0];
  c2_bc_y = c2_fb_a * c2_fb_b;
  c2_gb_a = c2_hc;
  c2_gb_b = c2_A;
  c2_cc_y = c2_gb_a * c2_gb_b;
  c2_hb_a = c2_rhow;
  c2_hb_b = c2_Vw;
  c2_dc_y = c2_hb_a * c2_hb_b;
  c2_ib_a = c2_dc_y;
  c2_ib_b = c2_cw;
  c2_ec_y = c2_ib_a * c2_ib_b;
  c2_i_A = c2_cc_y;
  c2_h_B = c2_ec_y;
  c2_p_x = c2_i_A;
  c2_fc_y = c2_h_B;
  c2_q_x = c2_p_x;
  c2_gc_y = c2_fc_y;
  c2_hc_y = c2_q_x / c2_gc_y;
  c2_jb_a = c2_hc_y;
  c2_jb_b = c2_x[1];
  c2_ic_y = c2_jb_a * c2_jb_b;
  c2_kb_a = c2_hh;
  c2_kb_b = c2_A;
  c2_jc_y = c2_kb_a * c2_kb_b;
  c2_lb_a = c2_hc;
  c2_lb_b = c2_A;
  c2_kc_y = c2_lb_a * c2_lb_b;
  c2_mb_a = c2_rhow;
  c2_mb_b = c2_Vw;
  c2_lc_y = c2_mb_a * c2_mb_b;
  c2_nb_a = c2_lc_y;
  c2_nb_b = c2_cw;
  c2_mc_y = c2_nb_a * c2_nb_b;
  c2_j_A = c2_jc_y + c2_kc_y;
  c2_i_B = c2_mc_y;
  c2_r_x = c2_j_A;
  c2_nc_y = c2_i_B;
  c2_s_x = c2_r_x;
  c2_oc_y = c2_nc_y;
  c2_pc_y = c2_s_x / c2_oc_y;
  c2_ob_a = c2_pc_y;
  c2_ob_b = c2_x[2];
  c2_qc_y = c2_ob_a * c2_ob_b;
  c2_dx3 = (c2_bc_y + c2_ic_y) - c2_qc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 40);
  c2_pb_a = -c2_wp;
  c2_pb_b = c2_x[3];
  c2_rc_y = c2_pb_a * c2_pb_b;
  c2_qb_a = c2_wp;
  c2_qb_b = c2_mdotc;
  c2_sc_y = c2_qb_a * c2_qb_b;
  c2_dx4 = c2_rc_y + c2_sc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 42);
  c2_xdot[0] = c2_dx1;
  c2_xdot[1] = c2_dx2;
  c2_xdot[2] = c2_dx3;
  c2_xdot[3] = c2_dx4;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -42);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 0U, sf_debug_get_script_id(
    "C:/Users/LabUser/Desktop/heat exchanger nuclear sanity/heat exchanger pump July 18 2016/heatexchangerpump.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i82;
  real_T c2_b_inData[3];
  int32_T c2_i83;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 3; c2_i82++) {
    c2_b_inData[c2_i82] = (*(real_T (*)[3])c2_inData)[c2_i82];
  }

  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    c2_u[c2_i83] = c2_b_inData[c2_i83];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_yout, const char_T *c2_identifier, real_T
  c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_yout), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_yout);
}

static void c2_b_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv6[3];
  int32_T c2_i84;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
    c2_y[c2_i84] = c2_dv6[c2_i84];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_yout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i85;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_yout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_yout), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_yout);
  for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
    (*(real_T (*)[3])c2_outData)[c2_i85] = c2_y[c2_i85];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i86;
  real_T c2_b_inData[4];
  int32_T c2_i87;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
    c2_b_inData[c2_i86] = (*(real_T (*)[4])c2_inData)[c2_i86];
  }

  for (c2_i87 = 0; c2_i87 < 4; c2_i87++) {
    c2_u[c2_i87] = c2_b_inData[c2_i87];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_xout, const char_T *c2_identifier, real_T
  c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_xout), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_xout);
}

static void c2_d_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv7[4];
  int32_T c2_i88;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
    c2_y[c2_i88] = c2_dv7[c2_i88];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_xout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i89;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_xout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_xout), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_xout);
  for (c2_i89 = 0; c2_i89 < 4; c2_i89++) {
    (*(real_T (*)[4])c2_outData)[c2_i89] = c2_y[c2_i89];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i90;
  real_T c2_b_inData[6];
  int32_T c2_i91;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i90 = 0; c2_i90 < 6; c2_i90++) {
    c2_b_inData[c2_i90] = (*(real_T (*)[6])c2_inData)[c2_i90];
  }

  for (c2_i91 = 0; c2_i91 < 6; c2_i91++) {
    c2_u[c2_i91] = c2_b_inData[c2_i91];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i92;
  real_T c2_b_inData[2];
  int32_T c2_i93;
  real_T c2_u[2];
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i92 = 0; c2_i92 < 2; c2_i92++) {
    c2_b_inData[c2_i92] = (*(real_T (*)[2])c2_inData)[c2_i92];
  }

  for (c2_i93 = 0; c2_i93 < 2; c2_i93++) {
    c2_u[c2_i93] = c2_b_inData[c2_i93];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_f_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6])
{
  real_T c2_dv8[6];
  int32_T c2_i94;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv8, 1, 0, 0U, 1, 0U, 1, 6);
  for (c2_i94 = 0; c2_i94 < 6; c2_i94++) {
    c2_y[c2_i94] = c2_dv8[c2_i94];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_noise;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i95;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_noise = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_noise), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_noise);
  for (c2_i95 = 0; c2_i95 < 6; c2_i95++) {
    (*(real_T (*)[6])c2_outData)[c2_i95] = c2_y[c2_i95];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_g_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[2])
{
  real_T c2_dv9[2];
  int32_T c2_i96;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv9, 1, 0, 0U, 1, 0U, 1, 2);
  for (c2_i96 = 0; c2_i96 < 2; c2_i96++) {
    c2_y[c2_i96] = c2_dv9[c2_i96];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_input;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[2];
  int32_T c2_i97;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_input = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_input), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_input);
  for (c2_i97 = 0; c2_i97 < 2; c2_i97++) {
    (*(real_T (*)[2])c2_outData)[c2_i97] = c2_y[c2_i97];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_HXpump_justplant_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[32];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i98;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 32), FALSE);
  for (c2_i98 = 0; c2_i98 < 32; c2_i98++) {
    c2_r0 = &c2_info[c2_i98];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i98);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[32])
{
  c2_info[0].context = "";
  c2_info[0].name = "mrdivide";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[0].fileTimeLo = 1357973148U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 1319751566U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].name = "rdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[1].fileTimeLo = 1346531988U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].name = "eml_scalexp_compatible";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[2].fileTimeLo = 1286840396U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[3].name = "eml_div";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[3].fileTimeLo = 1313369410U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "";
  c2_info[4].name = "heatexchangerpump";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[E]C:/Users/LabUser/Desktop/heat exchanger nuclear sanity/heat exchanger pump July 18 2016/heatexchangerpump.m";
  c2_info[4].fileTimeLo = 1469026235U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context =
    "[E]C:/Users/LabUser/Desktop/heat exchanger nuclear sanity/heat exchanger pump July 18 2016/heatexchangerpump.m";
  c2_info[5].name = "mtimes";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[5].fileTimeLo = 1289541292U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[E]C:/Users/LabUser/Desktop/heat exchanger nuclear sanity/heat exchanger pump July 18 2016/heatexchangerpump.m";
  c2_info[6].name = "mrdivide";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[6].fileTimeLo = 1357973148U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 1319751566U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "";
  c2_info[7].name = "mtimes";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[7].fileTimeLo = 1289541292U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "";
  c2_info[8].name = "eye";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c2_info[8].fileTimeLo = 1286840288U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[9].name = "eml_assert_valid_size_arg";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[9].fileTimeLo = 1286840294U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[10].name = "isinf";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[10].fileTimeLo = 1286840360U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[11].name = "mtimes";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[11].fileTimeLo = 1289541292U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[12].name = "eml_index_class";
  c2_info[12].dominantType = "";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[12].fileTimeLo = 1323192178U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[13].name = "intmax";
  c2_info[13].dominantType = "char";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[13].fileTimeLo = 1311276916U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[14].name = "eml_is_float_class";
  c2_info[14].dominantType = "char";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[14].fileTimeLo = 1286840382U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[15].name = "min";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[15].fileTimeLo = 1311276918U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[16].name = "eml_min_or_max";
  c2_info[16].dominantType = "char";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[16].fileTimeLo = 1334093090U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[17].name = "eml_scalar_eg";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[17].fileTimeLo = 1286840396U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[18].name = "eml_scalexp_alloc";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[18].fileTimeLo = 1352446460U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[19].name = "eml_index_class";
  c2_info[19].dominantType = "";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[19].fileTimeLo = 1323192178U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[20].name = "eml_scalar_eg";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[20].fileTimeLo = 1286840396U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[21].name = "eml_index_class";
  c2_info[21].dominantType = "";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[21].fileTimeLo = 1323192178U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[22].name = "eml_int_forloop_overflow_check";
  c2_info[22].dominantType = "";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[22].fileTimeLo = 1346531940U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[23].name = "intmax";
  c2_info[23].dominantType = "char";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[23].fileTimeLo = 1311276916U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[24].name = "eml_index_class";
  c2_info[24].dominantType = "";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[24].fileTimeLo = 1323192178U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[25].name = "eml_scalar_eg";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[25].fileTimeLo = 1286840396U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[26].name = "eml_xgemm";
  c2_info[26].dominantType = "char";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[26].fileTimeLo = 1299098372U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[27].name = "eml_blas_inline";
  c2_info[27].dominantType = "";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[27].fileTimeLo = 1299098368U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c2_info[28].name = "mtimes";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[28].fileTimeLo = 1289541292U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[29].name = "eml_index_class";
  c2_info[29].dominantType = "";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[29].fileTimeLo = 1323192178U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[30].name = "eml_scalar_eg";
  c2_info[30].dominantType = "double";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[30].fileTimeLo = 1286840396U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[31].name = "eml_refblas_xgemm";
  c2_info[31].dominantType = "char";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[31].fileTimeLo = 1299098374U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
}

static void c2_eml_scalar_eg(SFc2_HXpump_justplantInstanceStruct *chartInstance)
{
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_h_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i99;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i99, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i99;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_HXpump_justplant, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_HXpump_justplant), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_HXpump_justplant);
  return c2_y;
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_HXpump_justplantInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_HXpump_justplantInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_HXpump_justplant_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1820699231U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2970307431U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1761467818U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1466221644U);
}

mxArray *sf_c2_HXpump_justplant_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("OkuvlAHznSIS88Zh55EJsD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_HXpump_justplant_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_HXpump_justplant(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"xout\",},{M[1],M[11],T\"yout\",},{M[8],M[0],T\"is_active_c2_HXpump_justplant\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_HXpump_justplant_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_HXpump_justplantInstanceStruct *chartInstance;
    chartInstance = (SFc2_HXpump_justplantInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HXpump_justplantMachineNumber_,
           2,
           1,
           1,
           10,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_HXpump_justplantMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HXpump_justplantMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HXpump_justplantMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"xin");
          _SFD_SET_DATA_PROPS(1,2,0,1,"xout");
          _SFD_SET_DATA_PROPS(2,1,1,0,"hotpar");
          _SFD_SET_DATA_PROPS(3,1,1,0,"coldpar");
          _SFD_SET_DATA_PROPS(4,1,1,0,"wallpar");
          _SFD_SET_DATA_PROPS(5,1,1,0,"pumpar");
          _SFD_SET_DATA_PROPS(6,1,1,0,"input");
          _SFD_SET_DATA_PROPS(7,1,1,0,"simpar");
          _SFD_SET_DATA_PROPS(8,1,1,0,"noise");
          _SFD_SET_DATA_PROPS(9,2,0,1,"yout");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,901);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"heatexchangerpump",0,-1,918);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T *c2_pumpar;
          real_T *c2_simpar;
          real_T (*c2_xin)[4];
          real_T (*c2_xout)[4];
          real_T (*c2_hotpar)[6];
          real_T (*c2_coldpar)[4];
          real_T (*c2_wallpar)[4];
          real_T (*c2_input)[2];
          real_T (*c2_noise)[6];
          real_T (*c2_yout)[3];
          c2_yout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_noise = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 7);
          c2_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c2_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
          c2_pumpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c2_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
          c2_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
          c2_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c2_xout = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_xin = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_xin);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_xout);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_hotpar);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_coldpar);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_wallpar);
          _SFD_SET_DATA_VALUE_PTR(5U, c2_pumpar);
          _SFD_SET_DATA_VALUE_PTR(6U, *c2_input);
          _SFD_SET_DATA_VALUE_PTR(7U, c2_simpar);
          _SFD_SET_DATA_VALUE_PTR(8U, *c2_noise);
          _SFD_SET_DATA_VALUE_PTR(9U, *c2_yout);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HXpump_justplantMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "M1PoyWX7cSktxizx9tqpl";
}

static void sf_opaque_initialize_c2_HXpump_justplant(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar);
  initialize_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_HXpump_justplant(void *chartInstanceVar)
{
  enable_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_HXpump_justplant(void *chartInstanceVar)
{
  disable_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_HXpump_justplant(void *chartInstanceVar)
{
  sf_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_HXpump_justplant(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_HXpump_justplant
    ((SFc2_HXpump_justplantInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_HXpump_justplant();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_HXpump_justplant(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_HXpump_justplant();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_HXpump_justplant(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_HXpump_justplant(S);
}

static void sf_opaque_set_sim_state_c2_HXpump_justplant(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_HXpump_justplant(S, st);
}

static void sf_opaque_terminate_c2_HXpump_justplant(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_HXpump_justplantInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HXpump_justplant_optimization_info();
    }

    finalize_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_HXpump_justplant(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_HXpump_justplant((SFc2_HXpump_justplantInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_HXpump_justplant(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HXpump_justplant_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3026932252U));
  ssSetChecksum1(S,(226909982U));
  ssSetChecksum2(S,(2658181152U));
  ssSetChecksum3(S,(382197606U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_HXpump_justplant(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_HXpump_justplant(SimStruct *S)
{
  SFc2_HXpump_justplantInstanceStruct *chartInstance;
  chartInstance = (SFc2_HXpump_justplantInstanceStruct *)utMalloc(sizeof
    (SFc2_HXpump_justplantInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_HXpump_justplantInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_HXpump_justplant;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_HXpump_justplant;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_HXpump_justplant;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_HXpump_justplant;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_HXpump_justplant;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_HXpump_justplant;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_HXpump_justplant;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_HXpump_justplant;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_HXpump_justplant;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_HXpump_justplant;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_HXpump_justplant;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_HXpump_justplant_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_HXpump_justplant(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_HXpump_justplant(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_HXpump_justplant(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_HXpump_justplant_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
