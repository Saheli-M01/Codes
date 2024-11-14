#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//gcd calculation
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

//root calculation 
string root(int n) {
    n=abs(n);
    int sum = 1;

    // Factorize the number
    for (int i = 2; i * i <= n; i++) {
        if (n % (i * i) == 0) {
            sum *= i;
            n /= i * i;
        }
    }

    // Return root as a string
    return (sum == 1 ? (n != 1 ? "(" + to_string(n) + "^0.5)" : "1") : to_string(sum) + (n != 1 ? "*(" + to_string(n) + "^0.5)" : ""));
}

// Function to find factors of a number
vector<int> findFactors(int num) {
    vector<int> factors;
    for (int i = 1; i <= abs(num); ++i) {
        if (num % i == 0) {
            factors.push_back(i);
            if (i != abs(num) / i) {
                factors.push_back(-i);  // Account for negative factors
            }
        }
    }
    return factors;
}

// Check if the value of root satisfies the equation ax^3 + bx^2 + cx + d = 0
bool checkRoot(int a, int b, int c, int d, double root) {
    double result = a * pow(root, 3) + b * pow(root, 2) + c * root + d;
    return (result == 0);
}

// Function to perform cubic factorization
void cubicFactor(int a, int b, int c, int d) {
    
    cout<<a<<"x^3";
    cout<<(b >= 0 ? " + " : " - ") << abs(b) << "x^2";
    cout<<(c >= 0 ? " + " : " - ") << abs(c) << "x";
    cout<<(d >= 0 ? " + " : " - ") << abs(d) <<" : " ;
    // Find factors of a and d
    vector<int> factorsA = findFactors(a);
    vector<int> factorsD = findFactors(d);

    // Try each combination of factors of d/a
    for (int factorD : factorsD) {
        for (int factorA : factorsA) {
            double root = static_cast<double>(factorD) / factorA;
            if (checkRoot(a, b, c, d, root)) {
                // Construct the root string with a ternary operator
                int C=d/(-1)*factorD;
                int A=a/factorA;
                int B=(b-(-1*a*factorD))/factorA;

                int commonFactor= gcd((-1*factorD), factorA);
                factorD=(factorD/commonFactor)*(-1);
                factorA/=commonFactor;
                string cubeFactor ="("+ to_string(factorA) + "x " +((factorD<0)? "-" :"") + to_string(abs(factorD))+")";                
                
    //quad factor
                int tempa=A;
                int tempb=B;
                int tempc=C;
                //if a<0, * with -1 and at last add negative before the result
                if(A<0){
                    A*=(-1);
                    B*=(-1);
                    C=d*(-1);
                }
                
                //finding middle term factors
                int fac1=0;
                int fac2=0;

                //set ac
                int ac=A*C;

                // Find two numbers that multiply to (a * c) and add up to b
                for (int i = -abs(ac); i <= abs(ac); i++) {
                    if (i != 0 && (ac) % i == 0) { // avoid division by zero
                        int j = (ac) / i;
                        if (i + j == B) {
                            fac1 = i; //let's 5x^2 + 6x -5x -6,  fac1=-5;
                            fac2 = j;//let's 5x^2 + 6x -5x -6, fac2=6;
                            break;
                        }
                    }
                }


                //check if middle term factorisation possible or not
                if(fac1==0){
                    int p;
                    //calculate discriminant
                    int discriminant = (tempb*tempb)-(4*tempa*tempc);
                    
                    p = 2*tempa;
                    commonFactor*= ((p*p)/tempa); //to match the value of a
                
                    string realPart = to_string(p) + "x" + (tempb == 0 ? "" : (tempb < 0 ? " - " + to_string(abs(tempb)) : " + " + to_string(tempb)));

                    string q=root(discriminant);
                    if (discriminant < 0) {
                        q="i*"+ q;
                    }
                    
                    string factor1="(" + realPart + " + " + q + ")";
                    string factor2="(" + realPart + " - " + q + ")";
                    string quadFactors="(1/" + to_string(commonFactor) + ")" + factor1 + factor2;
                }else{
                    int common1=abs(gcd(a,fac1)); //let's 5x^2 + 6x -5x -6, common1=(gcd(5,-5))=-5
                    int common2=abs(gcd(c,fac2)); //let's 5x^2 + 6x -5x -6, common1=(gcd(-6,6))=6

                    int term00=a/common1; //term00=5/-5=-1, term00 is p in (px+q)(rx+s)
                    int term01=fac1/common1; //term00=-5/-5=1, term01 is q in (px+q)(rx+s)
                    int term10=fac2/common2; //term00=6/6=1, term10 is r in (px+q)(rx+s)
                    int term11=c/common2; //term00=-6/6=-1, term11 is s in (px+q)(rx+s)

                    //check if the factors are same or in (-1)*factor format
                    if(term00 == (-1)*term10 && term01 == (-1)* term11 ) {
                        common2*=(-1);
                    }
                
                    //check for any common factor
                    int commonFactor1 = gcd(term00, term01); //check if there is any common factor b/w p&q
                    int commonFactor2 = gcd(common1, common2); //check if there is any common factor b/w r&s
                    //calculating final p,q,r,s values
                    int p = term00 / commonFactor1;
                    int q = term01 / commonFactor1;
                    int r = common1 / commonFactor2;
                    int s = common2 / commonFactor2;
                    commonFactor= commonFactor1 * commonFactor2 ;

                // Print output with condition to avoid overlapping sign and proper coefficient

                    if (tempa < 0) {        //handling -a
                        commonFactor*=-1;
                    }
                    // string overallCommonFactorStr = to
                    string overallCommonFactor = (abs(commonFactor) == 1) ? (commonFactor == 1) ? "" : "-" : to_string(commonFactor);
                        
                    // Print the first factor with the common factor applied
                    string firstFactor="("+ (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) +
                                        (q >= 0 ? "+ " : "- ") + to_string(abs(q)) + ")";

                    // Print the second factor with the common factor applied
                    string secondFactor="(" + (r == 1 ? "x " : (r == -1 ? "-x " : to_string(r) + "x ")) +
                                        (s >= 0 ? "+ " : "- ") + to_string(abs(s)) + ")";
                    
                    string quadFactors= (overallCommonFactor + firstFactor + secondFactor);
        
    }
                string factor = quadFactors + cubeFactor;
                cout<<factor;
            }
            
        }
    }
    cout << "No rational root found." << endl;

}

int main() {
    int a, b, c, d;

    // cout << "Coefficient of x^3: ";
    // cin >> a;
    // cout << "Coefficient of x^2: ";
    // cin >> b;
    // cout << "Coefficient of x: ";
    // cin >> c;
    // cout << "Constant term: ";
    // cin >> d;

    // cubicFactor(a, b, c, d);
    // cubicFactor(90, -101, -63, 18);
    // cubicFactor(2, 11, 17, 6);
    // cubicFactor(30, 13, -13, -6);
    // cubicFactor(10, -3, -37, 18);
    // cubicFactor(1, -41, -1, 41);
    // cubicFactor(2, -1, -82, 41);
    // cubicFactor(4, 22, 34, 12); //issue
    // cubicFactor(1, -1, 41, -41); 
    //  cubicFactor(1, -6, 11, -6); 
    // cubicFactor(2, 4, -2, -4); 
    //  cubicFactor(1,1,1,1); 
     //cubicFactor(1,2,1,2);-getting error 
    cubicFactor(1,2,3,4);
    //handle if the first cubic factor has any common factor, if yes then multiply with the overall common factor from quadfactor, also check if factorA and factorD is <0 then take -1 common
    return 0;
}
