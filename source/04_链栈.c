#include "stdio.h"
#include "malloc.h"


#define TRUE  1
#define FALSE 0

typedef int ElemType;		// 链栈存储元素的数据类型


/*
 *	定义链栈结构体
*/
typedef struct Node{
	ElemType data;			// 栈结点数据域
	struct Node *next;		// 栈结点指针域
}*LinkStack, Node;


/********************* 链栈的常规操作 ****************************/

LinkStack 	 InitLinkStack();			// 初始化链栈
int   	 	 StackEmpty();				// 判断链栈空
int   	 	 StackLength();				// 求链栈长(链栈元素个数)
int    		 Push();					// 入栈 压栈
ElemType 	 Pop();						// 出栈 弹栈
void 	 	 DestroyStack();			// 销毁链栈

/***************************************************************/


// 程序主入口
int main(int argc, char const *argv[])
{
	LinkStack s = InitLinkStack();
	printf("StackEmpty():%d\n", StackEmpty(s));
	printf("StackLength():%d\n\n", StackLength(s));

	// 入栈元素
	ElemType datas[] = {1, 3, 5, 7, 9};

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
	printf("Pop(): ");
	while(!StackEmpty(s)){
		printf("%d\t", Pop(s));
	}
	printf("\nStackEmpty():%d\n", StackEmpty(s));
	printf("StackLength():%d\n\n", StackLength(s));
	return 0;
}


// 初始化链栈（带头结点的链栈）
LinkStack InitLinkStack(){
	LinkStack s = (LinkStack)malloc(sizeof(struct Node));
	s -> next = NULL;
	return s;
}


/*
 *	判断链栈是否空
 *  s 链栈
*/
int StackEmpty(LinkStack s){
	if(s == NULL){
		return FALSE;
	}
	return s -> next == NULL;
}


/*
 *	求链栈长度（栈中元素个数）
 *  s 链栈
*/
int StackLength(LinkStack s){
	LinkStack p;
	int len = 0;
	if(StackEmpty(s)){
		return FALSE;
	}
	p = s -> next;	// 带头结点的链栈要先移动一下
	while(p != NULL){
		len ++;
		p = p -> next;
	}
	return len;
}


/*
 *	入栈 压栈
 *  s 链栈
 *  data 入栈数据
*/
int Push(LinkStack s, ElemType data){
	// 分配入栈结点
	Node *new_node = (Node *)malloc(sizeof(struct Node));
	if (new_node == NULL) return FALSE;		// 结点分配失败

	// 跟单链表一样使用头插法
	new_node -> data = data;
	new_node -> next = s -> next;
	s -> next = new_node;
	return TRUE;
}


/*
 *	出栈 弹栈
 *	s 链栈
*/
ElemType Pop(LinkStack s){
	LinkStack top;
	ElemType data;
	// 判栈空
	if(StackEmpty(s)){
		return FALSE;
	}
	top = s -> next;	// 访问栈顶结点
	data = top -> data;	// 取出栈顶元素
	s -> next = top -> next;
	free(top);			// 释放栈顶空间
	return data;
}