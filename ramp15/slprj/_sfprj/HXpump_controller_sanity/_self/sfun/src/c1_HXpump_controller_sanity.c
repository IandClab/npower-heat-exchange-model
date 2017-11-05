/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HXpump_controller_sanity_sfun.h"
#include "c1_HXpump_controller_sanity.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HXpump_controller_sanity_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[73] = { "h", "rhoh", "Vh", "ch",
  "mdoth", "hh", "Thi", "rhoc", "Vc", "cc", "hc", "mdotc", "Tci", "rhow", "Vw",
  "cw", "A", "wp", "wa", "wb", "Sw_tc", "Sw_mh", "Sw_th", "Sw", "Sv_thi",
  "Sv_tho", "Sv_mh", "Sv", "c1", "c2", "c3", "c4", "a2", "a3", "a4", "b21",
  "b31", "b32", "b41", "b42", "b43", "K1", "K2", "K3", "K4", "slope", "ACT",
  "BwCT", "CCT", "ADT", "BwDT", "CDT", "xhat", "Pneg", "yhat", "inov", "inocov",
  "L", "nargin", "nargout", "xhatin", "hotpar", "coldpar", "wallpar", "pumppar",
  "input", "simpar", "y", "noisePSD", "Pin", "xhatout", "yhatout", "Pout" };

static const char * c1_b_debug_family_names[34] = { "rhoh", "Vh", "ch", "mdoth",
  "hh", "Thi", "rhoc", "Vc", "cc", "hc", "mdotc", "Tci", "rhow", "Vw", "cw", "A",
  "wp", "wa", "wb", "dx1", "dx2", "dx3", "dx4", "dx5", "dx6", "nargin",
  "nargout", "x", "hotpar", "coldpar", "wallpar", "pumppar", "input", "xdot" };

/* Function Declarations */
static void initialize_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void initialize_params_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void enable_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void disable_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void set_sim_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, const mxArray
   *c1_st);
static void finalize_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void sf_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void c1_chartstep_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void initSimStructsc1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void registerMessagesc1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance);
static void c1_EKFdynamics(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_x[6], real_T c1_hotpar[6], real_T c1_coldpar[4],
  real_T c1_wallpar[4], real_T c1_pumppar[3], real_T c1_input[2], real_T
  c1_xdot[6]);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_Pout, const char_T *c1_identifier, real_T
  c1_y[36]);
static void c1_b_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[36]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_yhatout, const char_T *c1_identifier, real_T
  c1_y[3]);
static void c1_d_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_xhatout, const char_T *c1_identifier, real_T
  c1_y[6]);
static void c1_f_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[6]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_g_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_h_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[18]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_i_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[9]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_j_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_k_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[120]);
static void c1_b_info_helper(c1_ResolvedFunctionInfo c1_info[120]);
static void c1_diag(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                    real_T c1_v[3], real_T c1_d[9]);
static void c1_eye(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                   real_T c1_I[36]);
static void c1_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_mpower(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_a[36], real_T c1_c[36]);
static void c1_b_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_c_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36]);
static real_T c1_b_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a);
static void c1_c_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a[36], real_T c1_c[36]);
static void c1_b_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36]);
static real_T c1_d_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a);
static void c1_e_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a[36], real_T c1_c[36]);
static void c1_c_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36]);
static real_T c1_f_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a);
static void c1_d_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_e_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_f_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_g_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_h_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_i_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_inv(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                   real_T c1_x[9], real_T c1_y[9]);
static void c1_inv3x3(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_x[9], real_T c1_y[9]);
static real_T c1_norm(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_x[9]);
static void c1_eml_warning(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_b_eml_warning(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, char_T c1_varargin_2[14]);
static void c1_j_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);
static void c1_l_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_sprintf, const char_T *c1_identifier, char_T
  c1_y[14]);
static void c1_m_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[14]);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_n_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_o_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_HXpump_controller_sanity,
  const char_T *c1_identifier);
static uint8_T c1_p_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_HXpump_controller_sanity = 0U;
}

static void initialize_params_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
}

static void enable_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[36];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i1;
  real_T c1_b_u[6];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i2;
  real_T c1_c_u[3];
  const mxArray *c1_d_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T (*c1_yhatout)[3];
  real_T (*c1_xhatout)[6];
  real_T (*c1_Pout)[36];
  c1_Pout = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_yhatout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_xhatout = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(4), FALSE);
  for (c1_i0 = 0; c1_i0 < 36; c1_i0++) {
    c1_u[c1_i0] = (*c1_Pout)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i1 = 0; c1_i1 < 6; c1_i1++) {
    c1_b_u[c1_i1] = (*c1_xhatout)[c1_i1];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    c1_c_u[c1_i2] = (*c1_yhatout)[c1_i2];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_HXpump_controller_sanity;
  c1_d_u = c1_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, const mxArray
   *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[36];
  int32_T c1_i3;
  real_T c1_dv1[6];
  int32_T c1_i4;
  real_T c1_dv2[3];
  int32_T c1_i5;
  real_T (*c1_Pout)[36];
  real_T (*c1_xhatout)[6];
  real_T (*c1_yhatout)[3];
  c1_Pout = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_yhatout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_xhatout = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)), "Pout",
                      c1_dv0);
  for (c1_i3 = 0; c1_i3 < 36; c1_i3++) {
    (*c1_Pout)[c1_i3] = c1_dv0[c1_i3];
  }

  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
                        "xhatout", c1_dv1);
  for (c1_i4 = 0; c1_i4 < 6; c1_i4++) {
    (*c1_xhatout)[c1_i4] = c1_dv1[c1_i4];
  }

  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
                        "yhatout", c1_dv2);
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    (*c1_yhatout)[c1_i5] = c1_dv2[c1_i5];
  }

  chartInstance->c1_is_active_c1_HXpump_controller_sanity =
    c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 3)),
    "is_active_c1_HXpump_controller_sanity");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_HXpump_controller_sanity(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
}

static void sf_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  int32_T c1_i15;
  int32_T c1_i16;
  int32_T c1_i17;
  real_T *c1_simpar;
  real_T (*c1_Pout)[36];
  real_T (*c1_yhatout)[3];
  real_T (*c1_xhatout)[6];
  real_T (*c1_Pin)[36];
  real_T (*c1_noisePSD)[6];
  real_T (*c1_y)[3];
  real_T (*c1_input)[2];
  real_T (*c1_pumppar)[3];
  real_T (*c1_wallpar)[4];
  real_T (*c1_coldpar)[4];
  real_T (*c1_hotpar)[6];
  real_T (*c1_xhatin)[6];
  c1_Pout = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_yhatout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_xhatout = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_Pin = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 9);
  c1_noisePSD = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 8);
  c1_y = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
  c1_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c1_pumppar = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c1_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c1_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c1_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c1_xhatin = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i6 = 0; c1_i6 < 6; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*c1_xhatin)[c1_i6], 0U);
  }

  for (c1_i7 = 0; c1_i7 < 6; c1_i7++) {
    _SFD_DATA_RANGE_CHECK((*c1_hotpar)[c1_i7], 1U);
  }

  for (c1_i8 = 0; c1_i8 < 4; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((*c1_coldpar)[c1_i8], 2U);
  }

  for (c1_i9 = 0; c1_i9 < 4; c1_i9++) {
    _SFD_DATA_RANGE_CHECK((*c1_wallpar)[c1_i9], 3U);
  }

  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    _SFD_DATA_RANGE_CHECK((*c1_pumppar)[c1_i10], 4U);
  }

  for (c1_i11 = 0; c1_i11 < 2; c1_i11++) {
    _SFD_DATA_RANGE_CHECK((*c1_input)[c1_i11], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_simpar, 6U);
  for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
    _SFD_DATA_RANGE_CHECK((*c1_y)[c1_i12], 7U);
  }

  for (c1_i13 = 0; c1_i13 < 6; c1_i13++) {
    _SFD_DATA_RANGE_CHECK((*c1_noisePSD)[c1_i13], 8U);
  }

  for (c1_i14 = 0; c1_i14 < 36; c1_i14++) {
    _SFD_DATA_RANGE_CHECK((*c1_Pin)[c1_i14], 9U);
  }

  for (c1_i15 = 0; c1_i15 < 6; c1_i15++) {
    _SFD_DATA_RANGE_CHECK((*c1_xhatout)[c1_i15], 10U);
  }

  for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
    _SFD_DATA_RANGE_CHECK((*c1_yhatout)[c1_i16], 11U);
  }

  for (c1_i17 = 0; c1_i17 < 36; c1_i17++) {
    _SFD_DATA_RANGE_CHECK((*c1_Pout)[c1_i17], 12U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_HXpump_controller_sanity(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HXpump_controller_sanityMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  int32_T c1_i18;
  real_T c1_xhatin[6];
  int32_T c1_i19;
  real_T c1_hotpar[6];
  int32_T c1_i20;
  real_T c1_coldpar[4];
  int32_T c1_i21;
  real_T c1_wallpar[4];
  int32_T c1_i22;
  real_T c1_pumppar[3];
  int32_T c1_i23;
  real_T c1_input[2];
  real_T c1_simpar;
  int32_T c1_i24;
  real_T c1_y[3];
  int32_T c1_i25;
  real_T c1_noisePSD[6];
  int32_T c1_i26;
  real_T c1_Pin[36];
  uint32_T c1_debug_family_var_map[73];
  real_T c1_h;
  real_T c1_rhoh;
  real_T c1_Vh;
  real_T c1_ch;
  real_T c1_mdoth;
  real_T c1_hh;
  real_T c1_Thi;
  real_T c1_rhoc;
  real_T c1_Vc;
  real_T c1_cc;
  real_T c1_hc;
  real_T c1_mdotc;
  real_T c1_Tci;
  real_T c1_rhow;
  real_T c1_Vw;
  real_T c1_cw;
  real_T c1_A;
  real_T c1_wp;
  real_T c1_wa;
  real_T c1_wb;
  real_T c1_Sw_tc;
  real_T c1_Sw_mh;
  real_T c1_Sw_th;
  real_T c1_Sw[9];
  real_T c1_Sv_thi;
  real_T c1_Sv_tho;
  real_T c1_Sv_mh;
  real_T c1_Sv[9];
  real_T c1_c1;
  real_T c1_c2;
  real_T c1_c3;
  real_T c1_c4;
  real_T c1_a2;
  real_T c1_a3;
  real_T c1_a4;
  real_T c1_b21;
  real_T c1_b31;
  real_T c1_b32;
  real_T c1_b41;
  real_T c1_b42;
  real_T c1_b43;
  real_T c1_K1[6];
  real_T c1_K2[6];
  real_T c1_K3[6];
  real_T c1_K4[6];
  real_T c1_slope[6];
  real_T c1_ACT[36];
  real_T c1_BwCT[18];
  real_T c1_CCT[18];
  real_T c1_ADT[36];
  real_T c1_BwDT[18];
  real_T c1_CDT[18];
  real_T c1_xhat[6];
  real_T c1_Pneg[36];
  real_T c1_yhat[3];
  real_T c1_inov[3];
  real_T c1_inocov[9];
  real_T c1_L[18];
  real_T c1_nargin = 10.0;
  real_T c1_nargout = 3.0;
  real_T c1_xhatout[6];
  real_T c1_yhatout[3];
  real_T c1_Pout[36];
  real_T c1_b_Sw_tc[3];
  real_T c1_dv3[9];
  int32_T c1_i27;
  real_T c1_b_Sv_thi[3];
  real_T c1_dv4[9];
  int32_T c1_i28;
  int32_T c1_i29;
  real_T c1_b_xhatin[6];
  int32_T c1_i30;
  real_T c1_b_hotpar[6];
  int32_T c1_i31;
  real_T c1_b_coldpar[4];
  int32_T c1_i32;
  real_T c1_b_wallpar[4];
  int32_T c1_i33;
  real_T c1_b_pumppar[3];
  int32_T c1_i34;
  real_T c1_b_input[2];
  real_T c1_dv5[6];
  int32_T c1_i35;
  int32_T c1_i36;
  real_T c1_b[6];
  int32_T c1_i37;
  real_T c1_b_b;
  int32_T c1_i38;
  int32_T c1_i39;
  real_T c1_c_xhatin[6];
  int32_T c1_i40;
  real_T c1_c_hotpar[6];
  int32_T c1_i41;
  real_T c1_c_coldpar[4];
  int32_T c1_i42;
  real_T c1_c_wallpar[4];
  int32_T c1_i43;
  real_T c1_c_pumppar[3];
  int32_T c1_i44;
  real_T c1_c_input[2];
  real_T c1_dv6[6];
  int32_T c1_i45;
  int32_T c1_i46;
  int32_T c1_i47;
  real_T c1_c_b;
  int32_T c1_i48;
  int32_T c1_i49;
  real_T c1_d_b[6];
  int32_T c1_i50;
  real_T c1_e_b;
  int32_T c1_i51;
  int32_T c1_i52;
  real_T c1_d_xhatin[6];
  int32_T c1_i53;
  real_T c1_d_hotpar[6];
  int32_T c1_i54;
  real_T c1_d_coldpar[4];
  int32_T c1_i55;
  real_T c1_d_wallpar[4];
  int32_T c1_i56;
  real_T c1_d_pumppar[3];
  int32_T c1_i57;
  real_T c1_d_input[2];
  real_T c1_dv7[6];
  int32_T c1_i58;
  int32_T c1_i59;
  int32_T c1_i60;
  real_T c1_f_b;
  int32_T c1_i61;
  int32_T c1_i62;
  int32_T c1_i63;
  real_T c1_g_b;
  int32_T c1_i64;
  int32_T c1_i65;
  real_T c1_h_b[6];
  real_T c1_i_b;
  int32_T c1_i66;
  int32_T c1_i67;
  real_T c1_e_xhatin[6];
  int32_T c1_i68;
  real_T c1_e_hotpar[6];
  int32_T c1_i69;
  real_T c1_e_coldpar[4];
  int32_T c1_i70;
  real_T c1_e_wallpar[4];
  int32_T c1_i71;
  real_T c1_e_pumppar[3];
  int32_T c1_i72;
  real_T c1_e_input[2];
  real_T c1_dv8[6];
  int32_T c1_i73;
  int32_T c1_i74;
  int32_T c1_i75;
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  int32_T c1_i79;
  int32_T c1_i80;
  real_T c1_j_b[6];
  int32_T c1_i81;
  int32_T c1_i82;
  real_T c1_a;
  real_T c1_k_b;
  real_T c1_b_y;
  real_T c1_b_a;
  real_T c1_l_b;
  real_T c1_c_y;
  real_T c1_c_a;
  real_T c1_m_b;
  real_T c1_d_y;
  real_T c1_d_a;
  real_T c1_n_b;
  real_T c1_e_y;
  real_T c1_b_A;
  real_T c1_B;
  real_T c1_x;
  real_T c1_f_y;
  real_T c1_b_x;
  real_T c1_g_y;
  real_T c1_h_y;
  real_T c1_e_a;
  real_T c1_o_b;
  real_T c1_i_y;
  real_T c1_f_a;
  real_T c1_p_b;
  real_T c1_j_y;
  real_T c1_g_a;
  real_T c1_q_b;
  real_T c1_k_y;
  real_T c1_c_A;
  real_T c1_b_B;
  real_T c1_c_x;
  real_T c1_l_y;
  real_T c1_d_x;
  real_T c1_m_y;
  real_T c1_n_y;
  real_T c1_h_a;
  real_T c1_r_b;
  real_T c1_o_y;
  real_T c1_i_a;
  real_T c1_s_b;
  real_T c1_p_y;
  real_T c1_j_a;
  real_T c1_t_b;
  real_T c1_q_y;
  real_T c1_d_A;
  real_T c1_c_B;
  real_T c1_e_x;
  real_T c1_r_y;
  real_T c1_f_x;
  real_T c1_s_y;
  real_T c1_t_y;
  real_T c1_k_a;
  real_T c1_u_b;
  real_T c1_u_y;
  real_T c1_l_a;
  real_T c1_v_b;
  real_T c1_v_y;
  real_T c1_m_a;
  real_T c1_w_b;
  real_T c1_w_y;
  real_T c1_e_A;
  real_T c1_d_B;
  real_T c1_g_x;
  real_T c1_x_y;
  real_T c1_h_x;
  real_T c1_y_y;
  real_T c1_ab_y;
  real_T c1_n_a;
  real_T c1_x_b;
  real_T c1_bb_y;
  real_T c1_o_a;
  real_T c1_y_b;
  real_T c1_cb_y;
  real_T c1_p_a;
  real_T c1_ab_b;
  real_T c1_db_y;
  real_T c1_q_a;
  real_T c1_bb_b;
  real_T c1_eb_y;
  real_T c1_f_A;
  real_T c1_e_B;
  real_T c1_i_x;
  real_T c1_fb_y;
  real_T c1_j_x;
  real_T c1_gb_y;
  real_T c1_hb_y;
  real_T c1_r_a;
  real_T c1_cb_b;
  real_T c1_ib_y;
  real_T c1_s_a;
  real_T c1_db_b;
  real_T c1_jb_y;
  real_T c1_t_a;
  real_T c1_eb_b;
  real_T c1_kb_y;
  real_T c1_g_A;
  real_T c1_f_B;
  real_T c1_k_x;
  real_T c1_lb_y;
  real_T c1_l_x;
  real_T c1_mb_y;
  real_T c1_nb_y;
  real_T c1_u_a;
  real_T c1_fb_b;
  real_T c1_ob_y;
  real_T c1_v_a;
  real_T c1_gb_b;
  real_T c1_pb_y;
  real_T c1_w_a;
  real_T c1_hb_b;
  real_T c1_qb_y;
  real_T c1_h_A;
  real_T c1_g_B;
  real_T c1_m_x;
  real_T c1_rb_y;
  real_T c1_n_x;
  real_T c1_sb_y;
  real_T c1_tb_y;
  real_T c1_x_a;
  real_T c1_ib_b;
  real_T c1_ub_y;
  real_T c1_y_a;
  real_T c1_jb_b;
  real_T c1_vb_y;
  real_T c1_ab_a;
  real_T c1_kb_b;
  real_T c1_wb_y;
  real_T c1_i_A;
  real_T c1_h_B;
  real_T c1_o_x;
  real_T c1_xb_y;
  real_T c1_p_x;
  real_T c1_yb_y;
  real_T c1_ac_y;
  real_T c1_bb_a;
  real_T c1_lb_b;
  real_T c1_bc_y;
  real_T c1_cb_a;
  real_T c1_mb_b;
  real_T c1_cc_y;
  real_T c1_db_a;
  real_T c1_nb_b;
  real_T c1_dc_y;
  real_T c1_j_A;
  real_T c1_i_B;
  real_T c1_q_x;
  real_T c1_ec_y;
  real_T c1_r_x;
  real_T c1_fc_y;
  real_T c1_gc_y;
  real_T c1_eb_a;
  real_T c1_ob_b;
  real_T c1_hc_y;
  real_T c1_fb_a;
  real_T c1_pb_b;
  real_T c1_ic_y;
  real_T c1_gb_a;
  real_T c1_qb_b;
  real_T c1_jc_y;
  real_T c1_hb_a;
  real_T c1_rb_b;
  real_T c1_kc_y;
  real_T c1_k_A;
  real_T c1_j_B;
  real_T c1_s_x;
  real_T c1_lc_y;
  real_T c1_t_x;
  real_T c1_mc_y;
  real_T c1_nc_y;
  real_T c1_ib_a;
  real_T c1_sb_b;
  real_T c1_oc_y;
  real_T c1_jb_a;
  real_T c1_tb_b;
  real_T c1_pc_y;
  real_T c1_kb_a;
  real_T c1_ub_b;
  real_T c1_qc_y;
  real_T c1_l_A;
  real_T c1_k_B;
  real_T c1_u_x;
  real_T c1_rc_y;
  real_T c1_v_x;
  real_T c1_sc_y;
  real_T c1_tc_y;
  real_T c1_lb_a;
  real_T c1_vb_b;
  real_T c1_uc_y;
  int32_T c1_i83;
  int32_T c1_i84;
  int32_T c1_i85;
  int32_T c1_i86;
  int32_T c1_i87;
  int32_T c1_i88;
  static real_T c1_dv9[3] = { 0.0, 1.0, 0.0 };

  int32_T c1_i89;
  int32_T c1_i90;
  static real_T c1_dv10[3] = { 0.0, 0.0, 1.0 };

  int32_T c1_i91;
  int32_T c1_i92;
  int32_T c1_i93;
  static real_T c1_mb_a[18] = { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c1_i94;
  real_T c1_nb_a[36];
  real_T c1_wb_b;
  int32_T c1_i95;
  int32_T c1_i96;
  real_T c1_b_ACT[36];
  real_T c1_ob_a[36];
  real_T c1_xb_b;
  int32_T c1_i97;
  int32_T c1_i98;
  int32_T c1_i99;
  real_T c1_c_ACT[36];
  real_T c1_pb_a[36];
  real_T c1_yb_b;
  int32_T c1_i100;
  int32_T c1_i101;
  int32_T c1_i102;
  real_T c1_d_ACT[36];
  real_T c1_qb_a[36];
  real_T c1_ac_b;
  int32_T c1_i103;
  int32_T c1_i104;
  real_T c1_dv11[36];
  int32_T c1_i105;
  int32_T c1_i106;
  real_T c1_rb_a[18];
  real_T c1_bc_b;
  int32_T c1_i107;
  int32_T c1_i108;
  int32_T c1_i109;
  real_T c1_cc_b[18];
  int32_T c1_i110;
  int32_T c1_i111;
  int32_T c1_i112;
  real_T c1_vc_y[18];
  int32_T c1_i113;
  int32_T c1_i114;
  real_T c1_dc_b;
  int32_T c1_i115;
  int32_T c1_i116;
  int32_T c1_i117;
  real_T c1_e_ACT[36];
  int32_T c1_i118;
  int32_T c1_i119;
  int32_T c1_i120;
  int32_T c1_i121;
  int32_T c1_i122;
  real_T c1_wc_y[18];
  int32_T c1_i123;
  int32_T c1_i124;
  real_T c1_ec_b;
  int32_T c1_i125;
  int32_T c1_i126;
  real_T c1_f_ACT[36];
  int32_T c1_i127;
  int32_T c1_i128;
  int32_T c1_i129;
  int32_T c1_i130;
  int32_T c1_i131;
  real_T c1_xc_y[18];
  int32_T c1_i132;
  int32_T c1_i133;
  real_T c1_fc_b;
  int32_T c1_i134;
  int32_T c1_i135;
  int32_T c1_i136;
  int32_T c1_i137;
  real_T c1_gc_b;
  int32_T c1_i138;
  int32_T c1_i139;
  int32_T c1_i140;
  int32_T c1_i141;
  int32_T c1_i142;
  int32_T c1_i143;
  int32_T c1_i144;
  int32_T c1_i145;
  int32_T c1_i146;
  int32_T c1_i147;
  int32_T c1_i148;
  int32_T c1_i149;
  int32_T c1_i150;
  int32_T c1_i151;
  int32_T c1_i152;
  int32_T c1_i153;
  int32_T c1_i154;
  int32_T c1_i155;
  int32_T c1_i156;
  int32_T c1_i157;
  real_T c1_hc_b[9];
  int32_T c1_i158;
  int32_T c1_i159;
  int32_T c1_i160;
  int32_T c1_i161;
  int32_T c1_i162;
  int32_T c1_i163;
  int32_T c1_i164;
  int32_T c1_i165;
  int32_T c1_i166;
  int32_T c1_i167;
  real_T c1_ic_b[18];
  int32_T c1_i168;
  int32_T c1_i169;
  int32_T c1_i170;
  int32_T c1_i171;
  int32_T c1_i172;
  int32_T c1_i173;
  int32_T c1_i174;
  int32_T c1_i175;
  int32_T c1_i176;
  int32_T c1_i177;
  int32_T c1_i178;
  real_T c1_C[3];
  int32_T c1_i179;
  int32_T c1_i180;
  int32_T c1_i181;
  int32_T c1_i182;
  int32_T c1_i183;
  int32_T c1_i184;
  int32_T c1_i185;
  int32_T c1_i186;
  int32_T c1_i187;
  int32_T c1_i188;
  int32_T c1_i189;
  int32_T c1_i190;
  int32_T c1_i191;
  int32_T c1_i192;
  int32_T c1_i193;
  int32_T c1_i194;
  int32_T c1_i195;
  int32_T c1_i196;
  int32_T c1_i197;
  int32_T c1_i198;
  static real_T c1_jc_b[18] = { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };

  int32_T c1_i199;
  int32_T c1_i200;
  int32_T c1_i201;
  int32_T c1_i202;
  int32_T c1_i203;
  int32_T c1_i204;
  int32_T c1_i205;
  int32_T c1_i206;
  real_T c1_b_inocov[9];
  int32_T c1_i207;
  int32_T c1_i208;
  int32_T c1_i209;
  int32_T c1_i210;
  int32_T c1_i211;
  int32_T c1_i212;
  int32_T c1_i213;
  int32_T c1_i214;
  int32_T c1_i215;
  int32_T c1_i216;
  int32_T c1_i217;
  int32_T c1_i218;
  int32_T c1_i219;
  int32_T c1_i220;
  int32_T c1_i221;
  int32_T c1_i222;
  int32_T c1_i223;
  int32_T c1_i224;
  int32_T c1_i225;
  int32_T c1_i226;
  int32_T c1_i227;
  int32_T c1_i228;
  int32_T c1_i229;
  int32_T c1_i230;
  int32_T c1_i231;
  int32_T c1_i232;
  int32_T c1_i233;
  int32_T c1_i234;
  int32_T c1_i235;
  int32_T c1_i236;
  int32_T c1_i237;
  int32_T c1_i238;
  int32_T c1_i239;
  int32_T c1_i240;
  int32_T c1_i241;
  int32_T c1_i242;
  int32_T c1_i243;
  int32_T c1_i244;
  int32_T c1_i245;
  int32_T c1_i246;
  int32_T c1_i247;
  int32_T c1_i248;
  real_T *c1_b_simpar;
  real_T (*c1_b_xhatout)[6];
  real_T (*c1_b_yhatout)[3];
  real_T (*c1_b_Pout)[36];
  real_T (*c1_b_Pin)[36];
  real_T (*c1_b_noisePSD)[6];
  real_T (*c1_yc_y)[3];
  real_T (*c1_f_input)[2];
  real_T (*c1_f_pumppar)[3];
  real_T (*c1_f_wallpar)[4];
  real_T (*c1_f_coldpar)[4];
  real_T (*c1_f_hotpar)[6];
  real_T (*c1_f_xhatin)[6];
  c1_b_Pout = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_yhatout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_xhatout = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_Pin = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 9);
  c1_b_noisePSD = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 8);
  c1_yc_y = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
  c1_b_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_f_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
  c1_f_pumppar = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c1_f_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c1_f_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
  c1_f_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c1_f_xhatin = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_simpar;
  for (c1_i18 = 0; c1_i18 < 6; c1_i18++) {
    c1_xhatin[c1_i18] = (*c1_f_xhatin)[c1_i18];
  }

  for (c1_i19 = 0; c1_i19 < 6; c1_i19++) {
    c1_hotpar[c1_i19] = (*c1_f_hotpar)[c1_i19];
  }

  for (c1_i20 = 0; c1_i20 < 4; c1_i20++) {
    c1_coldpar[c1_i20] = (*c1_f_coldpar)[c1_i20];
  }

  for (c1_i21 = 0; c1_i21 < 4; c1_i21++) {
    c1_wallpar[c1_i21] = (*c1_f_wallpar)[c1_i21];
  }

  for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
    c1_pumppar[c1_i22] = (*c1_f_pumppar)[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 2; c1_i23++) {
    c1_input[c1_i23] = (*c1_f_input)[c1_i23];
  }

  c1_simpar = c1_hoistedGlobal;
  for (c1_i24 = 0; c1_i24 < 3; c1_i24++) {
    c1_y[c1_i24] = (*c1_yc_y)[c1_i24];
  }

  for (c1_i25 = 0; c1_i25 < 6; c1_i25++) {
    c1_noisePSD[c1_i25] = (*c1_b_noisePSD)[c1_i25];
  }

  for (c1_i26 = 0; c1_i26 < 36; c1_i26++) {
    c1_Pin[c1_i26] = (*c1_b_Pin)[c1_i26];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 73U, 73U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h, 0U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhoh, 1U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vh, 2U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ch, 3U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_mdoth, 4U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_hh, 5U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Thi, 6U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhoc, 7U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vc, 8U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_cc, 9U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_hc, 10U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_mdotc, 11U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Tci, 12U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhow, 13U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vw, 14U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_cw, 15U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_A, 16U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wp, 17U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wa, 18U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wb, 19U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sw_tc, 20U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sw_mh, 21U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sw_th, 22U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Sw, 23U, c1_h_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sv_thi, 24U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sv_tho, 25U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Sv_mh, 26U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Sv, 27U, c1_h_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c1, 28U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c2, 29U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c3, 30U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_c4, 31U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_a2, 32U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_a3, 33U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_a4, 34U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b21, 35U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b31, 36U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b32, 37U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b41, 38U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b42, 39U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_b43, 40U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_K1, 41U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_K2, 42U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_K3, 43U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_K4, 44U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_slope, 45U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_ACT, 46U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_BwCT, 47U, c1_g_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_CCT, 48U, c1_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_ADT, 49U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_BwDT, 50U, c1_g_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_CDT, 51U, c1_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_xhat, 52U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Pneg, 53U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_yhat, 54U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_inov, 55U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_inocov, 56U, c1_h_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_L, 57U, c1_g_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 58U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 59U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_xhatin, 60U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_hotpar, 61U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_coldpar, 62U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_wallpar, 63U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_pumppar, 64U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_input, 65U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_simpar, 66U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_y, 67U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_noisePSD, 68U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_Pin, 69U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_xhatout, 70U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_yhatout, 71U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Pout, 72U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_h = c1_simpar;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_rhoh = c1_hotpar[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_Vh = c1_hotpar[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_ch = c1_hotpar[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_mdoth = c1_hotpar[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_hh = c1_hotpar[4];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_Thi = c1_hotpar[5];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_rhoc = c1_coldpar[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_Vc = c1_coldpar[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_cc = c1_coldpar[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_hc = c1_coldpar[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_mdotc = c1_input[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  c1_Tci = c1_input[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  c1_rhow = c1_wallpar[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
  c1_Vw = c1_wallpar[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 28);
  c1_cw = c1_wallpar[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  c1_A = c1_wallpar[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  c1_wp = c1_pumppar[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  c1_wa = c1_pumppar[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
  c1_wb = c1_pumppar[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
  c1_Sw_tc = c1_noisePSD[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_Sw_mh = c1_noisePSD[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
  c1_Sw_th = c1_noisePSD[2];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
  c1_b_Sw_tc[0] = c1_Sw_tc;
  c1_b_Sw_tc[1] = c1_Sw_mh;
  c1_b_Sw_tc[2] = c1_Sw_th;
  c1_diag(chartInstance, c1_b_Sw_tc, c1_dv3);
  for (c1_i27 = 0; c1_i27 < 9; c1_i27++) {
    c1_Sw[c1_i27] = c1_dv3[c1_i27];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
  c1_Sv_thi = c1_noisePSD[3];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 43);
  c1_Sv_tho = c1_noisePSD[4];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 44);
  c1_Sv_mh = c1_noisePSD[5];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
  c1_b_Sv_thi[0] = c1_Sv_thi;
  c1_b_Sv_thi[1] = c1_Sv_tho;
  c1_b_Sv_thi[2] = c1_Sv_mh;
  c1_diag(chartInstance, c1_b_Sv_thi, c1_dv4);
  for (c1_i28 = 0; c1_i28 < 9; c1_i28++) {
    c1_Sv[c1_i28] = c1_dv4[c1_i28];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
  c1_c1 = 0.16666666666666666;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
  c1_c2 = 0.33333333333333331;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
  c1_c3 = 0.33333333333333331;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 51);
  c1_c4 = 0.16666666666666666;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 52);
  c1_a2 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 53);
  c1_a3 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
  c1_a4 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 55);
  c1_b21 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 56);
  c1_b31 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 57);
  c1_b32 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 58);
  c1_b41 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 59);
  c1_b42 = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 60);
  c1_b43 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 62);
  for (c1_i29 = 0; c1_i29 < 6; c1_i29++) {
    c1_b_xhatin[c1_i29] = c1_xhatin[c1_i29];
  }

  for (c1_i30 = 0; c1_i30 < 6; c1_i30++) {
    c1_b_hotpar[c1_i30] = c1_hotpar[c1_i30];
  }

  for (c1_i31 = 0; c1_i31 < 4; c1_i31++) {
    c1_b_coldpar[c1_i31] = c1_coldpar[c1_i31];
  }

  for (c1_i32 = 0; c1_i32 < 4; c1_i32++) {
    c1_b_wallpar[c1_i32] = c1_wallpar[c1_i32];
  }

  for (c1_i33 = 0; c1_i33 < 3; c1_i33++) {
    c1_b_pumppar[c1_i33] = c1_pumppar[c1_i33];
  }

  for (c1_i34 = 0; c1_i34 < 2; c1_i34++) {
    c1_b_input[c1_i34] = c1_input[c1_i34];
  }

  c1_EKFdynamics(chartInstance, c1_b_xhatin, c1_b_hotpar, c1_b_coldpar,
                 c1_b_wallpar, c1_b_pumppar, c1_b_input, c1_dv5);
  for (c1_i35 = 0; c1_i35 < 6; c1_i35++) {
    c1_K1[c1_i35] = c1_dv5[c1_i35];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 63);
  for (c1_i36 = 0; c1_i36 < 6; c1_i36++) {
    c1_b[c1_i36] = c1_K1[c1_i36];
  }

  for (c1_i37 = 0; c1_i37 < 6; c1_i37++) {
    c1_b[c1_i37] *= 0.5;
  }

  c1_b_b = c1_h;
  for (c1_i38 = 0; c1_i38 < 6; c1_i38++) {
    c1_b[c1_i38] *= c1_b_b;
  }

  for (c1_i39 = 0; c1_i39 < 6; c1_i39++) {
    c1_c_xhatin[c1_i39] = c1_xhatin[c1_i39] + c1_b[c1_i39];
  }

  for (c1_i40 = 0; c1_i40 < 6; c1_i40++) {
    c1_c_hotpar[c1_i40] = c1_hotpar[c1_i40];
  }

  for (c1_i41 = 0; c1_i41 < 4; c1_i41++) {
    c1_c_coldpar[c1_i41] = c1_coldpar[c1_i41];
  }

  for (c1_i42 = 0; c1_i42 < 4; c1_i42++) {
    c1_c_wallpar[c1_i42] = c1_wallpar[c1_i42];
  }

  for (c1_i43 = 0; c1_i43 < 3; c1_i43++) {
    c1_c_pumppar[c1_i43] = c1_pumppar[c1_i43];
  }

  for (c1_i44 = 0; c1_i44 < 2; c1_i44++) {
    c1_c_input[c1_i44] = c1_input[c1_i44];
  }

  c1_EKFdynamics(chartInstance, c1_c_xhatin, c1_c_hotpar, c1_c_coldpar,
                 c1_c_wallpar, c1_c_pumppar, c1_c_input, c1_dv6);
  for (c1_i45 = 0; c1_i45 < 6; c1_i45++) {
    c1_K2[c1_i45] = c1_dv6[c1_i45];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 64);
  for (c1_i46 = 0; c1_i46 < 6; c1_i46++) {
    c1_b[c1_i46] = c1_K1[c1_i46];
  }

  for (c1_i47 = 0; c1_i47 < 6; c1_i47++) {
    c1_b[c1_i47] *= 0.0;
  }

  c1_c_b = c1_h;
  for (c1_i48 = 0; c1_i48 < 6; c1_i48++) {
    c1_b[c1_i48] *= c1_c_b;
  }

  for (c1_i49 = 0; c1_i49 < 6; c1_i49++) {
    c1_d_b[c1_i49] = c1_K2[c1_i49];
  }

  for (c1_i50 = 0; c1_i50 < 6; c1_i50++) {
    c1_d_b[c1_i50] *= 0.5;
  }

  c1_e_b = c1_h;
  for (c1_i51 = 0; c1_i51 < 6; c1_i51++) {
    c1_d_b[c1_i51] *= c1_e_b;
  }

  for (c1_i52 = 0; c1_i52 < 6; c1_i52++) {
    c1_d_xhatin[c1_i52] = (c1_xhatin[c1_i52] + c1_b[c1_i52]) + c1_d_b[c1_i52];
  }

  for (c1_i53 = 0; c1_i53 < 6; c1_i53++) {
    c1_d_hotpar[c1_i53] = c1_hotpar[c1_i53];
  }

  for (c1_i54 = 0; c1_i54 < 4; c1_i54++) {
    c1_d_coldpar[c1_i54] = c1_coldpar[c1_i54];
  }

  for (c1_i55 = 0; c1_i55 < 4; c1_i55++) {
    c1_d_wallpar[c1_i55] = c1_wallpar[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 3; c1_i56++) {
    c1_d_pumppar[c1_i56] = c1_pumppar[c1_i56];
  }

  for (c1_i57 = 0; c1_i57 < 2; c1_i57++) {
    c1_d_input[c1_i57] = c1_input[c1_i57];
  }

  c1_EKFdynamics(chartInstance, c1_d_xhatin, c1_d_hotpar, c1_d_coldpar,
                 c1_d_wallpar, c1_d_pumppar, c1_d_input, c1_dv7);
  for (c1_i58 = 0; c1_i58 < 6; c1_i58++) {
    c1_K3[c1_i58] = c1_dv7[c1_i58];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 65);
  for (c1_i59 = 0; c1_i59 < 6; c1_i59++) {
    c1_b[c1_i59] = c1_K1[c1_i59];
  }

  for (c1_i60 = 0; c1_i60 < 6; c1_i60++) {
    c1_b[c1_i60] *= 0.0;
  }

  c1_f_b = c1_h;
  for (c1_i61 = 0; c1_i61 < 6; c1_i61++) {
    c1_b[c1_i61] *= c1_f_b;
  }

  for (c1_i62 = 0; c1_i62 < 6; c1_i62++) {
    c1_d_b[c1_i62] = c1_K2[c1_i62];
  }

  for (c1_i63 = 0; c1_i63 < 6; c1_i63++) {
    c1_d_b[c1_i63] *= 0.0;
  }

  c1_g_b = c1_h;
  for (c1_i64 = 0; c1_i64 < 6; c1_i64++) {
    c1_d_b[c1_i64] *= c1_g_b;
  }

  for (c1_i65 = 0; c1_i65 < 6; c1_i65++) {
    c1_h_b[c1_i65] = c1_K3[c1_i65];
  }

  c1_i_b = c1_h;
  for (c1_i66 = 0; c1_i66 < 6; c1_i66++) {
    c1_h_b[c1_i66] *= c1_i_b;
  }

  for (c1_i67 = 0; c1_i67 < 6; c1_i67++) {
    c1_e_xhatin[c1_i67] = ((c1_xhatin[c1_i67] + c1_b[c1_i67]) + c1_d_b[c1_i67])
      + c1_h_b[c1_i67];
  }

  for (c1_i68 = 0; c1_i68 < 6; c1_i68++) {
    c1_e_hotpar[c1_i68] = c1_hotpar[c1_i68];
  }

  for (c1_i69 = 0; c1_i69 < 4; c1_i69++) {
    c1_e_coldpar[c1_i69] = c1_coldpar[c1_i69];
  }

  for (c1_i70 = 0; c1_i70 < 4; c1_i70++) {
    c1_e_wallpar[c1_i70] = c1_wallpar[c1_i70];
  }

  for (c1_i71 = 0; c1_i71 < 3; c1_i71++) {
    c1_e_pumppar[c1_i71] = c1_pumppar[c1_i71];
  }

  for (c1_i72 = 0; c1_i72 < 2; c1_i72++) {
    c1_e_input[c1_i72] = c1_input[c1_i72];
  }

  c1_EKFdynamics(chartInstance, c1_e_xhatin, c1_e_hotpar, c1_e_coldpar,
                 c1_e_wallpar, c1_e_pumppar, c1_e_input, c1_dv8);
  for (c1_i73 = 0; c1_i73 < 6; c1_i73++) {
    c1_K4[c1_i73] = c1_dv8[c1_i73];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 66);
  for (c1_i74 = 0; c1_i74 < 6; c1_i74++) {
    c1_b[c1_i74] = c1_K1[c1_i74];
  }

  for (c1_i75 = 0; c1_i75 < 6; c1_i75++) {
    c1_b[c1_i75] *= 0.16666666666666666;
  }

  for (c1_i76 = 0; c1_i76 < 6; c1_i76++) {
    c1_d_b[c1_i76] = c1_K2[c1_i76];
  }

  for (c1_i77 = 0; c1_i77 < 6; c1_i77++) {
    c1_d_b[c1_i77] *= 0.33333333333333331;
  }

  for (c1_i78 = 0; c1_i78 < 6; c1_i78++) {
    c1_h_b[c1_i78] = c1_K3[c1_i78];
  }

  for (c1_i79 = 0; c1_i79 < 6; c1_i79++) {
    c1_h_b[c1_i79] *= 0.33333333333333331;
  }

  for (c1_i80 = 0; c1_i80 < 6; c1_i80++) {
    c1_j_b[c1_i80] = c1_K4[c1_i80];
  }

  for (c1_i81 = 0; c1_i81 < 6; c1_i81++) {
    c1_j_b[c1_i81] *= 0.16666666666666666;
  }

  for (c1_i82 = 0; c1_i82 < 6; c1_i82++) {
    c1_slope[c1_i82] = ((c1_b[c1_i82] + c1_d_b[c1_i82]) + c1_h_b[c1_i82]) +
      c1_j_b[c1_i82];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 69);
  c1_a = c1_xhatin[3];
  c1_k_b = c1_ch;
  c1_b_y = c1_a * c1_k_b;
  c1_b_a = c1_hh;
  c1_l_b = c1_A;
  c1_c_y = c1_b_a * c1_l_b;
  c1_c_a = c1_rhoh;
  c1_m_b = c1_Vh;
  c1_d_y = c1_c_a * c1_m_b;
  c1_d_a = c1_d_y;
  c1_n_b = c1_ch;
  c1_e_y = c1_d_a * c1_n_b;
  c1_b_A = -(c1_b_y + c1_c_y);
  c1_B = c1_e_y;
  c1_x = c1_b_A;
  c1_f_y = c1_B;
  c1_b_x = c1_x;
  c1_g_y = c1_f_y;
  c1_h_y = c1_b_x / c1_g_y;
  c1_e_a = c1_hh;
  c1_o_b = c1_A;
  c1_i_y = c1_e_a * c1_o_b;
  c1_f_a = c1_rhoh;
  c1_p_b = c1_Vh;
  c1_j_y = c1_f_a * c1_p_b;
  c1_g_a = c1_j_y;
  c1_q_b = c1_ch;
  c1_k_y = c1_g_a * c1_q_b;
  c1_c_A = c1_i_y;
  c1_b_B = c1_k_y;
  c1_c_x = c1_c_A;
  c1_l_y = c1_b_B;
  c1_d_x = c1_c_x;
  c1_m_y = c1_l_y;
  c1_n_y = c1_d_x / c1_m_y;
  c1_h_a = c1_ch;
  c1_r_b = c1_xhatin[4] - c1_xhatin[0];
  c1_o_y = c1_h_a * c1_r_b;
  c1_i_a = c1_rhoh;
  c1_s_b = c1_Vh;
  c1_p_y = c1_i_a * c1_s_b;
  c1_j_a = c1_p_y;
  c1_t_b = c1_ch;
  c1_q_y = c1_j_a * c1_t_b;
  c1_d_A = c1_o_y;
  c1_c_B = c1_q_y;
  c1_e_x = c1_d_A;
  c1_r_y = c1_c_B;
  c1_f_x = c1_e_x;
  c1_s_y = c1_r_y;
  c1_t_y = c1_f_x / c1_s_y;
  c1_k_a = c1_xhatin[3];
  c1_u_b = c1_ch;
  c1_u_y = c1_k_a * c1_u_b;
  c1_l_a = c1_rhoh;
  c1_v_b = c1_Vh;
  c1_v_y = c1_l_a * c1_v_b;
  c1_m_a = c1_v_y;
  c1_w_b = c1_ch;
  c1_w_y = c1_m_a * c1_w_b;
  c1_e_A = c1_u_y;
  c1_d_B = c1_w_y;
  c1_g_x = c1_e_A;
  c1_x_y = c1_d_B;
  c1_h_x = c1_g_x;
  c1_y_y = c1_x_y;
  c1_ab_y = c1_h_x / c1_y_y;
  c1_n_a = c1_mdotc;
  c1_x_b = c1_cc;
  c1_bb_y = c1_n_a * c1_x_b;
  c1_o_a = c1_hc;
  c1_y_b = c1_A;
  c1_cb_y = c1_o_a * c1_y_b;
  c1_p_a = c1_rhoc;
  c1_ab_b = c1_Vc;
  c1_db_y = c1_p_a * c1_ab_b;
  c1_q_a = c1_db_y;
  c1_bb_b = c1_cc;
  c1_eb_y = c1_q_a * c1_bb_b;
  c1_f_A = -(c1_bb_y + c1_cb_y);
  c1_e_B = c1_eb_y;
  c1_i_x = c1_f_A;
  c1_fb_y = c1_e_B;
  c1_j_x = c1_i_x;
  c1_gb_y = c1_fb_y;
  c1_hb_y = c1_j_x / c1_gb_y;
  c1_r_a = c1_hc;
  c1_cb_b = c1_A;
  c1_ib_y = c1_r_a * c1_cb_b;
  c1_s_a = c1_rhoc;
  c1_db_b = c1_Vc;
  c1_jb_y = c1_s_a * c1_db_b;
  c1_t_a = c1_jb_y;
  c1_eb_b = c1_cc;
  c1_kb_y = c1_t_a * c1_eb_b;
  c1_g_A = c1_ib_y;
  c1_f_B = c1_kb_y;
  c1_k_x = c1_g_A;
  c1_lb_y = c1_f_B;
  c1_l_x = c1_k_x;
  c1_mb_y = c1_lb_y;
  c1_nb_y = c1_l_x / c1_mb_y;
  c1_u_a = c1_cc;
  c1_fb_b = c1_Tci - c1_xhatin[1];
  c1_ob_y = c1_u_a * c1_fb_b;
  c1_v_a = c1_rhoc;
  c1_gb_b = c1_Vc;
  c1_pb_y = c1_v_a * c1_gb_b;
  c1_w_a = c1_pb_y;
  c1_hb_b = c1_cc;
  c1_qb_y = c1_w_a * c1_hb_b;
  c1_h_A = c1_ob_y;
  c1_g_B = c1_qb_y;
  c1_m_x = c1_h_A;
  c1_rb_y = c1_g_B;
  c1_n_x = c1_m_x;
  c1_sb_y = c1_rb_y;
  c1_tb_y = c1_n_x / c1_sb_y;
  c1_x_a = c1_hh;
  c1_ib_b = c1_A;
  c1_ub_y = c1_x_a * c1_ib_b;
  c1_y_a = c1_rhow;
  c1_jb_b = c1_Vw;
  c1_vb_y = c1_y_a * c1_jb_b;
  c1_ab_a = c1_vb_y;
  c1_kb_b = c1_cw;
  c1_wb_y = c1_ab_a * c1_kb_b;
  c1_i_A = c1_ub_y;
  c1_h_B = c1_wb_y;
  c1_o_x = c1_i_A;
  c1_xb_y = c1_h_B;
  c1_p_x = c1_o_x;
  c1_yb_y = c1_xb_y;
  c1_ac_y = c1_p_x / c1_yb_y;
  c1_bb_a = c1_hc;
  c1_lb_b = c1_A;
  c1_bc_y = c1_bb_a * c1_lb_b;
  c1_cb_a = c1_rhow;
  c1_mb_b = c1_Vw;
  c1_cc_y = c1_cb_a * c1_mb_b;
  c1_db_a = c1_cc_y;
  c1_nb_b = c1_cw;
  c1_dc_y = c1_db_a * c1_nb_b;
  c1_j_A = c1_bc_y;
  c1_i_B = c1_dc_y;
  c1_q_x = c1_j_A;
  c1_ec_y = c1_i_B;
  c1_r_x = c1_q_x;
  c1_fc_y = c1_ec_y;
  c1_gc_y = c1_r_x / c1_fc_y;
  c1_eb_a = c1_hh;
  c1_ob_b = c1_A;
  c1_hc_y = c1_eb_a * c1_ob_b;
  c1_fb_a = c1_hc;
  c1_pb_b = c1_A;
  c1_ic_y = c1_fb_a * c1_pb_b;
  c1_gb_a = c1_rhow;
  c1_qb_b = c1_Vw;
  c1_jc_y = c1_gb_a * c1_qb_b;
  c1_hb_a = c1_jc_y;
  c1_rb_b = c1_cw;
  c1_kc_y = c1_hb_a * c1_rb_b;
  c1_k_A = -(c1_hc_y + c1_ic_y);
  c1_j_B = c1_kc_y;
  c1_s_x = c1_k_A;
  c1_lc_y = c1_j_B;
  c1_t_x = c1_s_x;
  c1_mc_y = c1_lc_y;
  c1_nc_y = c1_t_x / c1_mc_y;
  c1_ACT[0] = c1_h_y;
  c1_ACT[6] = 0.0;
  c1_ACT[12] = c1_n_y;
  c1_ACT[18] = c1_t_y;
  c1_ACT[24] = c1_ab_y;
  c1_ACT[30] = 0.0;
  c1_ACT[1] = 0.0;
  c1_ACT[7] = c1_hb_y;
  c1_ACT[13] = c1_nb_y;
  c1_ACT[19] = 0.0;
  c1_ACT[25] = 0.0;
  c1_ACT[31] = c1_tb_y;
  c1_ACT[2] = c1_ac_y;
  c1_ACT[8] = c1_gc_y;
  c1_ACT[14] = c1_nc_y;
  c1_ACT[20] = 0.0;
  c1_ACT[26] = 0.0;
  c1_ACT[32] = 0.0;
  c1_ACT[3] = 0.0;
  c1_ACT[9] = 0.0;
  c1_ACT[15] = 0.0;
  c1_ACT[21] = -c1_wa;
  c1_ACT[27] = 0.0;
  c1_ACT[33] = 0.0;
  c1_ACT[4] = 0.0;
  c1_ACT[10] = 0.0;
  c1_ACT[16] = 0.0;
  c1_ACT[22] = 0.0;
  c1_ACT[28] = -c1_wb;
  c1_ACT[34] = 0.0;
  c1_ACT[5] = 0.0;
  c1_ACT[11] = 0.0;
  c1_ACT[17] = 0.0;
  c1_ACT[23] = 0.0;
  c1_ACT[29] = 0.0;
  c1_ACT[35] = -c1_wp;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 75);
  c1_ib_a = c1_mdotc;
  c1_sb_b = c1_cc;
  c1_oc_y = c1_ib_a * c1_sb_b;
  c1_jb_a = c1_rhoc;
  c1_tb_b = c1_Vc;
  c1_pc_y = c1_jb_a * c1_tb_b;
  c1_kb_a = c1_pc_y;
  c1_ub_b = c1_cc;
  c1_qc_y = c1_kb_a * c1_ub_b;
  c1_l_A = c1_oc_y;
  c1_k_B = c1_qc_y;
  c1_u_x = c1_l_A;
  c1_rc_y = c1_k_B;
  c1_v_x = c1_u_x;
  c1_sc_y = c1_rc_y;
  c1_tc_y = c1_v_x / c1_sc_y;
  c1_lb_a = c1_tc_y;
  c1_vb_b = c1_Tci;
  c1_uc_y = c1_lb_a * c1_vb_b;
  c1_i83 = 0;
  for (c1_i84 = 0; c1_i84 < 3; c1_i84++) {
    c1_BwCT[c1_i83] = 0.0;
    c1_i83 += 6;
  }

  c1_BwCT[1] = c1_uc_y;
  c1_BwCT[7] = 0.0;
  c1_BwCT[13] = 0.0;
  c1_i85 = 0;
  for (c1_i86 = 0; c1_i86 < 3; c1_i86++) {
    c1_BwCT[c1_i85 + 2] = 0.0;
    c1_i85 += 6;
  }

  c1_i87 = 0;
  for (c1_i88 = 0; c1_i88 < 3; c1_i88++) {
    c1_BwCT[c1_i87 + 3] = c1_dv9[c1_i88];
    c1_i87 += 6;
  }

  c1_i89 = 0;
  for (c1_i90 = 0; c1_i90 < 3; c1_i90++) {
    c1_BwCT[c1_i89 + 4] = c1_dv10[c1_i90];
    c1_i89 += 6;
  }

  c1_i91 = 0;
  for (c1_i92 = 0; c1_i92 < 3; c1_i92++) {
    c1_BwCT[c1_i91 + 5] = 0.0;
    c1_i91 += 6;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 76);
  for (c1_i93 = 0; c1_i93 < 18; c1_i93++) {
    c1_CCT[c1_i93] = c1_mb_a[c1_i93];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 79);
  for (c1_i94 = 0; c1_i94 < 36; c1_i94++) {
    c1_nb_a[c1_i94] = c1_ACT[c1_i94];
  }

  c1_wb_b = c1_h;
  for (c1_i95 = 0; c1_i95 < 36; c1_i95++) {
    c1_nb_a[c1_i95] *= c1_wb_b;
  }

  for (c1_i96 = 0; c1_i96 < 36; c1_i96++) {
    c1_b_ACT[c1_i96] = c1_ACT[c1_i96];
  }

  c1_mpower(chartInstance, c1_b_ACT, c1_ob_a);
  c1_xb_b = c1_b_mpower(chartInstance, c1_h);
  for (c1_i97 = 0; c1_i97 < 36; c1_i97++) {
    c1_ob_a[c1_i97] *= c1_xb_b;
  }

  for (c1_i98 = 0; c1_i98 < 36; c1_i98++) {
    c1_ob_a[c1_i98] /= 2.0;
  }

  for (c1_i99 = 0; c1_i99 < 36; c1_i99++) {
    c1_c_ACT[c1_i99] = c1_ACT[c1_i99];
  }

  c1_c_mpower(chartInstance, c1_c_ACT, c1_pb_a);
  c1_yb_b = c1_d_mpower(chartInstance, c1_h);
  for (c1_i100 = 0; c1_i100 < 36; c1_i100++) {
    c1_pb_a[c1_i100] *= c1_yb_b;
  }

  for (c1_i101 = 0; c1_i101 < 36; c1_i101++) {
    c1_pb_a[c1_i101] /= 6.0;
  }

  for (c1_i102 = 0; c1_i102 < 36; c1_i102++) {
    c1_d_ACT[c1_i102] = c1_ACT[c1_i102];
  }

  c1_e_mpower(chartInstance, c1_d_ACT, c1_qb_a);
  c1_ac_b = c1_f_mpower(chartInstance, c1_h);
  for (c1_i103 = 0; c1_i103 < 36; c1_i103++) {
    c1_qb_a[c1_i103] *= c1_ac_b;
  }

  for (c1_i104 = 0; c1_i104 < 36; c1_i104++) {
    c1_qb_a[c1_i104] /= 24.0;
  }

  c1_eye(chartInstance, c1_dv11);
  for (c1_i105 = 0; c1_i105 < 36; c1_i105++) {
    c1_ADT[c1_i105] = (((c1_dv11[c1_i105] + c1_nb_a[c1_i105]) + c1_ob_a[c1_i105])
                       + c1_pb_a[c1_i105]) + c1_qb_a[c1_i105];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 80);
  for (c1_i106 = 0; c1_i106 < 18; c1_i106++) {
    c1_rb_a[c1_i106] = c1_BwCT[c1_i106];
  }

  c1_bc_b = c1_h;
  for (c1_i107 = 0; c1_i107 < 18; c1_i107++) {
    c1_rb_a[c1_i107] *= c1_bc_b;
  }

  for (c1_i108 = 0; c1_i108 < 36; c1_i108++) {
    c1_nb_a[c1_i108] = c1_ACT[c1_i108];
  }

  for (c1_i109 = 0; c1_i109 < 18; c1_i109++) {
    c1_cc_b[c1_i109] = c1_BwCT[c1_i109];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i110 = 0; c1_i110 < 6; c1_i110++) {
    c1_i111 = 0;
    for (c1_i112 = 0; c1_i112 < 3; c1_i112++) {
      c1_vc_y[c1_i111 + c1_i110] = 0.0;
      c1_i113 = 0;
      for (c1_i114 = 0; c1_i114 < 6; c1_i114++) {
        c1_vc_y[c1_i111 + c1_i110] += c1_nb_a[c1_i113 + c1_i110] *
          c1_cc_b[c1_i114 + c1_i111];
        c1_i113 += 6;
      }

      c1_i111 += 6;
    }
  }

  c1_dc_b = c1_b_mpower(chartInstance, c1_h);
  for (c1_i115 = 0; c1_i115 < 18; c1_i115++) {
    c1_vc_y[c1_i115] *= c1_dc_b;
  }

  for (c1_i116 = 0; c1_i116 < 18; c1_i116++) {
    c1_vc_y[c1_i116] /= 2.0;
  }

  for (c1_i117 = 0; c1_i117 < 36; c1_i117++) {
    c1_e_ACT[c1_i117] = c1_ACT[c1_i117];
  }

  c1_mpower(chartInstance, c1_e_ACT, c1_qb_a);
  for (c1_i118 = 0; c1_i118 < 36; c1_i118++) {
    c1_qb_a[c1_i118] *= 0.16666666666666666;
  }

  for (c1_i119 = 0; c1_i119 < 18; c1_i119++) {
    c1_cc_b[c1_i119] = c1_BwCT[c1_i119];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i120 = 0; c1_i120 < 6; c1_i120++) {
    c1_i121 = 0;
    for (c1_i122 = 0; c1_i122 < 3; c1_i122++) {
      c1_wc_y[c1_i121 + c1_i120] = 0.0;
      c1_i123 = 0;
      for (c1_i124 = 0; c1_i124 < 6; c1_i124++) {
        c1_wc_y[c1_i121 + c1_i120] += c1_qb_a[c1_i123 + c1_i120] *
          c1_cc_b[c1_i124 + c1_i121];
        c1_i123 += 6;
      }

      c1_i121 += 6;
    }
  }

  c1_ec_b = c1_d_mpower(chartInstance, c1_h);
  for (c1_i125 = 0; c1_i125 < 18; c1_i125++) {
    c1_wc_y[c1_i125] *= c1_ec_b;
  }

  for (c1_i126 = 0; c1_i126 < 36; c1_i126++) {
    c1_f_ACT[c1_i126] = c1_ACT[c1_i126];
  }

  c1_c_mpower(chartInstance, c1_f_ACT, c1_qb_a);
  for (c1_i127 = 0; c1_i127 < 36; c1_i127++) {
    c1_qb_a[c1_i127] *= 0.041666666666666664;
  }

  for (c1_i128 = 0; c1_i128 < 18; c1_i128++) {
    c1_cc_b[c1_i128] = c1_BwCT[c1_i128];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i129 = 0; c1_i129 < 6; c1_i129++) {
    c1_i130 = 0;
    for (c1_i131 = 0; c1_i131 < 3; c1_i131++) {
      c1_xc_y[c1_i130 + c1_i129] = 0.0;
      c1_i132 = 0;
      for (c1_i133 = 0; c1_i133 < 6; c1_i133++) {
        c1_xc_y[c1_i130 + c1_i129] += c1_qb_a[c1_i132 + c1_i129] *
          c1_cc_b[c1_i133 + c1_i130];
        c1_i132 += 6;
      }

      c1_i130 += 6;
    }
  }

  c1_fc_b = c1_f_mpower(chartInstance, c1_h);
  for (c1_i134 = 0; c1_i134 < 18; c1_i134++) {
    c1_xc_y[c1_i134] *= c1_fc_b;
  }

  for (c1_i135 = 0; c1_i135 < 18; c1_i135++) {
    c1_BwDT[c1_i135] = ((c1_rb_a[c1_i135] + c1_vc_y[c1_i135]) + c1_wc_y[c1_i135])
      + c1_xc_y[c1_i135];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 81);
  for (c1_i136 = 0; c1_i136 < 18; c1_i136++) {
    c1_CDT[c1_i136] = c1_mb_a[c1_i136];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 84);
  for (c1_i137 = 0; c1_i137 < 6; c1_i137++) {
    c1_b[c1_i137] = c1_slope[c1_i137];
  }

  c1_gc_b = c1_h;
  for (c1_i138 = 0; c1_i138 < 6; c1_i138++) {
    c1_b[c1_i138] *= c1_gc_b;
  }

  for (c1_i139 = 0; c1_i139 < 6; c1_i139++) {
    c1_xhat[c1_i139] = c1_xhatin[c1_i139] + c1_b[c1_i139];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 85);
  for (c1_i140 = 0; c1_i140 < 36; c1_i140++) {
    c1_nb_a[c1_i140] = c1_ADT[c1_i140];
  }

  for (c1_i141 = 0; c1_i141 < 36; c1_i141++) {
    c1_qb_a[c1_i141] = c1_Pin[c1_i141];
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  for (c1_i142 = 0; c1_i142 < 6; c1_i142++) {
    c1_i143 = 0;
    for (c1_i144 = 0; c1_i144 < 6; c1_i144++) {
      c1_pb_a[c1_i143 + c1_i142] = 0.0;
      c1_i145 = 0;
      for (c1_i146 = 0; c1_i146 < 6; c1_i146++) {
        c1_pb_a[c1_i143 + c1_i142] += c1_nb_a[c1_i145 + c1_i142] *
          c1_qb_a[c1_i146 + c1_i143];
        c1_i145 += 6;
      }

      c1_i143 += 6;
    }
  }

  c1_i147 = 0;
  for (c1_i148 = 0; c1_i148 < 6; c1_i148++) {
    c1_i149 = 0;
    for (c1_i150 = 0; c1_i150 < 6; c1_i150++) {
      c1_qb_a[c1_i150 + c1_i147] = c1_ADT[c1_i149 + c1_i148];
      c1_i149 += 6;
    }

    c1_i147 += 6;
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  for (c1_i151 = 0; c1_i151 < 6; c1_i151++) {
    c1_i152 = 0;
    for (c1_i153 = 0; c1_i153 < 6; c1_i153++) {
      c1_ob_a[c1_i152 + c1_i151] = 0.0;
      c1_i154 = 0;
      for (c1_i155 = 0; c1_i155 < 6; c1_i155++) {
        c1_ob_a[c1_i152 + c1_i151] += c1_pb_a[c1_i154 + c1_i151] *
          c1_qb_a[c1_i155 + c1_i152];
        c1_i154 += 6;
      }

      c1_i152 += 6;
    }
  }

  for (c1_i156 = 0; c1_i156 < 18; c1_i156++) {
    c1_rb_a[c1_i156] = c1_BwDT[c1_i156];
  }

  for (c1_i157 = 0; c1_i157 < 9; c1_i157++) {
    c1_hc_b[c1_i157] = c1_Sw[c1_i157];
  }

  c1_e_eml_scalar_eg(chartInstance);
  c1_e_eml_scalar_eg(chartInstance);
  for (c1_i158 = 0; c1_i158 < 6; c1_i158++) {
    c1_i159 = 0;
    c1_i160 = 0;
    for (c1_i161 = 0; c1_i161 < 3; c1_i161++) {
      c1_vc_y[c1_i159 + c1_i158] = 0.0;
      c1_i162 = 0;
      for (c1_i163 = 0; c1_i163 < 3; c1_i163++) {
        c1_vc_y[c1_i159 + c1_i158] += c1_rb_a[c1_i162 + c1_i158] *
          c1_hc_b[c1_i163 + c1_i160];
        c1_i162 += 6;
      }

      c1_i159 += 6;
      c1_i160 += 3;
    }
  }

  c1_i164 = 0;
  for (c1_i165 = 0; c1_i165 < 6; c1_i165++) {
    c1_i166 = 0;
    for (c1_i167 = 0; c1_i167 < 3; c1_i167++) {
      c1_ic_b[c1_i167 + c1_i164] = c1_BwDT[c1_i166 + c1_i165];
      c1_i166 += 6;
    }

    c1_i164 += 3;
  }

  c1_f_eml_scalar_eg(chartInstance);
  c1_f_eml_scalar_eg(chartInstance);
  for (c1_i168 = 0; c1_i168 < 6; c1_i168++) {
    c1_i169 = 0;
    c1_i170 = 0;
    for (c1_i171 = 0; c1_i171 < 6; c1_i171++) {
      c1_pb_a[c1_i169 + c1_i168] = 0.0;
      c1_i172 = 0;
      for (c1_i173 = 0; c1_i173 < 3; c1_i173++) {
        c1_pb_a[c1_i169 + c1_i168] += c1_vc_y[c1_i172 + c1_i168] *
          c1_ic_b[c1_i173 + c1_i170];
        c1_i172 += 6;
      }

      c1_i169 += 6;
      c1_i170 += 3;
    }
  }

  for (c1_i174 = 0; c1_i174 < 36; c1_i174++) {
    c1_Pneg[c1_i174] = c1_ob_a[c1_i174] + c1_pb_a[c1_i174];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 88);
  for (c1_i175 = 0; c1_i175 < 6; c1_i175++) {
    c1_b[c1_i175] = c1_xhat[c1_i175];
  }

  c1_g_eml_scalar_eg(chartInstance);
  c1_g_eml_scalar_eg(chartInstance);
  for (c1_i176 = 0; c1_i176 < 3; c1_i176++) {
    c1_yhat[c1_i176] = 0.0;
  }

  for (c1_i177 = 0; c1_i177 < 3; c1_i177++) {
    c1_yhat[c1_i177] = 0.0;
  }

  for (c1_i178 = 0; c1_i178 < 3; c1_i178++) {
    c1_C[c1_i178] = c1_yhat[c1_i178];
  }

  for (c1_i179 = 0; c1_i179 < 3; c1_i179++) {
    c1_yhat[c1_i179] = c1_C[c1_i179];
  }

  for (c1_i180 = 0; c1_i180 < 3; c1_i180++) {
    c1_C[c1_i180] = c1_yhat[c1_i180];
  }

  for (c1_i181 = 0; c1_i181 < 3; c1_i181++) {
    c1_yhat[c1_i181] = c1_C[c1_i181];
  }

  for (c1_i182 = 0; c1_i182 < 3; c1_i182++) {
    c1_yhat[c1_i182] = 0.0;
    c1_i183 = 0;
    for (c1_i184 = 0; c1_i184 < 6; c1_i184++) {
      c1_yhat[c1_i182] += c1_mb_a[c1_i183 + c1_i182] * c1_b[c1_i184];
      c1_i183 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 89);
  for (c1_i185 = 0; c1_i185 < 3; c1_i185++) {
    c1_inov[c1_i185] = c1_y[c1_i185] - c1_yhat[c1_i185];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 90);
  for (c1_i186 = 0; c1_i186 < 36; c1_i186++) {
    c1_qb_a[c1_i186] = c1_Pneg[c1_i186];
  }

  c1_h_eml_scalar_eg(chartInstance);
  c1_h_eml_scalar_eg(chartInstance);
  for (c1_i187 = 0; c1_i187 < 3; c1_i187++) {
    c1_i188 = 0;
    c1_i189 = 0;
    for (c1_i190 = 0; c1_i190 < 6; c1_i190++) {
      c1_ic_b[c1_i188 + c1_i187] = 0.0;
      c1_i191 = 0;
      for (c1_i192 = 0; c1_i192 < 6; c1_i192++) {
        c1_ic_b[c1_i188 + c1_i187] += c1_mb_a[c1_i191 + c1_i187] *
          c1_qb_a[c1_i192 + c1_i189];
        c1_i191 += 3;
      }

      c1_i188 += 3;
      c1_i189 += 6;
    }
  }

  c1_i_eml_scalar_eg(chartInstance);
  c1_i_eml_scalar_eg(chartInstance);
  for (c1_i193 = 0; c1_i193 < 3; c1_i193++) {
    c1_i194 = 0;
    c1_i195 = 0;
    for (c1_i196 = 0; c1_i196 < 3; c1_i196++) {
      c1_hc_b[c1_i194 + c1_i193] = 0.0;
      c1_i197 = 0;
      for (c1_i198 = 0; c1_i198 < 6; c1_i198++) {
        c1_hc_b[c1_i194 + c1_i193] += c1_ic_b[c1_i197 + c1_i193] *
          c1_jc_b[c1_i198 + c1_i195];
        c1_i197 += 3;
      }

      c1_i194 += 3;
      c1_i195 += 6;
    }
  }

  for (c1_i199 = 0; c1_i199 < 9; c1_i199++) {
    c1_inocov[c1_i199] = c1_hc_b[c1_i199] + c1_Sv[c1_i199];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 91);
  for (c1_i200 = 0; c1_i200 < 36; c1_i200++) {
    c1_nb_a[c1_i200] = c1_Pneg[c1_i200];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i201 = 0; c1_i201 < 6; c1_i201++) {
    c1_i202 = 0;
    for (c1_i203 = 0; c1_i203 < 3; c1_i203++) {
      c1_vc_y[c1_i202 + c1_i201] = 0.0;
      c1_i204 = 0;
      for (c1_i205 = 0; c1_i205 < 6; c1_i205++) {
        c1_vc_y[c1_i202 + c1_i201] += c1_nb_a[c1_i204 + c1_i201] *
          c1_jc_b[c1_i205 + c1_i202];
        c1_i204 += 6;
      }

      c1_i202 += 6;
    }
  }

  for (c1_i206 = 0; c1_i206 < 9; c1_i206++) {
    c1_b_inocov[c1_i206] = c1_inocov[c1_i206];
  }

  c1_inv(chartInstance, c1_b_inocov, c1_hc_b);
  c1_e_eml_scalar_eg(chartInstance);
  c1_e_eml_scalar_eg(chartInstance);
  for (c1_i207 = 0; c1_i207 < 18; c1_i207++) {
    c1_L[c1_i207] = 0.0;
  }

  for (c1_i208 = 0; c1_i208 < 18; c1_i208++) {
    c1_L[c1_i208] = 0.0;
  }

  for (c1_i209 = 0; c1_i209 < 18; c1_i209++) {
    c1_rb_a[c1_i209] = c1_L[c1_i209];
  }

  for (c1_i210 = 0; c1_i210 < 18; c1_i210++) {
    c1_L[c1_i210] = c1_rb_a[c1_i210];
  }

  for (c1_i211 = 0; c1_i211 < 18; c1_i211++) {
    c1_rb_a[c1_i211] = c1_L[c1_i211];
  }

  for (c1_i212 = 0; c1_i212 < 18; c1_i212++) {
    c1_L[c1_i212] = c1_rb_a[c1_i212];
  }

  for (c1_i213 = 0; c1_i213 < 6; c1_i213++) {
    c1_i214 = 0;
    c1_i215 = 0;
    for (c1_i216 = 0; c1_i216 < 3; c1_i216++) {
      c1_L[c1_i214 + c1_i213] = 0.0;
      c1_i217 = 0;
      for (c1_i218 = 0; c1_i218 < 3; c1_i218++) {
        c1_L[c1_i214 + c1_i213] += c1_vc_y[c1_i217 + c1_i213] * c1_hc_b[c1_i218
          + c1_i215];
        c1_i217 += 6;
      }

      c1_i214 += 6;
      c1_i215 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 92);
  for (c1_i219 = 0; c1_i219 < 18; c1_i219++) {
    c1_rb_a[c1_i219] = c1_L[c1_i219];
  }

  for (c1_i220 = 0; c1_i220 < 3; c1_i220++) {
    c1_C[c1_i220] = c1_inov[c1_i220];
  }

  c1_j_eml_scalar_eg(chartInstance);
  c1_j_eml_scalar_eg(chartInstance);
  for (c1_i221 = 0; c1_i221 < 6; c1_i221++) {
    c1_b[c1_i221] = 0.0;
    c1_i222 = 0;
    for (c1_i223 = 0; c1_i223 < 3; c1_i223++) {
      c1_b[c1_i221] += c1_rb_a[c1_i222 + c1_i221] * c1_C[c1_i223];
      c1_i222 += 6;
    }
  }

  for (c1_i224 = 0; c1_i224 < 6; c1_i224++) {
    c1_xhatout[c1_i224] = c1_xhat[c1_i224] + c1_b[c1_i224];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 93);
  for (c1_i225 = 0; c1_i225 < 18; c1_i225++) {
    c1_rb_a[c1_i225] = c1_L[c1_i225];
  }

  c1_f_eml_scalar_eg(chartInstance);
  c1_f_eml_scalar_eg(chartInstance);
  for (c1_i226 = 0; c1_i226 < 6; c1_i226++) {
    c1_i227 = 0;
    c1_i228 = 0;
    for (c1_i229 = 0; c1_i229 < 6; c1_i229++) {
      c1_pb_a[c1_i227 + c1_i226] = 0.0;
      c1_i230 = 0;
      for (c1_i231 = 0; c1_i231 < 3; c1_i231++) {
        c1_pb_a[c1_i227 + c1_i226] += c1_rb_a[c1_i230 + c1_i226] *
          c1_mb_a[c1_i231 + c1_i228];
        c1_i230 += 6;
      }

      c1_i227 += 6;
      c1_i228 += 3;
    }
  }

  c1_eye(chartInstance, c1_nb_a);
  for (c1_i232 = 0; c1_i232 < 36; c1_i232++) {
    c1_nb_a[c1_i232] -= c1_pb_a[c1_i232];
  }

  for (c1_i233 = 0; c1_i233 < 36; c1_i233++) {
    c1_qb_a[c1_i233] = c1_Pneg[c1_i233];
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  for (c1_i234 = 0; c1_i234 < 36; c1_i234++) {
    c1_Pout[c1_i234] = 0.0;
  }

  for (c1_i235 = 0; c1_i235 < 36; c1_i235++) {
    c1_Pout[c1_i235] = 0.0;
  }

  for (c1_i236 = 0; c1_i236 < 36; c1_i236++) {
    c1_ob_a[c1_i236] = c1_Pout[c1_i236];
  }

  for (c1_i237 = 0; c1_i237 < 36; c1_i237++) {
    c1_Pout[c1_i237] = c1_ob_a[c1_i237];
  }

  for (c1_i238 = 0; c1_i238 < 36; c1_i238++) {
    c1_ob_a[c1_i238] = c1_Pout[c1_i238];
  }

  for (c1_i239 = 0; c1_i239 < 36; c1_i239++) {
    c1_Pout[c1_i239] = c1_ob_a[c1_i239];
  }

  for (c1_i240 = 0; c1_i240 < 6; c1_i240++) {
    c1_i241 = 0;
    for (c1_i242 = 0; c1_i242 < 6; c1_i242++) {
      c1_Pout[c1_i241 + c1_i240] = 0.0;
      c1_i243 = 0;
      for (c1_i244 = 0; c1_i244 < 6; c1_i244++) {
        c1_Pout[c1_i241 + c1_i240] += c1_nb_a[c1_i243 + c1_i240] *
          c1_qb_a[c1_i244 + c1_i241];
        c1_i243 += 6;
      }

      c1_i241 += 6;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 96);
  for (c1_i245 = 0; c1_i245 < 3; c1_i245++) {
    c1_yhatout[c1_i245] = c1_yhat[c1_i245];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -96);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i246 = 0; c1_i246 < 6; c1_i246++) {
    (*c1_b_xhatout)[c1_i246] = c1_xhatout[c1_i246];
  }

  for (c1_i247 = 0; c1_i247 < 3; c1_i247++) {
    (*c1_b_yhatout)[c1_i247] = c1_yhatout[c1_i247];
  }

  for (c1_i248 = 0; c1_i248 < 36; c1_i248++) {
    (*c1_b_Pout)[c1_i248] = c1_Pout[c1_i248];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
}

static void registerMessagesc1_HXpump_controller_sanity
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance)
{
}

static void c1_EKFdynamics(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_x[6], real_T c1_hotpar[6], real_T c1_coldpar[4],
  real_T c1_wallpar[4], real_T c1_pumppar[3], real_T c1_input[2], real_T
  c1_xdot[6])
{
  uint32_T c1_debug_family_var_map[34];
  real_T c1_rhoh;
  real_T c1_Vh;
  real_T c1_ch;
  real_T c1_mdoth;
  real_T c1_hh;
  real_T c1_Thi;
  real_T c1_rhoc;
  real_T c1_Vc;
  real_T c1_cc;
  real_T c1_hc;
  real_T c1_mdotc;
  real_T c1_Tci;
  real_T c1_rhow;
  real_T c1_Vw;
  real_T c1_cw;
  real_T c1_A;
  real_T c1_wp;
  real_T c1_wa;
  real_T c1_wb;
  real_T c1_dx1;
  real_T c1_dx2;
  real_T c1_dx3;
  real_T c1_dx4;
  real_T c1_dx5;
  real_T c1_dx6;
  real_T c1_nargin = 6.0;
  real_T c1_nargout = 1.0;
  real_T c1_a;
  real_T c1_b;
  real_T c1_y;
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_b_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_c_y;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_d_y;
  real_T c1_b_A;
  real_T c1_B;
  real_T c1_b_x;
  real_T c1_e_y;
  real_T c1_c_x;
  real_T c1_f_y;
  real_T c1_g_y;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_h_y;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_i_y;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_j_y;
  real_T c1_h_a;
  real_T c1_h_b;
  real_T c1_k_y;
  real_T c1_c_A;
  real_T c1_b_B;
  real_T c1_d_x;
  real_T c1_l_y;
  real_T c1_e_x;
  real_T c1_m_y;
  real_T c1_n_y;
  real_T c1_i_a;
  real_T c1_i_b;
  real_T c1_o_y;
  real_T c1_j_a;
  real_T c1_j_b;
  real_T c1_p_y;
  real_T c1_k_a;
  real_T c1_k_b;
  real_T c1_q_y;
  real_T c1_l_a;
  real_T c1_l_b;
  real_T c1_r_y;
  real_T c1_d_A;
  real_T c1_c_B;
  real_T c1_f_x;
  real_T c1_s_y;
  real_T c1_g_x;
  real_T c1_t_y;
  real_T c1_u_y;
  real_T c1_m_a;
  real_T c1_m_b;
  real_T c1_v_y;
  real_T c1_n_a;
  real_T c1_n_b;
  real_T c1_w_y;
  real_T c1_o_a;
  real_T c1_o_b;
  real_T c1_x_y;
  real_T c1_p_a;
  real_T c1_p_b;
  real_T c1_y_y;
  real_T c1_q_a;
  real_T c1_q_b;
  real_T c1_ab_y;
  real_T c1_e_A;
  real_T c1_d_B;
  real_T c1_h_x;
  real_T c1_bb_y;
  real_T c1_i_x;
  real_T c1_cb_y;
  real_T c1_db_y;
  real_T c1_r_a;
  real_T c1_r_b;
  real_T c1_eb_y;
  real_T c1_s_a;
  real_T c1_s_b;
  real_T c1_fb_y;
  real_T c1_t_a;
  real_T c1_t_b;
  real_T c1_gb_y;
  real_T c1_u_a;
  real_T c1_u_b;
  real_T c1_hb_y;
  real_T c1_f_A;
  real_T c1_e_B;
  real_T c1_j_x;
  real_T c1_ib_y;
  real_T c1_k_x;
  real_T c1_jb_y;
  real_T c1_kb_y;
  real_T c1_v_a;
  real_T c1_v_b;
  real_T c1_lb_y;
  real_T c1_w_a;
  real_T c1_w_b;
  real_T c1_mb_y;
  real_T c1_x_a;
  real_T c1_x_b;
  real_T c1_nb_y;
  real_T c1_y_a;
  real_T c1_y_b;
  real_T c1_ob_y;
  real_T c1_g_A;
  real_T c1_f_B;
  real_T c1_l_x;
  real_T c1_pb_y;
  real_T c1_m_x;
  real_T c1_qb_y;
  real_T c1_rb_y;
  real_T c1_ab_a;
  real_T c1_ab_b;
  real_T c1_sb_y;
  real_T c1_bb_a;
  real_T c1_bb_b;
  real_T c1_tb_y;
  real_T c1_cb_a;
  real_T c1_cb_b;
  real_T c1_ub_y;
  real_T c1_db_a;
  real_T c1_db_b;
  real_T c1_vb_y;
  real_T c1_h_A;
  real_T c1_g_B;
  real_T c1_n_x;
  real_T c1_wb_y;
  real_T c1_o_x;
  real_T c1_xb_y;
  real_T c1_yb_y;
  real_T c1_eb_a;
  real_T c1_eb_b;
  real_T c1_ac_y;
  real_T c1_fb_a;
  real_T c1_fb_b;
  real_T c1_bc_y;
  real_T c1_gb_a;
  real_T c1_gb_b;
  real_T c1_cc_y;
  real_T c1_hb_a;
  real_T c1_hb_b;
  real_T c1_dc_y;
  real_T c1_i_A;
  real_T c1_h_B;
  real_T c1_p_x;
  real_T c1_ec_y;
  real_T c1_q_x;
  real_T c1_fc_y;
  real_T c1_gc_y;
  real_T c1_ib_a;
  real_T c1_ib_b;
  real_T c1_hc_y;
  real_T c1_jb_a;
  real_T c1_jb_b;
  real_T c1_ic_y;
  real_T c1_kb_a;
  real_T c1_kb_b;
  real_T c1_jc_y;
  real_T c1_lb_a;
  real_T c1_lb_b;
  real_T c1_kc_y;
  real_T c1_mb_a;
  real_T c1_mb_b;
  real_T c1_lc_y;
  real_T c1_j_A;
  real_T c1_i_B;
  real_T c1_r_x;
  real_T c1_mc_y;
  real_T c1_s_x;
  real_T c1_nc_y;
  real_T c1_oc_y;
  real_T c1_nb_a;
  real_T c1_nb_b;
  real_T c1_pc_y;
  real_T c1_ob_a;
  real_T c1_ob_b;
  real_T c1_pb_a;
  real_T c1_pb_b;
  real_T c1_qb_a;
  real_T c1_qb_b;
  real_T c1_qc_y;
  real_T c1_rb_a;
  real_T c1_rb_b;
  real_T c1_rc_y;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 34U, 34U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhoh, 0U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vh, 1U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ch, 2U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_mdoth, 3U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_hh, 4U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Thi, 5U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhoc, 6U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vc, 7U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_cc, 8U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_hc, 9U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_mdotc, 10U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Tci, 11U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_rhow, 12U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Vw, 13U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_cw, 14U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_A, 15U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wp, 16U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wa, 17U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_wb, 18U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx1, 19U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx2, 20U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx3, 21U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx4, 22U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx5, 23U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_dx6, 24U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 25U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 26U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_x, 27U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_hotpar, 28U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_coldpar, 29U, c1_f_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_wallpar, 30U, c1_f_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_pumppar, 31U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_input, 32U, c1_e_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_xdot, 33U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_rhoh = c1_hotpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 5);
  c1_Vh = c1_hotpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_ch = c1_hotpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_mdoth = c1_hotpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 8);
  c1_hh = c1_hotpar[4];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_Thi = c1_hotpar[5];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_rhoc = c1_coldpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_Vc = c1_coldpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_cc = c1_coldpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 15);
  c1_hc = c1_coldpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_mdotc = c1_input[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_Tci = c1_input[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_rhow = c1_wallpar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 23);
  c1_Vw = c1_wallpar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 24);
  c1_cw = c1_wallpar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 25);
  c1_A = c1_wallpar[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 28);
  c1_wp = c1_pumppar[0];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 29);
  c1_wa = c1_pumppar[1];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 30);
  c1_wb = c1_pumppar[2];
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 33);
  c1_a = c1_x[3];
  c1_b = c1_ch;
  c1_y = c1_a * c1_b;
  c1_b_a = c1_hh;
  c1_b_b = c1_A;
  c1_b_y = c1_b_a * c1_b_b;
  c1_c_a = c1_rhoh;
  c1_c_b = c1_Vh;
  c1_c_y = c1_c_a * c1_c_b;
  c1_d_a = c1_c_y;
  c1_d_b = c1_ch;
  c1_d_y = c1_d_a * c1_d_b;
  c1_b_A = -(c1_y + c1_b_y);
  c1_B = c1_d_y;
  c1_b_x = c1_b_A;
  c1_e_y = c1_B;
  c1_c_x = c1_b_x;
  c1_f_y = c1_e_y;
  c1_g_y = c1_c_x / c1_f_y;
  c1_e_a = c1_g_y;
  c1_e_b = c1_x[0];
  c1_h_y = c1_e_a * c1_e_b;
  c1_f_a = c1_hh;
  c1_f_b = c1_A;
  c1_i_y = c1_f_a * c1_f_b;
  c1_g_a = c1_rhoh;
  c1_g_b = c1_Vh;
  c1_j_y = c1_g_a * c1_g_b;
  c1_h_a = c1_j_y;
  c1_h_b = c1_ch;
  c1_k_y = c1_h_a * c1_h_b;
  c1_c_A = c1_i_y;
  c1_b_B = c1_k_y;
  c1_d_x = c1_c_A;
  c1_l_y = c1_b_B;
  c1_e_x = c1_d_x;
  c1_m_y = c1_l_y;
  c1_n_y = c1_e_x / c1_m_y;
  c1_i_a = c1_n_y;
  c1_i_b = c1_x[2];
  c1_o_y = c1_i_a * c1_i_b;
  c1_j_a = c1_x[3];
  c1_j_b = c1_ch;
  c1_p_y = c1_j_a * c1_j_b;
  c1_k_a = c1_rhoh;
  c1_k_b = c1_Vh;
  c1_q_y = c1_k_a * c1_k_b;
  c1_l_a = c1_q_y;
  c1_l_b = c1_ch;
  c1_r_y = c1_l_a * c1_l_b;
  c1_d_A = c1_p_y;
  c1_c_B = c1_r_y;
  c1_f_x = c1_d_A;
  c1_s_y = c1_c_B;
  c1_g_x = c1_f_x;
  c1_t_y = c1_s_y;
  c1_u_y = c1_g_x / c1_t_y;
  c1_m_a = c1_u_y;
  c1_m_b = c1_x[4];
  c1_v_y = c1_m_a * c1_m_b;
  c1_dx1 = (c1_h_y + c1_o_y) + c1_v_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 34);
  c1_n_a = c1_x[5];
  c1_n_b = c1_cc;
  c1_w_y = c1_n_a * c1_n_b;
  c1_o_a = c1_hc;
  c1_o_b = c1_A;
  c1_x_y = c1_o_a * c1_o_b;
  c1_p_a = c1_rhoc;
  c1_p_b = c1_Vc;
  c1_y_y = c1_p_a * c1_p_b;
  c1_q_a = c1_y_y;
  c1_q_b = c1_cc;
  c1_ab_y = c1_q_a * c1_q_b;
  c1_e_A = -(c1_w_y + c1_x_y);
  c1_d_B = c1_ab_y;
  c1_h_x = c1_e_A;
  c1_bb_y = c1_d_B;
  c1_i_x = c1_h_x;
  c1_cb_y = c1_bb_y;
  c1_db_y = c1_i_x / c1_cb_y;
  c1_r_a = c1_db_y;
  c1_r_b = c1_x[1];
  c1_eb_y = c1_r_a * c1_r_b;
  c1_s_a = c1_hc;
  c1_s_b = c1_A;
  c1_fb_y = c1_s_a * c1_s_b;
  c1_t_a = c1_rhoc;
  c1_t_b = c1_Vc;
  c1_gb_y = c1_t_a * c1_t_b;
  c1_u_a = c1_gb_y;
  c1_u_b = c1_cc;
  c1_hb_y = c1_u_a * c1_u_b;
  c1_f_A = c1_fb_y;
  c1_e_B = c1_hb_y;
  c1_j_x = c1_f_A;
  c1_ib_y = c1_e_B;
  c1_k_x = c1_j_x;
  c1_jb_y = c1_ib_y;
  c1_kb_y = c1_k_x / c1_jb_y;
  c1_v_a = c1_kb_y;
  c1_v_b = c1_x[2];
  c1_lb_y = c1_v_a * c1_v_b;
  c1_w_a = c1_x[5];
  c1_w_b = c1_cc;
  c1_mb_y = c1_w_a * c1_w_b;
  c1_x_a = c1_rhoc;
  c1_x_b = c1_Vc;
  c1_nb_y = c1_x_a * c1_x_b;
  c1_y_a = c1_nb_y;
  c1_y_b = c1_cc;
  c1_ob_y = c1_y_a * c1_y_b;
  c1_g_A = c1_mb_y;
  c1_f_B = c1_ob_y;
  c1_l_x = c1_g_A;
  c1_pb_y = c1_f_B;
  c1_m_x = c1_l_x;
  c1_qb_y = c1_pb_y;
  c1_rb_y = c1_m_x / c1_qb_y;
  c1_ab_a = c1_rb_y;
  c1_ab_b = c1_Tci;
  c1_sb_y = c1_ab_a * c1_ab_b;
  c1_dx2 = (c1_eb_y + c1_lb_y) + c1_sb_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 35);
  c1_bb_a = c1_hh;
  c1_bb_b = c1_A;
  c1_tb_y = c1_bb_a * c1_bb_b;
  c1_cb_a = c1_rhow;
  c1_cb_b = c1_Vw;
  c1_ub_y = c1_cb_a * c1_cb_b;
  c1_db_a = c1_ub_y;
  c1_db_b = c1_cw;
  c1_vb_y = c1_db_a * c1_db_b;
  c1_h_A = c1_tb_y;
  c1_g_B = c1_vb_y;
  c1_n_x = c1_h_A;
  c1_wb_y = c1_g_B;
  c1_o_x = c1_n_x;
  c1_xb_y = c1_wb_y;
  c1_yb_y = c1_o_x / c1_xb_y;
  c1_eb_a = c1_yb_y;
  c1_eb_b = c1_x[0];
  c1_ac_y = c1_eb_a * c1_eb_b;
  c1_fb_a = c1_hc;
  c1_fb_b = c1_A;
  c1_bc_y = c1_fb_a * c1_fb_b;
  c1_gb_a = c1_rhow;
  c1_gb_b = c1_Vw;
  c1_cc_y = c1_gb_a * c1_gb_b;
  c1_hb_a = c1_cc_y;
  c1_hb_b = c1_cw;
  c1_dc_y = c1_hb_a * c1_hb_b;
  c1_i_A = c1_bc_y;
  c1_h_B = c1_dc_y;
  c1_p_x = c1_i_A;
  c1_ec_y = c1_h_B;
  c1_q_x = c1_p_x;
  c1_fc_y = c1_ec_y;
  c1_gc_y = c1_q_x / c1_fc_y;
  c1_ib_a = c1_gc_y;
  c1_ib_b = c1_x[1];
  c1_hc_y = c1_ib_a * c1_ib_b;
  c1_jb_a = c1_hh;
  c1_jb_b = c1_A;
  c1_ic_y = c1_jb_a * c1_jb_b;
  c1_kb_a = c1_hc;
  c1_kb_b = c1_A;
  c1_jc_y = c1_kb_a * c1_kb_b;
  c1_lb_a = c1_rhow;
  c1_lb_b = c1_Vw;
  c1_kc_y = c1_lb_a * c1_lb_b;
  c1_mb_a = c1_kc_y;
  c1_mb_b = c1_cw;
  c1_lc_y = c1_mb_a * c1_mb_b;
  c1_j_A = c1_ic_y + c1_jc_y;
  c1_i_B = c1_lc_y;
  c1_r_x = c1_j_A;
  c1_mc_y = c1_i_B;
  c1_s_x = c1_r_x;
  c1_nc_y = c1_mc_y;
  c1_oc_y = c1_s_x / c1_nc_y;
  c1_nb_a = c1_oc_y;
  c1_nb_b = c1_x[2];
  c1_pc_y = c1_nb_a * c1_nb_b;
  c1_dx3 = (c1_ac_y + c1_hc_y) - c1_pc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 36);
  c1_ob_a = -c1_wa;
  c1_ob_b = c1_x[3];
  c1_dx4 = c1_ob_a * c1_ob_b;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 37);
  c1_pb_a = -c1_wb;
  c1_pb_b = c1_x[4];
  c1_dx5 = c1_pb_a * c1_pb_b;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_qb_a = -c1_wp;
  c1_qb_b = c1_x[5];
  c1_qc_y = c1_qb_a * c1_qb_b;
  c1_rb_a = c1_wp;
  c1_rb_b = c1_mdotc;
  c1_rc_y = c1_rb_a * c1_rb_b;
  c1_dx6 = c1_qc_y + c1_rc_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 40);
  c1_xdot[0] = c1_dx1;
  c1_xdot[1] = c1_dx2;
  c1_xdot[2] = c1_dx3;
  c1_xdot[3] = c1_dx4;
  c1_xdot[4] = c1_dx5;
  c1_xdot[5] = c1_dx6;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -40);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 0U, sf_debug_get_script_id(
    "C:/Users/LabUser/Documents/JGP Nuclear/wireless nuclear plant/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/EKFdynamics.m"));
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i249;
  int32_T c1_i250;
  int32_T c1_i251;
  real_T c1_b_inData[36];
  int32_T c1_i252;
  int32_T c1_i253;
  int32_T c1_i254;
  real_T c1_u[36];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i249 = 0;
  for (c1_i250 = 0; c1_i250 < 6; c1_i250++) {
    for (c1_i251 = 0; c1_i251 < 6; c1_i251++) {
      c1_b_inData[c1_i251 + c1_i249] = (*(real_T (*)[36])c1_inData)[c1_i251 +
        c1_i249];
    }

    c1_i249 += 6;
  }

  c1_i252 = 0;
  for (c1_i253 = 0; c1_i253 < 6; c1_i253++) {
    for (c1_i254 = 0; c1_i254 < 6; c1_i254++) {
      c1_u[c1_i254 + c1_i252] = c1_b_inData[c1_i254 + c1_i252];
    }

    c1_i252 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_Pout, const char_T *c1_identifier, real_T
  c1_y[36])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Pout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Pout);
}

static void c1_b_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[36])
{
  real_T c1_dv12[36];
  int32_T c1_i255;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv12, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c1_i255 = 0; c1_i255 < 36; c1_i255++) {
    c1_y[c1_i255] = c1_dv12[c1_i255];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Pout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[36];
  int32_T c1_i256;
  int32_T c1_i257;
  int32_T c1_i258;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_Pout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Pout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Pout);
  c1_i256 = 0;
  for (c1_i257 = 0; c1_i257 < 6; c1_i257++) {
    for (c1_i258 = 0; c1_i258 < 6; c1_i258++) {
      (*(real_T (*)[36])c1_outData)[c1_i258 + c1_i256] = c1_y[c1_i258 + c1_i256];
    }

    c1_i256 += 6;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i259;
  real_T c1_b_inData[3];
  int32_T c1_i260;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i259 = 0; c1_i259 < 3; c1_i259++) {
    c1_b_inData[c1_i259] = (*(real_T (*)[3])c1_inData)[c1_i259];
  }

  for (c1_i260 = 0; c1_i260 < 3; c1_i260++) {
    c1_u[c1_i260] = c1_b_inData[c1_i260];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_yhatout, const char_T *c1_identifier, real_T
  c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_yhatout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_yhatout);
}

static void c1_d_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv13[3];
  int32_T c1_i261;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv13, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i261 = 0; c1_i261 < 3; c1_i261++) {
    c1_y[c1_i261] = c1_dv13[c1_i261];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_yhatout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i262;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_yhatout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_yhatout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_yhatout);
  for (c1_i262 = 0; c1_i262 < 3; c1_i262++) {
    (*(real_T (*)[3])c1_outData)[c1_i262] = c1_y[c1_i262];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i263;
  real_T c1_b_inData[6];
  int32_T c1_i264;
  real_T c1_u[6];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i263 = 0; c1_i263 < 6; c1_i263++) {
    c1_b_inData[c1_i263] = (*(real_T (*)[6])c1_inData)[c1_i263];
  }

  for (c1_i264 = 0; c1_i264 < 6; c1_i264++) {
    c1_u[c1_i264] = c1_b_inData[c1_i264];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_xhatout, const char_T *c1_identifier, real_T
  c1_y[6])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_xhatout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_xhatout);
}

static void c1_f_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[6])
{
  real_T c1_dv14[6];
  int32_T c1_i265;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv14, 1, 0, 0U, 1, 0U, 1, 6);
  for (c1_i265 = 0; c1_i265 < 6; c1_i265++) {
    c1_y[c1_i265] = c1_dv14[c1_i265];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_xhatout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[6];
  int32_T c1_i266;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_xhatout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_xhatout), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_xhatout);
  for (c1_i266 = 0; c1_i266 < 6; c1_i266++) {
    (*(real_T (*)[6])c1_outData)[c1_i266] = c1_y[c1_i266];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i267;
  real_T c1_b_inData[2];
  int32_T c1_i268;
  real_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i267 = 0; c1_i267 < 2; c1_i267++) {
    c1_b_inData[c1_i267] = (*(real_T (*)[2])c1_inData)[c1_i267];
  }

  for (c1_i268 = 0; c1_i268 < 2; c1_i268++) {
    c1_u[c1_i268] = c1_b_inData[c1_i268];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i269;
  real_T c1_b_inData[4];
  int32_T c1_i270;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i269 = 0; c1_i269 < 4; c1_i269++) {
    c1_b_inData[c1_i269] = (*(real_T (*)[4])c1_inData)[c1_i269];
  }

  for (c1_i270 = 0; c1_i270 < 4; c1_i270++) {
    c1_u[c1_i270] = c1_b_inData[c1_i270];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_g_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct *
  chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i271;
  int32_T c1_i272;
  int32_T c1_i273;
  real_T c1_b_inData[18];
  int32_T c1_i274;
  int32_T c1_i275;
  int32_T c1_i276;
  real_T c1_u[18];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i271 = 0;
  for (c1_i272 = 0; c1_i272 < 3; c1_i272++) {
    for (c1_i273 = 0; c1_i273 < 6; c1_i273++) {
      c1_b_inData[c1_i273 + c1_i271] = (*(real_T (*)[18])c1_inData)[c1_i273 +
        c1_i271];
    }

    c1_i271 += 6;
  }

  c1_i274 = 0;
  for (c1_i275 = 0; c1_i275 < 3; c1_i275++) {
    for (c1_i276 = 0; c1_i276 < 6; c1_i276++) {
      c1_u[c1_i276 + c1_i274] = c1_b_inData[c1_i276 + c1_i274];
    }

    c1_i274 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 6, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_h_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[18])
{
  real_T c1_dv15[18];
  int32_T c1_i277;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv15, 1, 0, 0U, 1, 0U, 2, 6, 3);
  for (c1_i277 = 0; c1_i277 < 18; c1_i277++) {
    c1_y[c1_i277] = c1_dv15[c1_i277];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_L;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[18];
  int32_T c1_i278;
  int32_T c1_i279;
  int32_T c1_i280;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_L = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_L), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_L);
  c1_i278 = 0;
  for (c1_i279 = 0; c1_i279 < 3; c1_i279++) {
    for (c1_i280 = 0; c1_i280 < 6; c1_i280++) {
      (*(real_T (*)[18])c1_outData)[c1_i280 + c1_i278] = c1_y[c1_i280 + c1_i278];
    }

    c1_i278 += 6;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i281;
  int32_T c1_i282;
  int32_T c1_i283;
  real_T c1_b_inData[9];
  int32_T c1_i284;
  int32_T c1_i285;
  int32_T c1_i286;
  real_T c1_u[9];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i281 = 0;
  for (c1_i282 = 0; c1_i282 < 3; c1_i282++) {
    for (c1_i283 = 0; c1_i283 < 3; c1_i283++) {
      c1_b_inData[c1_i283 + c1_i281] = (*(real_T (*)[9])c1_inData)[c1_i283 +
        c1_i281];
    }

    c1_i281 += 3;
  }

  c1_i284 = 0;
  for (c1_i285 = 0; c1_i285 < 3; c1_i285++) {
    for (c1_i286 = 0; c1_i286 < 3; c1_i286++) {
      c1_u[c1_i286 + c1_i284] = c1_b_inData[c1_i286 + c1_i284];
    }

    c1_i284 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[9])
{
  real_T c1_dv16[9];
  int32_T c1_i287;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv16, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c1_i287 = 0; c1_i287 < 9; c1_i287++) {
    c1_y[c1_i287] = c1_dv16[c1_i287];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_inocov;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[9];
  int32_T c1_i288;
  int32_T c1_i289;
  int32_T c1_i290;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_inocov = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_inocov), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_inocov);
  c1_i288 = 0;
  for (c1_i289 = 0; c1_i289 < 3; c1_i289++) {
    for (c1_i290 = 0; c1_i290 < 3; c1_i290++) {
      (*(real_T (*)[9])c1_outData)[c1_i290 + c1_i288] = c1_y[c1_i290 + c1_i288];
    }

    c1_i288 += 3;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i291;
  int32_T c1_i292;
  int32_T c1_i293;
  real_T c1_b_inData[18];
  int32_T c1_i294;
  int32_T c1_i295;
  int32_T c1_i296;
  real_T c1_u[18];
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i291 = 0;
  for (c1_i292 = 0; c1_i292 < 6; c1_i292++) {
    for (c1_i293 = 0; c1_i293 < 3; c1_i293++) {
      c1_b_inData[c1_i293 + c1_i291] = (*(real_T (*)[18])c1_inData)[c1_i293 +
        c1_i291];
    }

    c1_i291 += 3;
  }

  c1_i294 = 0;
  for (c1_i295 = 0; c1_i295 < 6; c1_i295++) {
    for (c1_i296 = 0; c1_i296 < 3; c1_i296++) {
      c1_u[c1_i296 + c1_i294] = c1_b_inData[c1_i296 + c1_i294];
    }

    c1_i294 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 6), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_j_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[2])
{
  real_T c1_dv17[2];
  int32_T c1_i297;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv17, 1, 0, 0U, 1, 0U, 1, 2);
  for (c1_i297 = 0; c1_i297 < 2; c1_i297++) {
    c1_y[c1_i297] = c1_dv17[c1_i297];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_input;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2];
  int32_T c1_i298;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_input = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_input), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_input);
  for (c1_i298 = 0; c1_i298 < 2; c1_i298++) {
    (*(real_T (*)[2])c1_outData)[c1_i298] = c1_y[c1_i298];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static void c1_k_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4])
{
  real_T c1_dv18[4];
  int32_T c1_i299;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv18, 1, 0, 0U, 1, 0U, 1, 4);
  for (c1_i299 = 0; c1_i299 < 4; c1_i299++) {
    c1_y[c1_i299] = c1_dv18[c1_i299];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_wallpar;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i300;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_wallpar = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_wallpar), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_wallpar);
  for (c1_i300 = 0; c1_i300 < 4; c1_i300++) {
    (*(real_T (*)[4])c1_outData)[c1_i300] = c1_y[c1_i300];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_HXpump_controller_sanity_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[120];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i301;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  c1_b_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 120), FALSE);
  for (c1_i301 = 0; c1_i301 < 120; c1_i301++) {
    c1_r0 = &c1_info[c1_i301];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i301);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i301);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[120])
{
  c1_info[0].context = "";
  c1_info[0].name = "diag";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c1_info[0].fileTimeLo = 1286840286U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c1_info[1].name = "eml_index_class";
  c1_info[1].dominantType = "";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[1].fileTimeLo = 1323192178U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c1_info[2].name = "eml_index_plus";
  c1_info[2].dominantType = "coder.internal.indexInt";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[2].fileTimeLo = 1286840378U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[3].name = "eml_index_class";
  c1_info[3].dominantType = "";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[3].fileTimeLo = 1323192178U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c1_info[4].name = "eml_scalar_eg";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[4].fileTimeLo = 1286840396U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/diag.m";
  c1_info[5].name = "eml_int_forloop_overflow_check";
  c1_info[5].dominantType = "";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[5].fileTimeLo = 1346531940U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c1_info[6].name = "intmax";
  c1_info[6].dominantType = "char";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[6].fileTimeLo = 1311276916U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "";
  c1_info[7].name = "mrdivide";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[7].fileTimeLo = 1357973148U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 1319751566U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[8].name = "rdivide";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[8].fileTimeLo = 1346531988U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[9].name = "eml_scalexp_compatible";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[9].fileTimeLo = 1286840396U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[10].name = "eml_div";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[10].fileTimeLo = 1313369410U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context = "";
  c1_info[11].name = "EKFdynamics";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[E]C:/Users/LabUser/Documents/JGP Nuclear/wireless nuclear plant/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/EKFdynamics.m";
  c1_info[11].fileTimeLo = 1469210999U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[E]C:/Users/LabUser/Documents/JGP Nuclear/wireless nuclear plant/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/EKFdynamics.m";
  c1_info[12].name = "mtimes";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[12].fileTimeLo = 1289541292U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[E]C:/Users/LabUser/Documents/JGP Nuclear/wireless nuclear plant/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/EKFdynamics.m";
  c1_info[13].name = "mrdivide";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[13].fileTimeLo = 1357973148U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 1319751566U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context = "";
  c1_info[14].name = "mtimes";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[14].fileTimeLo = 1289541292U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context = "";
  c1_info[15].name = "eye";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c1_info[15].fileTimeLo = 1286840288U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c1_info[16].name = "eml_assert_valid_size_arg";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[16].fileTimeLo = 1286840294U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c1_info[17].name = "isinf";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c1_info[17].fileTimeLo = 1286840360U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c1_info[18].name = "mtimes";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[18].fileTimeLo = 1289541292U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[19].name = "eml_index_class";
  c1_info[19].dominantType = "";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[19].fileTimeLo = 1323192178U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c1_info[20].name = "intmax";
  c1_info[20].dominantType = "char";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[20].fileTimeLo = 1311276916U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c1_info[21].name = "eml_is_float_class";
  c1_info[21].dominantType = "char";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c1_info[21].fileTimeLo = 1286840382U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c1_info[22].name = "min";
  c1_info[22].dominantType = "double";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c1_info[22].fileTimeLo = 1311276918U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c1_info[23].name = "eml_min_or_max";
  c1_info[23].dominantType = "char";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c1_info[23].fileTimeLo = 1334093090U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c1_info[24].name = "eml_scalar_eg";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[24].fileTimeLo = 1286840396U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c1_info[25].name = "eml_scalexp_alloc";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[25].fileTimeLo = 1352446460U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c1_info[26].name = "eml_index_class";
  c1_info[26].dominantType = "";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[26].fileTimeLo = 1323192178U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c1_info[27].name = "eml_scalar_eg";
  c1_info[27].dominantType = "double";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[27].fileTimeLo = 1286840396U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c1_info[28].name = "eml_index_class";
  c1_info[28].dominantType = "";
  c1_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[28].fileTimeLo = 1323192178U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c1_info[29].name = "eml_int_forloop_overflow_check";
  c1_info[29].dominantType = "";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[29].fileTimeLo = 1346531940U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context = "";
  c1_info[30].name = "mpower";
  c1_info[30].dominantType = "double";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[30].fileTimeLo = 1286840442U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[31].name = "eml_scalar_floor";
  c1_info[31].dominantType = "double";
  c1_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[31].fileTimeLo = 1286840326U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[32].name = "eml_index_class";
  c1_info[32].dominantType = "";
  c1_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[32].fileTimeLo = 1323192178U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
  c1_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[33].name = "eml_scalar_eg";
  c1_info[33].dominantType = "double";
  c1_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[33].fileTimeLo = 1286840396U;
  c1_info[33].fileTimeHi = 0U;
  c1_info[33].mFileTimeLo = 0U;
  c1_info[33].mFileTimeHi = 0U;
  c1_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[34].name = "eml_scalar_abs";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[34].fileTimeLo = 1286840312U;
  c1_info[34].fileTimeHi = 0U;
  c1_info[34].mFileTimeLo = 0U;
  c1_info[34].mFileTimeHi = 0U;
  c1_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[35].name = "eml_scalar_floor";
  c1_info[35].dominantType = "double";
  c1_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[35].fileTimeLo = 1286840326U;
  c1_info[35].fileTimeHi = 0U;
  c1_info[35].mFileTimeLo = 0U;
  c1_info[35].mFileTimeHi = 0U;
  c1_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[36].name = "mtimes";
  c1_info[36].dominantType = "double";
  c1_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[36].fileTimeLo = 1289541292U;
  c1_info[36].fileTimeHi = 0U;
  c1_info[36].mFileTimeLo = 0U;
  c1_info[36].mFileTimeHi = 0U;
  c1_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[37].name = "eml_index_class";
  c1_info[37].dominantType = "";
  c1_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[37].fileTimeLo = 1323192178U;
  c1_info[37].fileTimeHi = 0U;
  c1_info[37].mFileTimeLo = 0U;
  c1_info[37].mFileTimeHi = 0U;
  c1_info[38].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[38].name = "eml_scalar_eg";
  c1_info[38].dominantType = "double";
  c1_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[38].fileTimeLo = 1286840396U;
  c1_info[38].fileTimeHi = 0U;
  c1_info[38].mFileTimeLo = 0U;
  c1_info[38].mFileTimeHi = 0U;
  c1_info[39].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[39].name = "eml_xgemm";
  c1_info[39].dominantType = "char";
  c1_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[39].fileTimeLo = 1299098372U;
  c1_info[39].fileTimeHi = 0U;
  c1_info[39].mFileTimeLo = 0U;
  c1_info[39].mFileTimeHi = 0U;
  c1_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[40].name = "eml_blas_inline";
  c1_info[40].dominantType = "";
  c1_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[40].fileTimeLo = 1299098368U;
  c1_info[40].fileTimeHi = 0U;
  c1_info[40].mFileTimeLo = 0U;
  c1_info[40].mFileTimeHi = 0U;
  c1_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c1_info[41].name = "mtimes";
  c1_info[41].dominantType = "double";
  c1_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[41].fileTimeLo = 1289541292U;
  c1_info[41].fileTimeHi = 0U;
  c1_info[41].mFileTimeLo = 0U;
  c1_info[41].mFileTimeHi = 0U;
  c1_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[42].name = "eml_index_class";
  c1_info[42].dominantType = "";
  c1_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[42].fileTimeLo = 1323192178U;
  c1_info[42].fileTimeHi = 0U;
  c1_info[42].mFileTimeLo = 0U;
  c1_info[42].mFileTimeHi = 0U;
  c1_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[43].name = "eml_scalar_eg";
  c1_info[43].dominantType = "double";
  c1_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[43].fileTimeLo = 1286840396U;
  c1_info[43].fileTimeHi = 0U;
  c1_info[43].mFileTimeLo = 0U;
  c1_info[43].mFileTimeHi = 0U;
  c1_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[44].name = "eml_refblas_xgemm";
  c1_info[44].dominantType = "char";
  c1_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[44].fileTimeLo = 1299098374U;
  c1_info[44].fileTimeHi = 0U;
  c1_info[44].mFileTimeLo = 0U;
  c1_info[44].mFileTimeHi = 0U;
  c1_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m!matrix_to_integer_power";
  c1_info[45].name = "inv";
  c1_info[45].dominantType = "double";
  c1_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c1_info[45].fileTimeLo = 1305339600U;
  c1_info[45].fileTimeHi = 0U;
  c1_info[45].mFileTimeLo = 0U;
  c1_info[45].mFileTimeHi = 0U;
  c1_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c1_info[46].name = "eml_index_class";
  c1_info[46].dominantType = "";
  c1_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[46].fileTimeLo = 1323192178U;
  c1_info[46].fileTimeHi = 0U;
  c1_info[46].mFileTimeLo = 0U;
  c1_info[46].mFileTimeHi = 0U;
  c1_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c1_info[47].name = "eml_xgetrf";
  c1_info[47].dominantType = "double";
  c1_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c1_info[47].fileTimeLo = 1286840406U;
  c1_info[47].fileTimeHi = 0U;
  c1_info[47].mFileTimeLo = 0U;
  c1_info[47].mFileTimeHi = 0U;
  c1_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c1_info[48].name = "eml_lapack_xgetrf";
  c1_info[48].dominantType = "double";
  c1_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c1_info[48].fileTimeLo = 1286840410U;
  c1_info[48].fileTimeHi = 0U;
  c1_info[48].mFileTimeLo = 0U;
  c1_info[48].mFileTimeHi = 0U;
  c1_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c1_info[49].name = "eml_matlab_zgetrf";
  c1_info[49].dominantType = "double";
  c1_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[49].fileTimeLo = 1302710594U;
  c1_info[49].fileTimeHi = 0U;
  c1_info[49].mFileTimeLo = 0U;
  c1_info[49].mFileTimeHi = 0U;
  c1_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[50].name = "realmin";
  c1_info[50].dominantType = "char";
  c1_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[50].fileTimeLo = 1307672842U;
  c1_info[50].fileTimeHi = 0U;
  c1_info[50].mFileTimeLo = 0U;
  c1_info[50].mFileTimeHi = 0U;
  c1_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[51].name = "eml_realmin";
  c1_info[51].dominantType = "char";
  c1_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[51].fileTimeLo = 1307672844U;
  c1_info[51].fileTimeHi = 0U;
  c1_info[51].mFileTimeLo = 0U;
  c1_info[51].mFileTimeHi = 0U;
  c1_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[52].name = "eml_float_model";
  c1_info[52].dominantType = "char";
  c1_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[52].fileTimeLo = 1326749596U;
  c1_info[52].fileTimeHi = 0U;
  c1_info[52].mFileTimeLo = 0U;
  c1_info[52].mFileTimeHi = 0U;
  c1_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[53].name = "eps";
  c1_info[53].dominantType = "char";
  c1_info[53].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[53].fileTimeLo = 1326749596U;
  c1_info[53].fileTimeHi = 0U;
  c1_info[53].mFileTimeLo = 0U;
  c1_info[53].mFileTimeHi = 0U;
  c1_info[54].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[54].name = "eml_is_float_class";
  c1_info[54].dominantType = "char";
  c1_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c1_info[54].fileTimeLo = 1286840382U;
  c1_info[54].fileTimeHi = 0U;
  c1_info[54].mFileTimeLo = 0U;
  c1_info[54].mFileTimeHi = 0U;
  c1_info[55].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[55].name = "eml_eps";
  c1_info[55].dominantType = "char";
  c1_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[55].fileTimeLo = 1326749596U;
  c1_info[55].fileTimeHi = 0U;
  c1_info[55].mFileTimeLo = 0U;
  c1_info[55].mFileTimeHi = 0U;
  c1_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c1_info[56].name = "eml_float_model";
  c1_info[56].dominantType = "char";
  c1_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[56].fileTimeLo = 1326749596U;
  c1_info[56].fileTimeHi = 0U;
  c1_info[56].mFileTimeLo = 0U;
  c1_info[56].mFileTimeHi = 0U;
  c1_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[57].name = "min";
  c1_info[57].dominantType = "coder.internal.indexInt";
  c1_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c1_info[57].fileTimeLo = 1311276918U;
  c1_info[57].fileTimeHi = 0U;
  c1_info[57].mFileTimeLo = 0U;
  c1_info[57].mFileTimeHi = 0U;
  c1_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c1_info[58].name = "eml_scalar_eg";
  c1_info[58].dominantType = "coder.internal.indexInt";
  c1_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[58].fileTimeLo = 1286840396U;
  c1_info[58].fileTimeHi = 0U;
  c1_info[58].mFileTimeLo = 0U;
  c1_info[58].mFileTimeHi = 0U;
  c1_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c1_info[59].name = "eml_scalexp_alloc";
  c1_info[59].dominantType = "coder.internal.indexInt";
  c1_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[59].fileTimeLo = 1352446460U;
  c1_info[59].fileTimeHi = 0U;
  c1_info[59].mFileTimeLo = 0U;
  c1_info[59].mFileTimeHi = 0U;
  c1_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c1_info[60].name = "eml_scalar_eg";
  c1_info[60].dominantType = "coder.internal.indexInt";
  c1_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[60].fileTimeLo = 1286840396U;
  c1_info[60].fileTimeHi = 0U;
  c1_info[60].mFileTimeLo = 0U;
  c1_info[60].mFileTimeHi = 0U;
  c1_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[61].name = "colon";
  c1_info[61].dominantType = "double";
  c1_info[61].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[61].fileTimeLo = 1348213528U;
  c1_info[61].fileTimeHi = 0U;
  c1_info[61].mFileTimeLo = 0U;
  c1_info[61].mFileTimeHi = 0U;
  c1_info[62].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[62].name = "colon";
  c1_info[62].dominantType = "double";
  c1_info[62].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[62].fileTimeLo = 1348213528U;
  c1_info[62].fileTimeHi = 0U;
  c1_info[62].mFileTimeLo = 0U;
  c1_info[62].mFileTimeHi = 0U;
  c1_info[63].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[63].name = "floor";
  c1_info[63].dominantType = "double";
  c1_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[63].fileTimeLo = 1343851980U;
  c1_info[63].fileTimeHi = 0U;
  c1_info[63].mFileTimeLo = 0U;
  c1_info[63].mFileTimeHi = 0U;
}

static void c1_b_info_helper(c1_ResolvedFunctionInfo c1_info[120])
{
  c1_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[64].name = "eml_scalar_floor";
  c1_info[64].dominantType = "double";
  c1_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[64].fileTimeLo = 1286840326U;
  c1_info[64].fileTimeHi = 0U;
  c1_info[64].mFileTimeLo = 0U;
  c1_info[64].mFileTimeHi = 0U;
  c1_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c1_info[65].name = "intmin";
  c1_info[65].dominantType = "char";
  c1_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c1_info[65].fileTimeLo = 1311276918U;
  c1_info[65].fileTimeHi = 0U;
  c1_info[65].mFileTimeLo = 0U;
  c1_info[65].mFileTimeHi = 0U;
  c1_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c1_info[66].name = "intmax";
  c1_info[66].dominantType = "char";
  c1_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[66].fileTimeLo = 1311276916U;
  c1_info[66].fileTimeHi = 0U;
  c1_info[66].mFileTimeLo = 0U;
  c1_info[66].mFileTimeHi = 0U;
  c1_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c1_info[67].name = "intmin";
  c1_info[67].dominantType = "char";
  c1_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c1_info[67].fileTimeLo = 1311276918U;
  c1_info[67].fileTimeHi = 0U;
  c1_info[67].mFileTimeLo = 0U;
  c1_info[67].mFileTimeHi = 0U;
  c1_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c1_info[68].name = "intmax";
  c1_info[68].dominantType = "char";
  c1_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[68].fileTimeLo = 1311276916U;
  c1_info[68].fileTimeHi = 0U;
  c1_info[68].mFileTimeLo = 0U;
  c1_info[68].mFileTimeHi = 0U;
  c1_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c1_info[69].name = "eml_isa_uint";
  c1_info[69].dominantType = "coder.internal.indexInt";
  c1_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c1_info[69].fileTimeLo = 1286840384U;
  c1_info[69].fileTimeHi = 0U;
  c1_info[69].mFileTimeLo = 0U;
  c1_info[69].mFileTimeHi = 0U;
  c1_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c1_info[70].name = "eml_unsigned_class";
  c1_info[70].dominantType = "char";
  c1_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c1_info[70].fileTimeLo = 1323192180U;
  c1_info[70].fileTimeHi = 0U;
  c1_info[70].mFileTimeLo = 0U;
  c1_info[70].mFileTimeHi = 0U;
  c1_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c1_info[71].name = "eml_index_class";
  c1_info[71].dominantType = "";
  c1_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[71].fileTimeLo = 1323192178U;
  c1_info[71].fileTimeHi = 0U;
  c1_info[71].mFileTimeLo = 0U;
  c1_info[71].mFileTimeHi = 0U;
  c1_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c1_info[72].name = "eml_index_class";
  c1_info[72].dominantType = "";
  c1_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[72].fileTimeLo = 1323192178U;
  c1_info[72].fileTimeHi = 0U;
  c1_info[72].mFileTimeLo = 0U;
  c1_info[72].mFileTimeHi = 0U;
  c1_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c1_info[73].name = "intmax";
  c1_info[73].dominantType = "char";
  c1_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[73].fileTimeLo = 1311276916U;
  c1_info[73].fileTimeHi = 0U;
  c1_info[73].mFileTimeLo = 0U;
  c1_info[73].mFileTimeHi = 0U;
  c1_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c1_info[74].name = "eml_isa_uint";
  c1_info[74].dominantType = "coder.internal.indexInt";
  c1_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c1_info[74].fileTimeLo = 1286840384U;
  c1_info[74].fileTimeHi = 0U;
  c1_info[74].mFileTimeLo = 0U;
  c1_info[74].mFileTimeHi = 0U;
  c1_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c1_info[75].name = "eml_index_plus";
  c1_info[75].dominantType = "double";
  c1_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[75].fileTimeLo = 1286840378U;
  c1_info[75].fileTimeHi = 0U;
  c1_info[75].mFileTimeLo = 0U;
  c1_info[75].mFileTimeHi = 0U;
  c1_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon";
  c1_info[76].name = "eml_int_forloop_overflow_check";
  c1_info[76].dominantType = "";
  c1_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[76].fileTimeLo = 1346531940U;
  c1_info[76].fileTimeHi = 0U;
  c1_info[76].mFileTimeLo = 0U;
  c1_info[76].mFileTimeHi = 0U;
  c1_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[77].name = "eml_index_class";
  c1_info[77].dominantType = "";
  c1_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[77].fileTimeLo = 1323192178U;
  c1_info[77].fileTimeHi = 0U;
  c1_info[77].mFileTimeLo = 0U;
  c1_info[77].mFileTimeHi = 0U;
  c1_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[78].name = "eml_index_plus";
  c1_info[78].dominantType = "double";
  c1_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[78].fileTimeLo = 1286840378U;
  c1_info[78].fileTimeHi = 0U;
  c1_info[78].mFileTimeLo = 0U;
  c1_info[78].mFileTimeHi = 0U;
  c1_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[79].name = "eml_int_forloop_overflow_check";
  c1_info[79].dominantType = "";
  c1_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[79].fileTimeLo = 1346531940U;
  c1_info[79].fileTimeHi = 0U;
  c1_info[79].mFileTimeLo = 0U;
  c1_info[79].mFileTimeHi = 0U;
  c1_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[80].name = "eml_index_minus";
  c1_info[80].dominantType = "double";
  c1_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[80].fileTimeLo = 1286840378U;
  c1_info[80].fileTimeHi = 0U;
  c1_info[80].mFileTimeLo = 0U;
  c1_info[80].mFileTimeHi = 0U;
  c1_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[81].name = "eml_index_class";
  c1_info[81].dominantType = "";
  c1_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[81].fileTimeLo = 1323192178U;
  c1_info[81].fileTimeHi = 0U;
  c1_info[81].mFileTimeLo = 0U;
  c1_info[81].mFileTimeHi = 0U;
  c1_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[82].name = "eml_index_minus";
  c1_info[82].dominantType = "coder.internal.indexInt";
  c1_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[82].fileTimeLo = 1286840378U;
  c1_info[82].fileTimeHi = 0U;
  c1_info[82].mFileTimeLo = 0U;
  c1_info[82].mFileTimeHi = 0U;
  c1_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[83].name = "eml_index_times";
  c1_info[83].dominantType = "coder.internal.indexInt";
  c1_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[83].fileTimeLo = 1286840380U;
  c1_info[83].fileTimeHi = 0U;
  c1_info[83].mFileTimeLo = 0U;
  c1_info[83].mFileTimeHi = 0U;
  c1_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[84].name = "eml_index_class";
  c1_info[84].dominantType = "";
  c1_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[84].fileTimeLo = 1323192178U;
  c1_info[84].fileTimeHi = 0U;
  c1_info[84].mFileTimeLo = 0U;
  c1_info[84].mFileTimeHi = 0U;
  c1_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[85].name = "eml_index_plus";
  c1_info[85].dominantType = "coder.internal.indexInt";
  c1_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[85].fileTimeLo = 1286840378U;
  c1_info[85].fileTimeHi = 0U;
  c1_info[85].mFileTimeLo = 0U;
  c1_info[85].mFileTimeHi = 0U;
  c1_info[86].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c1_info[86].name = "eml_ixamax";
  c1_info[86].dominantType = "double";
  c1_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c1_info[86].fileTimeLo = 1299098370U;
  c1_info[86].fileTimeHi = 0U;
  c1_info[86].mFileTimeLo = 0U;
  c1_info[86].mFileTimeHi = 0U;
  c1_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c1_info[87].name = "eml_blas_inline";
  c1_info[87].dominantType = "";
  c1_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[87].fileTimeLo = 1299098368U;
  c1_info[87].fileTimeHi = 0U;
  c1_info[87].mFileTimeLo = 0U;
  c1_info[87].mFileTimeHi = 0U;
  c1_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m!below_threshold";
  c1_info[88].name = "length";
  c1_info[88].dominantType = "double";
  c1_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[88].fileTimeLo = 1303167806U;
  c1_info[88].fileTimeHi = 0U;
  c1_info[88].mFileTimeLo = 0U;
  c1_info[88].mFileTimeHi = 0U;
  c1_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength";
  c1_info[89].name = "eml_index_class";
  c1_info[89].dominantType = "";
  c1_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[89].fileTimeLo = 1323192178U;
  c1_info[89].fileTimeHi = 0U;
  c1_info[89].mFileTimeLo = 0U;
  c1_info[89].mFileTimeHi = 0U;
  c1_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c1_info[90].name = "eml_index_class";
  c1_info[90].dominantType = "";
  c1_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[90].fileTimeLo = 1323192178U;
  c1_info[90].fileTimeHi = 0U;
  c1_info[90].mFileTimeLo = 0U;
  c1_info[90].mFileTimeHi = 0U;
  c1_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c1_info[91].name = "eml_refblas_ixamax";
  c1_info[91].dominantType = "double";
  c1_info[91].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c1_info[91].fileTimeLo = 1299098370U;
  c1_info[91].fileTimeHi = 0U;
  c1_info[91].mFileTimeLo = 0U;
  c1_info[91].mFileTimeHi = 0U;
  c1_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c1_info[92].name = "eml_index_class";
  c1_info[92].dominantType = "";
  c1_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[92].fileTimeLo = 1323192178U;
  c1_info[92].fileTimeHi = 0U;
  c1_info[92].mFileTimeLo = 0U;
  c1_info[92].mFileTimeHi = 0U;
  c1_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c1_info[93].name = "eml_xcabs1";
  c1_info[93].dominantType = "double";
  c1_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c1_info[93].fileTimeLo = 1286840306U;
  c1_info[93].fileTimeHi = 0U;
  c1_info[93].mFileTimeLo = 0U;
  c1_info[93].mFileTimeHi = 0U;
  c1_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c1_info[94].name = "abs";
  c1_info[94].dominantType = "double";
  c1_info[94].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[94].fileTimeLo = 1343851966U;
  c1_info[94].fileTimeHi = 0U;
  c1_info[94].mFileTimeLo = 0U;
  c1_info[94].mFileTimeHi = 0U;
  c1_info[95].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[95].name = "eml_scalar_abs";
  c1_info[95].dominantType = "double";
  c1_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[95].fileTimeLo = 1286840312U;
  c1_info[95].fileTimeHi = 0U;
  c1_info[95].mFileTimeLo = 0U;
  c1_info[95].mFileTimeHi = 0U;
  c1_info[96].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c1_info[96].name = "eml_int_forloop_overflow_check";
  c1_info[96].dominantType = "";
  c1_info[96].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[96].fileTimeLo = 1346531940U;
  c1_info[96].fileTimeHi = 0U;
  c1_info[96].mFileTimeLo = 0U;
  c1_info[96].mFileTimeHi = 0U;
  c1_info[97].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[97].name = "power";
  c1_info[97].dominantType = "double";
  c1_info[97].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[97].fileTimeLo = 1348213530U;
  c1_info[97].fileTimeHi = 0U;
  c1_info[97].mFileTimeLo = 0U;
  c1_info[97].mFileTimeHi = 0U;
  c1_info[98].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[98].name = "eml_scalar_eg";
  c1_info[98].dominantType = "double";
  c1_info[98].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[98].fileTimeLo = 1286840396U;
  c1_info[98].fileTimeHi = 0U;
  c1_info[98].mFileTimeLo = 0U;
  c1_info[98].mFileTimeHi = 0U;
  c1_info[99].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[99].name = "eml_scalexp_alloc";
  c1_info[99].dominantType = "double";
  c1_info[99].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[99].fileTimeLo = 1352446460U;
  c1_info[99].fileTimeHi = 0U;
  c1_info[99].mFileTimeLo = 0U;
  c1_info[99].mFileTimeHi = 0U;
  c1_info[100].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c1_info[100].name = "floor";
  c1_info[100].dominantType = "double";
  c1_info[100].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[100].fileTimeLo = 1343851980U;
  c1_info[100].fileTimeHi = 0U;
  c1_info[100].mFileTimeLo = 0U;
  c1_info[100].mFileTimeHi = 0U;
  c1_info[101].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c1_info[101].name = "eml_scalar_eg";
  c1_info[101].dominantType = "double";
  c1_info[101].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[101].fileTimeLo = 1286840396U;
  c1_info[101].fileTimeHi = 0U;
  c1_info[101].mFileTimeLo = 0U;
  c1_info[101].mFileTimeHi = 0U;
  c1_info[102].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c1_info[102].name = "mtimes";
  c1_info[102].dominantType = "double";
  c1_info[102].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[102].fileTimeLo = 1289541292U;
  c1_info[102].fileTimeHi = 0U;
  c1_info[102].mFileTimeLo = 0U;
  c1_info[102].mFileTimeHi = 0U;
  c1_info[103].context = "";
  c1_info[103].name = "inv";
  c1_info[103].dominantType = "double";
  c1_info[103].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c1_info[103].fileTimeLo = 1305339600U;
  c1_info[103].fileTimeHi = 0U;
  c1_info[103].mFileTimeLo = 0U;
  c1_info[103].mFileTimeHi = 0U;
  c1_info[104].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c1_info[104].name = "eml_index_class";
  c1_info[104].dominantType = "";
  c1_info[104].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[104].fileTimeLo = 1323192178U;
  c1_info[104].fileTimeHi = 0U;
  c1_info[104].mFileTimeLo = 0U;
  c1_info[104].mFileTimeHi = 0U;
  c1_info[105].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c1_info[105].name = "abs";
  c1_info[105].dominantType = "double";
  c1_info[105].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[105].fileTimeLo = 1343851966U;
  c1_info[105].fileTimeHi = 0U;
  c1_info[105].mFileTimeLo = 0U;
  c1_info[105].mFileTimeHi = 0U;
  c1_info[106].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c1_info[106].name = "eml_div";
  c1_info[106].dominantType = "double";
  c1_info[106].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[106].fileTimeLo = 1313369410U;
  c1_info[106].fileTimeHi = 0U;
  c1_info[106].mFileTimeLo = 0U;
  c1_info[106].mFileTimeHi = 0U;
  c1_info[107].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c1_info[107].name = "mtimes";
  c1_info[107].dominantType = "double";
  c1_info[107].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[107].fileTimeLo = 1289541292U;
  c1_info[107].fileTimeHi = 0U;
  c1_info[107].mFileTimeLo = 0U;
  c1_info[107].mFileTimeHi = 0U;
  c1_info[108].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!inv3x3";
  c1_info[108].name = "eml_index_plus";
  c1_info[108].dominantType = "double";
  c1_info[108].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[108].fileTimeLo = 1286840378U;
  c1_info[108].fileTimeHi = 0U;
  c1_info[108].mFileTimeLo = 0U;
  c1_info[108].mFileTimeHi = 0U;
  c1_info[109].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[109].name = "norm";
  c1_info[109].dominantType = "double";
  c1_info[109].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c1_info[109].fileTimeLo = 1336543694U;
  c1_info[109].fileTimeHi = 0U;
  c1_info[109].mFileTimeLo = 0U;
  c1_info[109].mFileTimeHi = 0U;
  c1_info[110].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c1_info[110].name = "abs";
  c1_info[110].dominantType = "double";
  c1_info[110].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[110].fileTimeLo = 1343851966U;
  c1_info[110].fileTimeHi = 0U;
  c1_info[110].mFileTimeLo = 0U;
  c1_info[110].mFileTimeHi = 0U;
  c1_info[111].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c1_info[111].name = "isnan";
  c1_info[111].dominantType = "double";
  c1_info[111].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[111].fileTimeLo = 1286840360U;
  c1_info[111].fileTimeHi = 0U;
  c1_info[111].mFileTimeLo = 0U;
  c1_info[111].mFileTimeHi = 0U;
  c1_info[112].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c1_info[112].name = "eml_guarded_nan";
  c1_info[112].dominantType = "char";
  c1_info[112].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c1_info[112].fileTimeLo = 1286840376U;
  c1_info[112].fileTimeHi = 0U;
  c1_info[112].mFileTimeLo = 0U;
  c1_info[112].mFileTimeHi = 0U;
  c1_info[113].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c1_info[113].name = "eml_is_float_class";
  c1_info[113].dominantType = "char";
  c1_info[113].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c1_info[113].fileTimeLo = 1286840382U;
  c1_info[113].fileTimeHi = 0U;
  c1_info[113].mFileTimeLo = 0U;
  c1_info[113].mFileTimeHi = 0U;
  c1_info[114].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[114].name = "mtimes";
  c1_info[114].dominantType = "double";
  c1_info[114].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[114].fileTimeLo = 1289541292U;
  c1_info[114].fileTimeHi = 0U;
  c1_info[114].mFileTimeLo = 0U;
  c1_info[114].mFileTimeHi = 0U;
  c1_info[115].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[115].name = "eml_warning";
  c1_info[115].dominantType = "char";
  c1_info[115].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c1_info[115].fileTimeLo = 1286840402U;
  c1_info[115].fileTimeHi = 0U;
  c1_info[115].mFileTimeLo = 0U;
  c1_info[115].mFileTimeHi = 0U;
  c1_info[116].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[116].name = "isnan";
  c1_info[116].dominantType = "double";
  c1_info[116].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[116].fileTimeLo = 1286840360U;
  c1_info[116].fileTimeHi = 0U;
  c1_info[116].mFileTimeLo = 0U;
  c1_info[116].mFileTimeHi = 0U;
  c1_info[117].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[117].name = "eps";
  c1_info[117].dominantType = "char";
  c1_info[117].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[117].fileTimeLo = 1326749596U;
  c1_info[117].fileTimeHi = 0U;
  c1_info[117].mFileTimeLo = 0U;
  c1_info[117].mFileTimeHi = 0U;
  c1_info[118].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c1_info[118].name = "eml_flt2str";
  c1_info[118].dominantType = "double";
  c1_info[118].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c1_info[118].fileTimeLo = 1309472796U;
  c1_info[118].fileTimeHi = 0U;
  c1_info[118].mFileTimeLo = 0U;
  c1_info[118].mFileTimeHi = 0U;
  c1_info[119].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c1_info[119].name = "char";
  c1_info[119].dominantType = "double";
  c1_info[119].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m";
  c1_info[119].fileTimeLo = 1319751568U;
  c1_info[119].fileTimeHi = 0U;
  c1_info[119].mFileTimeLo = 0U;
  c1_info[119].mFileTimeHi = 0U;
}

static void c1_diag(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                    real_T c1_v[3], real_T c1_d[9])
{
  int32_T c1_i302;
  int32_T c1_j;
  int32_T c1_b_j;
  int32_T c1_a;
  int32_T c1_c;
  for (c1_i302 = 0; c1_i302 < 9; c1_i302++) {
    c1_d[c1_i302] = 0.0;
  }

  for (c1_j = 1; c1_j < 4; c1_j++) {
    c1_b_j = c1_j;
    c1_a = c1_b_j;
    c1_c = c1_a;
    c1_d[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_c), 1, 3, 2, 0) - 1)) - 1]
      = c1_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c1_b_j), 1, 3, 1, 0) - 1];
  }
}

static void c1_eye(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                   real_T c1_I[36])
{
  int32_T c1_i303;
  int32_T c1_i;
  int32_T c1_b_i;
  for (c1_i303 = 0; c1_i303 < 36; c1_i303++) {
    c1_I[c1_i303] = 0.0;
  }

  for (c1_i = 1; c1_i < 7; c1_i++) {
    c1_b_i = c1_i;
    c1_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c1_b_i), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c1_b_i), 1, 6, 2, 0) - 1)) -
      1] = 1.0;
  }
}

static void c1_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_mpower(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_a[36], real_T c1_c[36])
{
  int32_T c1_i304;
  real_T c1_b_a[36];
  for (c1_i304 = 0; c1_i304 < 36; c1_i304++) {
    c1_b_a[c1_i304] = c1_a[c1_i304];
  }

  c1_matrix_to_integer_power(chartInstance, c1_b_a, c1_c);
}

static void c1_b_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_c_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36])
{
  real_T c1_e;
  boolean_T c1_firstmult;
  real_T c1_x;
  real_T c1_ed2;
  real_T c1_b;
  real_T c1_y;
  int32_T c1_i305;
  int32_T c1_i306;
  real_T c1_A[36];
  int32_T c1_i307;
  int32_T c1_i308;
  int32_T c1_i309;
  int32_T c1_i310;
  int32_T c1_i311;
  int32_T c1_i312;
  int32_T c1_i313;
  int32_T c1_i314;
  int32_T c1_i315;
  int32_T c1_i316;
  int32_T c1_i317;
  int32_T exitg1;
  c1_b_eml_scalar_eg(chartInstance);
  c1_e = 2.0;
  c1_firstmult = TRUE;
  do {
    exitg1 = 0;
    c1_x = c1_e / 2.0;
    c1_ed2 = c1_x;
    c1_ed2 = muDoubleScalarFloor(c1_ed2);
    c1_b = c1_ed2;
    c1_y = 2.0 * c1_b;
    if (c1_y != c1_e) {
      if (c1_firstmult) {
        for (c1_i305 = 0; c1_i305 < 36; c1_i305++) {
          c1_c[c1_i305] = c1_a[c1_i305];
        }

        c1_firstmult = FALSE;
      } else {
        c1_c_eml_scalar_eg(chartInstance);
        c1_c_eml_scalar_eg(chartInstance);
        for (c1_i306 = 0; c1_i306 < 36; c1_i306++) {
          c1_A[c1_i306] = c1_c[c1_i306];
        }

        for (c1_i307 = 0; c1_i307 < 6; c1_i307++) {
          c1_i308 = 0;
          for (c1_i309 = 0; c1_i309 < 6; c1_i309++) {
            c1_c[c1_i308 + c1_i307] = 0.0;
            c1_i310 = 0;
            for (c1_i311 = 0; c1_i311 < 6; c1_i311++) {
              c1_c[c1_i308 + c1_i307] += c1_A[c1_i310 + c1_i307] * c1_a[c1_i311
                + c1_i308];
              c1_i310 += 6;
            }

            c1_i308 += 6;
          }
        }
      }
    }

    if (c1_ed2 == 0.0) {
      exitg1 = 1;
    } else {
      c1_e = c1_ed2;
      c1_c_eml_scalar_eg(chartInstance);
      c1_c_eml_scalar_eg(chartInstance);
      for (c1_i312 = 0; c1_i312 < 36; c1_i312++) {
        c1_A[c1_i312] = c1_a[c1_i312];
      }

      for (c1_i313 = 0; c1_i313 < 6; c1_i313++) {
        c1_i314 = 0;
        for (c1_i315 = 0; c1_i315 < 6; c1_i315++) {
          c1_a[c1_i314 + c1_i313] = 0.0;
          c1_i316 = 0;
          for (c1_i317 = 0; c1_i317 < 6; c1_i317++) {
            c1_a[c1_i314 + c1_i313] += c1_A[c1_i316 + c1_i313] * c1_A[c1_i317 +
              c1_i314];
            c1_i316 += 6;
          }

          c1_i314 += 6;
        }
      }
    }
  } while (exitg1 == 0);
}

static real_T c1_b_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_e_a;
  real_T c1_b;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_e_a = c1_d_a;
  c1_b = c1_d_a;
  return c1_e_a * c1_b;
}

static void c1_c_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a[36], real_T c1_c[36])
{
  int32_T c1_i318;
  real_T c1_b_a[36];
  for (c1_i318 = 0; c1_i318 < 36; c1_i318++) {
    c1_b_a[c1_i318] = c1_a[c1_i318];
  }

  c1_b_matrix_to_integer_power(chartInstance, c1_b_a, c1_c);
}

static void c1_b_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36])
{
  real_T c1_e;
  boolean_T c1_firstmult;
  real_T c1_x;
  real_T c1_ed2;
  real_T c1_b;
  real_T c1_y;
  int32_T c1_i319;
  int32_T c1_i320;
  real_T c1_A[36];
  int32_T c1_i321;
  int32_T c1_i322;
  int32_T c1_i323;
  int32_T c1_i324;
  int32_T c1_i325;
  int32_T c1_i326;
  int32_T c1_i327;
  int32_T c1_i328;
  int32_T c1_i329;
  int32_T c1_i330;
  int32_T c1_i331;
  int32_T exitg1;
  c1_b_eml_scalar_eg(chartInstance);
  c1_e = 3.0;
  c1_firstmult = TRUE;
  do {
    exitg1 = 0;
    c1_x = c1_e / 2.0;
    c1_ed2 = c1_x;
    c1_ed2 = muDoubleScalarFloor(c1_ed2);
    c1_b = c1_ed2;
    c1_y = 2.0 * c1_b;
    if (c1_y != c1_e) {
      if (c1_firstmult) {
        for (c1_i319 = 0; c1_i319 < 36; c1_i319++) {
          c1_c[c1_i319] = c1_a[c1_i319];
        }

        c1_firstmult = FALSE;
      } else {
        c1_c_eml_scalar_eg(chartInstance);
        c1_c_eml_scalar_eg(chartInstance);
        for (c1_i320 = 0; c1_i320 < 36; c1_i320++) {
          c1_A[c1_i320] = c1_c[c1_i320];
        }

        for (c1_i321 = 0; c1_i321 < 6; c1_i321++) {
          c1_i322 = 0;
          for (c1_i323 = 0; c1_i323 < 6; c1_i323++) {
            c1_c[c1_i322 + c1_i321] = 0.0;
            c1_i324 = 0;
            for (c1_i325 = 0; c1_i325 < 6; c1_i325++) {
              c1_c[c1_i322 + c1_i321] += c1_A[c1_i324 + c1_i321] * c1_a[c1_i325
                + c1_i322];
              c1_i324 += 6;
            }

            c1_i322 += 6;
          }
        }
      }
    }

    if (c1_ed2 == 0.0) {
      exitg1 = 1;
    } else {
      c1_e = c1_ed2;
      c1_c_eml_scalar_eg(chartInstance);
      c1_c_eml_scalar_eg(chartInstance);
      for (c1_i326 = 0; c1_i326 < 36; c1_i326++) {
        c1_A[c1_i326] = c1_a[c1_i326];
      }

      for (c1_i327 = 0; c1_i327 < 6; c1_i327++) {
        c1_i328 = 0;
        for (c1_i329 = 0; c1_i329 < 6; c1_i329++) {
          c1_a[c1_i328 + c1_i327] = 0.0;
          c1_i330 = 0;
          for (c1_i331 = 0; c1_i331 < 6; c1_i331++) {
            c1_a[c1_i328 + c1_i327] += c1_A[c1_i330 + c1_i327] * c1_A[c1_i331 +
              c1_i328];
            c1_i330 += 6;
          }

          c1_i328 += 6;
        }
      }
    }
  } while (exitg1 == 0);
}

static real_T c1_d_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_ar;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_ar = c1_d_a;
  return muDoubleScalarPower(c1_ar, 3.0);
}

static void c1_e_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a[36], real_T c1_c[36])
{
  int32_T c1_i332;
  real_T c1_b_a[36];
  for (c1_i332 = 0; c1_i332 < 36; c1_i332++) {
    c1_b_a[c1_i332] = c1_a[c1_i332];
  }

  c1_c_matrix_to_integer_power(chartInstance, c1_b_a, c1_c);
}

static void c1_c_matrix_to_integer_power
  (SFc1_HXpump_controller_sanityInstanceStruct *chartInstance, real_T c1_a[36],
   real_T c1_c[36])
{
  real_T c1_e;
  boolean_T c1_firstmult;
  real_T c1_x;
  real_T c1_ed2;
  real_T c1_b;
  real_T c1_y;
  int32_T c1_i333;
  int32_T c1_i334;
  real_T c1_A[36];
  int32_T c1_i335;
  int32_T c1_i336;
  int32_T c1_i337;
  int32_T c1_i338;
  int32_T c1_i339;
  int32_T c1_i340;
  int32_T c1_i341;
  int32_T c1_i342;
  int32_T c1_i343;
  int32_T c1_i344;
  int32_T c1_i345;
  int32_T exitg1;
  c1_b_eml_scalar_eg(chartInstance);
  c1_e = 4.0;
  c1_firstmult = TRUE;
  do {
    exitg1 = 0;
    c1_x = c1_e / 2.0;
    c1_ed2 = c1_x;
    c1_ed2 = muDoubleScalarFloor(c1_ed2);
    c1_b = c1_ed2;
    c1_y = 2.0 * c1_b;
    if (c1_y != c1_e) {
      if (c1_firstmult) {
        for (c1_i333 = 0; c1_i333 < 36; c1_i333++) {
          c1_c[c1_i333] = c1_a[c1_i333];
        }

        c1_firstmult = FALSE;
      } else {
        c1_c_eml_scalar_eg(chartInstance);
        c1_c_eml_scalar_eg(chartInstance);
        for (c1_i334 = 0; c1_i334 < 36; c1_i334++) {
          c1_A[c1_i334] = c1_c[c1_i334];
        }

        for (c1_i335 = 0; c1_i335 < 6; c1_i335++) {
          c1_i336 = 0;
          for (c1_i337 = 0; c1_i337 < 6; c1_i337++) {
            c1_c[c1_i336 + c1_i335] = 0.0;
            c1_i338 = 0;
            for (c1_i339 = 0; c1_i339 < 6; c1_i339++) {
              c1_c[c1_i336 + c1_i335] += c1_A[c1_i338 + c1_i335] * c1_a[c1_i339
                + c1_i336];
              c1_i338 += 6;
            }

            c1_i336 += 6;
          }
        }
      }
    }

    if (c1_ed2 == 0.0) {
      exitg1 = 1;
    } else {
      c1_e = c1_ed2;
      c1_c_eml_scalar_eg(chartInstance);
      c1_c_eml_scalar_eg(chartInstance);
      for (c1_i340 = 0; c1_i340 < 36; c1_i340++) {
        c1_A[c1_i340] = c1_a[c1_i340];
      }

      for (c1_i341 = 0; c1_i341 < 6; c1_i341++) {
        c1_i342 = 0;
        for (c1_i343 = 0; c1_i343 < 6; c1_i343++) {
          c1_a[c1_i342 + c1_i341] = 0.0;
          c1_i344 = 0;
          for (c1_i345 = 0; c1_i345 < 6; c1_i345++) {
            c1_a[c1_i342 + c1_i341] += c1_A[c1_i344 + c1_i341] * c1_A[c1_i345 +
              c1_i342];
            c1_i344 += 6;
          }

          c1_i342 += 6;
        }
      }
    }
  } while (exitg1 == 0);
}

static real_T c1_f_mpower(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_ak;
  real_T c1_d_a;
  real_T c1_ar;
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_c_a;
  c1_d_a = c1_ak;
  c1_eml_scalar_eg(chartInstance);
  c1_ar = c1_d_a;
  return muDoubleScalarPower(c1_ar, 4.0);
}

static void c1_d_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_e_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_f_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_g_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_h_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_i_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_inv(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                   real_T c1_x[9], real_T c1_y[9])
{
  int32_T c1_i346;
  real_T c1_b_x[9];
  int32_T c1_i347;
  real_T c1_c_x[9];
  real_T c1_n1x;
  int32_T c1_i348;
  real_T c1_b_y[9];
  real_T c1_n1xinv;
  real_T c1_a;
  real_T c1_b;
  real_T c1_c_y;
  real_T c1_rc;
  real_T c1_d_x;
  boolean_T c1_b_b;
  real_T c1_e_x;
  int32_T c1_i349;
  static char_T c1_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c1_u[8];
  const mxArray *c1_d_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_c_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_d_u;
  const mxArray *c1_g_y = NULL;
  char_T c1_str[14];
  int32_T c1_i350;
  char_T c1_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c1_i346 = 0; c1_i346 < 9; c1_i346++) {
    c1_b_x[c1_i346] = c1_x[c1_i346];
  }

  c1_inv3x3(chartInstance, c1_b_x, c1_y);
  for (c1_i347 = 0; c1_i347 < 9; c1_i347++) {
    c1_c_x[c1_i347] = c1_x[c1_i347];
  }

  c1_n1x = c1_norm(chartInstance, c1_c_x);
  for (c1_i348 = 0; c1_i348 < 9; c1_i348++) {
    c1_b_y[c1_i348] = c1_y[c1_i348];
  }

  c1_n1xinv = c1_norm(chartInstance, c1_b_y);
  c1_a = c1_n1x;
  c1_b = c1_n1xinv;
  c1_c_y = c1_a * c1_b;
  c1_rc = 1.0 / c1_c_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c1_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c1_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c1_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c1_d_x = c1_rc;
    c1_b_b = muDoubleScalarIsNaN(c1_d_x);
    guard3 = FALSE;
    if (c1_b_b) {
      guard3 = TRUE;
    } else {
      if (c1_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c1_e_x = c1_rc;
      for (c1_i349 = 0; c1_i349 < 8; c1_i349++) {
        c1_u[c1_i349] = c1_cv0[c1_i349];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c1_b_u = 14.0;
      c1_e_y = NULL;
      sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c1_c_u = 6.0;
      c1_f_y = NULL;
      sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c1_d_u = c1_e_x;
      c1_g_y = NULL;
      sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c1_l_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c1_d_y, 14, c1_e_y, 14,
        c1_f_y), 14, c1_g_y), "sprintf", c1_str);
      for (c1_i350 = 0; c1_i350 < 14; c1_i350++) {
        c1_b_str[c1_i350] = c1_str[c1_i350];
      }

      c1_b_eml_warning(chartInstance, c1_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c1_eml_warning(chartInstance);
  }
}

static void c1_inv3x3(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_x[9], real_T c1_y[9])
{
  int32_T c1_p1;
  int32_T c1_p2;
  int32_T c1_p3;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_absx11;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_absx21;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_absx31;
  real_T c1_t1;
  real_T c1_h_x;
  real_T c1_b_y;
  real_T c1_z;
  real_T c1_i_x;
  real_T c1_c_y;
  real_T c1_b_z;
  real_T c1_a;
  real_T c1_b;
  real_T c1_d_y;
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_e_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_f_y;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_g_y;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_h_y;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_i_y;
  int32_T c1_itmp;
  real_T c1_n_x;
  real_T c1_j_y;
  real_T c1_c_z;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_k_y;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_l_y;
  real_T c1_o_x;
  real_T c1_m_y;
  real_T c1_t3;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_n_y;
  real_T c1_p_x;
  real_T c1_o_y;
  real_T c1_t2;
  int32_T c1_h_a;
  int32_T c1_c;
  real_T c1_i_a;
  real_T c1_h_b;
  real_T c1_p_y;
  real_T c1_j_a;
  real_T c1_i_b;
  real_T c1_q_y;
  real_T c1_q_x;
  real_T c1_r_y;
  real_T c1_d_z;
  int32_T c1_k_a;
  int32_T c1_b_c;
  int32_T c1_l_a;
  int32_T c1_c_c;
  real_T c1_r_x;
  real_T c1_s_y;
  real_T c1_m_a;
  real_T c1_j_b;
  real_T c1_t_y;
  real_T c1_s_x;
  real_T c1_u_y;
  int32_T c1_n_a;
  int32_T c1_d_c;
  real_T c1_o_a;
  real_T c1_k_b;
  real_T c1_v_y;
  real_T c1_p_a;
  real_T c1_l_b;
  real_T c1_w_y;
  real_T c1_t_x;
  real_T c1_x_y;
  real_T c1_e_z;
  int32_T c1_q_a;
  int32_T c1_e_c;
  int32_T c1_r_a;
  int32_T c1_f_c;
  real_T c1_y_y;
  real_T c1_s_a;
  real_T c1_m_b;
  real_T c1_ab_y;
  real_T c1_u_x;
  real_T c1_bb_y;
  int32_T c1_t_a;
  int32_T c1_g_c;
  real_T c1_u_a;
  real_T c1_n_b;
  real_T c1_cb_y;
  real_T c1_v_a;
  real_T c1_o_b;
  real_T c1_db_y;
  real_T c1_v_x;
  real_T c1_eb_y;
  real_T c1_f_z;
  int32_T c1_w_a;
  int32_T c1_h_c;
  int32_T c1_x_a;
  int32_T c1_i_c;
  boolean_T guard1 = FALSE;
  c1_p1 = 0;
  c1_p2 = 3;
  c1_p3 = 6;
  c1_b_x = c1_x[0];
  c1_c_x = c1_b_x;
  c1_absx11 = muDoubleScalarAbs(c1_c_x);
  c1_d_x = c1_x[1];
  c1_e_x = c1_d_x;
  c1_absx21 = muDoubleScalarAbs(c1_e_x);
  c1_f_x = c1_x[2];
  c1_g_x = c1_f_x;
  c1_absx31 = muDoubleScalarAbs(c1_g_x);
  guard1 = FALSE;
  if (c1_absx21 > c1_absx11) {
    if (c1_absx21 > c1_absx31) {
      c1_p1 = 3;
      c1_p2 = 0;
      c1_t1 = c1_x[0];
      c1_x[0] = c1_x[1];
      c1_x[1] = c1_t1;
      c1_t1 = c1_x[3];
      c1_x[3] = c1_x[4];
      c1_x[4] = c1_t1;
      c1_t1 = c1_x[6];
      c1_x[6] = c1_x[7];
      c1_x[7] = c1_t1;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    if (c1_absx31 > c1_absx11) {
      c1_p1 = 6;
      c1_p3 = 0;
      c1_t1 = c1_x[0];
      c1_x[0] = c1_x[2];
      c1_x[2] = c1_t1;
      c1_t1 = c1_x[3];
      c1_x[3] = c1_x[5];
      c1_x[5] = c1_t1;
      c1_t1 = c1_x[6];
      c1_x[6] = c1_x[8];
      c1_x[8] = c1_t1;
    }
  }

  c1_h_x = c1_x[1];
  c1_b_y = c1_x[0];
  c1_z = c1_h_x / c1_b_y;
  c1_x[1] = c1_z;
  c1_i_x = c1_x[2];
  c1_c_y = c1_x[0];
  c1_b_z = c1_i_x / c1_c_y;
  c1_x[2] = c1_b_z;
  c1_a = c1_x[1];
  c1_b = c1_x[3];
  c1_d_y = c1_a * c1_b;
  c1_x[4] -= c1_d_y;
  c1_b_a = c1_x[2];
  c1_b_b = c1_x[3];
  c1_e_y = c1_b_a * c1_b_b;
  c1_x[5] -= c1_e_y;
  c1_c_a = c1_x[1];
  c1_c_b = c1_x[6];
  c1_f_y = c1_c_a * c1_c_b;
  c1_x[7] -= c1_f_y;
  c1_d_a = c1_x[2];
  c1_d_b = c1_x[6];
  c1_g_y = c1_d_a * c1_d_b;
  c1_x[8] -= c1_g_y;
  c1_j_x = c1_x[5];
  c1_k_x = c1_j_x;
  c1_h_y = muDoubleScalarAbs(c1_k_x);
  c1_l_x = c1_x[4];
  c1_m_x = c1_l_x;
  c1_i_y = muDoubleScalarAbs(c1_m_x);
  if (c1_h_y > c1_i_y) {
    c1_itmp = c1_p2;
    c1_p2 = c1_p3;
    c1_p3 = c1_itmp;
    c1_t1 = c1_x[1];
    c1_x[1] = c1_x[2];
    c1_x[2] = c1_t1;
    c1_t1 = c1_x[4];
    c1_x[4] = c1_x[5];
    c1_x[5] = c1_t1;
    c1_t1 = c1_x[7];
    c1_x[7] = c1_x[8];
    c1_x[8] = c1_t1;
  }

  c1_n_x = c1_x[5];
  c1_j_y = c1_x[4];
  c1_c_z = c1_n_x / c1_j_y;
  c1_x[5] = c1_c_z;
  c1_e_a = c1_x[5];
  c1_e_b = c1_x[7];
  c1_k_y = c1_e_a * c1_e_b;
  c1_x[8] -= c1_k_y;
  c1_f_a = c1_x[5];
  c1_f_b = c1_x[1];
  c1_l_y = c1_f_a * c1_f_b;
  c1_o_x = c1_l_y - c1_x[2];
  c1_m_y = c1_x[8];
  c1_t3 = c1_o_x / c1_m_y;
  c1_g_a = c1_x[7];
  c1_g_b = c1_t3;
  c1_n_y = c1_g_a * c1_g_b;
  c1_p_x = -(c1_x[1] + c1_n_y);
  c1_o_y = c1_x[4];
  c1_t2 = c1_p_x / c1_o_y;
  c1_h_a = c1_p1 + 1;
  c1_c = c1_h_a;
  c1_i_a = c1_x[3];
  c1_h_b = c1_t2;
  c1_p_y = c1_i_a * c1_h_b;
  c1_j_a = c1_x[6];
  c1_i_b = c1_t3;
  c1_q_y = c1_j_a * c1_i_b;
  c1_q_x = (1.0 - c1_p_y) - c1_q_y;
  c1_r_y = c1_x[0];
  c1_d_z = c1_q_x / c1_r_y;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_c), 1, 9, 1, 0) - 1] = c1_d_z;
  c1_k_a = c1_p1 + 2;
  c1_b_c = c1_k_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_b_c), 1, 9, 1, 0) - 1] = c1_t2;
  c1_l_a = c1_p1 + 3;
  c1_c_c = c1_l_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_c_c), 1, 9, 1, 0) - 1] = c1_t3;
  c1_r_x = -c1_x[5];
  c1_s_y = c1_x[8];
  c1_t3 = c1_r_x / c1_s_y;
  c1_m_a = c1_x[7];
  c1_j_b = c1_t3;
  c1_t_y = c1_m_a * c1_j_b;
  c1_s_x = 1.0 - c1_t_y;
  c1_u_y = c1_x[4];
  c1_t2 = c1_s_x / c1_u_y;
  c1_n_a = c1_p2 + 1;
  c1_d_c = c1_n_a;
  c1_o_a = c1_x[3];
  c1_k_b = c1_t2;
  c1_v_y = c1_o_a * c1_k_b;
  c1_p_a = c1_x[6];
  c1_l_b = c1_t3;
  c1_w_y = c1_p_a * c1_l_b;
  c1_t_x = -(c1_v_y + c1_w_y);
  c1_x_y = c1_x[0];
  c1_e_z = c1_t_x / c1_x_y;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_d_c), 1, 9, 1, 0) - 1] = c1_e_z;
  c1_q_a = c1_p2 + 2;
  c1_e_c = c1_q_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_e_c), 1, 9, 1, 0) - 1] = c1_t2;
  c1_r_a = c1_p2 + 3;
  c1_f_c = c1_r_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_f_c), 1, 9, 1, 0) - 1] = c1_t3;
  c1_y_y = c1_x[8];
  c1_t3 = 1.0 / c1_y_y;
  c1_s_a = -c1_x[7];
  c1_m_b = c1_t3;
  c1_ab_y = c1_s_a * c1_m_b;
  c1_u_x = c1_ab_y;
  c1_bb_y = c1_x[4];
  c1_t2 = c1_u_x / c1_bb_y;
  c1_t_a = c1_p3 + 1;
  c1_g_c = c1_t_a;
  c1_u_a = c1_x[3];
  c1_n_b = c1_t2;
  c1_cb_y = c1_u_a * c1_n_b;
  c1_v_a = c1_x[6];
  c1_o_b = c1_t3;
  c1_db_y = c1_v_a * c1_o_b;
  c1_v_x = -(c1_cb_y + c1_db_y);
  c1_eb_y = c1_x[0];
  c1_f_z = c1_v_x / c1_eb_y;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_g_c), 1, 9, 1, 0) - 1] = c1_f_z;
  c1_w_a = c1_p3 + 2;
  c1_h_c = c1_w_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_h_c), 1, 9, 1, 0) - 1] = c1_t2;
  c1_x_a = c1_p3 + 3;
  c1_i_c = c1_x_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
    c1_i_c), 1, 9, 1, 0) - 1] = c1_t3;
}

static real_T c1_norm(SFc1_HXpump_controller_sanityInstanceStruct *chartInstance,
                      real_T c1_x[9])
{
  real_T c1_y;
  int32_T c1_j;
  real_T c1_b_j;
  real_T c1_s;
  int32_T c1_i;
  real_T c1_b_i;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_b_y;
  real_T c1_d_x;
  boolean_T c1_b;
  boolean_T exitg1;
  c1_y = 0.0;
  c1_j = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c1_j < 3)) {
    c1_b_j = 1.0 + (real_T)c1_j;
    c1_s = 0.0;
    for (c1_i = 0; c1_i < 3; c1_i++) {
      c1_b_i = 1.0 + (real_T)c1_i;
      c1_b_x = c1_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c1_b_i), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c1_b_j),
        1, 3, 2, 0) - 1)) - 1];
      c1_c_x = c1_b_x;
      c1_b_y = muDoubleScalarAbs(c1_c_x);
      c1_s += c1_b_y;
    }

    c1_d_x = c1_s;
    c1_b = muDoubleScalarIsNaN(c1_d_x);
    if (c1_b) {
      c1_y = rtNaN;
      exitg1 = TRUE;
    } else {
      if (c1_s > c1_y) {
        c1_y = c1_s;
      }

      c1_j++;
    }
  }

  return c1_y;
}

static void c1_eml_warning(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
  int32_T c1_i351;
  static char_T c1_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c1_u[27];
  const mxArray *c1_y = NULL;
  for (c1_i351 = 0; c1_i351 < 27; c1_i351++) {
    c1_u[c1_i351] = c1_varargin_1[c1_i351];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c1_y));
}

static void c1_b_eml_warning(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, char_T c1_varargin_2[14])
{
  int32_T c1_i352;
  static char_T c1_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c1_u[33];
  const mxArray *c1_y = NULL;
  int32_T c1_i353;
  char_T c1_b_u[14];
  const mxArray *c1_b_y = NULL;
  for (c1_i352 = 0; c1_i352 < 33; c1_i352++) {
    c1_u[c1_i352] = c1_varargin_1[c1_i352];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  for (c1_i353 = 0; c1_i353 < 14; c1_i353++) {
    c1_b_u[c1_i353] = c1_varargin_2[c1_i353];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c1_y, 14, c1_b_y));
}

static void c1_j_eml_scalar_eg(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance)
{
}

static void c1_l_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_sprintf, const char_T *c1_identifier, char_T
  c1_y[14])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sprintf), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_sprintf);
}

static void c1_m_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[14])
{
  char_T c1_cv1[14];
  int32_T c1_i354;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c1_i354 = 0; c1_i354 < 14; c1_i354++) {
    c1_y[c1_i354] = c1_cv1[c1_i354];
  }

  sf_mex_destroy(&c1_u);
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_n_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i355;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i355, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i355;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
    chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_o_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_HXpump_controller_sanity,
  const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_HXpump_controller_sanity), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_HXpump_controller_sanity);
  return c1_y;
}

static uint8_T c1_p_emlrt_marshallIn(SFc1_HXpump_controller_sanityInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_HXpump_controller_sanityInstanceStruct
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

void sf_c1_HXpump_controller_sanity_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1073816896U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(195662477U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(789960146U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2152675884U);
}

mxArray *sf_c1_HXpump_controller_sanity_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("UbmcNZde8JynnRQ1IDK8OG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,10,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_HXpump_controller_sanity_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_HXpump_controller_sanity(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[13],T\"Pout\",},{M[1],M[12],T\"xhatout\",},{M[1],M[15],T\"yhatout\",},{M[8],M[0],T\"is_active_c1_HXpump_controller_sanity\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_HXpump_controller_sanity_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
    chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)
      ((ChartInfoStruct *)(ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HXpump_controller_sanityMachineNumber_,
           1,
           1,
           1,
           13,
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
          init_script_number_translation(_HXpump_controller_sanityMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HXpump_controller_sanityMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HXpump_controller_sanityMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"xhatin");
          _SFD_SET_DATA_PROPS(1,1,1,0,"hotpar");
          _SFD_SET_DATA_PROPS(2,1,1,0,"coldpar");
          _SFD_SET_DATA_PROPS(3,1,1,0,"wallpar");
          _SFD_SET_DATA_PROPS(4,1,1,0,"pumppar");
          _SFD_SET_DATA_PROPS(5,1,1,0,"input");
          _SFD_SET_DATA_PROPS(6,1,1,0,"simpar");
          _SFD_SET_DATA_PROPS(7,1,1,0,"y");
          _SFD_SET_DATA_PROPS(8,1,1,0,"noisePSD");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Pin");
          _SFD_SET_DATA_PROPS(10,2,0,1,"xhatout");
          _SFD_SET_DATA_PROPS(11,2,0,1,"yhatout");
          _SFD_SET_DATA_PROPS(12,2,0,1,"Pout");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2340);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"EKFdynamics",0,-1,936);
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
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)
            c1_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T *c1_simpar;
          real_T (*c1_xhatin)[6];
          real_T (*c1_hotpar)[6];
          real_T (*c1_coldpar)[4];
          real_T (*c1_wallpar)[4];
          real_T (*c1_pumppar)[3];
          real_T (*c1_input)[2];
          real_T (*c1_y)[3];
          real_T (*c1_noisePSD)[6];
          real_T (*c1_Pin)[36];
          real_T (*c1_xhatout)[6];
          real_T (*c1_yhatout)[3];
          real_T (*c1_Pout)[36];
          c1_Pout = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 3);
          c1_yhatout = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c1_xhatout = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_Pin = (real_T (*)[36])ssGetInputPortSignal(chartInstance->S, 9);
          c1_noisePSD = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 8);
          c1_y = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 7);
          c1_simpar = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c1_input = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 5);
          c1_pumppar = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c1_wallpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
          c1_coldpar = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 2);
          c1_hotpar = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c1_xhatin = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_xhatin);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_hotpar);
          _SFD_SET_DATA_VALUE_PTR(2U, *c1_coldpar);
          _SFD_SET_DATA_VALUE_PTR(3U, *c1_wallpar);
          _SFD_SET_DATA_VALUE_PTR(4U, *c1_pumppar);
          _SFD_SET_DATA_VALUE_PTR(5U, *c1_input);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_simpar);
          _SFD_SET_DATA_VALUE_PTR(7U, *c1_y);
          _SFD_SET_DATA_VALUE_PTR(8U, *c1_noisePSD);
          _SFD_SET_DATA_VALUE_PTR(9U, *c1_Pin);
          _SFD_SET_DATA_VALUE_PTR(10U, *c1_xhatout);
          _SFD_SET_DATA_VALUE_PTR(11U, *c1_yhatout);
          _SFD_SET_DATA_VALUE_PTR(12U, *c1_Pout);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HXpump_controller_sanityMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "9DVmEpauuz4sbIvPClcDNG";
}

static void sf_opaque_initialize_c1_HXpump_controller_sanity(void
  *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_HXpump_controller_sanityInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
  initialize_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_HXpump_controller_sanity(void *chartInstanceVar)
{
  enable_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_HXpump_controller_sanity(void *chartInstanceVar)
{
  disable_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_HXpump_controller_sanity(void *chartInstanceVar)
{
  sf_c1_HXpump_controller_sanity((SFc1_HXpump_controller_sanityInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_HXpump_controller_sanity
  (SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_HXpump_controller_sanity();/* state var info */
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

extern void sf_internal_set_sim_state_c1_HXpump_controller_sanity(SimStruct* S,
  const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_HXpump_controller_sanity();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*)chartInfo->chartInstance,
     mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_HXpump_controller_sanity
  (SimStruct* S)
{
  return sf_internal_get_sim_state_c1_HXpump_controller_sanity(S);
}

static void sf_opaque_set_sim_state_c1_HXpump_controller_sanity(SimStruct* S,
  const mxArray *st)
{
  sf_internal_set_sim_state_c1_HXpump_controller_sanity(S, st);
}

static void sf_opaque_terminate_c1_HXpump_controller_sanity(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_HXpump_controller_sanityInstanceStruct*)
                    chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HXpump_controller_sanity_optimization_info();
    }

    finalize_c1_HXpump_controller_sanity
      ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_HXpump_controller_sanity
    ((SFc1_HXpump_controller_sanityInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_HXpump_controller_sanity(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_HXpump_controller_sanity
      ((SFc1_HXpump_controller_sanityInstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_HXpump_controller_sanity(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HXpump_controller_sanity_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,10);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 10; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(55689163U));
  ssSetChecksum1(S,(3722229974U));
  ssSetChecksum2(S,(1426419283U));
  ssSetChecksum3(S,(343104247U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_HXpump_controller_sanity(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_HXpump_controller_sanity(SimStruct *S)
{
  SFc1_HXpump_controller_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc1_HXpump_controller_sanityInstanceStruct *)utMalloc(sizeof
    (SFc1_HXpump_controller_sanityInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_HXpump_controller_sanityInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_HXpump_controller_sanity;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_HXpump_controller_sanity;
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

void c1_HXpump_controller_sanity_method_dispatcher(SimStruct *S, int_T method,
  void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_HXpump_controller_sanity(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_HXpump_controller_sanity(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_HXpump_controller_sanity(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_HXpump_controller_sanity_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
