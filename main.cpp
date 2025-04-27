#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end()); // Sort the array to handle duplicates
        vector<int> path;
        dfs(nums, 0, path, ans);
        return ans;
    }

private:
    void dfs(const vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& ans) {
        ans.push_back(path); // Add the current subset to the result

        for (int i = start; i < nums.size(); ++i) {
            // Skip duplicates
            if (i > start && nums[i] == nums[i - 1])
                continue;

            path.push_back(nums[i]); // Include nums[i] in the current subset
            dfs(nums, i + 1, path, ans); // Recurse for the next elements
            path.pop_back(); // Backtrack
        }
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j + 1 < result[i].size())
                cout << ",";
        }
        cout << "]";
        if (i + 1 < result.size())
            cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1
    vector<int> nums1 = {1, 2, 2};
    cout << "Input: nums = [1,2,2]" << endl;
    vector<vector<int>> result1 = solution.subsetsWithDup(nums1);
    cout << "Output: ";
    printResult(result1);

    // Example 2
    vector<int> nums2 = {0};
    cout << "Input: nums = [0]" << endl;
    vector<vector<int>> result2 = solution.subsetsWithDup(nums2);
    cout << "Output: ";
    printResult(result2);

    return 0;
}
