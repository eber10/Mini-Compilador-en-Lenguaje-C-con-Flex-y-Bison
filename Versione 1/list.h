#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct symT {
	const char* id;
	int value;
	UT_hash_handle hh;	
} symT;


void addVar (char *id, symT **table) {
	symT *tmp;
	HASH_FIND_STR(*table, id, tmp);
	if (tmp == NULL) {
		tmp = (symT*) malloc(sizeof(symT));
		tmp->id = id;
		tmp->value = 0;
		HASH_ADD_KEYPTR(hh, *table, tmp->id, strlen(tmp->id), tmp);
	} else {
		printf("ERROR: multiple definition for variable %s\n", id);
		exit(-1);
	}
}

int setVar (char *id, int value, symT **table) {
	symT *tmp;
	HASH_FIND_STR(*table, id, tmp);
	if(tmp==NULL) {
		return 0;
	}
	tmp->value = value;
	return 1;
}

int getVar(char *id, symT **table, int *val) {
	symT *tmp;
	HASH_FIND_STR(*table, id, tmp);
	if(tmp==NULL) {
		return 0;
	}
	*val = tmp->value;
	return 1;
}

struct SNode {
	symT* table;
	struct SNode* next;	
};

typedef struct SNode TNode;
typedef TNode *TList;

TNode* createNode() {
	TNode *new = (TNode*) malloc(sizeof(TNode));
	if(new == NULL) {
		printf("Memory error\n");
		exit(-1);
	}
	new->table = NULL;
	new->next = NULL;
	return new;
}

void destroyNode(TNode* node) {
	free(node);
}


TList insertElement(TList list) {
	TNode *new = createNode();
	new->next = list;
	return new;
}

TList removeElement(TList list) {
	TList updateList = list->next;
	destroyNode(list);
	return updateList;
}

void setVarList(char* id, int val, TList list){
	if(setVar(id, val, &list->table) == 0) {
		TList i = list->next;
		while(i != NULL && setVar(id, val, &i->table) == 0)
			i = i->next;
		if(i == NULL) {
			printf("Error: variable not defined\n");
			exit(-1);
		}
	}
}

int getVarList(char* id, TList list) {
	int val;
	if(getVar(id, &list->table, &val) == 0) {
		TList i = list->next;
		while (i != NULL && getVar(id, &i->table, &val) == 0)
			i = i->next;
		if(i == NULL) {
			printf("Error: variable not defined\n");
			exit(-1);
		} else
			return val;
	} else
		return val;
}