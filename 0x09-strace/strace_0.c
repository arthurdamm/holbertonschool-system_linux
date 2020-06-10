#include "strace.h"

void trace_child(char **av, char **envp);

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * @envp: environ
 * Return: EXIT_SUCCESS or error.
 */
int main(int ac, char **av, char **envp)
{
	pid_t child_pid;
	int status = 0;
	struct user_regs_struct uregs;
	unsigned long last_syscall = 0;

	if (ac < 2)
	{
		printf("Usage: %s command [args...]\n", av[0]);
		return (EXIT_FAILURE);
	}
	setbuf(stdout, NULL);
	child_pid = fork();
	if (child_pid == -1)
	{
		dprintf(STDERR_FILENO, "Fork failed: %d\n", errno);
		exit(-1);
	}
	else if (!child_pid)
	{
		trace_child(av, envp);
	}
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	do {
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		wait(&status);
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (last_syscall)
		{
			last_syscall = 0;
		}
		else
		{
			last_syscall = uregs.orig_rax;
			printf("%lu\n", last_syscall);
		}
	} while (!WIFEXITED(status));
	return (0);
}


/**
 * trace_child - traces child process
 * @av: argument vector for execve
 * @envp: environ for execve
 */
void trace_child(char **av, char **envp)
{
	ptrace(PTRACE_TRACEME, 0, 0, 0);
	if (execve(av[1], av + 1, envp) == -1)
	{
		dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
		exit(-1);
	}
}
