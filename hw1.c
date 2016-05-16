#include <stdio.h>
#include "hw1.h"
void Init() {
}
void InsertObjectToTail(Object* pObj, int objNum, ObjList listNum) {
	// ### Object Table Setting ### //
	if (ppObjListHead[listNum] == NULL) {
		// 리스트가 비어있는 경우.
		pObj->poPrev = NULL;
		pObj->poNext = NULL;
		ppObjListHead[listNum] = pObj;
		ppObjListTail[listNum] = pObj;
	}
	else {
		ppObjListTail[listNum]->poNext = pObj;
		pObj->poPrev = ppObjListTail[listNum];
		pObj->poNext = NULL;
		ppObjListTail[listNum] = pObj;
	}

	// ### Hash Table Setting ### //
	if (ppHashTail[objNum%HASH_TBL_SIZE] == NULL) {
		// Hash Table이 비어있는 경우
		ppHashHead[objNum%HASH_TBL_SIZE] = pObj;
		ppHashTail[objNum%HASH_TBL_SIZE] = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
	}
	else {
		ppHashTail[objNum%HASH_TBL_SIZE]->phNext = pObj;
		pObj->phPrev = ppHashTail[objNum%HASH_TBL_SIZE];
		pObj->phNext = NULL;
		ppHashTail[objNum%HASH_TBL_SIZE] = pObj;
	}
	pObj->objnum = objNum;
}


void InsertObjectToHead(Object* pObj, int objNum, ObjList listNum) {
	// ### Object Table Setting ### //
	if (ppObjListHead[listNum] == NULL) {
		// 리스트가 비어있는 경우.
		pObj->poPrev = NULL;
		pObj->poNext = NULL;
		ppObjListHead[listNum] = pObj;
		ppObjListTail[listNum] = pObj;
	}
	else {
		ppObjListTail[listNum]->poNext = pObj;
		pObj->poPrev = ppObjListTail[listNum];
		pObj->poNext = NULL;
		ppObjListTail[listNum] = pObj;
	}

	// ### Hash Table Setting ### //
	if (ppHashTail[objNum%HASH_TBL_SIZE] == NULL) {
		// Hash Table이 비어있는 경우
		ppHashHead[objNum%HASH_TBL_SIZE] = pObj;
		ppHashTail[objNum%HASH_TBL_SIZE] = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
	}
	else {
		ppHashHead[objNum%HASH_TBL_SIZE]->phPrev = pObj;
		pObj->phNext = ppHashHead[objNum%HASH_TBL_SIZE];
		pObj->phPrev = NULL;
		ppHashHead[objNum%HASH_TBL_SIZE] = pObj;
	}
	pObj->objnum = objNum;
}

// 성공시 Object* 반환
// 실패시 NULL 반환
Object* GetObjectByNum(int objnum) {
	Object* iterator;

	if (ppHashHead[objnum%HASH_TBL_SIZE] == NULL) {
		return NULL;
	}

	for (iterator = ppHashHead[objnum%HASH_TBL_SIZE]; iterator != NULL; iterator = iterator->phNext) {
		if (iterator->objnum == objnum) return iterator;
		else continue;
	}
	return NULL;
}

void DeleteObject(Object* pObj) {
	int i = 0;
	for (i = 0; i < 2; i++) {
		// Obj가 Object 리스트의 헤더이자 테일인 경우
		if (pObj == ppObjListHead[i] && pObj == ppObjListTail[i]) {
			ppObjListHead[i] = ppObjListTail[i] = NULL;
			break;
		}
		// Obj가 Object 리스트의 헤더인 경우
		else if (pObj == ppObjListHead[i]) {
			pObj->poNext->poPrev = NULL;
			ppObjListHead[i] = pObj->poNext;
			break;
		}
		// Obj가 Object 리스트의 테일인 경우
		else if (pObj == ppObjListTail[i]) {
			pObj->poPrev->poNext = NULL;
			ppObjListTail[i] = pObj->poPrev;
			break;
		}
		// Obj가 테이블의 중간에 있는 일반적인 경우
		else if (i == OBJ_LIST1) { // 위 조건에 모두 충족되지 않고 넘어왔으므로 일반적인 경우가 된다.
			pObj->poPrev->poNext = pObj->poNext;
			pObj->poNext->poPrev = pObj->poPrev;
			break;
		}
	}
	pObj->poNext = pObj->poPrev = NULL;

	for (i = 0; i < HASH_TBL_SIZE; i++) {
		// Obj가 Hash Table의 헤더이자 테일인 경우
		if (pObj == ppHashHead[i] && pObj == ppHashTail[i]) {
			ppHashHead[i] = ppHashTail[i] = NULL;
			break;
		}
		// Obj가 Hash Table의 헤더인 경우
		else if (pObj == ppHashHead[i]) {
			pObj->phNext->phPrev = NULL;
			ppHashHead[i] = pObj->phNext;
			break;
		}
		// Obj가 Hash Table의 테일인 경우
		else if (pObj == ppHashTail[i]) {
			pObj->phPrev->phNext = NULL;
			ppHashTail[i] = pObj->phPrev;
			break;
		}
		// Obj가 테이블의 중간에 있는 일반적인 경우
		else if (i == HASH_TBL_SIZE - 1) {// 위 조건에 모두 충족되지 않고 넘어왔으므로 일반적인 경우가 된다.
			pObj->phPrev->phNext = pObj->phNext;
			pObj->phNext->phPrev = pObj->phPrev;
			break;
		}
	}
	pObj->phNext = pObj->phPrev = NULL;
}

Object* GetObjectFromObjFreeList(void) {
	Object* temp = ppObjListTail[OBJ_FREELIST];

	if (temp == ppObjListHead[OBJ_FREELIST]) {
		// 남아있는 Obj가 1개인 경우 (헤드이자 테일인 경우)
		temp->poNext = temp->poPrev = NULL;
		ppObjListTail[OBJ_FREELIST] = ppObjListHead[OBJ_FREELIST] = NULL;
	}
	else if (temp == NULL) {
		// 비어있는 리스트에서 빼려하는 경우
		return NULL;
	}
	else {
		ppObjListTail[OBJ_FREELIST] = ppObjListTail[OBJ_FREELIST]->poPrev;
		ppObjListTail[OBJ_FREELIST]->poNext = NULL;
	}

	return temp;
}

void InsertObjectIntoObjFreeList(Object* pObj) {
	// 비어있는 리스트에 추가하려는 경우
	if (ppObjListTail[OBJ_FREELIST] == NULL) {
		ppObjListHead[OBJ_FREELIST] = pObj;
		ppObjListTail[OBJ_FREELIST] = pObj;
		pObj->poPrev = pObj->poNext = NULL;
	}
	else {
		ppObjListHead[OBJ_FREELIST]->poPrev = pObj;
		pObj->poNext = ppObjListHead[OBJ_FREELIST];
		pObj->poPrev = NULL;
		ppObjListHead[OBJ_FREELIST] = pObj;
	}
}
