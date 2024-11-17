#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

//gcd calculation
int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

//root calculation 
pair<int, int> findRoot(int n) {
    int sum = 1;
    int remainder = abs(n);

    // Factorize the number
    for (int i = 2; i * i <= remainder; i++) {
        while (remainder % (i * i) == 0) {
            sum *= i;
            remainder /= (i * i);
        }
    }

    return {sum, remainder};
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
string cubicFactor(int a, int b, int c, int d) {
    
    cout<<a<<"x^3";
    cout<<(b >= 0 ? " + " : " - ") << abs(b) << "x^2";
    cout<<(c >= 0 ? " + " : " - ") << abs(c) << "x";
    cout<<(d >= 0 ? " + " : " - ") << abs(d) <<" : " ;

    //taking common from a,b,c to simplify the calculations
    int cubicCommon=gcd(gcd(a,b),gcd(c,d));

    
    //simplifying a,b,c;
    a/=cubicCommon;
    b/=cubicCommon;
    c/=cubicCommon;
    d/=cubicCommon;
    if(a<0){
        cubicCommon*=(-1);
        a*=(-1);
        b*=(-1);
        c*=(-1);
        d*=(-1);    
    }

    // cout<<"a: "<<a<<endl<<
    // "b: "<<b<<endl<<
    // "c: "<<c<<endl<<
    // "d: "<<d<<endl;

    // Find factors of a and d
    vector<int> factorsA = findFactors(a);
    vector<int> factorsD = findFactors(d);

    bool rootFound = false;
    int quadA, quadB,quadC;
    string cubeFactor;
    // Try each combination of factors of d/a
    for (int factorD : factorsD) {
        for (int factorA : factorsA) {
            double root = static_cast<double>(factorD) / factorA;
            if (checkRoot(a, b, c, d, root)) {
                rootFound = true;
                // Construct the root string with a ternary operator
                // cout<<endl<<"factorD: "<<factorD<<endl<<"factorA: "<<factorA<<endl;
                int numerator=factorD*(-1);
                int denominator=factorA;
               
                cubeFactor ="("
                    + ((abs(denominator)==1)?((denominator==1)? "" : "-"):
                    to_string(denominator)) + "x " +(((numerator)<0)? "-" :"+ ") + to_string(abs(numerator))+")";
               
                quadA=a/denominator;
                quadB=(b-(quadA*numerator))/denominator;
                quadC=d/numerator;
        //    cout<<endl<<quadA<<endl<<quadB<<endl<<quadC<<endl;
                goto endLoops; 
                
            }
        }
    } 
    if (!rootFound) {
     
        return "No valid root found.";  // Return message if no root is found
    }
endLoops:
    // Quad factors  

     //taking common from a,b,c to simplify the calculations
    
    if(quadA<0){
        cubicCommon*=(-1);
        quadA*=(-1);
        quadB*=(-1);
        quadC*=(-1);
    }
    //set ac
    int ac=quadA*quadC;

    int factor1=0,factor2=0; //factor1=0, factor2=0 means middle term is not possible
    //find middle term factors 
    for (int i = -abs(ac); i <= abs(ac); i++) {
        if (i != 0 && (ac) % i == 0) { // avoid division by zero
            int j = (ac) / i;
            if (i + j == quadB) {
                factor1 = i; //let's 5x^2 + 6x -5x -6,  fac1=-5;
                factor2 = j;//let's 5x^2 + 6x -5x -6, fac2=6;
                break;
            }
        }
    } 

    if(factor1!=0){
        //middle term possible
        int common1=abs(gcd(quadA,factor1)); //let's 5x^2 + 6x -5x -6, common1=(gcd(5,-5))=-5
        int common2=abs(gcd(factor2,quadC)); //let's 5x^2 + 6x -5x -6, common1=(gcd(-6,6))=6

        int p=quadA/common1; //5/-5=-1,  p in (px+q)(rx+s)
        int q=factor1/common1; // -5/-5=1, q in (px+q)(rx+s)
        int r=factor2/common2; // 6/6=1, r in (px+q)(rx+s)
        int s=quadC/common2; // -6/6=-1, s in (px+q)(rx+s)

        
        // string overallCommonFactorStr = to
        string overallCommonFactor = 
                (abs(cubicCommon) == 1) ? 
                (cubicCommon == 1) ? "" : "-" 
                : to_string(cubicCommon);
        // Print the first factor with the common factor applied
        string firstFactor = "(" + (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) +
                             (q >= 0 ? "+ " : "- ") + to_string(abs(q)) + ")";
        string secondFactor = "(" + (common1 == 1 ? "x " : (common1 == -1 ? "-x " : to_string(common1) + "x ")) +
                              (common2 >= 0 ? "+ " : "- ") + to_string(abs(common2)) + ")";
        
        

        return overallCommonFactor + firstFactor + secondFactor + cubeFactor;
    }else{
        //middle term isn't possible
        //calculate discriminant
        int divisor = 2*quadA;  //2a

        int discriminant = (quadB*quadB)-(4*quadA*quadC);

        pair<int, int> root = findRoot(discriminant);
        int takeCommon=gcd(gcd(divisor,quadB),root.first);
        divisor/=takeCommon;
        b/=takeCommon;
        root.first/=takeCommon;
        int common=cubicCommon*takeCommon;

        int balanceFactor=2*divisor;
        int factor=gcd(balanceFactor,common);
        common/=factor;
        balanceFactor/=factor;

        string overallCommonFactor ="("+ ((balanceFactor == 1) ? to_string(common) :
                            (balanceFactor == -1) ? to_string(-common) :
                            to_string(common) + "/" + to_string(balanceFactor)) + ")";

        //common/balance factor ko handle kar lena bhai mera pilis
        string unrealPart = (discriminant < 0 ? "i*" : "") + 
                (root.first == 1 ? "" : to_string(abs(root.first))) + 
                "(" + to_string(root.second) + "^0.5)";
        string realPart=(divisor == 1 ? "" : to_string(divisor)) + "x" + 
                  (b == 0 ? "" : (b < 0 ? " - " + to_string(abs(b)) : " + " + to_string(b)));
        string firstFactor= "(" + realPart + "+" + unrealPart + ")";
        string secondFactor= "(" + realPart + "-" + unrealPart + ")";

        return overallCommonFactor + firstFactor + secondFactor + cubeFactor;
    }
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
    // cubicFactor(2, 11, 17, 6);s
    // cubicFactor(30, 13, -13, -6);
    // cubicFactor(10, -3, -37, 18);
    // cubicFactor(1, -41, -1, 41);
    // cout<< cubicFactor(2, -1, -82, 41)<<endl;
    // cout<<cubicFactor(4, 22, 34, 12)<<endl; //issue
    // cout<<cubicFactor(1, -1, 41, -41); 
    // cout<<cubicFactor(10, -3, -37, 18)<<endl;
    // cout<<cubicFactor(-10, 3, 37, -18)<<endl;
    // cout<<cubicFactor(20, -6, -74, 36)<<endl;
    // cout<<cubicFactor(-20, 6, 74, -36)<<endl;
    // cout<<cubicFactor(10, -11, -51, -18)<<endl;
    // cout<<cubicFactor(-10, 11, 51, 18)<<endl;
    //  cubicFactor(1, -6, 11, -6); 
    // cubicFactor(2, 4, -2, -4); 
    //  cout<<cubicFactor(1,1,1,1)<<endl; 
    //  //cubicFactor(1,2,1,2);-getting error 
    // // cout<< cubicFactor(1,2,3,4)<<endl;
    // cout<< cubicFactor(2,6,-26,-30)<<endl;
    // cout<< cubicFactor(-2,-6,26,30)<<endl;
    cout<< cubicFactor(2,2,82,82)<<endl;
    cout<< cubicFactor(-2,-2,-82,-82)<<endl;
    cout<< cubicFactor(1,1,-41,-41)<<endl;
    cout<< cubicFactor(-1,-1,41,41)<<endl;
    cout<< cubicFactor(2,2,-82,-82)<<endl;

    //handle if the first cubic factor has any common factor, if yes then multiply with the overall common factor from quadfactor, also check if factorA and factorD is <0 then take -1 common
    return 0;
}
