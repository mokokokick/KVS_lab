#include "kvs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int put(kvs_t* kvs, const char* key, const char* value)
{
    if (!kvs || !key || !value) {
        return -1; // 실패: 유효하지 않은 입력
    }

    printf("put: %s, %s\n", key, value);

    // 키가 존재하지 않으므로 새 노드를 추가
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        return -1; // 실패: 메모리 할당 문제
    }

    // 새로운 노드 초기화
    strncpy(new_node->key, key, sizeof(new_node->key) - 1);
    new_node->key[sizeof(new_node->key) - 1] = '\0'; // 널 종료 보장
    new_node->value = strdup(value);
    if (!new_node->value) { // 값 할당 실패 시 노드 해제 후 실패 반환
        free(new_node);
        return -1;
    }

    // 새 노드를 리스트의 맨 앞에 추가
    new_node->next = kvs->db;
    kvs->db = new_node;
    kvs->items++; // 항목 수 증가

    return 0; // 성공
}



