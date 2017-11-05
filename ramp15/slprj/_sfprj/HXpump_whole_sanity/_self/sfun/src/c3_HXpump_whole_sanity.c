/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HXpump_whole_sanity_sfun.h"
#include "c3_HXpump_whole_sanity.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HXpump_whole_sanity_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[17] = { "iterations", "filename",
  "text", "result", "line_num", "resultz", "sensor_value_tmp",
  "network_delay_tmp", "nargin", "nargout", "actual_value", "actual_value1",
  "ysensor_value", "ynetwork_delay", "sensor_value", "i", "network_array" };

static const char * c3_b_debug_family_names[7] = { "result_num", "sz_y", "i_rn",
  "nargin", "nargout", "result", "value" };

static const char * c3_c_debug_family_names[7] = { "result_num", "sz_y", "i_rn",
  "nargin", "nargout", "result", "delay" };

/* Function Declarations */
static void initialize_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void initialize_params_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void enable_c3_HXpump_whole_sanity(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance);
static void disable_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void set_sim_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance, const mxArray *c3_st);
static void finalize_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void sf_gateway_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void c3_chartstep_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void initSimStructsc3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static boolean_T c3_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_ischar, const char_T *c3_identifier);
static boolean_T c3_b_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_str2num, const char_T *c3_identifier, real_T
  c3_y[6]);
static void c3_d_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[6]);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_e_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_network_array, const char_T *c3_identifier,
  real_T c3_y[18006]);
static void c3_f_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[18006]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_g_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_i, const char_T *c3_identifier);
static real_T c3_h_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_sensor_value, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_j_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_k_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_ynetwork_delay, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_l_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_m_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_n_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_o_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[6]);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_p_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  char_T c3_y[26]);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(const mxArray **c3_info);
static const mxArray *c3_emlrt_marshallOut(const char * c3_u);
static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_u);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_q_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_r_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_HXpump_whole_sanity, const
  char_T *c3_identifier);
static uint8_T c3_s_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_sensor_value_not_empty = false;
  chartInstance->c3_i_not_empty = false;
  chartInstance->c3_network_array_not_empty = false;
  chartInstance->c3_is_active_c3_HXpump_whole_sanity = 0U;
}

static void initialize_params_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_HXpump_whole_sanity(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[3];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i1;
  real_T c3_b_u[3];
  const mxArray *c3_c_y = NULL;
  int32_T c3_i2;
  real_T c3_c_u[3];
  const mxArray *c3_d_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  int32_T c3_i3;
  real_T c3_e_u[18006];
  const mxArray *c3_f_y = NULL;
  int32_T c3_i4;
  real_T c3_f_u[3];
  const mxArray *c3_g_y = NULL;
  uint8_T c3_b_hoistedGlobal;
  uint8_T c3_g_u;
  const mxArray *c3_h_y = NULL;
  real_T (*c3_ysensor_value)[3];
  real_T (*c3_ynetwork_delay)[3];
  real_T (*c3_actual_value1)[3];
  c3_ynetwork_delay = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_ysensor_value = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_actual_value1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(7, 1), false);
  for (c3_i0 = 0; c3_i0 < 3; c3_i0++) {
    c3_u[c3_i0] = (*c3_actual_value1)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 3; c3_i1++) {
    c3_b_u[c3_i1] = (*c3_ynetwork_delay)[c3_i1];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  for (c3_i2 = 0; c3_i2 < 3; c3_i2++) {
    c3_c_u[c3_i2] = (*c3_ysensor_value)[c3_i2];
  }

  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_hoistedGlobal = chartInstance->c3_i;
  c3_d_u = c3_hoistedGlobal;
  c3_e_y = NULL;
  if (!chartInstance->c3_i_not_empty) {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c3_y, 3, c3_e_y);
  for (c3_i3 = 0; c3_i3 < 18006; c3_i3++) {
    c3_e_u[c3_i3] = chartInstance->c3_network_array[c3_i3];
  }

  c3_f_y = NULL;
  if (!chartInstance->c3_network_array_not_empty) {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 3001, 6),
                  false);
  }

  sf_mex_setcell(c3_y, 4, c3_f_y);
  for (c3_i4 = 0; c3_i4 < 3; c3_i4++) {
    c3_f_u[c3_i4] = chartInstance->c3_sensor_value[c3_i4];
  }

  c3_g_y = NULL;
  if (!chartInstance->c3_sensor_value_not_empty) {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 1, 3),
                  false);
  }

  sf_mex_setcell(c3_y, 5, c3_g_y);
  c3_b_hoistedGlobal = chartInstance->c3_is_active_c3_HXpump_whole_sanity;
  c3_g_u = c3_b_hoistedGlobal;
  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", &c3_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 6, c3_h_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[3];
  int32_T c3_i5;
  real_T c3_dv1[3];
  int32_T c3_i6;
  real_T c3_dv2[3];
  int32_T c3_i7;
  static real_T c3_dv3[18006];
  int32_T c3_i8;
  real_T c3_dv4[3];
  int32_T c3_i9;
  real_T (*c3_actual_value1)[3];
  real_T (*c3_ynetwork_delay)[3];
  real_T (*c3_ysensor_value)[3];
  c3_ynetwork_delay = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_ysensor_value = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_actual_value1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                        "actual_value1", c3_dv0);
  for (c3_i5 = 0; c3_i5 < 3; c3_i5++) {
    (*c3_actual_value1)[c3_i5] = c3_dv0[c3_i5];
  }

  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "ynetwork_delay", c3_dv1);
  for (c3_i6 = 0; c3_i6 < 3; c3_i6++) {
    (*c3_ynetwork_delay)[c3_i6] = c3_dv1[c3_i6];
  }

  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
                        "ysensor_value", c3_dv2);
  for (c3_i7 = 0; c3_i7 < 3; c3_i7++) {
    (*c3_ysensor_value)[c3_i7] = c3_dv2[c3_i7];
  }

  chartInstance->c3_i = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 3)), "i");
  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
                        "network_array", c3_dv3);
  for (c3_i8 = 0; c3_i8 < 18006; c3_i8++) {
    chartInstance->c3_network_array[c3_i8] = c3_dv3[c3_i8];
  }

  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 5)),
                        "sensor_value", c3_dv4);
  for (c3_i9 = 0; c3_i9 < 3; c3_i9++) {
    chartInstance->c3_sensor_value[c3_i9] = c3_dv4[c3_i9];
  }

  chartInstance->c3_is_active_c3_HXpump_whole_sanity = c3_r_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 6)),
     "is_active_c3_HXpump_whole_sanity");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_HXpump_whole_sanity(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  real_T (*c3_ynetwork_delay)[3];
  real_T (*c3_ysensor_value)[3];
  real_T (*c3_actual_value1)[3];
  real_T (*c3_actual_value)[3];
  c3_ynetwork_delay = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_ysensor_value = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_actual_value1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_actual_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i10 = 0; c3_i10 < 3; c3_i10++) {
    _SFD_DATA_RANGE_CHECK((*c3_actual_value)[c3_i10], 0U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_HXpump_whole_sanity(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HXpump_whole_sanityMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c3_i11 = 0; c3_i11 < 3; c3_i11++) {
    _SFD_DATA_RANGE_CHECK((*c3_actual_value1)[c3_i11], 1U);
  }

  for (c3_i12 = 0; c3_i12 < 3; c3_i12++) {
    _SFD_DATA_RANGE_CHECK((*c3_ysensor_value)[c3_i12], 2U);
  }

  for (c3_i13 = 0; c3_i13 < 3; c3_i13++) {
    _SFD_DATA_RANGE_CHECK((*c3_ynetwork_delay)[c3_i13], 3U);
  }
}

static void c3_chartstep_c3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  int32_T c3_i14;
  real_T c3_actual_value[3];
  uint32_T c3_debug_family_var_map[17];
  real_T c3_iterations;
  char_T c3_filename[26];
  const mxArray *c3_text = NULL;
  const mxArray *c3_result = NULL;
  real_T c3_line_num;
  real_T c3_resultz[6];
  real_T c3_sensor_value_tmp[3];
  real_T c3_network_delay_tmp[3];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 3.0;
  real_T c3_actual_value1[3];
  real_T c3_ysensor_value[3];
  real_T c3_ynetwork_delay[3];
  int32_T c3_i15;
  int32_T c3_i16;
  static char_T c3_cv0[26] = { 'n', 'o', 'n', 'c', 'l', '_', 'r', 'a', 'n', 'd',
    'o', 'm', 'F', 'I', '0', '.', '7', '_', 'd', 'e', 'l', 'a', 'y', '0', '.',
    '5' };

  int32_T c3_i17;
  char_T c3_u[26];
  const mxArray *c3_y = NULL;
  real_T c3_dv5[6];
  int32_T c3_b_line_num;
  int32_T c3_i18;
  int32_T c3_i19;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  real_T c3_b_result[6];
  uint32_T c3_b_debug_family_var_map[7];
  real_T c3_result_num[6];
  real_T c3_sz_y;
  real_T c3_i_rn;
  real_T c3_b_nargin = 1.0;
  real_T c3_b_nargout = 1.0;
  int32_T c3_i24;
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_b_i_rn;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  real_T c3_c_result[6];
  real_T c3_b_result_num[6];
  real_T c3_b_sz_y;
  real_T c3_c_i_rn;
  real_T c3_c_nargin = 1.0;
  real_T c3_c_nargout = 1.0;
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_i32;
  int32_T c3_d_i_rn;
  int32_T c3_i33;
  int32_T c3_i34;
  static char_T c3_cv1[12] = { 's', 'e', 'n', 's', 'o', 'r', '_', 'v', 'a', 'l',
    'u', 'e' };

  char_T c3_b_u[12];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i35;
  real_T c3_c_u[3];
  const mxArray *c3_c_y = NULL;
  int32_T c3_i36;
  static char_T c3_cv2[25] = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',
    '-', '-', 'i', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };

  char_T c3_d_u[25];
  const mxArray *c3_d_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_e_u;
  const mxArray *c3_e_y = NULL;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  int32_T c3_i40;
  static char_T c3_cv3[39] = { 'P', 'l', 'a', 'n', 't', ' ', '1', ',', ' ', 'T',
    'O', 'S', 'S', 'I', 'M', ' ', 'U', 'p', 'l', 'i', 'n', 'k', ' ', 'B', 'l',
    'o', 'c', 'k', ',', ' ', 'i', 's', ' ', 'c', 'a', 'l', 'l', 'e', 'd' };

  char_T c3_f_u[39];
  const mxArray *c3_f_y = NULL;
  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  real_T (*c3_b_actual_value1)[3];
  real_T (*c3_b_ysensor_value)[3];
  real_T (*c3_b_ynetwork_delay)[3];
  real_T (*c3_b_actual_value)[3];
  boolean_T exitg1;
  c3_b_ynetwork_delay = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_ysensor_value = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_actual_value1 = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_actual_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i14 = 0; c3_i14 < 3; c3_i14++) {
    c3_actual_value[c3_i14] = (*c3_b_actual_value)[c3_i14];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_iterations, 0U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_filename, 1U, c3_i_sf_marshallOut,
    c3_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_text, 2U, c3_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_result, 3U, c3_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_line_num, 4U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_resultz, 5U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_sensor_value_tmp, 6U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_network_delay_tmp, 7U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 8U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 9U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_actual_value, 10U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_actual_value1, 11U,
    c3_d_sf_marshallOut, c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_ysensor_value, 12U,
    c3_d_sf_marshallOut, c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_ynetwork_delay, 13U,
    c3_d_sf_marshallOut, c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_sensor_value, 14U,
    c3_c_sf_marshallOut, c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_i, 15U,
    c3_b_sf_marshallOut, c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_network_array, 16U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  c3_iterations = 3001.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 20);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 21);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 22);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 23);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 24);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 26);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 27);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 30);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c3_i_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
    chartInstance->c3_i = 0.0;
    chartInstance->c3_i_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 36);
    for (c3_i15 = 0; c3_i15 < 18006; c3_i15++) {
      chartInstance->c3_network_array[c3_i15] = 0.0;
    }

    chartInstance->c3_network_array_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 43);
    for (c3_i16 = 0; c3_i16 < 26; c3_i16++) {
      c3_filename[c3_i16] = c3_cv0[c3_i16];
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 47);
    for (c3_i17 = 0; c3_i17 < 26; c3_i17++) {
      c3_u[c3_i17] = c3_filename[c3_i17];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 26),
                  false);
    sf_mex_assign(&c3_text, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
      "fopen", 1U, 1U, 14, c3_y), false);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 48);
    sf_mex_assign(&c3_result, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
      "fgets", 1U, 1U, 14, sf_mex_dup(c3_text)), false);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 51);
    c3_line_num = 1.0;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
    exitg1 = false;
    while ((exitg1 == false) && CV_EML_WHILE(0, 1, 0, c3_emlrt_marshallIn
            (chartInstance, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
              "ischar", 1U, 1U, 14, sf_mex_dup(c3_result)), "ischar"))) {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 53);
      if (CV_EML_IF(0, 1, 1, c3_line_num <= c3_iterations)) {
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 54);
        c3_c_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                              (sfGlobalDebugInstanceStruct, "str2num", 1U, 1U,
          14, sf_mex_dup(c3_result)), "str2num", c3_dv5);
        c3_b_line_num = _SFD_EML_ARRAY_BOUNDS_CHECK("network_array", (int32_T)
          _SFD_INTEGER_CHECK("line_num", c3_line_num), 1, 3001, 1, 0) - 1;
        for (c3_i18 = 0; c3_i18 < 6; c3_i18++) {
          chartInstance->c3_network_array[c3_b_line_num + 3001 * c3_i18] =
            c3_dv5[c3_i18];
        }

        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 55);
        sf_mex_assign(&c3_result, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
          "fgets", 1U, 1U, 14, sf_mex_dup(c3_text)), false);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 60);
        c3_line_num++;
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 57);
        exitg1 = true;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 63);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "fclose", 0U, 1U, 14,
                      sf_mex_dup(c3_text));
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 69);
  for (c3_i19 = 0; c3_i19 < 3; c3_i19++) {
    c3_ysensor_value[c3_i19] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 70);
  for (c3_i20 = 0; c3_i20 < 3; c3_i20++) {
    c3_ynetwork_delay[c3_i20] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 77);
  chartInstance->c3_i++;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 79);
  c3_i21 = _SFD_EML_ARRAY_BOUNDS_CHECK("network_array", (int32_T)
    _SFD_INTEGER_CHECK("i", chartInstance->c3_i), 1, 3001, 1, 0) - 1;
  for (c3_i22 = 0; c3_i22 < 6; c3_i22++) {
    c3_resultz[c3_i22] = chartInstance->c3_network_array[c3_i21 + 3001 * c3_i22];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 84);
  for (c3_i23 = 0; c3_i23 < 6; c3_i23++) {
    c3_b_result[c3_i23] = c3_resultz[c3_i23];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c3_b_debug_family_names,
    c3_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_result_num, 0U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_sz_y, 1U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i_rn, 2U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 3U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 4U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_result, 5U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_sensor_value_tmp, 6U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 5);
  CV_SCRIPT_COND(0, 0, false);
  CV_SCRIPT_MCDC(0, 0, true);
  CV_SCRIPT_IF(0, 0, true);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 6);
  for (c3_i24 = 0; c3_i24 < 6; c3_i24++) {
    c3_result_num[c3_i24] = 0.0;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 7);
  for (c3_i25 = 0; c3_i25 < 6; c3_i25++) {
    c3_result_num[c3_i25] = c3_b_result[c3_i25];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 8);
  c3_sz_y = 3.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 10);
  for (c3_i26 = 0; c3_i26 < 3; c3_i26++) {
    c3_sensor_value_tmp[c3_i26] = 88.0;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 11);
  c3_i_rn = 1.0;
  c3_b_i_rn = 0;
  while (c3_b_i_rn < 3) {
    c3_i_rn = 1.0 + (real_T)c3_b_i_rn;
    CV_SCRIPT_FOR(0, 0, 1);
    _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 12);
    if (CV_SCRIPT_IF(0, 1, c3_result_num[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "result_num", (int32_T)_SFD_INTEGER_CHECK("i_rn", c3_i_rn), 1, 6, 1, 0)
                     - 1] >= 1.0)) {
      _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 13);
      c3_sensor_value_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("value", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_i_rn), 1, 3, 2, 0) - 1] = 1.0;
    } else {
      _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, 15);
      c3_sensor_value_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("value", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_i_rn), 1, 3, 2, 0) - 1] =
        c3_sensor_value_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("value", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_i_rn), 1, 3, 2, 0) - 1];
    }

    c3_b_i_rn++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_SCRIPT_FOR(0, 0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c3_sfEvent, -19);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 85);
  if (CV_EML_IF(0, 1, 2, chartInstance->c3_i == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 86);
    for (c3_i27 = 0; c3_i27 < 3; c3_i27++) {
      c3_sensor_value_tmp[c3_i27] = 1.0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 88);
  for (c3_i28 = 0; c3_i28 < 3; c3_i28++) {
    c3_ysensor_value[c3_i28] = c3_sensor_value_tmp[c3_i28];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 90);
  for (c3_i29 = 0; c3_i29 < 6; c3_i29++) {
    c3_c_result[c3_i29] = c3_resultz[c3_i29];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c3_c_debug_family_names,
    c3_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_result_num, 0U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_b_sz_y, 1U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_i_rn, 2U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargin, 3U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargout, 4U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_c_result, 5U, c3_g_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_network_delay_tmp, 6U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 4);
  CV_SCRIPT_COND(1, 0, false);
  CV_SCRIPT_MCDC(1, 0, true);
  CV_SCRIPT_IF(1, 0, true);
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 5);
  for (c3_i30 = 0; c3_i30 < 6; c3_i30++) {
    c3_b_result_num[c3_i30] = 0.0;
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 6);
  for (c3_i31 = 0; c3_i31 < 6; c3_i31++) {
    c3_b_result_num[c3_i31] = c3_c_result[c3_i31];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 7);
  c3_b_sz_y = 3.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 9);
  for (c3_i32 = 0; c3_i32 < 3; c3_i32++) {
    c3_network_delay_tmp[c3_i32] = 0.0;
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 10);
  c3_c_i_rn = 1.0;
  c3_d_i_rn = 0;
  while (c3_d_i_rn < 3) {
    c3_c_i_rn = 1.0 + (real_T)c3_d_i_rn;
    CV_SCRIPT_FOR(1, 0, 1);
    _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 13);
    if (CV_SCRIPT_IF(1, 1, c3_b_result_num[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "result_num", (int32_T)_SFD_INTEGER_CHECK("3+i_rn", 3.0 + c3_c_i_rn),
          1, 6, 1, 0) - 1] > 0.0)) {
      _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 14);
      c3_network_delay_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("delay", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_c_i_rn), 1, 3, 2, 0) - 1] =
        c3_b_result_num[_SFD_EML_ARRAY_BOUNDS_CHECK("result_num", (int32_T)
        _SFD_INTEGER_CHECK("3+i_rn", 3.0 + c3_c_i_rn), 1, 6, 1, 0) - 1];
    } else {
      _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, 16);
      c3_network_delay_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("delay", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_c_i_rn), 1, 3, 2, 0) - 1] =
        c3_network_delay_tmp[_SFD_EML_ARRAY_BOUNDS_CHECK("delay", (int32_T)
        _SFD_INTEGER_CHECK("i_rn", c3_c_i_rn), 1, 3, 2, 0) - 1];
    }

    c3_d_i_rn++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_SCRIPT_FOR(1, 0, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c3_sfEvent, -20);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 92);
  for (c3_i33 = 0; c3_i33 < 3; c3_i33++) {
    c3_ynetwork_delay[c3_i33] = c3_network_delay_tmp[c3_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 94);
  for (c3_i34 = 0; c3_i34 < 12; c3_i34++) {
    c3_b_u[c3_i34] = c3_cv1[c3_i34];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 12),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_b_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 95);
  for (c3_i35 = 0; c3_i35 < 3; c3_i35++) {
    c3_c_u[c3_i35] = c3_ysensor_value[c3_i35];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 2, 1, 3),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_c_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 98);
  for (c3_i36 = 0; c3_i36 < 25; c3_i36++) {
    c3_d_u[c3_i36] = c3_cv2[c3_i36];
  }

  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_d_u, 10, 0U, 1U, 0U, 2, 1, 25),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_d_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 99);
  c3_hoistedGlobal = chartInstance->c3_i;
  c3_e_u = c3_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_e_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 102);
  for (c3_i37 = 0; c3_i37 < 3; c3_i37++) {
    chartInstance->c3_sensor_value[c3_i37] = c3_ysensor_value[c3_i37];
  }

  chartInstance->c3_sensor_value_not_empty = true;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 105);
  for (c3_i38 = 0; c3_i38 < 3; c3_i38++) {
    c3_actual_value1[c3_i38] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 106);
  for (c3_i39 = 0; c3_i39 < 3; c3_i39++) {
    c3_actual_value1[c3_i39] = c3_actual_value[c3_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 113);
  for (c3_i40 = 0; c3_i40 < 39; c3_i40++) {
    c3_f_u[c3_i40] = c3_cv3[c3_i40];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_f_u, 10, 0U, 1U, 0U, 2, 1, 39),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_f_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -113);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c3_text);
  sf_mex_destroy(&c3_result);
  for (c3_i41 = 0; c3_i41 < 3; c3_i41++) {
    (*c3_b_actual_value1)[c3_i41] = c3_actual_value1[c3_i41];
  }

  for (c3_i42 = 0; c3_i42 < 3; c3_i42++) {
    (*c3_b_ysensor_value)[c3_i42] = c3_ysensor_value[c3_i42];
  }

  for (c3_i43 = 0; c3_i43 < 3; c3_i43++) {
    (*c3_b_ynetwork_delay)[c3_i43] = c3_ynetwork_delay[c3_i43];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_HXpump_whole_sanity
  (SFc3_HXpump_whole_sanityInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, c3_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/Users/wangwenchen/Downloads/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/value_summary.m"));
  _SFD_SCRIPT_TRANSLATION(c3_chartNumber, c3_instanceNumber, 1U,
    sf_debug_get_script_id(
    "/Users/wangwenchen/Downloads/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/network_delay_summary.m"));
}

static boolean_T c3_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_ischar, const char_T *c3_identifier)
{
  boolean_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ischar), &c3_thisId);
  sf_mex_destroy(&c3_ischar);
  return c3_y;
}

static boolean_T c3_b_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_str2num, const char_T *c3_identifier, real_T
  c3_y[6])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_str2num), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_str2num);
}

static void c3_d_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[6])
{
  real_T c3_dv6[6];
  int32_T c3_i44;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv6, 0, 0, 0U, 1, 0U, 2, 1, 6);
  for (c3_i44 = 0; c3_i44 < 6; c3_i44++) {
    c3_y[c3_i44] = c3_dv6[c3_i44];
  }

  sf_mex_destroy(&c3_u);
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  static real_T c3_b_inData[18006];
  int32_T c3_i48;
  int32_T c3_i49;
  int32_T c3_i50;
  real_T c3_u[18006];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i45 = 0;
  for (c3_i46 = 0; c3_i46 < 6; c3_i46++) {
    for (c3_i47 = 0; c3_i47 < 3001; c3_i47++) {
      c3_b_inData[c3_i47 + c3_i45] = (*(real_T (*)[18006])c3_inData)[c3_i47 +
        c3_i45];
    }

    c3_i45 += 3001;
  }

  c3_i48 = 0;
  for (c3_i49 = 0; c3_i49 < 6; c3_i49++) {
    for (c3_i50 = 0; c3_i50 < 3001; c3_i50++) {
      c3_u[c3_i50 + c3_i48] = c3_b_inData[c3_i50 + c3_i48];
    }

    c3_i48 += 3001;
  }

  c3_y = NULL;
  if (!chartInstance->c3_network_array_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3001, 6),
                  false);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_e_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_network_array, const char_T *c3_identifier,
  real_T c3_y[18006])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_network_array),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_network_array);
}

static void c3_f_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[18006])
{
  real_T c3_dv7[18006];
  int32_T c3_i51;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_network_array_not_empty = false;
  } else {
    chartInstance->c3_network_array_not_empty = true;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv7, 1, 0, 0U, 1, 0U, 2,
                  3001, 6);
    for (c3_i51 = 0; c3_i51 < 18006; c3_i51++) {
      c3_y[c3_i51] = c3_dv7[c3_i51];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_network_array;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  static real_T c3_y[18006];
  int32_T c3_i52;
  int32_T c3_i53;
  int32_T c3_i54;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_b_network_array = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_network_array),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_network_array);
  c3_i52 = 0;
  for (c3_i53 = 0; c3_i53 < 6; c3_i53++) {
    for (c3_i54 = 0; c3_i54 < 3001; c3_i54++) {
      (*(real_T (*)[18006])c3_outData)[c3_i54 + c3_i52] = c3_y[c3_i54 + c3_i52];
    }

    c3_i52 += 3001;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_i_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_g_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_i, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_i), &c3_thisId);
  sf_mex_destroy(&c3_b_i);
  return c3_y;
}

static real_T c3_h_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_i_not_empty = false;
  } else {
    chartInstance->c3_i_not_empty = true;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d0;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_i;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_b_i = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_i), &c3_thisId);
  sf_mex_destroy(&c3_b_i);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i55;
  real_T c3_b_inData[3];
  int32_T c3_i56;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i55 = 0; c3_i55 < 3; c3_i55++) {
    c3_b_inData[c3_i55] = (*(real_T (*)[3])c3_inData)[c3_i55];
  }

  for (c3_i56 = 0; c3_i56 < 3; c3_i56++) {
    c3_u[c3_i56] = c3_b_inData[c3_i56];
  }

  c3_y = NULL;
  if (!chartInstance->c3_sensor_value_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_i_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_sensor_value, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sensor_value), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_sensor_value);
}

static void c3_j_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv8[3];
  int32_T c3_i57;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_sensor_value_not_empty = false;
  } else {
    chartInstance->c3_sensor_value_not_empty = true;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv8, 1, 0, 0U, 1, 0U, 1, 3);
    for (c3_i57 = 0; c3_i57 < 3; c3_i57++) {
      c3_y[c3_i57] = c3_dv8[c3_i57];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sensor_value;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i58;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_b_sensor_value = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sensor_value), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_sensor_value);
  for (c3_i58 = 0; c3_i58 < 3; c3_i58++) {
    (*(real_T (*)[3])c3_outData)[c3_i58] = c3_y[c3_i58];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i59;
  real_T c3_b_inData[3];
  int32_T c3_i60;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i59 = 0; c3_i59 < 3; c3_i59++) {
    c3_b_inData[c3_i59] = (*(real_T (*)[3])c3_inData)[c3_i59];
  }

  for (c3_i60 = 0; c3_i60 < 3; c3_i60++) {
    c3_u[c3_i60] = c3_b_inData[c3_i60];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_k_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_ynetwork_delay, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ynetwork_delay), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_ynetwork_delay);
}

static void c3_l_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv9[3];
  int32_T c3_i61;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv9, 1, 0, 0U, 1, 0U, 1, 3);
  for (c3_i61 = 0; c3_i61 < 3; c3_i61++) {
    c3_y[c3_i61] = c3_dv9[c3_i61];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_ynetwork_delay;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i62;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_ynetwork_delay = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_ynetwork_delay), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_ynetwork_delay);
  for (c3_i62 = 0; c3_i62 < 3; c3_i62++) {
    (*(real_T (*)[3])c3_outData)[c3_i62] = c3_y[c3_i62];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_m_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d1;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d1, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i63;
  real_T c3_b_inData[3];
  int32_T c3_i64;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i63 = 0; c3_i63 < 3; c3_i63++) {
    c3_b_inData[c3_i63] = (*(real_T (*)[3])c3_inData)[c3_i63];
  }

  for (c3_i64 = 0; c3_i64 < 3; c3_i64++) {
    c3_u[c3_i64] = c3_b_inData[c3_i64];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_n_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv10[3];
  int32_T c3_i65;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv10, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c3_i65 = 0; c3_i65 < 3; c3_i65++) {
    c3_y[c3_i65] = c3_dv10[c3_i65];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_network_delay_tmp;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i66;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_network_delay_tmp = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_network_delay_tmp),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_network_delay_tmp);
  for (c3_i66 = 0; c3_i66 < 3; c3_i66++) {
    (*(real_T (*)[3])c3_outData)[c3_i66] = c3_y[c3_i66];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i67;
  real_T c3_b_inData[6];
  int32_T c3_i68;
  real_T c3_u[6];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i67 = 0; c3_i67 < 6; c3_i67++) {
    c3_b_inData[c3_i67] = (*(real_T (*)[6])c3_inData)[c3_i67];
  }

  for (c3_i68 = 0; c3_i68 < 6; c3_i68++) {
    c3_u[c3_i68] = c3_b_inData[c3_i68];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 6), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_o_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[6])
{
  real_T c3_dv11[6];
  int32_T c3_i69;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv11, 1, 0, 0U, 1, 0U, 2, 1, 6);
  for (c3_i69 = 0; c3_i69 < 6; c3_i69++) {
    c3_y[c3_i69] = c3_dv11[c3_i69];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_resultz;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[6];
  int32_T c3_i70;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_resultz = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_resultz), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_resultz);
  for (c3_i70 = 0; c3_i70 < 6; c3_i70++) {
    (*(real_T (*)[6])c3_outData)[c3_i70] = c3_y[c3_i70];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  const mxArray *c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = sf_mex_dup(*(const mxArray **)c3_inData);
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_duplicatearraysafe(&c3_u), false);
  sf_mex_destroy(&c3_u);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i71;
  char_T c3_b_inData[26];
  int32_T c3_i72;
  char_T c3_u[26];
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i71 = 0; c3_i71 < 26; c3_i71++) {
    c3_b_inData[c3_i71] = (*(char_T (*)[26])c3_inData)[c3_i71];
  }

  for (c3_i72 = 0; c3_i72 < 26; c3_i72++) {
    c3_u[c3_i72] = c3_b_inData[c3_i72];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 26), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_p_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  char_T c3_y[26])
{
  char_T c3_cv4[26];
  int32_T c3_i73;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_cv4, 1, 10, 0U, 1, 0U, 2, 1,
                26);
  for (c3_i73 = 0; c3_i73 < 26; c3_i73++) {
    c3_y[c3_i73] = c3_cv4[c3_i73];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_filename;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  char_T c3_y[26];
  int32_T c3_i74;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_filename = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_filename), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_filename);
  for (c3_i74 = 0; c3_i74 < 26; c3_i74++) {
    (*(char_T (*)[26])c3_outData)[c3_i74] = c3_y[c3_i74];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_HXpump_whole_sanity_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_createstruct("structure", 2, 3, 1),
                false);
  c3_info_helper(&c3_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(const mxArray **c3_info)
{
  const mxArray *c3_rhs0 = NULL;
  const mxArray *c3_lhs0 = NULL;
  const mxArray *c3_rhs1 = NULL;
  const mxArray *c3_lhs1 = NULL;
  const mxArray *c3_rhs2 = NULL;
  const mxArray *c3_lhs2 = NULL;
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("fclose"), "name", "name", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("mxArray"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/iofun/fclose.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1381871900U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c3_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("value_summary"), "name",
                  "name", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[E]/Users/wangwenchen/Downloads/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/value_summary.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1469211010U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c3_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("network_delay_summary"),
                  "name", "name", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[E]/Users/wangwenchen/Downloads/heat exchanger pump July 18 2016/heat exchanger pump July 18 2016/network_delay_summary.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1469211002U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c3_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs2), "lhs", "lhs", 2);
  sf_mex_destroy(&c3_rhs0);
  sf_mex_destroy(&c3_lhs0);
  sf_mex_destroy(&c3_rhs1);
  sf_mex_destroy(&c3_lhs1);
  sf_mex_destroy(&c3_rhs2);
  sf_mex_destroy(&c3_lhs2);
}

static const mxArray *c3_emlrt_marshallOut(const char * c3_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c3_u)), false);
  return c3_y;
}

static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 7, 0U, 0U, 0U, 0), false);
  return c3_y;
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_q_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i75;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i75, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i75;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_r_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_HXpump_whole_sanity, const
  char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_HXpump_whole_sanity), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_HXpump_whole_sanity);
  return c3_y;
}

static uint8_T c3_s_emlrt_marshallIn(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_HXpump_whole_sanityInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
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

void sf_c3_HXpump_whole_sanity_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3465552351U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2864833098U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3801421329U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2761200963U);
}

mxArray *sf_c3_HXpump_whole_sanity_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2S8XzcofAivevym2ja0rSB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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
      pr[0] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_HXpump_whole_sanity_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_HXpump_whole_sanity_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c3_HXpump_whole_sanity(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[5],T\"actual_value1\",},{M[1],M[7],T\"ynetwork_delay\",},{M[1],M[6],T\"ysensor_value\",},{M[4],M[0],T\"i\",S'l','i','p'{{M1x2[245 246],M[0],}}},{M[4],M[0],T\"network_array\",S'l','i','p'{{M1x2[260 273],M[0],}}},{M[4],M[0],T\"sensor_value\",S'l','i','p'{{M1x2[207 219],M[0],}}},{M[8],M[0],T\"is_active_c3_HXpump_whole_sanity\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_HXpump_whole_sanity_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HXpump_whole_sanityMachineNumber_,
           3,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           2,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_HXpump_whole_sanityMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HXpump_whole_sanityMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HXpump_whole_sanityMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"actual_value");
          _SFD_SET_DATA_PROPS(1,2,0,1,"actual_value1");
          _SFD_SET_DATA_PROPS(2,2,0,1,"ysensor_value");
          _SFD_SET_DATA_PROPS(3,2,0,1,"ynetwork_delay");
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
        _SFD_CV_INIT_EML(0,1,1,3,0,0,0,0,1,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2604);
        _SFD_CV_INIT_EML_IF(0,1,0,700,713,-1,1544);
        _SFD_CV_INIT_EML_IF(0,1,1,1293,1319,1420,1455);
        _SFD_CV_INIT_EML_IF(0,1,2,2021,2028,-1,2062);
        _SFD_CV_INIT_EML_WHILE(0,1,0,1264,1285,1496);
        _SFD_CV_INIT_SCRIPT(0,1,2,0,0,0,1,0,1,1);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"value_summary",0,-1,500);
        _SFD_CV_INIT_SCRIPT_IF(0,0,90,110,470,500);
        _SFD_CV_INIT_SCRIPT_IF(0,1,315,339,388,457);
        _SFD_CV_INIT_SCRIPT_FOR(0,0,285,303,469);

        {
          static int condStart[] = { 94 };

          static int condEnd[] = { 109 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,0,93,109,1,0,&(condStart[0]),&(condEnd[0]),
            2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(1,1,2,0,0,0,1,0,1,1);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"network_delay_summary",0,-1,585);
        _SFD_CV_INIT_SCRIPT_IF(1,0,97,117,558,585);
        _SFD_CV_INIT_SCRIPT_IF(1,1,385,410,476,545);
        _SFD_CV_INIT_SCRIPT_FOR(1,0,289,307,557);

        {
          static int condStart[] = { 101 };

          static int condEnd[] = { 116 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_SCRIPT_MCDC(1,0,100,116,1,0,&(condStart[0]),&(condEnd[0]),
            2,&(pfixExpr[0]));
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)
            c3_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)
            c3_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)
            c3_d_sf_marshallIn);
        }

        {
          real_T (*c3_actual_value)[3];
          real_T (*c3_actual_value1)[3];
          real_T (*c3_ysensor_value)[3];
          real_T (*c3_ynetwork_delay)[3];
          c3_ynetwork_delay = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 3);
          c3_ysensor_value = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 2);
          c3_actual_value1 = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c3_actual_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S,
            0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_actual_value);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_actual_value1);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_ysensor_value);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_ynetwork_delay);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HXpump_whole_sanityMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "KBgqYW9ku24b8nFEAAlOvF";
}

static void sf_opaque_initialize_c3_HXpump_whole_sanity(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_HXpump_whole_sanity
    ((SFc3_HXpump_whole_sanityInstanceStruct*) chartInstanceVar);
  initialize_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_HXpump_whole_sanity(void *chartInstanceVar)
{
  enable_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c3_HXpump_whole_sanity(void *chartInstanceVar)
{
  disable_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_HXpump_whole_sanity(void *chartInstanceVar)
{
  sf_gateway_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_HXpump_whole_sanity(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_HXpump_whole_sanity
    ((SFc3_HXpump_whole_sanityInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_HXpump_whole_sanity();/* state var info */
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

extern void sf_internal_set_sim_state_c3_HXpump_whole_sanity(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c3_HXpump_whole_sanity();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_HXpump_whole_sanity(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c3_HXpump_whole_sanity(S);
}

static void sf_opaque_set_sim_state_c3_HXpump_whole_sanity(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c3_HXpump_whole_sanity(S, st);
}

static void sf_opaque_terminate_c3_HXpump_whole_sanity(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_HXpump_whole_sanityInstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HXpump_whole_sanity_optimization_info();
    }

    finalize_c3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_HXpump_whole_sanity((SFc3_HXpump_whole_sanityInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_HXpump_whole_sanity(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c3_HXpump_whole_sanity
      ((SFc3_HXpump_whole_sanityInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_HXpump_whole_sanity(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HXpump_whole_sanity_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(553172568U));
  ssSetChecksum1(S,(1303706588U));
  ssSetChecksum2(S,(2235798552U));
  ssSetChecksum3(S,(881312616U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_HXpump_whole_sanity(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_HXpump_whole_sanity(SimStruct *S)
{
  SFc3_HXpump_whole_sanityInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_HXpump_whole_sanityInstanceStruct *)utMalloc(sizeof
    (SFc3_HXpump_whole_sanityInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_HXpump_whole_sanityInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c3_HXpump_whole_sanity;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_HXpump_whole_sanity_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_HXpump_whole_sanity(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_HXpump_whole_sanity(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_HXpump_whole_sanity(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_HXpump_whole_sanity_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
