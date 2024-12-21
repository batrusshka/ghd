#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "lab2.h"

#define MAX_LINE_LENGTH 1024

void replace_text(FILE *file, const char *old_text, const char *new_text) {
    char buffer[MAX_LINE_LENGTH];
    FILE *temp_file = fopen("temp.txt", "w");

    if (temp_file == NULL) {
        fprintf(stderr, "Не удалось открыть временный файл для записи.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        char *pos;
        while ((pos = strstr(buffer, old_text)) != NULL) {
            *pos = '\0';
            fprintf(temp_file, "%s%s%s", buffer, new_text, pos + strlen(old_text));
            strcpy(buffer, pos + strlen(old_text));
        }
        fprintf(temp_file, "%s", buffer);
    }

    fclose(temp_file);
    fclose(file);
    remove("input.txt");
    rename("temp.txt", "input.txt");
}

void delete_lines(FILE *file, const char *pattern) {
    char buffer[MAX_LINE_LENGTH];
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Ошибка компиляции регулярного выражения.\n");
        exit(EXIT_FAILURE);
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        fprintf(stderr, "Не удалось открыть временный файл для записи.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
            fprintf(temp_file, "%s", buffer);
        }
    }

    fclose(temp_file);
    fclose(file);
    regfree(&regex);
    remove("input.txt");
    rename("temp.txt", "input.txt");
}

void insert_text(FILE *file, const char *insert_text, int at_start) {
    char buffer[MAX_LINE_LENGTH];
    FILE *temp_file = fopen("temp.txt", "w");

    if (temp_file == NULL) {
        fprintf(stderr, "Не удалось открыть временный файл для записи.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        if (at_start) {
            fprintf(temp_file, "%s%s", insert_text, buffer);
        } else {
            fprintf(temp_file, "%s%s", buffer, insert_text);
        }
    }

    fclose(temp_file);
    fclose(file);
    remove("input.txt");
    rename("temp.txt", "input.txt");
}