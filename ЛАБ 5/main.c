#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILENAME "5.txt"

double** matrix_make (int k);
void matrix_clear (double** A, int N);

int main()
{
    char group[100];
    char name[100];
    double x1;
    double x2;
    double delta;
    int N;

    FILE* fp=fopen(FILENAME, "r");
    FILE* fp_output=fopen("5_out.txt", "w");
    FILE* fp_binary=fopen("5_bin.txt", "w+b");
    if (fp==NULL || fp_output==NULL || fp_binary==NULL)
    {
        printf("Error, one of the files don't exist");
        exit(0);
    }

    fscanf(fp, "%lf %lf %d %lf %s %s", &x1, &x2, &N, &delta, group, name);
    fclose(fp);

    if (N==0)
    {
        N=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(N-1);
    }
    fclose(fp);

    fprintf(fp_output, "**********************************\n");
    fprintf(fp_output, "\t* N * X * F(X) *\t\n");
    fprintf(fp_output, "**********************************\n");
    fwrite(&N, sizeof(int), 1, fp_binary);

    for(int i=0; i<N; i++)
    {
        double y=((pow(x1,3))/30) - 4 * (pow(x1,2)) + 50;

        fprintf(fp_output, "\t| %d| %.2lf| %.2lf|\t\n",i+1,x1,y);
        fprintf(fp_output, "+----------+----------+----------+\n");

        fwrite(&x1, sizeof(double), 1, fp_binary);
        fwrite(&y, sizeof(double), 1, fp_binary);
        x1=x1+delta;
    }
    fclose(fp_output);
    fclose(fp_binary);
    fp_binary = fopen("5_bin.txt", "r+b");

    int k;
    printf("%s %s\n", group, name);
    printf("**********************************\n");
    printf("\t* N * X * F(X) *\t\n");
    printf("**********************************");
    fread(&k, sizeof(int), 1, fp_binary);
    printf("\n");
    double** A = matrix_make(k);
    for(int i=0; i<k; i++)
    {
        int l;
        A[0][i]=i+1;
        l = (int)A[0][i];
        printf("%d ", l);
        for(int j=1; j<3; j++)
        {
            double val;
            fread(&val, sizeof(double), 1, fp_binary);
            A[j][i] = val;
            printf("%lf ", A[j][i]);
        }
    printf("\n");
    }
    matrix_clear(A, 3);
    return 0;
}

double** matrix_make(int k)
{
    double** A =(double**)malloc(3*sizeof(double*));
    for(int i=0; i<3; i++)
    {
        A[i]=(double*)malloc(k*sizeof(double));
    }
    return A;
}

void matrix_clear(double** A, int N)
{
    for(int i=0; i<N; i++)
    {
        free(A[i]);
    }
    free(A);
}
