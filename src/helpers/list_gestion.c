/*
** list_gestion.c for list in /home/trouve_b/Desktop/PSU_2015_myirc
** 
** Made by Alexis Trouve
** Login   <trouve_b@epitech.net>
** 
** Started on  Wed Jun  1 16:43:41 2016 Alexis Trouve
** Last update Mon Jun 13 14:45:57 2016 Alexis Trouve
*/

#include "list.hh"

t_iterator	*list_give_element(t_list *list, int pos)
{
  t_iterator	*it;

  it = list->begin;
  while (it->id != list->end->id)
    {
      if (pos == 0)
	return (it);
      pos--;
    }
  return (NULL);
}

int		list_element_exist(t_list *list, t_iterator *itsearch)
{
  unsigned int	i;
  t_iterator	*it;

  i = 0;
  if (itsearch == NULL)
    return (-1);
  it = list->begin;
  while (it->id != list->end->id)
    {
      if (itsearch->id == it->id)
	return (i);
      it = it->next;
      ++i;
    }
  return (-1);
}
