#include <iostream>
#include <string>

using namespace std;

class A {
   private:
    /* data */
   public:
    A(string a);
    ~A();
    void Announce();
};

A::A(string a) { cout << "A:" << a << endl; }
void A::Announce() { cout << "this is function" << endl; }

A::~A() {}

class B : public A {
   private:
    /* data */
   public:
    B(string a);
    ~B();
    virtual void Hi() = 0;
    void HiB();
};

B::B(string a) : A(a) { cout << "B:" << a << endl; }

B::~B() {}

class C : public B {
   private:
    /* data */
   public:
    C(string a);
    ~C();
    void Hi();
};

C::C(string a) : B(a) { cout << "C:" << a << endl; }

C::~C() {}

class D : public C {
   private:
    /* data */
   public:
    D(string a);
    ~D();
    void Hi();
};

D::D(string a):C(a) { cout << "D:" << a << endl; }

D::~D() {}

int main() {
    B *b = new D("D");
    b->HiB();
    b->Hi();
    system("pause");
}

void B::HiB() {
    cout << "this is B function" << endl;
}

void C::Hi() { cout << "this is C function" << endl; }

void D::Hi() { cout << "this is D function" << endl; }