class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0

        for idx, c in enumerate(s):
            curr_str_set = set(c)
            curr_len = 1
            for aft_c in s[idx + 1:]:
                if aft_c not in curr_str_set:
                    curr_str_set.add(aft_c)
                    curr_len += 1
                else:
                    break
                    
            if curr_len > max_len:
                max_len = curr_len

        return max_len
