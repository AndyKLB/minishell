/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:19:59 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/05 15:20:02 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_my_env	*ft_last_env(t_my_env *my_env)
{
	t_my_env	*current;

	if (!my_env)
		return (NULL);
	current = my_env;
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_back_env(t_my_env **my_env, t_my_env *new)
{
	t_my_env	*last;

	if (!new)
		return ;
	if (!*my_env)
		*my_env = new;
	else
	{
		last = ft_last_env(*my_env);
		last->next = new;
		new->next = NULL;
	}
}

t_my_env	*ft_new_env(int i)
{
	t_my_env	*elem;

	elem = malloc(sizeof(t_my_env));
	if (!elem)
		return (NULL);
	elem->key = NULL;
	elem->value = NULL;
	elem->index = i;
	elem->next = NULL;
	return (elem);
}

t_my_env	*create_node_env(t_my_env **my_env, int i)
{
	if (i == 0)
		*my_env = ft_new_env(i);
	else
		ft_back_env(my_env, ft_new_env(i));
	return (*my_env);
}

int	ft_lstsize_env(t_my_env *lst)
{
	int			i;
	t_my_env	*actuel;

	actuel = lst;
	i = 0;
	while (actuel)
	{
		actuel = actuel->next;
		i++;
	}
	return (i);
}
