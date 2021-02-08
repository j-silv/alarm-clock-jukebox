#include "main.h"

int main(void) {

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

  printf("Hello from Nios II!\n");
  //return 0;

  while(1) {

    // clear buffer chaque fois dans la boucle
    LEDseg_buffer = 0x0;

    // read the SW slider switch values
    SW_value = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);

    // separer le resultat dans 2 operands
    op1 = (SW_value & op1_mask);
    op2 = (SW_value >> 5);

    // on veut PAS effacer la valeur ou utiliser l'edge cap, car si on le fait, peu importe
    // le temps qu'on appuie sur un des bouton poussoirs, il va tout de suite
    // penser que les 2 boutons sont a 0 (clear edge_cap mets automatiquement
    // les bits a 0, et vu que si on lache pas le bouton il y aura pas de nouveau donnes
    // sur le bouton edge reg, on sera bloque a ADD!
    // on veut plutot juste lire les donnes sur le bouton!
    press = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);

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
    IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, HEX_bits);
    // display pattern on LEDs
    IOWR_ALTERA_AVALON_PIO_DATA(LEDR_BASE, LED_bits);

  }  
}








