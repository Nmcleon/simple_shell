#include "shell.h"
#include <unistd.h>

/**
 * print_crab - prints the soft shell logo!
 */
void print_crab(void)
{
	write(STDOUT_FILENO, "   /\\ \n", 7);
	write(STDOUT_FILENO, " ( /   @ @    ()   welcome\n", 28);
	write(STDOUT_FILENO, "  \\  __| |__  /     to\n", 21);
	write(STDOUT_FILENO, "   -/    \"    \\    soft\n", 22);
	write(STDOUT_FILENO, "  /-|         |-\\  shell\n", 24);
	write(STDOUT_FILENO, " / /-\\        /-\\\\ \n", 20);
	write(STDOUT_FILENO, "   / /-`---'-\\ \\ \n", 18);
	write(STDOUT_FILENO, "   /         \\ \\ \n\n", 19);
	write(STDOUT_FILENO, "\n(╯°□°)╯︵ ┻━┻ ===| ", 20);
}
