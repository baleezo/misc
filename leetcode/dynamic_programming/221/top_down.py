class Solution(object):
    def maximalSquare(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        def dp(i, j):
            if i < 0 or j < 0:
                return 0

            if i == 0 and j == 0 and matrix[i][j] == '1':
                return 1

            if res[i][j] is None:
                if matrix[i][j] == '1':
                    res[i][j] = min(dp(i - 1, j - 1), dp(i - 1, j), dp(i, j - 1)) + 1
                else:
                    res[i][j] = 0

            return res[i][j]

        m, n = len(matrix), len(matrix[0])
        res = [[None] * n for _ in range(m)]
        ans = 0
        for i in range(m):
            for j in range(n):
                ans = max(ans, dp(i, j))

        return ans ** 2

