#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

template <class T>
class Matrix{

public:
    // default ctor
    Matrix(int r = 0, int c = 0; T val);
    // copy ctor
    Matrix(const Matrix &rhs);

    // matrix info 
    int get_rows() const {return m_rows;}
    int get_cols() const {return m_cols;}

    // overloaded assignment operator
    const Matrix& operator=(const Matrix &rhs);

    // matrix matrix operations
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend Matrix matmul(const Matrix &m1, const Matrix &m2);

    // matrix scalar operations
    friend Matrix operator*(const Matrix &m, const T &c);
    friend Matrix operator*(const T &c, const Matrix &m);

    // matrix vector operations
    friend vector<T> operator*(const Matrix &m, const vector<T> &v);
    friend vector<T> operator*(const vector<T> &v, const Matrix &m);
    friend vecmul(const vector<T> &v, const Matrix &m);
    friend vecmul(const Matrix &m, const vector<T> &v);

private:
    int m_rows;
    int m_cols;
    vector<vector<T>> m;
};

template <class T>
Matrix<T>::Matrix(int r, int c, T val)
    : m_rows{r}, m_cols{c} 
{
    m.resize(m_rows);
    for(int i = 0; i < m.size(); i++){
        m[i].resize(m_cols, val);
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix &rhs){
    if(this == &rhs){ // avoid self-assignment
        return *this;
    }
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    m = rhs.m; // vectors already provide implementation
}


#endif