#include <iostream>
#include "Functions.h"
#include <iomanip>
#include <fstream>

using namespace std;

    /******************
    *  ВЫВОД МАССИВА  *
    ******************/

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << setw(5) << right << arr[i] ;
    }
    cout << endl;
}

void filePrintArray(int* arr, int size,char*f_name) {
    ofstream ofs(f_name);
    for (int i = 0; i < size; i++) {
        ofs << setw(5) << right << arr[i];
    }
    ofs << endl;
}

    /************************************
    *       АЛГОРИТМЫ СОРТИРОВКИ        *
    ************************************/

void* insertSort(   // Сортировка вставками
	int* arr,       // Массив элементов
	int size,       // Размер массива
    bool devKey,    // Выводить ли промежуточный результат
    int &transfers,  // Число перемещений 
    int &comparisons // Число сравнений
) {
    transfers = 0;
    comparisons = 0;
    int temp;   // Временная переменная для хранения значения элемента сортируемого массива
    int ind;    // Индекс предыдущего элемента
    for (int i = 1; i < size; i++)
    {
        temp = arr[i];  // Инициализируем временную переменную текущим значением элемента массива
        ind = i - 1;    // Запоминаем индекс предыдущего элемента массива
        while (ind >= 0 && arr[ind] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
        {
            comparisons++;
            transfers++;
            arr[ind + 1] = arr[ind]; // Перестановка элементов массива
            arr[ind] = temp;
            ind--;
        }

        if (devKey) {
            printArray(arr,size);
        }
    }
    return 0;
}

void* shellSort(    // Сортировка Шелла
    int* arr,       // Массив элементов
    int size,       // Размер массива
    bool devKey,    // Выводить ли промежуточный результат
    int &transfers,  // Число перемещений 
    int &comparisons // Число сравнений
) 
{
    transfers = 0;
    comparisons = 0;
    int interval = (size / 2);  // Длина промежутков между элементами

    while (interval > 0)
    {
        for (int i = 0; i < size - interval; i++)
        {
            int j = i;
            while (j >= 0  )
            {
               comparisons++;
                if (arr[j] > arr[j + interval]) {                   
                    
                    int temp = arr[j];
                    arr[j] = arr[j + interval];
                    arr[j + interval] = temp;  
                    transfers++;
                }
                j--;
            }
        }
        if (devKey) {
            printArray(arr, size);
        }
        interval /= 2;
    }
    return 0;
}