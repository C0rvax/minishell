/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:58:49 by aduvilla          #+#    #+#             */
/*   Updated: 2024/04/18 14:52:38 by aduvilla         ###   ########.fr       */
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

static char	**get_export(t_exec *exec)
{
	char	**export;
	int		len;
	int		i;
	int		j;

	len = ft_lenarr(exec->mini_env, exec->export);
	export = malloc(sizeof(char *) * (len + 1));
	if (!export)
		return (NULL);
	i = 0;
	while (exec->mini_env && exec->mini_env[i])
	{
		export[i] = exec->mini_env[i];
		i++;
	}
	j = 0;
	while (exec->export && exec->export[j])
	{
		export[i + j] = exec->export[j];
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
			if (str[i] == '=' && quote == 0)
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

int	print_export(t_exec *exec, int mode)
{
	int		i;
	int		fd;
	char	**export;

	i = 0;
	if (mode == 1)
		fd = redirect_out(exec);
	else
		fd = 1;
	if (fd < 0)
		return (clear_one(exec, msg_built(FD, exec->cmd->argv[1], 1)));
	export = get_export(exec);
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
