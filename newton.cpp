#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

const double PHI = (1 + sqrt(5)) / 2;
const double eps = 0.00001;

double newton(function<double (double)> f, function<double (double)> f_, double x0) {
    double xn, xn1 = x0;
    do {
        xn = xn1;
        xn1 = xn - f(xn) / f_(xn);
    } while (abs(xn - xn1) >= eps);
    return xn1;
}

int main() {
    double alpha = 10.0;
    double lambda = 380.0;
    double H = 0.003;

    auto f1 = [alpha, lambda, H](double pm) {
        return pm * sin(pm * H) - alpha/lambda * cos(pm * H);
    };
    auto f1_ = [alpha, lambda, H](double pm) {
        return H * pm * cos(pm * H) + (H * alpha * sin (pm * H))/(lambda);
    };
    auto f2 = [alpha, lambda, H](double pm) {
        return (pm - (alpha * alpha) / (lambda * lambda * pm)) * sin(pm * H) - 2.0 * alpha/lambda * cos(pm * H);
    };
    auto f2_ = [alpha, lambda, H](double pm) {
        return H * (pm - (alpha * alpha) / (lambda * lambda * pm)) * cos(pm * H) +
                (1.0 - (alpha * alpha) / (lambda * lambda * pm * pm)) * sin(pm * H)
               + (2.0 * H * alpha * sin (pm * H))/(lambda);
    };
    cout << "First function" << endl;
    double  x = 1.2;
    for (int i = 0; i < 5; ++i) {
        double res_f1 = newton(f1, f1_, x);
        cout << res_f1 << endl;
        x += M_PI / H;
    }
    cout << "Second function" << endl;
    x = 1.2;
    for (int i = 0; i < 5; ++i) {
        double res_f2 = newton(f2, f2_, x);
        cout << res_f2 << endl;
        x += M_PI / H;
    }

    return 0;
}
