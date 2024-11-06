/*Enter n=odd number and make n*n matrix where outermost loop will start from 1 and 2nd outer loop is 'A', and both will increase like the following pattern
n=11
1 1 1 1 1 1 1 1 1 1 1 
1 A A A A A A A A A 1 
1 A 2 2 2 2 2 2 2 A 1 
1 A 2 B B B B B 2 A 1 
1 A 2 B 3 3 3 B 2 A 1 
1 A 2 B 3 C 3 B 2 A 1 
1 A 2 B 3 3 3 B 2 A 1 
1 A 2 B B B B B 2 A 1 
1 A 2 2 2 2 2 2 2 A 1 
1 A A A A A A A A A 1 
1 1 1 1 1 1 1 1 1 1 1 
*/

#include <iostream>
using namespace std;

void generatePattern(int n) {
    int num=1;
    for (int i = 0; i < n; i++) {
     
        for (int j = 0; j < n; j++) {
            
            // layer value
            int layer = min(min(i, j), min (n - 1 - i, n - 1 - j));

            // number
            if (layer %2==0) {
                cout << (num +layer)/2+1 << " ";
            // Outer layer
            } else {
                // Char
                char value = 'A' + (layer/2); // Start from 'A' for layer 1
                cout << value<< " "; // Print the corresponding character
            }
        }
        cout << endl; 
    }
}

int main() {
    int n;
    cout << "Enter an odd number: ";
    cin >> n; 

    // Check if the number is odd
    if (n % 2 == 0) {
        cout << "Please enter an odd number." << endl;
        return 1;
    }

    generatePattern(n);
    return 0;
}
