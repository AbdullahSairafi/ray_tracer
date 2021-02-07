#include <iostream>
#include "matrix.h"

using namespace std;

test_default_ctor(){
    Matrix<double> mat(3, 3, 1.0);
    cout << mat << endl;
}
int main(){
    test_default_ctor();
    return 0;
}