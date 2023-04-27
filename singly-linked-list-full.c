/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
		printf("                 [----- [������] [2019068057] -----]             \n");
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //��� ���� �� �޸� ���� �Ҵ�
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //�ƹ� ��嵵 �������� �ʾ��� ���, headnode�� ����Ű�� ù��° ��带 �� ���� ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;  //ù��° ������ ����� n
	listNode* trail = h->first;  //���� ��带 ����Ű�� trail

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {  //������ ��尡 �Ǳ� ������
		if(n->key >= key) {  //���� �Է��� key�� �� ����� key������ �۰ų� ���� ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {  //���� �� ��尡 ù��° ����� ���
				h->first = node;  //�� ��带 ù��° ���� �ϰ�
				node->link = n;  //����� link�� �� ��� ���� ���� ����Ű�� �Ѵ�
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n;  //����� ��ũ�� �� ��带 ����Ű�� �Ѵ�
				trail->link = node;  //���� ����� ��ũ�� �� ��带 ����Ű�� �Ѵ�
			}
			return 0;
		}

		trail = n;  //���� ��带 �� ���� �ϰ�
		n = n->link; //���� ���� �̵�
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node;  //���� ����� link�� �� ��带 ����Ű�� �Ѵ�
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //��� ���� �� ���� �޸� �Ҵ�
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //��忡 �ƹ��͵� �����ٸ� ù��° ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;  //ù��° ������

	while(n->link != NULL) {  //����� link�� ����Ű�� ���� ������ ������ (������ ������)
		n = n->link;  //���� ���� �̵�
	}
	n->link = node;  //������ ��尡 �Ǹ� �� ����� link�� ������ ��带 ����Ű�� ����
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //��� ���� �� ���� �޸� �Ҵ�
	node->key = key;

	node->link = h->first;  //����� link�� ù��° ���� ����
	h->first = node;  //ù��° ��带 ������ ���� ����

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)  //���� ��尡 ���ٸ� ���� �޽����� �Բ� �Լ� ����
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {  //����� key�� ������� key�� ���� ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {  //���� �� ��尡 ù��° ��忴�ٸ�
				h->first = n->link;  //�� ��尡 ����Ű�� ���� ��带 ù��° ���� ����
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;  //���� ����� ��ũ�� �� ��尡 ����Ű�� ���� ���� ����
			}
			free(n);  //�� ��忡 �Ҵ�Ǿ��� �޸� ��ȯ
			return 0;
		}

		trail = n;  //���� ��带 �� ����
		n = n->link;  //���� ���� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)  //��尡 �ƹ��͵� ������ �����޽����� �Բ� �Լ� ����
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {  //�� ��尡 ����Ű�� ���� ��尡 ���� ���
		h->first = NULL;  //ù��° ��尡 ���ٰ� ������ ��
		free(n);  //�� ��� �޸� ��ȯ
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {  //����� link�� ����Ű�� ���� ���� ������
		trail = n;  //���� ��带 �� ���� �ϰ�
		n = n->link;  //���� ���� �̵�
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL;  //���� ����� link�� ����Ű�� ���� ���� ������ ��
	free(n);  //�� ����� �޸� ��ȯ

	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)  //��尡 �ƹ��͵� �������� ���� �޽����� �Բ� �Լ� ����
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;  //ù��° ��带 �� ��尡 ����Ű�� ���� ���� ����
	free(n);  //�� ��� �޸� ��ȯ

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) {  //��尡 �ƹ��͵� ���� ��, ���� �޽����� �Բ� �Լ� ����
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;  //���� ���
	listNode *middle = NULL;  //�߰� ���

	while(n != NULL){  //��尡 �������� ������
		trail = middle;  //���� ��带 �߰� ����, �߰� ��带 �� ���� �����ϰ�
		middle = n;
		n = n->link;  //���� ���� �̵�
		middle->link = trail;  //�߰� ����� link�� ���� ��尡 ����Ű�� ����
	}

	h->first = middle;  //�߰� ��带 ù��° ���� �ϰԲ�

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

