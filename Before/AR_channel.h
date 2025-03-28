#ifndef AR_CHANNEL_H
#define AR_CHANNEL_H

#include <vector>
#include <complex>
#include "eigen3/Eigen/Dense"

class AR_Channel {
public:
    AR_Channel(double fd = 50.0, double T = 1.0, double Ts = 0.001, int p = 4, double epsilon = 0.00001);
    
    std::vector<std::complex<double>> generateChannel();
    
private:
    double fd;  // Doppler frequency (Hz)
    double T;   // Total time
    double Ts;  // Time step
    int N;      // Number of samples
    int p;      // AR model order
    double epsilon;  
    void calculateAutoCorrelation(std::vector<std::complex<double>>& X_vec, std::vector<std::complex<double>>& W);
    
    void calculateARCoefficients(Eigen::VectorXd& a_vec, Eigen::MatrixXd& RXX_mat, Eigen::VectorXd& r);
};

#endif 
