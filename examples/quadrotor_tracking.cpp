// Quadrotor tracking example

// This script is just to show how to use the library, the data for this example is not tuned for our Crazyflie demo. Check the firmware code for more details.

// - NSTATES = 12
// - NINPUTS = 4
// - NHORIZON = anything you want
// - NTOTAL = 301 if using reference trajectory from trajectory_data/
// - tinytype = float if you want to run on microcontrollers
// States: x (m), y, z, phi, theta, psi, dx, dy, dz, dphi, dtheta, dpsi
// phi, theta, psi are NOT Euler angles, they are Rodiguez parameters
// check this paper for more details: https://ieeexplore.ieee.org/document/9326337
// Inputs: u1, u2, u3, u4 (motor thrust 0-1, order from Crazyflie)


#define NSTATES 2
#define NINPUTS 1

#define NHORIZON 10
#define NTOTAL 20001

#include <iostream>
#include <tinympc/tiny_api.hpp>
#include <iostream>
#include <fstream>

using namespace std; 

extern "C" {

#include "problem_data/quadrotor_20hz_params.hpp"
#include "trajectory_data/quadrotor_20hz_y_axis_line.hpp"
#include "trajectory_data/quad_delta.hpp"

typedef Matrix<tinytype, NINPUTS, NHORIZON-1> tiny_MatrixNuNhm1;
typedef Matrix<tinytype, NSTATES, NHORIZON> tiny_MatrixNxNh;
typedef Matrix<tinytype, NSTATES, 1> tiny_VectorNx;

int main()
{
    TinySolver *solver;

    tinyMatrix Adyn = Map<Matrix<tinytype, NSTATES, NSTATES, RowMajor>>(Adyn_data);
    // tinyMatrix Bdyn = Map<Matrix<tinytype, NSTATES, NINPUTS, RowMajor>>(Bdyn_data);
    tinyMatrix Bdyn = Map<Matrix<tinytype, NSTATES, NINPUTS>>(Bdyn_data);
    tinyMatrix Edyn = Map<Matrix<tinytype, NSTATES, NINPUTS>>(Edyn_data);

    tinyVector Q = Map<Matrix<tinytype, NSTATES, 1>>(Q_data);
    tinyVector R = Map<Matrix<tinytype, NINPUTS, 1>>(R_data);

    tinyMatrix x_min = tiny_MatrixNxNh::Constant(-5);
    tinyMatrix x_max = tiny_MatrixNxNh::Constant(5);
    tinyMatrix u_min = tiny_MatrixNuNhm1::Constant(-800);
    tinyMatrix u_max = tiny_MatrixNuNhm1::Constant(800);

    int status = tiny_setup(&solver,
                            Adyn, Bdyn, Q.asDiagonal(), R.asDiagonal(),
                            rho_value, NSTATES, NINPUTS, NHORIZON,
                            x_min, x_max, u_min, u_max, 1);
    
    // Update whichever settings we'd like
    // solver->settings->max_iter = 100;
    // solver->settings->max_iter = 1000;

    
    // // Alias solver->work for brevity
    // TinyWorkspace *work = solver->work;

    // // Map data from trajectory_data
    // Eigen::Map<const Matrix<tinytype, NTOTAL, NSTATES, Eigen::RowMajor>> Xref_total(Xref_data);
    // Matrix<tinytype, NSTATES, NTOTAL> Xref_total = Eigen::Map<Matrix<tinytype, NSTATES, NTOTAL>>(Xref_data);
    // work->Xref = Xref_total.block<NSTATES, NHORIZON>(0, 0);


    // std::vector<double> Xref_data_vector(NSTATES * NTOTAL);
    // 필요한 데이터를 Xref_data_vector에 저장
    // Eigen::Map<Eigen::Matrix<double, NSTATES, NTOTAL>> Xref_total(Xref_data_vector.data());

    // Eigen::Map<const Matrix<tinytype, NTOTAL, NSTATES, Eigen::RowMajor>> Xref_total(Xref_data);
    // work->Xref.block<NSTATES, NHORIZON>(0, 0) = Xref_total.transpose().block<NSTATES, NHORIZON>(0, k); // step에 맞는 reference 넣어주기

   
    // std::ofstream outfile("output.txt");

    // // Initial state
    // tiny_VectorNx x0;
    // x0 = work->Xref.col(0);

    // for (int k = 0; k < NTOTAL - NHORIZON; ++k)
    // {
    //     std::cout << "tracking error: " << (x0 - work->Xref.col(1)).norm() << std::endl;

    //     // 1. Update measurement
    //     tiny_set_x0(solver, x0);

    //     // 2. Update reference
    //     work->Xref.block<NSTATES, NHORIZON>(0, 0) = Xref_total.transpose().block<NSTATES, NHORIZON>(0, k); // step에 맞는 reference 넣어주기
    //     // work->Xref = Xref_total.block<NSTATES, NHORIZON>(0, k);

    // //     // 3. Reset dual variables if needed
    // //     work->y = tiny_MatrixNuNhm1::Zero();
    // //     work->g = tiny_MatrixNxNh::Zero();

    // outfile << x0[0] << ' ' << x0[1] << ' '  << work->u.col(0)  << std::endl;

    //     // 4. Solve MPC problem
    //     tiny_solve(solver);


    //   float state_E[2] = {0.0004, 0.00420};
    //   tiny_VectorNx random_num;
    //   for (int j = 0; j < NSTATES; ++j)
    //   {
    //     random_num(j) = state_E[j] * delta[k];
    //   }

    //   // 5. Simulate forward
    // //   x0 = work->Adyn * x0 + work->Bdyn * work->u.col(0) + work->Edyn * delta[k];

    //   tiny_VectorNx next_x = work->Adyn * x0 + work->Bdyn * work->u.col(0);
    //   x0 = next_x + random_num;
    //     // cout << work->u.col(0) << endl;

    // }
    // outfile.close();
    return 0;
}

} /* extern "C" */