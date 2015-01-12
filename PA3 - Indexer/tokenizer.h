
struct TokenizerT_ {
	char* copied_string;		
	char* current_position;
};

typedef struct TokenizerT_ TokenizerT;


char *unescape_string(char *);
char is_delimeter(char);
char is_escape_character(char);
int char_to_hex(char);
int char_to_oct(char);

TokenizerT *TKCreate(char*);
char *TKGetNextToken(TokenizerT *);
void TKDestory(TokenizerT *);

