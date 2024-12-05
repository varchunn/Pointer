#include <iostream>
#include "SmartPointers.h"
using namespace std;

struct Test 
{
    int value;
    Test(int v) : value(v) { cout << "Test object created"<<endl; }
    ~Test() { cout << "Test object destroyed"<<endl; }
    void display() { cout << "Value: " << value << endl; }
};

int main() 
{
    cout << "Testing UniquePtr:\n";
    UniquePtr<Test> uptr(new Test(10));
    uptr->display();

    UniquePtr<Test> uptr2 = move(uptr);
    if (!uptr)
    {
        cout << "uptr is now empty"<<endl;
    }
    uptr2->display();

    cout << "\nTesting SharedPtr:\n";
    SharedPtr<Test> sptr1(new Test(20));
    {
        SharedPtr<Test> sptr2 = sptr1;
        sptr2->display();
        cout << "End of inner scope\n";
    }
    sptr1->display();

    return 0;
}
