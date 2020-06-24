#include "stdio.h"
#include "malloc.h"

#define TRUE  1
#define FALSE 0
#define MAXSIZE 10

typedef int ElemType;


// 定义循环队列结构体
typedef struct Queue{

	int *base;	// 队列首地址
	int front;	// 队列头下标
	int rear;	// 队列尾下标

}*Queue;


/********************* 循环队列的常规操作 **************************/

Queue    InitQueue();             	// 初始化循环队列
int      QueueFull();               // 循环队列判满
int      QueueEmpty();              // 循环队列判空
int      QueueLength();             // 求循环队列长度(元素个数)
int      EnQueue();                 // 循环队列 入队
int      DeQueue();                 // 循环队列 出队

void     QueueStatus();             // 打印队满、队空、队长状态
/****************************************************************/


// 程序主入口
int main(int argc, char const *argv[])
{   
    Queue q = InitQueue();
    printf("QueueMaxSize: %d\n\n", MAXSIZE);
    QueueStatus(q); // 打印队满、队空、队长状态

    // 入队
    printf("EnQueue():");
    for(int i = 1; i < MAXSIZE * 2; i+=2){
        printf("%d\t", i);
        EnQueue(q, i);
    }

    printf("\n");
    QueueStatus(q);

    // 出队
    int val;
    printf("DeQueue():");
    while(!QueueEmpty(q)){
        DeQueue(q, &val);
        printf("%d\t", val);
    }
    printf("\n");
    QueueStatus(q);

    // 测试循环队列是否会假溢出
    int num = 20;
    printf("EnQueue(%d): %d\t(0 Failed, 1 Success)\n", num, EnQueue(q, num));
    QueueStatus(q);
    return 0;
}


/*
 * 初始化循环队列 
*/
Queue InitQueue(){
    Queue q;
    // 分配循环队列空间
    q -> base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    q -> front = q -> rear = 0;
    return q;
}


/*
 *  循环队列判满
 *  q 循环队列
*/
int QueueFull(Queue q){
    if(q == NULL){
        return FALSE;
    }
    return (q -> rear + 1) % MAXSIZE == q -> front;
}


/*
 *  循环队列判空
 *  q 循环队列
*/
int QueueEmpty(Queue q){
    if(q == NULL){
        return FALSE;
    }
    return q -> front == q -> rear;
}


/*
 *  计算循环队列长度
 *  q 循环队列
*/
int QueueLength(Queue q){
    if(q == NULL){
        return FALSE;
    }
    return (q -> rear - q -> front + MAXSIZE) % MAXSIZE;
}


/*
 *  循环队列 入队
 *  q 循环队列
 *  data 入队元素
*/
int EnQueue(Queue q, ElemType data){
    if(QueueFull(q)){
        return FALSE;
    }
    // 队尾入队
    q -> base[q -> rear] = data;
    // 更新队尾指针
    q -> rear = (q -> rear + 1) % MAXSIZE;
    return TRUE;
}


/*
 *  循环队列 出队
 *  q 循环队列
 *  *val 用来存出队元素的数据 
*/
int DeQueue(Queue q, ElemType *val){
    if(QueueEmpty(q)){
        return FALSE;
    }
    // 队头元素出队
    *val = q -> base[q -> front];
    // 更新队头指针
    q -> front = (q -> front + 1) % MAXSIZE;
    return TRUE;
}


/*
 * 打印队满、队空、队长状态
 * q 顺序队列
*/
void QueueStatus(Queue q){
    printf("QueueFull():%d\n", QueueFull(q));
    printf("QueueEmpty():%d\n", QueueEmpty(q));
    printf("QueueLength():%d\n\n", QueueLength(q));
}