#include "stdio.h"
#include "malloc.h"


#define TRUE  1
#define FALSE 0

typedef int ElemType;		// 单链表存储元素的数据类型

// 定义单链表结构体
typedef struct Node{
	ElemType data;			// 单链表结点数据域
	struct Node *next;		// 单链表结点地址域（指向下一个结点）
}*LinkList, Node;


/********************* 单链表的常规操作 ****************************/

LinkList CreateHeadListH();			// 头插法创建单链表
LinkList CreateHeadListT();			// 尾插法创建单链表
int      ListEmpty();				// 单链表判空
int		 ListLength();				// 求单链表长度
void 	 Travel();					// 遍历单链表
int 	 InsertNode();				// 插入结点
int      DeleteNode();				// 删除结点
ElemType GetElem();					// 按址查值
int 	 GetLocate();				// 按值查址
int 	 RemoveRepeat();			// 去除重复的值

void     OutList();					// 打印单链表的长度并遍历

/*****************************************************************/


// 程序入口
int main(int argc, char const *argv[])
{
	int datas[] = {2, 4, 6, 8, 10};
	// 动态计算datas数组的长度
	// 数组长度 = 数组的总空间大小 / 数组中每个元素所占空间大小
	int len = sizeof(datas) / sizeof(datas[0]);

	printf("头插法构造单链表\n");
	LinkList list_h = CreateHeadListH(datas, len);
	printf("ListEmpty():%d\n", ListEmpty(list_h));		// 判空
	OutList(list_h);									// 打印单链表长度并遍历															

	printf("尾插法构造单链表\n");
	LinkList list_t = CreateHeadListT(datas, len);
	printf("ListEmpty():%d\n", ListEmpty(list_t));
	OutList(list_t);

	ElemType data = 12, val;
	int pos = 6, status;

	printf("指定位置插入结点\n");
	status = InsertNode(list_t, data, pos);
	printf("InsertNode(data=%d, pos=%d):status = %d\n", data, pos, status);
	OutList(list_t);

	printf("指定位置删除结点\n");	
	pos = 5;
	status = DeleteNode(list_t, &val, pos);
	printf("DeleteNode(val=%d, pos=%d):status = %d\n", val, pos, status);
	OutList(list_t);

	printf("按址查值\n");
	pos = 2;
	printf("GetElem(pos=%d):%d\n", pos, GetElem(list_t, pos));

	printf("按值查址\n");
	data = 8;
	printf("GetLocate(data=%d):%d\n", data, GetLocate(list_t, data));

	printf("\n去重前的单链表\n");
	InsertNode(list_t, 6, 3);
	InsertNode(list_t, 8, 3);
	InsertNode(list_t, 8, 3);
	InsertNode(list_t, 2, 3);
	OutList(list_t);

	printf("去重后的单链表\n");
	RemoveRepeat(list_t);
	OutList(list_t);
	return 0;
}


/*
 *	头插法创建单链表(带头结点)
 *	datas 接收数组，用于赋值链表的结点数据
 *	len datas数组的长度，便于遍历
*/
LinkList CreateHeadListH(ElemType *datas, int len){
	// 创建头结点
	LinkList head, new_node;
	head = (LinkList)malloc(sizeof(Node));
	// head -> data = len;	// 可以把链表长度存在头结点的数据域中
	head -> next = NULL;

	// 分配新节点并用头插法链接起来
	for(int i=0;i<len;i++){
		new_node = (LinkList)malloc(sizeof(Node));
		new_node -> data = datas[i];
		new_node -> next = head -> next;
		head -> next = new_node;
	}
	return head;
}


/*
 *	尾插法创建单链表(带头结点)
 *	datas 接收数组，用于赋值链表的结点数据
 *	len datas数组的长度，便于遍历
*/
LinkList CreateHeadListT(ElemType *datas, int len){
	// 创建头结点
	LinkList head, p, new_node;
	head = (LinkList)malloc(sizeof(Node));
	head -> next = NULL;
	p = head;

	// 分配新节点并用尾插法链接起来
	for(int i=0;i<len;i++){
		new_node = (LinkList)malloc(sizeof(Node));
		new_node -> data = datas[i];
		new_node -> next = NULL;
		p -> next = new_node;
		p = new_node;
	}
	return head;
}



/*
 *	单链表判空
 *	list 接收单链表
*/
int ListEmpty(LinkList list){
	return (list == NULL || list -> next == NULL);
}


/*
 *	计算单链表的长度
 *	list 接收单链表
*/
int ListLength(LinkList list){
	LinkList p = list;
	int len = 0;
	if(ListEmpty(list)){
		return len;
	}
	p = p -> next;
	while(p != NULL){
		len ++;
		p = p -> next;
	}
	return len;
}

/*
 *	打印单链表的长度和遍历单链表
 *	list 单链表
*/
void OutList(LinkList list){
	LinkList p = list;
	if(!ListEmpty(list)){
		printf("ListLength():%d\n", ListLength(list));	// 求长
		printf("Travel():");								
		Travel(list);										// 遍历
	}
}

/*
 * 遍历单链表
 * list 单链表
*/
void Travel(LinkList list){
	LinkList p = list;
	if(!ListEmpty(list)){
		p = p -> next;	// 因为带头结点单链表所以要先走一步
		while(p != NULL){
			printf("%d\t", p -> data);
			p = p -> next;
		}
		printf("\n\n");
	}
}


/*
 * 单链表指定位置插入结点
 * list 单链表
 * data 要插入的结点的数据
 * pos  结点插入的位置（逻辑位置（1,2,3,...））
*/
int InsertNode(LinkList list, ElemType data, int pos){
	LinkList p = list, new_node;
	if(ListEmpty(list)){
		printf("空单链表\n");
		return FALSE;
	}

	// 判断插入位置是否合理
	if(pos <= 0 || pos > ListLength(list) + 1){
		printf("插入位置不合理\n");
		return FALSE;
	}
 	
	// 寻找到要插入位置的前一个结点
	for(int i = 0; i < pos - 1 && p != NULL; i++){
		p = p -> next;
	}

	// 准备新结点
	new_node = (LinkList)malloc(sizeof(Node));
	new_node -> data = data;

	// 此时p就是要插入位置的前一个结点，p -> next就是要插入位置的结点
	new_node -> next = p -> next;	
	p -> next = new_node;
	return TRUE;
}


/*
 * 单链表指定位置删除结点
 * list 单链表
 * *val 用来存储删除结点的数据
 * pos  结点删除的位置（逻辑位置（1,2,3,...））
*/
int DeleteNode(LinkList list, ElemType *val, int pos){
	LinkList p = list, r;
	if(ListEmpty(list)){
		printf("空单链表\n");
		return FALSE;
	}

	// 判断删除位置是否合理
	if(pos <= 0 || pos > ListLength(list)){
		printf("删除位置不合理\n");
		return FALSE;
	}

	// 寻找到要删除结点的前一个位置
	for(int i = 0; i < pos - 1 && p != NULL; i++){
		p = p -> next;
	}

	r = p -> next;			// 记录要删除的结点
	*val = r -> data;		// 把删除结点的数据利用指针返回去
	p -> next = r -> next;	// 把链表重新链接起来
	free(r);				// 释放删除结点的资源
	return TRUE;
}


/*
 *	根据指定位置求结点的值(没有找到返回 0 )
 *	list 单链表
 *	pos  结点位置（逻辑位置（1,2,3,...））
*/
ElemType GetElem(LinkList list, int pos){
	LinkList p = list;
	if(ListEmpty(list)){
		printf("空单链表\n");
		return FALSE;
	}
	if(pos <= 0 || pos > ListLength(list)){
		printf("位置不合理\n");
		return FALSE;
	}

	for(int i = 0; i < pos && p !=NULL; i++){
		p = p -> next;
	}
	return p -> data;
}


/*
 *	根据指定的值寻找结点的位置
 *	(如果有多个值相同返回第一个找到的结点的位置, 没找到则返回 0)
 *	list 单链表
 *  data 要查找的值
*/
int GetLocate(LinkList list, ElemType data){
	LinkList p = list;
	int pos = 0;
	if(ListEmpty(list)){
		return FALSE;
	}
	p = p -> next;
	while(p != NULL){
		pos ++;
		if(p -> data == data){
			return pos;
		}
		p = p -> next;
	}
	return FALSE;
}


/*
 *	去除单链表中重复的值（重复的值只保留一个）
 *	list 单链表
 *  返回值：对单链表进行了去重操作返回 1，否则返回 0
*/
int RemoveRepeat(LinkList list){
	LinkList p = list, q, r;
	int flag = 0;
	if(ListEmpty(list)){
		return FALSE;
	}

	p = p -> next;

	while(p != NULL){
		q = p;
		while(q != NULL && q -> next != NULL){
			if(p -> data == q -> next -> data){
				r = q -> next;	// 记录值相同的结点
				q -> next = r -> next;
				free(r);
				flag = 1;
			}else{
				q = q -> next;
			}
		}
		p = p -> next;
	}
	return flag;
}