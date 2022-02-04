# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def reverseBetween(self, head, left, right):
        """
        :type head: ListNode
        :type left: int
        :type right: int
        :rtype: ListNode
        """
        if left == right:
            return head

        if head is None:
            return head

        curr = head
        prev = None
        next_node = None
        reversed_left = None
        reversed_tail = None

        for i in range(right):
            next_node = curr.next

            if i >= left - 1:
                if i == left - 1:
                    reversed_left = prev
                    reversed_tail = curr
                curr.next = prev

            prev = curr
            curr = next_node

        reversed_tail.next = next_node

        if reversed_left:
            reversed_left.next = prev
        else:
            head = prev

        return head
