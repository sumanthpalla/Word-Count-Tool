// include the standard libraries and input/output
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<wctype.h>
#include<locale.h>
#include<wchar.h> // wide character 

/*
 @brief Info structure containing counted bytes, characters, words and lines

 */

typedef struct 
{
    /* data */
    unsigned long bytes;
    unsigned long chars;
    unsigned long words;
    unsigned long lines;
} Info;

/*
* @brief function that calculates chars, words and lines

* @param fd file descriptor we are reading from

* @return Info struct
*/

Info read_from_fd(FILE *fd){
    // wint_t : An integral type capable of storing any valid value of wchar_t, or WEOF.
    wint_t wc;

    // wopen = word open, meaning that word is being read;
    bool wopen = false;

    // new fancy way initialzing structs

    Info info = {.bytes = 0, .chars = 0, .words = 0, .lines = 0};

    // improved by buffering but reading one char at a time
    // works for now
    char buff[8];
    
    while(WEOF != (wc = fgetwc(fd))){
        info.chars++;

        // convert wide character to multibyte characters and the length to the sum of bytes
        info.bytes += wctomb(buff,wc);
        // wide character representing a new line L'\n'
        if(wc == L'\n')info.lines++;

        // check if the wide character is space 
        bool space = iswspace(wc);
        
        // stop reading the word if we see space else increase the word count
        if(wopen){
            if(space)wopen = false;
        }
        else{
            if(!space){
                wopen = true;
                info.words++;
            }
        }
    }

    // return info;

    return info;
}
/*
@brief: Print help
*/

void print_help(){
    printf("Usage ccwc [OPTION] ... [FILE]\n\n");
    printf("Print newline, word, and byte counts for FILE. A word is a non-zero-length sequence of printable characters delimited by white space.\n\n");
    printf("-c \t print the byte count \n");
    printf("-m \t print the character count \n");
    printf("-l \t print the newline count");
    printf("-w \t print the word count \n\n");
    printf("Without FILE, read standard input \n");
}


int main(int argc, char ** argv){
    bool cflag = false, wflag = false, lflag = false, mflag = false, hflag = false;
    char *filename = NULL;

    // One file descriptor declaration can be used both for FILE and standard input
    // In UNIX world, everything is a file
    // fgets(filename,sizeof(filename),stdin);
    FILE * inputfd;

    // Locale must be set in order to properly work with wide characters

    setlocale(LC_ALL,"");
    int c;
    while((c = getopt(argc,argv,"-mcwlh"))!=-1){
        switch (c){
            case 'c':
                cflag = true;
                break;
            case 'w':
                wflag = true;
                break;
            case 'l':
                lflag = true;
                break;
            case 'm':
                mflag = true;
                break;
            case 'h':
                hflag = true;
                break;
            case '?':
                fprintf(stderr,"ERROR Unknown Option: %c\n", optopt);
                exit(EXIT_FAILURE);
            case 1:
                filename = optarg;
                break;
            
        }
    }

    if(hflag){
        print_help();
        exit(EXIT_SUCCESS);
    }

    // if no flags -c, w and l are default

    if(!cflag && !wflag && !lflag && !mflag)cflag = wflag = lflag = true;

    // if file is provided, read it
    // if not, default to standard input

    if(filename){
        inputfd = fopen(filename,"r");
        if(inputfd == NULL){
            fprintf(stderr,"[ERROR] Cannot open file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        inputfd = stdin;
    }

    // Call the function

    Info info = read_from_fd(inputfd);

    // close the stream;

    fclose(inputfd);

    if(lflag)printf(" %ld", info.lines);
    if(wflag)printf(" %ld", info.words);
    if(mflag)printf(" %ld", info.chars);
    if(cflag)printf(" %ld", info.bytes);
    if(filename)printf(" %s", filename);

    printf("\n");
    return 0;

}