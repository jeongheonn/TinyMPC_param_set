        // tiny_MatrixX Adyn = tiny_MatrixX::Map(Adyn_data, nx, nx);
        // tiny_MatrixX Bdyn = tiny_MatrixX::Map(Bdyn_data, nx, nu);
        // tiny_MatrixX Q = tiny_MatrixX::Map(Q_data, nx, 1);
        // tiny_MatrixX R = tiny_MatrixX::Map(R_data, nu, 1);
        // tiny_MatrixX x_min = tiny_MatrixX::Map(x_min_data, nx, N);
        // tiny_MatrixX x_max = tiny_MatrixX::Map(x_max_data, nx, N);
        // tiny_MatrixX u_min = tiny_MatrixX::Map(u_min_data, nu, N - 1);
        // tiny_MatrixX u_max = tiny_MatrixX::Map(u_max_data, nu, N - 1);

        // // Update by adding rho * identity matrix to Q, R
        // Q = Q + rho * tiny_MatrixX::Ones(nx, 1);
        // R = R + rho * tiny_MatrixX::Ones(nu, 1);
        // tiny_MatrixX Q1 = Q.array().matrix().asDiagonal();
        // tiny_MatrixX R1 = R.array().matrix().asDiagonal();

        // // Printing
        // std::cout << "A = " << Adyn.format(CleanFmt) << std::endl;
        // std::cout << "B = " << Bdyn.format(CleanFmt) << std::endl;
        // std::cout << "Q = " << Q1.format(CleanFmt) << std::endl;
        // std::cout << "R = " << R1.format(CleanFmt) << std::endl;
        // std::cout << "rho = " << rho << std::endl;

        // Riccati recursion to get Kinf, Pinf
        // tiny_MatrixX Ktp1 = tiny_MatrixX::Zero(nu, nx);
        // tiny_MatrixX Ptp1 = rho * tiny_MatrixX::Ones(nx, 1).array().matrix().asDiagonal();
        // tiny_MatrixX Kinf = tiny_MatrixX::Zero(nu, nx);
        // tiny_MatrixX Pinf = tiny_MatrixX::Zero(nx, nx);

        // for (int i = 0; i < 1000; i++)
        // {
        //     Kinf = (R1 + Bdyn.transpose() * Ptp1 * Bdyn).inverse() * Bdyn.transpose() * Ptp1 * Adyn;
        //     Pinf = Q1 + Adyn.transpose() * Ptp1 * (Adyn - Bdyn * Kinf);
        //     // if Kinf converges, break
        //     if ((Kinf - Ktp1).cwiseAbs().maxCoeff() < 1e-5)
        //     {
        //         std::cout << "Kinf converged after " << i + 1 << " iterations" << std::endl;
        //         break;
        //     }
        //     Ktp1 = Kinf;
        //     Ptp1 = Pinf;
        // }

        // std::cout << "Precomputing finished" << std::endl;

        // // Compute cached matrices
        // tiny_MatrixX Quu_inv = (R1 + Bdyn.transpose() * Pinf * Bdyn).inverse();
        // tiny_MatrixX AmBKt = (Adyn - Bdyn * Kinf).transpose();
        // tiny_MatrixX coeff_d2p = Kinf.transpose() * R1 - AmBKt * Pinf * Bdyn;

        // std::cout << "Kinf = " << Kinf.format(CleanFmt) << std::endl;
        // std::cout << "Pinf = " << Pinf.format(CleanFmt) << std::endl;
        // std::cout << "Quu_inv = " << Quu_inv.format(CleanFmt) << std::endl;
        // std::cout << "AmBKt = " << AmBKt.format(CleanFmt) << std::endl;
        // std::cout << "coeff_d2p = " << coeff_d2p.format(CleanFmt) << std::endl;