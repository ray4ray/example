/*
 * @lc app=leetcode id=1143 lang=golang
 *
 * [1143] Longest Common Subsequence
 */

// @lc code=start
func longestCommonSubsequence(text1 string, text2 string) int {
	text1Len := len(text1)
	text2Len := len(text2)
	dp := make([][]int, text1Len+1)
	for i := 0; i <= text1Len; i++ {
		dp[i] = make([]int, text2Len+1)
	}

	for i := 1; i <= text1Len; i++ {
		for j := 1; j <= text2Len; j++ {
			if text1[i-1] == text2[j-1] {
				dp[i][j] = dp[i-1][j-1] + 1
			} else {
				dp[i][j] = max(dp[i][j-1], dp[i-1][j])
			}
		}
	}
	return dp[text1Len][text2Len]
}

func max(val1, val2 int) int {
	if val2 > val1 {
		return val2
	}
	return val1
}

// @lc code=end
