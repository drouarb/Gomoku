/*
** list_add.c for list in /home/trouve_b/Desktop/PSU_2015_myirc
** 
** Made by Alexis Trouve
** Login   <trouve_b@epitech.net>
** 
** Started on  Wed Jun  1 14:26:44 2016 Alexis Trouve
** Last update Mon Jun 13 17:37:15 2016 Alexis Trouve
*/

#include "Helpers/list.hh"

t_list		*list_init()
{
  t_list	*list;
  t_iterator	*it;

  if ((list = (t_list*)malloc(sizeof(t_list))) == NULL)
    exit(list_put_message_for_insufficient_memory());
  list->size = 0;
  if ((it = (t_iterator*)malloc(sizeof(t_iterator))) == NULL)
    exit(list_put_message_for_insufficient_memory());
  it->id = 0;
  it->next = NULL;
  it->prev = NULL;
  list->begin = it;
  list->end = it;
  return (list);
}

t_iterator	**list_destroy(t_list *list)
{
  t_iterator	**myreturn;
  t_iterator	*it;
  int		i;

  if ((myreturn = (t_iterator**)malloc(sizeof(t_iterator*) * (list->size + 1))) == NULL)
    exit(list_put_message_for_insufficient_memory());
  it = list->begin;
  i = 0;
  while (it->id != list->end->id)
    {
      myreturn[i++] = it;
      it = it->next;
    }
  myreturn[i] = NULL;
  free(list->end);
  free(list);
  return (myreturn);
}

bool		list_empty(t_list *list)
{
  return ((list->size == 0) ? true : false);
}

int		list_put_message_for_insufficient_memory()
{
  write(2, "Error : out of memory\n", 22);
  return (-1);
}
