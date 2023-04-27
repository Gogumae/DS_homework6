/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                 [----- [이찬희] [2019068057] -----]             \n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //노드 선언 및 메모리 동적 할당
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //아무 노드도 존재하지 않았을 경우, headnode가 가리키는 첫번째 노드를 이 노드로 설정
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;  //첫번째 노드부터 출발할 n
	listNode* trail = h->first;  //이전 노드를 가리키는 trail

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {  //마지막 노드가 되기 전까지
		if(n->key >= key) {  //만약 입력한 key가 앞 노드의 key값보다 작거나 같을 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {  //만약 앞 노드가 첫번째 노드일 경우
				h->first = node;  //이 노드를 첫번째 노드로 하고
				node->link = n;  //노드의 link를 앞 노드 였던 것을 가리키게 한다
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;  //노드의 링크를 앞 노드를 가리키게 한다
				trail->link = node;  //이전 노드의 링크가 이 노드를 가리키게 한다
			}
			return 0;
		}

		trail = n;  //이전 노드를 이 노드로 하고
		n = n->link; //다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;  //이전 노드의 link가 이 노드를 가리키게 한다
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //노드 선언 및 동적 메모리 할당
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //노드에 아무것도 없었다면 첫번째 노드로
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;  //첫번째 노드부터

	while(n->link != NULL) {  //노드의 link가 가리키는 것이 없어질 때까지 (마지막 노드까지)
		n = n->link;  //다음 노드로 이동
	}
	n->link = node;  //마지막 노드가 되면 그 노드의 link가 삽입할 노드를 가리키게 설정
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //노드 선언 및 동적 메모리 할당
	node->key = key;

	node->link = h->first;  //노드의 link를 첫번째 노드로 설정
	h->first = node;  //첫번째 노드를 삽입할 노드로 설정

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)  //만약 노드가 없다면 오류 메시지와 함께 함수 종료
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {  //노드의 key가 지우려는 key와 같을 경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {  //만약 이 노드가 첫번째 노드였다면
				h->first = n->link;  //이 노드가 가리키던 다음 노드를 첫번째 노드로 설정
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;  //이전 노드의 링크를 이 노드가 가리키던 다음 노드로 설정
			}
			free(n);  //이 노드에 할당되었던 메모리 반환
			return 0;
		}

		trail = n;  //이전 노드를 이 노드로
		n = n->link;  //다음 노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)  //노드가 아무것도 없으면 오류메시지와 함께 함수 종료
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {  //이 노드가 가리키는 다음 노드가 없을 경우
		h->first = NULL;  //첫번째 노드가 없다고 설정한 후
		free(n);  //이 노드 메모리 반환
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {  //노드의 link가 가리키는 곳이 없을 때까지
		trail = n;  //이전 노드를 이 노드로 하고
		n = n->link;  //다음 노드로 이동
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;  //이전 노드의 link가 가리키는 것이 없게 설정한 후
	free(n);  //이 노드의 메모리 반환

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)  //노드가 아무것도 없었으면 오류 메시지와 함께 함수 종료
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;  //첫번째 노드를 이 노드가 가리키던 다음 노드로 설정
	free(n);  //이 노드 메모리 반환

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {  //노드가 아무것도 없을 시, 오류 메시지와 함께 함수 종료
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;  //이전 노드
	listNode *middle = NULL;  //중간 노드

	while(n != NULL){  //노드가 없어지기 전까지
		trail = middle;  //이전 노드를 중간 노드로, 중간 노드를 이 노드로 설정하고
		middle = n;
		n = n->link;  //다음 노드로 이동
		middle->link = trail;  //중간 노드의 link를 이전 노드가 가리키게 설정
	}

	h->first = middle;  //중간 노드를 첫번째 노드로 하게끔

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

