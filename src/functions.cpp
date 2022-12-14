/*********************************************************************************************
*                                       Курс ПРОГРАММИРОВАНИЕ                                *
**********************************************************************************************
*Project type : CMAKE_CXX_STANDARD 11                                                        *
*Project name : lab-3-sorting		        		                                         *
*File name    : function.cpp	         	                                                 *
*Language     : CPP, GCC 11.3.0                                                              *
*Programmers  : Пысларь Александр Игоревич, Осминнов Никита Михайлович М3О-210Б-21           *
*Modified By  :                                                                              *
*Created      : 03.12.2022                                                                   *
*Last revision: 13.12.2022                                                                   *
*Comment      : Алгоритмы сортировки				                       			         *
*********************************************************************************************/






#include <iostream>
#include "functions.h"
#include <iomanip>
#include <fstream>
#include <math.h>

using namespace std;

/******************
*  ВЫВОД МАССИВА  *
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
    for (int i = 0; i < size; i++) {
        arr[i] = i * (minValue - maxValue) / (size - 1) + maxValue;
    }
    return 0;
}

/************************************
*       АЛГОРИТМЫ СОРТИРОВКИ        *
************************************/

void* insertSort(   // Сортировка вставками
    int* arr,       // Массив элементов
    int size,       // Размер массива
    bool devKey,    // Выводить ли промежуточный результат
    long long & transfers,  // Число перемещений 
    long long & comparisons // Число сравнений
) {
    transfers = 0;
    comparisons = 0;
    int temp;   // Временная переменная для хранения значения элемента сортируемого массива
    int ind;    // Индекс предыдущего элемента
    for (int i = 1; i < size; i++)
    {
        temp = arr[i];  // Инициализируем временную переменную текущим значением элемента массива
        ind = i - 1;    // Запоминаем индекс предыдущего элемента массива

        comparisons++;  // Считаем сранения 

        while (ind >= 0 && arr[ind] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
        {
            comparisons++; // Считаем сранения 
            transfers++;   // Считаем переносы 
            arr[ind + 1] = arr[ind]; // Перестановка элементов массива
            arr[ind] = temp;
            ind--;
        }

        if (devKey) {
            printArray(arr, size);
        }
    }
    return 0;
}

void* shellSort(    // Сортировка Шелла
    int* arr,       // Массив элементов
    int size,       // Размер массива
    bool devKey,    // Выводить ли промежуточный результат
    long long & transfers,  // Число перемещений 
    long long & comparisons // Число сравнений
)
{
    transfers = 0;
    comparisons = 0;
    int interval = (size / 2);  // Длина промежутков между элементами

    while (interval > 0)        // Пока интервал не равен нулю, сортировка продолжается
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
        if (devKey) {                               // Отладочная печать
            printArray(arr, size);
        }
        interval /= 2;                              // Уменьшаем интервал
    }
    return 0;
}