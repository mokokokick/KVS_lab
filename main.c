#include "kvs.h"

int main()
{
	kvs_t* kvs = open();

	if(!kvs) {
		printf("Failed to open kvs\n");
		return -1;
	}

	// workload execution  
	
	// 1) 	file read 
	// 2) 	if put, insert (key, value) into kvs.
	// 		if get, seach the key in kvs and return the value. 
	//		Return -1 if the key is not found  

        FILE *query_file = fopen("query.dat", "r");
    FILE *answer_file = fopen("answer.dat", "w");

    if (!query_file || !answer_file) {
        printf("Failed to open query.dat or answer.dat.\n");
        if (query_file) fclose(query_file);
        if (answer_file) fclose(answer_file);
        close(kvs);  // kvs 해제
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), query_file)) {
        char key[100], value[100];
        int operation;
        
        // query.dat에서 데이터를 읽고 파싱
        if (sscanf(line, "%[^,],%d,%[^,\n]", key, &operation, value) < 2) {
            continue; // 형식 오류 시 건너뜀
        }

        if (operation == 1) {
            // put 연산
            if (put(kvs, key, value) == 0) {
                fprintf(answer_file, "put: %s, %s\n", key, value);
            } else {
                fprintf(answer_file, "put: %s, FAILED\n", key);
            }
        } else if (operation == 0) {
            // get 연산
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "get: %s, %s\n", key, result);
            } else {
                fprintf(answer_file, "get: %s, NULL\n", key);
            }
        }
    }

    // 파일 포인터 해제
    fclose(query_file);
    fclose(answer_file); 
	close(kvs);
	
	return 0;
}
