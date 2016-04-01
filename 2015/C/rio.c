#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    //prototype
    int printVector (double* , int );
    int parseArguments (int* , double* ,int ,char** );
    void line();
    //variables
    int n;
    double A,B,C;
    double pel;
    //parse arguments and get the value of pel and n
    parseArguments(&n,&pel,argc,argv);
    //matrix
    A=1;
    B=(-pel)/(4*(n+1))-0.5;
    C=pel/(4*(n+1))-0.5;
    line();//printing
    printf("\nA=%.4f",A);
    printf("\nB=%.4f",B);
    printf("\nC=%.4f",C);
    //loop for matrification
    int k;
    double l[n],u[n],d[n];
    l[0]=d[0]=u[0]=1;
    for(k=0;k<n-1;k++){
        l[k+1]=B/d[k];
        u[k+1]=C/d[k];
        d[k+1]=A-l[k+1]*d[k]*u[k+1];
    }
    //loop for solvation
    int i,j,m;
    double z[n],y[n],x[n];
    //z
    z[0]=-B;
    for(i=1;i<n;i++)
        z[i]=-z[i-1]*l[i];
    //y
    y[0]=z[0];
    for(j=1;j<n;j++)
        y[j]=z[j]/d[j];
    //x
    x[n]=y[n];
    for(m=n-1;m>=0;m--)
        x[m]=y[m]-u[m+1]*x[m+1];
    
    line();//printing
    printf("\nVector L:\n");
    printVector(l,n);
    printf("Vector D:\n");
    printVector(d,n);
    printf("Vector U:\n");
    printVector(u,n);

    line();
    printf("\nVector Z:\n");
    printVector(z,n);
    printf("Vector Y:\n");
    printVector(y,n);
    printf("Vector X:\n");
    printVector(x,n);
    //solution::vector X
    printf("\nSOLUTION::");
    printVector(x,n);
    
    //end
    return 0;
}

int printVector (double* a, int length) {
    int i=0;
    printf("[");
    for(;i<length-1;){
        printf("%.4f,",a[i++]);
    }
    printf("%.4f]\n",a[i]);
}

int parseArguments (int* n, double* pel, int argc, char** argv) {
    //prototype
    void help();
    void error(int i);
    //variables
    double u,l,c;
    bool hasU=false,hasL=false,hasC=false,hasN=false;
    //options
    int i;
    for(i=1;i<argc;i++) {
        char* argp=argv[i];
        if(*argp=='-') {
            argp++;
            switch(*argp) {
                case '-':
                    argp++;
                    if(strcmp(argp,"help")==0)
                        help();
                    else
                        error(1);
                    break;
                case 'u': case 'U':
                    argp++;
                    if(*argp=':')
                        sscanf(argp,":%lf",&u);
                    else
                        error(1);
                    hasU=true;
                    break;
                case 'l': case 'L':
                    argp++;
                    if(*argp=':')
                        sscanf(argp,":%lf",&l);
                    else
                        error(1);
                    hasL=true;
                    break;
                case 'n': case 'N':
                    argp++;
                    if(*argp=':')
                        sscanf(argp,":%d",n);
                    else
                        error(1);
                    hasN=true;
                    break;
                case 'c': case 'C':
                    argp++;
                    if(*argp=':')
                        sscanf(argp,":%lf",&c);
                    else
                        error(1);
                    hasC=true;
                    break;
                case 'h':
                    if(strlen(argp)==1)
                        help();
                    else
                        error(1);
                    break;
		default:
		    error(1);
		    break;
            } //end of switch
        } //end of if(*argp='-')
        else
            error(1);
    } //end of for i
    if(hasN==true);
    else error(2);
    if(hasU==true && hasL==true && hasC==true);
    else error(3);
    
    *pel = u*l/c;
    printf("\npel=%.2f",*pel);
    return 0;
} //end of method
    
void error(int i) {
    char fallo[4][70];
    strcpy(fallo[0],"Error inesperado");
    strcpy(fallo[1],"Error en un argumento, compruebe que lo ha escrito bien");
    strcpy(fallo[2],"Error falta definir la variable n");
    strcpy(fallo[3],"Error falta u,l o c por definir");
    fprintf(stderr,"\nError -> %s",fallo[i]);
    fprintf(stderr,"\nPara mas informacion escriba --help o -h");
    exit(i);
}

void help() {
    printf("\nEste programa calcula las distribucion de un contaminante a lo \
largo de un rio. Para funcionar debes introducir los siguientes datos:\n");
    printf("\t--help       imprime la ayuda\n");
    printf("\t-h           imprime la ayuda\n");
    printf("\nLos siguiente valores son necesarios para hacer los calculos:\n");
    printf("\t-u:valor           introduce la velocidad en el programa\n");
    printf("\t-l:valor           introduce la longitud en el programa\n");
    printf("\t-c:valor           introduce el coeficiente en el programa\n");
    printf("\t-n:valor(entero)   introduce el numero de puntos necesarios \n");
    printf("\nPara los calculos\n   DEBE INTRODUCIR u, c, l y n");
    exit(0);
    
}

void line() {
    printf("\n--------------------------------------------");
}
