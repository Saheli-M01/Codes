//Factorization of Quadratic Polynomial 
// ax^2 + bx + c = (px+q)(rx+s) or (px+iq)(px-iq)
//Factorization of Quadratic Polynomial 
// ax^2 + bx + c = (px+q)(rx+s) or (px+iq)(px-iq)
#include <iostream>
#include <cmath> 
#include <vector>
#include <sstream>
using namespace std;

//gcd calculation
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
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
//factorisation
string factor(int a, int b, int c){
     if (a == 0) {
        return "Invalid input: Coefficient of x^2 cannot be zero.";
    }
    cout<<a<<"x^2";
    cout<<(b >= 0 ? " + " : " - ") << abs(b) << "x";
    cout<<(c >= 0 ? " + " : " - ") << abs(c) <<" : " ;

    //taking common from a,b,c to simplify the calculations
    int common=gcd(gcd(a,b),c);

    //simplifying a,b,c;
    a/=common;
    b/=common;
    c/=common;
    
    if(a<0){
        common*=(-1);
        a*=(-1);
        b*=(-1);
        c*=(-1);
    }
    //set ac
    int ac=a*c;

    int factor1=0,factor2=0; //factor1=0, factor2=0 means middle term is not possible
    //find middle term factors 
    for (int i = -abs(ac); i <= abs(ac); i++) {
        if (i != 0 && (ac) % i == 0) { // avoid division by zero
            int j = (ac) / i;
            if (i + j == b) {
                factor1 = i; //let's 5x^2 + 6x -5x -6,  fac1=-5;
                factor2 = j;//let's 5x^2 + 6x -5x -6, fac2=6;
                break;
            }
        }
    } 

    if(factor1!=0){
        //middle term possible
        int common1=abs(gcd(a,factor1)); //let's 5x^2 + 6x -5x -6, common1=(gcd(5,-5))=-5
        int common2=abs(gcd(factor2,c)); //let's 5x^2 + 6x -5x -6, common1=(gcd(-6,6))=6

        int p=a/common1; //5/-5=-1,  p in (px+q)(rx+s)
        int q=factor1/common1; // -5/-5=1, q in (px+q)(rx+s)
        int r=factor2/common2; // 6/6=1, r in (px+q)(rx+s)
        int s=c/common2; // -6/6=-1, s in (px+q)(rx+s)

        // string overallCommonFactorStr = to
        string overallCommonFactor = 
                (abs(common) == 1) ? 
                (common == 1) ? "" : "-" 
                : to_string(common);
        // Print the first factor with the common factor applied
        string firstFactor = "(" + (p == 1 ? "x " : (p == -1 ? "-x " : to_string(p) + "x ")) +
                             (q >= 0 ? "+ " : "- ") + to_string(abs(q)) + ")";
        string secondFactor = "(" + (common1 == 1 ? "x " : (common1 == -1 ? "-x " : to_string(common1) + "x ")) +
                              (common2 >= 0 ? "+ " : "- ") + to_string(abs(common2)) + ")";
        
        

        return (overallCommonFactor + firstFactor + secondFactor);
    }else{
        //middle term isn't possible
        //calculate discriminant
        int divisor = 2*a;  //2a

        int discriminant = (b*b)-(4*a*c);

        pair<int, int> root = findRoot(discriminant);
        int takeCommon=gcd(gcd(divisor,b),root.first);
        divisor/=takeCommon;
        b/=takeCommon;
        root.first/=takeCommon;
        common*=takeCommon;

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


        return overallCommonFactor + firstFactor + secondFactor;
    }


    

}

int main() {
    // int a,b,c;
    // cout << "Coefficient of x^2: ";
    // cin>>a;
    // cout << "Coefficient of x: ";
    // cin>>b;
    // cout << "Enter value of c: ";
    // cin>>c;

    // cout<<factor(1,2,9)<<endl;
    // cout<<factor(2,4,18)<<endl;
    cout<<factor(-4,-1,-41)<<endl;
    cout<<factor(4,1,41)<<endl;
    // cout<<factor(1,2,1)<<endl;
    // cout<<factor(-1,-2,-1)<<endl;
    // cout<<factor(2,9,7)<<endl;
    // cout<<factor(-4,-18,-14)<<endl;
    // cout<<factor(5,1,-6)<<endl;
    // cout<<factor(-5,-1,6)<<endl;
    // cout<<factor(5,-1,6)<<endl;
    // cout<<factor(-5,1,-6)<<endl;
    // cout<<factor(-4,0,4)<<endl;
    cout<<factor(1,-2,-6)<<endl;
    cout<<factor(-1,2,6)<<endl;
    cout<<factor(-10,20,-120)<<endl;
    cout<<factor(10,-20,120)<<endl;
    
    return 0;
}
