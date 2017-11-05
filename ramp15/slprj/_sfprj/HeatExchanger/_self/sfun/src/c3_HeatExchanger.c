/* Include files */

#include <stddef.h>
#include "blas.h"
#include "HeatExchanger_sfun.h"
#include "c3_HeatExchanger.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "HeatExchanger_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[23] = { "sensor_reading",
  "sensor_delay", "kk", "j", "avg_delay", "fileID", "nargin", "nargout",
  "yactual_value", "ysensor_value", "ynetwork_delay", "structure",
  "signal_vector", "delay_vector", "i", "yin_d", "delay_v", "yin",
  "sensor_value", "num", "ynd_tmp", "last_senReading", "last_senDelay" };

/* Function Declarations */
static void initialize_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void initialize_params_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct *
  chartInstance);
static void enable_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void disable_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_HeatExchanger
  (SFc3_HeatExchangerInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_HeatExchanger
  (SFc3_HeatExchangerInstanceStruct *chartInstance);
static void set_sim_state_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void sf_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct *chartInstance);
static void c3_chartstep_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void initSimStructsc3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void registerMessagesc3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct *chartInstance,
  const mxArray *c3_b_last_senDelay, const char_T *c3_identifier, real_T c3_y[9]);
static void c3_b_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_last_senReading, const char_T
  *c3_identifier, real_T c3_y[9]);
static void c3_d_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_e_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_ynd_tmp, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_f_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_g_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_num, const char_T *c3_identifier);
static real_T c3_h_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_sensor_value, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_j_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_k_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_yin, const char_T *c3_identifier, real_T
  c3_y[3]);
static void c3_l_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_m_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_delay_v, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_n_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_o_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_yin_d, const char_T *c3_identifier, real_T
  c3_y[3]);
static void c3_p_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_q_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_i, const char_T *c3_identifier);
static real_T c3_r_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_s_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_delay_vector, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_t_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_u_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB *c3_y);
static void c3_v_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_w_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_x_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[5]);
static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[32]);
static real_T c3_fopen(SFc3_HeatExchangerInstanceStruct *chartInstance);
static real_T c3_fileManager(SFc3_HeatExchangerInstanceStruct *chartInstance);
static void c3_isequal(SFc3_HeatExchangerInstanceStruct *chartInstance);
static int8_T c3_filedata(SFc3_HeatExchangerInstanceStruct *chartInstance);
static void c3_fprintf(SFc3_HeatExchangerInstanceStruct *chartInstance, real_T
  c3_fileID, real_T c3_varargin_1);
static void c3_fclose(SFc3_HeatExchangerInstanceStruct *chartInstance, real_T
                      c3_fileID);
static int32_T c3_b_fileManager(SFc3_HeatExchangerInstanceStruct *chartInstance,
  real_T c3_varargin_1);
static real_T c3_y_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_feval, const char_T *c3_identifier);
static real_T c3_ab_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static boolean_T c3_bb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_failp, const char_T *c3_identifier);
static boolean_T c3_cb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_db_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_eb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_eml_autoflush, const char_T *c3_identifier,
  boolean_T c3_y[20]);
static void c3_fb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  boolean_T c3_y[20]);
static uint8_T c3_gb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_HeatExchanger, const char_T
  *c3_identifier);
static uint8_T c3_hb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_HeatExchangerInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_i_not_empty = FALSE;
  chartInstance->c3_yin_d_not_empty = FALSE;
  chartInstance->c3_delay_v_not_empty = FALSE;
  chartInstance->c3_yin_not_empty = FALSE;
  chartInstance->c3_sensor_value_not_empty = FALSE;
  chartInstance->c3_num_not_empty = FALSE;
  chartInstance->c3_ynd_tmp_not_empty = FALSE;
  chartInstance->c3_last_senReading_not_empty = FALSE;
  chartInstance->c3_last_senDelay_not_empty = FALSE;
  chartInstance->c3_eml_openfiles_not_empty = FALSE;
  chartInstance->c3_eml_autoflush_not_empty = FALSE;
  chartInstance->c3_is_active_c3_HeatExchanger = 0U;
}

static void initialize_params_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct *
  chartInstance)
{
  const mxArray *c3_m0 = NULL;
  const mxArray *c3_mxField;
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB c3_r0;
  sf_set_error_prefix_string(
    "Error evaluating data 'structure' in the parent workspace.\n");
  c3_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c3_mxField = sf_mex_getfield(c3_m0, "i", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), &c3_r0.i, 1, 0, 0U, 0,
                      0U, 0);
  c3_mxField = sf_mex_getfield(c3_m0, "count", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), &c3_r0.count, 1, 0,
                      0U, 0, 0U, 0);
  c3_mxField = sf_mex_getfield(c3_m0, "sen_num", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), &c3_r0.sen_num, 1, 0,
                      0U, 0, 0U, 0);
  c3_mxField = sf_mex_getfield(c3_m0, "yin", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), c3_r0.yin, 1, 0, 0U,
                      1, 0U, 2, 1, 3);
  c3_mxField = sf_mex_getfield(c3_m0, "yin_d", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), c3_r0.yin_d, 1, 0, 0U,
                      1, 0U, 2, 3, 1);
  c3_mxField = sf_mex_getfield(c3_m0, "delay_v", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), c3_r0.delay_v, 1, 0,
                      0U, 1, 0U, 2, 3, 1);
  c3_mxField = sf_mex_getfield(c3_m0, "ynd_tmp", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), c3_r0.ynd_tmp, 1, 0,
                      0U, 1, 0U, 2, 1, 3);
  c3_mxField = sf_mex_getfield(c3_m0, "ranD", "structure", 0);
  sf_mex_import_named("structure", sf_mex_dup(c3_mxField), c3_r0.ranD, 1, 0, 0U,
                      1, 0U, 2, 1, 5);
  sf_mex_destroy(&c3_m0);
  chartInstance->c3_structure = c3_r0;
  sf_set_error_prefix_string("Stateflow Runtime Error (chart): ");
}

static void enable_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_HeatExchanger
  (SFc3_HeatExchangerInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_HeatExchanger
  (SFc3_HeatExchangerInstanceStruct *chartInstance)
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
  int32_T c3_i3;
  boolean_T c3_d_u[20];
  const mxArray *c3_e_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  int32_T c3_i4;
  real_T c3_f_u[9];
  const mxArray *c3_g_y = NULL;
  int32_T c3_i5;
  real_T c3_g_u[9];
  const mxArray *c3_h_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_h_u;
  const mxArray *c3_i_y = NULL;
  int32_T c3_i6;
  real_T c3_i_u[3];
  const mxArray *c3_j_y = NULL;
  int32_T c3_i7;
  real_T c3_j_u[3];
  const mxArray *c3_k_y = NULL;
  int32_T c3_i8;
  real_T c3_k_u[3];
  const mxArray *c3_l_y = NULL;
  int32_T c3_i9;
  real_T c3_l_u[3];
  const mxArray *c3_m_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_m_u;
  const mxArray *c3_n_y = NULL;
  real_T (*c3_signal_vector)[3];
  real_T (*c3_delay_vector)[3];
  c3_delay_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_signal_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(13), FALSE);
  for (c3_i0 = 0; c3_i0 < 3; c3_i0++) {
    c3_u[c3_i0] = (*c3_delay_vector)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i1 = 0; c3_i1 < 3; c3_i1++) {
    c3_b_u[c3_i1] = (*c3_signal_vector)[c3_i1];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  for (c3_i2 = 0; c3_i2 < 3; c3_i2++) {
    c3_c_u[c3_i2] = chartInstance->c3_delay_v[c3_i2];
  }

  c3_d_y = NULL;
  if (!chartInstance->c3_delay_v_not_empty) {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 2, c3_d_y);
  for (c3_i3 = 0; c3_i3 < 20; c3_i3++) {
    c3_d_u[c3_i3] = chartInstance->c3_eml_autoflush[c3_i3];
  }

  c3_e_y = NULL;
  if (!chartInstance->c3_eml_autoflush_not_empty) {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_d_u, 11, 0U, 1U, 0U, 1, 20),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_hoistedGlobal = chartInstance->c3_i;
  c3_e_u = c3_hoistedGlobal;
  c3_f_y = NULL;
  if (!chartInstance->c3_i_not_empty) {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 4, c3_f_y);
  for (c3_i4 = 0; c3_i4 < 9; c3_i4++) {
    c3_f_u[c3_i4] = chartInstance->c3_last_senDelay[c3_i4];
  }

  c3_g_y = NULL;
  if (!chartInstance->c3_last_senDelay_not_empty) {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 2, 1, 9),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 5, c3_g_y);
  for (c3_i5 = 0; c3_i5 < 9; c3_i5++) {
    c3_g_u[c3_i5] = chartInstance->c3_last_senReading[c3_i5];
  }

  c3_h_y = NULL;
  if (!chartInstance->c3_last_senReading_not_empty) {
    sf_mex_assign(&c3_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_g_u, 0, 0U, 1U, 0U, 2, 1, 9),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 6, c3_h_y);
  c3_b_hoistedGlobal = chartInstance->c3_num;
  c3_h_u = c3_b_hoistedGlobal;
  c3_i_y = NULL;
  if (!chartInstance->c3_num_not_empty) {
    sf_mex_assign(&c3_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_i_y, sf_mex_create("y", &c3_h_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c3_y, 7, c3_i_y);
  for (c3_i6 = 0; c3_i6 < 3; c3_i6++) {
    c3_i_u[c3_i6] = chartInstance->c3_sensor_value[c3_i6];
  }

  c3_j_y = NULL;
  if (!chartInstance->c3_sensor_value_not_empty) {
    sf_mex_assign(&c3_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_j_y, sf_mex_create("y", c3_i_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 8, c3_j_y);
  for (c3_i7 = 0; c3_i7 < 3; c3_i7++) {
    c3_j_u[c3_i7] = chartInstance->c3_yin[c3_i7];
  }

  c3_k_y = NULL;
  if (!chartInstance->c3_yin_not_empty) {
    sf_mex_assign(&c3_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_k_y, sf_mex_create("y", c3_j_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 9, c3_k_y);
  for (c3_i8 = 0; c3_i8 < 3; c3_i8++) {
    c3_k_u[c3_i8] = chartInstance->c3_yin_d[c3_i8];
  }

  c3_l_y = NULL;
  if (!chartInstance->c3_yin_d_not_empty) {
    sf_mex_assign(&c3_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_l_y, sf_mex_create("y", c3_k_u, 0, 0U, 1U, 0U, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 10, c3_l_y);
  for (c3_i9 = 0; c3_i9 < 3; c3_i9++) {
    c3_l_u[c3_i9] = chartInstance->c3_ynd_tmp[c3_i9];
  }

  c3_m_y = NULL;
  if (!chartInstance->c3_ynd_tmp_not_empty) {
    sf_mex_assign(&c3_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c3_m_y, sf_mex_create("y", c3_l_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c3_y, 11, c3_m_y);
  c3_c_hoistedGlobal = chartInstance->c3_is_active_c3_HeatExchanger;
  c3_m_u = c3_c_hoistedGlobal;
  c3_n_y = NULL;
  sf_mex_assign(&c3_n_y, sf_mex_create("y", &c3_m_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 12, c3_n_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[3];
  int32_T c3_i10;
  real_T c3_dv1[3];
  int32_T c3_i11;
  real_T c3_dv2[3];
  int32_T c3_i12;
  boolean_T c3_bv0[20];
  int32_T c3_i13;
  real_T c3_dv3[9];
  int32_T c3_i14;
  real_T c3_dv4[9];
  int32_T c3_i15;
  real_T c3_dv5[3];
  int32_T c3_i16;
  real_T c3_dv6[3];
  int32_T c3_i17;
  real_T c3_dv7[3];
  int32_T c3_i18;
  real_T c3_dv8[3];
  int32_T c3_i19;
  real_T (*c3_delay_vector)[3];
  real_T (*c3_signal_vector)[3];
  c3_delay_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_signal_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                        "delay_vector", c3_dv0);
  for (c3_i10 = 0; c3_i10 < 3; c3_i10++) {
    (*c3_delay_vector)[c3_i10] = c3_dv0[c3_i10];
  }

  c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "signal_vector", c3_dv1);
  for (c3_i11 = 0; c3_i11 < 3; c3_i11++) {
    (*c3_signal_vector)[c3_i11] = c3_dv1[c3_i11];
  }

  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
                        "delay_v", c3_dv2);
  for (c3_i12 = 0; c3_i12 < 3; c3_i12++) {
    chartInstance->c3_delay_v[c3_i12] = c3_dv2[c3_i12];
  }

  c3_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
    "eml_autoflush", c3_bv0);
  for (c3_i13 = 0; c3_i13 < 20; c3_i13++) {
    chartInstance->c3_eml_autoflush[c3_i13] = c3_bv0[c3_i13];
  }

  chartInstance->c3_i = c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 4)), "i");
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 5)),
                      "last_senDelay", c3_dv3);
  for (c3_i14 = 0; c3_i14 < 9; c3_i14++) {
    chartInstance->c3_last_senDelay[c3_i14] = c3_dv3[c3_i14];
  }

  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 6)),
                        "last_senReading", c3_dv4);
  for (c3_i15 = 0; c3_i15 < 9; c3_i15++) {
    chartInstance->c3_last_senReading[c3_i15] = c3_dv4[c3_i15];
  }

  chartInstance->c3_num = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 7)), "num");
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 8)),
                        "sensor_value", c3_dv5);
  for (c3_i16 = 0; c3_i16 < 3; c3_i16++) {
    chartInstance->c3_sensor_value[c3_i16] = c3_dv5[c3_i16];
  }

  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 9)),
                        "yin", c3_dv6);
  for (c3_i17 = 0; c3_i17 < 3; c3_i17++) {
    chartInstance->c3_yin[c3_i17] = c3_dv6[c3_i17];
  }

  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 10)),
                        "yin_d", c3_dv7);
  for (c3_i18 = 0; c3_i18 < 3; c3_i18++) {
    chartInstance->c3_yin_d[c3_i18] = c3_dv7[c3_i18];
  }

  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 11)),
                        "ynd_tmp", c3_dv8);
  for (c3_i19 = 0; c3_i19 < 3; c3_i19++) {
    chartInstance->c3_ynd_tmp[c3_i19] = c3_dv8[c3_i19];
  }

  chartInstance->c3_is_active_c3_HeatExchanger = c3_gb_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 12)),
     "is_active_c3_HeatExchanger");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_HeatExchanger(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
}

static void sf_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct *chartInstance)
{
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  int32_T c3_i24;
  real_T (*c3_delay_vector)[3];
  real_T (*c3_signal_vector)[3];
  real_T (*c3_ynetwork_delay)[3];
  real_T (*c3_ysensor_value)[3];
  real_T (*c3_yactual_value)[3];
  c3_delay_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_signal_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_ynetwork_delay = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c3_ysensor_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c3_yactual_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i20 = 0; c3_i20 < 3; c3_i20++) {
    _SFD_DATA_RANGE_CHECK((*c3_yactual_value)[c3_i20], 0U);
  }

  for (c3_i21 = 0; c3_i21 < 3; c3_i21++) {
    _SFD_DATA_RANGE_CHECK((*c3_ysensor_value)[c3_i21], 1U);
  }

  for (c3_i22 = 0; c3_i22 < 3; c3_i22++) {
    _SFD_DATA_RANGE_CHECK((*c3_ynetwork_delay)[c3_i22], 2U);
  }

  for (c3_i23 = 0; c3_i23 < 3; c3_i23++) {
    _SFD_DATA_RANGE_CHECK((*c3_signal_vector)[c3_i23], 3U);
  }

  for (c3_i24 = 0; c3_i24 < 3; c3_i24++) {
    _SFD_DATA_RANGE_CHECK((*c3_delay_vector)[c3_i24], 5U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_HeatExchanger(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_HeatExchangerMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
  int32_T c3_i25;
  real_T c3_yactual_value[3];
  int32_T c3_i26;
  real_T c3_ysensor_value[3];
  int32_T c3_i27;
  real_T c3_ynetwork_delay[3];
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB c3_b_structure;
  uint32_T c3_debug_family_var_map[23];
  real_T c3_sensor_reading[3];
  real_T c3_sensor_delay[3];
  real_T c3_kk;
  real_T c3_j;
  real_T c3_avg_delay;
  real_T c3_fileID;
  real_T c3_nargin = 4.0;
  real_T c3_nargout = 2.0;
  real_T c3_signal_vector[3];
  real_T c3_delay_vector[3];
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_i32;
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_b_kk;
  real_T c3_A;
  real_T c3_x;
  real_T c3_b_x;
  real_T c3_y;
  real_T c3_c_x;
  real_T c3_d_x;
  real_T c3_a;
  real_T c3_b_y;
  int32_T c3_b_j;
  real_T c3_b_A;
  real_T c3_e_x;
  real_T c3_f_x;
  real_T c3_c_y;
  real_T c3_g_x;
  real_T c3_h_x;
  real_T c3_b_a;
  real_T c3_d_y;
  int32_T c3_c_kk;
  real_T c3_c_A;
  real_T c3_i_x;
  real_T c3_j_x;
  int32_T c3_i39;
  int32_T c3_i40;
  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  static char_T c3_cv0[22] = { 'c', 'o', 'n', 'v', 'e', 'r', 't', 'e', 'd', ' ',
    's', 'e', 'n', 's', 'o', 'r', '_', 'v', 'a', 'l', 'u', 'e' };

  char_T c3_u[22];
  const mxArray *c3_e_y = NULL;
  int32_T c3_i44;
  real_T c3_b_u[3];
  const mxArray *c3_f_y = NULL;
  int32_T c3_i45;
  static char_T c3_cv1[23] = { 'c', 'o', 'n', 'v', 'e', 'r', 't', 'e', 'd', ' ',
    'n', 'e', 't', 'w', 'o', 'r', 'k', ' ', 'd', 'e', 'l', 'a', 'y' };

  char_T c3_c_u[23];
  const mxArray *c3_g_y = NULL;
  int32_T c3_i46;
  real_T c3_d_u[3];
  const mxArray *c3_h_y = NULL;
  int32_T c3_i47;
  static char_T c3_cv2[31] = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',
    '-', '-', '-', '-', '-', 'n', 'u', 'm', '-', '-', '-', '-', '-', '-', '-',
    '-', '-', '-', '-', '-', '-' };

  char_T c3_e_u[31];
  const mxArray *c3_i_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_f_u;
  const mxArray *c3_j_y = NULL;
  int32_T c3_i48;
  int32_T c3_i49;
  real_T (*c3_b_signal_vector)[3];
  real_T (*c3_b_delay_vector)[3];
  real_T (*c3_b_ynetwork_delay)[3];
  real_T (*c3_b_ysensor_value)[3];
  real_T (*c3_b_yactual_value)[3];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  boolean_T guard5 = FALSE;
  boolean_T guard6 = FALSE;
  c3_b_delay_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_signal_vector = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_ynetwork_delay = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_ysensor_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_yactual_value = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i25 = 0; c3_i25 < 3; c3_i25++) {
    c3_yactual_value[c3_i25] = (*c3_b_yactual_value)[c3_i25];
  }

  for (c3_i26 = 0; c3_i26 < 3; c3_i26++) {
    c3_ysensor_value[c3_i26] = (*c3_b_ysensor_value)[c3_i26];
  }

  for (c3_i27 = 0; c3_i27 < 3; c3_i27++) {
    c3_ynetwork_delay[c3_i27] = (*c3_b_ynetwork_delay)[c3_i27];
  }

  c3_b_structure = chartInstance->c3_structure;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 23U, 23U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_sensor_reading, 0U,
    c3_m_sf_marshallOut, c3_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_sensor_delay, 1U, c3_m_sf_marshallOut,
    c3_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_kk, 2U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_j, 3U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_avg_delay, 4U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_fileID, 5U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 6U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 7U, c3_l_sf_marshallOut,
    c3_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_yactual_value, 8U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ysensor_value, 9U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ynetwork_delay, 10U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_structure, 11U, c3_k_sf_marshallOut,
    c3_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_signal_vector, 12U,
    c3_j_sf_marshallOut, c3_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_delay_vector, 13U, c3_j_sf_marshallOut,
    c3_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_i, 14U,
    c3_i_sf_marshallOut, c3_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_yin_d, 15U,
    c3_h_sf_marshallOut, c3_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_delay_v, 16U,
    c3_g_sf_marshallOut, c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_yin, 17U,
    c3_f_sf_marshallOut, c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_sensor_value, 18U,
    c3_e_sf_marshallOut, c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c3_num, 19U,
    c3_d_sf_marshallOut, c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_ynd_tmp, 20U,
    c3_c_sf_marshallOut, c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_last_senReading, 21U,
    c3_b_sf_marshallOut, c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c3_last_senDelay, 22U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 14);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 26);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c3_yin_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 27);
    chartInstance->c3_i = c3_b_structure.i;
    chartInstance->c3_i_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
    for (c3_i28 = 0; c3_i28 < 3; c3_i28++) {
      chartInstance->c3_yin[c3_i28] = c3_b_structure.yin[c3_i28];
    }

    chartInstance->c3_yin_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
    for (c3_i29 = 0; c3_i29 < 3; c3_i29++) {
      chartInstance->c3_ynd_tmp[c3_i29] = c3_b_structure.ynd_tmp[c3_i29];
    }

    chartInstance->c3_ynd_tmp_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 31);
    for (c3_i30 = 0; c3_i30 < 3; c3_i30++) {
      chartInstance->c3_yin_d[c3_i30] = c3_b_structure.yin_d[c3_i30];
    }

    chartInstance->c3_yin_d_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
    for (c3_i31 = 0; c3_i31 < 3; c3_i31++) {
      chartInstance->c3_delay_v[c3_i31] = c3_b_structure.delay_v[c3_i31];
    }

    chartInstance->c3_delay_v_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 34);
    for (c3_i32 = 0; c3_i32 < 9; c3_i32++) {
      chartInstance->c3_last_senReading[c3_i32] = 0.0;
    }

    chartInstance->c3_last_senReading_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
    for (c3_i33 = 0; c3_i33 < 9; c3_i33++) {
      chartInstance->c3_last_senDelay[c3_i33] = 0.0;
    }

    chartInstance->c3_last_senDelay_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 43);
    for (c3_i34 = 0; c3_i34 < 3; c3_i34++) {
      chartInstance->c3_sensor_value[c3_i34] = 0.0;
    }

    chartInstance->c3_sensor_value_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 44);
    for (c3_i35 = 0; c3_i35 < 3; c3_i35++) {
      chartInstance->c3_sensor_value[c3_i35] = c3_ysensor_value[c3_i35];
    }

    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 45);
    chartInstance->c3_num = 0.0;
    chartInstance->c3_num_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 51);
  for (c3_i36 = 0; c3_i36 < 3; c3_i36++) {
    c3_sensor_reading[c3_i36] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 52);
  for (c3_i37 = 0; c3_i37 < 3; c3_i37++) {
    c3_sensor_delay[c3_i37] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 53);
  chartInstance->c3_num++;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 57);
  for (c3_i38 = 0; c3_i38 < 3; c3_i38++) {
    chartInstance->c3_sensor_value[c3_i38] = c3_ysensor_value[c3_i38];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 62);
  if (CV_EML_IF(0, 1, 1, chartInstance->c3_num == 1.0)) {
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 63);
    c3_kk = 1.0;
    c3_b_kk = 0;
    while (c3_b_kk < 3) {
      c3_kk = 1.0 + (real_T)c3_b_kk;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 64);
      chartInstance->c3_last_senReading[(int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
        _SFD_INTEGER_CHECK("kk", c3_kk), 1, 9, 1, 0) - 1] = c3_yactual_value
        [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("yactual_value", (int32_T)
        _SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 66);
      guard4 = FALSE;
      guard5 = FALSE;
      guard6 = FALSE;
      if (CV_EML_COND(0, 1, 0, c3_ynetwork_delay[(int32_T)(real_T)
                      _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay", (int32_T)
            _SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1] == 0.2)) {
        guard6 = TRUE;
      } else if (CV_EML_COND(0, 1, 1, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1] ==
                  0.3)) {
        guard6 = TRUE;
      } else if (CV_EML_COND(0, 1, 2, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1] ==
                  0.4)) {
        guard5 = TRUE;
      } else if (CV_EML_COND(0, 1, 3, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1] ==
                  0.5)) {
        guard4 = TRUE;
      } else {
        CV_EML_MCDC(0, 1, 0, FALSE);
        CV_EML_IF(0, 1, 2, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 69);
        c3_A = c3_ynetwork_delay[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
          "ynetwork_delay", (int32_T)_SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0)
          - 1];
        c3_x = c3_A;
        c3_b_x = c3_x;
        c3_y = c3_b_x / 0.1;
        c3_c_x = c3_y;
        c3_d_x = c3_c_x;
        c3_d_x = muDoubleScalarCeil(c3_d_x);
        c3_a = c3_d_x;
        c3_b_y = c3_a * 0.1;
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("kk", c3_kk), 1, 9, 1, 0) - 1] = c3_b_y;
      }

      if (guard6 == TRUE) {
        guard5 = TRUE;
      }

      if (guard5 == TRUE) {
        guard4 = TRUE;
      }

      if (guard4 == TRUE) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 2, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 67);
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("kk", c3_kk), 1, 9, 1, 0) - 1] = c3_ynetwork_delay
          [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
          (int32_T)_SFD_INTEGER_CHECK("kk", c3_kk), 1, 3, 1, 0) - 1];
      }

      c3_b_kk++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0, 0);
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 77);
  c3_j = 1.0;
  c3_b_j = 0;
  while (c3_b_j < 3) {
    c3_j = 1.0 + (real_T)c3_b_j;
    CV_EML_FOR(0, 1, 1, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 78);
    if (CV_EML_IF(0, 1, 3, chartInstance->c3_sensor_value[(int32_T)(real_T)
                  _SFD_EML_ARRAY_BOUNDS_CHECK("sensor_value", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 3, 2, 0) - 1] != 88.0)) {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 79);
      chartInstance->c3_last_senReading[(int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
        _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] = c3_yactual_value
        [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("yactual_value", (int32_T)
        _SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 82);
      guard1 = FALSE;
      guard2 = FALSE;
      guard3 = FALSE;
      if (CV_EML_COND(0, 1, 4, c3_ynetwork_delay[(int32_T)(real_T)
                      _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay", (int32_T)
            _SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] == 0.2)) {
        guard3 = TRUE;
      } else if (CV_EML_COND(0, 1, 5, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] ==
                             0.3)) {
        guard3 = TRUE;
      } else if (CV_EML_COND(0, 1, 6, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] ==
                             0.4)) {
        guard2 = TRUE;
      } else if (CV_EML_COND(0, 1, 7, c3_ynetwork_delay[(int32_T)(real_T)
                             _SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
                   (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] ==
                             0.5)) {
        guard1 = TRUE;
      } else {
        CV_EML_MCDC(0, 1, 1, FALSE);
        CV_EML_IF(0, 1, 4, FALSE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 85);
        c3_b_A = c3_ynetwork_delay[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
          "ynetwork_delay", (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0)
          - 1];
        c3_e_x = c3_b_A;
        c3_f_x = c3_e_x;
        c3_c_y = c3_f_x / 0.1;
        c3_g_x = c3_c_y;
        c3_h_x = c3_g_x;
        c3_h_x = muDoubleScalarCeil(c3_h_x);
        c3_b_a = c3_h_x;
        c3_d_y = c3_b_a * 0.1;
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] = c3_d_y;
      }

      if (guard3 == TRUE) {
        guard2 = TRUE;
      }

      if (guard2 == TRUE) {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        CV_EML_MCDC(0, 1, 1, TRUE);
        CV_EML_IF(0, 1, 4, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 83);
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] = c3_ynetwork_delay
          [(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("ynetwork_delay",
          (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1];
      }

      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 88);
      chartInstance->c3_yin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("yin",
        (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] =
        chartInstance->c3_last_senReading[(int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
        _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1];
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 89);
      chartInstance->c3_ynd_tmp[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
        "ynd_tmp", (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] =
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)_SFD_INTEGER_CHECK
                                    ("j", c3_j), 1, 9, 1, 0) - 1];
    } else {
      _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 92);
      if (CV_EML_IF(0, 1, 5, chartInstance->c3_num > 1.0)) {
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 93);
        chartInstance->c3_yin[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("yin",
          (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] =
          chartInstance->c3_last_senReading[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1];
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 94);
        chartInstance->c3_last_senReading[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] =
          chartInstance->c3_last_senReading[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senReading", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1];
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 95);
        chartInstance->c3_ynd_tmp[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
          "ynd_tmp", (int32_T)_SFD_INTEGER_CHECK("j", c3_j), 1, 3, 1, 0) - 1] =
          chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] + 0.1;
        _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 96);
        chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] =
          chartInstance->c3_last_senDelay[(int32_T)(real_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)
          _SFD_INTEGER_CHECK("j", c3_j), 1, 9, 1, 0) - 1] + 0.1;
      }
    }

    c3_b_j++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 1, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 101);
  c3_avg_delay = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 103);
  c3_kk = 1.0;
  c3_c_kk = 0;
  while (c3_c_kk < 3) {
    c3_kk = 1.0 + (real_T)c3_c_kk;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 106);
    c3_avg_delay += chartInstance->c3_last_senDelay[(int32_T)(real_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("last_senDelay", (int32_T)_SFD_INTEGER_CHECK(
      "kk", c3_kk), 1, 9, 1, 0) - 1];
    c3_c_kk++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 110);
  c3_c_A = c3_avg_delay;
  c3_i_x = c3_c_A;
  c3_j_x = c3_i_x;
  c3_avg_delay = c3_j_x / 3.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 111);
  c3_fileID = c3_fopen(chartInstance);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 112);
  c3_fprintf(chartInstance, c3_fileID, c3_avg_delay);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 113);
  c3_fclose(chartInstance, c3_fileID);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 120);
  for (c3_i39 = 0; c3_i39 < 3; c3_i39++) {
    chartInstance->c3_yin_d[c3_i39] = chartInstance->c3_yin[c3_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 121);
  for (c3_i40 = 0; c3_i40 < 3; c3_i40++) {
    chartInstance->c3_delay_v[c3_i40] = chartInstance->c3_ynd_tmp[c3_i40];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 125);
  for (c3_i41 = 0; c3_i41 < 3; c3_i41++) {
    c3_signal_vector[c3_i41] = chartInstance->c3_yin_d[c3_i41];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, MAX_int8_T);
  for (c3_i42 = 0; c3_i42 < 3; c3_i42++) {
    c3_delay_vector[c3_i42] = chartInstance->c3_delay_v[c3_i42];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 129U);
  for (c3_i43 = 0; c3_i43 < 22; c3_i43++) {
    c3_u[c3_i43] = c3_cv0[c3_i43];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 22),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_e_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 130U);
  for (c3_i44 = 0; c3_i44 < 3; c3_i44++) {
    c3_b_u[c3_i44] = c3_signal_vector[c3_i44];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 2, 1, 3),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_f_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 131U);
  for (c3_i45 = 0; c3_i45 < 23; c3_i45++) {
    c3_c_u[c3_i45] = c3_cv1[c3_i45];
  }

  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 23),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_g_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 132U);
  for (c3_i46 = 0; c3_i46 < 3; c3_i46++) {
    c3_d_u[c3_i46] = c3_delay_vector[c3_i46];
  }

  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_d_u, 0, 0U, 1U, 0U, 2, 1, 3),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_h_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 133U);
  for (c3_i47 = 0; c3_i47 < 31; c3_i47++) {
    c3_e_u[c3_i47] = c3_cv2[c3_i47];
  }

  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", c3_e_u, 10, 0U, 1U, 0U, 2, 1, 31),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_i_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 134U);
  c3_hoistedGlobal = chartInstance->c3_num;
  c3_f_u = c3_hoistedGlobal;
  c3_j_y = NULL;
  sf_mex_assign(&c3_j_y, sf_mex_create("y", &c3_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c3_j_y);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 139U);
  chartInstance->c3_i++;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -139);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i48 = 0; c3_i48 < 3; c3_i48++) {
    (*c3_b_signal_vector)[c3_i48] = c3_signal_vector[c3_i48];
  }

  for (c3_i49 = 0; c3_i49 < 3; c3_i49++) {
    (*c3_b_delay_vector)[c3_i49] = c3_delay_vector[c3_i49];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc3_HeatExchanger(SFc3_HeatExchangerInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i50;
  real_T c3_b_inData[9];
  int32_T c3_i51;
  real_T c3_u[9];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i50 = 0; c3_i50 < 9; c3_i50++) {
    c3_b_inData[c3_i50] = (*(real_T (*)[9])c3_inData)[c3_i50];
  }

  for (c3_i51 = 0; c3_i51 < 9; c3_i51++) {
    c3_u[c3_i51] = c3_b_inData[c3_i51];
  }

  c3_y = NULL;
  if (!chartInstance->c3_last_senDelay_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 9), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct *chartInstance,
  const mxArray *c3_b_last_senDelay, const char_T *c3_identifier, real_T c3_y[9])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_last_senDelay),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_last_senDelay);
}

static void c3_b_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9])
{
  real_T c3_dv9[9];
  int32_T c3_i52;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_last_senDelay_not_empty = FALSE;
  } else {
    chartInstance->c3_last_senDelay_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv9, 1, 0, 0U, 1, 0U, 2, 1,
                  9);
    for (c3_i52 = 0; c3_i52 < 9; c3_i52++) {
      c3_y[c3_i52] = c3_dv9[c3_i52];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_last_senDelay;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i53;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_last_senDelay = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_last_senDelay),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_last_senDelay);
  for (c3_i53 = 0; c3_i53 < 9; c3_i53++) {
    (*(real_T (*)[9])c3_outData)[c3_i53] = c3_y[c3_i53];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i54;
  real_T c3_b_inData[9];
  int32_T c3_i55;
  real_T c3_u[9];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i54 = 0; c3_i54 < 9; c3_i54++) {
    c3_b_inData[c3_i54] = (*(real_T (*)[9])c3_inData)[c3_i54];
  }

  for (c3_i55 = 0; c3_i55 < 9; c3_i55++) {
    c3_u[c3_i55] = c3_b_inData[c3_i55];
  }

  c3_y = NULL;
  if (!chartInstance->c3_last_senReading_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 9), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_last_senReading, const char_T
  *c3_identifier, real_T c3_y[9])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_last_senReading),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_last_senReading);
}

static void c3_d_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9])
{
  real_T c3_dv10[9];
  int32_T c3_i56;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_last_senReading_not_empty = FALSE;
  } else {
    chartInstance->c3_last_senReading_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv10, 1, 0, 0U, 1, 0U, 2, 1,
                  9);
    for (c3_i56 = 0; c3_i56 < 9; c3_i56++) {
      c3_y[c3_i56] = c3_dv10[c3_i56];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_last_senReading;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i57;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_last_senReading = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_last_senReading),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_last_senReading);
  for (c3_i57 = 0; c3_i57 < 9; c3_i57++) {
    (*(real_T (*)[9])c3_outData)[c3_i57] = c3_y[c3_i57];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i58;
  real_T c3_b_inData[3];
  int32_T c3_i59;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i58 = 0; c3_i58 < 3; c3_i58++) {
    c3_b_inData[c3_i58] = (*(real_T (*)[3])c3_inData)[c3_i58];
  }

  for (c3_i59 = 0; c3_i59 < 3; c3_i59++) {
    c3_u[c3_i59] = c3_b_inData[c3_i59];
  }

  c3_y = NULL;
  if (!chartInstance->c3_ynd_tmp_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_e_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_ynd_tmp, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_ynd_tmp), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_ynd_tmp);
}

static void c3_f_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv11[3];
  int32_T c3_i60;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_ynd_tmp_not_empty = FALSE;
  } else {
    chartInstance->c3_ynd_tmp_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv11, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c3_i60 = 0; c3_i60 < 3; c3_i60++) {
      c3_y[c3_i60] = c3_dv11[c3_i60];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_ynd_tmp;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i61;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_ynd_tmp = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_ynd_tmp), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_ynd_tmp);
  for (c3_i61 = 0; c3_i61 < 3; c3_i61++) {
    (*(real_T (*)[3])c3_outData)[c3_i61] = c3_y[c3_i61];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_num_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_g_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_num, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_num), &c3_thisId);
  sf_mex_destroy(&c3_b_num);
  return c3_y;
}

static real_T c3_h_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_num_not_empty = FALSE;
  } else {
    chartInstance->c3_num_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d0;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_num;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_num = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_num), &c3_thisId);
  sf_mex_destroy(&c3_b_num);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i62;
  real_T c3_b_inData[3];
  int32_T c3_i63;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i62 = 0; c3_i62 < 3; c3_i62++) {
    c3_b_inData[c3_i62] = (*(real_T (*)[3])c3_inData)[c3_i62];
  }

  for (c3_i63 = 0; c3_i63 < 3; c3_i63++) {
    c3_u[c3_i63] = c3_b_inData[c3_i63];
  }

  c3_y = NULL;
  if (!chartInstance->c3_sensor_value_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_i_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
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

static void c3_j_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv12[3];
  int32_T c3_i64;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_sensor_value_not_empty = FALSE;
  } else {
    chartInstance->c3_sensor_value_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv12, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c3_i64 = 0; c3_i64 < 3; c3_i64++) {
      c3_y[c3_i64] = c3_dv12[c3_i64];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sensor_value;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i65;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_sensor_value = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sensor_value), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_sensor_value);
  for (c3_i65 = 0; c3_i65 < 3; c3_i65++) {
    (*(real_T (*)[3])c3_outData)[c3_i65] = c3_y[c3_i65];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i66;
  real_T c3_b_inData[3];
  int32_T c3_i67;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i66 = 0; c3_i66 < 3; c3_i66++) {
    c3_b_inData[c3_i66] = (*(real_T (*)[3])c3_inData)[c3_i66];
  }

  for (c3_i67 = 0; c3_i67 < 3; c3_i67++) {
    c3_u[c3_i67] = c3_b_inData[c3_i67];
  }

  c3_y = NULL;
  if (!chartInstance->c3_yin_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_k_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_yin, const char_T *c3_identifier, real_T
  c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_yin), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_yin);
}

static void c3_l_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv13[3];
  int32_T c3_i68;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_yin_not_empty = FALSE;
  } else {
    chartInstance->c3_yin_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv13, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c3_i68 = 0; c3_i68 < 3; c3_i68++) {
      c3_y[c3_i68] = c3_dv13[c3_i68];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_yin;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i69;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_yin = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_yin), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_yin);
  for (c3_i69 = 0; c3_i69 < 3; c3_i69++) {
    (*(real_T (*)[3])c3_outData)[c3_i69] = c3_y[c3_i69];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i70;
  real_T c3_b_inData[3];
  int32_T c3_i71;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i70 = 0; c3_i70 < 3; c3_i70++) {
    c3_b_inData[c3_i70] = (*(real_T (*)[3])c3_inData)[c3_i70];
  }

  for (c3_i71 = 0; c3_i71 < 3; c3_i71++) {
    c3_u[c3_i71] = c3_b_inData[c3_i71];
  }

  c3_y = NULL;
  if (!chartInstance->c3_delay_v_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_m_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_delay_v, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_delay_v), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_delay_v);
}

static void c3_n_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv14[3];
  int32_T c3_i72;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_delay_v_not_empty = FALSE;
  } else {
    chartInstance->c3_delay_v_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv14, 1, 0, 0U, 1, 0U, 1, 3);
    for (c3_i72 = 0; c3_i72 < 3; c3_i72++) {
      c3_y[c3_i72] = c3_dv14[c3_i72];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_delay_v;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i73;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_delay_v = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_delay_v), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_delay_v);
  for (c3_i73 = 0; c3_i73 < 3; c3_i73++) {
    (*(real_T (*)[3])c3_outData)[c3_i73] = c3_y[c3_i73];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i74;
  real_T c3_b_inData[3];
  int32_T c3_i75;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i74 = 0; c3_i74 < 3; c3_i74++) {
    c3_b_inData[c3_i74] = (*(real_T (*)[3])c3_inData)[c3_i74];
  }

  for (c3_i75 = 0; c3_i75 < 3; c3_i75++) {
    c3_u[c3_i75] = c3_b_inData[c3_i75];
  }

  c3_y = NULL;
  if (!chartInstance->c3_yin_d_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_o_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_yin_d, const char_T *c3_identifier, real_T
  c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_yin_d), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_yin_d);
}

static void c3_p_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv15[3];
  int32_T c3_i76;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_yin_d_not_empty = FALSE;
  } else {
    chartInstance->c3_yin_d_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv15, 1, 0, 0U, 1, 0U, 1, 3);
    for (c3_i76 = 0; c3_i76 < 3; c3_i76++) {
      c3_y[c3_i76] = c3_dv15[c3_i76];
    }
  }

  sf_mex_destroy(&c3_u);
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_yin_d;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i77;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_yin_d = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_yin_d), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_yin_d);
  for (c3_i77 = 0; c3_i77 < 3; c3_i77++) {
    (*(real_T (*)[3])c3_outData)[c3_i77] = c3_y[c3_i77];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  if (!chartInstance->c3_i_not_empty) {
    sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_q_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_i, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_i), &c3_thisId);
  sf_mex_destroy(&c3_b_i);
  return c3_y;
}

static real_T c3_r_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d1;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_i_not_empty = FALSE;
  } else {
    chartInstance->c3_i_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d1, 1, 0, 0U, 0, 0U, 0);
    c3_y = c3_d1;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_i;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_i = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_i), &c3_thisId);
  sf_mex_destroy(&c3_b_i);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i78;
  real_T c3_b_inData[3];
  int32_T c3_i79;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i78 = 0; c3_i78 < 3; c3_i78++) {
    c3_b_inData[c3_i78] = (*(real_T (*)[3])c3_inData)[c3_i78];
  }

  for (c3_i79 = 0; c3_i79 < 3; c3_i79++) {
    c3_u[c3_i79] = c3_b_inData[c3_i79];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_s_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_delay_vector, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_delay_vector), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_delay_vector);
}

static void c3_t_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv16[3];
  int32_T c3_i80;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv16, 1, 0, 0U, 1, 0U, 1, 3);
  for (c3_i80 = 0; c3_i80 < 3; c3_i80++) {
    c3_y[c3_i80] = c3_dv16[c3_i80];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_delay_vector;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i81;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_delay_vector = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_delay_vector), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_delay_vector);
  for (c3_i81 = 0; c3_i81 < 3; c3_i81++) {
    (*(real_T (*)[3])c3_outData)[c3_i81] = c3_y[c3_i81];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB c3_u;
  const mxArray *c3_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  real_T c3_c_u;
  const mxArray *c3_c_y = NULL;
  real_T c3_d_u;
  const mxArray *c3_d_y = NULL;
  int32_T c3_i82;
  real_T c3_e_u[3];
  const mxArray *c3_e_y = NULL;
  int32_T c3_i83;
  real_T c3_f_u[3];
  const mxArray *c3_f_y = NULL;
  int32_T c3_i84;
  real_T c3_g_u[3];
  const mxArray *c3_g_y = NULL;
  int32_T c3_i85;
  real_T c3_h_u[3];
  const mxArray *c3_h_y = NULL;
  int32_T c3_i86;
  real_T c3_i_u[5];
  const mxArray *c3_i_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(c3_struct_GS2RmkGZ5GnB7UItqpfzDB *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  c3_b_u = c3_u.i;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_addfield(c3_y, c3_b_y, "i", "i", 0);
  c3_c_u = c3_u.count;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_addfield(c3_y, c3_c_y, "count", "count", 0);
  c3_d_u = c3_u.sen_num;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_addfield(c3_y, c3_d_y, "sen_num", "sen_num", 0);
  for (c3_i82 = 0; c3_i82 < 3; c3_i82++) {
    c3_e_u[c3_i82] = c3_u.yin[c3_i82];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 1, 3),
                FALSE);
  sf_mex_addfield(c3_y, c3_e_y, "yin", "yin", 0);
  for (c3_i83 = 0; c3_i83 < 3; c3_i83++) {
    c3_f_u[c3_i83] = c3_u.yin_d[c3_i83];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 2, 3, 1),
                FALSE);
  sf_mex_addfield(c3_y, c3_f_y, "yin_d", "yin_d", 0);
  for (c3_i84 = 0; c3_i84 < 3; c3_i84++) {
    c3_g_u[c3_i84] = c3_u.delay_v[c3_i84];
  }

  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_g_u, 0, 0U, 1U, 0U, 2, 3, 1),
                FALSE);
  sf_mex_addfield(c3_y, c3_g_y, "delay_v", "delay_v", 0);
  for (c3_i85 = 0; c3_i85 < 3; c3_i85++) {
    c3_h_u[c3_i85] = c3_u.ynd_tmp[c3_i85];
  }

  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_h_u, 0, 0U, 1U, 0U, 2, 1, 3),
                FALSE);
  sf_mex_addfield(c3_y, c3_h_y, "ynd_tmp", "ynd_tmp", 0);
  for (c3_i86 = 0; c3_i86 < 5; c3_i86++) {
    c3_i_u[c3_i86] = c3_u.ranD[c3_i86];
  }

  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", c3_i_u, 0, 0U, 1U, 0U, 2, 1, 5),
                FALSE);
  sf_mex_addfield(c3_y, c3_i_y, "ranD", "ranD", 0);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_u_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB *c3_y)
{
  emlrtMsgIdentifier c3_thisId;
  static const char * c3_fieldNames[8] = { "i", "count", "sen_num", "yin",
    "yin_d", "delay_v", "ynd_tmp", "ranD" };

  c3_thisId.fParent = c3_parentId;
  sf_mex_check_struct(c3_parentId, c3_u, 8, c3_fieldNames, 0U, 0);
  c3_thisId.fIdentifier = "i";
  c3_y->i = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c3_u, "i", "i", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "count";
  c3_y->count = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c3_u, "count", "count", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "sen_num";
  c3_y->sen_num = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c3_u, "sen_num", "sen_num", 0)), &c3_thisId);
  c3_thisId.fIdentifier = "yin";
  c3_v_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u, "yin",
    "yin", 0)), &c3_thisId, c3_y->yin);
  c3_thisId.fIdentifier = "yin_d";
  c3_w_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u, "yin_d",
    "yin_d", 0)), &c3_thisId, c3_y->yin_d);
  c3_thisId.fIdentifier = "delay_v";
  c3_w_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u,
    "delay_v", "delay_v", 0)), &c3_thisId, c3_y->delay_v);
  c3_thisId.fIdentifier = "ynd_tmp";
  c3_v_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u,
    "ynd_tmp", "ynd_tmp", 0)), &c3_thisId, c3_y->ynd_tmp);
  c3_thisId.fIdentifier = "ranD";
  c3_x_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c3_u, "ranD",
    "ranD", 0)), &c3_thisId, c3_y->ranD);
  sf_mex_destroy(&c3_u);
}

static void c3_v_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv17[3];
  int32_T c3_i87;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv17, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c3_i87 = 0; c3_i87 < 3; c3_i87++) {
    c3_y[c3_i87] = c3_dv17[c3_i87];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_w_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv18[3];
  int32_T c3_i88;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv18, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c3_i88 = 0; c3_i88 < 3; c3_i88++) {
    c3_y[c3_i88] = c3_dv18[c3_i88];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_x_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[5])
{
  real_T c3_dv19[5];
  int32_T c3_i89;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv19, 1, 0, 0U, 1, 0U, 2, 1, 5);
  for (c3_i89 = 0; c3_i89 < 5; c3_i89++) {
    c3_y[c3_i89] = c3_dv19[c3_i89];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_structure;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB c3_y;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_structure = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_structure), &c3_thisId,
                        &c3_y);
  sf_mex_destroy(&c3_b_structure);
  *(c3_struct_GS2RmkGZ5GnB7UItqpfzDB *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_feval;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_feval = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_feval), &c3_thisId);
  sf_mex_destroy(&c3_feval);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i90;
  real_T c3_b_inData[3];
  int32_T c3_i91;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i90 = 0; c3_i90 < 3; c3_i90++) {
    c3_b_inData[c3_i90] = (*(real_T (*)[3])c3_inData)[c3_i90];
  }

  for (c3_i91 = 0; c3_i91 < 3; c3_i91++) {
    c3_u[c3_i91] = c3_b_inData[c3_i91];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_sensor_delay;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i92;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_sensor_delay = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_sensor_delay), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_sensor_delay);
  for (c3_i92 = 0; c3_i92 < 3; c3_i92++) {
    (*(real_T (*)[3])c3_outData)[c3_i92] = c3_y[c3_i92];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_HeatExchanger_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[32];
  const mxArray *c3_m1 = NULL;
  int32_T c3_i93;
  c3_ResolvedFunctionInfo *c3_r1;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m1, sf_mex_createstruct("nameCaptureInfo", 1, 32), FALSE);
  for (c3_i93 = 0; c3_i93 < 32; c3_i93++) {
    c3_r1 = &c3_info[c3_i93];
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", c3_r1->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r1->context)), "context", "nameCaptureInfo",
                    c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", c3_r1->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r1->name)), "name", "nameCaptureInfo", c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", c3_r1->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r1->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", c3_r1->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r1->resolved)), "resolved", "nameCaptureInfo",
                    c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", &c3_r1->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", &c3_r1->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", &c3_r1->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i93);
    sf_mex_addfield(c3_m1, sf_mex_create("nameCaptureInfo", &c3_r1->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i93);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m1, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[32])
{
  c3_info[0].context = "";
  c3_info[0].name = "mrdivide";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[0].fileTimeLo = 1357973148U;
  c3_info[0].fileTimeHi = 0U;
  c3_info[0].mFileTimeLo = 1319751566U;
  c3_info[0].mFileTimeHi = 0U;
  c3_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[1].name = "rdivide";
  c3_info[1].dominantType = "double";
  c3_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[1].fileTimeLo = 1346531988U;
  c3_info[1].fileTimeHi = 0U;
  c3_info[1].mFileTimeLo = 0U;
  c3_info[1].mFileTimeHi = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[2].name = "eml_scalexp_compatible";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c3_info[2].fileTimeLo = 1286840396U;
  c3_info[2].fileTimeHi = 0U;
  c3_info[2].mFileTimeLo = 0U;
  c3_info[2].mFileTimeHi = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[3].name = "eml_div";
  c3_info[3].dominantType = "double";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[3].fileTimeLo = 1313369410U;
  c3_info[3].fileTimeHi = 0U;
  c3_info[3].mFileTimeLo = 0U;
  c3_info[3].mFileTimeHi = 0U;
  c3_info[4].context = "";
  c3_info[4].name = "ceil";
  c3_info[4].dominantType = "double";
  c3_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c3_info[4].fileTimeLo = 1343851972U;
  c3_info[4].fileTimeHi = 0U;
  c3_info[4].mFileTimeLo = 0U;
  c3_info[4].mFileTimeHi = 0U;
  c3_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/ceil.m";
  c3_info[5].name = "eml_scalar_ceil";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_ceil.m";
  c3_info[5].fileTimeLo = 1286840320U;
  c3_info[5].fileTimeHi = 0U;
  c3_info[5].mFileTimeLo = 0U;
  c3_info[5].mFileTimeHi = 0U;
  c3_info[6].context = "";
  c3_info[6].name = "mtimes";
  c3_info[6].dominantType = "double";
  c3_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[6].fileTimeLo = 1289541292U;
  c3_info[6].fileTimeHi = 0U;
  c3_info[6].mFileTimeLo = 0U;
  c3_info[6].mFileTimeHi = 0U;
  c3_info[7].context = "";
  c3_info[7].name = "fopen";
  c3_info[7].dominantType = "char";
  c3_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fopen.m";
  c3_info[7].fileTimeLo = 1352446460U;
  c3_info[7].fileTimeHi = 0U;
  c3_info[7].mFileTimeLo = 0U;
  c3_info[7].mFileTimeHi = 0U;
  c3_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fopen.m";
  c3_info[8].name = "fileManager";
  c3_info[8].dominantType = "char";
  c3_info[8].resolved =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m";
  c3_info[8].fileTimeLo = 1354862384U;
  c3_info[8].fileTimeHi = 0U;
  c3_info[8].mFileTimeLo = 0U;
  c3_info[8].mFileTimeHi = 0U;
  c3_info[9].context =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m";
  c3_info[9].name = "coder.internal.errorIf";
  c3_info[9].dominantType = "char";
  c3_info[9].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/errorIf.m";
  c3_info[9].fileTimeLo = 1334093538U;
  c3_info[9].fileTimeHi = 0U;
  c3_info[9].mFileTimeLo = 0U;
  c3_info[9].mFileTimeHi = 0U;
  c3_info[10].context =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m!STANDALONE";
  c3_info[10].name = "isequal";
  c3_info[10].dominantType = "char";
  c3_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[10].fileTimeLo = 1286840358U;
  c3_info[10].fileTimeHi = 0U;
  c3_info[10].mFileTimeLo = 0U;
  c3_info[10].mFileTimeHi = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[11].name = "eml_isequal_core";
  c3_info[11].dominantType = "char";
  c3_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c3_info[11].fileTimeLo = 1286840386U;
  c3_info[11].fileTimeHi = 0U;
  c3_info[11].mFileTimeLo = 0U;
  c3_info[11].mFileTimeHi = 0U;
  c3_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c3_info[12].name = "isnan";
  c3_info[12].dominantType = "char";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c3_info[12].fileTimeLo = 1286840360U;
  c3_info[12].fileTimeHi = 0U;
  c3_info[12].mFileTimeLo = 0U;
  c3_info[12].mFileTimeHi = 0U;
  c3_info[13].context =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m!SFUN";
  c3_info[13].name = "isequal";
  c3_info[13].dominantType = "char";
  c3_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[13].fileTimeLo = 1286840358U;
  c3_info[13].fileTimeHi = 0U;
  c3_info[13].mFileTimeLo = 0U;
  c3_info[13].mFileTimeHi = 0U;
  c3_info[14].context =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m!filedata";
  c3_info[14].name = "repmat";
  c3_info[14].dominantType = "int8";
  c3_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c3_info[14].fileTimeLo = 1352446460U;
  c3_info[14].fileTimeHi = 0U;
  c3_info[14].mFileTimeLo = 0U;
  c3_info[14].mFileTimeHi = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c3_info[15].name = "eml_assert_valid_size_arg";
  c3_info[15].dominantType = "int8";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[15].fileTimeLo = 1286840294U;
  c3_info[15].fileTimeHi = 0U;
  c3_info[15].mFileTimeLo = 0U;
  c3_info[15].mFileTimeHi = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c3_info[16].name = "mtimes";
  c3_info[16].dominantType = "double";
  c3_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[16].fileTimeLo = 1289541292U;
  c3_info[16].fileTimeHi = 0U;
  c3_info[16].mFileTimeLo = 0U;
  c3_info[16].mFileTimeHi = 0U;
  c3_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[17].name = "eml_index_class";
  c3_info[17].dominantType = "";
  c3_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[17].fileTimeLo = 1323192178U;
  c3_info[17].fileTimeHi = 0U;
  c3_info[17].mFileTimeLo = 0U;
  c3_info[17].mFileTimeHi = 0U;
  c3_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[18].name = "intmax";
  c3_info[18].dominantType = "char";
  c3_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[18].fileTimeLo = 1311276916U;
  c3_info[18].fileTimeHi = 0U;
  c3_info[18].mFileTimeLo = 0U;
  c3_info[18].mFileTimeHi = 0U;
  c3_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c3_info[19].name = "eml_index_class";
  c3_info[19].dominantType = "";
  c3_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[19].fileTimeLo = 1323192178U;
  c3_info[19].fileTimeHi = 0U;
  c3_info[19].mFileTimeLo = 0U;
  c3_info[19].mFileTimeHi = 0U;
  c3_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c3_info[20].name = "eml_assert_valid_size_arg";
  c3_info[20].dominantType = "double";
  c3_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c3_info[20].fileTimeLo = 1286840294U;
  c3_info[20].fileTimeHi = 0U;
  c3_info[20].mFileTimeLo = 0U;
  c3_info[20].mFileTimeHi = 0U;
  c3_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c3_info[21].name = "isinf";
  c3_info[21].dominantType = "double";
  c3_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c3_info[21].fileTimeLo = 1286840360U;
  c3_info[21].fileTimeHi = 0U;
  c3_info[21].mFileTimeLo = 0U;
  c3_info[21].mFileTimeHi = 0U;
  c3_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/repmat.m";
  c3_info[22].name = "eml_index_minus";
  c3_info[22].dominantType = "coder.internal.indexInt";
  c3_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[22].fileTimeLo = 1286840378U;
  c3_info[22].fileTimeHi = 0U;
  c3_info[22].mFileTimeLo = 0U;
  c3_info[22].mFileTimeHi = 0U;
  c3_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[23].name = "eml_index_class";
  c3_info[23].dominantType = "";
  c3_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[23].fileTimeLo = 1323192178U;
  c3_info[23].fileTimeHi = 0U;
  c3_info[23].mFileTimeLo = 0U;
  c3_info[23].mFileTimeHi = 0U;
  c3_info[24].context =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m!filedata";
  c3_info[24].name = "eml_int_forloop_overflow_check";
  c3_info[24].dominantType = "";
  c3_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[24].fileTimeLo = 1346531940U;
  c3_info[24].fileTimeHi = 0U;
  c3_info[24].mFileTimeLo = 0U;
  c3_info[24].mFileTimeHi = 0U;
  c3_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c3_info[25].name = "intmax";
  c3_info[25].dominantType = "char";
  c3_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[25].fileTimeLo = 1311276916U;
  c3_info[25].fileTimeHi = 0U;
  c3_info[25].mFileTimeLo = 0U;
  c3_info[25].mFileTimeHi = 0U;
  c3_info[26].context = "";
  c3_info[26].name = "fprintf";
  c3_info[26].dominantType = "double";
  c3_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fprintf.m";
  c3_info[26].fileTimeLo = 1354862384U;
  c3_info[26].fileTimeHi = 0U;
  c3_info[26].mFileTimeLo = 0U;
  c3_info[26].mFileTimeHi = 0U;
  c3_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fprintf.m";
  c3_info[27].name = "isequal";
  c3_info[27].dominantType = "char";
  c3_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c3_info[27].fileTimeLo = 1286840358U;
  c3_info[27].fileTimeHi = 0U;
  c3_info[27].mFileTimeLo = 0U;
  c3_info[27].mFileTimeHi = 0U;
  c3_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fprintf.m!validate_arguments";
  c3_info[28].name = "coder.internal.assert";
  c3_info[28].dominantType = "char";
  c3_info[28].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m";
  c3_info[28].fileTimeLo = 1334093538U;
  c3_info[28].fileTimeHi = 0U;
  c3_info[28].mFileTimeLo = 0U;
  c3_info[28].mFileTimeHi = 0U;
  c3_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fprintf.m!check_type";
  c3_info[29].name = "coder.internal.assert";
  c3_info[29].dominantType = "char";
  c3_info[29].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m";
  c3_info[29].fileTimeLo = 1334093538U;
  c3_info[29].fileTimeHi = 0U;
  c3_info[29].mFileTimeLo = 0U;
  c3_info[29].mFileTimeHi = 0U;
  c3_info[30].context = "";
  c3_info[30].name = "fclose";
  c3_info[30].dominantType = "double";
  c3_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fclose.m";
  c3_info[30].fileTimeLo = 1352446460U;
  c3_info[30].fileTimeHi = 0U;
  c3_info[30].mFileTimeLo = 0U;
  c3_info[30].mFileTimeHi = 0U;
  c3_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/fclose.m";
  c3_info[31].name = "fileManager";
  c3_info[31].dominantType = "char";
  c3_info[31].resolved =
    "[ILXPE]$matlabroot$/toolbox/eml/lib/matlab/lang/private/fileManager.m";
  c3_info[31].fileTimeLo = 1354862384U;
  c3_info[31].fileTimeHi = 0U;
  c3_info[31].mFileTimeLo = 0U;
  c3_info[31].mFileTimeHi = 0U;
}

static real_T c3_fopen(SFc3_HeatExchangerInstanceStruct *chartInstance)
{
  return c3_fileManager(chartInstance);
}

static real_T c3_fileManager(SFc3_HeatExchangerInstanceStruct *chartInstance)
{
  real_T c3_f;
  int32_T c3_i94;
  static char_T c3_cv3[5] = { 'f', 'o', 'p', 'e', 'n' };

  char_T c3_u[5];
  const mxArray *c3_y = NULL;
  int32_T c3_i95;
  static char_T c3_filename[15] = { 's', 'e', 'n', 's', 'o', 'r', '_', 'd', 'a',
    't', 'a', '.', 't', 'x', 't' };

  char_T c3_b_u[15];
  const mxArray *c3_b_y = NULL;
  char_T c3_c_u;
  const mxArray *c3_c_y = NULL;
  c3_isequal(chartInstance);
  for (c3_i94 = 0; c3_i94 < 5; c3_i94++) {
    c3_u[c3_i94] = c3_cv3[c3_i94];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 5), FALSE);
  for (c3_i95 = 0; c3_i95 < 15; c3_i95++) {
    c3_b_u[c3_i95] = c3_filename[c3_i95];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 15),
                FALSE);
  c3_c_u = 'a';
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_c_u, 10, 0U, 0U, 0U, 0), FALSE);
  c3_f = c3_y_emlrt_marshallIn(chartInstance, sf_mex_call_debug("feval", 1U, 3U,
    14, c3_y, 14, c3_b_y, 14, c3_c_y), "feval");
  c3_filedata(chartInstance);
  return c3_f;
}

static void c3_isequal(SFc3_HeatExchangerInstanceStruct *chartInstance)
{
}

static int8_T c3_filedata(SFc3_HeatExchangerInstanceStruct *chartInstance)
{
  int8_T c3_f;
  int32_T c3_i96;
  FILE * c3_a;
  int32_T c3_i97;
  int8_T c3_k;
  int8_T c3_b_k;
  boolean_T exitg1;
  if (!chartInstance->c3_eml_openfiles_not_empty) {
    for (c3_i96 = 0; c3_i96 < 20; c3_i96++) {
      chartInstance->c3_eml_autoflush[c3_i96] = FALSE;
    }

    chartInstance->c3_eml_autoflush_not_empty = TRUE;
    c3_a = NULL;
    for (c3_i97 = 0; c3_i97 < 20; c3_i97++) {
      chartInstance->c3_eml_openfiles[c3_i97] = c3_a;
    }

    chartInstance->c3_eml_openfiles_not_empty = TRUE;
  }

  c3_f = 0;
  c3_k = 1;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (c3_k < 21)) {
    c3_b_k = c3_k;
    if (chartInstance->c3_eml_openfiles[(int8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
         (int32_T)(int8_T)_SFD_INTEGER_CHECK("", (real_T)c3_b_k), 1, 20, 1, 0) -
        1] == (FILE *)NULL) {
      c3_f = c3_b_k;
      exitg1 = TRUE;
    } else {
      c3_k++;
    }
  }

  return c3_f;
}

static void c3_fprintf(SFc3_HeatExchangerInstanceStruct *chartInstance, real_T
  c3_fileID, real_T c3_varargin_1)
{
  int32_T c3_i98;
  static char_T c3_cv4[24] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'n', 'o', 't',
    'i', 'm', 'p', 'l', 'e', 'm', 'e', 'n', 't', 'e', 'd', '_', 'm', 'x' };

  char_T c3_u[24];
  const mxArray *c3_y = NULL;
  int32_T c3_i99;
  static char_T c3_cv5[24] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'F', 'i', 'l',
    'e', 'I', 'O', ':', 'I', 'n', 'v', 'a', 'l', 'i', 'd', 'F', 'i', 'd' };

  char_T c3_b_u[24];
  const mxArray *c3_b_y = NULL;
  int32_T c3_i100;
  static char_T c3_cv6[7] = { 'f', 'p', 'r', 'i', 'n', 't', 'f' };

  char_T c3_c_u[7];
  const mxArray *c3_c_y = NULL;
  real_T c3_d_u;
  const mxArray *c3_d_y = NULL;
  int32_T c3_i101;
  static char_T c3_formatSpec[4] = { '%', 'f', '\\', 'n' };

  char_T c3_e_u[4];
  const mxArray *c3_e_y = NULL;
  real_T c3_f_u;
  const mxArray *c3_f_y = NULL;
  const mxArray *c3_cfmt = NULL;
  const mxArray *c3_convs = NULL;
  c3_isequal(chartInstance);
  if (c3_fileID != 0.0) {
  } else {
    for (c3_i98 = 0; c3_i98 < 24; c3_i98++) {
      c3_u[c3_i98] = c3_cv4[c3_i98];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 24),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
      14, c3_y));
  }

  if (c3_fileID > -1.0) {
  } else {
    for (c3_i99 = 0; c3_i99 < 24; c3_i99++) {
      c3_b_u[c3_i99] = c3_cv5[c3_i99];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 24),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
      14, c3_b_y));
  }

  for (c3_i100 = 0; c3_i100 < 7; c3_i100++) {
    c3_c_u[c3_i100] = c3_cv6[c3_i100];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_c_u, 10, 0U, 1U, 0U, 2, 1, 7),
                FALSE);
  c3_d_u = c3_fileID;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  for (c3_i101 = 0; c3_i101 < 4; c3_i101++) {
    c3_e_u[c3_i101] = c3_formatSpec[c3_i101];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_e_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  c3_f_u = c3_varargin_1;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  c3_y_emlrt_marshallIn(chartInstance, sf_mex_call_debug("feval", 1U, 4U, 14,
    c3_c_y, 14, c3_d_y, 14, c3_e_y, 14, c3_f_y), "feval");
  sf_mex_destroy(&c3_cfmt);
  sf_mex_destroy(&c3_convs);
}

static void c3_fclose(SFc3_HeatExchangerInstanceStruct *chartInstance, real_T
                      c3_fileID)
{
  c3_b_fileManager(chartInstance, c3_fileID);
}

static int32_T c3_b_fileManager(SFc3_HeatExchangerInstanceStruct *chartInstance,
  real_T c3_varargin_1)
{
  int32_T c3_f;
  real_T c3_fid;
  int32_T c3_i102;
  static char_T c3_cv7[6] = { 'f', 'c', 'l', 'o', 's', 'e' };

  char_T c3_u[6];
  const mxArray *c3_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  const mxArray *c3_failp = NULL;
  c3_fid = c3_varargin_1;
  c3_isequal(chartInstance);
  for (c3_i102 = 0; c3_i102 < 6; c3_i102++) {
    c3_u[c3_i102] = c3_cv7[c3_i102];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 6), FALSE);
  c3_b_u = c3_fid;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_failp, sf_mex_call_debug("logical", 1U, 1U, 14,
    sf_mex_call_debug("feval", 1U, 2U, 14, c3_y, 14, c3_b_y)), FALSE);
  if (c3_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_failp), "failp")) {
    c3_f = -1;
  } else {
    c3_f = 0;
  }

  sf_mex_destroy(&c3_failp);
  c3_filedata(chartInstance);
  return c3_f;
}

static real_T c3_y_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_feval, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_feval), &c3_thisId);
  sf_mex_destroy(&c3_feval);
  return c3_y;
}

static real_T c3_ab_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d2;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d2, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d2;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static boolean_T c3_bb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_failp, const char_T *c3_identifier)
{
  boolean_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_failp), &c3_thisId);
  sf_mex_destroy(&c3_failp);
  return c3_y;
}

static boolean_T c3_cb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_db_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i103;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i103, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i103;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_eb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_eml_autoflush, const char_T *c3_identifier,
  boolean_T c3_y[20])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_eml_autoflush),
    &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_eml_autoflush);
}

static void c3_fb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  boolean_T c3_y[20])
{
  boolean_T c3_bv1[20];
  int32_T c3_i104;
  if (mxIsEmpty(c3_u)) {
    chartInstance->c3_eml_autoflush_not_empty = FALSE;
  } else {
    chartInstance->c3_eml_autoflush_not_empty = TRUE;
    sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_bv1, 1, 11, 0U, 1, 0U, 1, 20);
    for (c3_i104 = 0; c3_i104 < 20; c3_i104++) {
      c3_y[c3_i104] = c3_bv1[c3_i104];
    }
  }

  sf_mex_destroy(&c3_u);
}

static uint8_T c3_gb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_HeatExchanger, const char_T
  *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_hb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_HeatExchanger), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_HeatExchanger);
  return c3_y;
}

static uint8_T c3_hb_emlrt_marshallIn(SFc3_HeatExchangerInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_HeatExchangerInstanceStruct
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

void sf_c3_HeatExchanger_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3180507337U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(684453185U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1353982528U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(385827830U);
}

mxArray *sf_c3_HeatExchanger_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ujIXvZdAVH1DvNatdVbIqG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_HeatExchanger_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c3_HeatExchanger(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[14],T\"delay_vector\",},{M[1],M[5],T\"signal_vector\",},{M[4],M[0],T\"delay_v\",S'l','i','p'{{M1x2[364 371],M[0],}}},{M[4],M[0],T\"eml_autoflush\",S'l','i','p'{{M1x2[7051 7064],M[1],T\"C:/Program Files/MATLAB/R2013a/toolbox/eml/lib/matlab/lang/private/fileManager.m\"}}},{M[4],M[0],T\"i\",S'l','i','p'{{M1x2[356 357],M[0],}}},{M[4],M[0],T\"last_senDelay\",S'l','i','p'{{M1x2[439 452],M[0],}}},{M[4],M[0],T\"last_senReading\",S'l','i','p'{{M1x2[423 438],M[0],}}},{M[4],M[0],T\"num\",S'l','i','p'{{M1x2[400 403],M[0],}}},{M[4],M[0],T\"sensor_value\",S'l','i','p'{{M1x2[387 399],M[0],}}},{M[4],M[0],T\"yin\",S'l','i','p'{{M1x2[383 386],M[0],}}}}",
    "100 S1x3'type','srcId','name','auxInfo'{{M[4],M[0],T\"yin_d\",S'l','i','p'{{M1x2[358 363],M[0],}}},{M[4],M[0],T\"ynd_tmp\",S'l','i','p'{{M1x2[404 411],M[0],}}},{M[8],M[0],T\"is_active_c3_HeatExchanger\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 13, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_HeatExchanger_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_HeatExchangerInstanceStruct *chartInstance;
    chartInstance = (SFc3_HeatExchangerInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _HeatExchangerMachineNumber_,
           3,
           1,
           1,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_HeatExchangerMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_HeatExchangerMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _HeatExchangerMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"yactual_value");
          _SFD_SET_DATA_PROPS(1,1,1,0,"ysensor_value");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ynetwork_delay");
          _SFD_SET_DATA_PROPS(3,2,0,1,"signal_vector");
          _SFD_SET_DATA_PROPS(4,10,0,0,"structure");
          _SFD_SET_DATA_PROPS(5,2,0,1,"delay_vector");
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
        _SFD_CV_INIT_EML(0,1,1,6,0,0,0,3,0,8,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3420);
        _SFD_CV_INIT_EML_IF(0,1,0,633,648,-1,1194);
        _SFD_CV_INIT_EML_IF(0,1,1,1483,1494,-1,1883);
        _SFD_CV_INIT_EML_IF(0,1,2,1588,1698,1758,1839);
        _SFD_CV_INIT_EML_IF(0,1,3,1944,1968,2437,2712);
        _SFD_CV_INIT_EML_IF(0,1,4,2080,2186,2244,2323);
        _SFD_CV_INIT_EML_IF(0,1,5,2450,2458,-1,2696);
        _SFD_CV_INIT_EML_FOR(0,1,0,1499,1512,1878);
        _SFD_CV_INIT_EML_FOR(0,1,1,1930,1940,2716);
        _SFD_CV_INIT_EML_FOR(0,1,2,2734,2747,2888);

        {
          static int condStart[] = { 1591, 1618, 1646, 1673 };

          static int condEnd[] = { 1614, 1642, 1669, 1698 };

          static int pfixExpr[] = { 0, 1, -2, 2, -2, 3, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,1591,1698,4,0,&(condStart[0]),&(condEnd[0]),
                                7,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2083, 2109, 2136, 2162 };

          static int condEnd[] = { 2105, 2132, 2158, 2186 };

          static int pfixExpr[] = { 0, 1, -2, 2, -2, 3, -2 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,2083,2186,4,4,&(condStart[0]),&(condEnd[0]),
                                7,&(pfixExpr[0]));
        }

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
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)
            c3_j_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_k_sf_marshallOut,(MexInFcnForType)c3_k_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)
            c3_j_sf_marshallIn);
        }

        {
          real_T (*c3_yactual_value)[3];
          real_T (*c3_ysensor_value)[3];
          real_T (*c3_ynetwork_delay)[3];
          real_T (*c3_signal_vector)[3];
          real_T (*c3_delay_vector)[3];
          c3_delay_vector = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 2);
          c3_signal_vector = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c3_ynetwork_delay = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 2);
          c3_ysensor_value = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 1);
          c3_yactual_value = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_yactual_value);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_ysensor_value);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_ynetwork_delay);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_signal_vector);
          _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c3_structure);
          _SFD_SET_DATA_VALUE_PTR(5U, *c3_delay_vector);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _HeatExchangerMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "kMofQ4nlNXKmRdNdTs0hyG";
}

static void sf_opaque_initialize_c3_HeatExchanger(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_HeatExchangerInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
    chartInstanceVar);
  initialize_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_HeatExchanger(void *chartInstanceVar)
{
  enable_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_HeatExchanger(void *chartInstanceVar)
{
  disable_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_HeatExchanger(void *chartInstanceVar)
{
  sf_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_HeatExchanger(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_HeatExchanger
    ((SFc3_HeatExchangerInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_HeatExchanger();/* state var info */
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

extern void sf_internal_set_sim_state_c3_HeatExchanger(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_HeatExchanger();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_HeatExchanger(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_HeatExchanger(S);
}

static void sf_opaque_set_sim_state_c3_HeatExchanger(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c3_HeatExchanger(S, st);
}

static void sf_opaque_terminate_c3_HeatExchanger(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_HeatExchangerInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_HeatExchanger_optimization_info();
    }

    finalize_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_HeatExchanger(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_HeatExchanger((SFc3_HeatExchangerInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_HeatExchanger(SimStruct *S)
{
  /* Actual parameters from chart:
     structure
   */
  const char_T *rtParamNames[] = { "structure" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0],
    sf_get_param_data_type_id(S,0));
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_HeatExchanger_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2522913044U));
  ssSetChecksum1(S,(2035675049U));
  ssSetChecksum2(S,(1608022703U));
  ssSetChecksum3(S,(2222099063U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetSimStateCompliance(S, DISALLOW_SIM_STATE);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_HeatExchanger(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_HeatExchanger(SimStruct *S)
{
  SFc3_HeatExchangerInstanceStruct *chartInstance;
  chartInstance = (SFc3_HeatExchangerInstanceStruct *)utMalloc(sizeof
    (SFc3_HeatExchangerInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_HeatExchangerInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_HeatExchanger;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_HeatExchanger;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_HeatExchanger;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_HeatExchanger;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_HeatExchanger;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_HeatExchanger;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_HeatExchanger;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_HeatExchanger;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_HeatExchanger;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_HeatExchanger;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_HeatExchanger;
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

void c3_HeatExchanger_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_HeatExchanger(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_HeatExchanger(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_HeatExchanger(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_HeatExchanger_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
