//Siyuan Zhou
#include "list.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BETWEEN(c, start, end) ((c)>=(start)&&(c)<=(end))
//minor count of word
#define MIN_COUNT(node) ((node)->count[0]>(node)->count[1]?(node)->count[1]:(node)->count[0])
//compare two nodes
#define CMP_NODE(node1, node2) (MIN_COUNT(node1)-MIN_COUNT(node2))
//
#define IsWordCharType(c) (BETWEEN(c, 'a','z')||\
	BETWEEN(c, 'A','Z')||\
	BETWEEN(c, '0','9')||\
	BETWEEN(c, '\'', '\'')||\
	BETWEEN(c, '-', '-')\
	)

#define TO_LOWER(c) (BETWEEN(c, 'A','Z')?(c+32):(c))
//make a string to lowercase
static void strToLower(char*str){
	while(*str){
		*str=TO_LOWER(*str);
		++str;
	}
}
//find the node in the list
static ListNode*findNode(List list, const char*word){
	while(list!=NULL&&strcmp(word, list->word)){
		list=list->next;
	}
	return list;
}
static ListNode*CreateNode(const char*word){
	ListNode*tmpNode;
	tmpNode=(ListNode*)malloc(sizeof(ListNode));
	assert(tmpNode);
	strcpy(tmpNode->word, word);
	tmpNode->count[0]=tmpNode->count[1]=0;
	tmpNode->next=NULL;
	return tmpNode;
}



//read file and count the number of words, then insert into list
List ReadFile(List list, const char*fileName, int fileTh){
	FILE*pf;
	char str[1024];
	char*start, *end;
	char c;
	ListNode*tmpNode;
	if(NULL==(pf=fopen(fileName, "r")))
		return list;
	while(fscanf(pf, "%s", str)>0){
		//printf("%s\n",str);
		start=str;
		do 
		{
			//find first char which is legal  type
			while(*start&&!IsWordCharType(*start))
				++start;
			//end
			if(!*start)
				break;
			end=start+1;
			//get to the end of this word
			while(*end&&IsWordCharType(*end))
				++end;
			assert(end<start+WORD_LEN);
			c=*end;
			*end=0;
			strToLower(start);
			assert(BETWEEN(fileTh, 0,1));
			//find this word in the list,then add the count
			if(NULL!=(tmpNode=findNode(list, start))){
				++tmpNode->count[fileTh];
			}else{//new word,then create new list node
				tmpNode=CreateNode(start);
				tmpNode->count[fileTh]=1;
				if(list==NULL)
					list=tmpNode;
				else{
					tmpNode->next=list->next;
					list->next=tmpNode;
				}
			}
			start=end+1;
		} while (c);
	}
	fclose(pf);
	return list;
}

//sort the list in decreasing number
List SortInDec(List list){
	ListNode*prev, *cur,*next;
	int flag=1;//record if switch two nodes
	int num=0, k;
	prev=cur=next=NULL;
	cur=list;
	while(cur){
		++num;
		cur=cur->next;
	}
	//bubble sort
	while(flag&&--num){
		flag=0;
		cur=list;
		prev=NULL;
		k=num;
		while(k--){
			next=cur->next;
			//if cur<next, then exchange this two nodes
			if(next&&CMP_NODE(cur, next)<0){
				cur->next=next->next;
				next->next=cur;
				if(prev){
					prev->next=next;
				}else//head is changed
					list=next;
				flag=1;
				prev=next;
			}else{
				prev=cur;
				cur=next;
			}
		}
	}
	return list;
}

//free resource of list
void DestroyList(List list){
	List tmp;
	do 
	{
		if(list==NULL)
			break;
		tmp=list;
		list=list->next;
		free(tmp);
	} while (1);
}



