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

