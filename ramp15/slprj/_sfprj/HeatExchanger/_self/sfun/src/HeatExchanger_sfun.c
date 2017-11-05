/* Include files */

#include "HeatExchanger_sfun.h"
#include "HeatExchanger_sfun_debug_macros.h"
#include "c1_HeatExchanger.h"
#include "c2_HeatExchanger.h"
#include "c3_HeatExchanger.h"
#include "c4_HeatExchanger.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _HeatExchangerMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void HeatExchanger_initializer(void)
{
}

void HeatExchanger_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_HeatExchanger_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_HeatExchanger_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_HeatExchanger_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_HeatExchanger_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_HeatExchanger_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_HeatExchanger_process_check_sum_call( int nlhs, mxArray * plhs[],
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
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3487768889U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2833919940U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1942301138U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2827190773U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1991437916U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1559643357U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2785415556U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2100835998U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_HeatExchanger_get_check_sum(mxArray *plhs[]);
          sf_c1_HeatExchanger_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_HeatExchanger_get_check_sum(mxArray *plhs[]);
          sf_c2_HeatExchanger_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_HeatExchanger_get_check_sum(mxArray *plhs[]);
          sf_c3_HeatExchanger_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_HeatExchanger_get_check_sum(mxArray *plhs[]);
          sf_c4_HeatExchanger_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3564696471U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(678668628U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1090454852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3896867807U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2976213609U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3863545956U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3722951651U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2440937285U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_HeatExchanger_autoinheritance_info( int nlhs, mxArray * plhs[],
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
        if (strcmp(aiChksum, "35BW48TbPxkHqyFew5UFE") == 0) {
          extern mxArray *sf_c1_HeatExchanger_get_autoinheritance_info(void);
          plhs[0] = sf_c1_HeatExchanger_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "Mj2T6J2ySKGc8TQguP3unD") == 0) {
          extern mxArray *sf_c2_HeatExchanger_get_autoinheritance_info(void);
          plhs[0] = sf_c2_HeatExchanger_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "ujIXvZdAVH1DvNatdVbIqG") == 0) {
          extern mxArray *sf_c3_HeatExchanger_get_autoinheritance_info(void);
          plhs[0] = sf_c3_HeatExchanger_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "jC8Lmds3dEns5Z4bICwAjC") == 0) {
          extern mxArray *sf_c4_HeatExchanger_get_autoinheritance_info(void);
          plhs[0] = sf_c4_HeatExchanger_get_autoinheritance_info();
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

unsigned int sf_HeatExchanger_get_eml_resolved_functions_info( int nlhs, mxArray
  * plhs[], int nrhs, const mxArray * prhs[] )
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
        extern const mxArray
          *sf_c1_HeatExchanger_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_HeatExchanger_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_HeatExchanger_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_HeatExchanger_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_HeatExchanger_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_HeatExchanger_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_HeatExchanger_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_HeatExchanger_get_eml_resolved_functions_info();
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

unsigned int sf_HeatExchanger_third_party_uses_info( int nlhs, mxArray * plhs[],
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
        if (strcmp(tpChksum, "vvjMRfYzMJ2qTKlv2fFX8G") == 0) {
          extern mxArray *sf_c1_HeatExchanger_third_party_uses_info(void);
          plhs[0] = sf_c1_HeatExchanger_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "AHtGh4GHQ0zRcxZzPkWbeF") == 0) {
          extern mxArray *sf_c2_HeatExchanger_third_party_uses_info(void);
          plhs[0] = sf_c2_HeatExchanger_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "kMofQ4nlNXKmRdNdTs0hyG") == 0) {
          extern mxArray *sf_c3_HeatExchanger_third_party_uses_info(void);
          plhs[0] = sf_c3_HeatExchanger_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "qxkDjtHUHMyJUIa0CuOOmH") == 0) {
          extern mxArray *sf_c4_HeatExchanger_third_party_uses_info(void);
          plhs[0] = sf_c4_HeatExchanger_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void HeatExchanger_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _HeatExchangerMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "HeatExchanger","sfun",0,4,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _HeatExchangerMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _HeatExchangerMachineNumber_,0);
}

void HeatExchanger_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_HeatExchanger_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("HeatExchanger",
      "HeatExchanger");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_HeatExchanger_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
