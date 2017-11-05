#ifndef __c3_HeatExchanger_h__
#define __c3_HeatExchanger_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#include <stdio.h>
#ifndef typedef_c3_ResolvedFunctionInfo
#define typedef_c3_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c3_ResolvedFunctionInfo;

#endif                                 /*typedef_c3_ResolvedFunctionInfo*/

#ifndef struct_struct_GS2RmkGZ5GnB7UItqpfzDB_tag
#define struct_struct_GS2RmkGZ5GnB7UItqpfzDB_tag

struct struct_GS2RmkGZ5GnB7UItqpfzDB_tag
{
  real_T i;
  real_T count;
  real_T sen_num;
  real_T yin[3];
  real_T yin_d[3];
  real_T delay_v[3];
  real_T ynd_tmp[3];
  real_T ranD[5];
};

#endif                                 /*struct_struct_GS2RmkGZ5GnB7UItqpfzDB_tag*/

#ifndef typedef_c3_struct_GS2RmkGZ5GnB7UItqpfzDB
#define typedef_c3_struct_GS2RmkGZ5GnB7UItqpfzDB

typedef struct struct_GS2RmkGZ5GnB7UItqpfzDB_tag
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB;

#endif                                 /*typedef_c3_struct_GS2RmkGZ5GnB7UItqpfzDB*/

#ifndef typedef_SFc3_HeatExchangerInstanceStruct
#define typedef_SFc3_HeatExchangerInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_HeatExchanger;
  c3_struct_GS2RmkGZ5GnB7UItqpfzDB c3_structure;
  real_T c3_i;
  boolean_T c3_i_not_empty;
  real_T c3_yin_d[3];
  boolean_T c3_yin_d_not_empty;
  real_T c3_delay_v[3];
  boolean_T c3_delay_v_not_empty;
  real_T c3_yin[3];
  boolean_T c3_yin_not_empty;
  real_T c3_sensor_value[3];
  boolean_T c3_sensor_value_not_empty;
  real_T c3_num;
  boolean_T c3_num_not_empty;
  real_T c3_ynd_tmp[3];
  boolean_T c3_ynd_tmp_not_empty;
  real_T c3_last_senReading[9];
  boolean_T c3_last_senReading_not_empty;
  real_T c3_last_senDelay[9];
  boolean_T c3_last_senDelay_not_empty;
  FILE * c3_eml_openfiles[20];
  boolean_T c3_eml_openfiles_not_empty;
  boolean_T c3_eml_autoflush[20];
  boolean_T c3_eml_autoflush_not_empty;
} SFc3_HeatExchangerInstanceStruct;

#endif                                 /*typedef_SFc3_HeatExchangerInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_HeatExchanger_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_HeatExchanger_get_check_sum(mxArray *plhs[]);
extern void c3_HeatExchanger_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
