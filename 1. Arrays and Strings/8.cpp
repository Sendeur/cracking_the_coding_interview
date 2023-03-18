// Zero Matrix: write an algorithm such that if an element in an MxN matrix is 0,
// its entire row and column are set to 0.

#include <iostream>
#include <cassert>

#include <map>
#include <vector>
#include <string>

class Matrix {
public:
  Matrix(int lines, int columns, int value) : lines(lines), columns(columns) {
    mat.resize(lines);
    for (int i = 0; i < lines; i++)
      mat[i].resize(columns, value);
  }

  std::vector<int>& operator[](int i) {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    return mat[i];
  }

  const std::vector<int>& operator[](int i) const {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    return mat[i];
  }

  int& operator()(int i, int j) {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    if (j >= columns)
      throw std::out_of_range{"Column index out of range"};

    return mat[i][j];
  }

  const int& operator()(int i, int j) const {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    if (j >= columns)
      throw std::out_of_range{"Column index out of range"};

    return mat[i][j];
  }

  void zeroize_line(int i) {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    for (int j = 0; j < columns; j++)
      mat[i][j] = 0;
  }

  void zeroize_column(int j) {
    if (j >= columns)
      throw std::out_of_range{"Column index out of range"};

    for (int i = 0; i < lines; i++)
      mat[i][j] = 0;
  }

  bool line_has_zero(int i) {
    if (i >= lines)
      throw std::out_of_range{"Line index out of range"};

    for (int j = 0; j < columns; j++)
      if (!mat[i][j])
        return true;
    return false;
  }

  bool column_has_zero(int j) {
    if (j >= columns)
      throw std::out_of_range{"Column index out of range"};

    for (int i = 0; i < lines; i++)
      if (!mat[i][j])
        return true;
    return false;
  }

  bool operator==(const Matrix& m) {
    if (lines != m.lines)
      return false;

    if (columns != m.columns)
      return false;

    for (int i = 0; i < lines; i++)
      for (int j = 0; j < columns; j++)
        if (m(i, j) != mat[i][j])
          return false;

    return true;
  }

  std::vector<std::vector<int>> mat;
  int lines;
  int columns;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  for (int i = 0; i < m.lines; i++) {
    for (int j = 0; j < m.columns; j++)
      os << m(i, j) << " ";
    os << std::endl;
  }
  os << std::endl;
  return os;
}

void ZeroMatrix(Matrix& mat) {
  if (mat.lines == 0 or mat.columns == 0)
    return;

  if (mat.lines == 1 and mat.columns == 1)
    return ;

  bool zero_first_line = mat.line_has_zero(0);
  bool zero_first_column = mat.column_has_zero(0);

  // Iterate through matrix, find the zeroes and encode the information in the first line+column.
  for (int i = 1; i < mat.lines; i++)
    for (int j = 1; j < mat.columns; j++)
      if (mat(i, j) == 0) {
        mat(i, 0) = 0;
        mat(0, j) = 0;
      }

  // Zeroize lines
  for (int i = 0; i < mat.lines; i++)
    if (mat(i, 0) == 0)
      mat.zeroize_line(i);

  // Zeroize columns
  for (int j = 0; j < mat.columns; j++)
    if (mat(0, j) == 0)
      mat.zeroize_column(j);

  // Zeroize first line (if necessary)
  if (zero_first_line)
    mat.zeroize_line(0);

  // Zeroize first column (if necessary)
  if (zero_first_column)
    mat.zeroize_column(0);
}

/////////////
// Testing //
/////////////

bool test_0() {
  Matrix m(0, 0, 0);
  ZeroMatrix(m);
  Matrix mref(0, 0, 0);
  return m==mref;
}

bool test_1() {
  Matrix m(1, 1, 0);
  ZeroMatrix(m);
  Matrix mref(1, 1, 0);
  return m==mref;
}

bool test_2() {
  Matrix m(1, 1, 1);
  ZeroMatrix(m);
  Matrix mref(1, 1, 1);
  return m==mref;
}

bool test_3() {
  // 1 1 1
  // 0 1 1
  // 1 1 0
  Matrix m(3, 3, 1);
  m[1][0] = 0;
  m[2][2] = 0;

  ZeroMatrix(m);

  // 0 1 0
  // 0 0 0
  // 0 0 0
  Matrix mref(3, 3, 0);
  mref[0][1] = 1;

  return m==mref;
}

bool test_4() {
  // 1 1 1 1 1 1
  // 1 0 1 1 1 1
  // 1 1 0 0 0 1
  // 1 1 1 1 1 1
  // 1 1 1 0 1 1
  Matrix m(5, 6, 1);
  m[1][1] = 0;
  m[2][2] = 0;
  m[2][3] = 0;
  m[2][4] = 0;
  m[4][3] = 0;

  ZeroMatrix(m);

  // 1 0 0 0 0 1
  // 0 0 0 0 0 1
  // 0 0 0 0 0 1
  // 1 0 0 0 0 1
  // 0 0 0 0 0 0
  Matrix mref(5, 6, 0);
  mref[0][0] = 1;
  mref[0][5] = 1;
  mref[1][5] = 1;
  mref[2][5] = 1;
  mref[3][5] = 1;
  mref[3][0] = 1;

  return m == mref;
}

void run_tests() {
  std::map<std::string, bool(*)()> tests{
    {"Test 0", test_0},
    {"Test 1", test_1},
    {"Test 2", test_2},
    {"Test 3", test_3},
    {"Test 4", test_4},
  };

  for (auto&[test, testfunc] : tests) {
    if (testfunc())
      std::cout << test << " has PASSED!" << std::endl;
    else
      std::cout << test << " has FAILED!" << std::endl;
  }
}

int main() {
  run_tests();
  return 0;
}
