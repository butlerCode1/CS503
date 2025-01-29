#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    if (BUFFER_SZ < 1 || buff == NULL ||user_str == NULL) {
        return -2; //Error code 2 is the Invalid arguments error for buffer size
                        //And invalid pointers
    }
    len = 0; //Value is the length of the user string
    int buff_in = 0;//Value is the cuurent position of the buffer
    int whiteSpace = 0;//Tracks if the user String is in a white space now

    const char *ptr = user_str;

    while (*ptr != '\0') {
        if(isspace ((char)*ptr)) {
            //white space is the current char check if a space should replace a tab
            if (buff_in && !whiteSpace < BUFFER_SZ) { //if the character is white space index 
                buff[buff_in++] = ' '; // enter only one space to replace it
                len++; 
                whiteSpace = 1;

            }
        }else {
            if (buff_in < BUFFER_SZ) { // else if there no current whitespace 
                buff[buff_in++] = *ptr; //copy the index to the buffer
                len++; //increase the len variable
                whiteSpace = 0;
            } else {
                return -1;
            }
            ptr++;
        }

        if (buff_in > 0 && buff[buff_in -1] == '    ') {
            buff_in--;
            len--;
        }
        while (buff_in < BUFFER_SZ) {
            buff[buff_in++] = '.';
        }

        return len;

    }

    return 0; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int count =0;
    int i_word;
    int wc = 0;
    bool word_start = false;
    char space_char = ' ';
    int len = strlen(buff);

            for (int i = 0; i < len; i++)
        {
                char currentChar = buff;
                printf("Current Char at index %d: %c\n", i, currentChar);

                if (!word_start)
                {
                        if(currentChar == space_char) {
                                continue;
                        } else {
                                word_start = true;
                                wc++;
                        }
                } else {
                        if (currentChar == space_char) {
                                word_start = false;
                        }
                }
        }

        // Please implement
        return wc;

}

void word_print(char *str)//Display the word and the # of char in the word
{

        // suggested local variables
        int len = strlen(str);                 // length of string - aka strlen(str);
        int last_char_idx;       // index of last char - strlen(str)-1;
        int wc = 0;              // counts words
        int wlen = 0;            // length of current word
        bool word_start = false; // am I at the start of a new word

        // Please implement
         printf("%s (%d)\n", str, len);
        // printf(" Char count: %d\n ", len);

}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

void reverse_string(char *str) //Display the String in reverse
{
        // Suggested local variables
        int i = 0;
        int len = strlen(str);
        int end_idx = strlen(str) - 1; // should be length of string - 1
        int start_idx = 0;
        char tmp_char;

        // Please implement
        while (end_idx > start_idx) {
                //swap
                tmp_char = str[start_idx];
                str[start_idx] = str[end_idx];
                str[end_idx] = tmp_char;

                start_idx ++;
                end_idx --;
        } 
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    /* TODO ANSWER: 
        If argv[1] doesnt exist  the || checks the other condition as to whether the number of arguments 
        or argument count is less than 2. Since argv[1] is the second index of arguments than
        the second argument will be true. This allows the program to access the contents of the if statement 
        even if there is no second command added to the command prompt
        argv[0] would signify that there is at least one argument and the exit code of that argument
        will be called. This program is safe because of the or condition which checks the argument count 
        is first.
    */
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    /*
    This if statement has created to check if the argument count is less than three 
    This makes is so if one or two arguments (or in a more specific sense at least two) are input into the command line then 
    the cpu will process the command within the  if statement. If  the there  */
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    buff = (char *)malloc(BUFFER_SZ);
    if (buff == NULL) {
        exit(99);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
            reverse_string(input_string);
            printf("Reversed String: %s\n", input_string);
        break;
        case 'w':
        printf("Word Print\n----------\n");

                // TODO: #5. Call word_print, output should be
                //           printed by that function
                word_print(input_string);
                break;
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE