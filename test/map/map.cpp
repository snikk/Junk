#include <stdio.h>
#include <stdlib.h>
#include <map>

class MyClass {
public: 
    int param1;
    float param2;

    //virtual void override() = 0;
};

class Derived : public MyClass {
public:
    double param3;
    bool param4;
};

struct cmp_str {
    bool operator()(const char* lhs, const char* rhs) const {
        printf("lhs = %s | rhs = %s\n", lhs, rhs);
        return std::strcmp(lhs, rhs) < 0;
    }
};

int main(int argc, char** argv) {
    std::map<char*, MyClass*, cmp_str> m;

    MyClass item1;
    item1.param1 = 100;
    item1.param2 = 1234.5678f;
    MyClass item2;
    item2.param1 = 444;
    item2.param2 = 8765.4321f;

    Derived der;
    der.param1 = 998877;
    der.param2 = 22993388.44775566;
    der.param3 = 22993388.44775566;
    der.param4 = true;

    MyClass* pItem1 = (MyClass*) malloc(sizeof(MyClass));
    MyClass* pItem2 = (MyClass*) malloc(sizeof(MyClass));
    MyClass* pDerived = (Derived*) malloc(sizeof(Derived));

    m["test"] = &item1;
    MyClass* test = m["test"];
    *test = item1;
    m["another"] = &item2;
    test->param1 = 999;
    test->param2 = 222.22222;
    m["Third?"] = (MyClass*) malloc(sizeof(MyClass));
    auto third = m["Third?"];
    third->param1 = 777;
    third->param2 = 4747.47474;

    m["derived"] = &der;

    for (auto it = m.begin(); it != m.end(); ++it) {
        printf("m[%s] = { param1 = %d, param2 = %f }\n", it->first, it->second->param1, it->second->param2);
    }

    m.erase("Third?");

    printf("\n\n");
    
    for (auto it = m.begin(); it != m.end(); ++it) {
        printf("m[%s] = { param1 = %d, param2 = %f }\n", it->first, it->second->param1, it->second->param2);
    }

    Derived last = *(Derived *)m["derived"];
    printf("m[derived] = { param1 = %d, param2 = %f, param3 = %f, param4 = %s}\n", last.param1, last.param2, last.param3, last.param4 ? "true" : "false");

    
    return 0;
}
