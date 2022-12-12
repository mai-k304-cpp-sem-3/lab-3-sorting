#ifndef FUNC
#define FUNC

        /*********************
        *   ������� ������   *
        *********************/

void printArray(    // ����� � �������
    int* arr,       // ������
    int size        // ������ �������
);

void filePrintArray(
    int* arr,       // ������
    int size,       // ������ �������
    char* f_name    // �������� ������������ �����
);

    /*****************************************
    *     ���������� �������������������     *
    *****************************************/

void* allRandom(    // ������� ����������� ��������� ������������������
    int* arr,       // ������
    int size,       // ���������� ���������
    int minValue,   // ����������� �� ����������� �����
    int maxValue    // ����������� �� ������������ �����
);

void* upRegularize( // ������� ����������� ������������� ������������������ �� �����������
    int* arr,       // ������
    int size,       // ���������� ���������
    int minValue,   // ����������� �� ����������� �����
    int maxValue    // ����������� �� ������������ �����
);

void* downRegularize(   //������� ����������� ������������� ������������������ �� ��������
    int* arr,           //������
    int size,           //���������� ���������
    int minValue,       //����������� �� ����������� ��������� �����
    int maxValue        //����������� �� ������������ ��������� �����
);


        /************************************
        *       ��������� ����������        *
        ************************************/

void* insertSort(   // ���������� ���������
    int* arr,       // ������ ���������
    int size,       // ������ �������
    bool devKey,    // ����� �� ������������� �����
    int &transfers, // ���������� �����������
    int &comparisons// ���������� ���������
);

void* shellSort(    // ���������� �����
    int* arr,       // ������ ���������
    int size,       // ������ �������
    bool devKey,    // ����� �� ������������� �����
    int& transfers, // ���������� �����������
    int& comparisons// ���������� ���������
);


#endif
