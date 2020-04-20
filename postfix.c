#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen ,  /* ( 왼쪽 괄호 */
	rparen ,  /* ) 오른쪽 괄호*/
	times ,   /* * 곱셈 */
	divide ,  /* / 나눗셈 */
	plus ,    /* + 덧셈 */
	minus ,   /* - 뺄셈 */
	operand  /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	//infix expression을 저장하는 배열
char postfixExp[MAX_EXPRESSION_SIZE];	//postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];	//postfix로 변환을 위해 필요한 스택
int evalStack[MAX_STACK_SIZE];  //evalStack용 배열
int postfixStackTop = -1;  //postfixStack용 top
int evalStackTop = -1;  //evalStack용 top
int evalResult = 0;  //연산결과

static int isp[]={0,19,13,13,12,12,1};  //함수 내에서의 우선순위
static int icp[]={20,19,13,13,12,12,1};  //함수 밖에서의 우선순위
static int eval[]={0,9,7,6,5,4,1};  //계산 시 식별자

void postfixPush(char x)  //postfixStack에 push하는 함수
{
    postfixStack[++postfixStackTop] = x;  //top을 +1해주고 인수로 받아온 x를 대입
}

char postfixPop()  //postfixStack에 pop하는 함수
{
    char x;
    if(postfixStackTop == -1)  //top이 음수인 경우
        return '\0';  //null리턴
    else  //top이 0이거나 이상일 경우
    	x = postfixStack[postfixStackTop--];  //x에 현재 top번째 배열의 원소 출력 후 top--

    return x;  //x 리턴
}
void evalPush(int x)  //evalStack에서 push하는 함수
{
    evalStack[++evalStackTop] = x;  //top을 +1해주고 인수로 받아온 x를 대입
}

int evalPop()  //evalStack에서 pop하는 함수
{
    if(evalStackTop == -1)  //top이 음수인 경우
        return -1;  //-1을 리턴
    else{ //top이 0이거나 이상일 경우
        return evalStack[evalStackTop--];   //현재 top번째 배열의 원소 리턴 후 top--
    }
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()  //infixExp를 입력받는 함수
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);  //infixExp를 문자열 형태로 입력받기
}

precedence getToken(char symbol)  //연산자 또는 피연사자를 인수로 가져와 특정 니모닉을 반환하는 함수
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x)  //우선순위를 반환해주는 함수
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)  //문자 변수의 주소를 받아서 postfixExp에 추가하는 함수
{
	if (postfixExp == '\0')  //postfixExp가 비어있는 경우
		strncpy(postfixExp, c, 1);  //문자 c를 1만큼 바로 복사
	else  //비어있지않은 경우
		strncat(postfixExp, c, 1);  //문자 c를 1만큼 postfixExp 뒤에 붙여넣기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		precedence data;  //precedence 형의 변수 data 선언
		x=*exp;  //exp로부터 문자 하나를 읽어 x에 대입
		data = getPriority(x);  //data값에 우선순위 기호 대입
		if(isp[data] == 1){  //data가 operand 이면
			charCat(&x);  //PostfixExp 배열에 대입
		}
		else{  //data가 operand가 아닌 경우
			if(isp[data] == 0)  //왼쪽 괄호(lparen)인 경우
				postfixPush(x);  //stack에 push
			else if(isp[data] == 19){  //오른쪽 괄호(rparen)인 경우
			while(postfixStack[postfixStackTop]!='('){  //스택내에서 lprean이 나올 때 까지
				char y = postfixPop();  //pop한 값을 문자형 y에 대입
				charCat(&y);  //y를 PostfixExp 배열에 대입
				}
			postfixStack[postfixStackTop]='\0';  //stack내에서 '('삭제
			postfixPop();  //'('을 pop해줌으로서 top-1해줌
			}
			else {  //lparen 과 rparen 이 아닌 다른 연산자일 때
				precedence compare;  //precedence형 compare 변수 선언
				if(postfixStackTop<0)  //top이 음수인 경우
					postfixPush(x);  //문자 x 를 바로 push
				else{  //top이 음수가 아닌 경우
					compare = getPriority(postfixStack[postfixStackTop]);  //compare에 top이 위치한 스택의 원소값을 기호로 바꿔서 대입
					if(isp[compare] >= icp[data]){  //compare의 우선순위가 들어오는 data의 우선순위보다 크거나 같으면
						char z =postfixPop();  //z에 pop한 원소를 대입
						charCat(&z);  //z를 PostfixExp배열에 대입한 후
						postfixPush(x);  //문자 x 를 push
					}
					else{  //compare의 우선순위가 들어오는 data의 우선순위보다 작으면
						postfixPush(x);  //문자 x를 push
					}
				}
			}
		}
		exp++;  //infixExp에서 다음 문자를 가리키도록 함
		}//infixExp배열에서 더 이상 문자가 없으면
		for(int i=postfixStackTop;i>=0; i--){  //i가 top에서 0까지
			char y = postfixStack[postfixStackTop];  //stack에서 top번째 원소를 y에 대입
			charCat(&y);  //y를 postfixExp배열에 대입
			postfixPop();  //stack에서 top이 가리키는 원소 pop
		}

	}
void debug()  //진행결과를 출력해주는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);  //infix 출력
	printf("postExp =  %s\n", postfixExp);  //postfix 출력
	printf("eval result = %d\n", evalResult);  //연산결과 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);  //postfixStack에 담긴 내용을 출력

	printf("\n");

}

void reset()  //이전 데이터를 삭제해주는 함수
{
	infixExp[0] = '\0';  //infixExp 초기화
	postfixExp[0] = '\0';  //postfixExp 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';  //postfixStack 초기화

	postfixStackTop = -1;  //postfix용 top 초기화
	evalStackTop = -1;  //eval용 top 초기화
	evalResult = 0;  //연산결과 초기화

}

void evaluation()
{
	char x;  //문자형 변수 x 선언
	char * exp = postfixExp;  //postfixExp배열을 가리키는 문자형 포인터 변수 exp선언
	precedence data;  //enum의 precedence 형 변수 data 선언
	while(*exp!=0){  //postfixExp의 배열 끝이 아니면
		x=*exp;  //문자형 변수에 postfixExp로부터 한 문자씩 받아서 대입
		data = getToken(x);  //x를 기호화한 값을 data에 대입
		if(eval[data] == 1)  //operation이면
			evalPush(x-'0');  //문자 x에 문자 0을 뺀 값을 push(문자형 변수를 문자 그대로 정수화한것)
		else{  //operator이면
			int x =evalPop();  //정수형 변수 x에 evalstack에서 push한 값 대입
			int y= evalPop();  //정수형 변수 y에 evalstack에서 push한 값 대입
			switch(eval[data]){  //연산자를 다시 수치화 한 것을 비교
			case 5:  //연산자가 +이면
				evalPush(y+x);  //둘을 더한 값을 push
				break;
			case 4:  //연산자가 -이면
				evalPush(y-x);  //둘을 뺀 값을 push
				break;
			case 7:  //연산자가 *이면
				evalPush(y*x);  //둘을 곱한 값을 push
				break;
			case 6:  //연산자가 /이면
				evalPush(y/x);  //둘을 나눈 값을 push
				break;
			default:  //이외의 것(나올 리는 없지만)
				break;
			}
		}
		exp++;  //포인터를 +1하여 postfixExp에서 가리키는 값을 한 칸 뒤로 움직임
	}
	evalResult= evalPop();  //Pop한 값을 연산결과에 대입
}


int main()
{
	printf("=====[2017038069]=====[이동우]=====\n");  //학번 이름 출력
	char command;
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //command값 입력

		switch(command) {
		case 'i': case 'I':  //command가 i면
			getInfix();  //infix를 받는 함수로 이동
			break;
		case 'p': case 'P':  //command가 p이면
			toPostfix();  //postfix로 변환하는 함수로 이동
			break;
		case 'e': case 'E':  //command가 e면
			evaluation();  //evaluation하는 함수로 이동
			break;
		case 'd': case 'D':  //command가 d이면
			debug();  //전체 과정을 출력하는 함수로 이동
			break;
		case 'r': case 'R':  //command가 r이면
			reset();  //기존 데이터를 삭제하는 함수로 이동
			break;
		case 'q': case 'Q':  //command가 q면
			break;
		default:  //이외의 값이면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');  //command가 q가 아닐 때까지 반복

	return 0;

}
