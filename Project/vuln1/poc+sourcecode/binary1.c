#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *first_name(int nread, char *f_name) {
    // Vuln 1 - Overread
    // overflow secret if name is larger than the size

    int secret = 0xdeadc0de;
    char fname[1000] = {0};
    puts("Enter your first name: \n");
    nread = read(0,fname,0x10000);
    if (secret == 0x2021) {
        puts("Yikes! You found the 1st vulnerability!");
        exit(0);
    }
    else if (nread > 1000) {
        puts("Warning! The length of your first name is too long!");
        puts("To prevent any sort of overflows and system errors, we would need to shut down for the safety of the program.");
        puts("Next time please put in a smaller string.");
        puts("Terminating now...\n");
        exit(0);
    }
    f_name = fname;
    return f_name;
}

char *last_name(char *l_name) {
    // Vuln 2 - Strcpy buffer overflow
    // overflows flag if first argument is larger than buf size

    char flag[6] = "hidden";
    char buf[1000] = {0};
    char lname[1000] = {0};
    puts("Then your last name: \n");
    scanf("%s",lname);
    strcpy(buf,lname);
    if (strcmp(flag,"flags") == 0) {
        puts("Yikes! You found the 2nd vulnerability!");
        exit(0);
    }
    else if (strlen(buf) > 1000) {
        puts("Warning! The length of your last name is too long!");
        puts("To prevent any sort of overflows and system errors, we would need to shut down for the safety of the program.");
        puts("Next time please put in a smaller string.");
        puts("Terminating now...\n");
        exit(0);
    }
    l_name = lname;
    return l_name;
}

int char_sum(char *fname, char *lname) {
    // Vuln 3 - Integer overflow

    int sum = 0;

    for (int i = 0; i < 999; i++) {
        sum += (int)fname[i] * 8999;
    }
    for (int i = 0; i < 1000; i++) {
        sum += (int)lname[i] * 8999;
    }

    if ((sum % 2 == 0) && (sum > 0)) {
        printf("Your full name is %s %s.\n", fname, lname);
        exit(0);
    }
    else if ((sum % 2 == 1) && (sum > 0)) {
        printf("Your full name is %s %s.\n", lname, fname);
        exit(0);
    }
    else {
        puts("Yikes! You found the 3rd vulnerability!");
        exit(0);
    }
    puts("End of program. Terminating...");
    return 0;
}

int main() {

    int size = 1000;
    char *f_name = malloc(1000*sizeof(char));
    char *l_name = malloc(1000*sizeof(char));

    f_name = first_name(0, f_name);
    char f_name_new[1000] = {0};
    strncpy(f_name_new,f_name,999);
    f_name_new[strlen(f_name)-1] = '\0';


    l_name = last_name(l_name); 
    char l_name_new[10] = {0};
    strncpy(l_name_new,l_name,1000);
    l_name_new[strlen(l_name)] = '\0';

    int c_sum = char_sum(f_name_new, l_name_new);
    exit(0);
}