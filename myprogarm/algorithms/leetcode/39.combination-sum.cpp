/*
 * @lc app=leetcode id=39 lang=cpp
 *
 * [39] Combination Sum
 */

// @lc code=start
using namespace std;
class Solution {
private:
    vector<int> cadidates;
    vector<vector<int>> result;
    vector<int> path;
public:
    void DFS(int start, int target){
        if(target == 0 ){
            result.push_back(path);
            return;
        }

        for (int i = start; i < cadidates.size() && (target - cadidates[i]) >= 0 ; i++) {
            path.push_back(cadidates[i]);
            DFS(i, target - cadidates[i]);
            path.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        this->cadidates = candidates;
        DFS(0,target);
        return result;
    }
};
// @lc code=end