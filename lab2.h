#ifndef lab2
#define lab2

#include <stdio.h>

void replace_text(FILE *file, const char *old_text, const char *new_text);
void delete_lines(FILE *file, const char *pattern);
void insert_text(FILE *file, const char *insert_text, int at_start);

#endif // SED_SIMPLIFIED_H