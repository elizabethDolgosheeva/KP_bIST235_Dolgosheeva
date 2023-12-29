#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <locale.h>
#include <string.h>
#define MAX_COTTON 100

int space();
struct object surface_Area(struct object room);
int printFile(struct object room);
struct material* cottonFromText(char* fname, int* count_of_material);
int amount_of_box_material(struct object room);
int price_of_cotton(struct object room);


struct object {
    int space;
    int price;
    double width;
    double length;
    double higth;
    double square;
    double square_Of_Material;
    int amountInBox;
    int amount_Of_Box;
    char name[50];
};

struct material {
    char name[50];
    int width;
    int length;
    double square;
    int price;
    int amount_In_Box;
};


int main() {
    setlocale(LC_ALL, "RUS");
    while (1)
    {
        struct object room;
        char fname[50] = "Materials.txt";
        int count_of_material;
        struct material* cotton = cottonFromText(fname, &count_of_material);
        printf("Выберите материал  из предложенного каталога\n");
        int k;
        for (int i = 0; i < count_of_material; i++) {

            printf("%d. %s\n", i + 1, cotton[i].name);
            printf("Цена: %d\nДлина: %d\nШирина: %d\nПлощадь: %.2lf\nКоличество в упаковке: %d\n", cotton[i].price, cotton[i].length, cotton[i].width, cotton[i].square, cotton[i].amount_In_Box);
        }
        scanf("%d", &k);
        strcpy(room.name, cotton[k - 1].name);
        room.square_Of_Material = cotton[k - 1].square;
        room.amountInBox = cotton[k - 1].amount_In_Box;
        room.price = cotton[k - 1].price;
        printf("Вы выбрали материал - %s\n", room.name);


        room.space = space(); // Выбор пространства


        room = surface_Area(room); // Ввод параметров объекта

        while (1)
        {
            printf("                                                                         Главное меню\n");
            printf("1. Расчет площади покрытия объекта\n");
            printf("2. Подсчет количества упаковок\n");
            printf("3. Расчет суммы средств\n");
            int c;
            scanf("%d", &c);
            switch (c)
            {
            case 1:

                printf("Площадь поверхности объекта равна - %.3lf\n", room.square);
                break;
            case 2:
                room.amount_Of_Box = amount_of_box_material(room);// Подсчет количества коробок
                printf("Количество упаковок - %d\n", room.amount_Of_Box);
                break;
            case 3:
                room.price = price_of_cotton(room);
                printf("Коичество потраченных средств - %d\n", room.price); // Подсчет суммы
                break;
            default:
                printf("Введено неверное значение попробуйте еще\n");
                break;
            }
            printf("Продолжить?(Да - любое число, Нет - 0)\n");
            int d;
            scanf("%d", &d);
            if (d == 0)
            {
                break;
            }
        }

        printf("Желаете записать результаты в файл?(Да - любое число, Нет - 0)\n");
        int e;
        scanf("%d", &e);
        if (e != 0)
        {
            printFile(room); //запись результатов в файл
        }
        printf("Повторить вычисления?(Да - любое число, Нет - 0)\n");
        int g;
        scanf("%d", &g);
        if (g == 0)
        {
            break;
        }
    }


    return 0;

}

struct material* cottonFromText(char* fname, int* count_of_material) {
    FILE* file = fopen(fname, "r");//создание указателя на файл
    if (!file) {
        puts("При открытии файла произошла ошибка\n");
        return 0;
    }

    struct material* cotton = malloc(MAX_COTTON * sizeof(struct material)); // создание динамического массива
    if (!cotton) {
        puts("Не удалось выделить память для массива структур");
        return 0;
    }

    int count = 0;
    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL) { //считывание строки из файла
        if (line[0] == '№')
        {
            continue;
        }
        for (int i = 0; i < strlen(line); i++) { //присваивание в название материала название из файла
            if (line[2 + i] == ' ' && line[2 + i + 1] == ' ') { //остановка присваивания
                cotton[count].name[i] = '\0';
                break;
            }
            cotton[count].name[i] = line[2 + i];
        }
        char buffer[500];
        for (int i = 0; i < strlen(line); i++) {
            buffer[i] = line[22 + i];//удаление остатка строки
        }
        sscanf(buffer, " | %d | %d | %dх%d |", &cotton[count].price, &cotton[count].amount_In_Box, &cotton[count].length, &cotton[count].width);//присваивание в цену и кол-во квадратов материала из файла
        cotton[count].square = (double)((cotton[count].length * cotton[count].width) / 10000.0);
        count++;
    }
    fclose(file);
    *count_of_material = count; //подсчет кол-ва видов материала
    return cotton;


}

int space() {
    printf("Вы хотите покрыть материалом трехмерное пространтсво или двухмерное?\n");
    printf("Для ответа на вопрос введите 3 или 2\n");
    int i;

    scanf("%d", &i);
    while (i != 2 && i != 3)//проверка корректности ввода данных
    {
        printf("Введеное неверное значение\nПопробуйте еще раз\n");
        scanf("%d", &i);
    }
    if (i == 2)
    {
        printf("Вам необходимо покрыть двухмерное пространтсво\n");
    }
    if (i == 3)
    {
        printf("Вам необходимо покрыть трехмерное пространство\n");
    }
    return i;
}

struct object surface_Area(struct object room) {
    printf("                                                        Ввод размеров объекта\n");
    printf("Введите ширину объекта:\n");
    scanf("%lf", &room.width);
    while (room.width < 0) {
        printf("Введено неверное значение\n");
        scanf("%lf", &room.width);
    }
    printf("Введите длину объекта:\n");
    scanf("%lf", &room.length);
    while (room.length < 0)
    {
        printf("Введено неверное значение\n");
        scanf("%lf", &room.length);
    }
    if (room.space == 3)
    {
        printf("Введите высоту объекта:\n");
        scanf("%lf", &room.higth);
        while (room.higth < 0)
        {
            printf("Введено неверное значение\n");
            scanf("%lf", &room.higth);
        }
        room.square = 2 * (room.length * room.width + room.length * room.higth + room.width * room.higth);//расчет площади объекта при покрытия трехмерного пространства
    }
    else
    {
        room.square = room.width * room.length;//расчет площади объекта при покрытии двухмерного пространства 
    }

    return room;
}

int printFile(struct object room) {
    char filename[20] = "TextFile1.txt";

    FILE* file = fopen(filename, "w"); // открытие файла

    if (file == NULL)
    {
        puts("При открытии файла произошла ошибка\n");
        return 0;
    }

    fprintf(file, "Площадь объекта - %.1lf\n", room.square); // Печать результатов в файл
    fprintf(file, "Название материала - %s\n", room.name);
    fprintf(file, "Площадь покрытия одного материала - %.1lf\n", room.square_Of_Material);
    fprintf(file, "Количество коробок для покрытия - %d\n", room.amount_Of_Box);
    fprintf(file, "Потраченная сумма - %d\n", room.price);

    fclose(file);
    return 1;
}

int amount_of_box_material(struct object room) {
    room.amount_Of_Box = ceil(room.square / (room.square_Of_Material * room.amountInBox));//расчет количества упаковок с материалом
    return room.amount_Of_Box;
}

int price_of_cotton(struct object room) {
    room.price = room.amount_Of_Box * room.price;//расчет цены покрытия
    return room.price;
}