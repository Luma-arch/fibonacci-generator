#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

// Define cpp_int for simplicity
typedef cpp_int bigint;

// Function to multiply two 2x2 matrices
vector<vector<bigint>> matrix_multiply(const vector<vector<bigint>>& A, const vector<vector<bigint>>& B) {
    vector<vector<bigint>> result(2, vector<bigint>(2, 0));
    
    result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
    
    return result;
}

// Function to calculate matrix exponentiation
vector<vector<bigint>> matrix_power(const vector<vector<bigint>>& matrix, int n) {
    vector<vector<bigint>> result = {{1, 0}, {0, 1}};  // Identity matrix
    vector<vector<bigint>> base = matrix;
    
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrix_multiply(result, base);
        }
        base = matrix_multiply(base, base);
        n /= 2;
    }
    
    return result;
}

// Function to calculate the n-th Fibonacci number using matrix exponentiation
bigint fibonacci_matrix(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    vector<vector<bigint>> F = {{1, 1}, {1, 0}};
    vector<vector<bigint>> result_matrix = matrix_power(F, n - 1);
    
    return result_matrix[0][0];
}

int main() {
    // Calculate the 115000th Fibonacci number
    bigint fib_115000 = fibonacci_matrix(115000);
    
    // Convert to string and print
    string fib_str = fib_115000.str();
    cout << "Fibonacci number (115000th):\n" << fib_str << endl;
    
    return 0;
}
