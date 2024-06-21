#include <stdio.h> 
// ���� ���θ� �Ǵ��ϴ� �Լ�
int is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// ���� �� ���� ��ȯ�ϴ� �Լ�
int get_days_in_month(int year, int month) {
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && is_leap_year(year)) {
        return 29;
    } 
	else 
	{
        return days_in_month[month - 1];
    }
}

// Ư�� ���� ���� ������ ����ϴ� �Լ� (1900�� 1�� 1���� ������)
int get_starting_day_of_month(int year, int month) {
    int day = 1;
    int m, y;
    int total_days = 0;

    // 1900����� year-1������� ��� �� �� ���
    for (y = 1900; y < year; y++) {
        total_days += is_leap_year(y) ? 366 : 365;
    }

    // �ش� ������ 1������ month-1�������� ��� �� �� ���
    for (m = 1; m < month; m++) {
        total_days += get_days_in_month(year, m);
    }

    // 1900�� 1�� 1���� �������̹Ƿ� 1�� ���� ���� ���
    return (total_days + 1) % 7;
}

// ������ ���θ� Ȯ���ϴ� �Լ�
int is_holiday(int year, int month, int day) {
    // ���ѹα��� �ֿ� ������ ���� (���)
    struct {
        int month;
        int day;
    } holidays[] = {
        {1, 28},
		{1, 29},
		{1,	30},   // ���� ����	    
        {3, 1},    // ������
        {5, 5},    // ��̳�
        {6, 6},    // ������
        {8, 15},   // ������
        {9, 16},
        {9, 17},
        {9, 18},   //�߼� ���� 
		{10, 3},   // ��õ��
        {10, 9},   // �ѱ۳�
        {12, 25}   // ��ź��
    };
  int num_holidays = sizeof(holidays) / sizeof(holidays[0]);
    for (int i = 0; i < num_holidays; i++) {
        if (holidays[i].month == month && holidays[i].day == day) {
            return 1;
        }
    }

    return 0;
}

void print_calendar(int year, int month) {
    const char *days_of_week[] = { "��", "��", "ȭ", "��", "��", "��", "��" };
    int days_in_month = get_days_in_month(year, month);
    int starting_day = get_starting_day_of_month(year, month);

    printf("%d�� %d��\n", year, month);
    printf("--------------------\n");

    for (int i = 0; i < 7; i++) {
        printf("%s ", days_of_week[i]);
    }
    printf("\n");

    for (int i = 0; i < starting_day; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days_in_month; day++) {
        if (is_holiday(year, month, day)) {
            printf("\033[1;31m%2d \033[0m", day); // �������� ���������� ǥ��
        } 
		else {
            printf("%2d ", day);
        }

        if ((starting_day + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    if (is_leap_year(year)) {
        printf("%d���� �����Դϴ�.\n", year);
    } 
	else {
        printf("%d���� ������ �ƴմϴ�.\n", year);
    }
}

int main() {
    int year, month;

    printf("�⵵�� �Է��ϼ���: ");
    scanf("%d", &year);

    printf("���� �Է��ϼ���: ");
    scanf("%d", &month);
     
    printf("�������� ���������� ǥ�õ˴ϴ�.\n");
    print_calendar(year, month);

    return 0;
}



