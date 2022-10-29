#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

#include "Functions.h"
using namespace std;

const int FUNCTION_GENERATION_COUNT = 3; // Количество генераторов последовательностей
const int FUNCTION_SORT_COUNT = 2;       // Количество методов сортировки

const char OUT_PATH[] = "output//";      // Путь для сохранения выходных данных
const char input[] = "Input.txt";        // Название входного файла

const char* GENERATORS[] = {             
    {"allRandom"},
    {"upRegularize"},
    {"DownRegularize"}
};

const char* SORT_FUNCTIONS[] = {
    {"insertSort"},
    {"shellSort"}
};


int main()
{

    setlocale(LC_ALL, "ru");
          /*****************
          *   ПЕРЕМЕННЫЕ   *
          *****************/

    bool devKey;    // Отладочная печать
    
    int size;       // Размер массива
    int minValue;   // Нижняя граница генерации
    int maxValue;   // Верхняя граница генерации

    int transfers = 0;
    int comparisons = 0;

    int* array;     // Массив с исходными данными
    int* arr;       // Сортируемый массив в который мы переносим данные из исходного массива
    char* out;


    void* (*menuFunctionGeneration[FUNCTION_GENERATION_COUNT])
        (int* arr,              // Указатель на наш массив
         int size,             // Размер массива
         int minValue,    // Нижняя граница
         int maxValue     // Верхняя граница

            ) = {
      &allRandom,               // Генерация псевдослучайной последовательности чисел
      &upRegularize,            // Генерация упорядоченной по возрастанию последовательности
      &downRegularize           // Генерация упорядоченной по убыванию последовательности
    };

    void* (*menuFunctionSort[FUNCTION_SORT_COUNT])
        (
            int* arr,           // Указатель на сортируемый массив
            int size,            // Размер массива
            bool devKey,
            int &transfers,
            int &comparisons
            ) = {
            &insertSort,        // Сортировка вставками
            &shellSort          // Сортировка Шелла
    };

    ifstream ifs(input);

    if (ifs.is_open()) { //Считываем данные из файла
        ifs >> devKey;
        ifs >> size;
        ifs >> minValue;
        ifs >> maxValue;


        array = new int[size]; 
        arr = new int[size];

        for (int i = 0; i < FUNCTION_GENERATION_COUNT; i++) { // Проходим по всем вариантам набора данных всеми алгоритмами сортировки 
            cout << "   " << "-----------------------------------------" << endl;

            menuFunctionGeneration[i](array, size, minValue, maxValue);

            cout << "   " << setw(5) << GENERATORS[i] << ':' << endl;
            if (devKey) {                
                cout << "   " << setw(5) << "Исходный массив:" << endl;
                printArray(array, size);
                cout << endl;
            }

            for (int j = 0; j < FUNCTION_SORT_COUNT; j++) {

                for (int i = 0; i < size; i++) {
                    arr[i] = array[i]; 
                }

                cout <<"   " << SORT_FUNCTIONS[j] << ';' << endl;

                auto begin = chrono::steady_clock::now();	// Запуск отсчёта

                menuFunctionSort[j](arr, size, devKey,transfers,comparisons); //Сам вызов функции

                auto end = std::chrono::steady_clock::now();	// получаем время по окончанию 
                auto timeOfWork = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
               

                ofstream ofs(OUT_PATH + string(GENERATORS[i]) + '_' + string(SORT_FUNCTIONS[j]) + string(".txt"));

                

                ofs << "Исходный массив:" << endl;
                for (int i = 0; i < size; i++) {
                    ofs << setw(5) << right << array[i];
                }
                ofs << endl<<endl;

                ofs << "Отсортированный массив:" << endl;
                for (int i = 0; i < size; i++) {
                    ofs << setw(5) << right << arr[i];
                }
                ofs << endl;


                ofs << "Время выполнения сортировки: " << timeOfWork.count() << endl
                    << "Сравнений:   " << setw(8) << right<< comparisons << endl
                    << "Перемещений: " << setw(8) << right<< transfers << endl;
                
                if (devKey) {
                    cout << "   " << setw(5) << "Отсортированный массив:" << endl;
                    printArray(arr, size);
                }

                cout << endl
                    << "   " <<"Перемещений: \t"<<transfers<<endl
                    << "   " <<"Сравнений: \t\t"<<comparisons<<endl<<endl;
                ofs.close();
            }
        }
    }
    else {
        cout << "File not founded." << endl;
    }
}

