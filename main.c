//Siyuan Zhou

#include "list.h"
#include <stdio.h>

void PrintList(List list, int printNum);

int main(int argc, char* argv[])
{
	//1 make up single linked list
	//2 sort by miner number in dec
	//3 print the first 50 words
	List list=NULL;
	//read first file
	list=ReadFile(list, "RedBadge.txt", 0);
	printf("finish read file: RedBadge.txt\n");
	//second file
	list=ReadFile(list, "LittleRegiment.txt", 1);
	printf("finish read file: LittleRegiment.txt\n");
	//sort the list
	list=SortInDec(list);
	//print first 50
	printf("first 50 words: \n");
	PrintList(list, 50);
	//destroy
	DestroyList(list);
	
	return 0;
}

void PrintList(List list, int printNum){
	while(list&&printNum--){
		printf("%-20s\t%4d\t%4d\n", list->word, list->count[0], list->count[1]);
		list=list->next;
	}
}

    

