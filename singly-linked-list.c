#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {  //key값과 자기자신을 가리키는 link값을 가지는 구조체 Node형의 listNode 선언
	int key;
	struct Node* link;
} listNode;

typedef struct Head {  //노드의 가장 처음을 나타내는 head형 구조체 headNode 선언
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);  //노드를 첫상태로 돌려놓는 함수
int freeList(headNode* h);  //노드들의 동적할당을 해제해주는 함수
int insertFirst(headNode* h, int key);  //전체노드 첫번째 자리에 key값을 가지는 노드 삽입해주는 함수
int insertNode(headNode* h, int key);  //전체노드에 key값을 가지는 노드를 삽입해주는 함수(크기비교 후 특정 자리에)
int insertLast(headNode* h, int key);  //전체노드 마지막 자리에 key값을 가지는 노드를 삽입해주는 함수
int deleteFirst(headNode* h);  //첫번째 노드를 삭제해주는 함수
int deleteNode(headNode* h, int key);  //특정 key값을 가지는 노드를 삭제해주는 함수
int deleteLast(headNode* h);  //마지막 자리 노드를 삭제해주는 함수
int invertList(headNode* h);  //전체 노드를 역순으로 만드는 함수
void printList(headNode* h);  //전체 노드를 출력해주는 함수

int main()
{
	printf("=====[2017038069]=====[이동우]=====\n");  //학번과 이름 출력
	char command;
	int key;
	headNode* headnode=NULL;  //가장 첫번째 노드를 가리키는 headnode선언과 초기화

	do{
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
		scanf(" %c", &command);  //커멘드 값 입력

		switch(command) {
		case 'z': case 'Z':  //커멘드가 z이면
			headnode = initialize(headnode);  //전체 노드 초기화
			break;
		case 'p': case 'P':  //커멘드가 p이면
			printList(headnode);  //전체 노드 출력
			break;
		case 'i': case 'I':  //커멘드가 i이면
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력받고
			insertNode(headnode, key);  //입력받은 key값의 자리를 찾아 노드 삽입
			break;
		case 'd': case 'D':  //커멘드가 d이면
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력받고
			deleteNode(headnode, key);  //key값을 가지는 노드를 찾아서 삭제
			break;
		case 'n': case 'N':  //커멘드가 n이면
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력받고
			insertLast(headnode, key);  //key값을 가지는 노드를 마지막에 삽입
			break;
		case 'e': case 'E':  //커멘드가 e이면
			deleteLast(headnode);  //가장 마지막 노드 삭제
			break;
		case 'f': case 'F':  //커멘드가 f이면
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력
			insertFirst(headnode, key);  //가장 첫번째 자리에 노드 삽입
			break;
		case 't': case 'T':  //커멘드가 t이면
			deleteFirst(headnode);  //가장 첫번째 노드 삭제
			break;
		case 'r': case 'R':  //커멘드가 r이면
			invertList(headnode);  //전체 노드 역순으로
			break;
		case 'q': case 'Q':  //커멘드가 q이면
			freeList(headnode);  //전체 노드의 동적할당 해제
			break;
		default:  //이외의 커멘드가 입력되면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  //해당 문구 출력
			break;
		}

	}while(command != 'q' && command != 'Q');  //커멘드가 q가 될 때까지 반복

	return 1;
}

headNode* initialize(headNode* h) {  //헤더노드형 포인터 h를 인수로 받아 전체 노드를 초기화시키는 함수

	if(h != NULL)
		freeList(h);  //헤더노드형 h가 null이면 동적할당 해제

	headNode* temp = (headNode*)malloc(sizeof(headNode));  //헤더노드형의 포인터 temp를 동적할당
	temp->first = NULL;  //temp가 가리키는 구조체 멤버변수 first값을 null로 초기화
	return temp;  //temp 리턴
}

int freeList(headNode* h){  //헤더노드형 포인터 h를 인수로 받아 전체 노드의 동적할당 해제해주는 함수
	listNode* p = h->first;  //listNode 형의 포인터 p 를 선언하고 첫번째 노드를 가리키도록 함

	listNode* prev = NULL;  //이전 노드를 가리키기 위해 prev 선언 후 초기화
	while(p != NULL) {  //포인터 p가 null일 때까지
		prev = p;  //이전 노드 prev에 p를 대입
		p = p->link;  //p가 다음 노드를 가리키도록 다음 link값을 대입
		free(prev);  //이전 노드 prev의 동적할당 해제
	}
	free(h);  //헤더노드 동적할당 해제
	return 0;
}

int insertFirst(headNode* h, int key) {  //헤더노드 h와 key값을 받아서 가장 첫번째 자리에 노드 삽입해주는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));  //listnode형  node 선언 후 동적할당
	node->key = key;  //node의 멤버변수 key값에 인수로 받아온 key값 대입
	node->link = h->first;  //node의 link에 가장 첫번째 노드를 가리키는 first값 대입
	h->first = node;  //가장 첫번째 노드를 node로

	return 0;
}

int insertNode(headNode* h, int key) {  //key값 비교 후 key값보다 큰 수가 나오는 자리에 노드 대입해주는 함수

	listNode* lead = h-> first;  //listNode형의 lead 선언 후 첫번째 노드를 가리키는 first 값 대입
	listNode* middle =NULL;  //이전 노드를 가리키기 위해 middle 선언 후 초기화
	listNode *temp = (listNode *)malloc(sizeof(*temp));  //listnode형의 temp 동적할당
	temp -> key = key;  //temp의 key값에 인수로 받아온 key값 대입
	temp -> link =NULL;  //temp의 link값 초기화

	if(!lead){  //노드가 비어있는 노드일 때
		h -> first = temp;  //가장 첫번째 노드를 temp로
		return 1;
	}
	if(lead->key>key){  //첫번째 노드의 key값보다 인수로 받은 key값이 작다면
		temp->link=lead;  //temp의 다음 노드를 lead로 (기존 첫번째 노드)
		h->first=temp;  //첫번째 노드를 temp로 함
		return 1;
	}
	while(lead!=NULL){  //lead가 null이 아닐 때 까지 반복
		if(lead->key < key){  //lead의 key값보다 인수로 받은 key값이 클 경우
			middle=lead;  //이전노드를 가리키는 middle에 현재 노드 lead값 대입
			lead=lead->link;  //현 노드를 다음 노드로 가리키도록 함
		}
		else{  //lead의 key값보다 인수로 받은 key값이 작을 경우
			temp->link=lead;  //temp 다음 노드를 lead로 하고
			middle->link=temp;  //이전 노드의 다음 노드를 temp로 함
			return 1;
		}
	}  //lead가 마지막 노드를 지나 null값이 되었을 때
	middle->link=temp;  //middle의 다음 노드(마지막 노드)를 temp로 함
	return 1;
}

	int insertLast(headNode* h, int key) {  //가장 마지막 자리에 key값을 가지는 노드를 삽입해주는 함수
		listNode *lead =h->first;  //lead 선언 후 가장 첫번째 노드를 가리키도록 함
		listNode *temp = (listNode*)malloc(sizeof(*temp));  //temp선언 후 동적할당
		temp -> key =key;  //temp의 key값을 인수로 받은 key값으로
		temp -> link = NULL;  //temp의 다음 노드를 null값으로
		if(!lead)  //아무것도 없으면
			h -> first = temp;  //temp를 첫번째 노드로 함
		else{  //어떤 노드가 존재하면
			for(;lead->link;lead=lead->link);  //lead->link가 0이 될때까지(마지막 노드가 될때까지)반복
			lead->link=temp;  //마지막 노드를 temp로 함
		}
		return 1;
	}

	int deleteFirst(headNode* h) {  //첫번째 노드를 삭제하는 함수
		listNode *lead = h->first;  //lead선언 후 가장 첫번째 노드를 가리키도록 함
		if(!lead){  //lead가 null 이면
			printf("삭제할 것이 없습니다\n");
			return 1;  //삭제할 것이 없으므로 리턴
		}
		if(!(lead->link)){  //lead 다음 노드가 없다면(하나밖에 없는 노드라면)
			h->first=NULL;  //가장 첫번째 노드를 초기화
			free(lead);  //lead를 동적할당해제
		}
		else{  //lead 다음 노드가 존재한다면
			h->first = lead->link;  //first 노드를 lead의 다음 노드로(두번째 노드로 설정)
			free(lead);  //lead를 동적할당해제
		}
		return 1;
	}

	int deleteNode(headNode* h, int key) {  //key값을 가진 노드를 찾은 후 삭제
		listNode*lead=h->first;  //lead선언 후 가장 첫번째 노드를 가리키도록 함
		listNode*middle=NULL;  //이전 노드를 가리킬 middle 선언 후 초기화
		int result=0;  //key값을 못 찾았을 경우를 위해 result변수 선언
		if(!lead){  //아무것도 없으면
			printf("삭제할 것이 없습니다\n");
			return 1;  //삭제할 것이 없으므로 리턴
				}
		while(lead!=NULL){  //lead가 가장 마지막 노드 다음 노드가 될 때까지 반복
			if(lead->key==key){  //lead의 key값이 인수로 받은 key값과 같다면
				result=1;  //result에 1대입
				if(middle==NULL){  //이전 노드가 null값이면(가장 처음 노드일 경우)
					h->first=lead->link;  //첫번째 노드를 lead의 다음 노드로 설정
					free(lead);  //lead를 동적할당해제
				}
				else{  //가장 처음 노드가 아닐 경우
					middle->link=lead->link;  //이전 노드 값 다음 노드를 lead의 다음 노드로 설정
					free(lead);  //lead를 동적할당해제
				}
			}
			middle=lead;  //이전 노드값에 현재 노드 값 대입
			lead=lead->link;  //현재 노드를 다음 노드를 가리키도록 설정
		}
		if(result==1)  //값을 찾았다면
			printf("key값을 찾았고 삭제했습니다\n");
		else  //값을 찾지 못했다면
			printf("key값을 찾지 못했습니다\n");
		return 1;
	}


	int deleteLast(headNode* h) {  //가장 마지막 노드를 삭제하는 함수
		listNode*lead=h->first;  //lead선언 후 가장 첫번째 노드를 가리키도록 함
		listNode*middle=NULL;  //이전 노드를 가리킬 middle 노드 선언 후 초기화
		if(!lead){  //아무것도 없으면
			printf("삭제할 것이 없습니다\n");
			return 1;  //삭제할 것이 없으므로 리턴
		}
		while(lead->link!=NULL){  //lead의 다음 노드가 null이 아닐 때까지(마지막 노드 전까지 반복)
			middle=lead;  //이전노드에 현재 노드 대입
			lead=lead->link;  //현재 노드를 다음 노드를 가리키도록 대입
		}
		if(middle){  //이전 노드값이 null이 아니면(2번째 자리 이상의 노드일 경우)
			middle->link=NULL;  //이전 노드가 가리키는 것을 null로 설정(마지막 노드로)
			free(lead);  //lead동적할당해제
			return 1;
			}
		else{  //이전 노드값이 null값이면(첫번째 자리의 노드일 경우)
			h->first=NULL;  //가장 첫번째 노드를 null값으로
			free(lead);  //lead동적할당해제
			return 1;
		}
	}


	int invertList(headNode* h) {  //전체 노드를 역순으로 바꿔주는 함수
		listNode *lead=h->first;  //lead선언 후 가장 첫번째 노드를 가리키도록 함
		listNode *middle=NULL;  //이전 노드를 가리키는 middle 선언 후 초기화
		listNode *trail;  //이전 노드의 이전 노드를 가리키는 trail 선언

		if(!lead){  //아무 노드도 존재하지않으면
			printf("역순으로 재배치할 노드가 없습니다\n");
			return 1;  //재배치할 노드가 없으므로 리턴
		}

		while(lead){  //lead가 가장 마지막 노드가 될때까지 반복
			trail=middle;  //trail에 middle값 대입(이전 노드의 이전 노드를 이전 노드로 설정)
			middle=lead;  //middle에 lead값 대입(이전 노드를 현재 노드로 설정)
			lead=lead->link;  //lead에 다음 노드 값을 대입(현재 노드는 계속 다음 노드를 가리키도록 설정)
			middle->link=trail;  //middle이 trail값을 가리키도록 설정
		}
		h->first=middle;  //첫번째 노드를 middle값으로 설정(middle이 가장 마지막 노드가 되므로)
		return 1;
	}


	void printList(headNode* h) {  //전체 노드를 출력해주는 함수
		int i = 0;  //노드의 순서를 출력해줄 변수 i 선언 후 초기화
		listNode* p;  //listnode형 p 선언

		printf("\n---PRINT\n");

		if(h == NULL) {  //첫번째 노드가 null이면(노드가 아무것도 없으면)
			printf("Nothing to print....\n");
			return;  //출력할 노드가 없으므로 리턴
		}

		p = h->first;  //p가 첫번째 노드를 가리키도록 함

		while(p != NULL) {  //p가 가장 마지막 노드가 될때까지 반복
			printf("[ [%d]=%d ] ", i, p->key);  //노드의 순서와 그 노드의 key값 출력
			p = p->link;  //p가 다음 노드를 가리키도록 설정
			i++;  //i 증가
		}

		printf("  items = %d\n", i);  //전체 노드의 개수를 출력
	}




