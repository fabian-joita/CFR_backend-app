# CFR_backend-app
Aplicația de căutare și rezervare călătorii cu trenul are rolul de a permite utilizatorilor să caute și să rezerve bilete pentru trenuri, iar operatorilor să gestioneze cursele și să administreze conturile utilizatorilor. 

1. Actori și Funcționalități
Operator:
Operatorul este responsabil pentru gestionarea conturilor de utilizatori și a curselor de tren.

Login Operator: Autentificarea operatorului se face pe baza unui nume de utilizator și a unei parole, care sunt deja existente într-un fișier CSV. În cazul în care numele de utilizator sau parola sunt incorecte, se va arunca o excepție.

Adăugare Cursă: Operatorul poate adăuga noi curse de tren, cu detalii precum ora de plecare, ora de sosire, orașele de plecare și sosire, precum și alte detalii. Dacă datele sunt introduse greșit (ex. format incorect al datei, orașe invalide), se vor lansa excepții.

Ștergere Cursă: Operatorul poate șterge o cursă existentă, iar aceasta va fi reflectată într-un fișier CSV.

Utilizator:
Utilizatorul este persoana care creează un cont pe platformă și efectuează rezervări pentru călătorii.

Creare Cont: Utilizatorul își creează un cont prin introducerea unui nume de utilizator, a unei parole și a unui email. Parola va trebui să îndeplinească anumite cerințe de securitate (de exemplu, să conțină cel puțin o literă mare, o literă mică, o cifră și un caracter special).

Autentificare Utilizator: După ce contul a fost creat, utilizatorul poate să se autentifice folosind numele de utilizator și parola. Dacă datele sunt greșite, se va arunca o excepție.

Căutare Cursă: Utilizatorul poate căuta curse de tren pe baza orașelor de plecare și sosire, a datei călătoriei etc.

Rezervare Loc: După ce a găsit o cursă, utilizatorul poate rezerva un loc la clasa dorită (ex. clasa 1, clasa 2). Rezervarea va necesita și ora la care a fost efectuată.

2. Securitatea Parolei și Criptarea acesteia
Un aspect important al aplicației este securizarea parolelor utilizatorilor. Parolele vor fi criptate folosind Vigenère Cipher. Algoritmul de criptare Vigenère utilizează o cheie pentru a cripta și decripta textul. Parola utilizatorului va fi criptată înainte de a fi salvată în fișierul CSV.

Estimarea Securității Parolei: Pentru a determina cât de puternică este o parolă, aplicația va implementa un algoritm de estimare a securității parolei, care va verifica:

Lungimea parolei (parolele scurte vor fi considerate slabe),
Dacă conține cel puțin o literă mare,
Dacă conține cel puțin o literă mică,
Dacă conține cel puțin o cifră,
Dacă conține cel puțin un caracter special (ex. !@#$).
Pe baza acestor criterii, parolă va primi un scor de putere:

Weak (Slabă): Parola nu îndeplinește criteriile minime de securitate.
Ok: Parola îndeplinește doar cerințele de bază.
Good (Puternică): Parola îndeplinește toate cerințele de securitate și este considerată sigură.
În cazul în care parola este considerată slabă, utilizatorul va fi nevoit să o schimbe și să introducă o parolă mai puternică. Dacă utilizatorul nu respectă cerințele minime de securitate, aplicația va arunca o excepție și va solicita din nou introducerea unei parole valide.

3. Managementul Excepțiilor
Aplicația va implementa mecanisme de management al excepțiilor pentru diverse situații care pot apărea în timpul utilizării platformei. Printre cele mai importante excepții se numără:

Operator:
Login nereușit (utilizator sau parolă greșite): Aplicația va arunca o excepție care va fi prinsă de program și va solicita operatorului să încerce din nou.
Detalii greșite la adăugarea unei curse (ex. dată greșită, orașe invalide): Va fi aruncată o excepție de tip invalid_argument care va indica detaliile greșite.
Utilizator:
Login nereușit: Dacă datele de autentificare sunt greșite, se va arunca o excepție.
Parolă slabă: Dacă utilizatorul încearcă să creeze un cont cu o parolă slabă (nu respectă cerințele minime de securitate), va fi aruncată o excepție de tip invalid_argument.
Detalii greșite la rezervarea cursei (ex. dată de rezervare incorectă): Se va arunca o excepție care va solicita utilizatorului să introducă informațiile corect.
Excepțiile vor fi gestionate folosind structuri de try-catch, pentru a captura erorile și a oferi utilizatorului mesaje de eroare clare și utile.

4. Cum va Funcționa Criptarea Vigenère
Criptarea va utiliza un algoritm Vigenère, care presupune criptarea fiecărui caracter din parolă folosind o cheie secretă. Algoritmul funcționează astfel:

Fiecare literă din parolă va fi deplasată în funcție de valoarea corespunzătoare caracterului din cheia secretă.
Dacă cheia este mai scurtă decât parola, aceasta va fi repetată pentru a se potrivi lungimii parolei.
Atunci când utilizatorul se autentifică, aplicația va folosi aceeași cheie pentru a decripta parola stocată și a o compara cu parola introdusă de utilizator.

5. Fluxul Aplicației:
Operatorul se autentifică cu user și parolă. Dacă autentificarea este reușită, poate adăuga sau șterge curse.

Utilizatorul își creează un cont cu un nume de utilizator, o parolă (care este criptată cu Vigenère), și un email valid. După autentificare, utilizatorul poate căuta curse și rezerva locuri pe trenuri.

Rezervarea: Utilizatorul poate rezerva locuri pe trenuri, alegând clasa și ora dorită. Detaliile rezervării (ora, data, clasa) vor fi verificate înainte de a fi salvate.
