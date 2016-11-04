/*
** list_supr.c for list in /home/trouve_b/Desktop/PSU_2015_myirc
** 
** Made by Alexis Trouve
** Login   <trouve_b@epitech.net>
** 
** Started on  Wed Jun  1 16:40:18 2016 Alexis Trouve
** Last update Mon Jun 13 14:43:33 2016 Alexis Trouve
*/

#include "list.hh"

t_iterator	*list_pop_back(t_list *list)
{
  t_iterator	*it;

  if ((it = list->end->prev) == NULL)
    return (NULL);
  if (it->prev != NULL)
    it->prev->next = list->end;
  list->end->prev = it->prev;
  it->prev = NULL;
  it->next = NULL;
  --list->size;
  return (it);
}

t_iterator	*list_pop_front(t_list *list)
{
  t_iterator	*it;

  if ((it = list->begin)->id == list->end->id)
    return (NULL);
  it->next->prev = NULL;
  list->begin = it->next;
  it->next = NULL;
  it->prev = NULL;
  --list->size;
  return (it);
}

t_iterator	*list_supr(t_list *list, t_iterator *itsupr)
{
  t_iterator	*it;
  void		*data;

  if (itsupr == NULL || itsupr->id == list->end->id)
    return (NULL);
  it = list->begin;
  while (it->id != list->end->id)
    {
      if (it->id == itsupr->id)
	{
	  if (it->prev != NULL)
	    it->prev->next = it->next;
	  else
	    list->begin = it->next;
	  it->next->prev = it->prev;
	  it->next = NULL;
	  it->prev = NULL;
	  --list->size;
	  return (it);
	}
      it = it->next;
    }
  return (NULL);
}

t_iterator	**list_erase(t_list *list, t_iterator *begin, t_iterator *end)
{
  t_iterator	**data;
  t_iterator	*it;
  int		i;

  if (list_element_exist(list, begin) < 1 || list_element_exist(list, end) < 1
      || list_element_exist(list, begin) > list_element_exist(list, end))
    return (NULL);
  if ((data = (t_iterator**)malloc((list_element_exist(list, end)
				    - list_element_exist(list, begin))
				   * sizeof(t_iterator*))) == NULL)
    exit(list_put_message_for_insufficient_memory());
  i = 0;
  it = list->begin;
  while (it->id != list->end->id)
    {
      it->prev = NULL;
      it->next = NULL;
      data[i++] = it;
      it = it->next;
    }
  data[i] = NULL;
  while (begin->next->id != end->id && begin->next->id != list->end->id)
    list_supr(list, begin->next);
  list_supr(list, begin);
  list_supr(list, end);
  return (data);
}
