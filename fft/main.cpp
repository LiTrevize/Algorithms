#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

const double pi = 3.1415926;

// compute the Fourier transform of x. Its length n must be the power of 2.
void fft(complex<double> *x, complex<double> *y, int n);

void fft(complex<double> *x, complex<double> *y, int n) {
    if (n == 1) {
        y[0] = x[0];
        return;
    }

    complex<double> *x_e = new complex<double>[n / 2];
    complex<double> *x_o = new complex<double>[n / 2];
    complex<double> *y_e = new complex<double>[n / 2];
    complex<double> *y_o = new complex<double>[n / 2];

    for (int i = 0; i < n / 2; ++i) {
        x_e[i] = x[2 * i];
        x_o[i] = x[2 * i + 1];
    }

    fft(x_e, y_e, n / 2);
    fft(x_o, y_o, n / 2);

    complex<double> omega_k;
    for (int k = 0; k < n / 2; ++k) {
        omega_k = polar(1.0, 2 * pi * k / n);
        y[k] = y_e[k] + omega_k * y_o[k];
        y[k + n / 2] = y_e[k] - omega_k * y_o[k];
    }

    delete[] x_e, x_o, y_e, y_o;

}

int main() {
    int n;
    complex<double> *x, *y;
    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> n;
    x = new complex<double>[n];
    y = new complex<double>[n];

    for (int i = 0; i < n; i++) {
        infile >> x[i];
    }

    fft(x, y, n);

    for (int i = 0; i < n; i++)
        outfile << y[i] << endl;

    delete[] x, y;

    infile.close();
    outfile.close();
    return 0;
}

