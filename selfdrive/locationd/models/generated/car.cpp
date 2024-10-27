#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3813200851525374924) {
   out_3813200851525374924[0] = delta_x[0] + nom_x[0];
   out_3813200851525374924[1] = delta_x[1] + nom_x[1];
   out_3813200851525374924[2] = delta_x[2] + nom_x[2];
   out_3813200851525374924[3] = delta_x[3] + nom_x[3];
   out_3813200851525374924[4] = delta_x[4] + nom_x[4];
   out_3813200851525374924[5] = delta_x[5] + nom_x[5];
   out_3813200851525374924[6] = delta_x[6] + nom_x[6];
   out_3813200851525374924[7] = delta_x[7] + nom_x[7];
   out_3813200851525374924[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7507192596623646044) {
   out_7507192596623646044[0] = -nom_x[0] + true_x[0];
   out_7507192596623646044[1] = -nom_x[1] + true_x[1];
   out_7507192596623646044[2] = -nom_x[2] + true_x[2];
   out_7507192596623646044[3] = -nom_x[3] + true_x[3];
   out_7507192596623646044[4] = -nom_x[4] + true_x[4];
   out_7507192596623646044[5] = -nom_x[5] + true_x[5];
   out_7507192596623646044[6] = -nom_x[6] + true_x[6];
   out_7507192596623646044[7] = -nom_x[7] + true_x[7];
   out_7507192596623646044[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7417015785177301841) {
   out_7417015785177301841[0] = 1.0;
   out_7417015785177301841[1] = 0;
   out_7417015785177301841[2] = 0;
   out_7417015785177301841[3] = 0;
   out_7417015785177301841[4] = 0;
   out_7417015785177301841[5] = 0;
   out_7417015785177301841[6] = 0;
   out_7417015785177301841[7] = 0;
   out_7417015785177301841[8] = 0;
   out_7417015785177301841[9] = 0;
   out_7417015785177301841[10] = 1.0;
   out_7417015785177301841[11] = 0;
   out_7417015785177301841[12] = 0;
   out_7417015785177301841[13] = 0;
   out_7417015785177301841[14] = 0;
   out_7417015785177301841[15] = 0;
   out_7417015785177301841[16] = 0;
   out_7417015785177301841[17] = 0;
   out_7417015785177301841[18] = 0;
   out_7417015785177301841[19] = 0;
   out_7417015785177301841[20] = 1.0;
   out_7417015785177301841[21] = 0;
   out_7417015785177301841[22] = 0;
   out_7417015785177301841[23] = 0;
   out_7417015785177301841[24] = 0;
   out_7417015785177301841[25] = 0;
   out_7417015785177301841[26] = 0;
   out_7417015785177301841[27] = 0;
   out_7417015785177301841[28] = 0;
   out_7417015785177301841[29] = 0;
   out_7417015785177301841[30] = 1.0;
   out_7417015785177301841[31] = 0;
   out_7417015785177301841[32] = 0;
   out_7417015785177301841[33] = 0;
   out_7417015785177301841[34] = 0;
   out_7417015785177301841[35] = 0;
   out_7417015785177301841[36] = 0;
   out_7417015785177301841[37] = 0;
   out_7417015785177301841[38] = 0;
   out_7417015785177301841[39] = 0;
   out_7417015785177301841[40] = 1.0;
   out_7417015785177301841[41] = 0;
   out_7417015785177301841[42] = 0;
   out_7417015785177301841[43] = 0;
   out_7417015785177301841[44] = 0;
   out_7417015785177301841[45] = 0;
   out_7417015785177301841[46] = 0;
   out_7417015785177301841[47] = 0;
   out_7417015785177301841[48] = 0;
   out_7417015785177301841[49] = 0;
   out_7417015785177301841[50] = 1.0;
   out_7417015785177301841[51] = 0;
   out_7417015785177301841[52] = 0;
   out_7417015785177301841[53] = 0;
   out_7417015785177301841[54] = 0;
   out_7417015785177301841[55] = 0;
   out_7417015785177301841[56] = 0;
   out_7417015785177301841[57] = 0;
   out_7417015785177301841[58] = 0;
   out_7417015785177301841[59] = 0;
   out_7417015785177301841[60] = 1.0;
   out_7417015785177301841[61] = 0;
   out_7417015785177301841[62] = 0;
   out_7417015785177301841[63] = 0;
   out_7417015785177301841[64] = 0;
   out_7417015785177301841[65] = 0;
   out_7417015785177301841[66] = 0;
   out_7417015785177301841[67] = 0;
   out_7417015785177301841[68] = 0;
   out_7417015785177301841[69] = 0;
   out_7417015785177301841[70] = 1.0;
   out_7417015785177301841[71] = 0;
   out_7417015785177301841[72] = 0;
   out_7417015785177301841[73] = 0;
   out_7417015785177301841[74] = 0;
   out_7417015785177301841[75] = 0;
   out_7417015785177301841[76] = 0;
   out_7417015785177301841[77] = 0;
   out_7417015785177301841[78] = 0;
   out_7417015785177301841[79] = 0;
   out_7417015785177301841[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1112065875321844105) {
   out_1112065875321844105[0] = state[0];
   out_1112065875321844105[1] = state[1];
   out_1112065875321844105[2] = state[2];
   out_1112065875321844105[3] = state[3];
   out_1112065875321844105[4] = state[4];
   out_1112065875321844105[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1112065875321844105[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1112065875321844105[7] = state[7];
   out_1112065875321844105[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8982841478288654703) {
   out_8982841478288654703[0] = 1;
   out_8982841478288654703[1] = 0;
   out_8982841478288654703[2] = 0;
   out_8982841478288654703[3] = 0;
   out_8982841478288654703[4] = 0;
   out_8982841478288654703[5] = 0;
   out_8982841478288654703[6] = 0;
   out_8982841478288654703[7] = 0;
   out_8982841478288654703[8] = 0;
   out_8982841478288654703[9] = 0;
   out_8982841478288654703[10] = 1;
   out_8982841478288654703[11] = 0;
   out_8982841478288654703[12] = 0;
   out_8982841478288654703[13] = 0;
   out_8982841478288654703[14] = 0;
   out_8982841478288654703[15] = 0;
   out_8982841478288654703[16] = 0;
   out_8982841478288654703[17] = 0;
   out_8982841478288654703[18] = 0;
   out_8982841478288654703[19] = 0;
   out_8982841478288654703[20] = 1;
   out_8982841478288654703[21] = 0;
   out_8982841478288654703[22] = 0;
   out_8982841478288654703[23] = 0;
   out_8982841478288654703[24] = 0;
   out_8982841478288654703[25] = 0;
   out_8982841478288654703[26] = 0;
   out_8982841478288654703[27] = 0;
   out_8982841478288654703[28] = 0;
   out_8982841478288654703[29] = 0;
   out_8982841478288654703[30] = 1;
   out_8982841478288654703[31] = 0;
   out_8982841478288654703[32] = 0;
   out_8982841478288654703[33] = 0;
   out_8982841478288654703[34] = 0;
   out_8982841478288654703[35] = 0;
   out_8982841478288654703[36] = 0;
   out_8982841478288654703[37] = 0;
   out_8982841478288654703[38] = 0;
   out_8982841478288654703[39] = 0;
   out_8982841478288654703[40] = 1;
   out_8982841478288654703[41] = 0;
   out_8982841478288654703[42] = 0;
   out_8982841478288654703[43] = 0;
   out_8982841478288654703[44] = 0;
   out_8982841478288654703[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8982841478288654703[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8982841478288654703[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8982841478288654703[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8982841478288654703[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8982841478288654703[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8982841478288654703[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8982841478288654703[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8982841478288654703[53] = -9.8000000000000007*dt;
   out_8982841478288654703[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8982841478288654703[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8982841478288654703[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8982841478288654703[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8982841478288654703[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8982841478288654703[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8982841478288654703[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8982841478288654703[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8982841478288654703[62] = 0;
   out_8982841478288654703[63] = 0;
   out_8982841478288654703[64] = 0;
   out_8982841478288654703[65] = 0;
   out_8982841478288654703[66] = 0;
   out_8982841478288654703[67] = 0;
   out_8982841478288654703[68] = 0;
   out_8982841478288654703[69] = 0;
   out_8982841478288654703[70] = 1;
   out_8982841478288654703[71] = 0;
   out_8982841478288654703[72] = 0;
   out_8982841478288654703[73] = 0;
   out_8982841478288654703[74] = 0;
   out_8982841478288654703[75] = 0;
   out_8982841478288654703[76] = 0;
   out_8982841478288654703[77] = 0;
   out_8982841478288654703[78] = 0;
   out_8982841478288654703[79] = 0;
   out_8982841478288654703[80] = 1;
}
void h_25(double *state, double *unused, double *out_8986391671128314969) {
   out_8986391671128314969[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3754001319227893845) {
   out_3754001319227893845[0] = 0;
   out_3754001319227893845[1] = 0;
   out_3754001319227893845[2] = 0;
   out_3754001319227893845[3] = 0;
   out_3754001319227893845[4] = 0;
   out_3754001319227893845[5] = 0;
   out_3754001319227893845[6] = 1;
   out_3754001319227893845[7] = 0;
   out_3754001319227893845[8] = 0;
}
void h_24(double *state, double *unused, double *out_7597777148118732314) {
   out_7597777148118732314[0] = state[4];
   out_7597777148118732314[1] = state[5];
}
void H_24(double *state, double *unused, double *out_992508007738615189) {
   out_992508007738615189[0] = 0;
   out_992508007738615189[1] = 0;
   out_992508007738615189[2] = 0;
   out_992508007738615189[3] = 0;
   out_992508007738615189[4] = 1;
   out_992508007738615189[5] = 0;
   out_992508007738615189[6] = 0;
   out_992508007738615189[7] = 0;
   out_992508007738615189[8] = 0;
   out_992508007738615189[9] = 0;
   out_992508007738615189[10] = 0;
   out_992508007738615189[11] = 0;
   out_992508007738615189[12] = 0;
   out_992508007738615189[13] = 0;
   out_992508007738615189[14] = 1;
   out_992508007738615189[15] = 0;
   out_992508007738615189[16] = 0;
   out_992508007738615189[17] = 0;
}
void h_30(double *state, double *unused, double *out_5046235650302508503) {
   out_5046235650302508503[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6272334277735142472) {
   out_6272334277735142472[0] = 0;
   out_6272334277735142472[1] = 0;
   out_6272334277735142472[2] = 0;
   out_6272334277735142472[3] = 0;
   out_6272334277735142472[4] = 1;
   out_6272334277735142472[5] = 0;
   out_6272334277735142472[6] = 0;
   out_6272334277735142472[7] = 0;
   out_6272334277735142472[8] = 0;
}
void h_26(double *state, double *unused, double *out_4379965010966566671) {
   out_4379965010966566671[0] = state[7];
}
void H_26(double *state, double *unused, double *out_12498000353837621) {
   out_12498000353837621[0] = 0;
   out_12498000353837621[1] = 0;
   out_12498000353837621[2] = 0;
   out_12498000353837621[3] = 0;
   out_12498000353837621[4] = 0;
   out_12498000353837621[5] = 0;
   out_12498000353837621[6] = 0;
   out_12498000353837621[7] = 1;
   out_12498000353837621[8] = 0;
}
void h_27(double *state, double *unused, double *out_3984718403467469324) {
   out_3984718403467469324[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1449899060284228864) {
   out_1449899060284228864[0] = 0;
   out_1449899060284228864[1] = 0;
   out_1449899060284228864[2] = 0;
   out_1449899060284228864[3] = 1;
   out_1449899060284228864[4] = 0;
   out_1449899060284228864[5] = 0;
   out_1449899060284228864[6] = 0;
   out_1449899060284228864[7] = 0;
   out_1449899060284228864[8] = 0;
}
void h_29(double *state, double *unused, double *out_44562382641662858) {
   out_44562382641662858[0] = state[1];
}
void H_29(double *state, double *unused, double *out_263463666585322169) {
   out_263463666585322169[0] = 0;
   out_263463666585322169[1] = 1;
   out_263463666585322169[2] = 0;
   out_263463666585322169[3] = 0;
   out_263463666585322169[4] = 0;
   out_263463666585322169[5] = 0;
   out_263463666585322169[6] = 0;
   out_263463666585322169[7] = 0;
   out_263463666585322169[8] = 0;
}
void h_28(double *state, double *unused, double *out_4928228256369131759) {
   out_4928228256369131759[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1700166604980004082) {
   out_1700166604980004082[0] = 1;
   out_1700166604980004082[1] = 0;
   out_1700166604980004082[2] = 0;
   out_1700166604980004082[3] = 0;
   out_1700166604980004082[4] = 0;
   out_1700166604980004082[5] = 0;
   out_1700166604980004082[6] = 0;
   out_1700166604980004082[7] = 0;
   out_1700166604980004082[8] = 0;
}
void h_31(double *state, double *unused, double *out_1223126414307642528) {
   out_1223126414307642528[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3784647281104854273) {
   out_3784647281104854273[0] = 0;
   out_3784647281104854273[1] = 0;
   out_3784647281104854273[2] = 0;
   out_3784647281104854273[3] = 0;
   out_3784647281104854273[4] = 0;
   out_3784647281104854273[5] = 0;
   out_3784647281104854273[6] = 0;
   out_3784647281104854273[7] = 0;
   out_3784647281104854273[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3813200851525374924) {
  err_fun(nom_x, delta_x, out_3813200851525374924);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7507192596623646044) {
  inv_err_fun(nom_x, true_x, out_7507192596623646044);
}
void car_H_mod_fun(double *state, double *out_7417015785177301841) {
  H_mod_fun(state, out_7417015785177301841);
}
void car_f_fun(double *state, double dt, double *out_1112065875321844105) {
  f_fun(state,  dt, out_1112065875321844105);
}
void car_F_fun(double *state, double dt, double *out_8982841478288654703) {
  F_fun(state,  dt, out_8982841478288654703);
}
void car_h_25(double *state, double *unused, double *out_8986391671128314969) {
  h_25(state, unused, out_8986391671128314969);
}
void car_H_25(double *state, double *unused, double *out_3754001319227893845) {
  H_25(state, unused, out_3754001319227893845);
}
void car_h_24(double *state, double *unused, double *out_7597777148118732314) {
  h_24(state, unused, out_7597777148118732314);
}
void car_H_24(double *state, double *unused, double *out_992508007738615189) {
  H_24(state, unused, out_992508007738615189);
}
void car_h_30(double *state, double *unused, double *out_5046235650302508503) {
  h_30(state, unused, out_5046235650302508503);
}
void car_H_30(double *state, double *unused, double *out_6272334277735142472) {
  H_30(state, unused, out_6272334277735142472);
}
void car_h_26(double *state, double *unused, double *out_4379965010966566671) {
  h_26(state, unused, out_4379965010966566671);
}
void car_H_26(double *state, double *unused, double *out_12498000353837621) {
  H_26(state, unused, out_12498000353837621);
}
void car_h_27(double *state, double *unused, double *out_3984718403467469324) {
  h_27(state, unused, out_3984718403467469324);
}
void car_H_27(double *state, double *unused, double *out_1449899060284228864) {
  H_27(state, unused, out_1449899060284228864);
}
void car_h_29(double *state, double *unused, double *out_44562382641662858) {
  h_29(state, unused, out_44562382641662858);
}
void car_H_29(double *state, double *unused, double *out_263463666585322169) {
  H_29(state, unused, out_263463666585322169);
}
void car_h_28(double *state, double *unused, double *out_4928228256369131759) {
  h_28(state, unused, out_4928228256369131759);
}
void car_H_28(double *state, double *unused, double *out_1700166604980004082) {
  H_28(state, unused, out_1700166604980004082);
}
void car_h_31(double *state, double *unused, double *out_1223126414307642528) {
  h_31(state, unused, out_1223126414307642528);
}
void car_H_31(double *state, double *unused, double *out_3784647281104854273) {
  H_31(state, unused, out_3784647281104854273);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
