#include <stdio.h>
#include <stdlib.h>

typedef struct node {  //노드의 구조체
	int key;  //노드의 키값을 저장하는 멤버변수
	struct node *left;  //노드의 왼쪽 자식노드 주소를 저장하는 링크
	struct node *right;  //노드의 오른쪽 자식노드 주소를 저장하는 링크
} Node;

/* for stack */
#define MAX_STACK_SIZE		20  //스택사이즈 20
Node* stack[MAX_STACK_SIZE];  //스택사이즈를 가지고 만들어진 스택 배열
int top = -1;

Node* pop();  //stack에서 pop해주는 함수
void push(Node* aNode);  //stack에 push해주는 함수

/* for queue */
#define MAX_QUEUE_SIZE		20  //원형큐사이즈 20
Node* queue[MAX_QUEUE_SIZE];  //큐사이즈를 가지고 만들어진 큐 배열
int front = -1;
int rear = -1;

Node* deQueue();  //큐에서 원소를 삭제해주는 함수
void enQueue(Node* aNode);  //큐에 원소를 삽입해주는 함수


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("=====[2017038069]=====[이동우]=====\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //커멘드 값을 입력

		switch(command) {  //커멘드값을 각 경우에 비교해서 해당명령 실행
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;

		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
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
	if(*h != NULL)  //트리가 존재한다면 전체 트리를 free
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));  //트리가 없다면 동적할당으로 헤드노드를 만들고 값들 초기화
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;  //stack과 queue의 top front rear값도 모두 초기화

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)  //순환식 중위순회방식
{
	if(ptr) {  //ptr이 null이 아니라면
		recursiveInorder(ptr->left);  //트리의 가장 왼쪽 노드부터 시작해서
		printf(" [%d] ", ptr->key);  //부모노드를 출력
		recursiveInorder(ptr->right);  //오른쪽 자식 노드로 다시 순환호출
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)  //순차적 중위 순회
{
	if(!node){  //head->left가 비어있다면 트리가 비어있음을 알리고 리턴
		printf("트리가 비어있습니다\n");
		return;
	}
	while(1){  //무한루프
		while(node){  //node가 null일 때까지 왼쪽 자식노드를 탐색
			push(node);
			node = node->left;
		}
		node = pop();  //stack에서 원소 하나를 꺼낸 뒤 node에 대입
		if(node == NULL) break;  //더 이상 스택에서 꺼낼 원소가 없으면 무한루프 탈출
		printf( " [%d] ",node -> key);  //pop한 노드의 키값을 입력
		node = node ->right;  //pop한 노드에 오른쪽 자식 노드 주소 대입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)  //레벨 오더 순회
{
	if(!ptr){  //트리가 비어있을 경우
		printf("트리가 비어있습니다\n");
		return;
	}
	enQueue(ptr);  //우선 루트노드를 큐에 삽입
	while(1){
		ptr = deQueue();  //queue에서 원소 하나를 꺼냄
		if(!ptr) break;  //꺼낸 원소가 null이면 무한루프 탈출

		if(ptr -> left){  //꺼낸 노드의 왼쪽 노드가 존재하면
			enQueue(ptr->left);  //그 노드를 큐에 삽입
		}
		if(ptr -> right){  //꺼낸 노드의 오른쪽 노드가 존재하면
			enQueue(ptr->right);  //그 노드를 큐에 삽입
		}
		printf(" [%d] ", ptr->key);  //꺼낸 노드의 키값을 출력
	}
}


int insert(Node* head, int key)  //트리에 노드를 삽입해주는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));  //newNode선언 후 key값과 link값들을 초기화
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {  //트리가 존재하지않으면 newNode를 루트노드로 해서 리턴
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {  //ptr이 null이 아닐 때까지 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;  //중복된 값이 들어오면 바로 리턴

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;  //부모노드를 가리키는 포인터에 ptr주소 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)  //ptr의 키값이 키값보다 작으면 ptr에 오른쪽 자식 노드 주소 대입
			ptr = ptr->right;
		else  //ptr의 키값이 키값보다 크면 ptr에 왼쪽 자식 노드 주소 대입
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  //부모노드의 key값이 key값보다 크면 부모노드의 왼쪽에 newNode 위치
		parentNode->left = newNode;
	else
		parentNode->right = newNode;  //부모노드의 key값이 key값보다 작으면 부모노드의 오른쪽에 newNode 위치
	return 1;
}

int deleteNode(Node* head, int key)  //노드를 삭제하는 함수
{
	Node* lead = head -> left;  //lead가 루트노드를 가리키게 설정
	Node* middle = NULL;  //lead뒤에 노드를 가리키는 middle 설정
	if(!lead){  //트리가 비어있어서 삭제할 것이 없다면 그냥 리턴
		printf("트리가 비어있습니다\n");
		return 0;
	}
	while(lead){  //lead가 null이 아닐 때까지 반복
		if((lead -> key) > key){  //lead의 key값이 key값보다 큰 경우
			middle = lead;
			lead = lead -> left;  //lead에 왼쪽 자식 노드 주소 대입
		}
		else if((lead->key)<key){  //lead의 key값이 key값보다 작은 경우
			middle = lead;
			lead = lead -> right;  //lead에 오른쪽 자식 노드 주소 대입
		}
		else{  //key값을 찾았을 때
			printf("key값을 찾았고 삭제합니다\n");
			if(!(lead->left)&&!(lead->right)){  //해당 노드가 리프노드일 때
			if(!middle){  //해당 노드가 루트노드일때
				free(lead);  //lead를 동적할당해제 후
				head -> left = NULL;  //루트노드를 null로 설정
				return 0;
			}
			free(lead);  //루트노드가 아닐 경우 lead 동적할당 해제 후
			if((middle->key)>key) middle -> left =NULL;  //lead의 부모 노드의 키값이 키값보다 큰 경우 middle 왼쪽 링크를 null로
			else middle->right = NULL;  //lead의 부모 노드의 키값이 키값보다 작은 경우 middle 오른쪽 링크를 null로
			return 0;
			}
			else {  //해당 노드가 리프노드가 아닐 때
				if(!(lead->left)||!(lead->right)){  //해당 노드의 자식노드가 1개 있을 때
					if(!middle){  //루트노드 삭제 시
						if(lead->left){  //해당 노드의 왼쪽 자식노드가 존재할 때
							head -> left = lead -> left;  //루트노드를 lead 왼쪽 자식노드로
							free(lead);  //lead 동적할당해제
							return 0;
						}
						else if(lead -> right){  //해당 노드의 오른쪽 자식노드가 존재할 때
							head -> left = lead -> right;  //루트노드를 lead 오른쪽 자식노드로
							free(lead);  //lead 동적할당해제
							return 0;
						}
					}
						else{  //루트노드가 아닌 값 삭제 시
							if((middle->left)==lead){  //lead가 부모노드의 왼쪽 자식노드일 때
								if(lead -> left){  //lead 왼쪽 자식노드가 부모노드의 왼쪽에 가서 붙을 때
									middle -> left = lead -> left;
									free(lead);
									return 0;
								}
								else{  //lead 오른쪽 자식 노드가 부모노드의 왼쪽에 가서 붙을 때
									middle -> left = lead -> right;
									free(lead);
									return 0;
								}
							}
							else{  //lead가 부모노드의 오른쪽 자식노드일 때
								if(lead -> left){  //lead 왼쪽 자식노드가 부모노드의 오른쪽에 가서 붙을 때
									middle -> right = lead -> left;
									free(lead);
									return 0;
								}
								else{  //lead 오른쪽 자식노드가 부모노드의 오른쪽에 가서 붙을 때
									middle -> right = lead -> right;
									free(lead);
									return 0;
								}
							}
						}
					}
				else{  //자식노드가 모두 있는 노드일 경우
					Node*max = lead->left; //삭제하고자 하는 노드의 왼쪽 자식노드를 max로 설정
				Node*tail = NULL;  //max 전 노드를 가리킬 tail 설정
				while(max->right){  //max의 오른쪽 자식노드가 없을 때까지 max에 오른쪽 자식노드 주소 대입
					tail = max;
					max =  max ->right;
				}
				if(!max->left){  //왼쪽 트리에서 max를 찾았을 때 잔여트리가 존재하지않을 경우
					if(!tail){  //lead 바로 왼쪽 자식 노드가 max일 경우 lead의 키 값을 변경한 후 왼쪽 자식 노드를 null로 설정
					lead -> key = max -> key;
					lead -> left = NULL;
					free(max);
					}
					else{  //lead 바로 왼쪽 자식 노드가 max가 아닐 경우 lead의 키 값 변경한 후 max 이전 노드의 오른쪽 노드를 null로 설정
					lead -> key = max -> key;
					tail -> right = NULL;
					free(max);
					}
				}
				else{  //왼쪽 트리에서 max를 찾았을 때 잔여트리가 존재할 경우
					if(tail){  //lead 바로 왼쪽 자식 노드가 max가 아닐 경우
					tail -> right = max -> left;  //max의 왼쪽 트리를 max 이전 노드의 오른쪽 트리로 변경
					lead -> key = max -> key;  //lead 키 값 변경
					free(max);
					}
					else{  //lead 바로 왼쪽 자식 노드가 max일 경우
					lead -> left = max -> left;  //lead의 왼쪽에 max 왼쪽 트리를 넣어줌
					lead -> key = max -> key;  //lead 키값 변경
					free(max);
						}
					}
					return 0;
				}
				}


			}
		}
	printf("키값을 찾지 못했습니다\n");  //key값과 일치하는 노드를 찾지못하였다면
	return 0;
	}


void freeNode(Node* ptr) //순환식으로 동적할당해제해주는 함수
{
	if(ptr) {  //후위순회방식으로 트리를 동적할당해제
		freeNode(ptr->left);  //트리의 가장 왼쪽 노드를 재귀호출
		freeNode(ptr->right);  //오른쪽 자식 노드를 재귀호출
		free(ptr);  //해당 노드를 동적할당해제
	}
}

int freeBST(Node* head)  //전체트리를 동적할당해제해주는 함수
{

	if(head->left == head)  //트리가 비어있어서 헤드노드만 있는 경우
	{
		free(head);
		return 1;
	}

	Node* p = head->left;  //p가 루트노드를 가리키게 함

	freeNode(p);

	free(head);  //헤드도 동적할당해제
	return 1;
}



Node* pop()  //stack에서 pop하는 함수
{
	if(top < 0) return NULL;  //top이 -1이면 스택이 비어있으므로 리턴

	Node * lead = stack[top--];  //lead에 현재 스택에서 top이 가리키는 원소 대입 후 top값에서 1 감소
	return lead;
}

void push(Node* aNode)  //stack에 push하는 함수
{
	if(top >= MAX_STACK_SIZE){  //top이 스택 사이즈와 같거나 초과했을 경우 메세지 출력 후 리턴
		printf("Stack Full\n");
		return;
	}
	stack[++top] = aNode;  //stack의 top을 1 증가시킨 후 그 자리에 aNode 삽입
}



Node* deQueue()  //원형queue에서 원소를 삭제해주는 함수
 {
	if(front == rear){  //트리가 비어있다면 null리턴
		return NULL;
	}
	front = (front+1)%MAX_QUEUE_SIZE;  //front값을 1증가 후 modulo연산시킨 값을 대입
	Node * lead = queue[front];  //lead에 현재 큐에서 front가 가리키는 원소 대입
	return lead;  //lead 리턴
}

void enQueue(Node* aNode)  //원형queue에 원소를 삽입해주는 함수
{
	rear = (rear+1)%MAX_QUEUE_SIZE;  //rear값을 1증가 후 modulo연산시킨 값을 대입
	if(rear == front){  //큐가 꽉 차있다면 바로 원함수로 리턴
		printf("Queue Full!\n");
		return;
	}
	queue[rear]= aNode;  //현재 rear가 가리키는 자리에 aNode삽입
}




