#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool buffer_overflow(int index, int buf_size);
void increase_buffer_capacity(int* ptr_bufsize, char** commands);

bool buffer_overflow(int index, int buf_size) {
    return index >= buf_size;
}

void increase_buffer_capacity(int* ptr_bufsize, char** commands) {

    (*ptr_bufsize) *=2;
    commands = realloc(commands, (*ptr_bufsize) * sizeof(char*));
    //buffer_size*=2;
    //commands = realloc(commands, buffer_size * sizeof(char));
}

size_t indexOf(char c, char* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if(*(str + i) == c) {
            return i;
        }
    }
    return -1;
}

char*subString(char*str, size_t start_idx, size_t end_idx) {
    // start: inclusive, end: exclusive
    size_t size = end_idx - start_idx;
    char*result = malloc(size * sizeof(char));
    size_t count = 0;
    for (size_t i = start_idx; i < end_idx; i++) {
       *(result + count) = *(str + i);
       count++;
    }
    return result;
}

char*subStringEnd(char*str, size_t start_idx, size_t size) {
    size_t len = (size - start_idx) * sizeof(char);
    char*result = malloc(len);
    size_t count = 0;
    for (size_t i = start_idx; i < size; i++) {
        *(result + count) = *(str + i);
        count++;
    }
    return result;
}

char** biggerBuffer(char**arr, size_t buf_size) {
   return realloc(arr, (2 * buf_size) * sizeof(char*));
}

char**split(char*cmd, size_t len, size_t space_count) {
    size_t buf_size = 10;
    char**tmp = malloc(buf_size * sizeof(char*));
    size_t num_of_spaces = space_count;
    size_t count = 0;
    printf("%s\n","basla");
    for (size_t i = 0; i < len; i++) {
        printf("%zu.adım\n",i);
        if(*(cmd + i) == ' ') {
            printf("toplam bosluk: %zu\n", num_of_spaces);
            printf("%zu.adımda bosluk karakteri\n",i);
            size_t bosluk_idx = i;
            char*bastanBoslugaKadar = subString(cmd, 0, bosluk_idx);
            printf("bastan bosluga kadar: %s\n",bastanBoslugaKadar);

            if(i >= buf_size) {
                tmp = biggerBuffer(tmp, buf_size);
                printf("%s\n","buffer boyutu artırıldı");
            }

            *(tmp + count) = bastanBoslugaKadar;
            printf("%s dizinin %zu.sırasına atıldı: %s\n", bastanBoslugaKadar, count, *(tmp + count));

            size_t bosluktanSonrakiIlkChar = bosluk_idx + 1;
            cmd = subStringEnd(cmd, bosluktanSonrakiIlkChar, len);
            printf("geri kalan: %s\n",cmd);

            if(num_of_spaces == 1) {
                char**result = malloc((count + 1) * sizeof(char*));
                *(tmp + (count + 1)) = cmd;
                printf("son kalan: %s diziye %zu.sıradan eklendi cikiss yapiliyor\n",cmd, count+1);
                result = tmp;
                return result;
            }   
            
            i = 0; //kalan dizinin en basından basla
            num_of_spaces--;
            count++;
        }
    }
    return NULL;
}

void printStringArray(char**arr, size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("%zu.elm: %s\n", i, *(arr + i));
    }
}

size_t get_space_count(char* str, size_t len) {
    size_t space_count = 0;
    for (size_t i = 0; i < len; i++) {
        if(*(str + i) == ' ') {
            space_count++;
        }
    }
    return space_count;
}

int main(int argc, char const *argv[]) {
    
    char*str = "ahmed mehmed ayse";
    size_t len = strlen(str);
    size_t space_count = get_space_count(str, len);
    printf("space count: %zu\n",space_count);
    //printf("%s\n",str);
    char**boslugaGore = split(str, len, space_count);
    size_t elm_count = space_count + 1;
    printf("total elm count: %zu\n", elm_count);
    //printf("%s\n",boslugaGore[1]);
    //printStringArray(boslugaGore, elm_count);

    // char* a = NULL;
    // boslugaGore[elm_count] = a;
    return 0;
}
