//Siyuan ZHou
#ifndef LIST_H_
#define LIST_H_

#define WORD_LEN 32

struct _ListNode;
typedef struct _ListNode{
	char word[WORD_LEN];
	int count[2];//count in file1,file2
	struct _ListNode*next;
}ListNode;

typedef ListNode* List;

////create an empty list
//List CreateList(void);

//read file and count the number of words, then insert into list
List ReadFile(List list, const char*fileName, int fileTh);

//sort the list in decreasing number
List SortInDec(List list);

//free resource of list
void DestroyList(List list);
#endif
