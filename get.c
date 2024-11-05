#include "kvs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get(kvs_t* kvs, const char* key)
{
    // value를 함수 시작 부분에 선언 및 할당
    char* value = (char*)malloc(sizeof(char) * 100);

    if(!value){
        printf("Failed to malloc\n");
        return NULL;
    }

	/* do program here */

    // 유효성 검사
    if (!kvs || !key) {
        free(value); // 할당된 메모리 해제
        return NULL;
    }

    // 리스트에서 키를 검색
    node_t* current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // 키가 존재하면 value에 복사
            strncpy(value, current->value, 99);
            value[99] = '\0'; // 널 종결자 추가
            return value;
        }
        current = current->next;
    }

    // 키가 존재하지 않으면 "deadbeaf"를 반환
    strcpy(value, "deadbeaf");
    return value;
}

