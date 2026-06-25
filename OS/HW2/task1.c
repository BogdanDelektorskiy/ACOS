#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 4) {
        write(STDERR_FILENO, "Usage: ./task1 file I N\n", 24);
        return 1;
    }

    char *filename = argv[1];
    long start_line = atol(argv[2]);
    long lines_to_print = atol(argv[3]);
    if (start_line < 1 || lines_to_print < 0) {
        write(STDERR_FILENO, "Invalid line numbers\n", 21);
        return 1;
    }

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    char buf[BUF_SIZE];
    char outbuf[BUF_SIZE];
    ssize_t outpos = 0;
    long current_line = 1;
    long lines_output = 0;
    off_t file_offset = 0;
    ssize_t nread;

    while (file_offset < st.st_size && lines_output < lines_to_print) {
        nread = read(fd, buf, BUF_SIZE);
        if (nread <= 0) break;

        for (ssize_t i = 0; i < nread && lines_output < lines_to_print; i++) {
            if (current_line >= start_line) {
                outbuf[outpos++] = buf[i];
                if (outpos == BUF_SIZE) {
                    write(STDOUT_FILENO, outbuf, outpos);
                    outpos = 0;
                }
            }

            if (buf[i] == '\n') {
                if (current_line >= start_line) {
                    lines_output++;
                    if (lines_output == lines_to_print) {
                        break;
                    }
                }
                current_line++;
            }
        }
        file_offset += nread;
    }

    if (outpos > 0) {
        write(STDOUT_FILENO, outbuf, outpos);
    }

    close(fd);
    return 0;
}