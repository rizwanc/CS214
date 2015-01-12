/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *sepChar;
	char *tokStream;
	char *token;
	int sepLoc;
	int index;
	int backslashCounter;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
	
	//allcocate memory for struct temp
	TokenizerT *temp = malloc(sizeof(struct TokenizerT_));

	//allocate memory for sepChar member variable of struct temp
        temp->sepChar = (char*)malloc(sizeof(char) * (strlen(separators) + 1));

	//allocate memory for tokStrem member variable of struct temp
	temp->tokStream = (char*)malloc(sizeof(char) * (strlen(ts) + 1));

	//array to hold indicidual tokens
	temp->token = (char*)malloc(sizeof(char) * (strlen(ts) + 1));

       
	temp->index = 0; //variable to hold the position of the beginning of the string
	temp->sepLoc = -1; //variable to hole the location of separators
	
	
	strcpy(temp->sepChar, separators); //copy the contents of seprators to sepChar 
	strcpy(temp->tokStream, ts); //copy the contents of ts to tokStream
	
  return temp; //return struct 
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
	free(tk->sepChar); //free memory for the sepChar member variable
	free(tk->tokStream); //free memory for the tokStram member variable
	free(tk->token); //free memory of token holder
	free(tk); //free memory for the struct
}

//Find the separators in the string and note down their locations
void findSeperators(TokenizerT *tk) {

	int i = 0; //loop variable
	int j = 0; //loop vaiable
	char char1; //variable to hold string chars
	char char2; //variable to hold separator chars
	int found = 0; //variable to indicate if we found a token

	//set i equal to the index i.e. beginning of the string but leave index alone so it continues to point to the beginning of the string
	i = tk->index;

	while(tk->tokStream[i] != '\0') {		
	    while(tk->sepChar[j] != '\0') {
		char1 = tk->tokStream[i];
		char2 = tk->sepChar[j];

		//if we have found a delimeter
		if(char1 == char2) {

		   //if we have a delimeter at the beginning of the string
		    if(i == tk->index) {
		       tk->index = tk->index + 1;
 		       break;
		     }

		    tk->sepLoc = i; //set the location of the string
		    found++; //set the found variable to indicate we found a separator
                    break;
		} else {
		    j++;
		}
             }
		//break out of the outer loop if we found a separator otherwise continue looping through the string
	        if(found == 1) {
		    break;
		} else {
		  i++;
		  j = 0;
		  tk->sepLoc = 0;
		}
         }
	
	//if we never found a separator then the whole string is a token
	if(found == 0) {
	   tk->sepLoc = strlen(tk->tokStream);
	}

	//no more delims
	if(tk->index > strlen(tk->tokStream)) {
	   tk->sepLoc = -2;
	}
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

    if (tk->tokStream == NULL) {
	return NULL;
    }

    findSeperators(tk);

    //if the index is equal to the separator location then we have multipler separtors next to each other so we increment the index
    if(tk->index == tk->sepLoc) {
   	tk->index = tk->sepLoc+1;
	//printf("index: %d\n", tk->index);
	findSeperators(tk);
    }

    //if no longer have delims return
    if(tk->sepLoc == -2) {
	return 0;
    }

    int startIndex = tk->index; //start position of the string

    //printf("Indexes: %d\n", startIndex);
    
    int endIndex = tk->sepLoc; //en position of the string
    
    char *temp = (char*)malloc((endIndex-startIndex)+1); //var to hold our token

    int i = 0;
 
   //copy the token to temp
   while(startIndex < endIndex) {
		
	       //replace special characters with hex
		if(tk->tokStream[startIndex] == '\\') {
		      if(tk->tokStream[startIndex+1] == 'n') {

		     if(sizeof(tk->tokStream) > 3) {
			if(tk->tokStream[startIndex +2] == '\0'){
			    break;
			}
		     }
			
			temp = (char*)realloc(temp, sizeof(temp)+7);
			
				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = 'a';
				temp[i+5] = ']';
			i+= 6;
			startIndex += 2;
				

			} else if(tk->tokStream[startIndex+1] == 't') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);
		
				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = '9';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == 'v') {
				
			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }

			temp = (char*)realloc(temp, sizeof(temp)+7);
			
				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = 'b';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == 'r') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = 'd';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == 'f') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = 'c';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == 'a') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = '7';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == '\\') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '5';
				temp[i+4] = 'c';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == '\"') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }
				
			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '2';
				temp[i+4] = '2';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
				
			} else if(tk->tokStream[startIndex+1] == 'b') {

			if(sizeof(tk->tokStream) > 3) {
			    if(tk->tokStream[startIndex +2] == '\0'){
			    	break;
			    }
		        }

			temp = (char*)realloc(temp, sizeof(temp)+7);

				temp[i] = '[';
				temp[i+1] = '0';
				temp[i+2] = 'x';
				temp[i+3] = '0';
				temp[i+4] = '8';
				temp[i+5] = ']';

			i+= 6;
			startIndex += 2;
			} else {
			 startIndex++;					
			}
		}

	if(tk->tokStream[startIndex] == '\\') {
		continue;
	}	
	
	if(tk->tokStream[startIndex] == '\0') {
		break;	
	}

	temp[i] = tk->tokStream[startIndex];

	i++;
	startIndex++;
   }

   temp[i] = '\0';

   //copy the temp variable to the token variable
   strcpy(tk->token, temp);
   
   tk->index = tk->sepLoc + 1; //set the position of the index to poin to the next character in the string
   tk->sepLoc = tk->index; //set the locatiion of the separator var to the index position

   free(temp);
 
  return tk->token; //return the token
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

	//If the user has not entered the correct input
	//print an error message and return
	if (argc != 3){
	  printf("Invalid input.  Input must consist of two arguments\n");
	  return 1;
	}

	char *sepChar = argv[1]; //variable to hold seperator chars
	char *string = argv[2]; //variable to hold the string 
	char *printToken; //variable to hold the tokens to be printed

	//call the function TKCreate
	TokenizerT *tokens = TKCreate(sepChar, string);

	//While there are still tokens continue calling the function
	//TKGetNextToken and print the tokens to the console
	while ((printToken = TKGetNextToken(tokens)) != NULL) {
	     printf("%s\n", printToken);
	}

	//Free all memory allocated for structs and variable
	TKDestroy(tokens);

  return 0;
}
