#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab2.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s input.txt -r 'old text' 'new text'\n", argv[0]);
        fprintf(stderr, "или: %s input.txt -d 'text to delete'\n", argv[0]);
        fprintf(stderr, "или: %s input.txt -i -f 'insert text front'\n", argv[0]);
        fprintf(stderr, "или: %s input.txt -i -b 'insert text back'\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[2], "-r") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Неправильное количество аргументов для замены.\n");
            return EXIT_FAILURE;
        }
        replace_text(file, argv[3], argv[4]);
    } else if (strcmp(argv[2], "-d") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Неправильное количество аргументов для удаления.\n");
            return EXIT_FAILURE;
        }
        delete_lines(file, argv[3]);
    } else if (strcmp(argv[2], "-i") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Неправильное количество аргументов для вставки.\n");
            return EXIT_FAILURE;
        }
        if (strcmp(argv[3], "-f") == 0) {
            insert_text(file, argv[4], 1);
        } else if (strcmp(argv[3], "-b") == 0) {
            insert_text(file, argv[4], 0);
        } else {
            fprintf(stderr, "Неизвестная операция вставки.\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Неизвестная операция.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}