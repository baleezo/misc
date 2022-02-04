class Solution(object):
    def longestCommonSubsequence(self, text1, text2):
        """
        :type text1: str
        :type text2: str
        :rtype: int
        """
        def dp(i, j):
            if i < 0 or j < 0:
                return 0

            if res[i][j] is None:
                if text1[i] == text2[j]:
                    res[i][j] = dp(i - 1, j - 1) + 1
                else:
                    res[i][j] =  max(
                        dp(i - 1, j),
                        dp(i, j - 1)
                    )
            return res[i][j]

        res = [[None] * len(text2) for _ in range(len(text1))]

        return dp(len(text1) - 1, len(text2) - 1)
