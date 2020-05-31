#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char* ID;
    char* Fathersname;
    char* Name;
    char* Surname;
    char* Faculty;
    char* Dir;
};

//Сигнатуры функций

/*Базовые функции для обработки данных*/
int kolvo(FILE* fl);
char* read_a_string();
char* Str(FILE* fl);
/*Создание списка*/
void List(FILE* fl, int s);
struct Student* mcdir(struct Student* S, int o, FILE* fl);
/*Функции БД*/
void AddaStd(FILE* fl, int strok);
void find_this_MF(FILE* fl, int strok);
void delete(FILE* fl, int strok);


int main() {

    int i =0;
    FILE* file = fopen("C:\\Users\\Home\\CLionProjects\\Normal DB\\students.txt", "r+");
    int stroki = kolvo(file);
    printf("Hello, and welcome to my DB\n");
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
                printf("Goodbye!");
                fclose(file);
                exit(0);
        }
    }
    return(0);
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