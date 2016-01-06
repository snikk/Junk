#include <iostream>
#include <vector>

void timeFunction(void (*test)());
void dynamicMallocAllocation();
void alreadyAllocMallocAllocation();
void dynamicNewAllocation();
void alreadyNewAllocation();

const int NUM = 10000;

class Mine {
public:
    Mine(const char* str) : _counter(0) {
        //std::cout << "Created a new object for " << str << ". How about that! | this = " << this << std::endl;
        _str = str;
    }

    ~Mine() {
        //std::cout << _str << " was destroyed! What old nasty object.  Gross.\n";
    }

    void method() {
        //std::cout << _str << ". Here we are.  Born to be kings!\n";
    }

    void counter() {
        _counter++;
        //std::cout << _str << ". My counter = " << _counter++ << "\n";
    }

private:
    int _counter;
    const char* _str;
};

Mine* mineAlready;
std::vector<Mine*> vecForAlready;

void testFunc() {
    Mine m((char*)"Excalibur");

    m.counter();
    m.counter();
    m.counter();
    m.counter();
    m.method();

    Mine* m2 = new Mine((char*)"Hey now!");

    m2->counter();
    m2->counter();
    m2->counter();
    m2->counter();
    m2->counter();
    m2->counter();
    m2->method();

    void* buf = malloc(sizeof(Mine));
    Mine* m3 = new (buf) Mine((char*)"Another?");


    m3->counter();
    m3->counter();
    m3->counter();
    m3->counter();
    m3->counter();
    m3->counter();
    m3->method();

    m3 = new (buf) Mine((char*) "A third?  Preposterous");

    m3->counter();
    m3->counter();
    m3->counter();
    m3->counter();
    m3->method();


    const int num = 10;
    Mine* test = (Mine *)malloc(sizeof(Mine) * num);

    for (int i = 0; i < num; i++) {
        new (&test[i]) Mine((char*) "Repeat!");
        test[i].counter();
        test[i].counter();
        test[i].counter();
        test[i].method();
    }


    for (int i = 0; i < num; i++) {
        test[i].~Mine();
    }

    free(test);

    std::cout << "m = " << &m << " | m2 = " << m2 << " | m3 = " << m3 << " | buf = " << buf << " | sizeof(*test) = " << sizeof(*test) << " | sizeof(Mine) = " << sizeof(Mine) << std::endl;
    delete m2;
    delete m3;
}

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    testFunc();

    mineAlready = (Mine*) malloc(sizeof(Mine) * NUM);

    timeFunction(dynamicMallocAllocation);
    timeFunction(alreadyAllocMallocAllocation);
    timeFunction(dynamicNewAllocation);
    timeFunction(alreadyNewAllocation);

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

void dynamicMallocAllocation() {
    Mine* mine = (Mine*) malloc(sizeof(Mine) * NUM);

    for (int i = 0; i < NUM; i++) {
        new (&mine[i]) Mine("Test another one");

        mine[i].counter();
        mine[i].counter();
        mine[i].counter();
        mine[i].counter();
        mine[i].method();
    }

    for (int i = 0; i < NUM; i++) {
        mine[i].~Mine();
    }

    free(mine);
}

void alreadyAllocMallocAllocation() {
    for (int i = 0; i < NUM; i++) {
        new (&mineAlready[i]) Mine("Test another one");

        mineAlready[i].counter();
        mineAlready[i].counter();
        mineAlready[i].counter();
        mineAlready[i].counter();
        mineAlready[i].method();
    }

    for (int i = 0; i < NUM; i++) {
        mineAlready[i].~Mine();
    }
}

void dynamicNewAllocation() {
    std::vector<Mine*> mine;

    for (int i = 0; i < NUM; i++) {
        mine.push_back(new Mine("Here we go"));

        mine.back()->counter();
        mine.back()->counter();
        mine.back()->counter();
        mine.back()->counter();
        mine.back()->method();
    }

    for (int i = 0; i < mine.size(); i++) {
        delete mine[i];
    }
}

void alreadyNewAllocation() {
    for (int i = 0; i < NUM; i++) {
        vecForAlready.push_back(new Mine("Here we go"));

        vecForAlready.back()->counter();
        vecForAlready.back()->counter();
        vecForAlready.back()->counter();
        vecForAlready.back()->counter();
        vecForAlready.back()->method();
    }

    for (int i = 0; i < vecForAlready.size(); i++) {
        delete vecForAlready[i];
    }
}

