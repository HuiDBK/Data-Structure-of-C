#include "stdio.h"
#include "malloc.h"

#define  TRUE  1
#define  FALSE 0
#define  MAXSIZE 100		// 顺序栈的最大存储量

typedef int ElemType;		// 顺序栈存储元素的数据类型

/*
 *	定义顺序栈结构体
*/
typedef struct SeqStack{
	ElemType datas [MAXSIZE];
	int top;	// 栈顶指针
}*Stack;



/********************* 顺序栈的常规操作 **************************/

Stack 	 InitStack();				// 初始化栈
int   	 StackFull();				// 判断栈满
int   	 StackEmpty();				// 判断栈空
int   	 StackLength();				// 求栈长(栈元素个数)
int   	 Push();					// 入栈 压栈
ElemType Pop();						// 出栈 弹栈

/***************************************************************/


int main(int argc, char const *argv[])
{
	Stack s = InitStack();

	printf("StackEmpty():%d\n", StackEmpty(s));
	printf("StackLength():%d\n\n", StackLength(s));

	// 入栈元素
	ElemType datas[] = {2, 4, 6, 8, 10};

	// 动态计算入栈元素个数
	int len = sizeof(datas) / sizeof(datas[0]);	

	// for循环依次入栈
	printf("Push():");
	for(int i = 0; i < len; i++){
		printf("%d\t", datas[i]);
		Push(s, datas[i]);
	}
	printf("\nStackEmpty():%d\n", StackEmpty(s));
	printf("StackLength():%d\n\n", StackLength(s));

	// 出栈 弹栈
	printf("Pop():");
	for(int i = 0; i < len; i++){
		printf("%d\t", Pop(s));
	}
	printf("\nStackEmpty():%d\n", StackEmpty(s));
	printf("StackLength():%d\n\n", StackLength(s));
	return 0;
}


/*
 *	初始化顺序栈
*/
Stack InitStack(){
	// 分配顺序栈内存空间
	Stack s = (Stack)malloc(sizeof(struct SeqStack));
	s -> top = 0;
	return s;
}


/*
 *	顺序栈判空
 *  s 顺序栈
*/
int StackEmpty(Stack s){
	if(s == NULL){
		return FALSE;
	}
	return s -> top == 0;
}


/*
 *	顺序栈判满
 *  s 顺序栈
*/
int StackFull(Stack s){
	if(s == NULL){
		return FALSE;
	}
	return s -> top == MAXSIZE;
}



/*
 *	求顺序栈的长度（元素的个数）
 *	s 顺序栈
*/
int StackLength(Stack s){
	if(s == NULL){
		return FALSE;
	}
	return s -> top;
}

/*
 *	入栈 压栈
 *  s 顺序栈
 *  data 入栈数据
*/
int Push(Stack s, ElemType data){
	// 顺序栈判满
	if(StackFull(s)){
		return FALSE;
	}
	s -> datas[s -> top] = data;
	s -> top ++;
	return TRUE;
}


/*
 *	出栈 弹栈
 *	s 顺序栈
*/
ElemType Pop(Stack s){
	int data;
	// 判栈空
	if(StackEmpty(s)){
		return FALSE;
	}
	s -> top--;
	data = s -> datas[s -> top];
	return data;
}