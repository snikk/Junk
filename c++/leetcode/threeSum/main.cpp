#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ret = {};

        if (nums.size() == 0)
            return ret;

        vector<int> cNums = nums;
        sort(cNums.begin(), cNums.end());
                                                        
        for (auto b = cNums.begin(); b < cNums.end() - 3; ++b) {
            auto s = b + 1;
            auto e = cNums.end() - 1;

            while (s < e) {
                if (*b + *s + *e == 0) {
                    bool add = true;
                    for (auto check = ret.begin(); check != ret.end(); ++check) {
                        auto arr = *check;
                        if (arr[0] == *b && arr[1] == *s && arr[2] == *e) {
                            add = false;
                            break;
                        }
                    }
                    if (add) {
                        vector<int> val = {*b, *s, *e};
                        ret.push_back(val);
                    }

                    ++s;
                    --e;
                } else if (*b + *s + *e > 0) {
                    --e;
                } else {
                    ++s;
                }
            }
        }
                                                                
        return ret;
    }
};

int main(int argc, char** argv) {
    //vector<int> ns = {-1, 0, 1, 2, -1, -4};
    vector<int> ns = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    Solution sol;
    vector<vector<int> > results = sol.threeSum(ns);
    for (auto vecIt = results.begin(); vecIt != results.end(); ++vecIt) {
        printf("vec{ ");
        for (auto numIt = (*vecIt).begin(); numIt != (*vecIt).end(); ++numIt) {
            printf("%d, ", *numIt);
        }
        printf("}\n");
    }

    return 0;
}
