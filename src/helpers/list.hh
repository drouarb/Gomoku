/*
** list.h for list in /home/trouve_b/Desktop/PSU_2015_myirc
** 
** Made by Alexis Trouve
** Login   <trouve_b@epitech.net>
** 
** Started on  Wed Jun  1 14:30:35 2016 Alexis Trouve
** Last update Sat Jun 18 12:57:35 2016 Esteban Lewis
*/

#ifndef LIST_H_
# define LIST_H_

#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <string>

typedef	struct	s_list		t_list;
typedef	struct	s_iterator	t_iterator;
typedef struct	s_test		t_test;

struct			s_test
{
  t_test		*next;
  t_test		*prev;
  unsigned int		id;
  std::string		name;
};

struct                  s_iterator
{
  t_iterator		*next;
  t_iterator		*prev;
  unsigned int		id;
};

struct			s_list
{
  t_iterator		*begin;
  t_iterator		*end;
  unsigned int		size;
};

/*
**	used internally
*/

// put a message for insufficient memory
int		list_put_message_for_insufficient_memory();

/*
**	gestion basic de la liste
*/

// renvois un id unique utile lors de la creation d'it
unsigned int	give_unique_list_id();

// initialise la liste
t_list		*list_init();

// renvois si la liste est vide
bool		list_empty(t_list *list);

// free la liste et renvois ses iterateurs
// avec un NULL à la fin
t_iterator	**list_destroy(t_list *list);

/*
**	ajout de donnée
*/

// ajoute un élément à la fin de la liste
void		list_push_back(t_list *list, t_iterator *newit);

// ajoute un élément au début de la liste
void		list_push_front(t_list *list, t_iterator *newit);

// ajoute un élément à la position donnée
void		list_push_position(t_list *list, int position, t_iterator *newit);

// ajoute un élément après l'itérator envoyé
void		list_push_iterator(t_list *list, t_iterator *it, t_iterator *newit);

/*
**	suppression de donnée
*/

// supprime le dernier élément renvois l'iterateur
t_iterator	*list_pop_back(t_list *list);

// supprime le premier élément renvois l'iterateur
t_iterator	*list_pop_front(t_list *list);

// supprime l'itérateur de la liste renvois l'iterateur
t_iterator	*list_supr(t_list *list, t_iterator *it);

// supprime les itérateur de la liste ainsi que tout les intermédiaire
// renvois un tableau d'iterateur
t_iterator	**list_erase(t_list *list, t_iterator *begin, t_iterator *end);

/*
**	gestion de donnée
*/

// renvois l'iterateur à la position indiqué
t_iterator	*list_give_element(t_list *list, int pos);

// renvois la position si l'itérateur passé en paramètre
// en présent dans la liste et -1 si l'élément est introuvable
int		list_element_exist(t_list *list, t_iterator *it);

#endif
