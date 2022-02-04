class Solution(object):
    def maximalSquare(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        m, n = len(matrix), len(matrix[0])
        res = [[0] * (n) for _ in range(m)]
        ans = 0

        for i in range(m):
            for j in range(n):
                if matrix[i][j] == '1':
                    if i - 1 < 0 or j - 1 < 0:
                        res[i][j] = 1
                    else:
                        res[i][j] = min(res[i - 1][j - 1], res[i - 1][j], res[i][j - 1]) + 1

                    ans = max(ans, res[i][j])

        return ans ** 2
