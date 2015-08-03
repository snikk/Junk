#include <unistd.h>
#include <map>

class Container {
public:
    static Container& instance();
    void setValue(unsigned int i, bool b);
    void updateValue();
    void print();
private:
    static Container _cont;

    std::map<unsigned int, bool> map1;
    std::map<unsigned int, bool> map2;
};

int main(int argc, char** argv) {
    Container::instance().print();

    Container::instance().setValue(122, true);

    usleep(1000000);
    Container::instance().print();

    Container::instance().setValue(444, false);

    usleep(1000000);
    Container::instance().print();
    usleep(1000000);
    Container::instance().print();

    std::map<unsigned int, bool> map1;
    std::map<unsigned int, bool> map2;

    map1[123] = true;
    map1[444] = false;

    for (auto& it : map1) {
        printf("map1[%d] = %s\n", it.first, it.second ? "true" : "false");
    }

    for (auto& it : map2) {
        printf("map2[%d] = %s\n", it.first, it.second ? "true" : "false");
    }

    return 0;
}

Container& Container::instance() {
    static Container _cont;
    return _cont;
}

void Container::setValue(unsigned int i, bool b) {
    map1[i] = b;
}

void Container::print() {
    printf("Printing values!\n");

    for (auto& it2 : map2) {
        printf("map2[%d] = %s\n", it2.first, it2.second ? "true" : "false");
    }

    printf("---------------------------------------!\n");

    for (auto& it : map1) {
        printf("map1[%d] = %s\n", it.first, it.second ? "true" : "false");
        map2[it.first] = it.second;
    }

    printf("Finished printing!\n\n\n");
}

