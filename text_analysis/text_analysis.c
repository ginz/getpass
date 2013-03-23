#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int little_letter (char sym) {
    return 'a' <= sym && sym <= 'z';
}

int main (int argc, char* argv[]) {
    long long next_letter[26][26];
    long long length = 0;
    int i, j;
    if (argc == 1) {
        fprintf (stderr, "Usage: %s <file1 to analyse> [<file2 to analyse> ...]\n", argv[0]);
        exit (EXIT_SUCCESS);
    }
    else if (argc > 1) {
        memset (next_letter, 0, sizeof (next_letter));
        for (i = 1; i < argc; ++i) {
            FILE *F;
            char sym, prev_sym = 0;
            fprintf (stderr, "Processing file \"%s\": ...\n", argv[i]);
            if ((F = fopen (argv[i], "rt")) == NULL) {
                fprintf (stderr, "Error %i occured while file was opening\n", errno);
                continue;
            }
            while ((sym = fgetc(F)) != EOF) {
                if ('A' <= sym && sym <= 'Z')
                    sym -= 'A' - 'a';
                if (little_letter (prev_sym) && little_letter (sym)) {
                    ++next_letter[prev_sym-'a'][sym-'a'];
                    ++length;
                }
                prev_sym = sym;
            }
            fclose (F);
        }
    }

    for (i = 0; i < 26; ++i) {
        for (j = 0; j < 26; ++j)
            printf ("%lli ", next_letter[i][j]);
        printf ("\n");
    }
    return 0;
}
