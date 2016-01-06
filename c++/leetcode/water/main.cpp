#include <stdio.h>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> start;
        int total = 0;

        for (int i = 0; i < height.size(); i++) {
            int prevMax;
            if (start.empty()) {
                if (height[i] > 0) {
                    start.push_back(i);
                }
            } else {
                int bottomHeight = 0;
                if (height[i] <= height[start.back()]) {
                    if (height[start.back()] == height[i])
                        start.pop_back();
                    start.push_back(i);
                } else {
                    int bottom = height[i];
                    while (!start.empty() && height[i] >= height[start.back()]) {
                        if (height[start.back()] < bottom) {
                            bottom = height[start.back()];
                            start.pop_back();
                            continue;
                        }
                        int wellDepth = min(height[i], height[start.back()]) - bottom;
                        total += (i - start.back() - 1) * wellDepth;
                        bottom = height[start.back()];
                        start.pop_back();
                    }

                    if (!start.empty() && bottom < height[i]) {
                        int wellDepth = min(height[i], height[start.back()]) - bottom;
                        total += (i - start.back() - 1) * wellDepth;
                    }

                    start.push_back(i);
                }
            }
        }

        return total;
    }
};

int main(int argc, char** argv) {
    Solution sol;
    //vector<int> items = {0,1,0,2,1,0,1,3,2,1,2,1};
    //vector<int> items = {4,2,3};
    vector<int> items = {2,0,2};
    int amount = sol.trap(items);
    printf("total amount of rain = %d\n", amount);

    return 0;
}
