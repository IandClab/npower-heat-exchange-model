#ifndef __c3_HXpump_whole_sanity_h__
#define __c3_HXpump_whole_sanity_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_HXpump_whole_sanityInstanceStruct
#define typedef_SFc3_HXpump_whole_sanityInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_HXpump_whole_sanity;
  real_T c3_sensor_value[3];
  boolean_T c3_sensor_value_not_empty;
  real_T c3_i;
  boolean_T c3_i_not_empty;
  real_T c3_network_array[18006];
  boolean_T c3_network_array_not_empty;
} SFc3_HXpump_whole_sanityInstanceStruct;

#endif                                 /*typedef_SFc3_HXpump_whole_sanityInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_HXpump_whole_sanity_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c3_HXpump_whole_sanity_get_check_sum(mxArray *plhs[]);
extern void c3_HXpump_whole_sanity_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
