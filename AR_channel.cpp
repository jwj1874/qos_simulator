#include "AR_channel.h"
//#include "eigen3/Eigen/Dense"
#include <cmath>
#include <random>
#include <iostream>

using namespace std;

//const double M_PI = 3.14159265358979323846;

AR_Channel::AR_Channel(double fd, double T, double Ts, int p, double epsilon)
    : fd(fd), T(T), Ts(Ts), p(p), epsilon(epsilon) {
    N = static_cast<int>(T / Ts);  
}

void AR_Channel::calculateAutoCorrelation(std::vector<std::complex<double>>& X_vec, std::vector<std::complex<double>>& W) {
    Eigen::VectorXd RXX_vec(p + 1);
    for (int m = 0; m <= p; m++) {
        RXX_vec(m) = cyl_bessel_j(0, 2.0 * M_PI * fd * m * Ts);
    }

    Eigen::VectorXd r = RXX_vec.segment(1, p);
    Eigen::MatrixXd RXX_mat(p, p);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            RXX_mat(i, j) = RXX_vec(abs(i - j));
        }
    }
    RXX_mat += epsilon * Eigen::MatrixXd::Identity(p, p);
    Eigen::VectorXd a_vec = -RXX_mat.inverse() * r;

    double sigma2 = abs(RXX_vec(0) + r.transpose() * a_vec);

    for (int n = 0; n < N; n++) {
        complex<double> X = {0.0, 0.0};
        for (int m = 1; m <= p; m++) {
            if (n - m >= 0) X += a_vec(m - 1) * X_vec[n - m];
        }
        normal_distribution<double> dist(0.0, 1.0);
        random_device rd;
        mt19937 gen(rd());
        double real_noise = dist(gen);
        double imag_noise = dist(gen);
        W[n] = (1.0) / sqrt(2.0) * complex<double>(real_noise, imag_noise) * sqrt(sigma2);
        X_vec[n] = -X + W[n];
    }
}

std::vector<std::complex<double>> AR_Channel::generateChannel() {
    vector<complex<double>> h(N);
    vector<complex<double>> X_vec(N, {0.0, 0.0});
    vector<complex<double>> W(N, {0.0, 0.0});

    calculateAutoCorrelation(X_vec, W);
    
    h = X_vec;
    return h;
}
