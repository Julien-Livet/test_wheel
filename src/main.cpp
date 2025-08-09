#include <pybind11/pybind11.h>
#include <ceres/ceres.h>
#include <ceres/rotation.h>

namespace py = pybind11;

// Exemple simple : optimisation pour trouver x qui minimise (x-10)^2
struct CostFunctor {
    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        residual[0] = x[0] - T(10.0);
        return true;
    }
};

double solve_example(double initial_x) {
    double x = initial_x;
    ceres::Problem problem;
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor),
        nullptr,
        &x
    );

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = false;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    return x;
}

PYBIND11_MODULE(test_wheel, m) {
    m.def("solve_example", &solve_example, "Solve simple optimization problem");
}
