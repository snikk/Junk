#include <stdlib.h>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0;
        int j = 0;
        while (i < s.size() && j < p.size()) {
            switch (p[j]) {
                case '?':
                {
                    i++;
                    j++;
                    break;
                }
                case '*':
                {
                    if (j + 1 == p.size())
                        return true;

                    int diff = 1;
                    while (j + 1 < p.size() && (p[++j] == '?' || p[j] == '*')) {
                        diff++;
                    }

                    i += diff;

                    while (i < s.size() && s[i] != p[j]) i++;

                    break;
                }
                default:
                {
                    if (s[i++] != p[j++])
                        return false;
                    break;
                }
            }
        }

        return i == s.size() && j == p.size();
    }
};

int main(int argc, char** argv) {
    Solution sol;
    bool b = sol.isMatch("aaaab", "a*b");

    printf("isTrue = %s\n", b ? "true" : "false");

    return 0;
}
