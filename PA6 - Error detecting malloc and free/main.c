#include "malloc.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char*argv[])
{
  //--Test case one--	
  char *test1 = malloc(10);
  char *test2 = malloc(30);
  free(test1); /* Should free fine */
  free(test2); /* Should free fine */
  
  //--Test case two--
   char *test3 = malloc(30);
  free(test3); /* Should free fine */
  free(test3); /* Should throw error */
  
   //--Test case 3--
   free(0); /* Should throw error */
   char *test4 = malloc(10);
   
   //--Test case 4--
   char *p = (char *)malloc( 100 );
   free( p );
   p = (char *)malloc( 100 );
   free( p );
   
   //--Test case 5--
   char *str = malloc(sizeof(char) *strlen(argv[1]));
   strcpy(str, argv[1]);
   free(str);
   
   //--Test case 6--
int *x = malloc(sizeof(int));
free(x);
char *t = malloc(4);
free(x);


   
   return 0;
}
