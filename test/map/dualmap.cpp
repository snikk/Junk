#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <unordered_map>
#include <string>

void mapTest(int seed, int count, long num);
void unorderedMapTest(int seed, int count, long num);
void stringMapTest(int seed, int count, long num);
void stringUnorderedMapTest(int seed, int count, long num);

void createMap(int count);
void createUnorderedMap(int count);
void createStringMap(int count);
void createStringUnorderedMap(int count);

std::string getKey(long i);

std::map<int, std::string> m;
std::unordered_map<int, std::string> uom;
std::map<std::string, std::string> sm;
std::unordered_map<std::string, std::string> suom;

int main(int argc, char** argv) {
    int seed = time(NULL);
    int count = 10;
    long testNumber = 100000000;
    createMap(count);
    mapTest(seed, count, testNumber);
    createUnorderedMap(count);
    unorderedMapTest(seed, count, testNumber);

    createStringMap(count);
    stringMapTest(seed, count, testNumber);
    createStringUnorderedMap(count);
    stringUnorderedMapTest(seed, count, testNumber);

    return 0;
}

void mapTest(int seed, int count, long num) {
    printf("mapTest | seed = %d\n", seed);
    srand(seed);
    int len = 0;

    for (int i = 0; i < num; i++) {
        int idx = rand() % count;
        len += m[idx].size();
    }

    printf("len = %d | float = %f\n", len, (float) len / (float) num);
}

void unorderedMapTest(int seed, int count, long num) {
    printf("unorderedMapTest | seed = %d\n", seed);
    srand(seed);
    int len = 0;

    for (int i = 0; i < num; i++) {
        int idx = rand() % count;
        len += uom[idx].size();
    }

    printf("len = %d | float = %f\n", len, (float) len / (float) num);
}

void stringMapTest(int seed, int count, long num) {
    printf("StringMapTest | seed = %d\n", seed);
    srand(seed);
    int len = 0;

    for (int i = 0; i < num; i++) {
        int idx = rand() % count;
        len += sm[getKey(idx)].size();
    }

    printf("len = %d | float = %f\n", len, (float) len / (float) num);
}

void stringUnorderedMapTest(int seed, int count, long num) {
    printf("stringUnorderedMapTest | seed = %d\n", seed);
    srand(seed);
    int len = 0;

    for (int i = 0; i < num; i++) {
        int idx = rand() % count;
        len += suom[getKey(idx)].size();
    }

    printf("len = %d | float = %f\n", len, (float) len / (float) num);
}

void createMap(int count) {
    for (int i = 0; i < count; i++) {
        m[i] = "Number = " + std::to_string(i);
    }

}

void createUnorderedMap(int count) {
    for (int i = 0; i < count; i++) {
        uom[i] = "Number = " + std::to_string(i);
    }
}

void createStringMap(int count) {
    for (int i = 0; i < count; i++) {
        sm[getKey(i)] = "Number = " + std::to_string(i);
    }

}

void createStringUnorderedMap(int count) {
    for (int i = 0; i < count; i++) {
        suom[getKey(i)] = "Number = " + std::to_string(i);
    }
}

std::string getKey(long i) {
    return "This is the key! | num = " + std::to_string(i);
}

