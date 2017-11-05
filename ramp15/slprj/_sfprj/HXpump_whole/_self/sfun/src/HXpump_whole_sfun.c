/* Include files */

#include "HXpump_whole_sfun.h"
#include "HXpump_whole_sfun_debug_macros.h"
#include "c1_HXpump_whole.h"
#include "c2_HXpump_whole.h"
#include "c3_HXpump_whole.h"
#include "c4_HXpump_whole.h"
#include "c5_HXpump_whole.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _HXpump_wholeMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void HXpump_whole_initializer(void)
{
}

void HXpump_whole_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_HXpump_whole_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_HXpump_whole_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_HXpump_whole_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_HXpump_whole_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_HXpump_whole_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_HXpump_whole_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

extern void sf_HXpump_whole_uses_exported_functions(int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[])
{
  plhs[0] = mxCreateLogicalScalar(0);
}

unsigned int sf_HXpump_whole_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(189111616U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4261313529U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3978789033U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1891990642U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1965191117U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(976033033U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4166711139U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3763331981U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_HXpump_whole_get_check_sum(mxArray *plhs[]);
          sf_c1_HXpump_whole_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_HXpump_whole_get_check_sum(mxArray *plhs[]);
          sf_c2_HXpump_whole_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_HXpump_whole_get_check_sum(mxArray *plhs[]);
          sf_c3_HXpump_whole_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_HXpump_whole_get_check_sum(mxArray *plhs[]);
          sf_c4_HXpump_whole_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_HXpump_whole_get_check_sum(mxArray *plhs[]);
          sf_c5_HXpump_whole_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2515920432U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3908508645U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2530489944U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2924353608U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2118844682U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3413285643U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2340085728U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(655256496U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_HXpump_whole_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "ZRgtdwPW6FfSyO1xqeBiOH") == 0) {
          extern mxArray *sf_c1_HXpump_whole_get_autoinheritance_info(void);
          plhs[0] = sf_c1_HXpump_whole_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "T1NfobBlDdh2A5ceXqkM1C") == 0) {
          extern mxArray *sf_c2_HXpump_whole_get_autoinheritance_info(void);
          plhs[0] = sf_c2_HXpump_whole_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "SWjLFZtCmmBwv6QAw8wUvH") == 0) {
          extern mxArray *sf_c3_HXpump_whole_get_autoinheritance_info(void);
          plhs[0] = sf_c3_HXpump_whole_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "ZFsODYu5PVoiOexnItATcH") == 0) {
          extern mxArray *sf_c4_HXpump_whole_get_autoinheritance_info(void);
          plhs[0] = sf_c4_HXpump_whole_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "qKiNTc4ipzhiXDpmOoFwz") == 0) {
          extern mxArray *sf_c5_HXpump_whole_get_autoinheritance_info(void);
          plhs[0] = sf_c5_HXpump_whole_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_HXpump_whole_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_HXpump_whole_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_HXpump_whole_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_HXpump_whole_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_HXpump_whole_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_HXpump_whole_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_HXpump_whole_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_HXpump_whole_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_HXpump_whole_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_HXpump_whole_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_HXpump_whole_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_HXpump_whole_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "QhGQtGssuPCPIG5D3t1UaC") == 0) {
          extern mxArray *sf_c1_HXpump_whole_third_party_uses_info(void);
          plhs[0] = sf_c1_HXpump_whole_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "jYcEyh536gMNMXnvZiVGoE") == 0) {
          extern mxArray *sf_c2_HXpump_whole_third_party_uses_info(void);
          plhs[0] = sf_c2_HXpump_whole_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "1IViTdExFIBhov19kFFzNH") == 0) {
          extern mxArray *sf_c3_HXpump_whole_third_party_uses_info(void);
          plhs[0] = sf_c3_HXpump_whole_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "39kZDaXXgByi2Jxd9oP43") == 0) {
          extern mxArray *sf_c4_HXpump_whole_third_party_uses_info(void);
          plhs[0] = sf_c4_HXpump_whole_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "vQSFcQuZtnWGKN7rZqKVbC") == 0) {
          extern mxArray *sf_c5_HXpump_whole_third_party_uses_info(void);
          plhs[0] = sf_c5_HXpump_whole_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_HXpump_whole_jit_fallback_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "QhGQtGssuPCPIG5D3t1UaC") == 0) {
          extern mxArray *sf_c1_HXpump_whole_jit_fallback_info(void);
          plhs[0] = sf_c1_HXpump_whole_jit_fallback_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "jYcEyh536gMNMXnvZiVGoE") == 0) {
          extern mxArray *sf_c2_HXpump_whole_jit_fallback_info(void);
          plhs[0] = sf_c2_HXpump_whole_jit_fallback_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "1IViTdExFIBhov19kFFzNH") == 0) {
          extern mxArray *sf_c3_HXpump_whole_jit_fallback_info(void);
          plhs[0] = sf_c3_HXpump_whole_jit_fallback_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "39kZDaXXgByi2Jxd9oP43") == 0) {
          extern mxArray *sf_c4_HXpump_whole_jit_fallback_info(void);
          plhs[0] = sf_c4_HXpump_whole_jit_fallback_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "vQSFcQuZtnWGKN7rZqKVbC") == 0) {
          extern mxArray *sf_c5_HXpump_whole_jit_fallback_info(void);
          plhs[0] = sf_c5_HXpump_whole_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_HXpump_whole_updateBuildInfo_args_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "QhGQtGssuPCPIG5D3t1UaC") == 0) {
          extern mxArray *sf_c1_HXpump_whole_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_HXpump_whole_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "jYcEyh536gMNMXnvZiVGoE") == 0) {
          extern mxArray *sf_c2_HXpump_whole_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_HXpump_whole_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "1IViTdExFIBhov19kFFzNH") == 0) {
          extern mxArray *sf_c3_HXpump_whole_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_HXpump_whole_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "39kZDaXXgByi2Jxd9oP43") == 0) {
          extern mxArray *sf_c4_HXpump_whole_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_HXpump_whole_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "vQSFcQuZtnWGKN7rZqKVbC") == 0) {
          extern mxArray *sf_c5_HXpump_whole_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_HXpump_whole_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void sf_HXpump_whole_get_post_codegen_info( int nlhs, mxArray * plhs[], int nrhs,
  const mxArray * prhs[] )
{
  unsigned int chartFileNumber = (unsigned int) mxGetScalar(prhs[0]);
  char tpChksum[64];
  mxGetString(prhs[1], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  switch (chartFileNumber) {
   case 1:
    {
      if (strcmp(tpChksum, "QhGQtGssuPCPIG5D3t1UaC") == 0) {
        extern mxArray *sf_c1_HXpump_whole_get_post_codegen_info(void);
        plhs[0] = sf_c1_HXpump_whole_get_post_codegen_info();
        return;
      }
    }
    break;

   case 2:
    {
      if (strcmp(tpChksum, "jYcEyh536gMNMXnvZiVGoE") == 0) {
        extern mxArray *sf_c2_HXpump_whole_get_post_codegen_info(void);
        plhs[0] = sf_c2_HXpump_whole_get_post_codegen_info();
        return;
      }
    }
    break;

   case 3:
    {
      if (strcmp(tpChksum, "1IViTdExFIBhov19kFFzNH") == 0) {
        extern mxArray *sf_c3_HXpump_whole_get_post_codegen_info(void);
        plhs[0] = sf_c3_HXpump_whole_get_post_codegen_info();
        return;
      }
    }
    break;

   case 4:
    {
      if (strcmp(tpChksum, "39kZDaXXgByi2Jxd9oP43") == 0) {
        extern mxArray *sf_c4_HXpump_whole_get_post_codegen_info(void);
        plhs[0] = sf_c4_HXpump_whole_get_post_codegen_info();
        return;
      }
    }
    break;

   case 5:
    {
      if (strcmp(tpChksum, "vQSFcQuZtnWGKN7rZqKVbC") == 0) {
        extern mxArray *sf_c5_HXpump_whole_get_post_codegen_info(void);
        plhs[0] = sf_c5_HXpump_whole_get_post_codegen_info();
        return;
      }
    }
    break;

   default:
    break;
  }

  plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
}

void HXpump_whole_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _HXpump_wholeMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "HXpump_whole","sfun",0,5,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _HXpump_wholeMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_HXpump_wholeMachineNumber_,
    0);
}

void HXpump_whole_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_HXpump_whole_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("HXpump_whole",
      "HXpump_whole");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_HXpump_whole_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
