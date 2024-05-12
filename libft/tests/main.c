#include "../includes/ft_string_utils.h"
#include <stdio.h>
#include <string.h>

int main() {
	/*
    char str[] = "1234";
	char str2[] = "1234";
    const char delim[] = ""; // Delimiters: space, comma, period, exclamation mark

	char *save1;
	char *save2;
    // Get the first token
    char *token = ft_strtok_r(str2, delim, &save1);
	char *bench = strtok_r(str, delim, &save2);

    while (token != NULL) {
        printf("[%s]\n", token);
        token = ft_strtok_r(NULL, delim, &save1);
    }

	printf("\n________________________________\n\n");

    while (bench != NULL) {
        printf("[%s]\n", bench);
        bench = strtok_r(NULL, delim, &save2);
	}

    return 0;
	*/

	char test[80], blah[80];
	char *sep = "\\/:;=-";
	char *word, *phrase, *brkt, *brkb;
	
	strcpy(test, "This;is.a:test:of=the/string\\tokenizer-function.");
	
	for (word = strtok_r(test, sep, &brkt);
			word;
			word = strtok_r(NULL, sep, &brkt))
	{
		 strcpy(blah, "blah:blat:blab:blag");
		 
		 for (phrase = strtok_r(blah, sep, &brkb);
				 phrase;
				 phrase = strtok_r(NULL, sep, &brkb))
		 {
			 printf("So far we're at %s:%s\n", word, phrase);
		 }
	}

	printf("\n________________________________\n\n");

	char test1[80], blah1[80];
	char *sep1 = "\\/:;=-";
	char *word1, *phrase1, *brkt1, *brkb1;

	strcpy(test1, "This;is.a:test:of=the/string\\tokenizer-function.");

	for (word1 = ft_strtok_r(test1, sep1, &brkt1);
			word1;
			word1 = strtok_r(NULL, sep1, &brkt1))
	{
		 strcpy(blah1, "blah:blat:blab:blag");

		 for (phrase1 = ft_strtok_r(blah1, sep1, &brkb1);
				 phrase1;
				 phrase1 = strtok_r(NULL, sep1, &brkb1))
		 {
			 printf("So far we're at %s:%s\n", word1, phrase1);
		 }
	}

}
