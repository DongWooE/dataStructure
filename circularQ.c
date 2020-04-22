#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  //전체 원형 큐의 숫자

typedef char element;  //typedef를 통해 char 데이터형의 element 선언
typedef struct {  //typedef를 통해 QueueType 형의 struct 선언
	element queue[MAX_QUEUE_SIZE];  //4개의 크기를 가지는 char형 queue배열 선언
	int front, rear;  //정수형 변수 front, rear 선언
}QueueType;


QueueType *createQueue();  //구조체 포인터변수를 동적할당하여 만드는 함수
int isEmpty(QueueType *cQ);  //포인터 변수가 가리키는 원형큐가 비어있는 지 확인해주는 함수
int isFull(QueueType *cQ);  //포인터 변수가 가리키는 원형큐가 가득차있는 지 확인해주는 함수
void enQueue(QueueType *cQ, element item);  //포인터 변수가 가리키는 큐에 원소를 추가하는 함수
void deQueue(QueueType *cQ, element *item);  //포인터 변수가 가리키는 큐에 원소를 제거하는 함수
void printQ(QueueType *cQ);  //포인터 변수가 가리키는 원형 큐를 출력해주는 함수
void debugQ(QueueType *cQ);  //포인터 변수가 가리키는 원형 큐의 front, rear 와 원소를 출력해주는 함수
void freeQueue(QueueType *cQ); //동적할당해제해주는 함수

element getElement();  //원형큐에 원소를 받는 함수


int main(void)
{
	QueueType *cQ = createQueue();  //구조체 포인터 cQ를 선언하고 동적할당 후 멤버변수 front 와 rear 값 초기화
	element data;  //element 형(char 형) data 변수 선언
	printf("=====[2017038069]=====[이동우]=====\n");  //학번과 이름 출력
	char command;   //char 형 command 변수 선언

	do{
		printf("\n-----------------------------------------------------\n");  //메뉴 출력
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //command 입력받음

		switch(command) {  //command 값을 비교
		case 'i': case 'I':  //command가  i 또는 I 이면
			data = getElement();  //getElemnet()함수를 통해 data값을 입력받고
			enQueue(cQ, data);  //포인터 변수 cQ와 입력받은 data를 인수로 보내서 원형큐의 원소로 넣어줌
			break;  //switch 문 나가기
		case 'd': case 'D':  //command가 d 또는 D 이면
			deQueue(cQ,&data);  //포인터 변수 cQ와 입력받은 data의 주소를 인수로 보내 원형큐의 원소를 제거
			break;  //switch 문 나가기
		case 'p': case 'P':  //command가 p 또는 P 이면
			printQ(cQ);  //해당 포인터가 가리키는 배열의 원소를 출력
			break;  //switch 문 나가기
		case 'b': case 'B':  //command가 b 또는 B 이면i
			debugQ(cQ);  //해당 포인터가 가리키는 배열의 원소와 멤버 변수 값 출력
			break;  //switch 문 나가기
		case 'q': case 'Q':  //command가 q 또는 Q 이면
			break;  //switch 문 나가기
		default:  //command가 이외의 것이면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;  //switch 문 나가기
		}
	}while(command != 'q' && command != 'Q');  //command가 q 또는 Q이면 반복문 탈출
	freeQueue(cQ);  //cQ 동적할당 해제
	return 0;
}


QueueType *createQueue()  //동적할당한 QueueType형의 포인터 변수를 반환하는 함수
{
	QueueType *cQ;  //QueueType의 포인터 변수 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));  //cQ를 구조체 QueueType형의 크기만큼 heap 영역에서 동적할당함
	cQ->front = 0;  //멤버변수 front 값 0 으로 초기화
	cQ->rear = 0;  //멤버변수 rear 값 0 으로 초기화
	return cQ;  //구조체 포인터 변수 cQ 반환
}

element getElement()  //element형의 변수를 입력받고 반환하는 함수
{
	element item;  //element형 변수 item 선언
	printf("Input element = ");
	scanf(" %c", &item);  //element형 변수 item 입력
	return item;  //element형 변수 item 반환
}


int isEmpty(QueueType *cQ)  //QueueType의 포인터변수를 인수로 받아 멤버배열이 비어있는 지 확인하는 함수
{  //front의 바로 앞에 있는 원소가 비어있는 지 확인
	int p_front;  //int형 변수 p_front 선언
	p_front=(cQ->front+1)%MAX_QUEUE_SIZE;  //p_front에 멤버변수 front값에 1을 더하고 큐사이즈(4)로 나눈 나머지값을 대입
	if(cQ->queue[p_front]=='\0')  //멤버배열의 p_front(원형큐에서 front에 하나 뒤에 있는 값)번째 원소가 비어있으면
		return 0;  //0을 리턴
	else  //멤버배열의 p_front(원형큐에서 front에 하나 뒤에 있는 값)번째 원소가 비어있지않으면
		return 1;  //1을 리턴
}

int isFull(QueueType *cQ)  //QueueType의 포인터변수를 인수로 받아 멤버배열이 모두 차있는 지 확인하는 함수
{  //front의 바로 뒤에 있는 원소가 차있는 지 확인
	int p_front;  //int형 변수 p_front 선언
	if(cQ->front-1<0)  //멤버변수 front-1이 0보다 작으면 (front값이 0이라서 -1했을 때 음수가 나오면)
		p_front=3;  //p_front에 3대입
	else  //front값이 0이 아니라면
		p_front=(cQ->front-1)%MAX_QUEUE_SIZE;  //p_front에 멤버변수 front값에 1을 빼고 큐사이즈(4)를 나눈 나머지값을 대입
	if(cQ->queue[p_front]!='\0'){  //p_front번째의 멤버배열(front보다 뒤에 있는 배열의 원소가 있다면)이 비어있지않다면
		cQ->rear=p_front;  /*rear값에 p_front값 대입(enQueue함수에서 +1해진 rear값을 다시 -1하여
		함수에 들어왔을 때로 만들고 값을 고정시켜서 front값을 넘어가지못하도록 함*/
		return 0;  //0을 리턴
	}
	else  //p_front번째의 멤버배열(front보다 뒤에 있는 배열의 원소가 없다면)이 비어있다면
		return 1;  //1을 리턴
}


void enQueue(QueueType *cQ, element item){  /*QueueType의 포인터 변수와 element형의 변수를 인수로 받아 원형큐에 값을 넣어주는 함수*/
	cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE;  //modulo 연산을 사용해 멤버변수 rear값에 rear+1을 큐 사이즈(4)로 나눈 나머지값을 대입
	if(cQ->rear == cQ->front){  //멤버변수 rear 값과 front값이 같다면
		if(!isFull(cQ)){  //isFull함수를 호출해서 결과값이 리턴값이 0이면 (not 0이므로 true)
			printf("The function is Full\n");  //함수가 다 찼다고 출력하고
			return;  //함수를 끝냄
		}
	}
	cQ->queue[cQ->rear]=item;  //rear번째 queue 멤버배열에 item(입력받았던 data)값을 대입
}

void deQueue(QueueType *cQ, element *item){  /*QueueType의 포인터 변수와 element형의 포인터를 인수로 받아 원형큐에 값을 제거해주는 함수*/
	if(cQ->front==cQ->rear){  //멤버변수 rear값과 front값이 같다면
		if(!isEmpty(cQ)){  //isEmpty함수를 호출해서 리턴값이 0이면 (not 0이므로 true)
			printf("The function is Empty");  //함수가 비어있다고 출력
			return;  //함수를 끝냄
		}
	}
	cQ->queue[cQ->front]='\0';  //front번째의 멤버배열 queue에 \0값을 대입(비게 만듦)
	cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE;  //modulo 연산을 사용해 멤버변수 front값에 front+1을 큐 사이즈(4)로 나눈 나머지값을 대입
}

void printQ(QueueType *cQ){  //QueueType의 포인터 변수를 인수로 받아 해당 포인터 변수가 가리키는 멤버배열을 출력하는 함수
	int i, first, last;  //정수형 변수 i, first, last 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;  //modulo 연산을 사용해 first에 front+1을 큐 사이즈(4)로 나눈 나머지값을 대입
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;  //modulo 연산을 사용해 last값에 rear+1을 큐 사이즈(4)로 나눈 나머지값을 대입

	printf("Circular Queue : [");

	i = first;  //i에 first값 대입
	while(i != last){  //i와 last값이 같지않다면
		printf("%3c", cQ->queue[i]);  //3개 너비의 칸에 멤버배열 queue의 i번째 원소를 출력
		i = (i+1)%MAX_QUEUE_SIZE;   //modulo 연산을 사용해 i에 i+1을 큐 사이즈(4)로 나눈 나머지값을 대입

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ){  //QueueType의 포인터 변수를 인수로 받아 해당 포인터 변수가 가리키는 멤버배열의 값과 멤버변수 값 출력해주는 함수

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)  //i가 큐 사이즈까지
	{
		if(i == cQ->front) {  //i와 멤버변수 front 값이 같다면
			printf("  [%d] = front\n", i);  //front 값 출력
			continue;  //다시 for문으로 돌아가기
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);  //i와 멤버배열 queue의 i번째 원소 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);  //멤버변수 front와 rear값을 출력
}
void freeQueue(QueueType *cQ){ //동적할당해제해주는 함수

	printf("동적할당 해제합니다");
	free(cQ);  //동적할당해제
}
