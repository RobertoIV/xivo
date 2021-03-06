// Help functions.
// Author: Xiaohan Fei (feixh@cs.ucla.edu)
#pragma once
#include <algorithm>
#include <vector>

#include "alias.h"

namespace feh {

// Project matrix Hx onto the left nullspace of Hf via Givens rotations.
// i.e., A' * Hf = 0 and we compute Hx <- A' * Hx
// This can be achieved first concatenate Hf and Hx as [Hf | Hx]
// And then eliminate the left most block Hf via Givens rotation.
void SlowGivens(const MatX &Hf, MatX &Hx);

// zero-out measurement jacobian matrix H by applying Givens rotations
// same rotations will also be used to transform residual vector r.
// Effective_rows is the number of rows actually used. Since r, n, Hx, and Hf
// might be over-sized.
int Givens(VecX &r, MatX &Hx, MatX &Hf, int effective_rows = -1);

// QR-based measurement compression.
// Args:
//  r: residual vector
//  Hx: measurement jacobian
// Returns: size of the upper triangular matrix Th
int QR(VecX &r, MatX &Hx, int effective_rows = -1);

template <typename T> void MakePtrVectorUnique(std::vector<T *> &v) {
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
}

// triangulation method1
// g12: 2->1
// xc1: camera coordinates in frame 1
// xc2: camera coordiantes in frame 2
Vec3 Triangulate1(const SE3 &g12, const Vec2 &xc1, const Vec2 &xc2);

// triangulation method2
// interface same as triangulation method1 above
Vec3 Triangulate2(const SE3 &g12, const Vec2 &xc1, const Vec2 &xc2);

} // namespace feh
