class Solution(object):
    def maximumScore(self, nums, multipliers):
        """
        :type nums: List[int]
        :type multipliers: List[int]
        :rtype: int
        """
        m = len(multipliers)
        n = len(nums)
        res = [[0] * (m + 1) for _ in range(m + 1)]
        for i in range(m - 1, -1 , -1):
            for j in range(i, -1, -1):
                mul = multipliers[i]
                res[i][j] = max(
                    mul * nums[j] + res[i + 1][j + 1],
                    mul * nums[n - 1 - (i - j)] + res[i + 1][j]
                )

        return res[0][0]

