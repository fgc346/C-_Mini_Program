/*
 * @Author: fenggaochao
 * @Date: 2023-01-13 09:52:54
 * @LastEditTime: 2023-01-13 09:52:54
 * @LastEditors: fenggaochao
 * @Description: 
 * @FilePath: /C-Concurrence-master/common/test.cpp
 */

ListNode *ReverseList(ListNode *pHead)
{
  ListNode *p, *q, *r;
  if (pHead == NULL || pHead->next == NULL)
  {
    return pHead;
  }
  else
  {
    p = pHead;
    q = p->next;
    pHead->next = NULL;
    while (q != NULL)
    {
      r = q->next;
      q->next = p;
      p = q;
      q = r;
    }
    return p;
  }
}