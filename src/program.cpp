#include <iostream> // input and output control
#include <unordered_map> // unordered maps for recursive calculations
#include <boost/multiprecision/cpp_int.hpp> // multiprecision int to avoid using floats (because floats return values like 1000+e19 instead of the full number)
#include <chrono> // time measurement (seconds, milliseconds, microseconds, etc.)
#include <cstring> // for strcmp
#include <fstream> // for file writing (not implemented, gotta do it yourself)

// namespaces for convenience
using namespace std;
using namespace boost::multiprecision;

char i_r[128] = "";
unordered_map<int, cpp_int> memo; // create an unordered map for recursive calculations
bool iterativa = false; // choice between recursive or iterative calculation

// Fibonacci function
cpp_int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    // Check if the result is already memorized
    auto it = memo.find(n);
    if (it != memo.end()) {
        return it->second;
    }

    // iterative calculation
    if (iterativa == true) {
        cpp_int a = 0, b = 1, next;
        for (int i = 2; i <= n; ++i) {
            next = a + b;
            a = b;
            b = next;
        }
        return b; // Return the last Fibonacci number calculated
    }

    // Calculate recursively and store the result (it's 115% faster than iterative, but uses more RAM)
    cpp_int result = fibonacci(n - 1) + fibonacci(n - 2);
    memo[n] = result;
    return result;
}

// program start
int main() {
    // this part is self-explanatory
    int sequence_numbers = 0;
    cout << "Enter the number of Fibonacci sequence numbers you want to calculate: ";
    cin >> sequence_numbers;

    cout << "Do you want to calculate iteratively or recursively? (i / r): " << endl;
    cin >> i_r;

    if (strcmp(i_r, "i") == 0) {
        iterativa = true;
    }
    else if (strcmp(i_r, "r") == 0) {
        iterativa = false;
    }
    else {
        cout << "Invalid input." << endl;
        return 0;
    }

    chrono::steady_clock sc; // create a time clock object

    if (sequence_numbers <= 0) {
        cout << "Invalid number" << endl;
        return 1;
    }

    auto start = sc.now(); // start the timer

    // Fibonacci calculation section
    for (int i = 0; i <= sequence_numbers; ++i) {
        cout << i << " " << fibonacci(i) << endl;
    }

    memo.clear(); // clear the unordered map (free up memory)

    auto end = sc.now(); // stop the timer
    auto time_span = static_cast<chrono::duration<double>>(end - start); // time variable

    cout << endl;
    cout << "finished" << endl;
    cout << endl;

    cout << setprecision(8) << fixed << "time: " << time_span.count() << endl; // measure the time

    system("pause");

    return 0;
}
