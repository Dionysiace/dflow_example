#include <mpi.h>
#include <iostream>
#include <cstring>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

void writeFile(double* pp, int x_grid, int y_grid, const char* fileName) {
    FILE* fp;//文件指针

    /*文件的打开*/
    fp = fopen(fileName, "w");//csv文件可以直接用excel打开
    if (fp == NULL) //判断如果文件指针为空
    {
        printf("File cannot open! ");
        exit(0); //在以0的形式退出，必须在文件开头有#include <stdlib.h>,stdlib 头文件即standard library标准库头文件
    }

    //写入东西
    for (int i = 0; i <= y_grid - 1; i++)
    {
        for (int j = 0; j <= x_grid - 1; j++) {
            fprintf(fp, "%f,", *(pp + i * x_grid + j));//!!!!!尤其注意这里要用逗号隔开，因为excel表里面就默认识别逗号隔开的才能分类fprintf（文件指针，格式字符串，列表）

        }
        fprintf(fp, "\t\n");
    } //关闭文件 
    fclose(fp);
    printf("Write file finish\n");
    fflush(stdout);
}

void readFile(const char* fileName, float* readInput) {
    FILE* fp;//文件指针

    /*文件的打开*/
    fp = fopen(fileName, "r");//csv文件可以直接用excel打开
    if (fp == NULL) //判断如果文件指针为空
    {
        printf("File cannot open! ");
        exit(0); //在以0的形式退出，必须在文件开头有#include <stdlib.h>,stdlib 头文件即standard library标准库头文件
    }

    //写入东西
    for (int i = 0; i < 11; i++)
    {
        int ret = fscanf(fp, "%f", (readInput+i));
    } //关闭文件 
    fclose(fp);
    //printf("Read input file finish\n");
    fflush(stdout);
}

int my_itoa(int val, char* buf)
{
    const unsigned int radix = 10;

    char* p;
    unsigned int a;        //every digit
    int len;
    char* b;            //start of the digit char
    char temp;
    unsigned int u;

    p = buf;
    if (val < 0)
    {
        *p++ = '-';
        val = 0 - val;
    }
    u = (unsigned int)val;
    b = p;
    do
    {
        a = u % radix;
        u /= radix;
        *p++ = a + '0';
    } while (u > 0);
    len = (int)(p - buf);
    *p-- = 0;
    //swap
    do
    {
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;
    } while (b < p);
    return len;
}


int main(void)
{
    MPI_Init(NULL, NULL);

    int rank, nproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    MPI_Win win;
    MPI_Aint size;

    float* readInput=(float*)malloc(sizeof(float)*1);
    readFile("/tmp/mpiwin/input.txt",readInput);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Starting process %d\n", rank);
    fflush(stdout);

    if (rank == 0)
    {
        char buf[10]="",path[30]="/tmp/mpiwin/";
        int len = my_itoa((int)*(readInput), buf);
        writeFile(pp, x_grid, y_grid, strcat(path,strcat(buf, "_result.csv")));
    }

    free(readInput);
    MPI_Win_free(&win);
    MPI_Finalize();
    return 0;
}
