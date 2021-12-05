#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NAME_SIZE 100
#define ID_SIZE 1000
#define ROT 13
#define LETTERS 26

int randomtime() {
    int totalseconds = 0;
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    totalseconds = 3600*timeinfo->tm_hour + 60*timeinfo->tm_min + timeinfo->tm_sec;
    // printf("Total seconds: %d\n", totalseconds);
    
    return totalseconds % LETTERS;
}

char *caesar(const char *src, int shift) {
    if (src == NULL) {
        return NULL;
    }
    char* result = malloc(strlen(src));
    // static char result[10] = {0};
    if (result != NULL) {
        strcpy(result, src);
        // printf("Result: %s\n", result);
        // printf("Shift %d\n", shift);

        char* current_char = result;
        while (*current_char != '\0') {
            // Only increment alphabet characters
            if ((*current_char >= 97 && *current_char <= 122) || (*current_char >= 65 && *current_char <= 90)) {
                if (*current_char >= 97 && *current_char <= 122) {
                    if (shift > (122-*current_char)) {
                        *current_char = 97+shift-(122-*current_char+1);
                        // printf("Result: %s\n", result);
                    } else {
                        *current_char += shift;
                        // printf("Result: %s\n", result);
                    }
                }
                if (*current_char >= 65 && *current_char <= 90) {
                    if (shift > (90-*current_char)) {
                        *current_char = 65+shift-(90-*current_char+1);
                        // printf("Result: %s\n", result);
                    } else {
                        *current_char += shift;
                        // printf("Result: %s\n", result);
                    }
                }
            }
            current_char++;
        }
    }
    // printf("Result: %s\n", result);
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
    printf("Enter an id for yourself (0-%d):\n", ID_SIZE);
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
    printf("What would you like to change the ID to (0-%d):\n", 10*ID_SIZE);
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

void mystery_function(char *name, int id, int total) {
    int status;
    // printf("%d\n", status);
    puts("What would you like to change about your status?\n1) Name\n2) ID\n3) Neither\n4) Print name and id\n5) Quit");
    scanf("%d", &status);
    if (status == 1) {
        // change name
        char *name_new = malloc(10*NAME_SIZE*sizeof(char));
        name_new = name_change(name_new);
        // printf("Name: %s\nID: %d\n", name_new, id);
        mystery_function(name_new, id, 0);
    }
    else if (status == 2) {
        // change id
        while (true) {
            char randomID[10] = {0};
            puts("Random? Type YES for a random ID, otherwise type anything to continue and set your own ID");
            scanf("%s", randomID);
            if (strcmp(randomID, "YES") == 0) {
                // use-after-free
                id = (int)name[0];
                if (id == 0) {
                    puts("You've found a vulnerability!");
                    exit(0);
                }
                break;
            } else {
                int id_new = 0;
                id_new = id_change(id_new);
                mystery_function(name, id_new, 0);
                break;
            }
        }
    }
    else if (status == 3) {
        // free
        free(name);
        mystery_function(name, id, 0);
    }
    else if (status == 4) {
        // print name
        printf("Name: %s\nID: %d\n", name, id);
        mystery_function(name, id, 0);
    }
    else if (status == 5) {
        // quit
        // printf("ID: %d\n", id);
        char *name = malloc(10*NAME_SIZE*sizeof(char));
        puts("Quitting...");
    }
    else if (status == 6) {
        total += id;
        if (total > id) {
            // Don't touch total
            puts("You've found a vulnerability!");
        }
        mystery_function(name, id, 0);
    }
    else {
        mystery_function(name, id, 0);
    }
}

void confirm_choice(char *name, int id) {
    // char flag[10] = "flagtext";
    char choice[10] = {0};
    puts("Type CONFIRM to confirm your choices:");
    scanf("%s", choice);
    // printf("Flag: %s\n", flag);
    // printf("Choice: %s\n",  caesar("CONVERT", randomtime()));
    // if (strcmp(choice, caesar("CHANGE", 13)) == 0) {
    if (strcmp(choice, caesar("CHANGE", randomtime())) == 0) {  //encrypt it
        memset(choice, 0, 10);
        puts("Good news! I'm increasing the max size of the name and ID by an order of magnitude.");
        int total;
        mystery_function(name, id, total);
    }   
    else if (strcmp(choice, "CONFIRM") != 0) {  //remove stack smashing
        confirm_choice(name, id);
        exit(0);
    }
}

int main() {

    // for (int i = 0; i < 26; i++) {
    //     printf("Caesar[%d]: %s\n", i, caesar("abcdefghijklmnopqrstuvwxyz", i));
    // }

    // for (int i = 0; i < 26; i++) {
    //     printf("Caesar[%d]: %s\n", i+26, caesar("ABCDEFGHIJKLMNOPQRSTUVWXYZ", i));
    // }

    char *name = malloc(10*NAME_SIZE*sizeof(char));
    int id;

    name = name_init(name);
    id = id_init(id);

    printf("Name: %s\nID: %d\n", name, id);

    confirm_choice(name, id);

    free(name);

    exit(0);
}