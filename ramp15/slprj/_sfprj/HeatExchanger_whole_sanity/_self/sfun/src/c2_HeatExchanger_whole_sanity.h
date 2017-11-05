#ifndef __c2_HeatExchanger_whole_sanity_h__
#define __c2_HeatExchanger_whole_sanity_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_HeatExchanger_whole_sanityInstanceStruct
#define typedef_SFc2_HeatExchanger_whole_sanityInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_HeatExchanger_whole_sanity;
} SFc2_HeatExchanger_whole_sanityInstanceStruct;

#endif                                 /*typedef_SFc2_HeatExchanger_whole_sanityInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_HeatExchanger_whole_sanity_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_HeatExchanger_whole_sanity_get_check_sum(mxArray *plhs[]);
extern void c2_HeatExchanger_whole_sanity_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
