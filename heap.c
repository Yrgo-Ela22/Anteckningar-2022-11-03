/********************************************************************************
* heap.c: Demonstration av dynamisk minnesallokering i C, vilket inneb�r minne
*         som kan allokeras och deallokeras (frig�ras) fr�n en pool med minne
*         kallad heapen (eller DRAM, dynamic RAM memory). 
*
*         Dynamisk minnesallokering genomf�rs i C prim�rt via de tre funktionerna
*         malloc (f�r ny minnesallokering), realloc (f�r omallokering av
*         befintligt minne) samt free (f�r deallokering/frig�rande av minne).
*         Dessa funktioner �r deklarerade i standardbiblioteket stdlib.h, som
*         d�rmed m�ste inkluderas.
* 
*      1. Funktionen malloc anv�nds f�r att allokera minne och returnera
*         en pekare till detta minne enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)malloc(<m�ngden minne i byte>);
*          
*         Som exempel, f�r att allokera ett f�lt (en array) som rymmer 20 heltal
*         av datatypen int (4 byte per int, allts� totalt 4 x 20 = 80 byte) och
*         l�ta en pekare d�pt data peka p� detta f�lt, s� kan f�ljande 
*         instruktion anv�ndas:
* 
*         int* data = (int*)malloc(80);
* 
*         F�r att slippa r�kna antalet byte manuellt s� anv�nds normalt
*         sizeof-operatorn, som i detta fall anv�nds f�r att returnera storleken
*         p� en int. Vi allokerar d�rmed storleken av en int x 20, vilket medf�r
*         att minne allokeras f�r 20 variabler av datatypen int:
* 
*         int* data = (int*)malloc(sizeof(int) * 20);
* 
*         Funktionen malloc returnerar en voidpekare, vilket inneb�r en
*         generell pekare. Detta har gjort s� att funktionen malloc kan anv�ndas
*         f�r att returnera en pekare av godtycklig datatyp. Se till att 
*         typomvandla detta returv�rde till �nskad datatyp, i detta fall en
*         intpekare, via en explicit typomvandling (int*). Det fungerar att
*         inte g�ra detta i C (�ven om det �r d�lig kutym), men vid programmering
*         i C++ erh�lls d� ett kompilatorfel (implicit typomvandling fr�n void*
*         till int*).
* 
*         N�r funktionen malloc anropas s� sker ett f�rs�k att allokera �nskad
*         m�ngd minne. Detta lyckas om det finns en tillr�cklig m�ngd konsekutivt
*         minne p� heapen. Annars returneras en nullpekare. Kontrollera alltid
*         returv�rdet fr�n funktionen malloc. Om null retureras s� f�r ni 
*         hantera detta utefter vad ni finner l�mpligt. I detta program avslutas
*         programmet om detta sker enligt nedan:
* 
*         if (!data) return 1;
* 
*         Det g�r ocks� att skriva if (data == 0) eller if (data == NULL).
* 
*      2. Funktionen realloc anv�nds f�r att omallokera ett befintligt f�lt
*         enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)realloc(
*            <pekare till minnet som ska omallokeras>, <m�ngden minne i byte>);
* 
*         Som exempel, f�r att omallokera det f�lt som pekaren data ovan pekar
*         p� s� att det rymmer 40 heltal och l�ta en kopiapekare peka p� det
*         omallokerade f�ltet kan f�ljande instruktion anv�ndas:
* 
*         int* copy = (int*)realloc(data, sizeof(int) * 40);
*          
*         Vid lyckad omallokering frig�rs det gamla minnet om detta ligger
*         p� en annan adress, vilket d�rmed inte beh�ver g�ras manuellt.
*         Vid misslyckad minnesallokering returneras null, precis som f�r
*         funktionen malloc. F�r att undvika att skriva �ver adressen till
*         det gamla f�ltet med null s� b�r en kopiapekare ta emot returv�rdet
*         fr�n realloc (adressen till det nya f�ltet). Endast vid lyckad
*         omallokering (returv�rdet �r inte lika med null) b�r pekaren till
*         det ursprungliga f�ltet s�ttas till att peka p� adressen till det
*         nya f�ltet (den adress kopiapekaren pekar p�). Annars ifall
*         minnesallokeringen misslyckas s� bibeh�lls adressen till det gamla 
*         f�ltet, d� kopiapekaren tog emot null fr�n funktionen realloc.
*         Se i programmet nedan hur en pekare d�pt copy anv�nds f�r att 
*         omallokera ett f�lt som pekas p� av en pekare d�pt data:
* 
*      3. Funktionen free anv�nds f�r att frig�ra/deallokera dynamiskt 
*         allokerat minne enligt nedan:
* 
*         free(<pekare till minnet som ska frig�ras>);
* 
*         Som exempel, f�r att frig�ra det minne som pekas p� av pekaren data
*         ovan kan f�ljande instruktion anv�ndas:
* 
*         free(data);
* 
*         Viktigt �r att alltid s�tta pekaren till minnet till null efter
*         deallokeringen. Annars forts�tter pekaren att pekar p� den adress
*         d�r minnet tidigare l�g. Detta kan bjuda in misstag, exempelvis
*         att vi r�kar genomf�rs tilldelning till denna adress, vilket kan
*         medf�ra att programmet kraschar. En s�dan pekare kallas dangling 
*         pointer och b�r allts� undvikas. 
*
*         Pekaren data ovan kan s�ttas till null genom att tilldela denna adressen 0:
* 
*         data = 0;
* 
*         Alternativt kan makrot NULL anv�ndas:
* 
*         data = NULL;        
********************************************************************************/
#include <stdio.h>  /* Inneh�ller funktionalitet f�r utskrift och inmatning. */
#include <stdlib.h> /* Inneh�ller funktionalitet f�r dynamisk minnesallokering. */

/********************************************************************************
* int_array_assign: Fyller arrayen till bredden med heltal med angivet stegv�rde.
* 
*                   - self: Pekare till arrayen som ska tilldelas.
*                   - size: Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - step: Stegv�rdet, dvs. differensen mellan varje element.
********************************************************************************/
static void int_array_assign(int* self, 
                             const size_t size, 
                             const int step)
{
   for (size_t i = 0; i < size; ++i) 
   { 
      self[i] = (int)i * step;
   }

   return;
}

/********************************************************************************
* int_array_print: Skriver ut heltal lagrade i array via angiven utstr�m, d�r
*                  standardutenhet stdout anv�nds som default f�r utskrift
*                  i terminalen.
*
*                   - self   : Pekare till arrayen vars inneh�ll ska skrivas ut.
*                   - size   : Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - ostream: Pekare till angiven utstr�m (default = stdout).
********************************************************************************/
static void int_array_print(const int* self, 
                            const size_t size, 
                            FILE* ostream)
{
   if (!ostream) ostream = stdout;
   fprintf(ostream, "----------------------------------------------------------------------------\n");

   for (size_t i = 0; i < size; ++i)
   {
      fprintf(ostream, "%d\n", self[i]);
   }

   fprintf(ostream, "----------------------------------------------------------------------------\n\n");
   return;
}

/********************************************************************************
* main: Allokerar minne f�r ett f�lt som rymmer 20 heltal p� heapen. Ifall
*       minnesallokeringen misslyckades (null returnerades fr�n malloc) s� 
*       avslutas programmet med felkod 1. Annars fylls f�ltet till bredden
*       med heltal r�knat fr�n 0 med stegv�rde 2 (0, 2, 4, ... 38), f�ljt av
*       utskrift i terminalen. 
*
*       D�refter omallokeras f�ltet s� att det rymmer 40 heltal i st�llet. 
*       F�r att inte f�rlora adressen till det ursprungliga f�ltet ifall 
*       minnesallokeringen misslyckas s� anv�nds en kopiapekare, som pekar p� 
*       det nya f�ltet. Ifall minnesallokeringen misslyckas kommer d� denna
*       pekare att peka p� null (det fanns inte utrymme f�r det st�rre f�ltet),
*       medan det ursprunliga f�ltet kvarst�r och adressen �r bibeh�llen (utan
*       kopiapekaren hade adressen till det gamla f�ltet skrivits �ver med null
*       och vi hade f�tt en minnesl�cka).
* 
*       Ifall omallokeringen lyckades s�tts den ursprungliga pekaren till att
*       peka p� det nya f�lt som kopiapekaren pekar p�. Det gamla f�ltet har 
*       d� frigjorts via funktionen realloc och beh�ver d�rmed inte frig�ras 
*       manuellt av oss. D�refter tilldelas den nyligen allokerade delen av 
*       f�ltet med heltal r�knade fr�n 0 med stegv�rde -2. De heltal som 
*       tilldelades tidigare kvarst�r allts�, de nya talen l�ggs p� de 20 nya
*       adresserna som har allokerats.
* 
*       D�refter skrivs inneh�llet lagrat i f�ltet ut i terminalen samt till
*       en textfil d�pt "data.txt". Slutligen frig�rs minnet som har allokerats
*       f�r f�ltet och pekaren till f�ltet s�tts till null. Detta b�r alltid
*       g�ras efter frig�rande av minnet, annars ligger pekaren kvar och pekar
*       d�r f�ltet tidigare l�g (innan det raderades). Dynamiskt allokerat minne
*       m�ste alltid frig�ras av anv�ndaren. Om detta missas s� frig�rs inte
*       minnet f�rr�n d� du startar om din dator!
********************************************************************************/
int main(void)
{
   int* data = (int*)malloc(sizeof(int) * 20);
   if (!data) return 1;

   int_array_assign(data, 20, 2);     
   int_array_print(data, 20, 0); 

   int* copy = (int*)realloc(data, sizeof(int) * 40); 
   if (!copy) return 1; 
   data = copy; 

   int_array_assign(data + 20, 20, -2); 
   int_array_print(data, 40, 0); 

   FILE* ostream = fopen("data.txt", "w");
   int_array_print(data, 40, ostream);

   free(data); 
   data = 0; 
   return 0;
}