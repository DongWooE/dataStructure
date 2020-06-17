
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

void createGraph(Graph **graph);  //그래프를 만드는 함수
void insertVertex(Graph *graph);  //vertexlist가 null이 아님을 알려서 vertex가 존재하고 있음을 알리는 함수
void deleteVertex(Graph *graph);  //vertexlist 자리의 정보를 null로 만들어주는 함수
void destroyGraph(Graph **graph);  //동적할당받았던 graph
void printGraph(Graph *graph);
void insertEdge(Graph *graph);
void deleteEdge(Graph *graph);
void dfs(Graph *graph);
void bfs(Graph *graph);

int Stack[MAX_VERTEX_NUMBER];
int top = -1;
void push(int num);
int pop();

int Queue[MAX_VERTEX_NUMBER];
int front = -1;
int rear = -1;
void enqueue(int num);
int dequeue();

Vertex*flagNode();
void freeFlag(Vertex*flag);
void addNode(Graph *graph, int a, int b);
int cutNode(Graph *graph, int a, int b);

int boolGraph(Graph *graph);

int main(){
	char command;
	Graph *graph = NULL;
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
		createGraph(&graph);
		break;
	case 'f': case 'F':
		destroyGraph(&graph);
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
		destroyGraph(&graph);
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
int boolGraph(Graph *graph){
	if(!graph) return 0;
	return 1;
}
Vertex*flagNode(){
	Vertex* temp;
	temp = (Vertex*)malloc(sizeof(Vertex));
	temp -> link = NULL;
	return temp;
}
void freeFlag(Vertex*flag){
	free(flag);
}
void createGraph(Graph **graph){
	if(*graph){
		destroyGraph(graph);
	}
	Graph *temp=NULL;
	temp = (Graph*)malloc(sizeof(*temp));
	if(!temp){
		printf("메모리 공간이 충분하지않습니다\n");
		exit(1);
	}
	temp -> vlist = (VertexHead *)malloc(MAX_VERTEX_NUMBER*sizeof(VertexHead));
	if(!temp->vlist){
			printf("메모리 공간이 충분하지않습니다\n");
			exit(1);
		}

	for(int i =0; i< MAX_VERTEX_NUMBER;i++){
		temp -> vlist[i].head = NULL;
	}
	*graph = temp;
}
void insertVertex(Graph *graph){
	if(!boolGraph(graph)){
		printf("graph empty!\n");
		return;
	}
	int i;
	while(1){  //0~MAX_VERTEX_NUMBER까지의 숫자를 입력받을 때까지 반복
		printf("0 ~ %d까지의 숫자를 입력하세요 : ", MAX_VERTEX_NUMBER-1);
		scanf("%d",&i);
		if(i>=0 && i<=MAX_VERTEX_NUMBER-1){  //
			break;
			}
		}
	if(graph->vlist[i].head!=NULL){  //기존에 있는 것이면
		printf("이미 해당 vertex가 존재합니다\n");
		return;
	}
	graph->vlist[i].head = flagNode();
}
void printGraph(Graph *graph){
	int count = 0;
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	printf("\n========================================\n");
	printf("Vertex 출력\n");
	for(int i=0; i<MAX_VERTEX_NUMBER;i++){  //먼저 vertex 출력
		if(graph->vlist[i].head){
			printf(" %d ", i);
			count = 1;
		}
	}
	if(!count){
		printf("출력할 Vertex가 없습니다\n");
		printf("\n========================================\n");
		return;
	}
	printf("\n");
	printf("\n========================================\n");
	printf("Edge 출력\n");
	count = 0;
	for(int i=0; i< MAX_VERTEX_NUMBER;i++){
		if(graph->vlist[i].head!= NULL){
			Vertex *lead = graph->vlist[i].head->link;
			while(lead){
				if(i < lead->num)
					printf("( %d, %d) ", i, lead->num);
				lead = lead->link;
				count+=1;
				if(!count%10) printf("\n");
			}
		}
		}
	if(count == 0)
		printf("출력할 Edge가 없습니다\n");
	printf("\n");
}
void deleteVertex(Graph *graph){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	int search;
	printf("삭제하고자 하는 vertex number를 입력하세요 : ");
	scanf("%d", &search);
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){
		if(search == i){
			if(!graph->vlist[i].head){
				printf("해당 vertex가 존재하지않습니다\n");
				return;
			}
			else{
				Vertex*lead = graph->vlist[i].head->link;
				Vertex*prev = NULL;
				if(!lead){
					freeFlag(graph->vlist[i].head);
					graph->vlist[i].head = NULL;
					return;
				}
				while(lead){
					cutNode(graph,lead->num,i);
					prev = lead;
					lead = lead->link;
					free(prev);
				}
				graph->vlist[i].head = NULL;
			}
		}
	}
}
void addNode(Graph *graph, int a, int b){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	Vertex *temp = (Vertex*)malloc(sizeof(Vertex));
	if(!temp){
		printf("메모리가 충분하지않습니다\n");
		exit(1);
	}
	temp -> num = b;
	temp -> link = NULL;
	Vertex *lead; Vertex*prev = NULL;
	lead = graph->vlist[a].head->link;
	if(!lead){ graph->vlist[a].head->link = temp; return;}  //아무것도 없다면 그냥 link걸어버림
	else {
		if(lead->num == b){  //중복edge발생 방지
			free(temp);
			return;
		}
		if(lead->num > b){
			graph -> vlist[a].head->link = temp;
			temp->link = lead;
			return;
		}
		while(lead){
			if(lead->num > b){  //2번째 이상 자리에 들어갈 때
				prev -> link = temp;
				temp -> link  = lead;
				return;
			}
			prev = lead;
			lead = lead->link;
		}
	}
	prev -> link =temp;
}
void insertEdge(Graph *graph ){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	int a, b;
	printf("Edge를 입력하세요( vertex1 vertex2 ) : ");
	scanf("%d %d", &a, &b);
	if(a == b) {printf("self루프는 허용하지않습니다\n"); return;}
	if((!graph->vlist[a].head)||(!graph->vlist[b].head)){
		printf("해당 vertex가 존재하지않습니다\n");
		return;
	}
	addNode(graph,a,b);
	addNode(graph,b,a);
}
int cutNode(Graph *graph,int a,int b){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return 0;
		}
	Vertex *lead = graph->vlist[a].head->link;
	Vertex *prev = NULL;
	while(lead){
		if(lead->num == b){
			if(!prev) graph->vlist[a].head-> link = lead->link;
			else prev -> link = lead -> link;
			free(lead);
			return 1;
		}
		prev = lead;
		lead = lead->link;

	}
	return -1;

}
void deleteEdge(Graph *graph){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	int a, b;
	printf("Edge를 입력하세요( vertex1 vertex2 ) : ");
	scanf("%d %d", &a, &b);

	if(a == b){ printf("self루프는 존재하지않습니다\n"); return;};

	if((!graph->vlist[a].head)||(!graph->vlist[b].head)){
		printf("해당 vertex가 존재하지않습니다\n");
		return;
	}
	if(cutNode(graph, a, b)==-1){
		printf("해당 edge를 찾지못했습니다\n");
		return;
	}
		cutNode(graph, b, a);
}

void destroyGraph(Graph **graph){

	if(!boolGraph(*graph)) return;
	Graph *temp = *graph;
	for(int i = 0; i< MAX_VERTEX_NUMBER; i++){
		if(temp->vlist[i].head){
			Vertex*lead = temp->vlist[i].head->link;
			Vertex*prev =NULL;
			while(lead){
				prev = lead;
				lead = lead->link;
				free(prev);
			}
			freeFlag(temp->vlist[i].head);
		}
	}
	free(temp->vlist);  //먼저 vlist동적할당해제
	free(temp);  //그래프 동적할당해제
	*graph = NULL;
}

void dfs(Graph *graph){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	int num;
	printf("vertex를 입력하세요: ");
	scanf("%d", &num);

	Vertex* lead = graph->vlist[num].head;

		if(!lead){
			printf("해당 vertex가 존재하지않습니다\n");
			return;
		}
		if(!lead->link){
			printf(" %d\n", num);
			return;
		}

	int *flagStack = (int *)malloc(sizeof(int)*MAX_VERTEX_NUMBER);
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){  //flag 정보 초기화
		flagStack[i] = 0;
	}

	flagStack[num] = 1;  //visit마크 플래그 부여
	push(num);  //stack에 push
	lead = lead -> link;  //다음 vertex를 가리키도록 한다
	while(top>=-1){  //stack이 비어있을 떄까지 반복한다
		while(lead){  //인접리스트에서 null이 될 때까지 반복한다
		if(!flagStack[lead->num]){  //만약 전에 방문하지않았던 vertex이면
			flagStack[lead->num] = 1;  //visit마크 플래그 부여
			push(lead->num);  //stack에 push
			lead = graph->vlist[lead->num].head->link;
			continue;
		}
		//전에 방문했었던 vertex이면
			lead = lead -> link;
		}
		if(!lead){
			int index = pop();
			if(index == -1){ printf("\n"); return;}
			lead = graph->vlist[index].head->link;
		}
	}
	free(flagStack);
}
void push(int num){
	if(top >= STACK_SIZE){
		printf("STACK FULL\n");
		return;
	}
	Stack[++top] = num;
	printf(" %d ", Stack[top]);
}
int pop(){
	if(top <0){
		return -1;
	}
	int result = Stack[top --];
	return result;
}
void bfs(Graph *graph){
	if(!boolGraph(graph)){
			printf("graph empty!\n");
			return;
		}
	int num;
	printf("vertex를 입력하세요: ");
	scanf("%d", &num);

	Vertex* lead = graph->vlist[num].head;

		if(!lead){
			printf("해당 vertex가 존재하지않습니다\n");
			return;
		}
		if(!lead->link){
			printf(" %d\n", num);
			return;
		}

	int *flagStack = (int *)malloc(sizeof(int)*MAX_VERTEX_NUMBER);
	for(int i=0;i<MAX_VERTEX_NUMBER;i++){  //flag 정보 초기화
		flagStack[i] = 0;
	}
	flagStack[num] = 1;
	enqueue(num);
	while(1){
		int w = dequeue();
		if(w == -1){ printf("\n"); break;}
		printf(" %d ", w);
		lead = graph->vlist[w].head->link;
		while(lead){
			if(!flagStack[lead->num]){
				flagStack[lead->num] = 1;
				enqueue(lead->num);
				continue;
			}
			lead = lead->link;
		}
	}
	free(flagStack);
}

void enqueue(int num){
	rear = (rear+1)%MAX_VERTEX_NUMBER;
	if(rear == front){
		printf("Queue Full\n");
		return;
	}
	Queue[rear] = num;
}
int dequeue(){
	if(front == rear){
		return -1;
	}
	front = (front+1)%MAX_VERTEX_NUMBER;
	return Queue[front];
}






















