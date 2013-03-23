#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define maxlen 1000
#define randmax_move 15

long long next_sym[26][26];
long long sums[26];

int read_stat (char * stat_file) {
    FILE *F;
    int i, j;
    if ((F = fopen (stat_file, "rt")) == NULL) {
        return 1;
    }
    for (i = 0; i < 26; ++i) {
        for (j = 0; j < 26; ++j) {
            fscanf (F, " %lli ", &next_sym[i][j]);
            sums[i] += next_sym[i][j];
        }
        if (sums[i] == 0) {
            fprintf (stderr, "Text is too small, I think.\n");
            exit (EXIT_FAILURE);
        }
    }
    fclose (F);
    return 0;
}

long long llrand () {
    long long r = rand();
    r <<= randmax_move;
    r += rand();
    r <<= randmax_move;
    r += rand();
    return r;
}

int main (int argc, char* argv[]) {
    int length, i, j;
    char password[maxlen];
    srand (time (NULL));
    if (argc < 2) {
        fprintf (stderr, "Statistics file not mentioned. Nothing to do...\n");
        exit (EXIT_FAILURE);
    }
    if (read_stat (argv[1])) {
        fprintf (stderr, "Troubles with reading statistics file. Exiting\n");
        exit (EXIT_FAILURE);
    }
    fprintf (stderr, "Type length of password:\n");
    scanf ("%i", &length);
    while (length < 1 || length > maxlen) {
        fprintf (stderr, "Length must be positive and not greater than %i.\n", maxlen);
        scanf ("%i", &length);
    }
    password[0] = 'a' + rand() % 26;
    for (i = 1; i < length; ++i) {
        char prev = password[i - 1];
        long long rnd;
        rnd = llrand() % sums[prev-'a'];
        for (j = 0; j < 26; ++j)
            if (rnd < next_sym[prev - 'a'][j]) {
                password[i] = 'a' + j;
                break;
            }
            else
                rnd -= next_sym[prev - 'a'][j];            
    }
    password[length] = 0;
    fprintf (stderr, "Your password: ");
    printf ("%s\n", password);
    return 0;
}
