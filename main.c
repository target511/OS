#include <stdio.h>
#include "hw1.h"

void PrintHashTable();
void PrintObjectTable();
void main(void) {
	/*
	extern void		InsertObjectToTail(Object* pObj, int objNum, ObjList listNum);
	extern void		InsertObjectToHead(Object* pObj, int objNum, ObjList listNum);
	extern Object*		GetObjectByNum(int objnum);
	extern void 		DeleteObject(Object* pObj);
	extern Object*		GetObjectFromObjFreeList(void);
	extern void		InsertObjectIntoObjFreeList(Object* pObj);
	*/

	Object test1, test2, test3, test4, test5;
	test1.objnum = 12; // 1
	test2.objnum = 3; // 0
	test3.objnum = 9; // 0
	test4.objnum = 0; // 1
	test5.objnum = 16; // 1

	InsertObjectToTail(&test1, test1.objnum, OBJ_LIST1);
	InsertObjectToHead(&test2, test2.objnum, OBJ_LIST0);
	InsertObjectToHead(&test3, test3.objnum, OBJ_LIST0);
	InsertObjectToHead(&test4, test4.objnum, OBJ_LIST1);
	InsertObjectToTail(&test5, test5.objnum, OBJ_LIST1);

	PrintHashTable();
	PrintObjectTable();

	printf("%p\n", GetObjectByNum(12));
	printf("%p\n", &test1);
}

void PrintHashTable() {
	int i;
	Object* iter;
	for (i = 0; i < HASH_TBL_SIZE; i++) {
		printf("Hash Table [%d] : ", i);
		for (iter = ppHashHead[i]; iter != NULL; iter = iter->phNext) {
			if (iter == NULL) {
				break;
			}
			else {
				printf("%4d", iter->objnum);
			}
		}
		printf("\n");
	}
}

void PrintObjectTable() {
	int i;
	Object* iter;
	for (i = 0; i < 2; i++) {
		printf("Object List [%d] : ", i);
		for (iter = ppObjListHead[i]; iter != NULL; iter = iter->poNext) {
			if (iter == NULL) {
				break;
			}
			else {
				printf("%4d", iter->objnum);
			}
		}
		printf("\n");
	}
}
