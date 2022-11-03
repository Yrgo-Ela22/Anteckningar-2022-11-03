/********************************************************************************
* heap.c: Demonstration av dynamisk minnesallokering i C, vilket innebär minne
*         som kan allokeras och deallokeras (frigöras) från en pool med minne
*         kallad heapen (eller DRAM, dynamic RAM memory). 
*
*         Dynamisk minnesallokering genomförs i C primärt via de tre funktionerna
*         malloc (för ny minnesallokering), realloc (för omallokering av
*         befintligt minne) samt free (för deallokering/frigörande av minne).
*         Dessa funktioner är deklarerade i standardbiblioteket stdlib.h, som
*         därmed måste inkluderas.
* 
*      1. Funktionen malloc används för att allokera minne och returnera
*         en pekare till detta minne enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)malloc(<mängden minne i byte>);
*          
*         Som exempel, för att allokera ett fält (en array) som rymmer 20 heltal
*         av datatypen int (4 byte per int, alltså totalt 4 x 20 = 80 byte) och
*         låta en pekare döpt data peka på detta fält, så kan följande 
*         instruktion användas:
* 
*         int* data = (int*)malloc(80);
* 
*         För att slippa räkna antalet byte manuellt så används normalt
*         sizeof-operatorn, som i detta fall används för att returnera storleken
*         på en int. Vi allokerar därmed storleken av en int x 20, vilket medför
*         att minne allokeras för 20 variabler av datatypen int:
* 
*         int* data = (int*)malloc(sizeof(int) * 20);
* 
*         Funktionen malloc returnerar en voidpekare, vilket innebär en
*         generell pekare. Detta har gjort så att funktionen malloc kan användas
*         för att returnera en pekare av godtycklig datatyp. Se till att 
*         typomvandla detta returvärde till önskad datatyp, i detta fall en
*         intpekare, via en explicit typomvandling (int*). Det fungerar att
*         inte göra detta i C (även om det är dålig kutym), men vid programmering
*         i C++ erhålls då ett kompilatorfel (implicit typomvandling från void*
*         till int*).
* 
*         När funktionen malloc anropas så sker ett försök att allokera önskad
*         mängd minne. Detta lyckas om det finns en tillräcklig mängd konsekutivt
*         minne på heapen. Annars returneras en nullpekare. Kontrollera alltid
*         returvärdet från funktionen malloc. Om null retureras så får ni 
*         hantera detta utefter vad ni finner lämpligt. I detta program avslutas
*         programmet om detta sker enligt nedan:
* 
*         if (!data) return 1;
* 
*         Det går också att skriva if (data == 0) eller if (data == NULL).
* 
*      2. Funktionen realloc används för att omallokera ett befintligt fält
*         enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)realloc(
*            <pekare till minnet som ska omallokeras>, <mängden minne i byte>);
* 
*         Som exempel, för att omallokera det fält som pekaren data ovan pekar
*         på så att det rymmer 40 heltal och låta en kopiapekare peka på det
*         omallokerade fältet kan följande instruktion användas:
* 
*         int* copy = (int*)realloc(data, sizeof(int) * 40);
*          
*         Vid lyckad omallokering frigörs det gamla minnet om detta ligger
*         på en annan adress, vilket därmed inte behöver göras manuellt.
*         Vid misslyckad minnesallokering returneras null, precis som för
*         funktionen malloc. För att undvika att skriva över adressen till
*         det gamla fältet med null så bör en kopiapekare ta emot returvärdet
*         från realloc (adressen till det nya fältet). Endast vid lyckad
*         omallokering (returvärdet är inte lika med null) bör pekaren till
*         det ursprungliga fältet sättas till att peka på adressen till det
*         nya fältet (den adress kopiapekaren pekar på). Annars ifall
*         minnesallokeringen misslyckas så bibehålls adressen till det gamla 
*         fältet, då kopiapekaren tog emot null från funktionen realloc.
*         Se i programmet nedan hur en pekare döpt copy används för att 
*         omallokera ett fält som pekas på av en pekare döpt data:
* 
*      3. Funktionen free används för att frigöra/deallokera dynamiskt 
*         allokerat minne enligt nedan:
* 
*         free(<pekare till minnet som ska frigöras>);
* 
*         Som exempel, för att frigöra det minne som pekas på av pekaren data
*         ovan kan följande instruktion användas:
* 
*         free(data);
* 
*         Viktigt är att alltid sätta pekaren till minnet till null efter
*         deallokeringen. Annars fortsätter pekaren att pekar på den adress
*         där minnet tidigare låg. Detta kan bjuda in misstag, exempelvis
*         att vi råkar genomförs tilldelning till denna adress, vilket kan
*         medföra att programmet kraschar. En sådan pekare kallas dangling 
*         pointer och bör alltså undvikas. 
*
*         Pekaren data ovan kan sättas till null genom att tilldela denna adressen 0:
* 
*         data = 0;
* 
*         Alternativt kan makrot NULL användas:
* 
*         data = NULL;        
********************************************************************************/
#include <stdio.h>  /* Innehåller funktionalitet för utskrift och inmatning. */
#include <stdlib.h> /* Innehåller funktionalitet för dynamisk minnesallokering. */

/********************************************************************************
* int_array_assign: Fyller arrayen till bredden med heltal med angivet stegvärde.
* 
*                   - self: Pekare till arrayen som ska tilldelas.
*                   - size: Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - step: Stegvärdet, dvs. differensen mellan varje element.
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
* int_array_print: Skriver ut heltal lagrade i array via angiven utström, där
*                  standardutenhet stdout används som default för utskrift
*                  i terminalen.
*
*                   - self   : Pekare till arrayen vars innehåll ska skrivas ut.
*                   - size   : Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - ostream: Pekare till angiven utström (default = stdout).
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
* main: Allokerar minne för ett fält som rymmer 20 heltal på heapen. Ifall
*       minnesallokeringen misslyckades (null returnerades från malloc) så 
*       avslutas programmet med felkod 1. Annars fylls fältet till bredden
*       med heltal räknat från 0 med stegvärde 2 (0, 2, 4, ... 38), följt av
*       utskrift i terminalen. 
*
*       Därefter omallokeras fältet så att det rymmer 40 heltal i stället. 
*       För att inte förlora adressen till det ursprungliga fältet ifall 
*       minnesallokeringen misslyckas så används en kopiapekare, som pekar på 
*       det nya fältet. Ifall minnesallokeringen misslyckas kommer då denna
*       pekare att peka på null (det fanns inte utrymme för det större fältet),
*       medan det ursprunliga fältet kvarstår och adressen är bibehållen (utan
*       kopiapekaren hade adressen till det gamla fältet skrivits över med null
*       och vi hade fått en minnesläcka).
* 
*       Ifall omallokeringen lyckades sätts den ursprungliga pekaren till att
*       peka på det nya fält som kopiapekaren pekar på. Det gamla fältet har 
*       då frigjorts via funktionen realloc och behöver därmed inte frigöras 
*       manuellt av oss. Därefter tilldelas den nyligen allokerade delen av 
*       fältet med heltal räknade från 0 med stegvärde -2. De heltal som 
*       tilldelades tidigare kvarstår alltså, de nya talen läggs på de 20 nya
*       adresserna som har allokerats.
* 
*       Därefter skrivs innehållet lagrat i fältet ut i terminalen samt till
*       en textfil döpt "data.txt". Slutligen frigörs minnet som har allokerats
*       för fältet och pekaren till fältet sätts till null. Detta bör alltid
*       göras efter frigörande av minnet, annars ligger pekaren kvar och pekar
*       där fältet tidigare låg (innan det raderades). Dynamiskt allokerat minne
*       måste alltid frigöras av användaren. Om detta missas så frigörs inte
*       minnet förrän då du startar om din dator!
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