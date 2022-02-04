class Solution(object):
    def tribonacci(self, n):
        """
        :type n: int
        :rtype: int
        """
        def dp(i):
            if i == 0:
                return 0
            if i in (1, 2):
                return 1
            if i not in res:
                res[i] = dp(i - 1) + dp(i - 2) + dp(i - 3)
            return res[i]

        res = {}
        return dp(n)

