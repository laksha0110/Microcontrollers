/** Default Project for TM4C1294ncpdt
 *
 * File:    main.c
 * Author:
 * Date:
 * Version:
 *
 * Blinks the onboard LED using a busy-wait loop as delay
 */

#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>

/*******************************************************************************************/

void wait(int ticks) {
    for (int i = 0; i < ticks; i++);   
}

/*******************************************************************************************/

void configure_led() {
    SYSCTL_RCGCGPIO_R       |= (0x1 << 12);  // switch on clock for Port N
    while (!(SYSCTL_PRGPIO_R & 0x1000));      // wait for clock to stabilize
    GPIO_PORTN_DEN_R        |= (0x1 << 1);   // digital I/O enable pin PN1
    GPIO_PORTN_DIR_R        |= 0x02;         // set PortN 1 Output
    GPIO_PORTN_DATA_R        = 0x00;         // set PortN Output to zero
}

/*******************************************************************************************/

void configure_portM(){
    SYSCTL_RCGCGPIO_R |= 0x00000800;
    while((SYSCTL_RCGCGPIO_R & 0x00000800)== 0); 

    GPIO_PORTM_DIR_R = 0xF0;
    GPIO_PORTM_DEN_R = 0xFF;
}

/*******************************************************************************************/

unsigned char readKey(void){
    int no_key_pressed = ;
    char key_pressed ='';
    const unsigned char x_value[4] = {0x0E, 0x0D, 0x0B, 0x07}
    const unsigned char key[4][4]= {
        '1', '2', '3', 'F'
        '4', '5', '6', 'E'
        '7', '8', '9', 'D'
        'A', '0', 'B', 'C'
    }

    for (col =0; col < 4; col++){
        GPIO_PORTN_DATA_R = x_value[col];
        wait(1000000);

        y= (GPIO_PORTM_DATA_R & 0xF0) >> 4; //keeps only the y and then shifting them by 4 bits >> 0000 yyyy

        for (row=0: row< 4; row++){
            if ((y & ( 1<< row)== 0)){     //checking which row is pressed at corresponding y
                key_pressed = key[row][col];
                no_key_pressed++;
            }

        }
    }

   if (no_key_pressed == 0){
        return 0;
    else if {no_key_pressed== 1}{
        return key_pressed;
    else{
         return 'X';
        }
    }
   } 
}
/*******************************************************************************************/

int main(void) {

    int i = 0; // loop counter

    char key, last_key;


    // Configure LED 1
    configure_led();

    configure_portM();

    while(1) {
        // toggle LED
        if ((GPIO_PORTN_DATA_R & 0x02)) // check if led is ON
            GPIO_PORTN_DATA_R &= ~0x02; // turn LED off
        else
            GPIO_PORTN_DATA_R |= 0x02;  // turn LED on

        // software delay
        wait(100000);


        /******************************************************************************************/
        key= readKey();

        if (key == 'X'){
            printf("Error: several keys pressed ");
            last_key='X';
        }else if (key != 0 && key != last_key) {
            printf("key pressed: %c\n", key);
        }else if (key==0){
            last_key=0;
        }
        /******************************************************************************************/
        
        printf("\nCounter value: %d", i++);  

          
    }
}
