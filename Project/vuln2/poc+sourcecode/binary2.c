#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

char* mysteryEncoder(char input_str[], int len_str) {
    // Character set of base64 encoding scheme
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
     
    // Resultant string
    char *res_str = (char *) malloc(1000 * sizeof(char));
     
    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;
     
    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (i = 0; i < len_str; i += 3) {
            val = 0, count = 0, no_of_bits = 0;
            for (j = i; j < len_str && j <= i + 2; j++) {
                // binary data of input_str is stored in val
                val = val << 8;

                // (A + 0 = A) stores character in val
                val = val | input_str[j];
                 
                // calculates how many time loop
                // ran if "MEN" -> 3 otherwise "ON" -> 2
                count++;
            }
 
            no_of_bits = count * 8;
 
            // calculates how many "=" to append after res_str.
            padding = no_of_bits % 3;
 
            // extracts all bits from val (6 at a time)
            // and find the value of each block
            while (no_of_bits != 0) {
                // retrieve the value of each block
                if (no_of_bits >= 6) {
                    temp = no_of_bits - 6;
                     
                    // binary of 63 is (111111) f
                    index = (val >> temp) & 63;
                    no_of_bits -= 6;        
                }
                else {
                    temp = 6 - no_of_bits;
                     
                    // append zeros to right if bits are less than 6
                    index = (val << temp) & 63;
                    no_of_bits = 0;
                }
                res_str[k++] = char_set[index];
            }
    }
 
    // padding is done here
    for (i = 1; i <= padding; i++)
    {
        res_str[k++] = '=';
    }
 
    res_str[k] = '\0;';
 
    return res_str;
}

char* mysteryDecoder(char encoded[], int len_str) {
    char* decoded_string;
 
    decoded_string = (char*)malloc(sizeof(char) * 1000);
 
    int i, j, k = 0;
 
    // stores the bitstream.
    int num = 0;
 
    // count_bits stores current
    // number of bits in num.
    int count_bits = 0;
 
    // selects 4 characters from
    // encoded string at a time.
    // find the position of each encoded
    // character in char_set and stores in num.
    for (i = 0; i < len_str; i += 4) {
        num = 0, count_bits = 0;
        for (j = 0; j < 4; j++) {
            // make space for 6 bits.
            if (encoded[i + j] != '=') {
                num = num << 6;
                count_bits += 6;
            }
 
            /* Finding the position of each encoded
            character in char_set
            and storing in "num", use OR
            '|' operator to store bits.*/
 
            // encoded[i + j] = 'E', 'E' - 'A' = 5
            // 'E' has 5th position in char_set.
            if (encoded[i + j] >= 'A' && encoded[i + j] <= 'Z')
                num = num | (encoded[i + j] - 'A');
 
            // encoded[i + j] = 'e', 'e' - 'a' = 5,
            // 5 + 26 = 31, 'e' has 31st position in char_set.
            else if (encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
                num = num | (encoded[i + j] - 'a' + 26);
 
            // encoded[i + j] = '8', '8' - '0' = 8
            // 8 + 52 = 60, '8' has 60th position in char_set.
            else if (encoded[i + j] >= '0' && encoded[i + j] <= '9')
                num = num | (encoded[i + j] - '0' + 52);
 
            // '+' occurs in 62nd position in char_set.
            else if (encoded[i + j] == '+')
                num = num | 62;
 
            // '/' occurs in 63rd position in char_set.
            else if (encoded[i + j] == '/')
                num = num | 63;
 
            // ( str[i + j] == '=' ) remove 2 bits
            // to delete appended bits during encoding.
            else {
                num = num >> 2;
                count_bits -= 2;
            }
        }
 
        while (count_bits != 0) {
            count_bits -= 8;
 
            // 255 in binary is 11111111
            decoded_string[k++] = (num >> count_bits) & 255;
        }
    }
 
    // place NULL character to mark end of string.
    decoded_string[k] = '\0';
 
    return decoded_string;
}


char *first_name(int nread, char *f_name) {
    // Vuln 1 - Overread
    // overflow secret if name is larger than the size

    int secret = 0xdeadc0de;
    char fname[SIZE] = {0};

    puts("This binary is just a fix of the previous binary that had a lot of bugs. Sorry about that :)");

    puts("Enter your first name: \n");
    nread = read(0,fname,0x10000);
    // printf("secret: %x\n", secret);
    if (secret == 20211225) {
        puts("Yikes! You found the 1st vulnerability!");
        exit(0);
    }
    else if (nread > SIZE) {
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

    char flag[10] = "hiddentext";
    char buf[SIZE] = {0};
    char lname[SIZE] = {0};
    // printf("lname: %zu\n", sizeof(lname));
    puts("Then your last name: \n");
    scanf("%s",lname);
    // printf("lname: %s\n", lname); 
    strncpy(buf, lname, SIZE); 
    // printf("buf: %s\n", buf); 
    // printf("flag: %s\n", flag);
    // printf("flag: %s\n", mysteryDecoder("bmV3ZmxhZw==", 12));
    if (strcmp(flag, mysteryDecoder("bmV3ZmxhZw==", 12)) == 0) { //bmV3ZmxhZw==
        puts("Yikes! You found the 2nd vulnerability!");
        exit(0);
    }
    else if (strlen(buf) > SIZE) {
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

    for (int i = 0; i < strlen(fname)/2; i++) {
        sum += (int)fname[i] * 17227;
    }
    for (int i = 0; i < strlen(lname)/2; i++) {
        sum += (int)lname[i] * 17227;
    }

    // printf("sum: %d\n", sum);

    if ((sum % 2 == 0) && (sum >= 0)) {
        printf("Your full name is %s, %s.\n", fname, lname);
        exit(0);
    }
    else if ((sum % 2 == 1) && (sum >= 0)) {
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

    char *f_name = malloc(SIZE*sizeof(char));
    char *l_name = malloc(SIZE*sizeof(char));

    f_name = first_name(0, f_name);
    char f_name_new[SIZE] = {0};
    strncpy(f_name_new,f_name,SIZE-1);
    f_name_new[strlen(f_name)-1] = '\0';

    l_name = last_name(l_name); 
    char l_name_new[SIZE] = {0};
    strncpy(l_name_new,l_name,SIZE-1);
    l_name_new[strlen(l_name)] = '\0';

    int c_sum = char_sum(f_name_new, l_name_new);
    exit(0);
}