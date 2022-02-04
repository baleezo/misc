class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        m, n = len(matrix), len(matrix[0])
        ans = 0
        dp = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '1':
                    if j - 1 < 0:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = dp[i][j - 1] + 1

                if matrix[i][j] != '1':
                    continue

                current_w = n
                for h in range(i + 1):
                    current_w = min(current_w, dp[i - h][j])
                    if current_w == 0:
                        break

                    ans = max(ans, (h + 1) * current_w)

        return ans

