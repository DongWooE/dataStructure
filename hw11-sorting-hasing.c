#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //랜덤으로 숫자를 뽑아야하므로 time.h를 포함

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);  //배열을 초기화해주는 함수
int freeArray(int *a);  //동적으로 할당받은 메모리를 반환해주는 함수
void printArray(int *a);  //배열을 출력해주는 함수

int selectionSort(int *a);  //선택정렬함수
int insertionSort(int *a);  //삽입정렬함수
int bubbleSort(int *a);  //버블정렬함수
int shellSort(int *a);  //셸정렬함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);  //퀵정렬함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);  //key값을 해시테이블에 올리기위해 주소를 계산해주는 함수

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);  //hashtable에 데이터들을 올려주는 함수

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);  //hashtable에 key값이 있는지 탐색해주는 함수


int main()
{
	char command;
	int *array = NULL;   //배열을 가리키는 포인터 변수
	int *hashtable = NULL;  //hashtable을 가리키는 포인터 변수
	int key = -1;  //search함수에서 사용할 key값 선언 후 초기화
	int index = -1;  //search함수에서 찾은 해시테이블의 주소를 반환받을 변수

	srand(time(NULL));  //시드값 초기화
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);  //command값 입력 후 각각 경우에 따라 함수를 실행

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);  //quick정렬은 재귀호출을 사용해서 printArray를 따로 호출함
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);  //위에서 선언한 hashtable 포인터변수의 주소를 넘겨서 함수에서 만들어질 hashtable의 주소를 대입함
			printArray(hashtable);  //hashtable정보 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);  //key값을 입력받아서
			printArray(hashtable);
			index = search(hashtable, key);  //해시테이블내에서 key값과 일치하는 값을 찾으면 index에 해당 주소를 대입함
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)  //double pointer를 인수로 받아 초기화하는 함수
{
	int *temp = NULL;  //정수형 temp포인터 생성 후 null값으로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {  //array가  null이면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);  //temp를 정수형 사이즈 * 배열의 수를 곱한 만큼 동적할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else  //array가 null이 아니면
		temp = *a;  //temp에 array의 주소 대입

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;  //각각의 인덱스에 0~MAX_ARRAY_SIZE-1까지 중 랜덤값을 대입

	return 0;
}

int freeArray(int *a)  //array의 메모리를 반환해주는 함수
{
	if(a != NULL)  //array가 null이 아니면 array 메모리 반환
		free(a);
	return 0;
}

void printArray(int *a)  //array의 원소들을 출력해주는 함수
{
	if (a == NULL) {  //원소가 아무것도 없다면 문구 출력 후 반환
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //인덱스들을 출력(출력형식은 2개의 자리에서 모자른 자릿수를 '0'으로 채워서 출력)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)  //배열의 원소를 출력(출력형식은 5개의 자리를 확보한 후 오른쪽 정렬되듯이 출력)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  //선택정렬함수
{
	int min;  //배열안에서 가장 작은 원소가 들어갈 변수
	int minindex;  //배열안에서 가장 작은 원소의 인덱스가 들어갈 변수
	int i, j;  //탐색의 기준이 되는 변수 i와, i에 따라서 배열을 탐색하는 j 변수 선언

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //먼저 배열을 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  //0번째 원소부터 총 배열의 크기만큼 반복
	{
		minindex = i;  //먼저 i번째 인덱스를 minindex로 가정
		min = a[i];  //minindex의 원소를 min에 대입
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)  //i 다음 인덱스부터 끝의 원소 전까지 반복
		{
			if (min > a[j])  //기존 min보다 작은 원소가 나오면 그 값을 min으로 지정하고 그 인덱스도 minindex로 지장
			{
				min = a[j];
				minindex = j;
			}
		}  //위의 반복문에서 최솟값이 결정이 되면
		a[minindex] = a[i];  //현재위치 i의 원소와 minindex의 원소를 교체한다
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //현재 배열을 출력한다
	return 0;
}

int insertionSort(int *a)  //삽입정렬 함수
{
	int i, j, t;  //배열을 탐색하는 기준이 되는 인덱스 변수를 i, i를 기준으로 탐색하는 데 사용할 변수를 j, 임시저장소로 사용할 t를 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //먼저 배열을 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)  //i가 마지막 원소의 인덱스가 될때까지 반복
	{
		t = a[i];  //t에 현재 i의 원소 대입
		j = i;  //j에 현재 인덱스 i 대입
		while (a[j-1] > t && j > 0)  //j가 0보다 크고 기존 t보다 큰 원소가 나온다면 반복문에 들어가게 된다
		{
			a[j] = a[j-1];  //j앞에 있는 원소의 값을 j위치로 옮겨준다
			j--;  //j에 바로 앞 인덱스를 넣어준다
		}
		a[j] = t;  //while문에 들어가지않았다면 a[j]=a[i]=t이므로 변경사항이 없지만 while문안에 들어갔다면 j가 연산을 거쳐서 t가 들어갈 자리가 정해지게 된다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)  //버블정렬 함수
{
	int i, j, t;  //i는 탐색의 기준이 되는 인덱스가 저장되는 변수, j는 i를 기준으로해서 뒤의 인덱스로 움직이면서 정렬이 이루어지는 변수, t는 변수의 값을 바꿀 때
					//사용되는 임시 변수이다

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE-1; i++)  //i가 마지막 인덱스 바로 앞 인덱스가 될 때까지 반복
	{
		for (j = 1 ; j < MAX_ARRAY_SIZE; j++)  //j가 i바로 다음 인덱스부터 마지막 인덱스가 될 때까지 반복
		{  //j가 움직이면서 해당 범위 내의 배열에서 가장 큰 값을 가장 뒤로 보내게 된다
			//현재 코드에서는 j가 정렬이 완료된 앞부분을 계속해서 검사하기때문에 비효율적이다
			if (a[j-1] > a[j])  //j와 j의 전 원소의 값을 비교해서 더 큰 원소가 더 앞에 있다면
			{
				t = a[j-1];  //임시변수 t를 사용해 j와 j-1에 들어있는 값을 바꿔준다
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)  //셸 정렬 a는 배열의 주소를 받게 된다
{
	int i, j, k, h, v;  //h는 원소들 사이의 간격이 저장되는 변수, i j는 각각 h보다 작은 값의 원소를 탐색하기위한 변수, i로 부터 해당 간격만큼 떨어진 원소의 인덱스
							//v는 i로 부터 h 간격만큼 떨어진 원소를 담는 변수이다

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)  //간격을 전체 배열의 크기의 반으로 설정하고 계속 *1/2 배를 하면서 간격을 조정한다
	{
		for (i = 0; i < h; i++)  //간격 h보다 작은 배열의 인덱스에 접근
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  //i에서 h 만큼의 간격만큼 떨어진 모든 원소를 탐색
			{
				v = a[j];  //v값에 현재 간격만큼 떨어진 곳의 원소를 넣어주고
				k = j;  //k에 그 인덱스를 대입해놓은다
				while (k > h-1 && a[k-h] > v)  //삽입정렬의 정렬 알고리즘을 사용한다
													//어떤 원소의 인덱스에서 간격만큼 계속 감소를 시키면서 앞에 위치한 원소들과 크기비교를 해서
													// 그 인덱스보다 앞에 위치한 원소가 현재 그 위치의 원소보다 큰 크기를 가진다면(정렬이 되지않은 상태라면)
				{
					a[k] = a[k-h];  //현재 인덱스에 앞에서 찾은 크기가 큰 값을 대입하고
					k -= h;  //k값을 간격크기만큼 줄여서 간격 앞의 원소와 크기비교를 반복한다
				}
				a[k] = v;  //while문을 거치지않았다면 a[k]의 값은 변화가 없을 것이고 while문을 거쳤다면 v가 들어갈 알맞은 위치가 k값에 대입되어있을 것이다
			}
		}  //간격을 1/2배 만큼 줄여가면서 현재 과정을 반복한다
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)  //퀵 정렬 a는 해당 배열의 주소이고 n은 배열의 크기
{
	int v, t;  //피봇값이 들어가는 v, 변수값을 옮기기위한 임시변수 t
	int i, j;  //각각 피봇의 크기를 기준으로 left와 right를 나타내는 변수


	if (n > 1)
	{
		v = a[n-1];  //현재 배열의 가장 마지막 원소를 피봇으로 설정
		i = -1;  //현재 배열에서 가장 왼쪽 원소(피봇 기준으로 left)
		j = n - 1;  //현재 배열에서 가장 오른쪽 원소(피봇 기준으로 right)

		while(1)  //특정 조건에서 break하는 무한루프
		{
			while(a[++i] < v);  //가장 왼쪽 위치에서 i를 하나씩 증가시키면서 피봇보다 큰 값을 탐색해서 인덱스를 i에 저장
			while(a[--j] > v);  //가장 오른쪽 위치(현재 피봇이 가장 오른쪽 원소이므로 피봇보다 하나 왼쪽에 있는 원소)에서 j를 하나씩
									//감소시켜면서 피봇보다 작은 값을 탐색해서 인덱스를 j에 저장

			if (i >= j) break;  //만약 left가 right보다 커지면 while문 탈출
			t = a[i];  //피봇의 값을 비교해서 왼쪽에서 피봇보다 큰 값과 오른쪽에서 피봇보다 작은 값을 서로 바꿔준다
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];  //left값이 right값보다 커진다면 피봇값과 left인덱스의 원소를 바꿔준다
		a[i] = a[n-1];
		a[n-1] = t;
		//여기까지 현재 피봇값이 위치한 지점으로 해서 왼쪽은 피봇값보다 작은 값이 오른쪽은 피봇값보다 큰 값이 위치하게 된다
		quickSort(a, i);  //현재 루프에서 피봇값이 위치했던 지점과 그 뒤의 지점으로 공간을 나눠서 재귀호출하게 된다 새로운 루프에서는 피봇값이 변하게 된다
		quickSort(a+i+1, n-i-1);  //첫번째 인수에는 피봇뒤의 인덱스 주소가 들어가게 되고 배열의 크기가 들어가는 2번째 인수에 i+1을 빼준 값이 들어가게 된다
	}


	return 0;
}

int hashCode(int key) {  //key를 해시함수를 통해서 code화시켜주는 함수
   return key % MAX_HASH_TABLE_SIZE;  //인수로 넘어온 key값의 modulo연산을 통해 코드화한다
}

int hashing(int *a, int **ht)  //해싱함수, 첫번째 인수로 배열을 받고 두번째 인수로 hashtable을 받는다
{
	int *hashtable = NULL; //해쉬테이블을 가리킬 정수형 포인터 변수 선언

	if(*ht == NULL) {  //해쉬테이블이 현재 비어있다면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);  //4byte씩 MAX_ARRAY_SIZE만큼 heap영역에서 동적할당받아서 hashtable이 해당 메모리를 가리키게 한다
		*ht = hashtable;  //*ht에 hashtable의 주소를 대입한다(주소복사이기때문에 main에서도 *ht에는 hashtable의 주소가 들어있게 된다)
	} else {  //해쉬테이블이 비어있지않다면
		hashtable = *ht;	//hashtable에 ht가 가리키는 메모리영역의 주소를 대입한다
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)  //해쉬테이블에 있는 각각의 데이터에 접근하여 값을 -1로 초기화해준다
		hashtable[i] = -1;

	int key = -1;  //해시테이블에 올라갈 데이터를 잠깐 저장해놓는 변수
	int hashcode = -1;  //해시함수를 통해 코드화된 숫자(주소)가 저장되는 변수
	int index = -1;  //비어있는 버킷을 찾을 때 사용하는 변수
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  //key값에 현재 i번째 인덱스에 있는 값을 대입
		hashcode = hashCode(key);  //hashcode변수에 key값이 해시함수를 통해 나온 값을 대입
		if (hashtable[hashcode] == -1)  //현재 해시테이블의 버킷에 아무것도 없다면(위에서 각각의 해쉬테이블을 -1로 초기화시켰기때문에)
		{
			hashtable[hashcode] = key;  //해시함수를 통해 나온 인덱스(곧 해시주소)의 값에 데이터값(key)을 대입한다
		} else 	{  //현재 버킷에 다른 데이터가 들어가있다면

			index = hashcode;  //index에 현재 hashcode값을 대입한다

			while(hashtable[index] != -1)  //hashtable의 버킷중에서 비어있는 공간을 찾을 때까지 반복한다(선형조사법)
			{  //만약 비어있는 버킷을 찾지못했다면 무한루프를 돌게 된다
				index = (++index) % MAX_HASH_TABLE_SIZE;  //index를 하나 증가시켜주고 modulo연산을 진행해서 비어있는 버킷의 주소를 찾는다
			}
			hashtable[index] = key;  //while문을 통해서 비어있는 버킷의 주소를 찾았다면 그곳에 key값을 대입해준다
		}
	}

	return 0;
}

int search(int *ht, int key)  //현재 hashtable에 있는 원소값을 탐색하는 함수
{
	int index = hashCode(key);  //index값에 key값을 해시함수에 넘겨 해시테이블의 주소값을 대입한다

	if(ht[index] == key)  //해시함수를 통해 반환받은 해시테이블 주소에 가서 key값을 찾았다면
		return index;  //해당 해시테이블 주소를 반환한다

	while(ht[++index] != key)  //index를 하나씩 증가해가면서 해시테이블을 탐색할 때 key값을 찾을 때까지 반복
	{  //원하는 key값을 찾지못하였다면 계속 무한루프를 돌게 된다
		index = index % MAX_HASH_TABLE_SIZE;  //index값을 modulo연산으로 계속 변환시켜준다
	}
	return index;  //key값의 해시테이블 주소를 반환한다
}

