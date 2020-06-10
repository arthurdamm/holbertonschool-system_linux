#include "strace.h"

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
	char *dict[] = SYSCALL_NUM_TO_NAME;

	setbuf(stdout, NULL);
	if (ac < 2)
		return (EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
	{
		dprintf(STDERR_FILENO, "Fork failed: %d\n", errno);
		exit(-1);
	}
	else if (!child_pid)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		if (execve(av[1], av + 1, envp) == -1)
		{
			dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
			exit(-1);
		}
	}

	do {
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		wait(&status);
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (last_syscall)
			last_syscall = 0;
		else
		{
			last_syscall = uregs.orig_rax;
			printf("%s\n", dict[last_syscall]);
		}
	} while (!WIFEXITED(status));
	return (0);
}
