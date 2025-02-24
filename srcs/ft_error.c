/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:50:37 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/23 12:48:10 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_all *all)
{
	if (all->cmds)
		free_redir(all->cmds);
	if (all->strs)
	{
		free_strs(all->strs);
		all->strs = NULL;
	}
	if (all->cmds)
		free_cmds(&all->cmds);
	if (all->lexer)
		free_lexer(&all->lexer);
	if (all->expand)
		free_expand(&all->expand);
	if (all->shell_id)
		all->shell_id = NULL;
	if (all->line)
		free(all->line);
	all->line = NULL;
}

int	is_triple_redir(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '<')
	{
		while (line[i])
		{
			if (line[i] == '<' && line[i + 1] == '<')
				i++;
			else
				i++;
		}
	}
	if (i == 0)
		i++;
	return (i);
}

int	ft_final(t_all *all, char *error, char *msgerror, int sortie)
{
	if (all->fd_in > 0)
	{
		dup2(all->fd_in, STDIN_FILENO);
		close(all->fd_in);
	}
	if (msgerror)
		msg_error(all, msgerror, error, sortie);
	free_all(all);
	all->exit_code = sortie;
	return (sortie);
}

void	msg_error(t_all *all, char *msgerror, char *error, int sortie)
{
	if (is_triple_redir(all->line) == 3)
		error = "newline";
	if (!ft_strncmp(msgerror, ERR_SYNTAX, 26))
		ft_printf_fd(2, "%s%s'", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_EGAL, 20))
		ft_printf_fd(2, "%s%s': not a valid identifier", msgerror, error);
	else if (!ft_strncmp(msgerror, ERR_BASE, 14))
		ft_printf_fd(2, "%s%s': command not found", msgerror, error);
	else if (sortie == ERR_DIR)
		ft_printf_fd(2, "minishell: %s: %s", error, msgerror);
	else if (sortie == ERR_DIDIR)
		ft_printf_fd(2, "minishell: %s: %s", error, msgerror);
	else if (sortie == ERR_USAGE && !ft_strncmp(msgerror, "file not found", 14))
		ft_printf_fd(2, "minishell: %s: %s: %s", error, all->cmds->strs[1],
			msgerror);
	else if (sortie == ERR_USAGE)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", error, msgerror);
		ft_printf_fd(2, "%s: usage: %s filename [arguments]", error, error);
	}
	else
		ft_putstr_fd(msgerror, 2);
	ft_putchar_fd('\n', 1);
	all->exit_code = sortie;
}
