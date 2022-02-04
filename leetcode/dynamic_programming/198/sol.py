class Solution(object):
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def dp(i):
            if i == 0:
                return nums[0]
            if i == 1:
                return max(nums[0], nums[1])

            if i not in res:
                res[i] = max(dp(i - 1), dp(i - 2) + nums[i])
            return res[i]

        res = {}
        return dp(len(nums) - 1)
