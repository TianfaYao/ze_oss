#pragma once

#include <ze/common/types.h>
#include <ze/common/transformation.h>
#include <ze/geometry/robust_cost.h>
#include <ze/geometry/least_squares_solver.h>

namespace ze {

//! Estimates relative transformation between two sets of associated pints
class PoseAligner :
    public LeastSquaresSolver<6, Transformation, PoseAligner>
{
public:
  using LeastSquaresSolver::HessianMatrix;
  using LeastSquaresSolver::GradientVector;
  using ScaleEstimator = UnitScaleEstimator<FloatType>;
  using WeightFunction = UnitWeightFunction<FloatType>;

  PoseAligner(
      const TransformationVector& T_W_A,
      const TransformationVector& T_W_B,
      const FloatType measurement_sigma_pos,
      const FloatType measurement_sigma_rot);

  double evaluateError(
      const Transformation& T_A_B,
      HessianMatrix* H,
      GradientVector *g);

  void update(
      const Transformation& T_A_Bold,
      const UpdateVector& dx,
      Transformation& T_A_Bnew);

private:
  const TransformationVector& T_W_A_;
  const TransformationVector& T_W_B_;
  FloatType measurement_sigma_pos_;
  FloatType measurement_sigma_rot_;
};

inline Matrix6 dRelpose_dTransformation(
    const Transformation& T_A_B,
    const Transformation& T_W_A,
    const Transformation& T_W_B)
{
  Quaternion R_W_B_predicted = T_W_A.getRotation() * T_A_B.getRotation();
  Quaternion R_error = T_W_B.getRotation().inverse() * R_W_B_predicted;

  Matrix6 J = Z_6x6;
  J.block<3,3>(0,0) = R_W_B_predicted.getRotationMatrix(); // drt / dt
  J.block<3,3>(3,3) = logmapDerivativeSO3(R_error.log());  // drR / dR

  return J;
}

} // namespace ze
