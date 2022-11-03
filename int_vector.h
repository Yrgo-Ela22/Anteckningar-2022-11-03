/**************************************************************************************************
* int_vector.h: Implementering av dynamiska vektorer f�r lagring av signerade heltal av datatypen
*               int via strukten int_vector samt associerade funktioner.
**************************************************************************************************/
#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************************
* int_vector: Vektor inneh�llande ett dynamiskt f�lt f�r lagring av signerade heltal. Antalet
*             element som lagras i f�ltet r�knas upp och uttrycks i form av vektorns storlek.
**************************************************************************************************/
struct int_vector
{
   int* data;   /* Pekare till dynamiskt f�lt inneh�llande heltal. */
   size_t size; /* Vektorns storlek, dvs. antalet element den rymmer. */
};

/**************************************************************************************************
* int_vector_init: Initierar ny tom vektor.
*
*                  - self: Pekare till vektorn som ska initieras.
**************************************************************************************************/
void int_vector_init(struct int_vector* self);

/**************************************************************************************************
* int_vector_clear: T�mmer inneh�llet i angiven vektor genom att frig�ra allokerat minne.
*
*                   - self: Pekare till vektorn som ska t�mmas.
**************************************************************************************************/
void int_vector_clear(struct int_vector* self);

/**************************************************************************************************
* int_vector_new: Returnerar en pekare till en ny heapallokerad vektor av angiven storlek.
*
*                 - size: Vektorns storlek (antalet element den rymmer) vid start.
**************************************************************************************************/
struct int_vector* int_vector_new(const size_t size);

/**************************************************************************************************
* int_vector_delete: Frig�r minne f�r en heapallokerad vektor. Vektorpekarens adress passeras
*                    f�r att b�de frig�ra minnet f�r det dynamiska f�lt denna peka p�, minnet
*                    f�r sj�lva vektorn samt att vektorpekaren s�tts till null.
*
*                    - self: Adressen till vektorpekaren.
**************************************************************************************************/
void int_vector_delete(struct int_vector** self);

/**************************************************************************************************
* int_vector_resize: �ndrar storleken / kapaciteten p� en vektor via omallokering. Vid lyckad
*                    omallokering returneras 0, annars returneras felkod 1.
*
*                    - self    : Pekare till vektorn vars storlek skall �ndras.
*                    - new_size: Vektorns nya storlek efter omallokeringen.
**************************************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t new_size);

/**************************************************************************************************
* int_vector_push: L�gger till ett nytt element l�ngst bak i en vektor. Ifall det nya elementet
*                  lyckas l�ggas till returneras 0, annars returneras felkod 1.
*
*                  - self       : Pekare till vektorn som ska tilldelas det nya elementet.
*                  - new_element: Det nya element som skall l�ggas till l�ngst bak i vektorn.
**************************************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int new_element);

/**************************************************************************************************
* int_vector_pop: Tar bort ett element l�ngst bak i angiven vektor, om ett s�dant finns.
*                 Ifall elementet lyckas tas bort returneras 0, annars returneras felkod 1.
*
*                 - self: Pekare till vektorn vars sista elemenet ska tas bort.
**************************************************************************************************/
int int_vector_pop(struct int_vector* self);

/**************************************************************************************************
* int_vector_print: Skriver ut inneh�llet lagrat i angiven vektor via angiven utstr�m, d�r
*                   standardutenheten stdout anv�nds som default f�r utskrift i terminalen.
*
*                   - self   : Pekare till vektorn vars inneh�ll ska skrivas ut.
*                   - ostream: Pekare till angiven utstr�m (default = stdout).
**************************************************************************************************/
void int_vector_print(const struct int_vector* self, 
                      FILE* ostream);

/**************************************************************************************************
* int_vector_begin: Returnerar adressen till det f�rsta elementet i angiven vektor.
*                   Om vektorn �r tom returneras null.
*
*                   - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_begin(const struct int_vector* self);

/**************************************************************************************************
* int_vector_end: Returnerar adressen direkt efter det sista elementet i angiven vektor.
*                 Om vektorn �r tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_end(const struct int_vector* self);

/**************************************************************************************************
* int_vector_last: Returnerar adressen till det sista elementet i angiven vektor.
*                  Om vektorn �r tom returneras null.
*
*                 - self: Pekare till vektorn.
**************************************************************************************************/
int* int_vector_last(const struct int_vector* self);

#endif /* INT_VECTOR_H_ */