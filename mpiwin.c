#include <mpi.h>
#include <iostream>
#include <cstring>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

void writeFile(int data, const char* fileName) {
    FILE* fp;//文件指针

    /*文件的打开*/
    fp = fopen(fileName, "w");//csv文件可以直接用excel打开
    if (fp == NULL) //判断如果文件指针为空
    {
        printf("File cannot open! ");
        exit(0); //在以0的形式退出，必须在文件开头有#include <stdlib.h>,stdlib 头文件即standard library标准库头文件
    }

    //写入东西
    fprintf(fp, "%s,", "hellow world");//!!!!!尤其注意这里要用逗号隔开，因为excel表里面就默认识别逗号隔开的才能分类fprintf（文件指针，格式字符串，列表）
    
    //关闭文件 
    fclose(fp);
    printf("Write file finish\n");
    fflush(stdout);
}

int main(void)
{
    MPI_Init(NULL, NULL);

    int rank, nproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    MPI_Win win;
    MPI_Aint size;

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Starting process %d\n", rank);
    fflush(stdout);

    if (rank == 0)
    {
        char path[30]="/tmp/mpiwin/";
        writeFile(0, strcat(path,result.csv"));
    }

    MPI_Win_free(&win);
    MPI_Finalize();
    return 0;
}
