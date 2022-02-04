class Solution(object):
    def deleteAndEarn(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n_cnt = [0] * 10001
        n_max = 0
        for i in nums:
            n_cnt[i] += 1
            if i > n_max:
                n_max = i

        def dp(i):
            if i == 0:
                return 0
            if i == 1:
                return n_cnt[1]
            if i not in res:
                res[i] = max(dp(i - 1), dp(i - 2) + n_cnt[i] * i)
            return res[i]

        res = {}
        return dp(n_max)
