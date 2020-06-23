#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User{
    char* ID;
    char* pswrd;
    char* Alvl; // Уровень доступа
};

struct Book {
    char* ISBN;
    char* auth;
    char* name;
    int vsego;
    int ostalos;
};

struct Student{
    char* ID;
    char* Surname;
    char* Name;
    char* Fathersname;
    char* Faculty;
    char* Dir; // Направление
};

//Сигнатуры функций

/*Базовые функции для обработки данных*/

#include "help.h"

/*Создание списка*/

void List(FILE* fl, int s); //Вывести на консоль всю базу данных Студентов
struct Student* mcdir(struct Student* S, int o, FILE* fl); // Создат массив структур типа Студент из файла
struct Book* mcdirb(struct Book* B, int o, FILE* fl); // Аналог для типа Бук


/*Функции БД Студентов*/

void AddaStd(FILE* fl, int strok); // Добавление студента в БД
void find_this_MF(FILE* fl, int strok); // Найти студента по АйДи
void delete(FILE* fl, int strok); // Удалить студента по АйДи
char* enter_a_DB(FILE* fl); // Войти в БД (логин и пароль). Возвращает строку с уровнем доступа
int menustud(int UP, FILE* file, int stroki); //меню, использовавшееся для студентов


/*Функции БД Книг*/

int menubooks (int UP, FILE* b, int k);// Аналог менюстд
void Listbook(FILE* fl, int s); // Вывести на консоль всю базу данных Книг
void AddaBook(FILE* fl, int strok); // Добавить книгу
void deleteb(FILE* b, int strok); // Удалить книгу
void takeAbook(FILE* fb, int stroch); // Забрать книгу
void returnAbook(FILE* fb, int stroch); // Вернуть книгу


int main() {
    char* privelege;
    FILE* a = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\Usr.txt", "r+");
    privelege = enter_a_DB(a);
    if(strcmp(privelege, "NA") == 0) exit(0);
    int UP = WhoRU(privelege);
    int i =0;
    FILE* file = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\students.txt", "r+");
    FILE* b = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\books.txt", "r+");
    int stroki = kolvo(file);
    int kbooks = kolvo(b);
    printf("Hello, and welcome to my DB\n");
    printf("You can only see the list of students if you are admin\n");
    printf("Or if you are the Decan\n");
    printf("And... ");
    if(UP == 1) {
        int in =0;
        printf("You are the admin\n");
        printf("God Bless You\n");
        priv();
        scanf("%d", &in);
        while(1){
            switch (in) {
                case 1:
                    menustud(UP, file, stroki);
                    priv();
                    scanf("%d", &in);
                    break;
                case 2:
                    menubooks(UP, b, kbooks);
                    priv();
                    scanf("%d", &in);
                    break;
                    case 3:
                        printf("Have a great time!\n");
                        exit(0);
            }
        }
    }
    if(UP == 2) {
        printf("You are the student\n");
        printf("Hey man, wassup. Here are some Books DB for ya\n");
        menubooks(UP, b, kbooks);
        }
    if(UP == 3){
        printf("Oh, sorry, you are the Decan\n");
        printf("Here are functions for you to operate the Students DB\n");
        menustud(UP, file, stroki);
    }
}

int menustud(int UP, FILE* file, int stroki) {
    int i;
        printf("What do you want to do?\n");
        printf("1)See the list\n" "2)Add a Student\n" "3)Delete a Student by ID\n" "4)Find a student by ID\n" "5)Save 'n Exit\n");
        scanf("%i", &i);
        while(1) {
            if(i<1 || i > 5) printf("No such a function");
            switch (i) {
                case 1:
                    List(file, stroki);
                    printf("\nWhat are you going to do now?\n");
                    scanf("%i", &i);
                    break;
                case 2:
                    AddaStd(file, stroki);
                    printf("\nWhat are you going to do now?\n");
                    scanf("%i", &i);
                    break;
                case 3:
                    delete(file, stroki);
                    printf("\nWhat are you going to do now?\n");
                    scanf("%i", &i);
                    break;
                case 4:
                    find_this_MF(file, stroki);
                    printf("\nWhat are you going to do now?\n");
                    scanf("%i", &i);
                    break;
                case 5:
                    printf("Goodbye!\n");
                    fclose(file);
                    return (0);
            }
        }
        return(0);
};

int menubooks (int UP, FILE* b, int k){
    int i;
    printf("What do you want to do?\n");
    printf("1)See the list\n" "2)Add a Book (Adm)\n" "3)Delete a Book by ISBN (Adm)\n" "4)Get a Book By ISBN\n" "5)Return a Book by ISBN\n" "6)Save 'n Exit\n");
    scanf("%i", &i);
    while(1) {
        if(i<1 || i > 6) {
            printf("No such a function");
            scanf("%i", &i);
            break;
        }
        switch (i) {
            case 1:
                Listbook(b, k);
                printf("\nWhat are you going to do now?\n");
                scanf("%i", &i);
                break;
            case 2:

                AddaBook(b, k);
                printf("\nWhat are you going to do now?\n");
                scanf("%i", &i);
                break;
            case 3:
                deleteb(b, k);
                printf("\nWhat are you going to do now?\n");
                scanf("%i", &i);
                break;
            case 4:
                takeAbook(b, k);
                printf("\nWhat are you going to do now?\n");
                scanf("%i", &i);
                break;
            case 5:
                returnAbook(b, k);
                printf("\nWhat are you going to do now?\n");
                scanf("%i", &i);
                break;
            case 6:
                printf("Goodbye!\n");
                fclose(b);
                return (0);
        }
    }
    return (0);
}

struct Student* mcdir(struct Student* S, int o, FILE* fl){
    int i = 0;
    rewind(fl);
    while (i < o){
        S[i].ID = Str(fl);
        S[i].Surname = Str(fl);
        S[i].Name = Str(fl);
        S[i].Fathersname = Str(fl);
        S[i].Faculty = Str(fl);
        S[i].Dir = Str(fl);
        i++;
    }
    return (S);
}

void List(FILE* fl, int s) {
    int a = 0;
    struct Student *Students = malloc(s * sizeof(struct Student));
    Students = mcdir(Students, s, fl);
    printf
            ("ID      Surname       Name        Fathersname        Faculty   Direction\n");
    while (a < s) {
        printf("%-8s%-12s  %-10s  %-20s %-6s  %-20s\n", Students[a].ID, Students[a].Surname, Students[a].Name,
               Students[a].Fathersname, Students[a].Faculty, Students[a].Dir);
        a++;
    }
    rewind(fl);
}

void Listbook(FILE* b, int s) {
    int a = 0;
    struct Book* Books = malloc(s * sizeof(struct Book));
    Books = mcdirb(Books, s, b);
    printf
            ("ISBN        Author        Name                 Total  Available\n");
    while (a < s) {
        printf("%-8s  %-12s  %-20s  %-5d %-2d\n", Books[a].ISBN, Books[a].auth, Books[a].name,
               Books[a].vsego, Books[a].ostalos);
        a++;
    }
    rewind(b);
}

struct Book* mcdirb(struct Book* B, int o, FILE* b){
    int i = 0;
    rewind(b);
    while (i < o){
        B[i].ISBN = Str(b);
        B[i].auth = Str(b);
        B[i].name = Str(b);
        B[i].vsego = char_to_int(Str(b));
        B[i].ostalos = char_to_int(Str(b));
        i++;
    }
    return (B);
}

void AddaBook(FILE* blin, int strok){
    int a = 0;
    int ind;
    struct Book *Books = malloc(strok * sizeof(struct Book));
    Books = mcdirb(Books, strok, blin);
    printf("Enter ISBN:\n");
    Books[strok+1].ISBN = read_a_string();
    scanf("%s", Books[strok+1].ISBN);

    printf("Enter Author's Name:\n");
    Books[strok+1].auth = read_a_string();
    scanf("%s", Books[strok+1].auth);

    printf("Enter Book's Name:\n");
    Books[strok+1].name = read_a_string();
    scanf("%s", Books[strok+1].name);

    printf("Enter Total Count of Books:\n");
    Books[strok+1].vsego = char_to_int(read_a_string());
    scanf("%d", &Books[strok+1].vsego);

    printf("Enter Count of Books left:\n");
    Books[strok+1].ostalos = char_to_int(read_a_string());
    scanf("%d", &Books[strok+1].ostalos);


    while(a < strok){
        if(strcmp(Books[a].ISBN, Books[strok+1].ISBN) == 0) ind = 1;
        a++;
    }
    if(ind != 1){
        fputc('\n', blin);

        fputs(Books[strok+1].ISBN,blin);
        fputc(';', blin);

        fputs(Books[strok+1].auth,blin);
        fputc(';', blin);

        fputs(Books[strok+1].name,blin);
        fputc(';', blin);

        fputs(int_to_char(Books[strok+1].vsego),blin);
        fputc(';', blin);

        fputs(int_to_char(Books[strok+1].ostalos),blin);

        printf("You've succesfuly added a Book to the DB\n");
    }
    else{
        printf("This Book already exists in DB\n");
    }
}

void AddaStd(FILE* fl, int strok){
    int a = 0;
    int ind;
    struct Student *Students = malloc(strok * sizeof(struct Student));
    Students = mcdir(Students, strok, fl);
    printf("Enter ID:\n");
    Students[strok+1].ID = read_a_string();
    scanf("%s", Students[strok+1].ID);
    //fflush(stdin);
    printf("Enter Surname:\n");
    Students[strok+1].Surname = read_a_string();
    scanf("%s", Students[strok+1].Surname);
    //fflush(stdin);
    printf("Enter Name:\n");
    Students[strok+1].Name = read_a_string();
    scanf("%s", Students[strok+1].Name);
    //fflush(stdin);
    printf("Enter Fathersname:\n");
    Students[strok+1].Fathersname = read_a_string();
    scanf("%s", Students[strok+1].Fathersname);
    //fflush(stdin);
    printf("Enter Faculty ID:\n");
    Students[strok+1].Faculty = read_a_string();
    scanf("%s", Students[strok+1].Faculty);
    //fflush(stdin);
    printf("Enter Direction:\n");
    Students[strok+1].Dir = read_a_string();
    scanf("%s", Students[strok+1].Dir);
    //fflush(stdin);
    while(a < strok){
        if(strcmp(Students[a].ID, Students[strok+1].ID) == 0) ind = 1;
        a++;
    }
    if(ind != 1){

        fputs(Students[strok+1].ID,fl);
        fputc(';', fl);

        fputs(Students[strok+1].Surname,fl);
        fputc(';', fl);

        fputs(Students[strok+1].Name,fl);
        fputc(';', fl);

        fputs(Students[strok+1].Fathersname,fl);
        fputc(';', fl);

        fputs(Students[strok+1].Faculty,fl);
        fputc(';', fl);

        fputs(Students[strok+1].Dir,fl);
        fputc('\n', fl);
        printf("You've succesfuly added a student to the DB\n");
    }
    else{
        printf("This student already exists in DB\n");
    }
}

void find_this_MF(FILE* fl, int strok){
    int a = 0;

    char* find = read_a_string();

    struct Student *Students = malloc(strok * sizeof(struct Student));
    Students = mcdir(Students, strok, fl);
    printf("Enter ID:\n");
    scanf("%s", find);
    printf("That's who I found\n");
    while(a != strok){
        if(strcmp (Students[a].ID, find) == 0){
            printf("%-8s%-12s  %-10s  %-20s %-6s  %-20s\n", Students[a].ID, Students[a].Surname, Students[a].Name,
                   Students[a].Fathersname, Students[a].Faculty, Students[a].Dir);
        }
        a++;
    }
}

void delete(FILE* fl, int strok){
    int a;
    int s = 0;
    int i = 0;

    char* find = read_a_string();

    struct Student *Students = malloc(strok * sizeof(struct Student));
    Students = mcdir(Students, strok, fl);
    printf("Enter ID:\n");
    scanf("%s", find);
    while(strcmp (Students[s].ID, find) != 0){
        s++;
    }
    printf("%-8s%-12s  %-10s  %-20s %-6s  %-20s\n", Students[s].ID, Students[s].Surname, Students[s].Name,
           Students[s].Fathersname, Students[s].Faculty, Students[s].Dir);
    printf("That's who I will delete\n1)Yes\n2)No\n");

    scanf("%i", &a);
    switch (a) {
        case 1:
            while(i != strok){
                if(strcmp (Students[i].ID, find) == 0){
                    FILE* f = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\bcp.txt", "w");
                    for(int o = 0; o<strok - 1; o++){
                        fputs(Students[o].ID,f);
                        fputc(';', f);
                        fputs(Students[o].Surname,f);
                        fputc(';', f);
                        fputs(Students[o].Name,f);
                        fputc(';', f);
                        fputs(Students[o].Fathersname,f);
                        fputc(';', f);
                        fputs(Students[o].Faculty,f);
                        fputc(';', f);
                        fputs(Students[o].Dir,f);
                        fputc('\n', f);
                    }
                    fclose(f);
                    FILE* fo = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\students.txt", "w");
                    int o = 0;
                    while(o < strok-1){
                        if(o == s) o++;
                        fputs(Students[o].ID,fo);
                        fputc(';', fo);

                        fputs(Students[o].Surname,fo);
                        fputc(';', fo);

                        fputs(Students[o].Name,fo);
                        fputc(';', fo);

                        fputs(Students[o].Fathersname,fo);
                        fputc(';', fo);

                        fputs(Students[o].Faculty,fo);
                        fputc(';', fo);

                        fputs(Students[o].Dir,fo);
                        fputc('\n', fo);
                        o++;
                    }
                    fclose(fo);
                }
                i++;
            }
            break;
        case 2:
            break;
    }
}

char* enter_a_DB(FILE* fil){
    int s = kolvo(fil);
    char* UsrID;
    char* Pass;
    int flg = 0;
    int aflg = 0;
    char* priv;
    struct User* Users = malloc(s * sizeof(struct User));
    for (int o = 0; o < s; o++){
        Users[o].ID = Str(fil);
        Users[o].pswrd = Str(fil);
        Users[o].Alvl = Str(fil);
    }
    int o = 0;
    printf("What's your name tho?\n");
    UsrID = read_a_string();
    while(o<s){
        if (strcmp(UsrID, Users[o].ID) == 0) {
            flg = 1;
        }
        o++;
    }
    if (flg == 0){
        printf("There's no %s allowed in here\n", UsrID);
        return("NA");
    }
    printf("What's the password then?\n");
    Pass = read_a_string();
    int oo = 0;
    while(oo<s){
        if (strcmp(Pass, Users[oo].pswrd) == 0) {
            aflg = 1;
            priv = Users[oo].Alvl;
        }
        oo++;
    }
    if (aflg == 0){
        printf("That's a wrong pass\n");
        return("NA");
    }
    else return(priv);
}

void takeAbook(FILE* fb, int stroch){
    int f = 0;
    int h = 0;
    struct Book* Bks = malloc(stroch * sizeof(struct Book));
    Bks = mcdirb(Bks, stroch, fb);
    printf("Book's ISBN:\n");
    char* ISBN = read_a_string();
    scanf("%s", ISBN);
    while(f < stroch){
        if(strcmp(Bks[f].ISBN, ISBN) == 0){
            FILE* fo = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\books.txt", "w");
            while (h < stroch-1){
                if (f != 0){
                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);
                } else {
                    Bks[h].ostalos = Bks[h].ostalos - 1;
                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);
                }
                h++;
                while(h < stroch-1){
                    if(h == f) {
                      Bks[h].ostalos = Bks[h].ostalos - 1;
                        fputc('\n', fo);

                        fputs(Bks[h].ISBN,fo);
                        fputc(';', fo);

                        fputs(Bks[h].auth,fo);
                        fputc(';', fo);

                        fputs(Bks[h].name,fo);
                        fputc(';', fo);

                        fputs(int_to_char(Bks[h].vsego),fo);
                        fputc(';', fo);

                        fputs(int_to_char(Bks[h].ostalos),fo);

                        h++;
                    }
                    fputc('\n', fo);

                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);


                    h++;
                }
                fclose(fo);
                printf("You've taken your book");
            }
        }
       f++;
    }
}

void returnAbook(FILE* fb, int stroch){
    int f = 0;
    int h = 0;
    struct Book* Bks = malloc(stroch * sizeof(struct Book));
    Bks = mcdirb(Bks, stroch, fb);
    printf("Book's ISBN:\n");
    char* ISBN = read_a_string();
    scanf("%s", ISBN);
    while(f < stroch){
        if(strcmp(Bks[f].ISBN, ISBN) == 0){
            FILE* fo = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\books.txt", "w");
            while (h < stroch-1){
                if (f != 0){
                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);
                } else {
                    Bks[h].ostalos = Bks[h].ostalos + 1;
                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);
                }
                h++;
                while(h < stroch-1){
                    if(h == f) {
                        Bks[h].ostalos = Bks[h].ostalos + 1;
                        fputc('\n', fo);

                        fputs(Bks[h].ISBN,fo);
                        fputc(';', fo);

                        fputs(Bks[h].auth,fo);
                        fputc(';', fo);

                        fputs(Bks[h].name,fo);
                        fputc(';', fo);

                        fputs(int_to_char(Bks[h].vsego),fo);
                        fputc(';', fo);

                        fputs(int_to_char(Bks[h].ostalos),fo);

                        h++;
                    }
                    fputc('\n', fo);

                    fputs(Bks[h].ISBN,fo);
                    fputc(';', fo);

                    fputs(Bks[h].auth,fo);
                    fputc(';', fo);

                    fputs(Bks[h].name,fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].vsego),fo);
                    fputc(';', fo);

                    fputs(int_to_char(Bks[h].ostalos),fo);


                    h++;
                }
                fclose(fo);
                printf("You've returned your book");
            }
        }
        f++;
    }
}

void deleteb(FILE* b, int strok){
    int a;
    int s = 0;
    int i = 0;

    char* find = read_a_string();

    struct Book *Books = malloc(strok+1 * sizeof(struct Book));
    Books = mcdirb(Books, strok, b);
    printf("Enter ISBN:\n");
    scanf("%s", find);
    while(strcmp (Books[s].ISBN, find) != 0){
        s++;
    }
    printf("%-10s%-12s\n", Books[s].ISBN, Books[s].name);
    printf("That's who I will delete\n1)Yes\n2)No\n");

    scanf("%i", &a);
    switch (a) {
        case 1:
            while(i != strok){
                if(strcmp (Books[i].ISBN, find) == 0){
                    FILE* bb = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\bcpbooks.txt", "w");
                    for(int o = 0; o<strok - 1; o++){

                        fputs(Books[o].ISBN,bb);
                        fputc(';', bb);
                        fputs(Books[o].auth,bb);
                        fputc(';', bb);
                        fputs(Books[o].name,bb);
                        fputc(';', bb);
                        fputs(int_to_char(Books[o].vsego),bb);
                        fputc(';', bb);
                        fputs(int_to_char(Books[o].ostalos),bb);
                        fputc('\n', bb);

                    }
                    fclose(bb);
                    FILE* fo = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\books.txt", "w");
                    int o = 0;
                    if (o != s){
                        fputs(Books[o].ISBN,fo);
                        fputc(';', fo);

                        fputs(Books[o].auth,fo);
                        fputc(';', fo);

                        fputs(Books[o].name,fo);
                        fputc(';', fo);

                        fputs(int_to_char(Books[o].vsego),fo);
                        fputc(';', fo);

                        fputs(int_to_char(Books[o].ostalos),fo);
                    }
                    o++;
                    while(o < strok-1){
                        if(o == s) o++;
                        fputc('\n', fo);

                        fputs(Books[o].ISBN,fo);
                        fputc(';', fo);

                        fputs(Books[o].auth,fo);
                        fputc(';', fo);

                        fputs(Books[o].name,fo);
                        fputc(';', fo);

                        fputs(int_to_char(Books[o].vsego),fo);
                        fputc(';', fo);

                        fputs(int_to_char(Books[o].ostalos),fo);


                        o++;
                    }
                    fclose(fo);
                }
                i++;
            }
            break;
        case 2:
            break;
    }
}