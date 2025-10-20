#include <stdio.h>

int main(void) {

    int hour_in_12_hours;
    int hour_in_24_hours;
    int minute_in_12_hours;
    int minute_in_24_hours;

    int array_departure_time[2][8] = {{480, 583, 679, 767, 840, 945, 1140, 1305}, {616, 712, 811, 900, 968, 1075, 1280, 1438}};

    int array_col_size = sizeof(array_departure_time[0]) / sizeof(array_departure_time[0][0]);
    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &hour_in_24_hours, &minute_in_24_hours);

    if (hour_in_24_hours > 12) {
        hour_in_12_hours = hour_in_24_hours - 12;
    }

    // printf("%d:%d PM", hour_in_12_hours, minute_in_24_hours);

    int total_minute = (hour_in_24_hours * 60) + minute_in_24_hours;

    int closest_time;
    int arrival_time;

    for (int i = 0; i < array_col_size; i++) {
        if (total_minute < array_departure_time[0][i]) {
            if ((array_departure_time[0][i] - total_minute) < (total_minute - array_departure_time[0][i - 1])) {
                closest_time = array_departure_time[0][i];
                arrival_time = array_departure_time[1][i];

                printf("%d", arrival_time);
            } else {
                closest_time = array_departure_time[0][i - 1];
            }
            break;
        }
    }

    int departure_time_hour = closest_time / 60;
    int departure_time_minute = closest_time % 60;

    int arrival_time_hour = arrival_time / 60;
    int arrival_time_minute = arrival_time % 60;

    if (total_minute > 719){
        printf("Closest departure time is: %d:%d, arriving at %d:%d", departure_time_hour, departure_time_minute, arrival_time_hour, arrival_time_minute);
    }
    
    return 0;
}