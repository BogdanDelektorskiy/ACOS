#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./task2 file\n", 20);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
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

    if (st.st_size == 0) {
        close(fd);
        return 0;
    }

    off_t mid = st.st_size / 2;

    off_t search_start = mid - BUF_SIZE;
    if (search_start < 0) search_start = 0;
    char buf[BUF_SIZE];
    lseek(fd, search_start, SEEK_SET);
    ssize_t n = read(fd, buf, mid - search_start);
    if (n <= 0) { close(fd); return 1; }

    off_t line_start = 0;
    for (ssize_t i = n - 1; i >= 0; i--) {
        if (buf[i] == '\n') {
            line_start = search_start + i + 1;
            break;
        }
    }
    if (line_start == 0 && search_start > 0) {
        line_start = 0;
    }

    lseek(fd, mid, SEEK_SET);
    n = read(fd, buf, BUF_SIZE);
    if (n < 0) { close(fd); return 1; }

    off_t line_end = st.st_size;
    for (ssize_t i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            line_end = mid + i;
            break;
        }
    }

    lseek(fd, line_start, SEEK_SET);
    off_t len = line_end - line_start;
    if (len > 0) {
        char outbuf[BUF_SIZE];
        while (len > 0) {
            ssize_t to_read = len < BUF_SIZE ? len : BUF_SIZE;
            ssize_t r = read(fd, outbuf, to_read);
            if (r <= 0) break;
            write(STDOUT_FILENO, outbuf, r);
            len -= r;
        }
    }
    write(STDOUT_FILENO, "\n", 1);

    close(fd);
    return 0;
}