#include <iostream>
#include "Functions.h"

using namespace std;



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
    arr[0] = minValue;
    for (int i = 1; i < size; i++) {
        arr[i] = (i * -round((maxValue - minValue) / (size - 1)) + maxValue);
    }
    return 0;
}


