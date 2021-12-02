#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 100
#define ID_SIZE 1000
#define ROT 13

char *rot13(const char *src)
{
    if (src == NULL){
        return NULL;
    }

    char* result = malloc(strlen(src));
    
    if (result != NULL) {
        strcpy(result, src);
        char* current_char = result;

        while(*current_char != '\0') {
        
            //Only increment alphabet characters
            if ((*current_char >= 97 && *current_char <= 122) || (*current_char >= 65 && *current_char <= 90)) {
                if (*current_char > 109 || (*current_char > 77 && *current_char < 91)) {
                    //Characters that wrap around to the start of the alphabet
                    *current_char -= 13;
                }
                else {
                    //Characters that can be safely incremented
                    *current_char += 13;
                }
            }
            current_char++;
        }
    }
    return result;
}

char *name_init(char *name) {
    printf("Enter your name (limit %d characters):\n", NAME_SIZE);
    scanf("%s", name);
    // printf("strlen: %ld\n", strlen(name));
    if (strlen(name) > NAME_SIZE) {
        name_init(name);
    }
    else {
        return name;
    }
}

int id_init(int id) {
    id = 0;
    // printf("before: %d\n", id);
    printf("Enter an id for yourself (1-%d):\n", ID_SIZE);
    scanf("%d", &id);
    // printf("after: %d\n", id);
    if (id > ID_SIZE+1 || id < 0) {
        // puts("hello");
        id_init(id);
    }
    else {
        // printf("return: %d\n", id);
        return id;
    }
}

char *name_change(char *name) {
    printf("What would you like to change your name to (limit %d characters):\n", 10*NAME_SIZE);
    scanf("%s", name);
    // printf("strlen: %ld\n", strlen(name));
    if (strlen(name) > 10*NAME_SIZE) {
        name_change(name);
    }
    else {
        return name;
    }
}

int id_change(int id) {
    id = 0;
    // printf("before: %d\n", id);
    printf("What would you like to change the ID to (1-%d):\n", 10*ID_SIZE);
    scanf("%d", &id);
    // printf("after: %d\n", id);
    if (id > 10*ID_SIZE+1 || id < 0) {
        // puts("hello");
        id_change(id);
    }
    else {
        // printf("return: %d\n", id);
        return id;
    }
}

void mystery_function(char *name, int id) {
    int status;
    // printf("%d\n", status);
    puts("What would you like to change about your status?\n1) Name\n2) ID\n3) Neither\n4) Print name and id\n5) Quit");
    scanf("%d", &status);
    if (status == 1) {
        // change name
        char *name_new = malloc(10*NAME_SIZE*sizeof(char));
        name_new = name_change(name_new);
        // printf("First name: %s\nLast name: %d\n", name_new, id);
        mystery_function(name_new, id);
    }
    else if (status == 2) {
        // change id
        int id_new = 0;
        id_new = id_change(id_new);
        mystery_function(name, id_new);
    }
    else if (status == 3) {
        // can double free  
        free(name);
        mystery_function(name, id);
    }
    else if (status == 4) {
        // print name
        printf("First name: %s\nLast name: %d\n", name, id);
        mystery_function(name, id);
    }
    else if (status == 5) {
        // quit
        if (strcmp(name,"") == 0) {
            // Use-after-free
            puts("You've found a vulnerability!");   
        }
        char *name = malloc(10*NAME_SIZE*sizeof(char));
        puts("Quitting...");
    }
    else {
        mystery_function(name, id);
    }
}

void confirm_choice(char *name, int id) {
    char flag[10] = "flagtext";
    char choice[10] = {0};
    puts("Type CONFIRM to confirm your choices:");
    scanf("%s", choice);
    // printf("Flag: %s\n", flag);
    if (strcmp(rot13(flag), "CHOICE") == 0) { //PUBVPR
        // Another buffer overflow
        puts("You've found a vulnerability!");
    }
    else if (strcmp(choice, rot13("CHANGE")) == 0) {  //encrypt it
        memset(choice, 0, 10);
        puts("Good news! I'm increasing the max size of the name and ID by an order of magnitude.");
        mystery_function(name, id);
    }
    else if (strcmp(choice, "CONFIRM") != 0) {  //remove stack smashing
        confirm_choice(name, id);
        exit(0);
    }
}

int main() {

    char *name = malloc(10*NAME_SIZE*sizeof(char));
    int id;

    name = name_init(name);
    id = id_init(id);

    printf("First name: %s\nLast name: %d\n", name, id);

    confirm_choice(name, id);

    free(name);

    exit(0);
}