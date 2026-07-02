

#include "inc/tm4c1294ncpdt.h" // Header of the controller type
#include <stdint.h> // Header w. types for the register ..
#include <stdio.h>
#include <string.h>

#define IDLETIME 1000 // waiting time between transmissions
#define MAXSIZE 30 // max size array

int wt = 0; // auxillary variable

void PortP(void){
    // initialize Port P
    SYSCTL_RCGCGPIO_R |= 0x02000; // switch on clock for Port P
    wt++; // delay for stable clock
    // initialize Port P
    GPIO_PORTP_DEN_R |= 0x2; // enable digital pin function for PP1
    GPIO_PORTP_DIR_R |= 0x2; // set PP1 to output and PP0 as input
    GPIO_PORTP_AFSEL_R |= 0x2; // switch to alternate pin function PP1
    GPIO_PORTP_PCTL_R |= 0x10; // select alternate pin function PP1->U6Tx*/
    // **** Task 2 ****
    GPIO_PORTP_DEN_R |= (1 << 1) | (1 << 0); // enable digital pin function for PP1 and PP0
    GPIO_PORTP_AFSEL_R |= (1 << 1) | (1 << 0); // switch to alternate pin function PP1 and PP0
    GPIO_PORTP_PCTL_R |= 0x11; // select alternate pin function PP1->U6Tx and PP0->U6Rx
}

void PortM(void){
    SYSCTL_RCGCGPIO_R |= (1 << 11); // port M
    wt++;
    GPIO_PORTM_DEN_R |= 0x0F; // enabling 1-4 LEDs
    GPIO_PORTM_DIR_R |= 0x0F; // 1-4 LEDs as outputs
    GPIO_PORTM_DATA_R &= ~0x0F; // turn off 1-4 LEDs
}

void config_uart(void){
    // initialize UART6
    SYSCTL_RCGCUART_R |= 0x40; // switch on clock for UART6
    wt++; // delay for stable clock
    UART6_CTL_R &= ~0x01; // disable UART6 for config
    // initialize bitrate of 4800 bit per second
    UART6_IBRD_R = 208; // set DIVINT of BRD floor(16 MHz/16*4800 bps)
    UART6_FBRD_R = 21; // set DIVFRAC of BRD remaining fraction divide
    UART6_LCRH_R = 0x00000048; // serial format 7N2 01001000
    UART6_CTL_R = (1 << 9) | (1 << 8) | (1 << 0); // Rx, Tx and enable UART*/
    // **** Task 2 ****
    // initialize bitrate of 4800 bps
    UART6_IBRD_R = 208; // integer bdr
    UART6_FBRD_R = 0x15; // fractional bdr
    UART6_LCRH_R = (2 << 5); // 7 bits (7N2)
    UART6_LCRH_R = (1 << 3); // 2 stop bits
    UART6_CTL_R = (1 << 9) | (1 << 8) | (1 << 0); // Rx, Tx and enable UART*/
}

void idle() { // simple wait for idle state
    int i;
    for (i=IDLETIME;i>0;i--); // count down loop for waiting
}

// **** Task 2 ****
void Write_UART6(char c){
    while((UART6_FR_R & (1 << 5)) != 0); // wait until transmit FIFO is NOT FULL
    UART6_DR_R = c; // write char
}

// **** Task 2 ****
char Read_UART6(void){
    while((UART6_FR_R & (1 << 4)) != 0); // wait until receive FIFO is NOT EMPTY
    return (char)(UART6_DR_R & 0xFF); // read char
}

// **** Task 3 ****
void decode_LEDcommand(char* command){
    if (command[0] == 'l' && command[1] == 'e' && command[2] == 'd' && command[5] == '\0'){

        char action = command[3]; // + or -
        char led_num = command[4]; // 0, 1, 2, or 3

        if (action == '+'){
            if (led_num == '0') {
                GPIO_PORTM_DATA_R |= (1 << 0); // LED0 on
            } else if (led_num == '1'){
                GPIO_PORTM_DATA_R |= (1 << 1); // LED1 on
            } else if (led_num == '2'){
                GPIO_PORTM_DATA_R |= (1 << 2); // LED2 on
            } else if (led_num == '3'){
                GPIO_PORTM_DATA_R |= (1 << 3); // LED3 on
            }
        } else if (action == '-'){
            if (led_num == '0') {
                GPIO_PORTM_DATA_R &= ~(1 << 0); // LED0 off
            } else if (led_num == '1'){
                GPIO_PORTM_DATA_R &= ~(1 << 1); // LED1 off
            } else if (led_num == '2'){
                GPIO_PORTM_DATA_R &= ~(1 << 2); // LED2 off
            } else if (led_num == '3'){
                GPIO_PORTM_DATA_R &= ~(1 << 3); // LED3 off
            }
        }
    }
}


/*******************************************************************************************/

int main(void) {

    PortP();
    PortM();
    config_uart();

    // **** Task 2 ****
    char buffer[MAXSIZE]; // Rx data buffer array

    printf("hello\n");

    while(1){
        while((UART6_FR_R & 0x20) !=0); // till transmit FIFO not full
        UART6_DR_R = 0x3B; // send the character 0x3B 00111011
        idle(); // idle time
        // **** Task 2 ****
        while((UART6_FR_R & 0x20) !=0); // wait until transmit FIFO not full
        Write_UART6('\r'); // carriage return
        Write_UART6('\n'); // line feed
        Write_UART6('>'); // symbol as a prompt

        int index = 0;
        int receivingFlag = 1;

        while(receivingFlag){
            char receivedChar = Read_UART6();

            if(receivedChar == '\r' || index == (MAXSIZE - 1)){ // check for termination condition
                buffer[index] = '\0'; // last value
                receivingFlag = 0;
            } else {
                buffer[index] = receivedChar; // add received char to array
                index++; // increment index
            }
        }

        printf("\nReceived string: %s\n", buffer);
       
        // **** Task 3 ****
        decode_LEDcommand(buffer);
    }
}
