/*Step 1: Sort the Array: Sort arr in ascending order with a time complexity of O(nlogn).
Step2:Remove Duplicates  by hashing
Step3: Split the Array :Split the sorted array into two equal halves. If 𝑛 is odd, the first half should contain one extra element.
Ste4: Reverse Each Half using function..
Step5: Prepare for the next set of transformations.
Calculate the sum of even numbers in the first half (evenSum1) and the sum of odd numbers in the second half (oddSum2). 
For each element in the first half:
If the element is even, subtract oddSum2. 
If the element is odd, add evenSum1. 
For each element in the second half: 
If the element is odd, subtract evenSum1. 
If the element is even, add oddSum2.
Step 6: Merge and print the array
ex-
i/p:5 5 4 3 2 1     o/p:5 -3 3 3 9
i/p:6 3 9 1 190 5 3      o/p:5 3 1 199 9 15
*/
#include<iostream>
#include<vector>
#include <unordered_set>
using namespace std;
//remove duplicates by hashing
vector<int> removeDuplicates(const vector<int> &arr) {
    unordered_set<int> uniqueElements;
    vector<int> result;

    for (int x : arr) {
        // If the element is not already in the set, add it to the result
        if (uniqueElements.find(x) == uniqueElements.end()) {
            uniqueElements.insert(x);
            result.push_back(x);
        }
    }

    return result;
}
//merge Sort
void merge(vector<int> &arr, int s, int e){ //s=start, e=end
    int mid = s-(s-e)/2;

    int lengthLeft= mid-s+1;
    int lengthRight=e-mid;

    int *left= new int[lengthLeft];
    int *right= new int[lengthRight];
    
    //copying values
    int originalArrayIndex =s;
    for(int i=0;i<lengthLeft;){
        left[i++]=arr[originalArrayIndex++];
    }
    for(int i=0;i<lengthRight;){
        right[i++]=arr[originalArrayIndex++];
    }
    //merge
    int leftIndex=0;
    int rightIndex=0;
    int arrayIndex=s;

    //merging final values
    while(leftIndex < lengthLeft && rightIndex < lengthRight){
        if(left[leftIndex] < right[rightIndex]){
            arr[arrayIndex++]=left[leftIndex++];
        }else{
            arr[arrayIndex++]=right[rightIndex++];
        }
    }
    //check if any array complets and anothe one left with element
    while(leftIndex < lengthLeft){
        arr[arrayIndex++]= left[leftIndex++];
    }
    while(rightIndex < lengthRight){
        arr[arrayIndex++]= right[rightIndex++];
    }
    //deleting the extra arrays taken 
    delete[] left;
    delete[] right;
    
}
void mergeSort(vector<int> &arr, int s, int e){
    if(s>=e){
        return;
    }
    int mid=s-(s-e)/2;
    mergeSort(arr, s, mid);
    mergeSort(arr, mid+1, e);

    merge(arr,s,e);
}

//reverse array
void reverseArray(vector<int> &arr){
    int start= 0;
    int end=arr.size()-1;

    while(start < end){
        swap(arr[start++], arr[end--]);
    }
}

//calculate odd sum of array
int oddSum(vector<int> &arr){
    int sum=0;
    for(int i=0; i<arr.size();i++){
        if(arr[i]%2!=0) sum+=arr[i];
    }
    return sum;
}
//calculate even sum of array
int evenSum(vector<int> &arr){
    int sum=0;
    for(int i=0; i<arr.size();i++){
        if(arr[i]%2==0) sum+=arr[i];
    }
    return sum;
}

//modified array
void modifiedArray(vector<int> &arr, int n){
    //step1: Sort the array 
    mergeSort(arr,0,n-1);

    //step2:Remove duplicates from array by hashing
    vector<int> result = removeDuplicates(arr);

    //step3:Split the arrays into two halves. If 𝑛 is odd, the first half should contain one extra element.
    int lengthLeft = result.size() / 2;
    int lengthRight = result.size() / 2;

    if(result.size()%2!=0) lengthLeft++;
    
    vector<int> left(lengthLeft);
    vector<int> right(lengthRight);
    int head=0;
    //copying elements in left and right array and
    for(int i=0;i<lengthLeft;){
        left[i++]=result[head++];
    }
    for(int i=0;i<lengthRight;){
        right[i++]=result[head++];
    }
    //Ste4: Reverse Each Half using recursion.
    reverseArray(left);
    reverseArray(right);

    //step5:
    int even_Sum= evenSum(left);
    int odd_Sum= oddSum(right);

    for(int i=0;i<lengthLeft;i++){  //For each element in the first half:If the element is even, subtract oddSum.If the element is odd, add evenSum. 
        if(left[i]%2==0){
            left[i]-=odd_Sum;
        }else{
            left[i]+=even_Sum;
        }
    }
     for(int i=0;i<lengthRight;i++){  //For each element in the second half:If the element is odd, subtract evenSum. If the element is even, add oddSum.
        if(right[i]%2==0){
            right[i]+=odd_Sum;
        }else{
            right[i]-=even_Sum;
        }
    }
    //step6:Merge and print the array
    //merging final values
    for (int i = 0; i < lengthLeft; i++) {
        result[i] = left[i];
    }
    for (int i = 0; i < lengthRight; i++) {
        result[lengthLeft + i] = right[i];
    }

    //printing the final array
    for(int num : result) cout<<num<< " ";
}

int main(){
    int n;
    cout<<"Enter number of array elements: ";
    cin>>n;
    cout<<"Enter array elements: ";
    vector<int> arr(n);
    for(int &x: arr){
        cin>>x;
    }
    modifiedArray(arr,n);
    return 0;

}
