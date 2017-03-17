#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

using namespace std;


const double PHI = (1 + sqrt(5)) / 2;
const double eps = 0.001;
const double L = 0.01;
const double E = 0.00001;

vector<double> get_fib(double d) {
    vector<double> fib;
    fib.push_back(1.0);
    fib.push_back(1.0);
    while (fib[fib.size() - 1] < d) {
        fib.push_back(fib[fib.size() - 2] + fib[fib.size() - 1]);
    }
    return fib;
}

double diff (double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
};

double find_min_gold(function<double(double)> f, double l, double r){
        do {
            double x1 = r - (r - l) / PHI;
            double x2 = l + (r - l) / PHI;

            if (f(x1) >= f(x2))
                l = x1;
            else
                r = x2;

        } while (abs(r - l) >= eps);

        return (l + r) / 2;
    }


double find_min_y_gold(function<double(double, double)> g, double x, double l, double r){
        do {
            double y1 = r - (r - l) / PHI;
            double y2 = l + (r - l) / PHI;

            if (g(x, y1) >= g(x, y2))
                l = y1;
            else
                r = y2;

        } while (abs(r - l) >= eps);

        return (l + r) / 2;
    }

double find_min_x_gold(function<double(double, double)> g, double y, double l, double r){
        double x1, x2;
        do {
            x1 = r - (r - l) / PHI;
            x2 = l + (r - l) / PHI;

            if (g(x1, y) >= g(x2, y))
                l = x1;
            else
                r = x2;

        } while  (abs(r - l) >= eps);

        return (l + r) / 2;
    }

pair<double, double> find_min_2_gold(function<double(double, double)> g, double x0, double y0, double l, double r){

    double x1 = x0, y1 = y0;
    do {
        x0 = x1, y0 = y1;
        y1 = find_min_y_gold(g, x0, l, r);
        x1 = find_min_x_gold(g, y1, l, r);
    } while (diff(x0, y0, x1, y1) >= eps);
    return make_pair(x0, y0);
}

double find_min_fib(function<double(double)> f, double l, double r) {
    vector<double> fib = get_fib(abs(l - r) / L);
    double x1 = l + fib[fib.size() - 3] / fib[fib.size() - 1] * (r - l);
    double x2 = l + fib[fib.size() - 2] / fib[fib.size() - 1] * (r - l);
    int k = 1;
    while (k < fib.size() - 2) {
        if (f(x1) > f(x2)) {
            l = x1;
            x1 = x2;
            x2 = l + fib[fib.size() - k - 2] / fib[fib.size() - k - 1] * (r - l);
        } else {
            r = x2;
            x2 = x1;
            x1 = l + fib[fib.size() - k - 3] / fib[fib.size() - k - 1] * (r - l);
        }
        k++;
    }
    x2 += E;
    if (f(x1) > f(x2)) {
        l = x1;
    } else {
        r = x2;
    }
    return l;
}

double find_min_x_fib(function<double(double, double)> g, double y0, double l, double r) {
    vector<double> fib = get_fib(abs(l - r) / L);
    double x1 = l + fib[fib.size() - 3] / fib[fib.size() - 1] * (r - l);
    double x2 = l + fib[fib.size() - 2] / fib[fib.size() - 1] * (r - l);
    int k = 1;
    while (k < fib.size() - 2) {
        if (g(x1, y0) > g(x2, y0)) {
            l = x1;
            x1 = x2;
            x2 = l + fib[fib.size() - k - 2] / fib[fib.size() - k - 1] * (r - l);
        } else {
            r = x2;
            x2 = x1;
            x1 = l + fib[fib.size() - k - 3] / fib[fib.size() - k - 1] * (r - l);
        }
        k++;
    }
    x2 += E;
    if (g(x1, y0) > g(x2, y0)) {
        l = x1;
    } else {
        r = x2;
    }
    return l;
}

double find_min_y_fib(function<double(double, double)> g, double x0, double l, double r) {
    vector<double> fib = get_fib(abs(l - r) / L);

    double y1 = l + fib[fib.size() - 3] / fib[fib.size() - 1] * (r - l);
    double y2 = l + fib[fib.size() - 2] / fib[fib.size() - 1] * (r - l);
    int k = 1;

    while (k < fib.size() - 2) {
        if (g(x0, y1) > g(x0, y2)) {
            l = y1;
            y1 = y2;
            y2 = l + fib[fib.size() - k - 2] / fib[fib.size() - k - 1] * (r - l);
        } else {
            r = y2;
            y2 = y1;
            y1 = l + fib[fib.size() - k - 3] / fib[fib.size() - k - 1] * (r - l);
        }
        k++;
    }
    y2 += E;
    if (g(x0, y1) > g(x0, y2)) {
        l = y1;
    } else {
        r = y2;
    }
    return l;
}

pair<double, double> find_min_2_fib(function<double(double, double)> g, double x0, double y0, double l, double r) {

    double x1 = x0, y1 = y0;
    do {
        x0 = x1, y0 = y1;
        y1 = find_min_y_fib(g, x0, l, r);
        x1 = find_min_x_fib(g, y1, l, r);
    } while (diff(x0, y0, x1, y1) >= eps);
    return make_pair(x0, y0);
}


int main() {
    auto f = [](double x) {
        return x * x * x * x + x * x * x - 7.0 * x * x - x + 1.0;
    };
    auto g = [](double x, double y) {
        return -48.0 * x + 6.0 * x * x - 42.0 * y + 21.0 * y * y + 16.0 * x * y - 2.0 * x * x * y - 8.0 * x * y * y + x * x * y * y;
    };

    double res_f = find_min_gold(f, -100, 100);
    cout << "Golden ratio - one dimension" << endl;
    cout << res_f << " | " << f(res_f) << endl;

    auto res_g = find_min_2_gold(g, 0, 0, -100, 100);
    cout << "Golden ratio - two dimensions" << endl;
    cout << res_g.first << " " << res_g.second << " | " << g(res_g.first, res_g.second) << endl;

    double res_f2 = find_min_fib(f, -100, 100);
    cout << "Fibonacci method - one dimension" << endl;
    cout << res_f2 << " | " << f(res_f2) << endl;

    auto res_g2 = find_min_2_fib(g, -100, -100, -100, 100);
    cout << "Fibonacci - two dimensions" << endl;
    cout << res_g2.first << " " << res_g2.second << " | " << g(res_g2.first, res_g2.second) << endl;

    return 0;
}