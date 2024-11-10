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

//factorisation
void factor(int a, int b, int c){
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
        string realPart = (tempb < 0) ? 
                  (to_string(p) + "x - " + to_string(abs(tempb))) : 
                  (to_string(p) + "x + " + to_string(tempb));

        string q;
        if (discriminant < 0) {
            q="i("+to_string(abs(discriminant))+"^.5)";
        }else{
            q="("+to_string(abs(discriminant))+"^.5)";
        }
        

        cout << "(1/" + to_string(commonFactor) + ")(" + realPart + " + " + q + ")(" + realPart + " - " + q + ")";
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
        if (tempa < 0) {        //handling -a
            overallCommonFactor*=-1;
        }
        // Check if the overall common factor is 1 or -1
        if (overallCommonFactor == 1 || overallCommonFactor == -1) {
            // If the overall common factor is -1, start with a negative sign
            if (overallCommonFactor == -1) cout << "-";

            cout<<"(";
            // Print the first factor
            cout << (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) 
                << (q >= 0 ? "+ " : "- ") << abs(q) << ") ";

            // Print the second factor
            cout << "(" << (r == 1 ? "x " : (r == -1 ? "-x " : to_string(r) + "x ")) 
                << (s >= 0 ? "+ " : "- ") << abs(s) << ")";
        } else {
            // If the overall common factor is not 1 or -1, print it as a multiplier
            cout << overallCommonFactor << "(";

            // Print the first factor with the common factor applied
            cout << (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) 
                << (q >= 0 ? "+ " : "- ") << abs(q) << ") ";

            // Print the second factor with the common factor applied
            cout <<"(" << (r == 1 ? "x " : (r == -1 ? "-x " : to_string(r) + "x ")) 
                << (s >= 0 ? "+ " : "- ") << abs(s) << ")";
        }
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

    factor(a,b,c);
    
    //test cases
    // factor(-1,2,-1);// Expected output:(x + 1) (x + 1)
    // cout<<endl;
    // factor(-1,-2,-1); //Expected output: -(x + 1) (x + 1)
    //  cout<<endl;
    // factor(3, 10, 3);        // Expected output: (x + 3)(3x + 1)
    // cout << endl;
    // factor(9, 30, 9);        // Expected output: 3(x + 3)(3x + 1)
    // cout << endl;
    // factor(1, -1, -2);       // Expected output: (x + 1)(x - 2)
    // cout << endl;
    // factor(3, -10, 3);       // Expected output: (x - 3)(3x - 1)    
    // cout << endl;
    // factor(8, 6, -2);        // Expected output: 2(4x - 1)(x + 1)
    // cout << endl;
    // factor(8, 6, 2);         // Expected output: Factorization is not possible
    // cout << endl;
    // factor(2, 7, -15);       // Expected output: (2x - 3)(x + 5)
    // cout << endl;
    // factor(1, 1, -1);       // Expected output: Factorization is not possible
    // cout << endl;
    // factor(1, 6, 8);       // Expected output: (x + 2)(x + 4)
    // cout << endl;
    // factor(1, -5, 6);          // Expected output: (x - 2)(x - 3)
    // cout << endl;
    // factor(1, 4, 4);           // Expected output: (x + 2)(x + 2)
    // cout << endl;
    // factor(2, 7, 3);           // Expected output: (2x + 1)(x + 3)
    // cout << endl;
    // factor(1, 3, -10);         // Expected output: (x + 5)(x - 2)
    // cout << endl;
    // factor(2, 1, -6);          // Expected output: (2x - 3)(x + 2)
    // cout << endl;
    // factor(-8, -15, 2);      // Expected output: (x + 2)(-8x + 1)
    // cout << endl;
    // factor(8, 14, -15);        // Expected output: (4x-3)(2x+5)
    // cout << endl;
    // factor(4, -4, -5);         // Expected output: Factorization is not possible
    // cout << endl;
    // factor(5, 1, -6);          // Expected output: (x-1) (5x+6)
    // cout << endl;
    // factor(4, -1, -5);         // Expected output: (4x-5)(x+1)
    // cout << endl;
    // factor(6, 11, 5);          // Expected output: (6x + 5)(x + 1)
    // cout << endl;
    // factor(10, 7, 6);          // Expected output: Factorization is not possible
    // cout << endl;
    // factor(8, 14, -15);        // Expected output: (4x-3)(2x+5)
    // cout << endl;
    // factor(6, 17, 5);        // Expected output: (3x + 1) (2x+ 5)
    // cout << endl;
    // factor(9, 0, -16);        // Expected output: (3x + 4)(3x – 4)
    // cout << endl;
    // factor(1, -10, 25);        // Expected output: (x – 5)(x – 5) 
    // cout << endl;
    return 0;
}
