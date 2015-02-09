#ifndef DS_SCANNER_H
#define DS_SCANNER_H

#define MAX_ID_LEN 128

enum tok_types {
        tok_true = 256,
        tok_false,
        tok_num,
        tok_id,

        tok_type_int = 260,
        tok_type_float,
        tok_type_double,
        tok_type_char
};

typedef struct Token {
        int type;     // aka Tag
        void *data;
} tok_t, *tokp;

tokp scan(FILE *in);
void tok_free(tokp);

#endif
