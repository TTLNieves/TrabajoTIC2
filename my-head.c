#include <stdio.h>
#include <stdlib.h>
#include <string.h>// requerida por función exit



void
filecopy(FILE *ifp, FILE *ofp)  // copia archivo ifp a archivo ofp
{
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

void
linecopy(FILE *ifp, FILE *ofp, int lineas)  // copia archivo ifp a archivo ofp
{
    int i,c;
    for (i=0; i<lineas;i++){
        while ((c = getc(ifp)) != EOF && (c = getc(ifp) != "\n")) {
            putc(c, ofp);
        }
        putc((int) "\n", ofp);
    }
}


int
main(int argc, char *argv[])
{
    FILE *fp;               // tipo declarado en stdio.h, al igual que stdin y stdout
    char *prog = argv[0];// nombre del programa para errores
    int lineas;
    if (*argv[1]=="-" && atoi(argv[1])){
        int lineas=argv[1];
    }else{
        filecopy(stdin, stdout);
    }


    if(argc == 1) {         // sin argumentos en la línea de comandos, copia stdin
        filecopy(stdin, stdout);
    } else {                // con argumentos, abre cada uno de los archivos
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {   // chequea retorno exitoso de fopen
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                linecopy(fp, stdout,lineas);
                fclose(fp);
            }
        }
    }

    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    exit(0);
}