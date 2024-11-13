//Factorization of Quadratic Polynomial 
// ax^2 + bx + c = (px+q)(rx+s) or (px+iq)(px-iq)
#include <iostream>
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
//factorisation
string factor(int a, int b, int c){
    int tempa=a;
    int tempb=b;
    int tempc=c;
    //if a<0, * with -1 and at last add negative before the result
    if(a<0){
        a*=(-1);
        b*=(-1);
        c*=(-1);
    }
    
    //finding middle term factors
    int fac1=0;
    int fac2=0;

    //set ac
    int ac=a*c;

    // Find two numbers that multiply to (a * c) and add up to b
    for (int i = -abs(ac); i <= abs(ac); i++) {
        if (i != 0 && (ac) % i == 0) { // avoid division by zero
            int j = (ac) / i;
            if (i + j == b) {
                fac1 = i; //let's 5x^2 + 6x -5x -6,  fac1=-5;
                fac2 = j;//let's 5x^2 + 6x -5x -6, fac2=6;
                break;
            }
        }
    }

    cout<<tempa<<"x^2";
    cout<<(tempb >= 0 ? " + " : " - ") << abs(tempb) << "x";
    cout<<(tempc >= 0 ? " + " : " - ") << abs(tempc) <<" : " ;

    //check if middle term factorisation possible or not
    if(fac1==0){
        int p;
        //calculate discriminant
        int discriminant = (tempb*tempb)-(4*tempa*tempc);
        
        p = 2*tempa;
        int commonFactor= (p*p)/tempa; //to match the value of a
      
        string realPart = to_string(p) + "x" + (tempb == 0 ? "" : (tempb < 0 ? " - " + to_string(abs(tempb)) : " + " + to_string(tempb)));

        string q=root(discriminant);
        if (discriminant < 0) {
            q="i*"+ q;
        }
        
        cout<<"\n\t\t";
        string factor1="(" + realPart + " + " + q + ")";
        string factor2="(" + realPart + " - " + q + ")";
        return "(1/" + to_string(commonFactor) + ")" + factor1 + factor2;
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
        int overallCommonFactor= commonFactor1 * commonFactor2;

       // Print output with condition to avoid overlapping sign and proper coefficient
       cout<<"\n\t\t";
        if (tempa < 0) {        //handling -a
            overallCommonFactor*=-1;
        }
        // string overallCommonFactorStr = to
        string overallCommonFactorStr = (abs(overallCommonFactor) == 1) ? (overallCommonFactor == 1) ? "" : "-" : to_string(overallCommonFactor);
            
        // Print the first factor with the common factor applied
        string firstFactor="("+ (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) +
                            (q >= 0 ? "+ " : "- ") + to_string(abs(q)) + ")";

        // Print the second factor with the common factor applied
        string secondFactor="(" + (r == 1 ? "x " : (r == -1 ? "-x " : to_string(r) + "x ")) +
                            (s >= 0 ? "+ " : "- ") + to_string(abs(s)) + ")";
        
        return (overallCommonFactorStr + firstFactor + secondFactor);
        
    }
    
}
int main() {
    int a,b,c;
    cout << "Coefficient of x^2: ";
    cin>>a;
    cout << "Coefficient of x: ";
    cin>>b;
    cout << "Enter value of c: ";
    cin>>c;

    cout<<factor(a,b,c);
    
    return 0;
}
