#include <iostream>
#include "Functions.h"

using namespace std;



/*****************************************
*     ГЕНЕРАТОРЫ ПОСЛЕДОВАТЕЛЬНОСТЕЙ     *
*****************************************/



        /*************************
        *      ЦЕЛОЧИСЛЕННЫЕ     *
        *************************/

void* allRandom( // Функция формирующая псевдослучайную последовательность
    int* arr, // Массив
    int size, // Количество элементов
    int minValue, // Ограничение на минимальное число
    int maxValue // Ограничение на максимальное число
) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = minValue + rand() % (maxValue - minValue);
    }
    return 0;
}


void* upRegularize( // Функция формирующая упорядоченную последовательность по возрастанию
    int* arr, // Массив
    int size, // Количество элементов
    int minValue, // Ограничение на минимальное число
    int maxValue // Ограничение на максимальное число
) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * (maxValue - minValue) / (size - 1) + minValue;
    }
    return 0;
}



void* downRegularize( //функция формирующая упорядоченную последовательность по убыванию
    int* arr, //массив
    int size, //количество элементов
    int minValue, //ограничение на минимальное рандомное число
    int maxValue //ограничение на максимальное рандомное число
) 
{
    arr[0] = minValue;
    for (int i = 1; i < size; i++) {
        arr[i] = (i * -round((maxValue - minValue) / (size - 1)) + maxValue);
    }
    return 0;
}


