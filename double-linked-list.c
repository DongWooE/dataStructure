#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {  //node 구조체
	int key;  //키값
	struct Node* llink;   //노드의 왼쪽 링크
	struct Node* rlink;  //노드의 오른쪽 링크
} listNode;


typedef struct Head {  //노드를 가리키는 헤더 노드 구조체
	struct Node* first;  //가장 첫번째 노드를 가리키는 구조체 node형 포인터
}headNode;

int initialize(headNode** h);  //이중포인터를 받는 노드 초기화 함수
int freeList(headNode* h);  //노드를 동적할당해제해주는 함수
int insertNode(headNode* h, int key);  //노드를 삽입해주는 함수
int insertLast(headNode* h, int key);  //가장 마지막 자리에 노드를 삽입해주는 함수
int insertFirst(headNode* h, int key);  //가장 첫번째 자리에 노드를 삽입해주는 함수
int deleteNode(headNode* h, int key);  //key값에 해당하는 노드를 삭제해주는 함수
int deleteLast(headNode* h);  //가장 마지막 노드를 삭제해주는 함수
int deleteFirst(headNode* h);  //가장 첫번재 노드를 삭제해주는 함수
int invertList(headNode* h);  //노드 순서를 역변으로 해주는 함수
void printList(headNode* h);  //모든 노드를 출력해주는 함수


int main()
{
	char command;  //char형 command값
	int key;
	headNode* headnode=NULL;  //headnode를 초기화
	printf("=====[2017038069]=====[이동우]\n");  //학번과 이름 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //command 값 입력

		switch(command) {  //케이스별 분류
		case 'z': case 'Z':  //z 입력시
			initialize(&headnode);  //포인터 headnode형의 주소를 넘겨서 초기화해주는 함수
			break;
		case 'p': case 'P':  //p 입력시
			printList(headnode);  //노드를 출력해주는 함수
			break;
		case 'i': case 'I':  //i 입력시
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력
			insertNode(headnode, key);  //key값과 같이 노드에 삽입
			break;
		case 'd': case 'D':  //d 입력시
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력
			deleteNode(headnode, key);  //key값을 가지는 노드 삭제
			break;
		case 'n': case 'N':  //n 입력시
			printf("Your Key = ");
			scanf("%d", &key);  //key값 입력
			insertLast(headnode, key);  //노드의 마지막 자리에 key값을 가지는 노드 삽입
			break;
		case 'e': case 'E':  //e 입력시
			deleteLast(headnode);  //가장 마지막 노드 삭제
			break;
		case 'f': case 'F':  //f 입력시
			printf("Your Key = ");
			scanf("%d", &key);  //key값 입력
			insertFirst(headnode, key);  //가장 첫번째 자리에 key값을 가지는 노드 삽입
			break;
		case 't': case 'T':  //t 입력시
			deleteFirst(headnode);  //가장 첫번째 노드 삭제
			break;
		case 'r': case 'R':  //r 입력시
			invertList(headnode);  //전체 노드를 역순으로 바꿈
			break;
		case 'q': case 'Q':  //q 입력시
			freeList(headnode);  //노드 전체 동적할당해제
			break;
		default:  //이외의 값 입력시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //command가 q가 될 때까지 반복

	return 1;
}


int initialize(headNode** h) {  //이중포인터 h를 받고 전체 노드를 초기화시켜주는 함수
	if(*h!=NULL)  // h가 가리키는 값이 null이 아니면 임의의 노드가 존재하면
			freeList(*h);  //h가 가리키는 구조체의 동적할당 해제
	headNode*temp = (headNode*)malloc(sizeof(*temp));  //헤더노드형 구조체 temp를 동적할당
	temp->first=NULL;  //헤더노드 temp의 멤버변수 first가 가리키는 값을  null로 초기화
	*h=temp;  //h가 동적할당해준 temp 구조체를 가리키도록 설정
	return 1;
}

int freeList(headNode* h){  //동적할당해제해주는 함수
	listNode * lead = h -> first;  //listNode형의 lead가 첫번째 노드를 가리키도록 설정
	listNode * middle = NULL;  //listnode형의 middle을 null값으로 초기화(middle은 현재 노드의 전 노드를 가리키는 포인터)
	while(lead !=NULL){  //lead가 NULL일때까지 (lead가 노드의 끝자리를 넘어갈 때까지 반복)
		middle = lead;  //middle에 lead값을 대입
		lead=lead -> rlink;  //lead를 다음 노드로 설정
		free(middle);  //middle의 동적할당해제
	}
	free(h);  //헤더노드 h 동적할당해제
	return 0;
}


void printList(headNode* h) {  //노드값을 출력해주는 함수
	int i = 0;  //정수형 변수 i 선언 후 초기화
	listNode* p;  //listnode 형 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {  //노드가 비어있으면
		printf("Nothing to print....\n");  //문구 출력
		return;
	}

	p = h->first;  //p가 첫번째 노드를 가리키도록 설정

	while(p != NULL) {  //p가 마지막 노드 다음 자리를 가리킬 때가지 반복
		printf("[ [%d]=%d ] ", i, p->key);  //i값과 p가 가리키는 노드의 key값 출력
		p = p->rlink;  //p가 다음 링크를 가리키도록 설정
		i++;  //i를 1증가
	}

	printf("  items = %d\n", i);  //전체 노드의 개수를 출력
}

int insertLast(headNode* h, int key) {  //노드 가장 마지막 자리에 key값을 가지는 노드 삽입해주는 함수
	listNode * temp = (listNode *)malloc(sizeof*temp);  //temp를 동적할당
	temp -> key = key;  //temp의 key값에 인수로 받은 key값 대입
	temp -> rlink = NULL;  //temp 다음의 자리를 null로 초기화
	if(!(h->first)){  //비어있는 노드였을 때
			h -> first = temp;  //첫번째 노드를 가리키는 포인터에 temp로 설정
			return 0;
		}
	listNode * lead = h->first;  //lead가 첫번째 노드를 가리키도록 설정
	listNode * middle =NULL;  //현재 노드의 전 노드를 가리키는 구조체 포인터 선언 후 초기화
	while(lead){  //lead가 NULL값이 될 때까지 반복
		middle = lead;  //lead의 전 노드를 가리키는 middle에 lead 값 대입
		lead = lead -> rlink;  //lead가 다음 노드를 가리키도록 설정
	}  //lead가 null이 되면
	temp -> llink = middle;  //temp의 왼쪽 노드를 middle로 설정
	middle -> rlink = temp;  //middle의 오른쪽 노드를 temp로 설정
	return 0;
}

int deleteLast(headNode* h) {  //가장 마지막 노드를 삭제해주는 함수
	if(!(h->first)){  //전체 노드가 비어있을 때
			printf("삭제할 노드가 없습니다\n");  //해당 문구 출력
			return 0;
		}
	listNode * lead = h -> first;  //lead가 첫번째 노드를 가리키도록 설정
	while(lead ->rlink !=NULL)  //lead가 마지막 노드가 되기전까지 반복
		lead = lead -> rlink;  //lead가 다음 노드를 가리키도록 설정
	if(lead==(h->first)){  //lead가 첫번째 노드일 경우
		h->first = NULL;  //첫번째 노드를 null로 설정
		free(lead);  //lead를 동적할당해제해줌
		return 0;
	}
	else{
		(lead->llink)->rlink = NULL;  //lead의 전 노드의 다음 노드를 가리키는 값을 null로 설정
		free(lead);  //lead를 동적할당해제해줌
		return 0;
	}
}

int insertFirst(headNode* h, int key) {  //가장 첫번째 자리에 key값을 가지는 노드를 삽입해주는 함수
	listNode *temp = (listNode *)malloc(sizeof*temp);  //temp를 동적할당해줌
	temp -> key = key;  //temp의 key값에 인수로 받은 key값 대입
	temp -> rlink = NULL;  //temp의 왼쪽 오른쪽 링크를 null로 초기화
	temp -> llink = NULL;
	if(!(h->first)){  //첫번째 노드를 가리키는 포인터가 NULL이면
		h -> first = temp;  //temp를 첫번째 자리로
		return 0;
	}
	listNode * lead = h ->first;  //lead가 첫번째 노드를 가리키도록 설정
	temp -> rlink = lead;  //temp의 오른쪽 노드를 lead로
	lead -> llink = temp;  //lead의 왼쪽 노드를 temp로
	h-> first = temp;  //첫번째 노드를 temp로 설정
	return 0;
}

int deleteFirst(headNode* h) {  //가장 첫번째 노드를 삭제하는 함수
	if(!(h->first)){  //노드가 비어있으면
			printf("삭제할 노드가 없습니다\n");  //문구 출력
			return 0;
		}
	listNode * lead = h->first;  //lead가 첫번째 노드를 가리키도록 설정
	if(!(lead -> rlink)){  //노드가 하나밖에 없으면
		h->first=NULL;  //첫번째 노드를 가리키는 first를 null로
	}
	else{  //노드가 2개 이상이면
		(lead -> rlink) -> llink = NULL;  //lead의 오른쪽 노드의 왼쪽 링크를 null로
		h->first = lead -> rlink;  //첫번째 노드를 lead의 오른쪽 링크의 노드로 설정(기존 두번째 노드를 첫번째 노드로 설정한다)
	}
	free(lead);  //lead 동적할당 해제
	return 0;
}

int invertList(headNode* h) {  //노드를 역순으로 만들어주는 함수
	if(!(h->first)){  //노드가 비어있으면
			printf("역순할 노드가 없습니다\n");
			return 0;
		}
	listNode *lead = h -> first;  //lead가 첫번째 노드를 가리키도록 설정
	listNode *middle = NULL;  //lead의 전 노드를 가리킬 middle 선언 후 초기화
	listNode *trail;  //middle의 전 노드를 가리킬 trail 선언 후 초기화
	while(lead!= NULL){  //lead가 노드의 마지막 자리의 다음 자리까지 갈 때까지 반복
		trail = middle;  //trail에 middle 값 대입
		middle = lead;  //middle에 lead 값 대입
		lead = lead -> rlink;  //lead를 다음 자리를 가리키도록 설정
		middle -> llink = lead;  //middle의 왼쪽 링크가 다음 노드를 가리키도록 설정(노드의 llink와 rlink를 뒤바꿔주는 과정)
		middle -> rlink = trail;  //middle의 오른쪽 링크가 전 노드를 가리키도록 설정
	}
	h->first = middle;  //첫번째 노드를 middle로 설정
	return 0;
}

int insertNode(headNode* h, int key) {  //key값을 가지는 노드를 추가해주는 함수
	listNode * lead =h->first;  //lead가 첫번째 노드를 가리키도록 설정
	listNode * middle = NULL;  //lead의 전 노드를 가리키는 middle 선언 후 초기화
	listNode * temp = (listNode*)malloc(sizeof*lead);  //listnode형 temp 선언 후 동적할당
	temp -> key = key;  //temp의 key값에 key값 대입
	temp -> rlink = NULL;  //temp의 오른쪽 링크를 null값으로
	temp -> llink = NULL;  //temp의 왼쪽 링크를  null값으로

	if(!lead){  //노드가 비어있을 때
		h -> first = temp;  //temp를 첫번째 노드로 설정
		return 0;
	}
	if( lead -> key >= key){  //첫번째 노드의 키값이랑 키값 비교해서 기존 노드의 key값이 크거나 같으면
		temp -> rlink = h -> first;  //temp의 오른쪽 링크에 기존 첫번째 노드를 대입
		h-> first -> llink = temp;   //첫번째 노드의 왼쪽 링크를 temp로
		h -> first = temp;  //첫번째 노드를 temp로 설정
		return 0;
	}  //바로 첫번째 노드와 비교했는 데 바로 자리를 찾았을 경우의 코드
	while(lead!=NULL){  //lead가 마지막 노드의 다음 자리를 가리킬 때까지 반복
		if(lead -> key < key){  //lead의 key값이 key값도 작으면
			middle = lead;  //middle을 다음 노드를 가리키도록
			lead = lead -> rlink;  //lead를 다음 노드를 가리키도록 설정
		}  //key값의 자리를 못찾았으므로 다음 자리를 탐색한다
		else{  //lead의 key값이 더 크다면
			temp -> llink = middle;  //temp의 왼쪽 링크를 middle로 설정
			temp -> rlink = lead;  //temp의 오른쪽 링크를 lead로 설정
			middle -> rlink = temp;  //middle의 오른쪽 자리에 temp 대입
			lead -> llink = temp;  //lead의 왼쪽 자리에 temp  대입
			return 0;
		}  //key값의 자리를 찾았으므로 노드 사이에 대입
	}  //만약 노드를 전부 탐색했는 데 자리를 못 찾았다면
	middle -> rlink = temp;  //middle(현재 마지막 노드)의 오른쪽 자리에 temp 대입
	temp -> llink = middle;  //temp의 왼쪽링크를 middle로 설정
	return 0;
}

int deleteNode(headNode* h, int key) {  //key값을 가지는 노드를 탐색 후 삭제
	if(!(h->first)){  //빈 노드일 경우
		printf("삭제할 노드가 없습니다\n");
		return 0;
	}
	listNode * lead = h -> first;  //lead를 첫번째 노드를 가리키도록 설정
	listNode * middle = NULL;  //lead의 전 노드 middle 선언
	while(lead !=NULL){  //lead가 마지막 노드의 다음 자리를 갈 때까지 반복
		if(lead -> key == key){  //key값에 해당하는 노드를 찾았다면
			if(!(middle)){  //아직 탐색한 노드가 하나밖에 없을 때
				h -> first = NULL;  //첫번째 노드를 가리키는 포인터를 NULL로 설정
				if(lead -> rlink){  //lead의 오른쪽에 노드가 존재한다면
					h -> first = lead ->rlink;  //첫번째 노드를 lead다음 노드로 설정
				}
			}
			else{ //탐색한 노드가 2개 이상일 때
				if(!(lead->rlink)){  //찾은 노드가 마지막 자리의 노드일 때
					middle -> rlink = NULL;  //middle를 마지막 노드로 설정
				}
				else{  //찾은 노드가 마지막 자리의 노드가 아닐 경우(노드들 사이에서 찾았을 경우)
					middle-> rlink = lead -> rlink;  //middle의 오른쪽 링크를 lead의 오른쪽 링크로
					(lead -> rlink) -> llink = middle;  //lead의 오른쪽 노드의 왼쪽 링크를 middle로 설정
				}
			}
		free(lead);  //lead 동적할당해제
		printf("key값을 찾았고 삭제하였습니다\n");
		return 0;
		}
	middle = lead;  //middle을 다음 자리로 이동
	lead = lead -> rlink;  //lead를 다음 자리로 이동
	}  //key값을 찾지 못했을 때 문구 출력
	printf("key값을 찾지 못했습니다\n");
	return 0;
}

