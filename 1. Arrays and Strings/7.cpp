#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
struct Matrix {
  Matrix(size_t n) : n(n) {
    mat.resize(n);

    int val = 1;
    for (int i = 0; i < n; i++) {
      mat[i].resize(n);
      for (int j = 0; j < n; j++) {
        mat[i][j] = val++;
      }
    }
  }

  std::vector<T>& operator[](int i) {
    if (i < 0 || i > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    return mat[i];
  }

  const std::vector<T>& operator[](int i) const {
    if (i < 0 || i > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    return mat[i];
  }

  T& operator()(int i, int j) {
    if (i < 0 || i > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    if (j < 0 || j > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    return mat[i][j];
  }

  const T& operator()(int i, int j) const {
    if (i < 0 || i > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    if (j < 0 || j > n-1)
      throw std::out_of_range("Out-of-bounds Matrix subscription");

    return mat[i][j];
  }

  bool operator==(const Matrix<T>& matrix) {
    if (n != matrix.n)
      return false;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (mat[i][j] != matrix[i][j])
          return false;

    return true;
  }

  std::vector<std::vector<T>> mat;
  size_t n;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T> mat) {
  os << "Mat[" << mat.n << "][" << mat.n << "]" << std::endl;
  for (int i = 0; i < mat.n; i++) {
    for (int j = 0; j < mat.n; j++)
      os << mat[i][j] << " ";
    os << std::endl;
  }
  os << "________" << std::endl;
  return os;
}

// Reference function, works surely
template <typename T>
Matrix<T> rotate90ref(const Matrix<T>& mat) {
  Matrix<T> rmat(mat.n);

  for (int i = 0; i < mat.n; i++)
    for (int j = 0; j < mat.n; j++)
      rmat(j, mat.n - 1 - i) = mat(i, j);

  return rmat;
}

// In-place 90* rotate
/*
template<typename T>
void rotate90(Matrix<T>& mat) {
  int n = mat.n;
  int level = 0;
  int max_level = n/2;

  while (level < max_level) {
    int elemNo = 0;

    // cache upper_line
    std::vector<T> upper_line;
    for (int j = level; j < n-level; j++)
      upper_line.push_back(mat[level][j]);

    // left_col => upper_line
    for (int j = level; j < n-level; j++)
      mat[level][j] = mat[n-1-j][level];

    // lower_line => left_col
    for (int j = level; j < n-level; j++)
      mat[j][level] = mat[n-1-level][j];

    // right_col => lower_line
    for (int j = level; j < n-level; j++)
      mat[n-1-level][j] = mat[n-1-level-j][n-1-level];

    // cached_upper_line => right_col
    for (int j = level; j < n-level; j++)
      mat[j][n-1-level] = upper_line[j-level];

    level++;
  }
}
*/

// In-place 90* rotate
template<typename T>
void rotate90(Matrix<T>& mat) {
  int n = mat.n;
  int level = 0;
  int max_level = n/2;

  while (level < max_level) {
    int elemIdx = 0;

    while (elemIdx < n-2*level) {
      // Cache upper line elem
      int elem = mat[level][elemIdx];

      // Upper-line elem = Left-col elem
      mat[level][level+elemIdx] = mat[n-1-elemIdx-level][level];

      // Left-col elem = Lower-line elem
      mat[n-1-level-elemIdx][level] = mat[n-1-level][n-1-level-elemIdx];

      // Lower-line elem = right-col elem
      mat[n-1-level][n-1-level-elemIdx] = mat[level+elemIdx][n-1-level];

      // Right-col elem = cached elem
      mat[level+elemIdx][n-1-level] = elem;

      elemIdx++;
    }

    level++;
  }
}

void test_2() {
  Matrix<int> m(2);
  Matrix<int> refm = rotate90ref(m);

  rotate90(m);
  std::cout << m;
  assert(m == refm);
}

void test_4() {
  Matrix<int> m(4);
  Matrix<int> refm = rotate90ref(m);

  rotate90(m);
  std::cout << m;
  assert(m == refm);
}

void test_8() {
  Matrix<int> m(8);
  Matrix<int> refm = rotate90ref(m);

  rotate90(m);
  assert(m == refm);
}

void test_100() {
  Matrix<int> m(100);
  Matrix<int> refm = rotate90ref(m);

  rotate90(m);
  assert(m == refm);
}

int main() {
  test_2();
  test_4();
  test_8();
  test_100();
  return 0;
}
