#include "strace.h"

void trace_child(char **av, char **envp);
void trace_parent(pid_t child_pid);
int await_syscall(pid_t child_pid);
unsigned long get_syscall_param(struct user_regs_struct uregs, size_t i,
	pid_t child);

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
		trace_child(av, envp);
	else
		trace_parent(child_pid);
	return (0);
}

/**
 * trace_child - traces child process
 * @av: argument vector for execve
 * @envp: environ for execve
 */
void trace_child(char **av, char **envp)
{
	setbuf(stdout, NULL);
	printf("execve(0, 0, 0) = 0\n");
	ptrace(PTRACE_TRACEME, 0, 0, 0);
	kill(getpid(), SIGSTOP);
	if (execve(av[1], av + 1, envp) == -1)
	{
		dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
		exit(-1);
	}
}

/**
 * trace_parent - calls made by tracing parent
 * @child_pid: pid of child to trace
 */
void trace_parent(pid_t child_pid)
{
	int status, i, first = 1;
	struct user_regs_struct uregs;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (first && uregs.orig_rax == 59)
			first = 1;
		else
		{
			printf("%s(", syscalls_64_g[uregs.orig_rax].name);
			for (i = 0; i < (int)syscalls_64_g[uregs.orig_rax].nb_params; i++)
			{
				if (i)
					printf(", ");
				if (syscalls_64_g[uregs.orig_rax].params[i] == VARARGS)
					printf("...");
				else if(syscalls_64_g[uregs.orig_rax].params[i] == CHAR_P)
					printf("%s", (char *)get_syscall_param(uregs, i, child_pid));
				else
					printf("%#lx", get_syscall_param(uregs, i, child_pid));
			}
		}
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (first && uregs.orig_rax == 59)
			first = 0;
		else
			printf(") = %#lx\n", (unsigned long)uregs.rax);
	}
}

/**
 * await_syscall - waits for a syscall
 * @child_pid: pid of process to await
 * Return: 0 if child stopped, 1 if exited
 */
int await_syscall(pid_t child_pid)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		waitpid(child_pid, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
		{
			printf(") = ?\n");
			return (1);
		}
	}
}

/**
 * get_syscall_param - gets given parameter for syscall
 * @uregs: userspace register struct
 * @i: syscall parameter index
 * @child_pid: pid of child
 * Return: value of param
 */
unsigned long get_syscall_param(struct user_regs_struct uregs, size_t i,
	pid_t child)
{
	switch (i)
	{
		case 0: return (uregs.rdi);
		case 1: return (uregs.rsi);
		case 2: return (uregs.rdx);
		case 3: return (uregs.r10);
		case 4: return (uregs.r8);
		case 5: return (uregs.r9);
		default: return (-1);
	}
	(void)uregs;
	(void)child;
}
