#include <iostream>
#include <chrono>
#include <vector>

const int COUNT = 10000;

void timeFunction(void (*test)());
void testStars();
void testArrayInit();
void testArrayAccess();
void testVectorInit();
void testVectorAccess();

int main() {
    std::cout << "Hello, World!\n";

    timeFunction(testStars);
    timeFunction(testArrayInit);
    timeFunction(testArrayAccess);
    timeFunction(testVectorInit);
    timeFunction(testVectorAccess);

    return 0;
}

void timeFunction(void (*test)()) {
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double> time_span;

    std::cout << "\n\nTiming function\n";
    
    t1 = std::chrono::high_resolution_clock::now();

    test();

    t2 = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
    int lengthOfStr;
    printf("It took %f seconds.\n%n", time_span.count(), &lengthOfStr);
    std::cout << "It took " << time_span.count() << " seconds.\n";
    std::cout << "The printf line took " << lengthOfStr << " to print.\n";
}

void testStars() {
    std::cout << "****  Testing stars output  ****\n";
    for (int i = 0; i < 10000; i++) {
        std::cout << "*";
    }

    std::cout << std::endl;
    std::cout << "****  Finished stars testing  ****\n";
}

void testArrayInit() {
    std::cout << "****  Testing Array init testing  ****\n";

    int* arr = (int*)malloc(sizeof(int) * COUNT);
    memset(arr, 0, sizeof(int) * COUNT);

    std::cout << "****  Finished Array init testing  ****\n";
}

void testArrayAccess() {
    std::cout << "****  Testing Array access testing  ****\n";

    int* arr = (int*)malloc(sizeof(int) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        arr[i] = i;
        for (int j = 0; j < COUNT; j++) {
            arr[j] = arr[i] * j;
        }
    }

    std::cout << "****  Finished Array access testing  ****\n";
}

void testVectorInit() {
    std::cout << "****  Testing Vector init testing  ****\n";
    std::vector<int> arr;
    for (int i = 0; i < COUNT; i++) {
        arr.push_back(0);
    }
    std::cout << "****  Finished Vector init testing  ****\n";
}

void testVectorAccess() {
    std::cout << "****  Testing Vector access testing  ****\n";

    std::vector<int> arr(COUNT);
    for (int i = 0; i < COUNT; i++) {
        arr[i] = i;
        for (int j = 0; j < COUNT; j++) {
            arr[j] = arr[i] * j;
        }
    }



    std::cout << "****  Finished Vector access testing  ****\n";
}

