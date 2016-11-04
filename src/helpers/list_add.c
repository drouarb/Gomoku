/*
** list_add.c for list in /home/trouve_b/Desktop/PSU_2015_myirc
** 
** Made by Alexis Trouve
** Login   <trouve_b@epitech.net>
** 
** Started on  Wed Jun  1 14:41:40 2016 Alexis Trouve
** Last update Mon Jun 13 14:41:41 2016 Alexis Trouve
*/

#include "list.hh"

unsigned int	give_unique_list_id()
{
  static int		i = 0;

  return (++i);
}

void		list_push_back(t_list *list, t_iterator *newit)
{
  newit->prev = list->end->prev;
  newit->next = list->end;
  if (list->begin == NULL || list->begin->id == list->end->id)
    list->begin = newit;
  if (list->end->prev != NULL)
    list->end->prev->next = newit;
  list->end->prev = newit;
  list->size++;
}

void		list_push_front(t_list *list, t_iterator *newit)
{
  newit->prev = NULL;
  newit->next = list->begin;
  list->begin->prev = newit;
  list->begin = newit;
  list->size++;
}

void		list_push_position(t_list *list, int pos, t_iterator *newit)
{
  t_iterator	*it;

  if (pos-- == 0 || list->size == 0)
    return (list_push_front(list, newit));
  it = list->begin;
  while (it->id != list->end->id)
    {
      if (pos == 0)
	{
	  newit->prev = it;
	  newit->next = it->next;
	  it->next->prev = newit;
	  it->next = (it->id != list->end->id) ? newit : it->next;
	  list->size++;
	  break;
	}
      it = it->next;
      --pos;
    }
}

void		list_push_iterator(t_list *list, t_iterator *it, t_iterator *newit)
{
  t_iterator	*itnext;

  if (it == NULL)
    return (list_push_front(list, newit));
  itnext = list->begin;
  while (itnext->id != list->end->id)
    {
      if (itnext->id == it->id)
	{
	  newit->prev = it;
	  newit->next = it->next;
	  it->next->prev = newit;
	  if (it->id != list->end->id)
	    it->next = newit;
	  break;
	}
      itnext = itnext->next;
    }
}
