#define GITHUB_USERNAME "askepen"
#define LED_MATRIX_WIDTH 48 // Width of all matrices combined. We have 3 matrices that are 16 LED's wide, thus 3 * 16 = 48
#define LED_MATRIX_HEIGHT 8 

/// Returns true if a commit was made that day
int did_commit(int week, int day_of_week) {
    // TODO: Implement this function
    return 0;
}

/// Updates the LED Matrix with commit dates 
///
///  Mapping of days to 8x16 led matrix (Ex.: F6 = Friday of week 6):   
///
///        0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15    16  17 
///  0 |  M1  M2  M3  M4  M5  M6  M7  M8  M9 M10 M11 M12 M13 M14 M15 M16 | M19 M20  ....
///  1 |  T1  T2  T3  T4  T5  T6  T7  T8  T9 T10 T11 T12 T13 T14 T15 T16 | T19 T20  ....
///  2 |  W1  W2  W3  W4  W5  W6  W7  W8  W9 W10 W11 W12 W13 W14 W15 W16 | W19 W20  .... 
///  3 |  T1  T2  T3  T4  T5  T6  T7  T8  T9 T10 T11 T12 T13 T14 T15 T16 | T19 T20  ....
///  4 |  F1  F2  F3  F4  F5  F6  F7  F8  F9 F10 F11 F12 F13 F14 F15 F16 | F19 F20  ....
///  5 |  S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 | S19 S20  ....
///  6 |  S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 | S19 S20  ....
///    +-----------------------------------------------------------------+---------     
///  7 | M17 T17 W17 T17 F17 S17 S17  -- M18 T18 W18 T18 F18 S18 S18  -- | M27 T27  ....
///
void update(int led_matrix[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH]) {
    
    // How wide each individual LED matrix is. 
    // In our case we are using three 8x16 matrices, thus each segment is 16
    const int segment_width = 16;

    // Loop over every week of the year - maybe change to 53
    for(int week = 0; week < 52; week++) {
        
        // Integer division rounds down, resulting in:
        //  ->  0 if week = [0-15], 
        //  ->  2 if week = [16-31]
        //  ->  4 if week = [32-48]
        //  ->  etc.
        int week_offset = (week / segment_width) * 2; 
        
        // Loop over every weekday. Eg. 0=monday .. 6=sunday
        for(int day_of_week = 0; day_of_week < 7; day_of_week++) {

            // Turn the light on if a commit was made that day
            int light_on = did_commit(week, day_of_week);
            
            if(week % segment_width == 0) {
                led_matrix[7][week * segment_width + day_of_week] = light_on;
            } else if (week % segment_width + 1  == 0) {
                led_matrix[7][week * segment_width + day_of_week + 7] = light_on;
            } else {
                led_matrix[day_of_week][week-week_offset] = light_on;
            }
        }
    }
    
    // TODO: Send led_matrix to driver
}

void main() {
    
    int led_matrix[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH];

    while(1) {
        update(led_matrix);
        
        // Wait 10 seconds
        // delay(10000) 
    }

}
