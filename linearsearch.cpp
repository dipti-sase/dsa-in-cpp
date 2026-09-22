#include<iostream>
using namespace std;
int linear_search(int a[], int n, int x)
{
    for(int i=0;i<n;i++)
    {
        if (a[i]==x)
{
    return i;
}
    }
    return -1;
}
int main()
{
    int n;
    int a[20];
    cout<<"Enter the size of array:";

    cin>>n;
    cout<<"Enter"<<n<<"Integers:"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int x;
    cout<<"Enter the target element search for:";
    cin>>x;
    int location=linear_search(a,n,x);
    if (location !=-1)
    {
        cout<<"Element"<<x<<"Found at index:"<<location<<endl;
    }
    else
    {
        cout<<"Element"<<x<<"Not found in the array"<<endl;
    }
    return 0;
 }
    


 //D:\Dipti>cd "d:\Dipti\" && g++ linearsearch.cpp -o linearsearch && "d:\Dipti\"linearsearch
//Enter the size of array:5
//Enter5Integers:
//10
//20
//30
//40
//50
//Enter the target element search for:30
//Element30Found at index:2
