#include <stdio.h> 
// 윤년 여부를 판단하는 함수
int is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// 월별 일 수를 반환하는 함수
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

// 특정 월의 시작 요일을 계산하는 함수 (1900년 1월 1일은 월요일)
int get_starting_day_of_month(int year, int month) {
    int day = 1;
    int m, y;
    int total_days = 0;

    // 1900년부터 year-1년까지의 모든 날 수 계산
    for (y = 1900; y < year; y++) {
        total_days += is_leap_year(y) ? 366 : 365;
    }

    // 해당 연도의 1월부터 month-1월까지의 모든 날 수 계산
    for (m = 1; m < month; m++) {
        total_days += get_days_in_month(year, m);
    }

    // 1900년 1월 1일이 월요일이므로 1을 더해 요일 계산
    return (total_days + 1) % 7;
}

// 공휴일 여부를 확인하는 함수
int is_holiday(int year, int month, int day) {
    // 대한민국의 주요 공휴일 정의 (양력)
    struct {
        int month;
        int day;
    } holidays[] = {
        {1, 28},
		{1, 29},
		{1,	30},   // 설날 연휴	    
        {3, 1},    // 삼일절
        {5, 5},    // 어린이날
        {6, 6},    // 현충일
        {8, 15},   // 광복절
        {9, 16},
        {9, 17},
        {9, 18},   //추석 연휴 
		{10, 3},   // 개천절
        {10, 9},   // 한글날
        {12, 25}   // 성탄절
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
    const char *days_of_week[] = { "일", "월", "화", "수", "목", "금", "토" };
    int days_in_month = get_days_in_month(year, month);
    int starting_day = get_starting_day_of_month(year, month);

    printf("%d년 %d월\n", year, month);
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
            printf("\033[1;31m%2d \033[0m", day); // 공휴일을 빨간색으로 표시
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
        printf("%d년은 윤년입니다.\n", year);
    } 
	else {
        printf("%d년은 윤년이 아닙니다.\n", year);
    }
}

int main() {
    int year, month;

    printf("년도를 입력하세요: ");
    scanf("%d", &year);

    printf("달을 입력하세요: ");
    scanf("%d", &month);
     
    printf("공휴일은 빨간색으로 표시됩니다.\n");
    print_calendar(year, month);

    return 0;
}



