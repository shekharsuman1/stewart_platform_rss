/*
 * File: _coder_stewart_platform_v2_api.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

#ifndef _CODER_STEWART_PLATFORM_V2_API_H
#define _CODER_STEWART_PLATFORM_V2_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void stewart_platform_v2(real_T yaw, real_T pitch, real_T roll, real_T dx,
                         real_T dy, real_T dz, real_T final_angle[6]);

void stewart_platform_v2_api(const mxArray *const prhs[6],
                             const mxArray **plhs);

void stewart_platform_v2_atexit(void);

void stewart_platform_v2_initialize(void);

void stewart_platform_v2_terminate(void);

void stewart_platform_v2_xil_shutdown(void);

void stewart_platform_v2_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_stewart_platform_v2_api.h
 *
 * [EOF]
 */
