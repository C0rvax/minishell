/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:24 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/23 12:49:04 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_in_env(char **tab, char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!tab || !str)
		return (0);
	var = ft_strjoin(str, "=");
	if (!var)
		return (0);
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var, ft_strlen(var)))
			return (free(var), 1);
	}
	return (free(var), 0);
}

static int	is_unset(char *str, char **tab)
{
	int		i;
	char	*var;

	i = 1;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		var = ft_strjoin(tab[i], "=");
		if (!var)
			return (0);
		if (ft_strncmp(str, var, ft_strlen(var)))
			return (free(var), 1);
		free(var);
		i++;
	}
	return (0);
}

void	exec_unset(t_exec *exec, t_persistent *pers)
{
	char	**cpy;
	char	**new;
	int		i;
	int		count;

	i = 0;
	count = 0;
	cpy = pers->mini_env;
	while (exec->cmd->argv[++i])
	{
		if (is_in_env(cpy, exec->cmd->argv[i]))
			count++;
	}
	ft_printf("count : %d\n", count);
	new = malloc(sizeof(char *) * (ft_lenarr(cpy, 1) - count + 1));
	if (!new)
		clean_exit_parent(exec, msg_error("minishell:", strerror(errno), 1));
	i = 0;
	count = 0;
	while (cpy[i + count])
	{
		if (!is_unset(cpy[i + count], exec->cmd->argv))
		{
			ft_printf("on print la ligne\n");
			new[i] = ft_strdup(cpy[i + count]);
			if (!new[i])
				clean_exit_parent(exec,
					  msg_error("minishell:", strerror(errno), 1));
			i++;
		}
		else
			count++;
	}
	new[i] = NULL;
	ft_freetab(cpy);
	pers->mini_env = new;
}
