*This project has been created as part of the 42 curriculum by aboel-ma.*

# Get Next Line

## Description

**Get Next Line** is a project from the 42 curriculum. Its goal is to develop a function that reads and returns a line from a file descriptor, one line at a time.

The function must return a line including the newline character (`\n`) when it exists. If the end of the file is reached and the last line does not end with a newline, it must return the remaining characters.

The main objective of this project is to understand how file descriptors, the `read()` function, static variables, and dynamic memory allocation work in C.

### Function Prototype

```c
char *get_next_line(int fd);
```

- `fd`: The file descriptor to read from.
- Return value: A string containing the next line, or `NULL` if there is nothing left to read or an error occurs.

## Instructions

### Compilation

This project does not use a Makefile or an external library.

Compile the source files directly using `cc`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` determines the maximum number of bytes read in each call to `read()`.

You can change its value to test different reading conditions:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Execution

Run the compiled program with:

```bash
./gnl
```

The `main.c` file is used only for testing. It should not be included in the final submitted files if the project subject does not allow it.

### Testing

It is important to test different situations:

- A file containing multiple lines.
- An empty file.
- A file containing only one line.
- A file without a newline at the end.
- A very long line.
- Different `BUFFER_SIZE` values.
- Invalid file descriptors.

## Algorithm and Technical Choices

### 1. Reading with `read()`

The project uses the `read()` system call to read data from a file descriptor.

Instead of reading the entire file at once, the function reads a limited number of bytes determined by `BUFFER_SIZE`.

The `read()` function can return:

- A positive value: the number of bytes successfully read.
- `0`: the end of the file has been reached.
- `-1`: an error has occurred.

### 2. Using a Static Variable

A static variable is used to preserve the data that has been read but has not yet been returned.

This is necessary because `get_next_line()` is called multiple times, and each call must continue reading from where the previous call stopped.

For example, if the stored data is:

```text
Hello\nWorld\n
```

The first call returns:

```text
Hello\n
```

The remaining data:

```text
World\n
```

is kept for the next call.

### 3. Reading and Saving Data

The function reads data into a temporary buffer.

If no newline is found, it continues reading and joins the new data with the previously stored content.

This process continues until:

- A newline character is found.
- The end of the file is reached.
- A reading or memory allocation error occurs.

### 4. Extracting the Line

Once a newline is found, the function extracts the first complete line from the stored data.

The extracted line includes `\n` if it exists.

The original stored data is not immediately discarded because it may contain additional lines.

### 5. Updating the Stored Data

After extracting the line, the remaining characters are saved for the next function call.

The memory used by the previous stored string is freed after the remaining content has been copied successfully.

This process prevents unnecessary memory usage and allows the function to continue reading correctly.

### Why This Algorithm?

This algorithm was selected because it allows the program to read files progressively without loading the entire file into memory.

Using a static variable preserves unread data between function calls, while dynamic memory allocation allows the stored content to grow depending on the size of the line.

It also provides a clear separation between reading data, extracting a line, and keeping the remaining content.

## Resources

The following resources were used to understand the concepts behind this project:

- **read(2)** — Linux manual page: https://man7.org/linux/man-pages/man2/read.2.html
- **malloc(3)** — Linux manual page: https://man7.org/linux/man-pages/man3/malloc.3.html
- **free(3)** — Linux manual page: https://man7.org/linux/man-pages/man3/free.3.html
- **42 Get Next Line Subject** — The official project subject.
- **42 Intra / Peer Learning** — Discussions and explanations about file descriptors, static variables, memory allocation, and file reading.

### AI Usage

AI tools were used as learning and development support during this project.

They helped with:

- Understanding file descriptors, inodes, and the `read()` system call.
- Understanding static variables and how they preserve data between function calls.
- Learning dynamic memory allocation and memory management with `malloc()` and `free()`.
- Understanding the algorithm and the different steps of Get Next Line.
- Reviewing code, identifying potential errors, and understanding edge cases.
- Preparing test cases and improving the project documentation.

AI was used as an educational assistant. The implementation was developed and tested by the student, with the goal of understanding the code and being able to explain its behavior.