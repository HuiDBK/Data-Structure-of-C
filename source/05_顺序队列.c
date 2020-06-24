#include "stdio.h"
#include "malloc.h"

#define TRUE  1
#define FALSE 0
#define MAXSIZE 10  // 队列最大的存储量

typedef int ElemType;


// 定义顺序队列结构体
typedef struct SeQueue{
    ElemType *base; // 队列首地址
    int front;      // 队列头下标
    int rear;       // 队列尾下标
}*Queue;


/********************* 顺序队列的常规操作 **************************/

Queue    InitSeQueue();             // 初始化顺序队列
int      QueueFull();               // 判断顺序队列满
int      QueueEmpty();              // 判断顺序队列空
int      QueueLength();             // 求顺序队列长度(元素个数)
int      EnQueue();                 // 入队
int      DeQueue();                 // 出队

void     QueueStatus();             // 打印队满、队空、队长状态
/****************************************************************/


// 程序主入口
int main(int argc, char const *argv[])
{   
    Queue q = InitSeQueue();
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

    // 此时队列元素全出队了，测试假溢出
    int num = 20;
    printf("EnQueue(%d): %d\t(0 Failed, 1 Success)\n", num, EnQueue(q, num));
    return 0;
}


/*
 *  初始化顺序队列
*/
Queue InitSeQueue(){
    Queue q;
    // 分配队列空间
    q -> base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    q -> front = q -> rear = 0; // 开始队列的头尾下标相等
    return q;
}


/*  
 *  顺序队列判满
 *  q 顺序队列
*/
int QueueFull(Queue q){
    if(q == NULL){
        return FALSE;
    }
    // 判断队列尾下标是否超过最大容量
    if(q -> rear >= MAXSIZE){
        return TRUE;
    }
    return FALSE;
}


/*
 *  顺序队列判空
 *  q 顺序队列
*/
int QueueEmpty(Queue q){
    if(q == NULL){
        return FALSE;
    }
    return q -> front == q -> rear;
}


/*
 *  求顺序队列的长度(元素个数)
 *  q 顺序队列
*/
int QueueLength(Queue q){
    if(q == NULL){
        return FALSE;
    }
    return q -> rear - q -> front;
}


/*
 *  入队
 *  q 顺序队列
 *  data 入队元素
*/
int EnQueue(Queue q, ElemType data){
    // 队列判满
    if(QueueFull(q)){
        return FALSE;
    }
    // 把元素插入队尾
    q -> base[q -> rear] = data;    
    q -> rear++;
    return TRUE;
}


/*
 *  出队  
 *  q 顺序队列
 *  *val 用来存出队元素的数据 
*/
int DeQueue(Queue q, ElemType *val){
    // 队列判空
    if(QueueEmpty(q)){
        return FALSE;
    }
    // 把队头元素取出来并利用指针返回去
    *val = q -> base[q -> front];
    q -> front ++;
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