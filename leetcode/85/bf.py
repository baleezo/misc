class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
       
        m, n = len(matrix), len(matrix[0])
        ans = 0
        for row in range(m):
            for col in range(n):
                r = 0
                min_w = n
                while r < m - row and matrix[row + r][col] == '1':
                    c = 0
                    while c < n - col and matrix[row + r][col + c] == '1':
                        c += 1
                    r += 1
                    min_w = min(min_w, c)
                    ans = max(ans, r * min_w)        
                            
        return ans
