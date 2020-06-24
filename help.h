#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int kolvo(FILE* fl); //Количество строк в файле
char* read_a_string(); //Считать строку из потока ввода, оканчивающуюся на Энтер
char* Str(FILE* fl); // Считать из файла отдельно то, что разделено ; или переходом на новую строку
int WhoRU(char* pr); // Определить статус пользователя 1 - админ, 2 - обычный пользователь
void priv();// Выводит список возможностей админа
char* int_to_char(int digit);
int char_to_int(char* str);

int kolvo(FILE* fl){
    int n = 1;
    char c = fgetc(fl);
    while (c != EOF){
        if (c == '\n') n++;
        c = fgetc(fl);
    }
    rewind(fl);
    return(n);
}

char* read_a_string(){
    int i = 0;
    char c;
    char* find = malloc(1 * sizeof(char));
    while ((c = getchar()) != '\n')
    {
        *(find + i) = c;
        i++;
        find = realloc(find, (i + 1) * sizeof(char));
    }
    *(find + i) = '\0';
    return (find);
}

char* Str(FILE* fl){
    char* str = malloc(1 * sizeof(char)); //место под первую букву
    int i = 0;
    char c;
    while ((c = getc(fl)) != '\n' && c != ';' && c != EOF){
        str[i] = c;
        i++;
        str = realloc(str, (i+1) * sizeof(char)); // расширение строки
    }
    str[i] = '\0'; // добавить символ конца строки

    return(str);

}

int WhoRU(char* priv){
    int U;
    if(strcmp(priv, "adm") == 0){
        U = 1;
    }
    if(strcmp(priv, "std") == 0){
        U = 2;
    }
    if(strcmp(priv, "decan") == 0){
        U = 3;
    }
    return (U);
}

void priv(){
    printf("Which DB do you need?\n");
    printf("1) Students\n");
    printf("2) Books\n");
    printf("3) I'm done\n");
}


int char_to_int(char* str){
    int digit = 0;
    int i = 0;
    while (str[i] != '\0') {
        digit = digit * 10;
        digit = digit + (str[i] - '0');
        i++;
    }
    return digit;
}

char* int_to_char(int digit){
    int n = 0;
    int* d = malloc(1 * sizeof(int));
    char* str = malloc(1 * sizeof(char));
    while (digit> 0) {
        n++;
        d[n - 1] = digit % 10;
        d = realloc(d, (n + 1) * sizeof(int));
        digit = digit / 10;
    }
    str = realloc(str, n * sizeof(char));
    for (int i = 0; i < n; ++i) {
        str[i] = d[n - i - 1] + '0';
    }
    str[n] = '\0';
    return(str);
}