class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        w_start = 0
        position_of_c = {}

        for w_end, c in enumerate(s):
            if c in position_of_c:
                w_start = max(w_start, position_of_c[c] + 1)

            max_len = max(max_len, w_end - w_start + 1)
            position_of_c[c] = w_end
                
        return max_len
