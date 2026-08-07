/*
 * File: any.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

/* Include Files */
#include "any.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const bool x[6]
 * Return Type  : bool
 */
bool any(const bool x[6])
{
  int k;
  bool exitg1;
  bool y;
  y = false;
  k = 0;
  exitg1 = false;
  while (!exitg1 && (k < 6)) {
    if (x[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  return y;
}

/*
 * File trailer for any.c
 *
 * [EOF]
 */
