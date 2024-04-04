/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:33:18 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/04 18:43:29 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	sort_alpharr(char **export, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (strcmp(export[j], export[j + 1]) > 0)
			{
				tmp = export[j + 1];
				export[j + 1] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**get_export(t_persistent *pers)
{
	char	**export;
	int		len;
	int		i;
	int		j;

	len = ft_lenarr(pers->mini_env, pers->export);
	export = malloc(sizeof(char *) * (len + 1));
	if (!export)
		return (NULL);
	i = 0;
	while (pers->mini_env && pers->mini_env[i])
	{
		export[i] = pers->mini_env[i];
		i++;
	}
	j = 0;
	while (pers->export && pers->export[j])
	{
		export[i + j] = pers->export[j];
		j++;
	}
	export[i + j] = NULL;
	sort_alpharr(export, len);
	return (export);
}

static int	ft_putexport_fd(char *str, int fd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putchar_fd(str[i], fd);
			if (str[i] == '=')
			{
				ft_putchar_fd('"', fd);
				quote = 1;
			}
			i++;
		}
	}
	if (quote)
		ft_putchar_fd('"', fd);
	return (i);
}

static int	print_env(t_exec *exec, t_persistent *pers)
{
	int		i;
	int		fd;
	char	**export;

	i = 0;
	fd = redirect_out(exec);
	if (fd < 0)
		return (clear_one(exec, msg_built(FD, exec->cmd->argv[1], 1)));
	export = get_export(pers);
	if (!export)
		return (clear_one(exec, msg_built(BMALLOC, strerror(errno), 1)));
	while (export[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putexport_fd(export[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	free(export);
	if (fd != 1)
		close(fd);
	return (0);
}

int	exec_export(t_exec *exec, t_persistent *pers)
{
	char	**new;
	char	**argv;
	char	**cpy;

	if (exec->total_cmd != 1)
		return (clear_one(exec, 0));
	argv = exec->cmd->argv;
	if (!argv[1])
		if (print_env(exec, pers))
			return (1);
	cpy = exec->mini_env;
	new = ft_joinarr(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->mini_env = new;
	cpy = pers->export;
	new = ft_joinexp(argv, cpy);
	if (!new)
		return (clear_one(exec, msg_built(BMALLOC, argv[1], 1)));
	ft_freetab(cpy);
	pers->export = new;
	return (clear_one(exec, 0));
}
