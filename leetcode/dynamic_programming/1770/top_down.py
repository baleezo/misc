class Solution(object):
    # will TLE
    def maximumScore(self, nums, multipliers):
        """
        :type nums: List[int]
        :type multipliers: List[int]
        :rtype: int
        """
        def dp(i, j):
            if i == m:
                return 0

            mul = multipliers[i]
            right = n - 1 - (i - j)

            if res[i][j] is None:
                res[i][j] = max(
                    mul * nums[j] + dp(i + 1, j + 1),
                    mul * nums[right] + dp(i + 1, j)
                )

            return res[i][j]

        m = len(multipliers)
        n = len(nums)
        res = [[None] * (m) for _ in range(m)]


        return dp(0, 0)

