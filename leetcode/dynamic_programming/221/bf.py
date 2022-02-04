class Solution(object):
    def maximalSquare(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        def is_valid_square(r, c, side_len):
            for i in range(r, r + side_len):
                if not all(x == '1' for x in matrix[i][c:c + side_len]):
                    return False
            return True

        m, n = len(matrix), len(matrix[0])
        max_side_len = 0
        for r in range(m):
            for c in range(n):
                for side_len in range(min(m - r, n - c) + 1):
                    #print(side_len)
                    if is_valid_square(r, c, side_len):
                        max_side_len = max(max_side_len, side_len)

        return max_side_len * max_side_len

