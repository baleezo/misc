class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        start = 0
        position_of_c = {}

        for idx, c in enumerate(s):
            if c in position_of_c:
                start = max(start, position_of_c[c] + 1)

            max_len = max(max_len, idx - start + 1)
            position_of_c[c] = idx
                
        return max_len
