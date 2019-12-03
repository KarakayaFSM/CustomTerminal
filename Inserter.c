# include <stdio.h>
# include <stdlib.h>

int ctoi(char c) { return c - '0'; }

int stoi(const char*str) {
    int num;
    sscanf(str, "%d", &num);
    return num;
}

char*biggerBuffer(char*str, size_t buffer_size) {
    return realloc(str, 2 * buffer_size * sizeof(char));
}   

int* toInt(char const *argv[], int argc) {
    int* intArr =  malloc(argc * sizeof(char*));
    for (size_t i = 1; i < argc; i++) { //discard command text (get only numbers)
        *(intArr + i -1) = stoi(argv[i]);
    }
    return intArr;
}

void WriteFile(FILE*fp, int*params, size_t len) {
    for (size_t i = 0; i < len - 1; i++) { //discard trailing zero (at the end)
        fprintf(fp, "%d ", *(params + i));
    }
}

int main(int argc, char const *argv[]) {
    
    int*params = toInt(argv, argc);
    FILE* fp = fopen("./files/database.txt","a");

    if(fp == NULL) {
        perror("Error on opening file");
        return -1;
    }

    WriteFile(fp, params, argc);

    int status = fclose(fp);

    if(status == EOF) {
        perror("Error on closing file");
        return -2;
    }

    return 0;
}