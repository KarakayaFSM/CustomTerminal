#ifndef KUTUPHANEM_H_   /* Include guard */
#define KUTUPHANEM_H_

#include "limits.h"
#include <stdlib.h>

//işaretsiz tamsayıların alabileceği en büyük değer
#define TSY_ISZ_SINIR (INT_MAX * 2U + 1U)
#define TSY_ISZ_SINIR_HATA "Isaretsiz Tamsayi Siniri Asildi"

typedef char karakter;
typedef char* metin;
typedef int tamsayi;
typedef unsigned int tamsayi_isaretsiz;


tamsayi kareAl(tamsayi sayi);

metin metinAl(void);

#endif

