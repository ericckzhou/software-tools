#define SUPERVISOR(regular) regular + 5 

int main() {
    int regular_pay = 20;
    int hours_worked = 10;
    printf("pay is %d\n", (hours_worked * SUPERVISOR(regular_pay)));
    //  rest omitted

/*
# 1 "preprocessor.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "preprocessor.c"


int main() {
    int regular_pay = 20;
    int hours_worked = 10;
    printf("pay is %d\n", (hours_worked * regular_pay + 5));

}
*/
}