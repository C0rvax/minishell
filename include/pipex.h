/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:03:33 by aduvilla          #+#    #+#             */
/*   Updated: 2024/03/05 16:28:49 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct data_s
{
	char	**av;
	char	**env;
	char	**paths;
	char	**argv;
	char	*cmd;
	int		hd;
	int		cmd_n;
	int		cmd_max;
	int		*fd;
	int		**pipefd;
	int		*pid;
}				t_data;

typedef enum error_e
{
	MALLOC,
	PIPE,
	CMD,
	DUP,
	EXEC,
	FORK,
	INFILE,
	OUTFILE
}			t_err;

t_data	init_struct(int ac, char **av, char **env);
void	free_struct(t_data *data);
void	init_argv(t_data *data);
void	exec_cmd(t_data *data);
void	open_file(t_data *data);
void	close_file(t_data *data);
void	clean_exit(t_data *data, t_err error, int status_code);
void	print_error(char *s1, char *s2);

#endif
