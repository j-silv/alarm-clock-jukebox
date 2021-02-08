#define APP0
//#define APP1
//#define APP2
//#define APP3

#include <stdio.h>
#include "system.h"
#include <unistd.h>
#include  "altera_avalon_pio_regs.h"

static void initial_message(){ printf("\n\n***CE PROGRAMME UTILISE DES POINTEURS***\n"); }

int main(void) {

	#ifdef APP0
		/* "Hello World" example.
	 *
	 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
	 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
	 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
	 * device in your system's hardware.
	 * The memory footprint of this hosted application is ~69 kbytes by default
	 * using the standard reference design.
	 *
	 * For a reduced footprint version of this template, and an explanation of how
	 * to reduce the memory footprint for a given application, see the
	 * "small_hello_world" template.
	 *
	 */
		printf("Hello from Nios II!\n");
		return 0;
	#endif

	#ifdef APP1
		/*This program demonstrates use of parallel ports in the Computer System, It displays a
		rotating pattern on the LEDs and HEXs:
		* 1. if a KEY0 is pressed, LEDs uses SW positions as a pattern
		* 2. if a KEY1 is pressed, HEXs uses inverted SW positions as a pattern */

		 volatile int * LED_ptr = (int *)LEDR_BASE; // LED address
		 volatile int * SW_switch_ptr = (int *)INTERRUPTEURS_BASE; // SW slider address
		 volatile int * KEY_ptr = (int *)BOUTONS_POUSSOIRS_BASE; // pushbutton KEY address
		 volatile int * HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE; // HEX3_HEX0 address
		 int HEX_bits = 0x0; // initial pattern for HEX displays
		 int LED_bits = 0x0; // initial pattern for LED lights
		 int SW_value; //, KEY_value;
		 int press, delay_count = 0;
		 initial_message();
		 while (1)
		 {
			 SW_value = *(SW_switch_ptr); // read the SW slider switch values

			 press = *(KEY_ptr + 3); // read the pushbutton edge capture register

			 *(KEY_ptr + 3) = press; // Clear the edge capture register

			 if (press & 0x1) // KEY0 pressed
				 LED_bits = SW_value; // set LEDs pattern using SW values
			 if (press & 0x2) // KEY1 pressed
				 HEX_bits = ~SW_value; // set HEX pattern using SW values

			 *(HEX3_HEX0_ptr) = HEX_bits; // display pattern on HEX3 ... HEX0
			 *(LED_ptr)= LED_bits;

			 if (HEX_bits & 0x80000000) HEX_bits = (HEX_bits << 1) | 1;
			 else HEX_bits = HEX_bits << 1;
			 if (LED_bits & 0x00000001) LED_bits = (LED_bits >> 1) | 0x80000000;
			 else LED_bits = (LED_bits >> 1) & 0x7FFFFFFF;
			 for (delay_count = 200000; delay_count != 0; --delay_count); // delay loop
		 }

	#endif

	#ifdef APP2
		// Application 2 : Utilisation des MACROs altera pour communiquer avec les PIOs :

		 int HEX_bits = 0x0; // initial pattern for HEX displays
		 int LED_bits = 0x0; // initial pattern for LED lights
		 int SW_value; //, KEY_value;
		 int press, delay_count = 0;
		 initial_message();


		 while (1)
		 {
			 // read the SW slider switch values
			 SW_value = IORD_ALTERA_AVALON_PIO_DATA(INTERRUPTEURS_BASE);

			 // read the pushbutton edge capture register
			 press = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE);

			 // Clear the edge capture register
			 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BOUTONS_POUSSOIRS_BASE, press);

			 // KEY0 pressed
			 if (press & 0x1)
				 LED_bits = SW_value; // set LEDs pattern using SW values
			 // KEY1 pressed
			 if (press & 0x2)
				 HEX_bits = ~SW_value; // set HEX pattern using SW values

			 // display pattern on HEX3 ... HEX0
			 IOWR_ALTERA_AVALON_PIO_DATA(HEX3_HEX0_BASE, HEX_bits);

			 // display pattern on LEDs
			 IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, LED_bits);

			 if (HEX_bits & 0x80000000) HEX_bits = (HEX_bits << 1) | 1;
			 else HEX_bits = HEX_bits << 1;
			 if (LED_bits & 0x00000001) LED_bits = (LED_bits >> 1) | 0x80000000;
			 else LED_bits = (LED_bits >> 1) & 0x7FFFFFFF;
			 for (delay_count = 200000; delay_count != 0; --delay_count); // delay loop
		 }

    #endif

	#ifdef APP3
		 // Application 3 : Realisation dune unite arithmatique simple
		 #define ADD 0x0
		 #define SUB 0x1
		 #define DIV 0x2
		 #define MULT 0x3

     /* COMMON CATHODE SEG MAPPING
        0	0111111	3F
        1	0000110	06
        2	1011011	5B
        3	1001111	4F
        4	1100110	66
        5	1101101	6D
        6	1111101	7D
        7	0000111	07
        8	1111111	7F
        9	1001111	4F

        COMMON ANODE SEG MAPPING
        0	1000000	C0
        1	1111001	F9
        2	0100100	A4
        3	0110000	B0
        4	0011001	99
        5	0010010	92
        6	0000010	82
        7	1111000	F8
        8	0000000	80
        9	0010000	90
        */

     // array position [0] correspond a afficher 0, [1] -> 1, etc.
     // position [10] -> tous les bits OFF
     // position [11] -> le signe moins (-, segment G)
     int SEG_TABLE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x3F};

		 // nous pouvons pas afficher plus que 999
		 #define MAX_ABS_VALUE 999

		 int SW_value; 		 // KEY_value;
		 int press = 0;    // tactile button value

		 int HEX_bits = 0x0; // initial pattern for HEX displays
		 int LED_bits = 0x0; // initial pattern for LED lights

     // operand1 (op1) sont les 5 bits LSBs des switches
     // operand2 (op2) sont les 5 bits MSBs des switches
		 int op1, op2 = 0x0;

     // nous n'avons pas besoin d'un op2 mask car on va decaler
     // a droite pour isoler ces bits MSBs
		 int op1_mask = 0b0000011111;

     // valeurs qu'on affiche sur notre dev kit
     // si signe = 1, alors le 4ieme hex affiche negatif, sinon
     // il n'est pas allume
		 int signe, val_absolu, reste = 0;

     // on a besoin d'une valeur temp. pour determiner 
     // le signe du resultat (mult, div, sub) et aussi pour 
     // determiner le reste
     int val_temp = 0; 

     // position [2] correspond a le MSB de l'afficheur HEX
     int resultat_bcd[3] = {0x0,0x0,0x0};
     int resultat_LEDseg[3] = {0x0,0x0,0x0};
     int LEDseg_buffer = 0x0;

     // variable de comptage
     int i = 0;

		 while(1) {

			 // clear buffer chaque fois dans la boucle
			 LEDseg_buffer = 0x0;

			 // read the SW slider switch values
			 SW_value = IORD_ALTERA_AVALON_PIO_DATA(INTERRUPTEURS_BASE);

			 // separer le resultat dans 2 operands
			 op1 = (SW_value & op1_mask);
			 op2 = (SW_value >> 5);

			 // on veut PAS effacer la valeur ou utiliser l'edge cap, car si on le fait, peu importe
       // le temps qu'on appuie sur un des bouton poussoirs, il va tout de suite
       // penser que les 2 boutons sont a 0 (clear edge_cap mets automatiquement
       // les bits a 0, et vu que si on lache pas le bouton il y aura pas de nouveau donnes
       // sur le bouton edge reg, on sera bloque a ADD!
       // on veut plutot juste lire les donnes sur le bouton!
       press = IORD_ALTERA_AVALON_PIO_DATA(BOUTONS_POUSSOIRS_BASE);

			 switch(press) {
			 	 case ADD :

           // ce n'etait pas specifie si on utilise du binaire en complement a 2, donc
           // pour cette excercice je vais dire que les operands ne le sont pas et qu'ils sont juste
           // positifs... par consequent une addition sera toujours positifs
           // nous n'aurons jamais les chiffres negatifs
			 		 val_absolu = op1 + op2;
           signe = 0;
			 		 // vu que les operands peuvent pas etre plus que 31 chacun,
			 		 // ce n'est pas possible de depasser 999 pour le resultat
			 		 reste = 0;

			 		 break;

			 	 case SUB :
			 		 val_temp = op1 - op2;
           if (val_temp < 0 ) {
             signe = 1;
           }
           else {
             signe = 0;
           }
           val_absolu = abs(val_temp);
           // pas possible de depasser la limite permissible par les 2 operands
           reste = 0;
			 		 break;

			 	 case DIV :
			 		 val_absolu = op1/op2;
           reste = op1 % op2; // modulu operator
           //printf("val_temp = %d\nreste = %d\n", val_absolu,reste);
           signe = 0;
			 		 break;

			 	 case MULT :
			 	 	 val_temp = op1*op2;
           if (val_temp < 0 ) {
             signe = 1;
           }
           else {
             signe = 0;
           }
           val_absolu = abs(val_temp);
           // pas possible de depasser la limite permissible par les 2 operands
           reste = 0;
			 	 	 break;

			 	 default :
			 		 val_absolu = 0;
			 		 signe = 0;
			 		 reste = 0;
			 }

       // conversion dec a BCD (on commence avec le MSB)
       resultat_bcd[2] = val_absolu/100;
       resultat_bcd[1] = (val_absolu - resultat_bcd[2]*100)/10;
       resultat_bcd[0] = (val_absolu - (resultat_bcd[2]*100 + resultat_bcd[1]*10))/1;
       /*
        exemple donne avec 512:
        val_absolu = 512
        bcd[2] = 512/100 = 5
        bcd[1] = (512-5*100)/10 = 12/10 = 1
        bcd[0] = (512 - (5*100 + 1*10))/1 = 2
       */

       // conversion BCD a LED seg et construction du buffer
       // shift par 8 bits chaque fois pour cibler chaque chiffre de l'afficheur hex
       for (i=0; i < 3; i++) {
         // resultat_bcd[i] correspond bien a une position du SEG_TABLE et cette
         // position est la valeur BCD!
         resultat_LEDseg[i] = SEG_TABLE[(resultat_bcd[i])];
         LEDseg_buffer |= (resultat_LEDseg[i] << 8*i);
       }

       // si l'operation mathematique en haut a donne un signe negatif (signe == 1)
       // alors nous mettons le chiffre approprie des afficheurs hex a un signe moins
       if (signe == 1) {
         LEDseg_buffer |= (SEG_TABLE[11] << 3*8);
       }

       // sinon le chiffre va etre etteint
       else {
         LEDseg_buffer |= (SEG_TABLE[10] << 3*8);
       }

       // LEDseg_buffer est le resultat final (LED seg encoded)
       HEX_bits = LEDseg_buffer;

       // nous pouvons directemment charger le banc de LEDs avec le resultat
       LED_bits = reste;

			 // display pattern on HEX3 ... HEX0
			 IOWR_ALTERA_AVALON_PIO_DATA(HEX3_HEX0_BASE, HEX_bits);
			 // display pattern on LEDs
			 IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, LED_bits);

		 }

	#endif
}







