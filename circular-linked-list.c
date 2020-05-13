#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {  //node구조체
	int key;  //key값
	struct Node* llink;  //노드의 left link
	struct Node* rlink;  //노드의 right link
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);  //노드를 초기화하는 함수
int freeList(listNode* h);  //전체 노드를 동적할당해제하는 함수
int insertLast(listNode* h, int key);  //마지막 자리에 노드를 삽입하는 함수
int deleteLast(listNode* h);  //마지막 노드를 삭제하는 함수
int insertFirst(listNode* h, int key);  //첫번째 자리에 노드를 삽입하는 함수
int deleteFirst(listNode* h);  //첫번째 노드를 삭제하는 함수
int invertList(listNode* h);  //전체 노드를 역순으로 재배치하는 함수
int insertNode(listNode* h, int key);  //키값 비교후 알맞은 자리에 노드를 삽입해주는 함수
int deleteNode(listNode* h, int key);  //키값이 일치하는 노드를 찾아 삭제하는 함수
void printList(listNode* h);  //전체 노드를 출력해주는 함수

int main()
{
	printf("=====[2017038069]==========[이동우]=====\n");  //학번과 이름 출력
	char command;
	int key;
	listNode* headnode=NULL;  //head노드 선언 후 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //커멘드 값 입력

		switch(command) {  //커멘드 값 비교 후 해당 명령 실행
		case 'z': case 'Z':
			initialize(&headnode);
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


int initialize(listNode** h) {  //노드를 초기화해주는 함수(더블 포인터를 받음)

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)  //해당 h의 주소가 가리키는 값이 없으면 null이 아니면(h가 존재하면)
		freeList(*h);  //h를 free함수에 넘겨서 동적할당해제
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));  //h를 구조체 크기만큼 동적할당
	(*h)->rlink = *h;  //h의 오른쪽 링크가 자기자신을 가리키도록 설정
	(*h)->llink = *h;  //h의 왼쪽 링크가 자기자신을 가리키도록 설정
	(*h)->key = -9999;  //h의 키값을 -9999를 대입
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode * lead = h -> rlink;  //lead가 첫번째 노드를 가리키도록 설정
	listNode * middle=NULL;  //middle은 lead의 뒤에 오는 노드를 가리킴
	if(lead!=h){  //헤더노드가 자기자신을 가리키지않으면
	while(lead!=h){  //lead가 마지막 자리가 될때까지
		middle = lead;  //middle값을 lead로
		lead = lead -> rlink;  //lead가 자기 다음 노드를 가리키도록 하고
		free(middle);  //middle 동적할당해제
	}
	}
	free(h);  //헤더노드 동적할당 해제
	return 0;
}



void printList(listNode* h) {  //전체 노드를 출력해주는 함수
	int i = 0;  //i를 0으로 초기화
	listNode* p;  //listNode p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {  //헤더노드가 null이면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;  //p가 가장 첫번째 노드를 가리키도록 함

	while(p != NULL && p != h) {  //p가 null이 아니거나 또는 p가 h로 돌아오지않으면(모든 노드를 탐색할 동안)
		printf("[ [%d]=%d ] ", i, p->key);  //i값과 p의 키값 출력
		p = p->rlink;  //p가 다음 노드를 가리키도록
		i++;  //i에 1더해줌
	}
	printf("  items = %d\n", i);  //i값 출력

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);  //헤더노드의 주소정보와 링크들에 대한 주소 정보 출력

	i = 0;  //i초기화
	p = h->rlink;  //p가 다시 첫번째 노드를 가리키도록 설정
	while(p != NULL && p != h) {  //모든 노드 탐색
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);  //각 노드들의 주소와 링크들에 대한 주소 정보 출력
		p = p->rlink;  //p가 다음 노드를 가리키도록 설정
		i++;  //i에 1 더해줌
	}

}
/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {  //가장 마지막 자리에 노드를 삽입해주는 함수
	listNode* temp = (listNode*)malloc(sizeof(*temp));  //temp 선언 후 동적할당
	temp -> key =key;  //temp의 키값에 입력된 키값 대입
	temp -> llink = NULL;  //temp의 링크 정보들을 초기화
	temp -> rlink =NULL;
	listNode *lead = h->rlink;  //lead선언 후 가장 첫번째 노드를 가리키도록 설정
	listNode *middle = NULL;  //lead 전 노드를 가리키는 middle선언 후 초기화
	if(lead==h){  //노드가 하나밖에 없을 때
		temp -> llink =h;  //temp의 링크들이 h를 가리키도록 설정
		temp -> rlink =h;
		h -> llink = temp;  //h의 링크들이 temp를 가리키도록 설정
		h -> rlink = temp;
		return 0;  //main으로 리턴
	}
	while(lead!=h){  //lead가 다 돌아서 헤드노드를 가리키기 전까지
		middle = lead;  //middle을 다음 노드로
		lead = lead -> rlink;  //lead를 다음 노드로 설정
	}  //middle이 가장 마지막 노드임
	temp -> rlink = h;  //temp의 다음 노드를 헤더노드로 설정
	temp -> llink = middle;  //temp의 왼쪽 노드를 마지막 노드였던 middle로 설정
	middle -> rlink = temp;  //middle의 다음 노드를 temp로 설정
	h -> llink = temp;  //가장 마지막 노드를 temp로 설정
	return 1;  //main으로 리턴
}
/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {  //가장 마지막 노드를 삭제하는 함수
	listNode*lead = h -> rlink;  //lead가 가장 첫번째 노드를 가리키도록 설정
	if(lead == h){  //노드가 아무것도 없으면
		printf("삭제할 노드가 없습니다\n");
		return 0;
	}
	while((lead -> rlink)!=h)  //lead가 가장 마지막 자리까지 가도록 반복
		lead = lead-> rlink;
	if(lead == (h -> rlink)){  //lead가 가장 첫번째 노드이므로 노드가 하나밖에 없던 경우
		h -> llink =h;  //h의 링크들이 자기 자신을 가리키도록 설정
		h -> rlink =h;
		free(lead);  //lead 동적할당해제
		return 0;  //main으로 리턴
	}
	else{  //노드가 2개이상이었을 때
		(lead-> llink)-> rlink = h;  //lead의 전노드의 다음 노드가 헤더노드를 가리키도록
		h -> llink = lead->llink;  //가장 마지막 노드를 lead 전노드로 설정
		free(lead);  //lead를 동적할당해제
		return 0;  //main으로 리턴
	}
}
/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {  //가장 첫번째 자리에 노드를 삽입해주는 함수
	listNode * temp = (listNode*)malloc(sizeof(*temp));  //temp를 동적할당
	temp -> key = key;  //temp의 키값에 입력된 키값 대입
	temp -> llink =NULL;  //temp의 링크들을 초기화
	temp -> rlink = NULL;
	listNode * lead = h -> rlink;  //lead가 가장 마지막 노드를 가리키도록 설정
	if(lead == h){  //노드가 하나밖에 없으면
		temp -> llink =h;  //temp의 링크들이 헤더노드를 가리키도록 설정
		temp -> rlink =h;
		h -> llink = temp;  //헤더노드들의 링크들이 temp를 가리키도록 설정
		h -> rlink = temp;
		return 0;  //메인으로 리턴
	}//노드가 2개 이상이면
	temp -> rlink = lead;  //temp의 다음 노드를 lead로 설정
	temp -> llink = h;  //temp의 이전 노드를 헤더노드로 설정
	lead -> llink = temp;  //lead의 이전 노드를 temp로 설정
	h -> rlink = temp;  //가장 첫번째 노드를 temp로 설정
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {  //가장 첫번째 원소를 삭제하는 함수
	listNode*lead = h -> rlink;  //노드에서 가장 첫번째 원소를 가리키는 lead 선언
	if(lead == h){  //노드에 아무것도 없을 때
		printf("삭제할 노드가 없습니다\n");
		return 0;
	}
	if((lead -> rlink)==h){  //노드가 하나밖에 없을 때
		h -> rlink = h;  //가장 첫번째 노드를 헤드노드로
		h -> llink = h;  //가장 마지막 노드를 헤드노드로
	}
	else{  //노드가 2개 이상일 때
		(lead -> rlink)-> llink = h;  //lead 다음노드의 왼쪽 노드를 h로
		h -> rlink = lead -> rlink; //가장 첫번째 원소를 lead 다음 노드로 설정
	}
	free(lead);  //lead 동적할당 해제
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {  //전체 노드들을 역순으로 재배치하는 함수
	listNode* lead= h -> rlink;  //lead가 가장 마지막 노드를 가리키도록 설정
	if(lead == h){  //노드가 없으면
		printf("역순할 노드가 없습니다\n");
		return 0;
	}
	listNode * middle = NULL;  //lead이전노드를 가리킬 middle선언
	listNode * trail;  //middle이전노드를 가리킬 trail선언
	h -> llink = lead;  //마지막 노드를 lead로 설정
	while(lead!=h){  //lead가 헤더노드로 되돌아올 때까지
		trail = middle;  //trail을 다음노드로
		middle = lead;  //middle을 다음노드로
		lead = lead -> rlink;  //lead를 다음노드로
		middle -> llink = lead;  //middle의 왼쪽 링크를 lead로 설정
		middle -> rlink = trail;  //middle의 오른쪽 링크를 trail로 설정
	}  //현재 middle이 가장 마지막 노드
	h -> rlink = middle;  //가장 첫번째 노드를 middle로 설정
	(h -> llink)->rlink = h;  //가장 마지막 노드의 오른쪽 링크가 자기자신을 가리키도록 설정
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {  //키값 비교 후 알맞은 자리에 노드를 삽입해주는 함수
	listNode * lead = h -> rlink;  //lead를 가장 첫번째 노드를 가리키도록 설정
	listNode * middle = NULL;  //lead 전노드를 가리킬 middle 선언
	listNode * temp = (listNode *)malloc(sizeof*temp);  //temp 선언 후 동적할당
	temp -> key = key;  //temp의 키값을 입력받은 키값으로
	temp -> llink =NULL;  //temp의 링크들을 초기화
	temp -> rlink = NULL;

	if(lead==h){  //노드가 하나밖에 없으면
		temp -> llink = h;  //temp의 링크들이 헤더노드를 가리키도록 설정
		temp -> rlink = h;
		h-> llink = temp;  //헤더노드의 링크들이 temp를 가리키도록 설정
		h -> rlink = temp;
		return 0;  //main으로 리턴
	}
	if(lead -> key >= key){  //temp노드가 첫번째 자리에 들어갈 경우
		temp -> llink = h;  //temp의 왼쪽 링크에 헤더노드 주소 대입
		temp -> rlink = lead;  //temp의 오른쪽 링크에 기존 첫번째 노드 주소 대입
		lead -> llink = temp;  //기존 첫번째 노드의 왼쪽링크에 temp주소 대입
		h -> rlink = temp;  //가장 첫번째 노드를 temp로 설정
		return 0;  //main으로 리턴
	}
	while(lead!=h){  //lead가 마지막 노드를 지나 헤더노드로 돌아올 때까지 반복
		if(lead -> key < key){  //아직 temp가 들어갈 자리를 찾지못했다면
			middle = lead;  //middle을 다음 노드로
			lead = lead -> rlink;  //lead를 다음 노드로
		}
		else{  //temp가 들어갈 자리를 찾았다면
			temp -> llink = middle;  //temp의 이전 노드를 middle로 설정
			temp -> rlink = lead;  //temp의 다음 노드를 lead로 설정
			middle -> rlink = temp;  //middle의 다음 노드를 temp로 설정
			lead -> llink = temp;  //lead의 이전 노드를 temp로 설정
			return 0;  //main으로 리턴
		}
	}  //temp를 가장 마지막 자리에 삽입하는 경우
	temp -> llink = middle;  //temp의 이전 노드를 middle로 설정
	temp -> rlink = h;  //temp의 다음 노드를 헤더노드로 설정
	middle -> rlink =temp;  //middle의 다음 노드를 temp로 설정
	h -> llink = temp;  //가장 마지막 노드를 temp로 설정
	return 0;  //main으로 리턴
}
/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {  //해당 키값을 갖는 노드를 찾으면 삭제하는 함수
	listNode * lead = h -> rlink;  //lead선언 후 가장 첫번째 노드를 가리키도록 설정
	listNode * middle = NULL;  //lead 이전 노드를 가리킬 middle 선언
	if(lead==h){  //노드가 없으면
		printf("삭제할 노드가 없습니다\n");
		return 0;
	}
	while(lead!=h){  //lead가 모든 노드를 탐색하고 다시 헤더노드를 가리킬 때까지 반복
		if(lead -> key ==key){  //키값이 같은 노드를 찾았다면
			if(!middle){  //첫번째 노드가 찾은 노드라면
				h -> rlink = h;  //가장 첫번째 노드를 헤더노드 자신으로 설정
				if((lead-> rlink)!=h){  //lead다음에도 노드들이 더 있다면
					h -> rlink = lead -> rlink;  //첫번째 노드를 lead 다음노드로 설정
					(lead -> rlink)-> llink = h;  //lead 다음 노드의 왼쪽 링크를 헤더노드로 설정
				}
			}
			else{  //두번째 자리 이상에서 노드를 찾았다면
				if((lead->rlink)==h){  //가장 마지막 자리였다면
					middle -> rlink = h;  //middle의 다음 노드를 헤더노드로 설정
					h -> llink = middle;  //가장 마지막 노드를 middle 로 설정
				}
				else{  //가장 마지막 자리가 아니었다면
					middle -> rlink = lead -> rlink;  //middle의 다음 노드를 lead의 다음 노드로 설정
					(lead -> rlink)->llink = middle;  //lead의 다음 노드의 왼쪽 링크를 middle로 설정
				}

			}
		free(lead);  //lead의 동적할당해제
		printf("key값을 찾았고 삭제하였습니다\n");  //키값 찾았다고 출력
		return 0;  //main으로 리턴
		}
	middle = lead;  //middle을 다음 노드를 가리키도록
	lead = lead -> rlink;  //lead가 다음 노드를 가리키도록
	}
	printf("key값을 찾지 못했습니다\n");  //조건문을 타지못했으므로 키값을 찾지 못함
	return 0;
}

