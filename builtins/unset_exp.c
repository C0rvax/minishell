/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:01:17 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/16 16:11:43 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_in_exp(char **tab, char *str)
{
	int	i;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], str))
			return (1);
		i++;
	}
	return (0);
}

static int	count_in_exp(char **exp, char **argv)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (argv && argv[0])
	{
		while (argv[i])
		{
			if (is_in_exp(exp, argv[i]))
				count++;
			i++;
		}
	}
	return (count);
}

static int	copy_export(char ***new, char **exp, char **argv)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (exp[i + count])
	{
		if (!is_in_exp(&argv[1], exp[i + count]))
		{
			new[0][i] = ft_strdup(exp[i + count]);
			if (!new[0][i])
				return (1);
			i++;
		}
		else
			count++;
	}
	new[0][i] = NULL;
	return (0);
}

int	unset_exp(t_exec *exec, t_pers *pers)
{
	int		count;
	char	**cpy;
	char	**argv;
	char	**new;

	cpy = pers->export;
	argv = exec->cmd->argv;
	count = count_in_exp(cpy, argv);
	if (count > 0)
	{
		new = malloc(sizeof(char *) * (ft_lenarr(NULL, cpy) - count + 1));
		if (!new)
			return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
		if (copy_export(&new, cpy, argv))
		{
			ft_freetab(new);
			return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
		}
		ft_freetab(cpy);
		pers->export = new;
	}
	return (0);
}
