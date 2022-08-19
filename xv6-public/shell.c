#include "types.h"
#include "stat.h"
#include "user.h"
#include "stddef.h"
#include "fcntl.h"

#define MAX_INPUT 100


#define C(x)  ((x)-'@') // Ctrl + x

int length(char* str) {
    int ctr = 0;
    char* s =str;
    

    while ((*s) != '\0') {
        ctr++;
        s++;
    }
    // printf(1, "The length: %d\n", ctr);

    return ctr;
}

int cmpstr(char* str1, char* str2)
{
    char* s1 = str1, *s2 = str2;
    int n;

    if (length(s1) != length(s2)) {
        return -1;
    } else {
        n = length(s1);
        while (n--) {
            if (*s1 != *s2) return -1;
            s1++;
            s2++;
        }
    }

    return 0;
}


void copystr(char* w1, char* w2)
{
    char* t1 = w1, *t2 = w2;
    int i = 0;
    while (i != MAX_INPUT && *t2 != '\0') {
        *t1 = *t2;
        t1++;
        t2++;
        i++;
    }
    *t1 = '\0';

    
    // printf(1, "The copied string: %s\n", w1);
}

int bexec(char* tokens[MAX_INPUT/2], int lentokens) {

    char* firsttoken = tokens[0];
    int pid, i;

    // printf(1, "First token: %s\n", firsttoken);

    char* command[MAX_INPUT/2];

    for (i = 0; i < lentokens; i++) {
        command[i] = tokens[i];
    }

    command[i] = NULL;

    int st = 0;

    
    // printf(1, "%s %d\n", firsttoken, length(firsttoken));

    if (!cmpstr("ls", firsttoken)) {
        // printf(2, "hello8");
        pid = fork();
        if (pid == 0) {
            st = exec("ls", command);
            exit(st);
        }
    } else if (!cmpstr("cat", firsttoken)) {

        pid = fork();
        if (pid == 0) {
            st = exec("cat", command);
            exit(st);
        }
    } else if (!cmpstr("grep", firsttoken)) {

        pid = fork();
        if (pid == 0){
            st = exec("grep", command);
            exit(st);
        }
    } else if (!cmpstr("echo", firsttoken)) {
        
        pid = fork();
        if (pid == 0){
            st = exec("echo", command);
            exit(st);
        }
    } else if (!cmpstr("wc", firsttoken)) {
        pid = fork();
        if (pid == 0){
            st = exec("wc", command);
            exit(st);
        }
    } else if (!cmpstr("ps", firsttoken)) {
        
        pid = fork();
        if (pid == 0){
            st = exec("ps", command);
            exit(st);
        }
    } else if (!cmpstr("procinfo", firsttoken)) {
        
        pid = fork();
        if (pid == 0){
            st = exec("procinfo", command);
            exit(st);
        }
    } else if (!cmpstr("executeCommands", firsttoken)) {
        
        pid = fork();
        if (pid == 0){
            close(0);
            int fdi = open(command[1], 0);            

            char* argv[] = {"shell"};
            // main(1, argv);

            exec("shell", argv);

            close(fdi);
            exit(0);
        }
    } else if (!cmpstr("exit", firsttoken)) {
        
        return -2;

    } else {
        return -1;
    }

 
    // printf(1, "Yaya\n");

        // printf(2, "hello9");
    int status;
    
    while(wait(&status) != pid);


    // printf(2, "hello10");

    if (status == -1) {
        return -1;
    } else return 0;

}

// int iord(char** tokens, int len)
// {
//     int i, ii = -1, oi = -1, ifi = -1, ofi = -1;

//     for (i = 0; i < len; i++) {
//         if (!cmpstr(">", tokens[i])) {sc
//             ii = i;
//         } else if (!cmpstr("<", tokens[i])) {
//             oi = i;
//         }
//     }

//     if (ii != -1)
//         ifi = ii + 1;
    
//     if (oi != -1) 
//         ofi = oi + 1;

    

// }


int parsetokens(char** tokens, int len) 
{

       return  bexec(tokens, len);
}



int getcmnd(char* cmnds, char **tokens, int* x)
{
    int i, v;
    char c;
    char word[MAX_INPUT];

    int numword = 0, wi = 0;

    printf(2, "MyShell>");

    for (i = 0; i < MAX_INPUT; i++) {
        v = read(0, &c, 1);

        if (v < 1) {
            printf(2, "\n");
            exit(0); 
        }
        // printf(1, "Got a character %c\n", c);


        if (c == '\n') {
            word[wi] = '\0';
            // printf(1, "Got a newline!\n");
            if (length(word) > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            break;
        } else if (c == '|') {

            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

            word[wi] = c;
            wi++;

            v = read(0, &c, 1);

            if (c == '|') {
                word[wi] = c;
                wi++;

                word[wi] = '\0';
                if (wi > 0) {
                    tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                    copystr(tokens[numword], word);
                    numword++;
                }
                wi = 0;

                cmnds[i++] = '|';
                cmnds[i] = '|';
                continue;

            } else {
                word[wi] = '\0';
                if (wi > 0) {
                    tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                    copystr(tokens[numword], word);
                    numword++;
                }
                wi = 0;

                if (c != ' ') {
                    word[wi] = c;
                    wi++;
                }

                if (c == '\n') return 0;
            }



        } else if (c == '&') {

            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

            word[wi] = c;
            wi++;


            v = read(0, &c, 1);

            if (c == '&') {
                word[wi] = c;
                wi++;
                word[wi] = '\0';
                if (wi > 0) {
                    tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                    copystr(tokens[numword], word);
                    numword++;
                }

                wi=0;
                cmnds[i++] = '&';
                cmnds[i] = '&';
                continue;
            } 

        } else if (c == ';') {
            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

            word[wi] = c;
            wi++;

            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

        } else if (c == '>') {
            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

            word[wi] = c;
            wi++;

            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

        } else if (c == '<') {
            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;

            word[wi] = c;
            wi++;

            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;
        } else if (c == ' '){
            word[wi] = '\0';
            if (wi > 0) {
                tokens[numword] = (char*)malloc(sizeof(char) * MAX_INPUT);
                copystr(tokens[numword], word);
                numword++;
            }
            wi = 0;
        } else {
            word[wi] = c;
            wi++;
        }




        cmnds[i] = c;

    }

    *x = numword;

    cmnds[i] = '\0';

    if (length(cmnds) == 0) return -1;

    return 0;
}


int makeleftright(char **tokens, int index, int totaltokens, char** left, char** right, int* lz, int* rz) {
    int i;

    for (i = 0; i < index; i++) {
        left[i] = tokens[i];
    }

    left[i] = NULL;

    *lz = i;

    for (i = index + 1; i < totaltokens; i++) {
        right[i - index - 1] = tokens[i];
    }

    right[i] = NULL;

    *rz = i - index - 1;



    return 0;
}

int firsti(char** tokens, int len, char* str) 
{
    int i = 0;

    for (i = 0; i < len; i++) {
        if (!cmpstr(tokens[i], str)) return i;
    }

    return -1;
}

int lasti(char** tokens, int len, char* str) 
{
    int i = 0, tempi = -1;

    for (i = 0; i < len; i++) {

        if (!cmpstr(tokens[i], str)) tempi = i;
    }

    return tempi;
}


int separators(char** tokens, int len) 
{
    int sc = -1, aa = -1, oo = -1, p = -1, lt = -1, gt = -1;
    int lz, rz, flag = 0;

    int status = 0;

    int pipefd[2];

    char* left[MAX_INPUT/2];
    char* right[MAX_INPUT/2];

    // printf(1, "Hoora\n");

    sc = firsti(tokens, len, ";");
    aa = lasti(tokens, len, "&&");
    oo = lasti(tokens, len, "||");
    p = firsti(tokens, len, "|");
    lt = firsti(tokens, len, "<");
    gt = firsti(tokens, len, ">");


    // printf(1, "Hooraff\n");
    // printf(1, "%d %d %d", sc, aa, oo);

    int pid1, pid2;
    // char** left, **right;

    if (sc != -1) {
        makeleftright(tokens, sc, len  , left, right, &lz, &rz);

        // for (int i = 0; i < lz; i++) {
        //     printf(1, "%s\n", left[i]);
        // }


        // for (int i = 0; i < rz; i++) {
        //     printf(1, "%s\n", right[i]);
        // }


        pid1 = fork();

        if (pid1 == 0) {
            int st = separators(left, lz);
            exit(st);
        }


        pid2 = fork();

        if (pid2 == 0) {
            int st = separators(right, rz);
            exit(st);
        }


        
        int st1 = 0, st2 = 0;
        wait(&st1);
        wait(&st2);


        if (st1 == -2 || st2 == -2) return -2;

        if (st1 == -1 || st2 == -1) status = -1;




    } else if (aa != -1 || oo != -1) {

        
        if (aa == -1) {
            flag = 1;
        } else if (oo == -1) {
            flag = 0;
        } else {
            if (aa < oo) flag = 1;
            else flag = 0;
        }

        if (flag) {

            int st1 = 0, st2=0;
            // OR ||
            makeleftright(tokens, oo, len  , left, right, &lz, &rz);

            pid1 = fork();

            if (pid1 == 0) {
                int st = separators(left, lz);
                exit(st);
            }

            while (wait(&st1) != pid1);

            if (st1 == -2) return -2;

            // printf(1, "Statuss: %d\n", status);
            
            if (st1 == -1) {

                // printf(1, "hello\n");

                pid2 = fork();

                if (pid2 == 0) {
                    int st = separators(right, rz);
                    exit(st);
                }


                while (wait(&st2) != pid2);

                if (st2 == -2) return -2;
            }

            if (st1 == -1 || st2 == -1) status = -1;

        } else {

            // AND &&
            int st1 = 0, st2 = 0;
            makeleftright(tokens, aa, len  , left, right, &lz, &rz);

            pid1 = fork();

            if (pid1 == 0) {
                int st = separators(left, lz);
                exit(st);
            }

            while (wait(&st1) != pid1);


            if (st1 == -2) return -2;

            // printf(1, "Statuss: %d\n", status);
            
            if (st1 == 0) {

                // printf(1, "hello\n");

                pid2 = fork();

                if (pid2 == 0) {
                    int st = separators(right, rz);
                    exit(st);
                }


                while (wait(&st2) != pid2);


                if (st2 == -2) return -2;    

            }

            if (st1 == -1 || st2 == -1) status = -1;
            
        }


    } else if (p != -1) {


    makeleftright(tokens, p, len  , left, right, &lz, &rz);

    pipe(pipefd);

    pid1 = fork();

    if (pid1 == 0) {
        close(1);
        dup(pipefd[1]);
        close(pipefd[0]);
        close(pipefd[1]);
        int st = separators(left, lz);
        exit(st);
    }

    pid2 = fork();

    if (pid2 == 0) {
        close(0);
        dup(pipefd[0]);
        close(pipefd[0]);
        close(pipefd[1]);
        int st2 = separators(right, rz);
        exit(st2);
    }


    close(pipefd[0]);
    close(pipefd[1]);
    int s1 = 0, s2 = 0;
    wait(&s1);
    wait(&s2);

    
    if (s1 == -2 || s2 == -2) {
        return -2;
    }
    if (s1 == -1 || s2 == -1) status = -1;

    } else if (lt != -1) {
    makeleftright(tokens, lt, len, left, right, &lz, &rz);



        pid1 = fork();

        if (pid1 == 0) {
            close(0);
            int fdi = open(tokens[lt + 1], O_RDONLY), fdo;
            if (gt != -1) {
                close(1);
                fdo = open(tokens[gt + 1], O_WRONLY | O_CREATE);

            }
            int st = separators(left, lz);
            close(fdi);
            if (gt != -1)
                close(fdo);
            exit(st);
        }

        while (wait(&status) != pid1);

        if (status == -2) return -2;

        
    } else if (gt != -1) {
    // printf(2, "hello1");
    makeleftright(tokens, gt, len, left, right, &lz, &rz);
    // printf(2, "hello2");

    // printf(2, "hello4");


            // close(1);
            // dup(fdo);
            // printf(1, "%s\n", tokens[gt + 1]);
        pid1 = fork();

        if (pid1 == 0) {
    // printf(2, "hello5");
    close(1);
    // printf(2, "hello3");
    int fdo = open(tokens[gt + 1], O_WRONLY | O_CREATE);
            int st = separators(left, lz);
        close(fdo);
    // printf(2, "hello8");
            exit(st);
        }

        while (wait(&status) != pid1);

        if (status == -2) return -2;
        // wait(0);


        
    } else {
        // printf(1, "parseeeis\n");
    // printf(2, "hello6");
            pid1 = fork();

            if (pid1 == 0) {
                int st = parsetokens(tokens, len);
                exit(st);
            }

        while (wait(&status) != pid1);

        if (status == -2) return -2;

    // printf(2, "hello7");



    }

    return status;
}

int main(int argc, char* argv[])
{
    
    static char cmnds[MAX_INPUT];
    static char* tokens[MAX_INPUT/2];


    int totaltokens = 0;

    // int i = 0;
    int x = -1;

    
    while (1) {

        if (getcmnd(cmnds, tokens, &totaltokens) == -1)
            continue;

        // for (i = 0; i < totaltokens; i++) {
        //     printf(1, "%s\n", tokens[i]);
        // }

        x = separators(tokens, totaltokens);

        if (x == -2) exit(0);

        if (x == -1){
            printf(2, "Illegal command or arguments\n");
        }

        // if (pipeindex != -1) {

        //     // mypipe(tokens, pipeindex, totaltokens);

        // } else {
        //     // parsetokens(tokens, totaltokens);
        // }

        // freetokens(tokens);
        
    }   
    exit(0);
}