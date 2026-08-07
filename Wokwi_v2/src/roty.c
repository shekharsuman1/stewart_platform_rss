/*
 * File: roty.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

/* Include Files */
#include "roty.h"
#include "cosd.h"
#include "rt_nonfinite.h"
#include "sind.h"

/* Function Definitions */
/*
 * Arguments    : double beta
 *                double rotmat[9]
 * Return Type  : void
 */
void roty(double beta, double rotmat[9])
{
  double b_rotmat_tmp;
  double rotmat_tmp;
  rotmat_tmp = beta;
  b_sind(&rotmat_tmp);
  b_rotmat_tmp = beta;
  b_cosd(&b_rotmat_tmp);
  rotmat[0] = b_rotmat_tmp;
  rotmat[3] = 0.0;
  rotmat[6] = rotmat_tmp;
  rotmat[1] = 0.0;
  rotmat[4] = 1.0;
  rotmat[7] = 0.0;
  rotmat[2] = -rotmat_tmp;
  rotmat[5] = 0.0;
  rotmat[8] = b_rotmat_tmp;
}

/*
 * File trailer for roty.c
 *
 * [EOF]
 */
