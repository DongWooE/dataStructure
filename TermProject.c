#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUMBER 20  //전체 vertex 수를 20개로 한정
#define STACK_SIZE 20  //dps에서 쓰일 stack의 사이즈를 20개로 한정
#define QUEUE_SIZE 20  //bps에서 쓰일 queue의 사이즈를 20개로 한정

typedef struct Vertex{  //각각의 vertex 정보를 저장하는 vertex구조체
	int num;
	struct Vertex *link;  //인접리스트에서 vertex끼리를 연결할 링크
}Vertex;

typedef struct VertexHead{  //인접리스트에서 각각의 vertex들의 링크를 나타낼 기준이 될 구조체
	Vertex *head;
}VertexHead;

typedef struct Graph{  //전체 그래프를 나타내는 그래프 구조체
	VertexHead *vlist;
}Graph;

void createGraph(Graph **graph);  //그래프를 만드는 함수, 포인터값 변경을 위해 더블 포인터로 인수 지정
void insertVertex(Graph *graph);  //vertexlist가 null이 아님을 알려서 vertex가 존재하고 있음을 알리는 함수
void deleteVertex(Graph *graph);  //vertexlist 자리의 정보를 null로 만들어주는 함수
void destroyGraph(Graph **graph);  //동적할당받았던 graph의 메모리를 반환해주는 함수, 포인터값 변경을 위해 더블 포인터로 인수 지정
void printGraph(Graph *graph);  //그래프의 vertex와 edge를 출력해주는 함수
void insertEdge(Graph *graph);  //edge를 추가해주는 함수
void deleteEdge(Graph *graph);  //edge를 삭제해주는 함수
void dfs(Graph *graph);  //depth first search, 깊이 우선 탐색 함수
void bfs(Graph *graph);  //breathe first search, 너비 우선 탐색 함수

int Stack[MAX_VERTEX_NUMBER];  //dfs에서 데이터를 저장해줄 stack
int top = -1;  //stack에서 가장 마지막에 들어온 원소를 나타내는 함수
void push(int num);  //stack에 원소를 추가해주는 함수
int pop();  //stack에서 원소 하나를 추출하는 함수

int Queue[MAX_VERTEX_NUMBER];  //bfs에서 데이터를 저장해줄 queue
int front = -1;  //queue의 앞을 나타내는 변수
int rear = -1;  //queue의 뒤를 나타내는 변수
void enqueue(int num);  //queue에 원소를 추가해주는 함수
int dequeue();  //queue에서 원소를 삭제해주는 함수

Vertex*flagNode();  //각각의 vlist자리에 vertex가 있음을 나타내는 flag를 추가해주는 함수
void freeFlag(Vertex*flag);  //flag노드를 동적할당해제해주는 함수
int addNode(Graph *graph, int a, int b);  //인접리스트의 각 연결리스트에서 node들의 정렬된 자리를 찾아서 알맞은 자리에 삽입해주는 함수
int cutNode(Graph *graph, int a, int b);  //인접리스트의 각 연결리스트에서 node들을 찾아서 삭제해주는 함수
int boolGraph(Graph *graph);  //graph 메모리가 존재하는지 알려주는 함수

int main(){
	char command;
	Graph *graph = NULL;  //graph 포인터를 선언하고 null값으로 초기화
do{
	printf("----------------------------------------------------------------\n");
	printf("                        Graph                       \n");
	printf("----------------------------------------------------------------\n");
	printf(" Create Graph      = g           Quit             = q\n");
	printf(" Destroy Graph     = f           Insert Edge   	  = e\n");
	printf(" Insert Vertex     = I           delete Edge      = w\n");
	printf(" Delete Vertex     = d           Print Graph      = p\n");
	printf(" Depth First Traversal      = t		           		    \n");
	printf(" Breathe First Traversal    = b          				\n");
	printf("----------------------------------------------------------------\n");

	printf("Command = ");
	scanf(" %c", &command);  //command값 입력 후 각각 경우에 따라 함수를 실행

	switch(command) {
	case 'g': case 'G':
		createGraph(&graph);  //포인터 변수에 메모리할당을 위해 더블포인터 사용하므로 해당 포인터 변수의 주소값을 인수로 넘긴다
		break;
	case 'f': case 'F':
		destroyGraph(&graph);  //동적할당받은 graph 포인터 변수의 메모리 반환을 위해 더블 포인터 사용을 위해 포인터 변수의 주소값을 인수로 넘긴다
		break;
	case 'i': case 'I':
		insertVertex(graph);
		break;
	case 'p': case 'P':
		printGraph(graph);
		break;
	case 'd': case 'D':
		deleteVertex(graph);
		break;
	case 'e': case 'E':
		insertEdge(graph);
		break;
	case 'w': case 'W':
		deleteEdge(graph);
		break;
	case 'q': case 'Q':
		destroyGraph(&graph);  //동적할당받은 graph 포인터 변수의 메모리 반환을 위해 더블 포인터 사용을 위해 포인터 변수의 주소값을 인수로 넘긴다
		break;
	case 't': case 'T':
		dfs(graph);
		break;
	case 'b': case 'B':
		bfs(graph);
		break;
	default:
		printf("\n       >>>>>   Concentration!!   <<<<<     \n");
		break;
	}

}while(command != 'q' && command != 'Q');
	return 0;
}
int boolGraph(Graph *graph){  //간단하게 graph에 메모리가 할당되어있는 지 확인해주는 함수
	if(!graph) return 0;
	return 1;
}
Vertex*flagNode(){  //각각의 vertex에 대해서 해당 vertex가 존재함을 알려주는 flag노드를 생성해주는 함수
	Vertex* temp;
	temp = (Vertex*)malloc(sizeof(Vertex));  //Vertex* 형 temp선언 후 메모리 할당
	temp -> link = NULL;  //flagNode는 단순히 vertex가 존재함을 알려주는 공간이므로 데이터를 따로 넣어주지않고 링크도 null로 초기화한다
	return temp;
}
void freeFlag(Vertex*flag){  //vertex존재함을 판별하기위해 만들어놓은 flagNode의 메모리를 반환해주는 함수
	free(flag);  //인수로 받은 Vertex형 포인터 변수의 메모리를 반환
}
void createGraph(Graph **graph){  //graph를 생성하는 함수
	if(*graph){  //만약 기존에 graph가 존재한다면 destroyGraph를 통해 메모리 반환
		destroyGraph(graph);
	}
	Graph *temp=NULL;  //graph 생성 용이를 위해 단일 포인터 temp 생성 후 초기화
	temp = (Graph*)malloc(sizeof(*temp));  //temp에 메모리 공간 할당
	if(!temp){  //동적할당과정에서 문제가 발생한다면
		printf("메모리 공간이 충분하지않습니다\n");
		exit(1);  //프로그램 종료
	}
	temp -> vlist = (VertexHead *)malloc(MAX_VERTEX_NUMBER*sizeof(VertexHead));  //인접리스트에서 각각의 vertex의 연결리스트를 저장할 vlist동적할당
	if(!temp->vlist){  //동적할당과정에서 문제가 발생한다면
			printf("메모리 공간이 충분하지않습니다\n");
			exit(1);  //프로그램 종료
		}

	for(int i =0; i< MAX_VERTEX_NUMBER;i++){  //할당받은 vlist에서 각각의 vertex 정보를 초기화한다
		temp -> vlist[i].head = NULL;
	}
	*graph = temp;  //graph가 가리키는 공간에 temp의 주소를 대입한다(graph가 temp를 가리키도록 설정한다)
}
void insertVertex(Graph *graph){  //vlist에서 vertexhead가 flagNode를 가리키게 해서 해당 vertex가 존재함을 알리게 하는 함수
	if(!boolGraph(graph)){  //graph생성 이전에 해당 함수를 실행할 경우를 걸러준다
		printf("graph empty!\n");
		return;
	}
	int i;
	while(1){  //0~MAX_VERTEX_NUMBER까지의 숫자를 입력받을 때까지 반복
		printf("0 ~ %d까지의 숫자를 입력하세요 : ", MAX_VERTEX_NUMBER-1);
		scanf("%d",&i);
		if(i>=0 && i<=MAX_VERTEX_NUMBER-1){  //해당 범위의 값이 들어왔을 경우에만 while문을 탈출할 수 있게 한다
			break;
			}
		}
	if(graph->vlist[i].head!=NULL){  //만약 기존에 해당 vertex가 존재한다면
		printf("이미 해당 vertex가 존재합니다\n");
		return;  //바로 원함수로 리턴한다
	}
	graph->vlist[i].head = flagNode();  //해당 vertex헤드에 flagNode의 주소를 대입하면서 해당 vertex가 존재한다는 것을 의미하게 한다
}
void printGraph(Graph *graph){  //전체 vertex와 edge 정보를 출력해주는 함수
	int count = 0;  //불필요한 정보가 출력되는 것을 막기위해 count 변수 선언
	if(!boolGraph(graph)){  //graph생성 이전에 해당 함수를 실행할 경우를 걸러준다
			printf("graph empty!\n");
			return;
		}
	printf("\n========================================\n");
	printf("Vertex 출력\n");
	for(int i=0; i<MAX_VERTEX_NUMBER;i++){  //vertex정보를 출력
		if(graph->vlist[i].head){  //vlist 자리에 flagNode가 존재하여 vertex가 존재할 경우
			printf(" %d ", i);
			count = 1;  //count를 1로 설정해준다
		}
	}
	if(!count){  //count값이 변하지않았으므로 위의 반복문에서 count값이 변경되지않은 것을 뜻한다, 그것은 곧 vertex가 존재하지않는다는 것을 뜻함
		printf("출력할 Vertex가 없습니다\n");
		printf("\n========================================\n");
		return;
	}
	printf("\n");
	printf("\n========================================\n");
	printf("Edge 출력\n");
	count = 0;  //count값을 초기화하여 재사용한다
	for(int i=0; i< MAX_VERTEX_NUMBER;i++){
		if(graph->vlist[i].head!= NULL){  //해당 vertex가 존재한다면
			Vertex *lead = graph->vlist[i].head->link;   //vertexlist 탐색을 위해 vertex형의 포인터 변수를 하나 선언해서 탐색한다
			while(lead){  //하나의 연결리스트 전체를 탐색
				if(i < lead->num){  //중복 출력을 막기위해 어떤 edge(a,b) a <b인 경우만 출력한다
					printf("( %d, %d) ", i, lead->num);
					count +=1;  //count값을 증가시켜준다
					if(count%10==0) printf("\n");  //edge가 한 줄에 10의 배수만큼 출력되면 다음줄에 출력한다
				}
				lead = lead->link;  //lead의 링크값 변경
			}
		}
		}
	if(count == 0)  //count가 0이라는 것은 위의 반복문을 들어가지않은 것이므로 edge가 존재하지않는다는 의미이다
		printf("출력할 Edge가 없습니다\n");
	printf("\n");
}
void deleteVertex(Graph *graph){  //vertex를 삭제하는 함수
	if(!boolGraph(graph)){  //graph생성 이전에 해당 함수를 실행할 경우를 걸러준다
			printf("graph empty!\n");
			return;
		}
	int search;  //vertex를 찾기위한 변수
	printf("삭제하고자 하는 vertex number를 입력하세요 : ");
	scanf("%d", &search);  //찾고자하는 vertex입력
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){  //해당 vertex를 찾는 함수, vlist의 flagNode유무를 탐색
		if(search == i){  //search와 같은 i값을 찾았을 때
			if(!graph->vlist[i].head){  //vlist flagNode가 존재하지않을 때
				printf("해당 vertex가 존재하지않습니다\n");
				return;
			}
			else{  //vlist의 flagNode가 존재할 때
				Vertex*lead = graph->vlist[i].head->link;  //vlist에 연결된 리스트 탐색을 lead 선언
				Vertex*prev = NULL;  //lead의 전 노드를 가리킬 prev선언
				if(!lead){  //연결된 리스트가 없다면, 연결된 edge가 존재하지않다면
					freeFlag(graph->vlist[i].head);  //flagNode 동적할당해제
					graph->vlist[i].head = NULL;  //vlist를 null값으로 만들어서 해당 vlist에 vertex가 없음을 알린다
					return;
				}
				while(lead){  //리스트 마지막 노드까지 탐색
					cutNode(graph,lead->num,i);  //cutNode함수를 불러서 edge로 연결된 다른 노드에서도 i vertex정보를 삭제해준다
					prev = lead;  //노드의 정보를 변경시켜준다
					lead = lead->link;
					free(prev);  //cutNode를 통해서 다른 리스트에서도 vertex정보를 삭제해주었다면 리스트에서 edge 정보를 free해준다
				}
				graph->vlist[i].head = NULL;  //vlist정보를 null값으로 설정하면서 해당 vertex가 존재하지않음을 알린다
			}
		}
	}
}
int addNode(Graph *graph, int a, int b){  //리스트에 vertex정보를 정렬 후 추가해주는 함수
	Vertex *temp = (Vertex*)malloc(sizeof(Vertex));  //추가할 vertex 정보를 저장할 공간을 동적할당
	if(!temp){  //동적할당과정에서 문제 발생시 비정상종류
		printf("메모리가 충분하지않습니다\n");
		exit(1);
	}
	temp -> num = b;  //temp의 num정보에 인수로 받은 b값 대입
	temp -> link = NULL;  //temp의 링크 정보를 null로 세팅
	Vertex *lead; Vertex*prev = NULL;  //리스트 정보를 탐색할 lead와 prev선언
	lead = graph->vlist[a].head->link;  //a의 vlist의 edge 탐색
	if(!lead){ graph->vlist[a].head->link = temp; return 1;}  //edge가 아무것도 없다면 바로 temp를 연결한다
	else {
		if(lead->num == b){  //만약 b와 같은 edge가 존재한다면 중복이 일어난 경우이므로 바로 free해준다
			free(temp);
			return -1;
		}
		if(lead->num > b){  //리스트 첫번쨰 원소가 b보다 커서 리스트 가장 첫번쨰 자리에 temp가 들어가야할 경우
			graph -> vlist[a].head->link = temp;  //바로 첫번째 자리에 temp 대입
			temp->link = lead;  //temp의 링크정보도 수정해준다
			return 1;
		}
		while(lead){  //가장 마지막 노드까지 탐색한다
			if(lead->num == b){  //중복 엣지 방지를 위해 바로 free진행
						free(temp);
						return -1;
					}
			else if(lead->num > b){  //노드 사이에 temp를 넣어야할 때
				prev -> link = temp;  //이전 노드의 링크를 temp로
				temp -> link  = lead;  //temp의 링크를 lead로 설정
				return 1;
			}
			prev = lead;  //링크 정보 수정
			lead = lead->link;
		}
	}  //만약 b값보다 큰 값이 리스트에 없어서 가장 마지막 자리에 위치해야할 때
	prev -> link =temp;  //lead는 null이므로 prev의 다음 노드를 temp로 설정한다
	return 1;
}
void insertEdge(Graph *graph ){  //edge정보를 추가해주는 함수
	if(!boolGraph(graph)){  //만약 graph자체가 동적할당받지않았다면 바로 리턴
			printf("graph empty!\n");
			return;
		}
	int a, b;  //2개의 edge가 될 vertex의 정보를 저장할 a 와 b 선언
	printf("Edge를 입력하세요( vertex1 vertex2 ) : ");
	scanf("%d %d", &a, &b);
	if(a == b) {printf("self루프는 허용하지않습니다\n"); return;}  //그래프에서는 self loop는 허용하지않으므로 a와 b가 같으면 바로 리턴
	if((!graph->vlist[a].head)||(!graph->vlist[b].head)){  //두개의 vertex 중에 하나라도 존재하지않는 vertex입력 시에도 바로 리턴
		printf("해당 vertex가 존재하지않습니다\n");
		return;
	}
	if(addNode(graph,a,b)==-1) printf("이미 해당 edge가 존재합니다\n");  //addNode에서 중복엣지 존재할 시에는 1값을 리턴하므로 중복엣지가 존재한다는 것을 알린다
	addNode(graph,b,a);  //무방향그래프이므로 각각의  vlist 리스트에 vertex정보를 추가해줘야하므로 변수 2개의 위치를 바꿔가며 호출한다
}
int cutNode(Graph *graph,int a,int b){  //deleteVertex에 의해서 vertex가 삭제될 때 edge의 또 다른 vertex의 리스트에서 해당 vertex정보를 삭제해주는 함수
	Vertex *lead = graph->vlist[a].head->link;  //vlist에서 처음 edge 리스트를 가리키는 포인터 변수 선언
	Vertex *prev = NULL;  //lead 이전 노드를 가리킬 prev 선언
	while(lead){  //리스트 마지막 노드까지 탐색
		if(lead->num == b){  //해당 vertex를 찾았다면
			if(!prev) graph->vlist[a].head-> link = lead->link;  //만약 그 자리가 리스트 가장 첫번째 원소였을 경우에 lead의 다음 링크를 vlist의 첫번째 노드로 설정한다
			else prev -> link = lead -> link;  //두번째 이상 자리에, 노드 중간에 위치했을 경우 이전 노드의 링크를 lead 다음 링크로 해준다
			free(lead);  //lead를 free해준다
			return 1;
		}
		prev = lead;  //노드의 링크 정보를 변경해준다
		lead = lead->link;
	}
	return -1;

}
void deleteEdge(Graph *graph){  //edge정보를 삭제해주는 함수
	if(!boolGraph(graph)){  //graph가 존재하지않는 다면 바로 리턴
			printf("graph empty!\n");
			return;
		}
	int a, b;  //두 개의 vertex 정보를 담을 변수 선언
	printf("Edge를 입력하세요( vertex1 vertex2 ) : ");
	scanf("%d %d", &a, &b);

	if(a == b){ printf("self루프는 존재하지않습니다\n"); return;};  //그래프에서 self loop허용하지않으므로 바로 return

	if((!graph->vlist[a].head)||(!graph->vlist[b].head)){  //두 개의 vertex 중 하나라도 vlist flagNode가 존재하지않는다면, 현재 그래프에서 vertex가 존재하지않는다면
		printf("해당 vertex가 존재하지않습니다\n");
		return;
	}
	if(cutNode(graph, a, b)==-1){  //cutNode에서 해당 vertex들을 찾지못해서 -1을 리턴했을 경우
		printf("해당 edge를 찾지못했습니다\n");
		return;
	}
		cutNode(graph, b, a);  //무방향 그래프에서는 2개의 변수에 중복된 edge정보가 존재하므로 두 개의 변수 순서를 바꿔서 다시 호출한다
}

void destroyGraph(Graph **graph){  //전체 그래프 정보를 free해주는 함수

	if(!boolGraph(*graph)) return;  //free할 그래프가 없다면 바로 리턴
	Graph *temp = *graph;  //temp 포인터 변수를 선언해서 graph 정보를 대입한다
	for(int i = 0; i< MAX_VERTEX_NUMBER; i++){  //먼저 vlist 리스트 정보를 free해준다
		if(temp->vlist[i].head){  //vlist에 vertex정보가 존재한다면
			Vertex*lead = temp->vlist[i].head->link;  //리스트의 첫번째 노드를 가리킬 포인터변수 lead선언
			Vertex*prev =NULL;  //lead의 이전 노드 정보를 가리킬 prev변수 선언
			while(lead){  //가장 마지막 노드까지 탐색
				prev = lead; //링크 정보를 계속 수정
				lead = lead->link;
				free(prev);  //이전 노드를 계속 free해준다
			}
			freeFlag(temp->vlist[i].head);  //리스트 정보를 모두를 free해준 뒤 flagNode를 free해준다
		}
	}
	free(temp->vlist);  //전체 20개의 vlist 배열을 동적할당해제
	free(temp);  //그래프 동적할당해제
	*graph = NULL;  //그래프가 가리키는 값을 null로 설정
}

void dfs(Graph *graph){  //깊이우선탐색 함수
	if(!boolGraph(graph)){  //traversal한 그래프가 존재하지않는다면 바로 리턴
			printf("graph empty!\n");
			return;
		}
	int num;  //traversal의 기준이 될 vertex 입력
	printf("vertex를 입력하세요: ");
	scanf("%d", &num);

	Vertex* lead = graph->vlist[num].head;  //num번째 vlist를 가리키는 lead 포인터 변수 선언

		if(!lead){  //만약 해당 vlist에 flagNode가 존재하지않는다면 그냥 리턴
			printf("해당 vertex가 존재하지않습니다\n");
			return;
		}
		if(!lead->link){  //만약 edge리스트가 존재하지않는다면 vertex만 출력한다
			printf(" %d\n", num);
			return;
		}
	int *flagStack = (int *)malloc(sizeof(int)*MAX_VERTEX_NUMBER);  //visiting flag를 저정할 배열을 동적할당
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){  //visiting flag 정보 초기화
		flagStack[i] = 0;
	}
	flagStack[num] = 1;  //먼저 num의 visit마크 플래그 부여
	push(num);  //num에 stack에 push
	while(1){
		if(top<0){printf("\n"); break;}  //stack이 비어있을 때 break
		lead = graph->vlist[Stack[top]].head->link;  //lead에 현재 스택의 top에 위치한 vlist의 링크를 대입해준다
		while(lead){  //리스트의 마지막 노드까지 탐색
		if(!flagStack[lead->num]){  //만약 전에 방문하지않았던 vertex이면
			flagStack[lead->num] = 1;  //visiting flag 부여
			push(lead->num);  //stack에 push
			break;  //반복문 탈출
			}
		else{  //전에 방문했던 vertex라면
			lead = lead -> link;  //리스트의 다음 노드를 가리키게 설정
			}
		}
	if(!lead) {int index = pop();}  //만약 lead가 null이 되어서 while문을 탈출한다면 stack에서 한 개의 원소를 추출한다
}
	free(flagStack);  //모든 traversal이 끝났다면 flag 배열의 메모리를 반환한다
}
void push(int num){  //stack에 원소를 삽입하는 함수
	if(top >= STACK_SIZE){  //만약 top이 stacksize보다 크게 된다면 스택이 꽉 찼으므로 리턴한다
		printf("STACK FULL\n");
		return;
	}
	Stack[++top] = num;  //스택에 빈공간이 있다면 top값을 증가시켜준 후 num을 삽입해준다
	printf(" %d ", Stack[top]);  //preorder방식으로 stack에 push된 원소를 바로 print해준다
}
int pop(){  //stack에 원소를 빼주는 함수
	if(top <0){  //만약 top이 0보다 작게 된다면 스택이 비어있다는 의미이므로 바로 리턴한다
		return -1;
	}
	int result = Stack[top--];  //top값을 감소시켜준 다음에 result변수에 대입 후 리턴한다
	return result;
}
void bfs(Graph *graph){  //너미우선탐색
	if(!boolGraph(graph)){  //graph가 생성되기 이전이라면 바로 리턴
			printf("graph empty!\n");
			return;
		}
	int num;  //traversal의 기준이 될 노드의 정보가 저장될 변수
	printf("vertex를 입력하세요: ");
	scanf("%d", &num);

	Vertex* lead = graph->vlist[num].head;  //입력받은 num번째 vlist의 리스트 원소를 가리키는 포인터 변수 선언

		if(!lead){  //만약 해당 vlist자리에 flagNode가 존재하지않는다면 바로 리턴
			printf("해당 vertex가 존재하지않습니다\n");
			return;
		}
		if(!lead->link){  //해당 vlist에 edge가 존재하지않는다면 바로 리턴
			printf(" %d\n", num);
			return;
		}
	int *flagStack = (int *)malloc(sizeof(int)*MAX_VERTEX_NUMBER);  //visiting flag를 저장할 배열을 동적할당
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){  //전체 visiting flag 정보 초기화
		flagStack[i] = 0;
	}
	flagStack[num] = 1;  //num번째 vlist는 방문했으므로 visiting flag정보를 최신화한다
	enqueue(num);  //queue에 num을 넣어준다
	while(1){  //큐가 empty상황이면 무한루프를 빠져나오도록 설정
		int w = dequeue();  //먼저 큐에서 원소 하나를 빼준 후 변수에 저장
		if(w == -1){ printf("\n"); break;}  //-1이 리턴되었다는 것은 큐가 empty인 상황이므로 break한다
		printf(" %d ", w);
		lead = graph->vlist[w].head->link;  //lead가 큐에서 빼낸 원소의 vlist 리스트를 가리키도록 설정한다
		while(lead){  //리스트에서 가장 마지막 노드까지 탐색한다
			if(!flagStack[lead->num]){  //만약 방문하지않은 노드라면
				flagStack[lead->num] = 1;  //visiting flag정보를 수정해준다
				enqueue(lead->num);  //큐에 해당 원소들을 삽입해준다
				continue;  //다시 반복문으로 올라간다
			}
			lead = lead->link;  //링크정보를 수정한다
		}
	}
	free(flagStack);  //모든 traversal이 끝났을 경우 visiting flag정보를 free해준다
}

void enqueue(int num){  //원형큐에 원소를 추가하는 함수
	rear = (rear+1)%MAX_VERTEX_NUMBER;  //큐의 마지막 원소를 가리키는 rear값을 증가 후 modulo연산 수행
	if(rear == front){  //만약 modulo연산 후 2개의 값이 같다면 queue가 찼으므로 return
		printf("Queue Full\n");
		return;
	}
	Queue[rear] = num;  //큐에 여유공간이 있다면 num값을 추가
}
int dequeue(){  //원형큐에 원소를 삭제하는 함수
	if(front == rear){  //큐가 empty한 상황이라면
		return -1;  //-1을 리턴해서 큐가 empty인 상황을 알려준다
	}
	front = (front+1)%MAX_VERTEX_NUMBER;  //front값을 증가 후 modulo연산 수행 후
	return Queue[front];  //queue의 해당 인덱스의 원소를 반환한다
}
