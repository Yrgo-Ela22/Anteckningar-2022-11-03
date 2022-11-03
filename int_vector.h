/**************************************************************************************************
* int_vector.h: Implementering av dynamiska vektorer för lagring av signerade heltal av datatypen
*               int via strukten int_vector samt associerade funktioner.
**************************************************************************************************/
#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************************
* int_vector: Vektor innehållande ett dynamiskt fält för lagring av signerade heltal. Antalet
*             element som lagras i fältet räknas upp och uttrycks i form av vektorns storlek.
**************************************************************************************************/
struct int_vector
{
   int* data;   /* Pekare till dynamiskt fält innehållande heltal. */
   size_t size; /* Vektorns storlek, dvs. antalet element den rymmer. */
};

/**************************************************************************************************
* int_vector_init: Initierar ny tom vektor.
*
*                  - self: Pekare till vektorn som ska initieras.
**************************************************************************************************/
void int_vector_init(struct int_vector* self);

/**************************************************************************************************
* int_vector_clear: Tömmer innehållet i angiven vektor genom att frigöra allokerat minne.
*
*                   - self: Pekare till vektorn som ska tömmas.
**************************************************************************************************/
void int_vector_clear(struct int_vector* self);

/**************************************************************************************************
* int_vector_new: Returnerar en pekare till en ny heapallokerad vektor av angiven storlek.
*
*                 - size: Vektorns storlek (antalet element den rymmer) vid start.
**************************************************************************************************/
struct int_vector* int_vector_new(const size_t size);

/**************************************************************************************************
* int_vector_delete: Frigör minne för en heapallokerad vektor. Vektorpekarens adress passeras
*                    för att både frigöra minnet för det dynamiska fält denna peka på, minnet
*                    för själva vektorn samt att vektorpekaren sätts till null.
*
*                    - self: Adressen till vektorpekaren.
**************************************************************************************************/
void int_vector_delete(struct int_vector** self);

/**************************************************************************************************
* int_vector_resize: Ändrar storleken / kapaciteten på en vektor via omallokering. Vid lyckad
*                    omallokering returneras 0, annars returneras felkod 1.
*
*                    - self    : Pekare till vektorn vars storlek skall ändras.
*                    - new_size: Vektorns nya storlek efter omallokeringen.
**************************************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t new_size);

/**************************************************************************************************
* int_vector_push: Lägger till ett nytt element längst bak i en vektor. Ifall det nya elementet
*                  lyckas läggas till returneras 0, annars returneras felkod 1.
*
*                  - self       : Pekare till vektorn som ska tilldelas det nya elementet.
*                  - new_element: Det nya element som skall läggas till längst bak i vektorn.
**************************************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int new_element);

/**************************************************************************************************
* int_vector_pop: Tar bort ett element längst bak i angiven vektor, om ett sådant finns.
*                 Ifall elementet lyckas tas bort returneras 0, annars returneras felkod 1.
*
*                 - self: Pekare till vektorn vars sista elemenet ska tas bort.
**************************************************************************************************/
int int_vector_pop(struct int_vector* self);

/**************************************************************************************************
* int_vector_print: Skriver ut innehållet lagrat i angiven vektor via angiven utström, där
*                   standardutenheten stdout används som default för utskrift i terminalen.
*
*                   - self   : Pekare till vektorn vars innehåll ska skrivas ut.
*                   - ostream: Pekare till angiven utström (default = stdout).
**************************************************************************************************/
void int_vector_print(const struct int_vector* self, 
                      FILE* ostream);

/**************************************************************************************************
* int_vector_begin: Returnerar adressen till det första elementet i angiven vektor.
*                   Om vektorn är tom returneras null.
*
*                   - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_begin(const struct int_vector* self);

/**************************************************************************************************
* int_vector_end: Returnerar adressen direkt efter det sista elementet i angiven vektor.
*                 Om vektorn är tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_end(const struct int_vector* self);

/**************************************************************************************************
* int_vector_last: Returnerar adressen till det sista elementet i angiven vektor.
*                  Om vektorn är tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_last(const struct int_vector* self);

#endif /* INT_VECTOR_H_ */