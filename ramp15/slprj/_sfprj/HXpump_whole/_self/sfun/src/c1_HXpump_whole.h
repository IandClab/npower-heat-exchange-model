#ifndef __c1_HXpump_whole_h__
#define __c1_HXpump_whole_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_HXpump_wholeInstanceStruct
#define typedef_SFc1_HXpump_wholeInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_HXpump_whole;
  real_T (*c1_xhatin)[6];
  real_T (*c1_hotpar)[6];
  real_T (*c1_coldpar)[4];
  real_T (*c1_wallpar)[4];
  real_T (*c1_pumppar)[3];
  real_T (*c1_input)[2];
  real_T *c1_simpar;
  real_T (*c1_y)[3];
  real_T (*c1_ys)[3];
  real_T (*c1_noisePSD)[6];
  real_T (*c1_Pin)[36];
  real_T (*c1_xhatout)[6];
  real_T (*c1_yhatout)[3];
  real_T (*c1_Pout)[36];
} SFc1_HXpump_wholeInstanceStruct;

#endif                                 /*typedef_SFc1_HXpump_wholeInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_HXpump_whole_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_HXpump_whole_get_check_sum(mxArray *plhs[]);
extern void c1_HXpump_whole_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
