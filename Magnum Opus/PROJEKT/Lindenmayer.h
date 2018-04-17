#define _CRT_SECURE_NO_WARNINGS

//glowna funkcja transformujaca L-system 
int lindenmayerManual(int iter);
//funkcja pobierajaca od uzytkownika wszystkie potrzebne rzeczy do dzialania L-systemu
int lindenmayerPlus(int iter, int *var, int varN, int **rule);
//funkcja obslugujaca wczytywanie danych od uzytkownika
//varN - liczba zmiennych, consN - liczba stalych
//*var  - tablica na zmienne, *cons - tablica na stale
void vcInit(int varN, int consN, int *var, int *cons);
//funkcja obslugujaca wczytanie zasad od uzytkownika
//**rule - tablica zasad (po jednej do kazdej zmiennej)
//varN - liczba zmiennych, *var - tablica zmiennych
void rulesInit(int **rule, int varN, int *var);
//funkcja inicjacji poczatkowego lancucha znakow
void axiomInit(FILE *axiom);
//funkcja przeksztalcajaca lancuch znakow z pliku
//*pomoc - plik pomocniczy 
void transformIter(FILE *axiom, int **rule, int *var, int varN, int consN, FILE *pomoc);
//funkcja przepisujaca zawartosc jednego pliku do drugiego
void rewrite(FILE *axiom, FILE *pomoc);
//funkcja zliczajaca ilosc elementow finalnego lancucha znakow
int countH(FILE *axiom);


