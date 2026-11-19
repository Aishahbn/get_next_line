*This project has been created as part of the 42 curriculum by yabuhuss.*

# get_next_line

## Description

`get_next_line()` is a C function that returns one line at a time from a file
descriptor. Calling it repeatedly in a loop reads the whole file (or standard
input) line by line, until there is nothing left to read.

```c
char	*get_next_line(int fd);
```

- Returns the line that was read, **including the terminating `\n`** (except for
  the last line if the file does not end with a newline).
- Returns `NULL` when there is nothing left to read or when an error occurs.
- Only `read`, `malloc` and `free` are used. No `libft`, no `lseek`, no global
  variables.

The main goal of the project is to learn about **static variables**: the
function must remember what it has already read between two calls.

### Bonus

The bonus version manages **several file descriptors at the same time** using
a **single static variable**. You can read a line from fd 3, then fd 4, then fd
3 again, and each one continues from where it stopped.

### Files

| Part      | Files                                                                 |
|-----------|-----------------------------------------------------------------------|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`          |
| Bonus     | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` |

## Instructions

### Compilation

The buffer size for `read()` is set at compile time with `-D BUFFER_SIZE=n`.
If the flag is not given, a default value of `42` is used.

```sh
# Mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

`main.c` is your own test file that includes the header and calls
`get_next_line()`. It is not part of the project.

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

The caller is responsible for calling `free()` on every returned line.

### Testing

The function was tested with `-fsanitize=address,undefined` and with
`BUFFER_SIZE` values of 1, 2, 42, 9999 and 10000000, as well as without the
flag. Cases covered: regular file, empty file, file without a final `\n`, file
made only of `\n`, a very long line, standard input (pipe), invalid fd (`-1`,
out of range, closed fd), and, for the bonus, interleaved reads from several
file descriptors.

## Algorithm

The algorithm uses a **static buffer ("stash")** that keeps the data that was
read but not yet returned.

Each call to `get_next_line(fd)` does the following:

1. **Check the input.** If `fd < 0` or `BUFFER_SIZE <= 0` (and, in the bonus,
   `fd >= MAX_FD`), return `NULL`.
2. **`read_to_stash`**: while the stash does not contain a `\n` and `read()`
   has not reached the end of the file, read `BUFFER_SIZE` bytes into a
   temporary buffer and append it to the stash with `str_join`.
   Reading stops as soon as a newline is in the stash, so the function never
   reads more than needed to return the current line.
3. **`extract_line`**: copy everything from the start of the stash up to and
   including the first `\n` (or up to the end of the stash if there is none).
4. **`update_stash`**: build a new stash containing only what comes after the
   returned line, and free the old one. If nothing is left, the stash becomes
   `NULL`.

Memory is freed on every path: when `read()` fails, when a `malloc` fails, when
the end of the file is reached, and when `extract_line` fails (the stash is
freed and set back to `NULL` so no dangling pointer remains).

### Why this design

- **Static string as the state.** The subject forbids global variables, and a
  static pointer is the simplest way to keep the leftover data between calls.
- **Reading `BUFFER_SIZE` bytes at a time until a `\n` appears.** It respects
  the rule of reading as little as possible, and it works with any buffer size
  (1 as well as 10000000), because the buffer is allocated on the heap and
  the loop does not depend on the line length.
- **Small helper functions.** Each function does one job
  (`read_to_stash`, `extract_line`, `update_stash`), which keeps every function
  within the Norm limits and makes each step easy to test and explain.
- **Trade-off.** `str_join` allocates a new string and copies the old content
  each time, so a very long line read with a very small buffer costs more
  copies. A linked list of chunks would avoid this, but a plain string was
  chosen for simplicity and readability.

### Bonus: multiple file descriptors

The single static variable becomes an **array of pointers**:

```c
static char	*stash[MAX_FD];
```

Each file descriptor uses its own slot, `stash[fd]`, so the reading state of
one fd never mixes with another. `MAX_FD` is defined in the header (1024) and
`fd >= MAX_FD` is rejected, to avoid reading outside of the array. The helper
functions are unchanged because they work on a single `char *` and do not need
to know which fd it belongs to.

## Resources

### References

- `man 2 read`, `man 3 malloc`, `man 3 free`
- The 42 `get_next_line` subject
- Documentation on static variables and storage duration in C
- AddressSanitizer / UndefinedBehaviorSanitizer documentation (GCC / Clang)

### Use of AI

AI (Claude) was used as a learning and review tool, not as a replacement for
writing the project. AI also helped me write this README: it was drafted with
AI assistance from my code and the subject requirements, and I then reviewed,
corrected and approved the final text myself.

- **Explaining concepts**: what a static variable is, and how to adapt the
  design to handle several file descriptors in the bonus.
- **Code review**: pointing out memory leaks and error-path problems in my
  `read_to_stash` and `get_next_line` (the old stash not being freed after
  `str_join`, after a `read()` error, and when `extract_line` fails), and Norm
  issues (indentation, brackets, trailing whitespace, missing 42 headers,
  wrong `#include` in the bonus utils file).
- **Fixes**: after the review, a corrected version of `read_to_stash` and the
  `extract_line` failure handling in `get_next_line` were suggested; I then
  adapted them into my files for the mandatory and bonus parts.
- **Testing**: running my files with sanitizers and different buffer sizes
  and fd cases to check the behaviour.
- **Documentation (README)**: AI helped me write this README file. It was
  drafted with AI help from my code and the subject requirements, and I checked
  that every statement matches what my code actually does.

The core structure (stash, helper functions, and the bonus array) was written
by me, and I reviewed and tested every change before submitting.
