/**************************************************************************************************
* main.c: Demonstration av dynamiska vektorer för lagring och utskrift av heltal i C.
**************************************************************************************************/
#include "int_vector.h"

/**************************************************************************************************
* main: Deklarerar två dynamiska vektorer, varav den första allokeras statiskt och den andra
*       dynamiskt. Den statiskt allokerade vektorn tilldelas tio heltal med startvärde 0 samt 
*       stegvärde 2 (0, 2, 4, 6... 18). Den dynamiskt allokerade vektorn sätts till att rymma 
*       20 heltal vid start, vilket tilldelas med startvärde 20 med stegvärde 1 (20, 19, 18... 1).
*       Vektorernas innehåll skrivs ut i terminalen innan programmet avslutas.
**************************************************************************************************/
int main(void)
{
   struct int_vector v1, *v2;
   int num = 20;

   int_vector_init(&v1);
   v2 = int_vector_new(20);

   for (int i = 0; i < 10; ++i)
   {
      int_vector_push(&v1, i * 2);
   }

   for (int* i = int_vector_begin(v2); i < int_vector_end(v2); ++i)
   {
      *i = num--;
   }

   int_vector_print(&v1, 0);
   int_vector_print(v2, 0);
   return 0;
}