/*
 * File: rotx.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

/* Include Files */
#include "rotx.h"
#include "cosd.h"
#include "rt_nonfinite.h"
#include "sind.h"

/* Function Definitions */
/*
 * Arguments    : double alpha
 *                double rotmat[9]
 * Return Type  : void
 */
void rotx(double alpha, double rotmat[9])
{
  double b_rotmat_tmp;
  double rotmat_tmp;
  rotmat_tmp = alpha;
  b_sind(&rotmat_tmp);
  b_rotmat_tmp = alpha;
  b_cosd(&b_rotmat_tmp);
  rotmat[0] = 1.0;
  rotmat[3] = 0.0;
  rotmat[6] = 0.0;
  rotmat[1] = 0.0;
  rotmat[4] = b_rotmat_tmp;
  rotmat[7] = -rotmat_tmp;
  rotmat[2] = 0.0;
  rotmat[5] = rotmat_tmp;
  rotmat[8] = b_rotmat_tmp;
}

/*
 * File trailer for rotx.c
 *
 * [EOF]
 */
