#include <iostream>
#include "list.hh"

t_iterator *creait()
{
  t_test *it;

  it = new t_test();
  it->prev = NULL;
  it->next = NULL;
  it->id = give_unique_list_id();
  it->name = " name";
  return ((t_iterator*)it);
}

void	dump_list(t_list *list)
{
  t_iterator	*it;

  it = list->begin;
  while (it != list->end)
    {
      std::cout << "it:" << it->id << std::endl;
      it = it->next;
    }
}

int main(int ac, char **av)
{
  t_list *list;

  list = list_init();
  list_push_back(list, creait());
  list_push_back(list, creait());
  list_push_back(list, creait());
  t_iterator *newit = creait();
  list_push_back(list, newit);
  list_push_back(list, creait());
  list_push_back(list, creait());
  list_push_front(list, creait());
  list_push_position(list, 4, creait());
  list_push_iterator(list, newit, creait());
  std::cout << "size = " << list->size << std::endl;
  std::cout << "specelem id = " << newit->id << std::endl;
  t_test *test;
  test = (t_test*)newit;
  dump_list(list);
  std::cout << "name = " << test->name << std::endl;
  list_pop_back(list);
  list_pop_back(list);
  list_pop_back(list);
  list_pop_front(list);
  list_supr(list, list->begin);
  dump_list(list);
  return (0);
}
