#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

template <typename T>
class TemplateClass {
public:
    void init(int size);
    T* arr;
    T* get(int idx);
    T& getObj(int idx);
    T* begin();
    T* end();

private:
    int size;

};

class MyClass {
public:
    int member1;
    double member2;

};

struct StructTest {
    float fValue;
    int iValue;
    bool bValue;
};


int main(int argc, char** argv) {
    printf("Hello, World!\n");

    TemplateClass<MyClass> template1;
    TemplateClass<struct StructTest> template2;

    long size = 100000000;
    double constValue = 172.2873;

    template1.init(size);
    template2.init(size);

    /*
    for (int i = 0; i < size; i++) {
        template1.arr[i].member1 = i;
        template1.arr[i].member2 = i * constValue;
    }

    for (int i = 0; i < size; i++) {
        template2.arr[i].fValue = i * constValue;
        template2.arr[i].iValue = i;
        template2.arr[i].bValue = i % 2 == 0;
    }

    for (int i = 0; i < size; i++) {
        MyClass* cls = template1.get(i);
        cls->member1 = i;
        cls->member2 = i * constValue;
    }

    for (int i = 0; i < size; i++) {
        struct StructTest* tmp = template2.get(i);
        tmp->fValue = i * constValue;
        tmp->iValue = i;
        tmp->bValue = i % 2 == 0;
    }
    */

    MyClass* begin = template1.begin();
    MyClass* end = template1.end();
    int i = 0;
    for (MyClass* cls = begin; cls != end; cls++) {
        i++;
        cls->member1 = i;
        cls->member2 = i * constValue;
    }

    struct StructTest* tmpBegin = template2.begin();
    struct StructTest* tmpEnd = template2.end();
    i = 0;
    for (struct StructTest* tmp = tmpBegin; tmp != tmpEnd; tmp++) {
        i++;
        tmp->fValue = i * constValue;
        tmp->iValue = i;
        tmp->bValue = i % 2 == 0;
    }

    /*
    for (int i = 0; i < size; i++) {
        MyClass& cls = template1.getObj(i);
        cls.member1 = i;
        cls.member2 = i * constValue;
    }

    for (int i = 0; i < size; i++) {
        struct StructTest& tmp = template2.getObj(i);
        tmp.fValue = i * constValue;
        tmp.iValue = i;
        tmp.bValue = i % 2 == 0;
    }
    */

    /*
    printf("Template1\n------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("member1 = %d | member2 = %f\n", template1.arr[i].member1, template1.arr[i].member2);
    }

    printf("------------------------------------------------------\n");
    printf("Template2\n------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("fValue = %f | iValue = %d | bValue = %d\n", template2.arr[i].fValue, template2.arr[i].iValue, template2.arr[i].bValue);
    }
    printf("------------------------------------------------------\n");
    printf("Mem 1\n------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        MyClass* mClassItem = (MyClass*) mem1.get(i);
        printf("member1 = %d | member2 = %f\n", mClassItem->member1, mClassItem->member2);
    }
    printf("------------------------------------------------------\n");
    printf("Mem 2\n------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        struct StructTest* structItem = (struct StructTest*) mem2.get(i);
        printf("fValue = %f | iValue = %d | bValue = %d\n", structItem->fValue, structItem->iValue, structItem->bValue);
    }
    printf("------------------------------------------------------\n");
    */

    return 0;
}

template <typename T>
void TemplateClass<T>::init(int size) {
    arr = (T*) malloc(sizeof(T) * size);

    this->size = size;

    printf("Allocated! = %lu | sizeof T = %lu | size = %d\n", sizeof(T) * size, sizeof(T), size);
}

template <typename T>
T* TemplateClass<T>::get(int idx) {
    return arr + idx;
}

template <typename T>
T& TemplateClass<T>::getObj(int idx) {
    return arr[idx];
}

template <typename T>
T* TemplateClass<T>::begin() {
    return arr;
}

template <typename T>
T* TemplateClass<T>::end() {
    return &arr[size];
}

