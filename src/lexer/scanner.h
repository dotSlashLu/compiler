#ifndef DS_SCANNER_H
#define DS_SCANNER_H

#define MAX_ID_LEN 128

enum tok_types {
        tok_true = 256,
        tok_false,
        tok_num,
        tok_id
};

typedef struct Token {
        int type;     // aka Tag
        void *data;
} tok_t, *tokp;

tokp scan(FILE *in);
void tok_free(tokp);

#endif
