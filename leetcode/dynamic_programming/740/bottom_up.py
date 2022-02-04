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

        res = {}

        res[0] = 0
        res[1] = n_cnt[1]
        for i in range(2, n_max + 1):
            res[i] = max(res[i - 1], res[i - 2] + n_cnt[i] * i)

        return res[n_max]
