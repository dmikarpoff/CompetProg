#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>

//#define TRAIN

struct RestPair {
    double winner;
    double r1, r2;
    double d1, d2;
};

struct LinearModel {
    double a = 2.727;
    double b = 5.55842;
    double neg = 0.0;

    double score(double r, double d) const {
        return a * pow(r, 4.0) + b * pow((1 - d), 30.0);
    }
    std::complex<double> deriv(double r, double d) const {
        return {pow(r, 4.0) , pow(1 - d, 30.0)};
    }
};



template <class Model>
double estimate_error(const std::vector<RestPair>& data, const Model& model) {
    double err = 0.0;
    for (const auto& p : data) {
        double score1 = model.score(p.r1, p.d1);
        double score2 = model.score(p.r2, p.d2);
        if (p.winner > 0.75) {
            std::swap(score1, score2);
        }
        auto single_err = log(1 + exp(score2 - score1));
        /*
        if (single_err > 0.5) {
            std::cout << "big err = " << single_err << std::endl;
            std::cout << p.winner << " (" << p.r1 << ", " << p.d1 << ")  (" << p.r2 << ", " << p.d2 << ")" << std::endl;
        }
        */
        err += single_err;
    }
    return err / data.size();
}

template <class Model>
std::complex<double> estimate_update(const RestPair& p, const Model& model) {
    double score1 = model.score(p.r1, p.d1);
    auto deriv1 = model.deriv(p.r1, p.d1);
    double score2 = model.score(p.r2, p.d2);
    auto deriv2 = model.deriv(p.r2, p.d2);
    if (p.winner > 0.75) {
        std::swap(score1, score2);
        std::swap(deriv1, deriv2);
    }
    return exp(score2 - score1) / (1 + exp(score2 - score1)) * (deriv2 - deriv1);
}

template <class Model>
void update_model(const std::vector<RestPair>& data, Model& model, double step) {
    std::complex<double> g{0.0, 0.0};
    for (const auto& p : data) {
        g += estimate_update(p, model);
    }
    g *= (step / data.size());
    model.a -= g.real();
    model.b -= g.imag();
}

int main()
{
    LinearModel model;
#ifdef TRAIN
    std::ifstream in("restaurants_train.txt");
    std::string line;
    std::vector<RestPair> data;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss;
        ss.str(line);
        RestPair p;
        in >> p.winner >> p.r1 >> p.r2 >> p.d1 >> p.d2;
        p.r1 /= 10.0;
        p.r2 /= 10.0;
        if (p.r1 < -0.05) {
            p.r1 *= model.neg;
        }
        if (p.r2 < -0.05) {
            p.r2 *= model.neg;
        }
        data.push_back(p);
    }

    for (int t = 0; t < 1000; ++t) {
        update_model(data, model, 10.0);
        std::cout << "e = " << estimate_error(data, model) << std::endl;
        std::string l;
        getline(std::cin, l);
        if (l == "s") {
            break;
        }
    }

    std::cout << "Final verification: " << std::endl;
    std::cout << "a = " << model.a << std::endl;
    std::cout << "b = " << model.b << std::endl;
    std::cout << estimate_error(data, model);
#else
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        double r, d;
        std::cin >> r >> d;
        r /= 10.0;
        if (r < -0.05) {
            r *= model.neg;
        }
        std::cout << model.score(r, d) << std::endl;
    }
#endif
    return 0;
}
