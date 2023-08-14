/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-den <nvan-den@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:21:12 by nvan-den          #+#    #+#             */
/*   Updated: 2023/08/14 13:29:05 by nvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_pipes(int num_pipes, int (*pipes)[2])
{
    int i = 0;
    while (i < num_pipes)
    {
        if (pipe(pipes[i]) == -1)
            error_msg("Error creating pipe\n");
        i++;
    }
}

void close_unused_pipes(int num_pipes, int (*pipes)[2], int current_pipe)
{
    int i = 0;
    while (i < num_pipes)
    {
        if (i != current_pipe)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        i++;
    }
}

void execute_pipes(t_cmd *cmds, int num_pipes, int (*pipes)[2], t_data *data)
{
	int status;
	int pid[data->pipex + 1];
	int	i;
	
	i = 0;
	while (i < num_pipes)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error_msg("Error creating process\n");
		else if (pid[i] == 0)
		{ // Child process
			close_unused_pipes(num_pipes, pipes, i);
			if (i > 0)
				dup2(pipes[i- 1][0], STDIN_FILENO); // Read from previous pipe
			if (i < num_pipes - 1)
				dup2(pipes[i][1], STDOUT_FILENO); // Write to current pipe
			execute_command(pipes[i][0], pipes[i][1], &cmds[i], data);
		} 
		else 
		{ // Parent process
			close(pipes[i][1]); // Close write end of current pipe
		}
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            printf("Child process %d exited with status %d\n", pid[i], WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Child process %d terminated by signal %d\n", pid[i], WTERMSIG(status));
		i++;
	}
}