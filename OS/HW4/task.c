#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regex text replacement\n", argv[0]);
        return 1;
    }

    char *pattern = argv[1];
    char *text = argv[2];
    char *replacement = argv[3];

    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Invalid regular expression\n");
        return 1;
    }

    size_t buf_size = 128;
    char *result = malloc(buf_size);
    if (!result) {
        perror("malloc");
        regfree(&regex);
        return 1;
    }
    size_t result_len = 0;
    result[0] = '\0';

    size_t search_start = 0;
    size_t text_len = strlen(text);
    regmatch_t match;
    int nomatch = regexec(&regex, text + search_start, 1, &match, 0);

    while (nomatch == 0) {
        size_t prefix_len = match.rm_so;

        if (prefix_len > 0) {
            while (result_len + prefix_len + 1 > buf_size) {
                buf_size *= 2;
                result = realloc(result, buf_size);
                if (!result) {
                    perror("realloc");
                    regfree(&regex);
                    return 1;
                }
            }
            memcpy(result + result_len, text + search_start, prefix_len);
            result_len += prefix_len;
            result[result_len] = '\0';
        }

        size_t repl_len = strlen(replacement);
        if (repl_len > 0) {
            while (result_len + repl_len + 1 > buf_size) {
                buf_size *= 2;
                result = realloc(result, buf_size);
                if (!result) {
                    perror("realloc");
                    regfree(&regex);
                    return 1;
                }
            }
            memcpy(result + result_len, replacement, repl_len);
            result_len += repl_len;
            result[result_len] = '\0';
        }

        search_start += match.rm_eo;
        if (search_start >= text_len) break;
        nomatch = regexec(&regex, text + search_start, 1, &match, REG_NOTBOL);
    }

    size_t remaining = text_len - search_start;
    if (remaining > 0) {
        while (result_len + remaining + 1 > buf_size) {
            buf_size *= 2;
            result = realloc(result, buf_size);
            if (!result) {
                perror("realloc");
                regfree(&regex);
                return 1;
            }
        }
        memcpy(result + result_len, text + search_start, remaining);
        result_len += remaining;
        result[result_len] = '\0';
    }

    printf("%s\n", result);

    free(result);
    regfree(&regex);
    return 0;
}