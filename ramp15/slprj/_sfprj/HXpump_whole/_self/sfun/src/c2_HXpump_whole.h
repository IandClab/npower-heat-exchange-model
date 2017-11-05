#ifndef __c2_HXpump_whole_h__
#define __c2_HXpump_whole_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_HXpump_wholeInstanceStruct
#define typedef_SFc2_HXpump_wholeInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_HXpump_whole;
  real_T (*c2_xin)[4];
  real_T (*c2_xout)[4];
  real_T (*c2_hotpar)[6];
  real_T (*c2_coldpar)[4];
  real_T (*c2_wallpar)[4];
  real_T (*c2_pumpar)[3];
  real_T (*c2_input)[2];
  real_T *c2_simpar;
  real_T (*c2_noise)[6];
  real_T (*c2_yout)[3];
} SFc2_HXpump_wholeInstanceStruct;

#endif                                 /*typedef_SFc2_HXpump_wholeInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_HXpump_whole_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_HXpump_whole_get_check_sum(mxArray *plhs[]);
extern void c2_HXpump_whole_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
