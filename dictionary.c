#include <stdio.h>
#include <string.h>
#include "dictionary.h"

/*
 * Form hash value for string s
 * This produces a starting value in the dictionary array
 */
unsigned Hash(const char* s)
{
	unsigned hashVal;

	for (hashVal = 0; *s != '\0'; ++s) {
		hashVal = *s + (31 * hashVal);
	}

	return hashVal;
}

DNode* LookUp(DNode** dictionary, int hashSize, const char* key)
{
	DNode* np;
	unsigned int hashVal = Hash(key);

	for (np = dictionary[hashVal % hashSize]; np != NULL; np = np->next) {
		if (strCmp(key, np->key) == 0) {
			return np;
		}
	}

	return NULL; //not found
}

DNode* Insert(DNode** dictionary, int hashSize, const char* key)
{
    DNode* np;
	unsigned int hashVal;

    if ((np = LookUp(dictionary, hashSize, key)) == NULL ) {
		np = (DNode *)malloc(sizeof (*np));

		if (np == NULL || (np->key = copyStr (key)) == NULL) {
			return NULL;
		}

		hashVal = Hash(key) % hashSize;

		np->next = dictionary[hashVal];
		dictionary[hashVal] = np;
	}

	return np;
}

void FreeDictionary(DNode** dictionary, int hashSize)
{
	int i;

	for (i = 0; i < hashSize; ++i) {
		if (dictionary[i] != NULL) { //if there is an entry at position i
			DNode* head = dictionary[i];
			DNode* current = head;
			while (current != NULL) {
				DNode* temp = current;
				current = current->next;
				free(temp);
			}

			dictionary[i] = NULL;  //BUG fix
		}
	}
}

char* CopyStr(const char* s)
{
	char* p;
	int len = strlen(s);

	p = (char *) malloc(len + 1); // +1 for ?\0
	if (p != NULL) {
		strncpy(p, s, len);
	}

	p[len] = '\0';

	return p;
}
