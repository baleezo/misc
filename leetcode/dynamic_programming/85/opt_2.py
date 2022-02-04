class Solution(object):
    # monotonic stack
    # related to leetcode 84

    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        m, n = len(matrix), len(matrix[0])
        dp = [[0] * n for _ in range(m)]
        ans = 0

        for i in range(m):
            stack = []
            for j in range(n):
                if matrix[i][j] == '1':
                    if i - 1 < 0:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = dp[i - 1][j] + 1

                while len(stack) > 0 and dp[i][stack[-1]] >= dp[i][j]:
                    k = stack.pop()
                    height = dp[i][k]

                    if len(stack) == 0:
                        width = j
                    else:
                        width = j - stack[-1] - 1

                    ans = max(ans, width * height)

                stack.append(j)

            f = stack[-1]
            while len(stack) > 0:
                k = stack.pop()
                height = dp[i][k]

                if len(stack) == 0:
                    width = f + 1
                else:
                    width = f - stack[-1]

                ans = max(ans, width * height)

        return ans

