/*Print pattern like this, for n=5
1 
A * B 
2 * 3 * 4 
C * D * E * F 
5 * 6 * 7 * 8 * 9 
9 * 8 * 7 * 6 * 5 
F * E * D * C 
4 * 3 * 2 
B * A 
1
*/
  
#include <iostream>
using namespace std;

int main() {
    int n=5;
    int num=1;
    char ch='A';
    for(int i=1; i<=n; i++){
            for(int j=1; j<=2*i-1;j++){
            if(j%2==0){
                //print *
                cout<<"* ";
            }else{
                //print others
            if(i%2!=0){
                //num print
               if(j%2!=0){
                    cout<<num++<<" ";
                }
                }else{
                    //ch print
                    if(j%2!=0){
                        cout<<ch++<<" ";
                    }
            }
                
            }
        } cout<<endl;
    }

    for(int i=n;i>=1;i--){
        
        for(int j=1;j<=2*i-1;j++){
            if(j%2==0){
                cout<<"* ";
            }else{
             //ch print
                 if(i%2==0){
                     if(j%2!=0){
                         cout<<--ch<<" ";
                     }
                 }else{
                     //num print
                     if(j%2==1){
                         cout<<--num<<" ";
                     }
                 }
            }
        }cout<<endl;
    }

    return 0;
}

