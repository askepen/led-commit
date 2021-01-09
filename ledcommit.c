#define GITHUB_USERNAME "askepen"
#define LED_MATRIX_WIDTH 48 //8*6
#define LED_MATRIX_HEIGHT 8 

/// Returns true if a commit was made that day
int did_commit(int week, int day_of_week, int year) {
    // TODO: Implement this function
    return 0;
}

/// Calls an API to get the current year
int get_current_year() {
    // TODO: Implement this function
    return 2021; 
}

/// Updates the LED Matrix 
void update(int led_matrix[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH], int year) {
        
    // Loop over every week of the year - maybe change to 53
    for(int week = 0; week < 52; week++) {
        
        // Integer division rounds down, resulting in:
        //  ->  0 if week = [0-7], 
        //  ->  1 if week = [8-15]
        //  ->  2 if week = [16-32]
        //  ->  etc.
        int week_offset = week / 8; 
        
        // Loop over every weekday. Eg. monday..sunday
        for(int day_of_week = 0; day_of_week < 7; day_of_week++) {

            // Turn the light on if a commit was made that day
            int light_on = did_commit(week, day_of_week, year);
            
            if(week % 8 == 0) {
                led_matrix[7][week * 8 + day_of_week] = light_on;
            } else {
                led_matrix[day_of_week][week-week_offset] = light_on;
            }
        }
    }
    
    // TODO: Send led_matrix to driver
}

void main() {

    // Fetch current year we are in 
    int year = get_current_year();

   /* 
        Layout of 8x16 led matrix (Ex.: W6 = Wednesday of week 6):   

             0  1  2  3  4  5  6  7   8   9  10  11  12  13  14  15    16  17  18  19  20  21  22  23 
        0 | M1 M2 M3 M4 M5 M6 M7 M8 M10 M11 M12 M13 M14 M15 M16 M17 | M19 M20 M21 M22 M23 M24 M25 M26 | ....
        1 | T1 T2 T3 T4 T5 T6 T7 T8 T10 T11 T12 T13 T14 T15 T16 T17 | T19 T20 T21 T22 T23 T24 T25 T26 | ....
        2 | W1 W2 W3 W4 W5 W6 W7 W8 W10 W11 W12 W13 W14 W15 W16 W17 | W19 W20 W21 W22 W23 W24 W25 W26 | .... 
        3 | T1 T2 T3 T4 T5 T6 T7 T8 T10 T11 T12 T13 T14 T15 T16 T17 | T19 T20 T21 T22 T23 T24 T25 T26 | ....
        4 | F1 F2 F3 F4 F5 F6 F7 F8 F10 F11 F12 F13 F14 F15 F16 F17 | F19 F20 F21 F22 F23 F24 F25 F26 | ....
        5 | S1 S2 S3 S4 S5 S6 S7 S8 S10 S11 S12 S13 S14 S15 S16 S17 | S19 S20 S21 S22 S23 S24 S25 S26 | ....
        6 | S1 S2 S3 S4 S5 S6 S7 S8 S10 S11 S12 S13 S14 S15 S16 S17 | S19 S20 S21 S22 S23 S24 S25 S26 | ....
          +---------------------------------------------------------+---------------------------------+     
        7 | M9 T9 W9 T9 F9 S9 S9 -  M19 T19 W19 T19 F19 S19 S19 -   | M27 T27 W27 T27 F27 S27 S27 -   | ....
    */
    int led_matrix[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH];

    while(1) {
        update(led_matrix, year);
        
        // Wait 10 seconds
        // delay(10000) 
    }

}
