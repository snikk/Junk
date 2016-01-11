#include <stdio.h>
#include <memory>

class ObjWithoutPointer {
public:
    ObjWithoutPointer(int d) : data(d) {
        printf("ObjWithoutPointer Constructor | d = %d\n", data);
    }

    ~ObjWithoutPointer() {
        printf("ObjWithoutPointer Destructor | d = %d\n", data);
    }
    int data;
};

class ObjWithPointer {
public:
    ObjWithPointer(std::shared_ptr<ObjWithoutPointer> obj, int d)
        : pointer(obj), data(d)
    {
        printf("ObjWithPointer Constructor | d = %d\n", data);
    }

    ~ObjWithPointer() {
        printf("ObjWithPointer Destructor | d = %d\n", data);
    }
    std::shared_ptr<ObjWithoutPointer> pointer;
    int data;
};

void test() {
    std::shared_ptr<ObjWithoutPointer> owop(new ObjWithoutPointer(123));
    std::shared_ptr<ObjWithPointer> owp(new ObjWithPointer(owop, 456));

    owp->data = 777;
    owp->pointer->data = 999;
}

int main(int argc, char** argv) {
    test();

    return 0;
}
