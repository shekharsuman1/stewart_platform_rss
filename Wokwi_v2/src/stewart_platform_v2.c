/*
 * File: stewart_platform_v2.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Jul-2026 12:51:27
 */

/* Include Files */
#include "stewart_platform_v2.h"
#include "any.h"
#include "rotx.h"
#include "roty.h"
#include "rotz.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    double d;
    y = fabs(u0);
    d = fabs(u1);
    if (rtIsInf(u1)) {
      if (y == 1.0) {
        y = 1.0;
      } else if (y > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d == 0.0) {
      y = 1.0;
    } else if (d == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * This directive forces MATLAB to check for C-compatibility in real-time.
 *
 * Arguments    : double yaw
 *                double pitch
 *                double roll
 *                double dx
 *                double dy
 *                double dz
 *                double final_angle[6]
 * Return Type  : void
 */
void stewart_platform_v2(double yaw, double pitch, double roll, double dx,
                         double dy, double dz, double final_angle[6])
{
  static const double rotation_matrices[96] = {
      -1.0,   0.0,    0.0,  0.0, 0.0,       0.0,     1.0,  0.0,
      0.0,    1.0,    0.0,  0.0, 42.735,    -115.0,  10.0, 1.0,
      1.0,    0.0,    0.0,  0.0, 0.0,       0.0,     1.0,  0.0,
      0.0,    -1.0,   0.0,  0.0, -42.735,   -115.0,  10.0, 1.0,
      0.5,    0.866,  0.0,  0.0, -0.0,      0.0,     1.0,  0.0,
      0.866,  -0.5,   0.0,  0.0, -120.9604, 20.4904, 10.0, 1.0,
      -0.5,   -0.866, 0.0,  0.0, 0.0,       0.0,     1.0,  0.0,
      -0.866, 0.5,    0.0,  0.0, -78.2254,  94.5096, 10.0, 1.0,
      0.5,    -0.866, 0.0,  0.0, 0.0,       0.0,     1.0,  0.0,
      -0.866, -0.5,   0.0,  0.0, 78.2254,   94.5096, 10.0, 1.0,
      -0.5,   0.866,  -0.0, 0.0, -0.0,      0.0,     1.0,  0.0,
      0.866,  0.5,    0.0,  0.0, 120.9604,  20.4904, 10.0, 1.0};
  static const double dv5[18] = {43.2,   -35.18, -2.5, -43.2, -35.18, -2.5,
                                 -52.07, -19.82, -2.5, -8.87, 55.0,   -2.5,
                                 8.87,   55.0,   -2.5, 52.07, -19.82, -2.5};
  double dv4[18];
  double translatedPlatform[18];
  double dv[9];
  double dv1[9];
  double dv2[9];
  double dv3[9];
  double theta_NR[6];
  double b_dx[3];
  double solution_new;
  double u;
  double v;
  int b_i;
  int counter;
  int i;
  int i1;
  bool bv[6];
  bool exitg1;
  /*  Preallocation & Structural Layout */
  for (i = 0; i < 6; i++) {
    final_angle[i] = rtNaN;
    theta_NR[i] = rtNaN;
  }
  /*  Platform coordinates in the platform frame */
  /*  1. Platform Orientation & Translation */
  /*  Apply rotation and translate platform to the base frame */
  /*  Base offset distance in z-direction (240.33) added to your input dz */
  rotz(yaw, dv);
  roty(pitch, dv1);
  rotx(roll, dv2);
  memset(&dv3[0], 0, 9U * sizeof(double));
  for (i = 0; i < 3; i++) {
    u = dv3[3 * i];
    b_i = 3 * i + 1;
    counter = 3 * i + 2;
    for (i1 = 0; i1 < 3; i1++) {
      v = dv1[i1 + 3 * i];
      u += dv[3 * i1] * v;
      dv3[b_i] += dv[3 * i1 + 1] * v;
      dv3[counter] += dv[3 * i1 + 2] * v;
    }
    dv3[3 * i] = u;
  }
  memset(&dv[0], 0, 9U * sizeof(double));
  for (i = 0; i < 3; i++) {
    u = dv[3 * i];
    b_i = 3 * i + 1;
    counter = 3 * i + 2;
    for (i1 = 0; i1 < 3; i1++) {
      v = dv2[i1 + 3 * i];
      u += dv3[3 * i1] * v;
      dv[b_i] += dv3[3 * i1 + 1] * v;
      dv[counter] += dv3[3 * i1 + 2] * v;
    }
    dv[3 * i] = u;
  }
  memset(&dv4[0], 0, 18U * sizeof(double));
  for (i = 0; i < 6; i++) {
    u = dv4[3 * i];
    b_i = 3 * i + 1;
    counter = 3 * i + 2;
    for (i1 = 0; i1 < 3; i1++) {
      v = dv5[i1 + 3 * i];
      u += dv[3 * i1] * v;
      dv4[b_i] += dv[3 * i1 + 1] * v;
      dv4[counter] += dv[3 * i1 + 2] * v;
    }
    dv4[3 * i] = u;
  }
  b_dx[0] = dx;
  b_dx[1] = dy;
  b_dx[2] = dz + 240.33;
  for (i = 0; i < 3; i++) {
    u = b_dx[i];
    for (i1 = 0; i1 < 6; i1++) {
      translatedPlatform[i1 + 6 * i] = dv4[i + 3 * i1] + u;
    }
  }
  /*  2. Homogeneous Transformation Matrices (HTMs: Servo to Base) */
  solution_new = 0.0;
  /*  3. Kinematic Solver Loop (Newton-Raphson) */
  /*  Link length */
  /*  Servo arm length */
  b_i = 0;
  exitg1 = false;
  while (!exitg1 && (b_i < 6)) {
    double HTM[16];
    double A;
    double A_tmp;
    double B;
    double C;
    double err;
    double solution_initial;
    double w;
    bool exitg2;
    solution_initial = 0.0;
    counter = 1;
    err = 1.0;
    for (i = 0; i < 4; i++) {
      int HTM_tmp;
      int b_HTM_tmp;
      HTM_tmp = i << 2;
      b_HTM_tmp = HTM_tmp + (b_i << 4);
      HTM[HTM_tmp] = rotation_matrices[b_HTM_tmp];
      HTM[HTM_tmp + 1] = rotation_matrices[b_HTM_tmp + 1];
      HTM[HTM_tmp + 2] = rotation_matrices[b_HTM_tmp + 2];
      HTM[HTM_tmp + 3] = rotation_matrices[b_HTM_tmp + 3];
    }
    u = HTM[12] - translatedPlatform[b_i];
    v = HTM[13] - translatedPlatform[b_i + 6];
    w = HTM[14] - translatedPlatform[b_i + 12];
    A_tmp = HTM[6] * HTM[6];
    A = 1225.0 * ((HTM[0] * HTM[0] + HTM[1] * HTM[1]) - A_tmp);
    B = 70.0 * (u * HTM[0] + v * HTM[1]);
    C = 70.0 * w * HTM[6];
    u = (((u * u + v * v) + w * w) + A_tmp * 1225.0) - 59536.0;
    exitg2 = false;
    while (!exitg2 && ((err > 0.0001) && (counter <= 20))) {
      double dfx;
      double dfx_tmp;
      /*  Local Functions (C-Compatible) */
      v = rt_powd_snf(solution_initial, 3.0);
      w = (A - B) + u;
      A_tmp = 2.0 * C;
      dfx_tmp = solution_initial * solution_initial;
      dfx = ((4.0 * w * v + 6.0 * C * dfx_tmp) +
             4.0 * (-A + u) * solution_initial) +
            A_tmp;
      /*  Safeguard against zero derivative */
      if (fabs(dfx) < 1.0E-12) {
        counter = 21;
        exitg2 = true;
      } else {
        solution_new =
            solution_initial -
            ((((((w * rt_powd_snf(solution_initial, 4.0) + A_tmp * v) +
                 (-2.0 * A + 2.0 * u) * dfx_tmp) +
                A_tmp * solution_initial) +
               A) +
              B) +
             u) /
                dfx;
        err = fabs(solution_new - solution_initial);
        solution_initial = solution_new;
        counter++;
      }
    }
    if ((err <= 0.0001) && (counter <= 20)) {
      theta_NR[b_i] = 2.0 * (57.29577951308232 * atan(solution_new));
      /*  Output in degrees */
      b_i++;
    } else {
      exitg1 = true;
    }
  }
  for (i = 0; i < 6; i++) {
    bv[i] = rtIsNaN(theta_NR[i]);
  }
  if (!any(bv)) {
    for (i = 0; i < 6; i++) {
      final_angle[i] = theta_NR[i];
    }
  }
}

/*
 * File trailer for stewart_platform_v2.c
 *
 * [EOF]
 */
