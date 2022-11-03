/**************************************************************************************************
* int_vector.c: Innehåller definitioner av associerade funktioner för strukten int_vector, som 
*               används för implementering av dynamiska vektorer för lagring av signerade heltal.
**************************************************************************************************/
#include "int_vector.h"

/**************************************************************************************************
* int_vector_init: Initierar ny tom vektor.
*
*                  - self: Pekare till vektorn som ska initieras.
**************************************************************************************************/
void int_vector_init(struct int_vector* self)
{
   self->data = 0;
   self->size = 0;
   return;
}

/**************************************************************************************************
* int_vector_clear: Tömmer innehållet i angiven vektor genom att frigöra allokerat minne
*
*                   - self: Pekare till vektorn som ska tömmas.
**************************************************************************************************/
void int_vector_clear(struct int_vector* self)
{
   free(self->data);
   self->data = 0;
   self->size = 0;
   return;
}

/**************************************************************************************************
* int_vector_new: Returnerar en pekare till en ny heapallokerad vektor av angiven storlek.
*
*                 - size: Vektorns storlek (antalet element den rymmer) vid start.
**************************************************************************************************/
struct int_vector* int_vector_new(const size_t size)
{
   struct int_vector* self = (struct int_vector*)malloc(sizeof(struct int_vector));
   if (!self) return 0;
   self->data = 0;
   self->size = 0;
   int_vector_resize(self, size);
   return self;
}

/**************************************************************************************************
* int_vector_delete: Frigör minne för en heapallokerad vektor. Vektorpekarens adress passeras 
*                    för att både frigöra minnet för det dynamiska fält denna peka på, minnet 
*                    för själva vektorn samt att vektorpekaren sätts till null.
*
*                    - self: Adressen till vektorpekaren.
**************************************************************************************************/
void int_vector_delete(struct int_vector** self)
{
   int_vector_clear(*self);
   free(*self);
   *self = 0;
   return;
}

/**************************************************************************************************
* int_vector_resize: Ändrar storleken / kapaciteten på en vektor via omallokering. Vid lyckad
*                    omallokering returneras 0, annars returneras felkod 1.
*
*                    - self    : Pekare till vektorn vars storlek skall ändras.
*                    - new_size: Vektorns nya storlek efter omallokeringen.
**************************************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t new_size)
{
   int* copy = (int*)realloc(self->data, sizeof(int) * new_size);
   if (!copy) return 1;
   self->data = copy;
   self->size = new_size;
   return 0;
}

/**************************************************************************************************
* int_vector_push: Lägger till ett nytt element längst bak i en vektor. Ifall det nya elementet
*                  lyckas läggas till returneras 0, annars returneras felkod 1.
*
*                  - self       : Pekare till vektorn som ska tilldelas det nya elementet.
*                  - new_element: Det nya element som skall läggas till längst bak i vektorn.
**************************************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int new_element)
{
   int* copy = (int*)realloc(self->data, sizeof(int) * (self->size + 1));
   if (!copy) return 1;
   copy[self->size++] = new_element;
   self->data = copy;
   return 0;
}

/**************************************************************************************************
* int_vector_pop: Tar bort ett element längst bak i angiven vektor, om ett sådant finns. 
*                 Ifall elementet lyckas tas bort returneras 0, annars returneras felkod 1.
*
*                 - self: Pekare till vektorn vars sista elemenet ska tas bort.
**************************************************************************************************/
int int_vector_pop(struct int_vector* self)
{
   if (self->size <= 1)
   {
      int_vector_clear(self);
      return 1;
   }
   else
   {
      int* copy = (int*)realloc(self->data, sizeof(int) * (self->size - 1));
      if (!copy) return 1;
      self->data = copy;
      self->size--;
      return 0;
   }
}

/**************************************************************************************************
* int_vector_print: Skriver ut innehållet lagrat i angiven vektor via angiven utström, där
*                   standardutenheten stdout används som default för utskrift i terminalen.
*
*                   - self   : Pekare till vektorn vars innehåll ska skrivas ut.
*                   - ostream: Pekare till angiven utström (default = stdout).
**************************************************************************************************/
void int_vector_print(const struct int_vector* self,
                      FILE* ostream)
{
   if (!self->size) return;
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------\n");

   for (size_t i = 0; i < self->size; ++i)
   {
      fprintf(ostream, "%d\n", self->data[i]);
   }

   fprintf(ostream, "--------------------------------------------------------------------------\n\n");
   return;
}

/**************************************************************************************************
* int_vector_begin: Returnerar adressen till det första elementet i angiven vektor.
*                   Om vektorn är tom returneras null.
* 
*                   - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_begin(const struct int_vector* self)
{
   return self->data;
}

/**************************************************************************************************
* int_vector_end: Returnerar adressen direkt efter det sista elementet i angiven vektor. 
*                 Om vektorn är tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_end(const struct int_vector* self)
{
   return self->data + self->size;
}

/**************************************************************************************************
* int_vector_last: Returnerar adressen till det sista elementet i angiven vektor. 
*                  Om vektorn är tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_last(const struct int_vector* self)
{
   return self->size > 0 ? self->data + self->size - 1 : 0;
}

