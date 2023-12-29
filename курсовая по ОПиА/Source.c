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
        printf("�������� ��������  �� ������������� ��������\n");
        int k;
        for (int i = 0; i < count_of_material; i++) {

            printf("%d. %s\n", i + 1, cotton[i].name);
            printf("����: %d\n�����: %d\n������: %d\n�������: %.2lf\n���������� � ��������: %d\n", cotton[i].price, cotton[i].length, cotton[i].width, cotton[i].square, cotton[i].amount_In_Box);
        }
        scanf("%d", &k);
        strcpy(room.name, cotton[k - 1].name);
        room.square_Of_Material = cotton[k - 1].square;
        room.amountInBox = cotton[k - 1].amount_In_Box;
        room.price = cotton[k - 1].price;
        printf("�� ������� �������� - %s\n", room.name);


        room.space = space(); // ����� ������������


        room = surface_Area(room); // ���� ���������� �������

        while (1)
        {
            printf("                                                                         ������� ����\n");
            printf("1. ������ ������� �������� �������\n");
            printf("2. ������� ���������� ��������\n");
            printf("3. ������ ����� �������\n");
            int c;
            scanf("%d", &c);
            switch (c)
            {
            case 1:

                printf("������� ����������� ������� ����� - %.3lf\n", room.square);
                break;
            case 2:
                room.amount_Of_Box = amount_of_box_material(room);// ������� ���������� �������
                printf("���������� �������� - %d\n", room.amount_Of_Box);
                break;
            case 3:
                room.price = price_of_cotton(room);
                printf("��������� ����������� ������� - %d\n", room.price); // ������� �����
                break;
            default:
                printf("������� �������� �������� ���������� ���\n");
                break;
            }
            printf("����������?(�� - ����� �����, ��� - 0)\n");
            int d;
            scanf("%d", &d);
            if (d == 0)
            {
                break;
            }
        }

        printf("������� �������� ���������� � ����?(�� - ����� �����, ��� - 0)\n");
        int e;
        scanf("%d", &e);
        if (e != 0)
        {
            printFile(room); //������ ����������� � ����
        }
        printf("��������� ����������?(�� - ����� �����, ��� - 0)\n");
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
    FILE* file = fopen(fname, "r");//�������� ��������� �� ����
    if (!file) {
        puts("��� �������� ����� ��������� ������\n");
        return 0;
    }

    struct material* cotton = malloc(MAX_COTTON * sizeof(struct material)); // �������� ������������� �������
    if (!cotton) {
        puts("�� ������� �������� ������ ��� ������� ��������");
        return 0;
    }

    int count = 0;
    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL) { //���������� ������ �� �����
        if (line[0] == '�')
        {
            continue;
        }
        for (int i = 0; i < strlen(line); i++) { //������������ � �������� ��������� �������� �� �����
            if (line[2 + i] == ' ' && line[2 + i + 1] == ' ') { //��������� ������������
                cotton[count].name[i] = '\0';
                break;
            }
            cotton[count].name[i] = line[2 + i];
        }
        char buffer[500];
        for (int i = 0; i < strlen(line); i++) {
            buffer[i] = line[22 + i];//�������� ������� ������
        }
        sscanf(buffer, " | %d | %d | %d�%d |", &cotton[count].price, &cotton[count].amount_In_Box, &cotton[count].length, &cotton[count].width);//������������ � ���� � ���-�� ��������� ��������� �� �����
        cotton[count].square = (double)((cotton[count].length * cotton[count].width) / 10000.0);
        count++;
    }
    fclose(file);
    *count_of_material = count; //������� ���-�� ����� ���������
    return cotton;


}

int space() {
    printf("�� ������ ������� ���������� ���������� ������������ ��� ����������?\n");
    printf("��� ������ �� ������ ������� 3 ��� 2\n");
    int i;

    scanf("%d", &i);
    while (i != 2 && i != 3)//�������� ������������ ����� ������
    {
        printf("�������� �������� ��������\n���������� ��� ���\n");
        scanf("%d", &i);
    }
    if (i == 2)
    {
        printf("��� ���������� ������� ���������� ������������\n");
    }
    if (i == 3)
    {
        printf("��� ���������� ������� ���������� ������������\n");
    }
    return i;
}

struct object surface_Area(struct object room) {
    printf("                                                        ���� �������� �������\n");
    printf("������� ������ �������:\n");
    scanf("%lf", &room.width);
    while (room.width < 0) {
        printf("������� �������� ��������\n");
        scanf("%lf", &room.width);
    }
    printf("������� ����� �������:\n");
    scanf("%lf", &room.length);
    while (room.length < 0)
    {
        printf("������� �������� ��������\n");
        scanf("%lf", &room.length);
    }
    if (room.space == 3)
    {
        printf("������� ������ �������:\n");
        scanf("%lf", &room.higth);
        while (room.higth < 0)
        {
            printf("������� �������� ��������\n");
            scanf("%lf", &room.higth);
        }
        room.square = 2 * (room.length * room.width + room.length * room.higth + room.width * room.higth);//������ ������� ������� ��� �������� ����������� ������������
    }
    else
    {
        room.square = room.width * room.length;//������ ������� ������� ��� �������� ����������� ������������ 
    }

    return room;
}

int printFile(struct object room) {
    char filename[20] = "TextFile1.txt";

    FILE* file = fopen(filename, "w"); // �������� �����

    if (file == NULL)
    {
        puts("��� �������� ����� ��������� ������\n");
        return 0;
    }

    fprintf(file, "������� ������� - %.1lf\n", room.square); // ������ ����������� � ����
    fprintf(file, "�������� ��������� - %s\n", room.name);
    fprintf(file, "������� �������� ������ ��������� - %.1lf\n", room.square_Of_Material);
    fprintf(file, "���������� ������� ��� �������� - %d\n", room.amount_Of_Box);
    fprintf(file, "����������� ����� - %d\n", room.price);

    fclose(file);
    return 1;
}

int amount_of_box_material(struct object room) {
    room.amount_Of_Box = ceil(room.square / (room.square_Of_Material * room.amountInBox));//������ ���������� �������� � ����������
    return room.amount_Of_Box;
}

int price_of_cotton(struct object room) {
    room.price = room.amount_Of_Box * room.price;//������ ���� ��������
    return room.price;
}