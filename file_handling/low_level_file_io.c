#include <unistd.h>      /* read(), write(), close() */
#include <fcntl.h>       /* open() and flags */
#include <sys/stat.h>    /* permission bits */
#include <stdio.h>       /* printf(), perror() */
#include <string.h>      /* strlen() */


/*
 * low_level_file_io.c
 * -------------------
 * Short, focused tutorial demonstrating low-level OS file I/O.
 * Concepts covered:
 *  - File descriptors (integers returned by open())
 *  - open(), read(), write(), close()
 *  - Simple buffer usage and a safe read/write loop for copying
 *
 * Notes:
 *  - This intentionally avoids stdio buffering (fopen/fread/fwrite)
 *    so you see how the OS API behaves directly.
 *  - Keep this file small and readable; we'll expand later.
 *
 * Build and run:
 *   cd "Personal project ideas/c_projects/expense-tracker-c/file_handling"
 *   gcc -std=c11 -Wall -O2 -o low_level_file_io low_level_file_io.c
 *   ./low_level_file_io
 */

static void explain_fd(void) {
    printf("\n-- File descriptors --\n");
    printf("0=stdin, 1=stdout, 2=stderr. Files you open return 3+.\n");
}

static void example_write(void) {
    printf("\n-- write() example --\n");
    int fd = open("llio_out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open for write failed");
        return;
    }

    const char *line = "Hello from write() syscall!\n";
    ssize_t n = write(fd, line, strlen(line));
    if (n == -1) perror("write failed");
    else printf("Wrote %zd bytes to llio_out.txt (fd=%d)\n", n, fd);

    close(fd);
}



static void example_read(void) {
    printf("\n-- read() example --\n");
    int fd = open("llio_out.txt", O_RDONLY);
    if (fd == -1) {
        perror("open for read failed");
        return;
    }

    char buf[128];
    ssize_t r = read(fd, buf, sizeof(buf) - 1);
    if (r == -1) {
        perror("read failed");
        close(fd);
        return;
    }
    buf[r] = '\0';
    printf("Read %zd bytes:\n%s", r, buf);

    close(fd);
}

static void example_copy(char* src_path, char* dst_path) {
    printf("\n-- copy example (safe loop) --\n");
    int src = open(src_path, O_RDONLY);
    if (src == -1) { perror("open src"); return; }

    int dst = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst == -1) { perror("open dst"); close(src); return; }

    char buf[4096]; /* good default buffer size (1024 bytes - 1 kb, 4kb) */ 

    // char buf[3];
    // _ , _, _, \0
    //             
    while (1) {
        ssize_t nr = read(src, buf, sizeof(buf));
        printf("Read %zd bytes\n", nr);
        if (nr == 0) break; /* EOF */
        if (nr == -1) { perror("read"); break; }

        /* handle partial writes in a loop */
        ssize_t to_write = nr;
        char *p = buf;
        while (to_write > 0) {
            ssize_t actually_to_write = to_write > 1024 ? 1024 : to_write; /* write in chunks if needed */
            ssize_t nw = write(dst, p, actually_to_write);
            if (nw == -1) { perror("write"); close(src); close(dst); return; }
            printf("Wrote %zd bytes\n", nw);
            to_write -= nw;
            p += nw;
        }
    }

    printf("Created a copy of %s at %s\n", src_path, dst_path);
    close(src);
    close(dst);
}

int main(void) {
    printf("Low-level file I/O tutorial (compact)\n");
    //explain_fd();
    //example_write();
    //example_read();
    example_copy("development.md", "development_copy.md");
    //printf("\nDone — inspect llio_out.txt and llio_copy.txt\n");
    return 0;
}
