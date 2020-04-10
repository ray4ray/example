/*
 * @lc app=leetcode id=5 lang=golang
 *
 * [5] Longest Palindromic Substring
 */

// @lc code=start
func longestPalindrome(s string) string {
	slen := len(s)
	if len(s) <= 1 {
		return s
	}

	left, right := 0, 0
	for i := 0; i < slen; i++ {
		// lengthen of substring is odd
		if leftTmp, rightTmp := checkPanlindrome(s, i, i); (rightTmp - leftTmp) > (right - left) {
			left, right = leftTmp, rightTmp
		}

		//lengthen of substring is even
		if leftTmp, rightTmp := checkPanlindrome(s, i, i+1); (rightTmp - leftTmp) > (right - left) {
			left, right = leftTmp, rightTmp
		}
	}

	return string(s[left : right+1])
}

func checkPanlindrome(s string, leftTmp, rightTmp int) (int, int) {

	//must set as 0, otherwise this init value will be return to upper function
	left, right := 0, 0
	for leftTmp >= 0 && rightTmp < len(s) {
		if s[leftTmp] != s[rightTmp] {
			break
		}

		//save index about equal item
		left, right = leftTmp, rightTmp
		leftTmp--
		rightTmp++
	}
	return left, right
}

// @lc code=end
