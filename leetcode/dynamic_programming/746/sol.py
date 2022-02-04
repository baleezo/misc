class Solution(object):
    def minCostClimbingStairs(self, cost):
        """
        :type cost: List[int]
        :rtype: int
        """
        cost += [0]
        def dp(i):
            if i == 0:
                return 0
            if i == 1:
                return 0
            if i not in res:
                res[i] = min(dp(i - 2) + cost[i - 2], dp(i - 1) + cost[i - 1])

            return res[i]

        res = {}
        return dp(len(cost) - 1)
