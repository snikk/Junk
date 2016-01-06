#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        int start = 0;
        while (str[start] == ' ') start++;
        int end = start;
        int sign = 1;
        if (str[end] == '-' || str[end] == '+') {
            if (str[end] == '-')
                sign = -1;
            start++;
            end++;
        }
        while (end < str.size() && str[end] >= '0' && str[end] <= '9') end++;
        for (int i = end - 1; i >= start; i--) {
            int c = str[i] - '0';
            if (c >= 0 && c < 10) {
                ret += c * pow(10, end - 1 - i);
            } else {
                return 0;
            }
        }
        
        return ret * sign;
    }
};

int main(int argc, char** argv) {
    Solution sol;
    int result = sol.myAtoi("    -1a1234");

    printf("result = %d\n", result);

    return 0;
}
