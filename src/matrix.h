#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cassert>
#include <initializer_list>

using namespace std;

template <class T> 
class Matrix;

// matrix matrix operations
template <class T>
Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2);
template <class T>
Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2);
template <class T>
Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2);
template <class T>
Matrix<T> matmul(const Matrix<T> &m1, const Matrix<T> &m2);

// matrix scalar operations
template <class T>
Matrix<T> operator*(const Matrix<T> &m, const T &c);
template <class T>
Matrix<T> operator*(const T &c, const Matrix<T> &m);

// matrix vector operations

template <class T>
Matrix<T> operator*(const Matrix<T> &m, const vector<T> &v);
template <class T>
Matrix<T> operator*(const vector<T> &v, const Matrix<T> &m);
template <class T>
Matrix<T> vecmul(const Matrix<T> &m, const vector<T> &v);
template <class T>
Matrix<T> vecmul(const vector<T> &v, const Matrix<T> &m);

// printing 
template <class T>
ostream& operator<<(ostream &out, const Matrix<T> &m);

// comparison (for testing purposes)
template <class T>
bool operator==(const Matrix<T> &m1, const Matrix<T> &m2);

template <class T>
class Matrix{

public:
    // default ctor
    Matrix(int r, int c, T val);
    // copy ctor
    Matrix(const Matrix &rhs);
    // list intitilizer ctor
    Matrix(initializer_list<initializer_list<T>> list);

    // matrix info 
    int get_rows() const {return m_rows;}
    int get_cols() const {return m_cols;}

    // overloaded assignment operator
    Matrix<T>& operator=(const Matrix<T> &rhs);

    //overloaded +=, -=, *=
    Matrix<T>& operator+=(const Matrix<T> &rhs);
    Matrix<T>& operator-=(const Matrix<T> &rhs);
    Matrix<T>& operator*=(const Matrix<T> &rhs);

    // overload access operator()
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;

    // matrix matrix operations
    friend Matrix<T> operator+ <> (const Matrix<T> &m1, const Matrix<T> &m2);
    friend Matrix<T> operator- <> (const Matrix<T> &m1, const Matrix<T> &m2);
    friend Matrix<T> operator* <> (const Matrix<T> &m1, const Matrix<T> &m2);
    friend Matrix<T> matmul <> (const Matrix<T> &m1, const Matrix<T> &m2);

    // matrix scalar operations
    friend Matrix<T> operator* <> (const Matrix<T> &m, const T &c);
    friend Matrix<T> operator* <> (const T &c, const Matrix<T> &m);

    // matrix vector operations
    friend Matrix<T> operator* <> (const Matrix<T> &m, const vector<T> &v);
    friend Matrix<T> operator* <> (const vector<T> &v, const Matrix<T> &m);
    friend Matrix<T> vecmul <> (const Matrix<T> &m, const vector<T> &v);
    friend Matrix<T> vecmul <> (const vector<T> &v, const Matrix<T> &m);
   
    // printing 
    friend ostream& operator<< <T> (ostream &out, const Matrix<T> &m);
    
    // comparison
    friend bool operator== <>(const Matrix<T> &m1, const Matrix<T> &m2);

private:
    int m_rows;
    int m_cols;
    vector<vector<T>> m;
};

template <class T>
Matrix<T> vec_to_mat(const vector<T> &v, bool row_vec = false);

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
Matrix<T>::Matrix(initializer_list<initializer_list<T>> listlist){
    m_rows = listlist.size();
    m_cols = listlist.begin()->size();

    // resize this->m
    m.resize(m_rows);
    for(int i = 0; i < m.size(); i++){
        m[i].resize(m_cols);
    }

    // copy elements from intilizer list to matrix
    int i = 0;
    for(auto list : listlist){
        int j = 0;
        for(auto element : list){
            m[i][j] = element;
            j++;
        }
        i++;
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &rhs){
    *this = rhs; // use operator=() function
}

template <class T> 
Matrix<T>& Matrix<T>::operator=(const Matrix &rhs){
   if(this == &rhs){ // avoid self-assignment
        return *this;
    }
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;

    // resize this->m
    m.resize(m_rows);
    for(int i = 0; i < m.size(); i++){
        m[i].resize(m_cols);
    }

    // copy values
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            m[i][j] = rhs(i,j);
        }
    }

    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &rhs){
    *this = *this + rhs;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &rhs){
    *this = *this - rhs;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &rhs){
    *this = *this * rhs;
    return *this;
}


template <class T>
Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2){
    // make sure m1 and m2 are compatible for addition
    assert(m1.get_rows() == m2.get_rows() && m1.get_cols() == m2.get_cols());
    Matrix<T> result{m1.get_rows(), m1.get_cols(), T{}};
    for(int i = 0; i < result.m_rows; i++){
        for(int j = 0; j < result.m_cols; j++){
            result(i,j) = m1(i,j) + m2(i,j);
        }
    }
    return result;
}

template <class T>
Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2){
    // make sure m1 and m2 are compatible for subtraction
    assert(m1.get_rows() == m2.get_rows() && m1.get_cols() == m2.get_cols());
    Matrix<T> result{m1.get_rows(), m1.get_cols(), T{}};
    for(int i = 0; i < result.m_rows; i++){
        for(int j = 0; j < result.m_cols; j++){
            result(i,j) = m1(i,j) - m2(i,j);
        }
    }
    return result;
}

template <class T>
Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2){
    // make sure m1 and m2 are compatible for matrix multiplication
    assert(m1.get_cols() == m2.get_rows());
    Matrix<T> result{m1.get_rows(), m2.get_cols(), T{}};
    for(int i = 0; i < result.m_rows; i++){
        for(int j = 0; j < result.m_cols; j++){
            for(int k = 0; k < m1.m_cols; k++){
                result(i,j) += m1(i,k) * m2(k,j);
            }
        }
    }
    return result;
}

template <class T>
Matrix<T> matmul(const Matrix<T> &m1, const Matrix<T> &m2){
    return m1 * m2;
}


template <class T>
Matrix<T> operator*(const Matrix<T> &m, const T &c){
    int rows = m.get_rows();
    int cols = m.get_cols();
    Matrix<T> result{rows, cols, T{}};
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result(i,j) = m(i,j) * c;
        }
    }
    return result;
}

template <class T>
Matrix<T> operator*(const T &c, const Matrix<T> &m){
    return m * c;
}

template <class T>
Matrix<T> operator*(const Matrix<T> &m, const vector<T> &v){
    assert(m.m_cols == v.size()); // check compatibility
    bool row_vec = false;
    Matrix<T> vec_mat = vec_to_mat(v, row_vec); // get a matrix for the input vector
    return m * vec_mat;
}

template <class T>
Matrix<T> operator*(const vector<T> &v, const Matrix<T> &m){
    assert(m.m_rows == v.size()); // check compatibility
    bool row_vec = true;
    Matrix<T> vec_mat = vec_to_mat(v, row_vec); // get a matrix for the input vector
    return vec_mat * m;
}

template <class T>
Matrix<T> vecmul(const Matrix<T> &m, const vector<T> &v){
    return m * v;
}

template <class T> 
Matrix<T> vecmul(const vector<T> &v, const Matrix<T> &m){
    return v * m;
}

template <class T> 
T& Matrix<T>::operator()(int i, int j){
    assert(0 <= i && i < m_rows);
    assert(0 <= j && j < m_cols);
    return m[i][j];
}

template <class T>
const T& Matrix<T>::operator()(int i, int j) const {
    assert(i >= 0 && i < m_rows);
    assert(j >= 0 && j < m_cols);
    return m[i][j];
}

template <class T>
ostream& operator<<(ostream &out, const Matrix<T> &m){
    for(int i = 0; i < m.m_rows; i++){
        for(int j = 0; j < m.m_cols; j++){
            out << m(i,j) << " ";
        }
        out << endl;
    }

    return out;
}

template <class T>
bool operator==(const Matrix<T> &m1, const Matrix<T> &m2){
    // ensure compatibility for comparison 
    assert(m1.get_rows() == m2.get_rows() && m1.get_cols() == m2.get_cols());
    int rows = m1.m_rows;
    int cols = m1.m_cols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(m1(i,j) != m2(i,j)){
               return false;
            }
        }
    }
    return true;
}

template <class T>
Matrix<T> vec_to_mat(const vector<T> &v, bool row_vec){
    if(row_vec){
        Matrix<T> mat{1, v.size(), T{}};
        // copy vector into row vector matrix 1xN
        for(int i = 0; i < v.size(); i++){
            mat(0, i) = v[i];
        }

        return mat;
    }
    else{
        Matrix<T> mat{v.size(), 1, T{}};
        // copy vector into col vector matrix Nx1
        for(int i = 0; i < v.size(); i++){
            mat(i, 0) = v[i];
        }
        return mat;
    }
}


#endif