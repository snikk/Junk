#include <stdio.h>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = 0;
        int st = 0;
        int e = 1;
        
        while (e < s.size()) {
            bool end = false;
            for (int i = e - 1; i >= st; i--) {
                printf("i = %d | st = %d | e = %d\n", i, st, e);
                if (s[i] == s[e]) {
                    end = true;
                    break;
                }
            }
            if (end) {
                if (e - st > len)
                    len = e - st;
                st = e;
            }
            e++;
        }
        
        if (e - st > len)
            len = e - st;
        
        return len;
    }
};

int main(int argc, char** argv) {
    Solution s;
    int len = s.lengthOfLongestSubstring("ab");

    printf("len = %d\n", len);
    return 0;
}
