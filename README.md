# Anteckningar 2022-11-03
Demonstration av dynamisk minnesallokering i C via funktioner malloc, realloc och free.

Filen "heap.c" utgör ett enkelt exempel på dynamisk minnesallokering, omallokering samt frigörande av ett fält.
Här beskrivs också ovanstående funktioner i detalj.

Filer "main.c", "int_vector.h" samt "int_vector.c" demonstrerar hur dynamiska vektorer kan implementeras i C via en strukt
döpt int_vector. Just denna vektorstrukt är anpassad för lagring av heltal, men motsvarande vektor kan implementeras
med nästan samma kod, enbart modifierad så att motsvarande datatyp allokeras och används i stället för int. Exempelvis
ska då struktens fältpekare data sättas till önskad datatyp. Vid omallokering med realloc (och malloc, men används inte här)
bör också minne allokeras för önskad datatyp x antalet element i fältet.