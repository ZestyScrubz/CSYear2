#include <stdio.h>
#include <stdbool.h>

int main(void) {

    int hour_in_12_hours;
    int hour_in_24_hours;
    int minute_in_12_hours;
    int minute_in_24_hours;

    int array_departure_time[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};

    int array_size = sizeof(array_departure_time) / sizeof(array_departure_time[0]);
    bool flag = true;

    while (flag) {

    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &hour_in_24_hours, &minute_in_24_hours);

    // if (hour_in_24_hours > 12) {
    //     hour_in_12_hours = hour_in_24_hours - 12;
    // }

    // printf("%d:%d PM", hour_in_12_hours, minute_in_24_hours);

    int total_minute = (hour_in_24_hours * 60) + minute_in_24_hours;

    int closest_time;
    int arrival_time;

    for (int i = 0; i < array_size; i++) {
        if (total_minute < array_departure_time[0]){
            closest_time = array_departure_time[0];
            break;
        }
        if (total_minute < array_departure_time[i]) {
            if ((array_departure_time[i] - total_minute) < (total_minute - array_departure_time[i - 1])) {
                closest_time = array_departure_time[i];
            } else {
                closest_time = array_departure_time[i - 1];
            }
            break;
        } else {
            closest_time = array_departure_time[i];
        }
    }


    if (closest_time == array_departure_time[0]){
        printf("Closest departure time is: 8:00 am, arriving at 10:16 am");
    }
    if (closest_time == array_departure_time[1]){
        printf("Closest departure time is: 9:43 am, arriving at 11:52 am");
    }
    if (closest_time == array_departure_time[2]){
        printf("Closest departure time is: 11:19 am, arriving at 1:31 pm");
    }
    if (closest_time == array_departure_time[3]){
        printf("Closest departure time is: 12:47 pm, arriving at 3:00 pm");
    }
    if (closest_time == array_departure_time[4]){
        printf("Closest departure time is: 2:00 pm, arriving at 4:08 pm");
    }
    if (closest_time == array_departure_time[5]){
        printf("Closest departure time is: 3:45 pm, arriving at 5:55 pm");
    }
    if (closest_time == array_departure_time[6]){
        printf("Closest departure time is: 7:00 pm, arriving at 9:20 pm");
    }
    if (closest_time == array_departure_time[7]){
        printf("Closest departure time is: 9:45 pm, arriving at 11:58 pm");
    }

    int quit;

    printf("\n");
    printf("Enter 1 to continute or 0 to quit: ");
    scanf("%d", &quit);

        if (quit != 1){
            flag = false;
        }
    }



    return 0;
}