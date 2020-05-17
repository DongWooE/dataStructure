#include <stdio.h>
#include <stdlib.h>

typedef struct node {  //트리의 각 노드의 구조체
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);  //전체 트리를 초기화시켜주는 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
/* you may add your own defined functions if necessary */

void free_postorder(Node * ptr);  //후위순회를 사용한 free함수


int main()
{
	printf("=====[2017038069]=====[이동우]=====\n");  //학번과 이름 출력
	char command;
	int key;
	Node* head = NULL;  //헤더노드 초기화
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //커멘드 입력

		switch(command) {  //커멘드 비교 후 해당 함수 호출
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {  //전체 트리를 초기화해주는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)  //헤더노드가 비어있지않다면
		freeBST(*h);  //동적할당해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  //헤더노드가 존재하지않는 다면 동적할당
	(*h)->left = NULL;	/* root */  //루트노드를 가리킬 왼쪽 링크를 초기화
	(*h)->right = *h;  //사용하지않는 오른쪽 링크는 자기자신을 가리키도록 함
	(*h)->key = -9999;  //key값은 의미없는 -9999로 설정
	return 1;
}



void inorderTraversal(Node* ptr)  //전위순회 함수
{
	if(ptr){  //ptr이 null이 아닐 때까지 반복
		inorderTraversal(ptr->left);  //트리에서 가장 왼쪽 자식노드까지 가도록 재귀호출
		printf(" %d ", ptr->key);  //왼쪽 자식노드, 부모 노드, 오른쪽 자식 노드 순으로 출력
		inorderTraversal(ptr -> right);  //왼쪽 자식노드가 null이면 오른쪽 탐색
	}
}

void preorderTraversal(Node* ptr)  //중위순회 함수
{
	if(ptr){  //ptr이 null이 아닐 때까지 반복
		printf(" %d ", ptr->key);  //부모 노드를 먼저 출력
		preorderTraversal(ptr->left);  //왼쪽 자식노드를 재귀호출
		preorderTraversal(ptr->right);  //왼쪽 자식노드가 null이면 오른쪽 자식노드를 재귀호출
	}
}

void postorderTraversal(Node* ptr)  //후위순회 함수
{
	if(ptr){  //ptr이 null이 아닐 때까지 반복
		postorderTraversal(ptr->left);  //트리의 가장 왼쪽 자식노드까지 가도록 재귀호출
		postorderTraversal(ptr->right);  //왼쪽 자식노드가 null이면 오른쪽 자식노드를 재귀호출
		printf(" %d ", ptr -> key);  //자식노드들을 먼저 출력하고 부모노드는 나중에 출력
	}
}


int insert(Node* head, int key)  //트리에 키값을 가진 노드를 넣어주는 함수
{
	Node* temp = (Node*)malloc(sizeof(*temp));  //먼저 구조체형 temp선언 후 key값 입력 후 링크들 null로 세팅
	temp -> key = key;
	temp -> left = NULL;
	temp -> right = NULL;

	Node* lead = head -> left;  //lead가 루트노드를 가리키도록 함
	Node* middle = NULL;  //lead 전 노드를 가리킬 middle 선언 후 null로 세팅
	if(!lead){  //루트노드가 없다면
		head -> left = temp;  //temp를 루트노드로 하고
		return 0;  //리턴
	}
	while(lead){  //lead가 null이 아닐 때까지 반복
		if((lead->key)==key){  //key값이 같은 노드가 나오면 그냥 리턴
			return 0;
		}
		else if((lead->key)>key){  //기존 노드의 key값이 더 크면
			middle = lead;  //middle에 lead값을 넣어주고
			lead = lead -> left;  //lead를 왼쪽 자식노드로
		}
		else{  //기존 노드의 key값이 작으면
			middle = lead;  //middle에 lead값을 넣어주고
			lead = lead -> right;  //lead를 오른쪽 자식노드로
		}
	}  //lead가 자식노드들로 내려가다가 null이 되면
	if((middle->key)>key) middle->left = temp;  //middle의 키값이 key보다 크면 middle의 왼쪽 자식노드에 temp 삽입
	else middle-> right = temp;  //middle의 키값이 key보다 작으면 middle의 오른쪽 자식노드에 temp 삽입
	return 0;
}

int deleteLeafNode(Node* head, int key)  //key값과 일치하는 리프노드를 삭제하는 함수
{
	Node * lead = head -> left;  //lead가 헤드노드를 가리키도록 설정
	Node * middle = NULL;  //lead 전 노드를 가리킬 middle 선언 후 null로 세팅
	while(lead){  //lead가 null이 아닐 때까지 반복
		if((lead-> key)>key){  //lead의 key값이 key보다 크면 lead가 왼쪽 자식 노드로 가도록 세팅
			middle = lead;
			lead = lead -> left;}
		else if((lead-> key)<key) {  //lead의 key값이 key보다 작으면 lead가 오른쪽 자식 노드로 가도록 세팅
			middle = lead;
			lead = lead -> right;}
		else{  //key값이 일치하는 노드를 찾았을 경우
			if(!(lead->left)&&!(lead->right)){  //lead가 현재 리프노드이면
				if(!middle){  //middle이 null이므로 트리에서 루트노드말고는 없다면
					free(lead); //lead를 동적할당해제하고
					head -> left =NULL;  //루트노드를 null로 세팅
					printf("key값을 찾았고 삭제하였습니다\n");
					return 0;  //원함수로 리턴
				}
				free(lead);  //lead가 루트노드가 아니면 lead 동적할당해제
				if((middle->key)>key) middle->left=NULL;  //부모노드를 가리키는 middle의 키값이 key보다 크면 왼쪽 자식링크를 null로 세팅
				else middle-> right=NULL;  //부모노드를 가리키는 middle의 키값이 Key보다 작으면 오른쪽 자식링크를 null로 세팅
				printf("key값을 찾았고 삭제하였습니다\n");
				return 0;  //원함수로 리턴
				}
			else{
				printf("leaf node가 아닙니다\n");  //키값이 일치하는 노드를 찾았으나 리프노드가 아닐경우
				return 0;  //원함수로 리턴
			}
			}
		}  //lead가 null이 돼서 while문을 나온 상황, key값을 찾지못한 상황
	printf("key값을 찾지못했습니다\n");
	return 0;
}

Node* searchRecursive(Node* ptr, int key)  //재귀호출을 사용한 탐색 함수
{
	if(ptr){  //ptr이 null이 아닐때까지 반복
		if((ptr->key)==key) return ptr;  //key값이 일치하면 ptr을 리턴
		else if((ptr->key)>key) return searchRecursive(ptr->left, key);  //ptr의 키값이 key보다 크면 왼쪽 자식링크로 재귀호출
		else return searchRecursive(ptr->right, key);  //ptr의 키값이 key보다 작으면 오른쪽 자식링크로 재귀호출
		}
	return NULL;  //찾지못했다면 null리턴
}

Node* searchIterative(Node* head, int key)  //비순환호출을 사용한 탐색 함수
{
	Node*lead = head -> left;  //lead가 루트노드를 가리키도록 함
	while(lead){  //lead가 null이 아닐 때까지 반복
		if((lead->key) == key) return lead;  //키값이 일치하는 노드를 찾으면 바로 리턴
		else if ((lead->key)>key) lead = lead -> left;  //키값이 현재 노드의 키값보다 작으면 lead를 왼쪽 자식 링크로
		else lead = lead -> right;  //키값이 현재 노드의 키값보다 큰 경우 lead를 오른쪽 자식 링크로
	}
	return NULL;  //찾지못했다면 null리턴
}


int freeBST(Node* head)  //전체 트리를 동적할당해제해주는 함수
{
	Node * lead = head -> left;  //lead가 루트 노드를 가리키도록 함
	free_postorder(lead);  //루트노드를 인수로 해서 free_postorder함수 호출
	free(head);  //헤더노드 동적할당해제
	return 0;
}
void free_postorder(Node * ptr){  //후위순회를 이용한 트리 free함수

	if(ptr){  //ptr이 null이 아닐 때까지 반복
		free_postorder(ptr->left);  //트리의 가장 왼쪽 노드까지 재귀 호출
		free_postorder(ptr->right);  //트리의 왼쪽 자식 노드가 없으면 오른쪽 자식 노드를 재귀 호출
		free(ptr);  //ptr 동적할당해제
	}
}




