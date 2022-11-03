/**************************************************************************************************
* int_vector.c: Inneh�ller definitioner av associerade funktioner f�r strukten int_vector, som 
*               anv�nds f�r implementering av dynamiska vektorer f�r lagring av signerade heltal.
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
* int_vector_clear: T�mmer inneh�llet i angiven vektor genom att frig�ra allokerat minne
*
*                   - self: Pekare till vektorn som ska t�mmas.
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
* int_vector_delete: Frig�r minne f�r en heapallokerad vektor. Vektorpekarens adress passeras 
*                    f�r att b�de frig�ra minnet f�r det dynamiska f�lt denna peka p�, minnet 
*                    f�r sj�lva vektorn samt att vektorpekaren s�tts till null.
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
* int_vector_resize: �ndrar storleken / kapaciteten p� en vektor via omallokering. Vid lyckad
*                    omallokering returneras 0, annars returneras felkod 1.
*
*                    - self    : Pekare till vektorn vars storlek skall �ndras.
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
* int_vector_push: L�gger till ett nytt element l�ngst bak i en vektor. Ifall det nya elementet
*                  lyckas l�ggas till returneras 0, annars returneras felkod 1.
*
*                  - self       : Pekare till vektorn som ska tilldelas det nya elementet.
*                  - new_element: Det nya element som skall l�ggas till l�ngst bak i vektorn.
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
* int_vector_pop: Tar bort ett element l�ngst bak i angiven vektor, om ett s�dant finns. 
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
* int_vector_print: Skriver ut inneh�llet lagrat i angiven vektor via angiven utstr�m, d�r
*                   standardutenheten stdout anv�nds som default f�r utskrift i terminalen.
*
*                   - self   : Pekare till vektorn vars inneh�ll ska skrivas ut.
*                   - ostream: Pekare till angiven utstr�m (default = stdout).
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
* int_vector_begin: Returnerar adressen till det f�rsta elementet i angiven vektor.
*                   Om vektorn �r tom returneras null.
* 
*                   - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_begin(const struct int_vector* self)
{
   return self->data;
}

/**************************************************************************************************
* int_vector_end: Returnerar adressen direkt efter det sista elementet i angiven vektor. 
*                 Om vektorn �r tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_end(const struct int_vector* self)
{
   return self->data + self->size;
}

/**************************************************************************************************
* int_vector_last: Returnerar adressen till det sista elementet i angiven vektor. 
*                  Om vektorn �r tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_last(const struct int_vector* self)
{
   return self->size > 0 ? self->data + self->size - 1 : 0;
}

