#include <sys/types.h>
#include <signal.h>

/**
 * pid_exist - checks if pid exists
 * @pid: the pid to check
 * Return: 1 if exists else 0
 */
int pid_exist(pid_t pid)
{
	return (!kill(pid, 0));
}
