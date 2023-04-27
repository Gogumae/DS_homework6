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
} headNode;


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
		printf("               [----- [이찬희] [2019068057] -----]               \n");
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



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;  //우선 링크 연결 안함

	listNode* n = h->first;  //headnode가 가리키는 첫번째 노드 n
	listNode* trail = h->first;  //headnode가 가리키는 노드를 trail로

	while(n != NULL) {  //앞 노드가 없지 않으면
		if(n->key >= key) {  //앞 노드의 key가 새로운 key보다 높거나 같을 경우
			if(n == h->first) {  //앞 노드가 첫번째 노드였을 경우
				h->first = node;  //삽입하려는 이 노드를 첫번째 노드로 설정
				node->link = n;  //노드의 link로 원래 처음 노드였던 n을 가리키게 설정
			}
			else {
				node->link = n;  //node의 link가 앞 노드을 가리키게끔 수정
				trail->link = node;  //headnode의 link가 가리키는 노드를 이 노드로
			}
			return 0;
		}
		trail = n;  //첫번째 노드가 없으면 trail과 n을 같게 한다
		n = n->link;  //첫번째 노드..
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;  //마지막 노드이기에 link NULL

	if(h->first == NULL) {  //만약 첫번째 노드가 없는 상태라면 이 노드를 첫번째 노드로 하고 함수 종료
		h->first = node;
		return 0;
	}

	listNode* n = h->first;  //첫번째 노드 n
	while(n->link != NULL) {  //첫번째 노드부터 마지막 노드까지 link를 타고 이동
		n = n->link;
	}
	n->link = node; //마지막 노드의 link로 node를 가리키게 설정
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;

	h->first = n->link;
	free(n);


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if(h->first == NULL) {  //첫번째 노드가 없으면 함수 종료
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {  //앞 노드가 없지 않으면
		if(n->key == key) {  //앞 노드의 키와 입력된 키가 같을 경우
			if(n == h->first) {  //앞 노드가 첫번째 노드였을 경우
				h->first = n->link;  //headnode가 가리키는 첫번째 노드를 앞 노드가 가리키던 노드로
			}
			else {
				trail->link = n->link;  //trail가 가리키는 노드를 앞 노드가 가리키던 노드로
			}
			free(n);  //노드 n에 할당된 메모리 반환
			return 0;
		}
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	trail->link = NULL;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;
	listNode* middle = NULL;

	while(n != NULL) {
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

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

