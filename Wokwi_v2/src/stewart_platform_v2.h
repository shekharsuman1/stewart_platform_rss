/*
 * File: stewart_platform_v2.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

#ifndef STEWART_PLATFORM_V2_H
#define STEWART_PLATFORM_V2_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void stewart_platform_v2(double yaw, double pitch, double roll,
                                double dx, double dy, double dz,
                                double final_angle[6]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for stewart_platform_v2.h
 *
 * [EOF]
 */
