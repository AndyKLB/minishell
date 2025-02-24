/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:57:23 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/14 15:29:56 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_node(t_my_env *env, char *key, char *value, int index)
{
	t_my_env	*tmp_env;

	create_node_env(&env, index);
	tmp_env = ft_last_env(env);
	tmp_env->index = index;
	tmp_env->key = ft_strdup(key);
	tmp_env->value = ft_strdup(value);
}

t_my_env	*modify_env(char *key, char *value, t_my_env *env)
{
	t_my_env	*tmp_env;
	int			index;

	index = 0;
	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strlen(tmp_env->key) == ft_strlen(key))
		{
			if (!ft_strncmp(tmp_env->key, key, ft_strlen(tmp_env->key)))
			{
				free(tmp_env->value);
				tmp_env->value = ft_strdup(value);
				break ;
			}
		}
		tmp_env = tmp_env->next;
		index++;
	}
	if (!tmp_env)
		add_node(env, key, value, index);
	return (env);
}
