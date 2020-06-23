#include "stdio.h"
#include "malloc.h"

#define MAXSIZE 100			// 顺序表的最大存储量
#define TRUE  1
#define FALSE 0

typedef int ElemType;		// 顺序表存储元素的数据类型


// 定义顺序表结构体
typedef struct SeqList{
	ElemType elems[MAXSIZE];
	int len;		// 当前顺序表的长度
}*SeqList;

/********************* 顺序表的常规操作 *******************************/

SeqList InitList();				// 初始化线性表
void    DestroyList();			// 销毁线性表
void    ClearList();			// 清空线性表
int     ListEmpty();			// 判断线性表是否为空
int     ListLen();				// 求线性表的长度
void	Travel();				// 遍历线性表
int     ListInsert();			// 向线性表插入元素
int     ListDelete();			// 从线性表删除元素
int     GetElem();				// 找到线性表指定位置的元素值
int     LocateElem();			// 找到线性表指定元素值的位置

/********************************************************************/



// 程序主入口
int main(int argc, char const *argv[]){
	SeqList list = InitList();
	
	// 往顺序表插入元素
	for(int i=1;i<=5;i++){
		ListInsert(list, i, i);
	}

	printf("list -> len:%d\n", list -> len);
	Travel(list);

	// 删除
	int val,pos = 5;
	ListDelete(list, pos, &val);
	printf("删除顺序表第%d个元素\n删除的元素为：%d\n", pos, val);
	Travel(list);
	printf("list -> len:%d\n", list -> len);

	// 查找指定位置的元素
	int status = GetElem(list, pos, &val);
	if(status){
		printf("查找顺序表第%d个元素\n查找的元素为：%d\n", pos, val);
	}else{
		printf("无法查找到顺序表第%d个元素\n", pos);
	}

	// 查找指定元素的位置
	int i, elem=4;
	int result = LocateElem(list, elem, &i);
	if(result){
		printf("查找元素%d，位置为：%d\n", elem, i);
	}else{
		printf("无法查找到元素%d的位置\n", elem);
	}

	return 0;
}


// 初始化顺序表
SeqList InitList(){
	SeqList list = (SeqList)malloc(sizeof(struct SeqList));		// 分配顺序表内存大小
	list -> len = 0;		// 顺序表的初始长度
	return list;
}


// // 销毁顺序表
// void DestroyList(SeqList list){
// 	if(list -> elems != NULL){
// 		free(list -> elems);	//释放动态数组内存
// 	}
// 	list -> elems = NULL;
// }


// 清空顺序表
void ClearList(SeqList list){
	list -> len = 0;		// 将顺序表的长度置为 0
}


// 顺序表判空
int ListEmpty(SeqList list){
	if(list == NULL) return FALSE;
	return list -> len == 0;
}


// 获取顺序表的长度
int GetLen(SeqList list){
	return list -> len;
}


// 遍历顺序表
void Travel(SeqList list){
	for(int i=0;i<list -> len;i++){
		printf("%d\t", list -> elems[i]);
	}
	printf("\n");
}


/*
 * 指定位置在顺序表插入元素
 * pos 物理下标 (1, 2, 3, ...)
 * elem 要插入顺序表的元素
*/
int ListInsert(SeqList list, int pos, ElemType elem){
	// 判断插入位置是否合法
	if(pos <= 0 || pos > list -> len + 1){
		return FALSE;
	}

	// 判断顺序表是否已满
	if(list -> len == MAXSIZE){
		return FALSE;
	}

	// 元素后移
	for(int i=list -> len;i>= pos;i--){
		// 1 [2] 3 4 5
		list -> elems[i] = list -> elems[i-1];
	}

	// 元素插入
	list -> elems[pos - 1] = elem;
	list -> len ++;	// 记得更新顺序表长度
	return TRUE;
}


/*
 * 指定位置在顺序表删除元素
 * pos 物理下标 (1, 2, 3, ...)
 * val 用来保存删除元素的值
*/
int ListDelete(SeqList list, int pos, ElemType *val){
	// 判断删除位置是否合法
	if(pos <= 0 || pos > list -> len){
		return FALSE;
	}

	*val = list -> elems[pos - 1];	// 先保存要删除元素的值

	// 元素前移
	for(int i=pos - 1;i<list -> len;i++){
		list -> elems[i] = list -> elems[i + 1];
	}

	list -> len --;	// 记得更新顺序表长度
	return FALSE;
}


/*
 * 查找指定位置的顺序表元素
 * pos 物理下标 (1, 2, 3, ...)查找的位置
 * val 用来保存元素的值
*/
int GetElem(SeqList list, int pos, ElemType *val){
	// 判断位置是否合理
	if(pos <= 0 || pos > list -> len){
		return FALSE;
	}
	*val = list -> elems[pos - 1];
	return TRUE;
}


/*
 * 查找顺序表指定元素的位置(第一个匹配成功的元素位置)
 * elem 要查找的元素
 * pos 物理下标 (1, 2, 3, ...)用来保存元素的位置
*/			
int LocateElem(SeqList list, ElemType elem, int *pos){
	for(int i=0;i<list -> len;i++){
		if(list -> elems[i] == elem){	// 判断元素是否相等
			*pos = i + 1;
			return TRUE;
		}
	}
	return FALSE; 	// 没找到返回FAlSE
}		
