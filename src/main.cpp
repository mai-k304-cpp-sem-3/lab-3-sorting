#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

#include "functions.h"

using namespace std;

const int FUNCTION_GENERATION_COUNT = 3; // Количество генераторов последовательностей
const int FUNCTION_SORT_COUNT = 2;       // Количество методов сортировки

const char OUT_PATH[] = "output//";      // Путь для сохранения выходных данных
const char input[] = "Input.txt";        // Название входного файла

const char VerticalLine = (char)186; //"║" - Вертикальная линия
const char HorizontalLine = (char)205; //"═" - Горизонтальная линия
const char TopLeftCorner = (char)201; //"╔" - Левый верхний угол
const char TopRightCorner = (char)187; //"╗" - Правый верхний угол
const char BottomLeftCorner = (char)200; //"╚" - Левый нижний угол
const char BottomRightCorner = (char)188; //"╝" - Правый нижний угол
const char LeftJunction = (char)185; //"╣" - вертикальная "труба влево"
const char RightJunction = (char)204; //"╠" - вертикальная "труба вправо"
const char BottomJunction = (char)203; //"╦" - Горизонтальная вниз "труба"
const char TopJunction = (char)202; //"╩" - Горизонтальная вниз "труба"
const char CrossJunction = (char)206; //"╬" - пересечение линий
const char Space = (char)32;

const int space = 20;

const char* GENERATORS[] = {
    {"allRandom"},
    {"upRegularize"},
    {"downRegularize"}
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

    long long transfers = 0;
    long long comparisons = 0;

    int* array;     // Массив с исходными данными
    int* arr;       // Сортируемый массив в который мы переносим данные из исходного массива


    void* (*menuFunctionGeneration[FUNCTION_GENERATION_COUNT]) (
        int* arr,              // Указатель на наш массив
        int size,             // Размер массива
        int minValue,    // Нижняя граница
        int maxValue     // Верхняя граница
        ) = {
        &allRandom,               // Генерация псевдослучайной последовательности чисел
        &upRegularize,            // Генерация упорядоченной по возрастанию последовательности
        &downRegularize           // Генерация упорядоченной по убыванию последовательности
    };

    void* (*menuFunctionSort[FUNCTION_SORT_COUNT]) (
        int* arr,           // Указатель на сортируемый массив
        int size,            // Размер массива
        bool devKey,
        long long & transfers,
        long long & comparisons
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
            cout << "   -------------------------------------------" << endl;
            menuFunctionGeneration[i](array, size, minValue, maxValue);

            if (devKey) {
                cout << "   " << setw(5) << "Исходный массив:" << endl;
                printArray(array, size);
                cout << endl;
            }
            else {
                setlocale(LC_ALL, "C");

                cout << TopLeftCorner << setfill(HorizontalLine) << setw(space * 4)
                    << TopRightCorner << endl;

                cout << VerticalLine << setfill(Space)
                    << setw(space * 4 - 1) << right << GENERATORS[i] << VerticalLine << endl;


                cout << RightJunction << setfill(HorizontalLine)
                    << setw(space) << BottomJunction << setw(space)
                    << BottomJunction << setw(space)
                    << BottomJunction << setw(space)
                    << LeftJunction << endl;


                cout << VerticalLine << setfill(Space)
                    << setw(space - 1) << right << "Function" << VerticalLine
                    << setw(space - 1) << right << "time" << VerticalLine
                    << setw(space - 1) << right << "counts" << VerticalLine
                    << setw(space - 1) << right << "transfers" << VerticalLine << endl;
            }

            for (int j = 0; j < FUNCTION_SORT_COUNT; j++) {


                for (int i = 0; i < size; i++) {
                    arr[i] = array[i];
                }

                auto begin = chrono::steady_clock::now();	// Запуск отсчёта

                menuFunctionSort[j](arr, size, devKey, transfers, comparisons); //Сам вызов функции

                auto end = std::chrono::steady_clock::now();	// получаем время по окончанию 
                auto timeOfWork = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

                ofstream ofs(string(GENERATORS[i]) + '_' + string(SORT_FUNCTIONS[j]) + string(".txt"));

                ofs << "Исходный массив:" << endl;          // Печать в файл
                for (int i = 0; i < size; i++) {
                    ofs << setw(5) << right << array[i];
                }
                ofs << endl << endl;

                ofs << "Отсортированный массив:" << endl;
                for (int i = 0; i < size; i++) {
                    ofs << setw(5) << right << arr[i];
                }
                ofs << endl;
                if (!devKey) {
                    // ╠══╬══╬══╬══╣
                    cout << RightJunction << setfill(HorizontalLine)
                        << setw(space) << CrossJunction
                        << setw(space)
                        << CrossJunction << setw(space)
                        << CrossJunction << setw(space)
                        << LeftJunction << endl;

                    cout << VerticalLine << setfill(Space)
                        << setw(space - 1) << right << SORT_FUNCTIONS[j] << VerticalLine
                        << setw(space - 1) << right << timeOfWork.count() << VerticalLine
                        << setw(space - 1) << right << comparisons << VerticalLine
                        << setw(space - 1) << right << transfers << VerticalLine << endl;
                }

                ofs << "Время выполнения сортировки: " << timeOfWork.count() << endl
                    << "Сравнений:   " << setw(8) << right << comparisons << endl
                    << "Перемещений: " << setw(8) << right << transfers << endl;

                if (devKey) {
                    cout << "   " << setw(5) << "Отсортированный массив:" << endl;
                    printArray(arr, size);
                }

                ofs.close();
            }
            if (!devKey) {
                // ╚══╩══╩══╩══╝
                cout << BottomLeftCorner << setfill(HorizontalLine)
                    << setw(space) << TopJunction << setw(space)
                    << TopJunction << setw(space) << TopJunction
                    << setw(space) << BottomRightCorner << endl;
            }
        }
    }
    else {
        cout << "File not founded." << endl;
    }
}

