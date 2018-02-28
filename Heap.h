#include<stdio.h>
#include<time.h>
#include<assert.h>

typedef int Datatype;

void AdjustDown(Datatype* a, size_t n, int root)//���µ���(���)
{
	int parent = root;
	int child = (root * 2 + 1);//����
	while (child < n)
	{
		if (a[child] < a[child + 1] && (child + 1 < n))//�Ƚ����Һ��Ӵ�С��ȡ�ϴ�ֵ
		{
			++child;
		}
		if (a[parent] < a[child])//���׺ͽϴ�ֵ�Ƚ�һ�κ󣬿���Ӱ���������������������ظ��Ƚϣ����µ���
		{
			Datatype tmp = a[child];
			a[child] = a[parent];
			a[parent] = tmp;
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void AdjustUp(Datatype* a,size_t size,int child)//���ϵ���
{
	int parent = (child - 1) >> 1;
	while (child > 0)
	{
		if (a[child] > a[parent])
		{
			Datatype tmp = a[child];
			a[child] = a[parent];
			a[parent] = tmp;
			child = parent;
			parent = (child - 1) >> 1;
		}
		else
			break;
	}
}
void MakeHeap(Datatype* a,size_t n)//����
{
	int i = (n - 2) / 2;
	for (; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}
}
void TestHeap()
{
	int a[] = { 1,2,3,19,4,5,6,7,8,9 };
	printf("��ʼ����>");
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	MakeHeap(a, sizeof(a) / sizeof(a[0]));
	printf("���>");
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}
}

void TopK(Datatype* a, size_t k, int n)//Ѱ��ǰK���ϴ����
{
	MakeHeap(a, k);
	for (int i = k+1; i < n; i++)
	{
		if (a[i] > a[0])
		{
			a[0] = a[i];
			AdjustDown(a, k, 0);
		}
		else
			continue;
	}
}
void TestTopK()
{
	int a[1000] = { 0 };
	srand(time(0));
	int i = 0;
	for (i = 0; i < 1000; i++)
		a[i] = rand() % 10000;
	a[525] = 10001;
	a[89] = 10002;
	a[0] = 10003;
	a[789] = 10004;
	a[23] = 10005;
	a[180] = 11111;
	a[999] = 26985;
	a[666] = 10259;
	a[483] = 19853;
	a[359] = 20061;

	TopK(a, 10, sizeof(a) / sizeof(a[0]));
	for (i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
}

#define N 1000
typedef struct PriorityQueue
{
	Datatype a[N];
	size_t size;
}PriorityQueue;
void PriorityQueuePush(PriorityQueue* q,Datatype data);
void PriorityQueueInit(PriorityQueue* q);
void PriorityQueuePop(PriorityQueue* q);
Datatype PriorityQueueTop(PriorityQueue* q);
size_t PriorityQueueEmpty(PriorityQueue* q);
size_t PriorityQueueSize(PriorityQueue* q);

void PriorityQueueInit(PriorityQueue* q)
{
	assert(q);
	q->size = 0;
	memset(q->a, 0, sizeof(Datatype)*N);
}
void PriorityQueuePush(PriorityQueue* q, Datatype data)
{
	assert(q);
	if (N == q->size)
	{
		printf("PriorityQueue is FULL\n");
		return;
	}
	q->a[q->size] = data;
	q->size++;
	/*for (int i = 0; i < q->size; i++)
	{
		AdjustDown(q->a, q->size, i);
	}*/
	AdjustUp(q->a, q->size, q->size-1);
}
void PriorityQueuePop(PriorityQueue* q)
{
	assert(q);
	if (0 == q->size)
	{
		printf("PriorityQueue is NULL\n");
		return;
	}
	size_t begin = 1;
	while (begin < q->size)
	{
		q->a[begin - 1] = q->a[begin];
		++begin;
	}
	q->size--;
}
Datatype PriorityQueueTop(PriorityQueue* q)
{
	return q->a[0];
}
size_t PriorityQueueEmpty(PriorityQueue* q)
{
	if (0 == q->size)
		return 0;
}
size_t PriorityQueueSize(PriorityQueue* q)
{
	assert(q);
	int count = 0;
	while (q->size--)
	{
		count++;
	}
	return count;
}
void TestPriorityQueue()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5);
	PriorityQueuePush(&q, 2);
	PriorityQueuePush(&q, 3);
	PriorityQueuePush(&q, 7);
	PriorityQueuePush(&q, 6);
	PriorityQueuePush(&q, 1);
	PriorityQueuePush(&q, 4);
	while (PriorityQueueEmpty(&q) != 0)
	{
		printf("%d ", PriorityQueueTop(&q));
		PriorityQueuePop(&q);
	}
	printf("\n");
}

void HeapSort(Datatype* a, size_t n)//����
{
	MakeHeap(a, n);
	Datatype tmp = a[0];
	a[0] = a[n-1];
	a[n-1] = tmp;
	while (--n)
	{
		AdjustDown(a, n, 0);
		Datatype tmp = a[0];
		a[0] = a[n - 1];
		a[n - 1] = tmp;
	}
}
void TestHeapSort()
{
	int a[10] = { 0 };
	srand(time(0));
	printf("ԭ����>");
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 20;
		printf("%d ", a[i]);
	}
	printf("\n");
	HeapSort(a, sizeof(a) / sizeof(a[0]));
	printf("������--���򣨴�ѣ�-->");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}