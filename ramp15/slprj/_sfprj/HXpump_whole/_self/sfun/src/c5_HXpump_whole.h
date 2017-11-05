#ifndef __c5_HXpump_whole_h__
#define __c5_HXpump_whole_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc5_HXpump_wholeInstanceStruct
#define typedef_SFc5_HXpump_wholeInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_isStable;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_HXpump_whole;
  real_T *c5_u;
  real_T *c5_y;
} SFc5_HXpump_wholeInstanceStruct;

#endif                                 /*typedef_SFc5_HXpump_wholeInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_HXpump_whole_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_HXpump_whole_get_check_sum(mxArray *plhs[]);
extern void c5_HXpump_whole_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
