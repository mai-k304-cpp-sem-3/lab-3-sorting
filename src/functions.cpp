/*********************************************************************************************
*                                       ���� ����������������                                *
**********************************************************************************************
*Project type : CMAKE_CXX_STANDARD 11                                                        *
*Project name : lab-3-sorting		        		                                         *
*File name    : function.cpp	         	                                                 *
*Language     : CPP, GCC 11.3.0                                                              *
*Programmers  : ������� ��������� ��������, �������� ������ ���������� �3�-210�-21           *
*Modified By  :                                                                              *
*Created      : 03.12.2022                                                                   *
*Last revision: 13.12.2022                                                                   *
*Comment      : ��������� ����������				                       			         *
*********************************************************************************************/






#include <iostream>
#include "functions.h"
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

/******************
*  ����� �������  *
******************/

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(5) << right << arr[i];
    }
    cout << endl;
}

void filePrintArray(int* arr, int size, char* f_name) {
    ofstream ofs(f_name);
    for (int i = 0; i < size; i++) {
        ofs << setw(5) << right << arr[i];
    }
    ofs << endl;
}

/*****************************************
*     ���������� �������������������     *
*****************************************/



/*************************
*      �������������     *
*************************/

void* allRandom( // ������� ����������� ��������������� ������������������
    int* arr, // ������
    int size, // ���������� ���������
    int minValue, // ����������� �� ����������� �����
    int maxValue // ����������� �� ������������ �����
) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = minValue + rand() % (maxValue - minValue);
    }
    return 0;
}


void* upRegularize( // ������� ����������� ������������� ������������������ �� �����������
    int* arr, // ������
    int size, // ���������� ���������
    int minValue, // ����������� �� ����������� �����
    int maxValue // ����������� �� ������������ �����
) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * (maxValue - minValue) / (size - 1) + minValue;
    }
    return 0;
}



void* downRegularize( //������� ����������� ������������� ������������������ �� ��������
    int* arr, //������
    int size, //���������� ���������
    int minValue, //����������� �� ����������� ��������� �����
    int maxValue //����������� �� ������������ ��������� �����
)
{
    for (int i = 0; i < size; i++) {
        arr[i] = i * (minValue - maxValue) / (size - 1) + maxValue;
    }
    return 0;
}

/************************************
*       ��������� ����������        *
************************************/

void* insertSort(   // ���������� ���������
    int* arr,       // ������ ���������
    int size,       // ������ �������
    bool devKey,    // �������� �� ������������� ���������
    long long & transfers,  // ����� ����������� 
    long long & comparisons // ����� ���������
) {
    transfers = 0;
    comparisons = 0;
    int temp;   // ��������� ���������� ��� �������� �������� �������� ������������ �������
    int ind;    // ������ ����������� ��������
    for (int i = 1; i < size; i++)
    {
        temp = arr[i];  // �������������� ��������� ���������� ������� ��������� �������� �������
        ind = i - 1;    // ���������� ������ ����������� �������� �������

        comparisons++;  // ������� �������� 

        while (ind >= 0 && arr[ind] > temp) // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
        {
            comparisons++; // ������� �������� 
            transfers++;   // ������� �������� 
            arr[ind + 1] = arr[ind]; // ������������ ��������� �������
            arr[ind] = temp;
            ind--;
        }

        if (devKey) {
            printArray(arr, size);
        }
    }
    return 0;
}

void* shellSort(    // ���������� �����
    int* arr,       // ������ ���������
    int size,       // ������ �������
    bool devKey,    // �������� �� ������������� ���������
    long long & transfers,  // ����� ����������� 
    long long & comparisons // ����� ���������
)
{
    transfers = 0;
    comparisons = 0;
    int interval = (size / 2);  // ����� ����������� ����� ����������

    while (interval > 0)        // ���� �������� �� ����� ����, ���������� ������������
    {
        for (int interval = size / 2; interval > 0; interval /= 2)
        {
            for (int i = interval; i < size; i ++)
            {
                int temp = arr[i];
                int j;
                comparisons++;
                for (j = i; (j >= interval) && (arr[j - interval] > temp); j -= interval) {
                    arr[j] = arr[j - interval];
                    comparisons++;
                    transfers++;
                }
                arr[j] = temp;
            }
        }
        if (devKey) {                               // ���������� ������
            printArray(arr, size);
        }
        interval /= 2;                              // ��������� ��������
    }
    return 0;
}