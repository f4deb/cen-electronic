#ifndef LCD_HD44780_H
#define LCD_HD44780_H

#include <stdbool.h>

/*******************
 * Definition des ports utilisés pour utiliser l'afficheur LCD
 ********************/


#ifdef PROG_32




#define CLCK_MATRIX  PORTFbits.RF3
#define DATA_MATRIX  PORTFbits.RF1
#define STRO_MATRIX  PORTFbits.RF0

#define A0_MATRIX  PORTEbits.RE0
#define A1_MATRIX  PORTEbits.RE1
#define A2_MATRIX  PORTEbits.RE2
#define E1_MATRIX  PORTEbits.RE3
//#define C4_MATRIX  PORTEbits.RE4

#define TRIS_DATA_MATRIX TRISFbits.TRISF1
#define TRIS_CLCK_MATRIX TRISFbits.TRISF3
#define TRIS_STRO_MATRIX  TRISFbits.TRISF0

#define TRIS_A0_MATRIX TRISEbits.TRISE0
#define TRIS_A1_MATRIX TRISEbits.TRISE1
#define TRIS_A2_MATRIX TRISEbits.TRISE2
#define TRIS_E1_MATRIX TRISEbits.TRISE3
//#define TRIS_C4_MATRIX TRISEbits.TRISE4

#endif

/**
 * Initialise l'afficheur LCD
 * 
 */
void hd44780_initLcd(void);

/**
 * Envoie une commande à l'afficheur sur 8bits
 */
void hd44780_sendComLcd(unsigned char value);


/**
 * Envoie une commande à l'afficheur lors de l'initialisation sur 4bits
 */
void hd44780_sendIniComLcd(unsigned char D7, unsigned char D6, unsigned char D5, unsigned char D4);

/**
 * Envoie une data à l'afficheur
 */
void hd44780_sendDataLcd(unsigned char DataLcd);

/**
 * Show a string
 * @param text to send
 */
void hd44780_writeString(const char *text);

/**
 * Affiche une chaine de texte
 * @param texte à transmettre
 * @param colonne
 * @param ligne
 */
void hd44780_affTexteLcdXY(const char *text, unsigned char colonneLcd, unsigned char ligneLcd);

/**
 * Set the cursor at the specified row and column.
 * @param row row index between 1 and 4 = N° de la ligne de 1 à 4
 * @param column column index de 1 à 20
 */
void hd44780_setCursorRowAndColumn(unsigned char row, unsigned char column);

/**
 * Hide the cursor.
 */
void hd44780_hideCursor(void);

/**
 * Set an underline to see the cursor.
 */
void hd44780_showUnderlineCursor(void);

/**
 * Set or not the backlight.
 */
void hd44780_setBacklight(bool enabled);

/**
 * Use blink cursor.
 */
void hd44780_setBlinkCursor(void);

/**
 * Set the cursor at the top and left of the screen.
 */
void hd44780_setCursorAtHome(void);

/**
 * Efface l'écran
 */
void hd44780_clearScreen(void);

/**
 * Affiche un caractere à la position actuel du curseur et décal de 1 le curseur
 * @param Caractère à afficher
 */
void hd44780_writeChar(unsigned char carac);

#endif
