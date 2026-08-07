/*
 * File: rotz.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

/* Include Files */
#include "rotz.h"
#include "cosd.h"
#include "rt_nonfinite.h"
#include "sind.h"

/* Function Definitions */
/*
 * Arguments    : double b_gamma
 *                double rotmat[9]
 * Return Type  : void
 */
void rotz(double b_gamma, double rotmat[9])
{
  double b_rotmat_tmp;
  double rotmat_tmp;
  rotmat_tmp = b_gamma;
  b_sind(&rotmat_tmp);
  b_rotmat_tmp = b_gamma;
  b_cosd(&b_rotmat_tmp);
  rotmat[0] = b_rotmat_tmp;
  rotmat[3] = -rotmat_tmp;
  rotmat[6] = 0.0;
  rotmat[1] = rotmat_tmp;
  rotmat[4] = b_rotmat_tmp;
  rotmat[7] = 0.0;
  rotmat[2] = 0.0;
  rotmat[5] = 0.0;
  rotmat[8] = 1.0;
}

/*
 * File trailer for rotz.c
 *
 * [EOF]
 */
