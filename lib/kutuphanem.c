#include "kutuphanem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>

typedef _Bool boolean;
# define true 1
# define false 0

boolean buffer_overflow(int const* index, int const* buf_size);
void increase_buffer_capacity(int* ptr_bufsize, char** commands);

tamsayi kareAl(tamsayi sayi)
{
    return sayi * sayi;
}

metin metinAl(void)
{

    //Metinleri tutacak deponun boyutu
    tamsayi_isaretsiz boyut = 33;

    //Depo
    metin depo = malloc(boyut * sizeof(char));

    //Depodaki eleman sayısı
    tamsayi_isaretsiz i = 0;

    tamsayi k;

    while ((k = getchar()) != '\n' && k != EOF)
    {

        if (i >= boyut)
        {
            if (boyut * 2 > TSY_ISZ_SINIR)
            {
                free(depo);
                perror(TSY_ISZ_SINIR_HATA);
                return NULL;
            }

            boyut *= 2;
            depo = realloc(depo, boyut * sizeof(karakter));
            printf("%s : %d\n","yeni boyut",boyut);
        }
        depo[i++] = (karakter)k;
    }

    if (i == 0 && k == EOF) {
        perror("Girdi yok");
        return " ";
    }

    metin kucultulmus = malloc((i + 1) * sizeof(karakter));
    strncpy(kucultulmus, depo, i);
    free(depo);

    kucultulmus[i] = '\0';
    return kucultulmus;
}

boolean buffer_overflow(int const* ptr_index, int const* ptr_buf_size) {
    return *ptr_index >= *ptr_buf_size;
}

void increase_buffer_capacity(int* ptr_bufsize, char** commands) {

    (*ptr_bufsize) *=2;
    commands = realloc(commands, (*ptr_bufsize) * sizeof(char*));
    //buffer_size*=2;
    //commands = realloc(commands, buffer_size * sizeof(char));
} 