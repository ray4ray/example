import "sort"

/*
 * @lc app=leetcode id=39 lang=golang
 *
 * [39] Combination Sum
 */

// @lc code=start
func combinationSum(candidates []int, target int) [][]int {
	sort.Ints(candidates)
	res := [][]int{}
	dfs(candidates, nil, target, 0, &res)
	return res
}

func dfs(candidates, nums []int, target, left int, res *[][]int) {
	if target == 0 {
		tmp := make([]int, len(nums))
		copy(tmp, nums)
		*res = append(*res, tmp)
		return
	}

	for i := left; i < len(candidates); i++ {
		if target < candidates[i] {
			return
		}
		dfs(candidates, append(nums, candidates[i]), target-candidates[i], i, res)
	}
}

// @lc code=end
