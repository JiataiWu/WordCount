#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Function prototypes
int count_characters(const char *filename);
int count_words(const char *filename);

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] <input_file_name>\n", argv[0]);
        return 1;
    }

    // Determine the mode: count characters or words
    if (strcmp(argv[1], "-c") == 0) {
        int char_count = count_characters(argv[2]);
        if (char_count == -1) {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
        printf("字符数：%d\n", char_count);
    } else if (strcmp(argv[1], "-w") == 0) {
        int word_count = count_words(argv[2]);
        if (word_count == -1) {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
        printf("单词数：%d\n", word_count);
    } else {
        fprintf(stderr, "Invalid parameter. Use -c to count characters or -w to count words.\n");
        return 1;
    }

    return 0;
}

int count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int char_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        char_count++;
    }

    fclose(file);
    return char_count;
}

int count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int word_count = 0;
    int in_word = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') {
            if (in_word) {
                in_word = 0;
                word_count++;
            }
        } else {
            in_word = 1;
        }
    }

    // Count the last word if the file does not end with a space or a comma
    if (in_word) {
        word_count++;
    }

    fclose(file);
    return word_count;
}
