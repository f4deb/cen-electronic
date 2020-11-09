#include "../../common/commons.h"

#include <plib.h>

#include <string.h>

#include "lcdHd44780_Matrix.h"
#include "../../common/police/5x7/5x7.h"
#include "../../common/delay/cenDelay.h"

#define LCD_ROW_COUNT                       4
#define LCD_COLUMN_COUNT                   20

static unsigned char currentRow;
static unsigned char currentColumn;

#define LCD_DELAY_COMMAND_MICRO_SECOND     400
#define LCD_DELAY_DATA_MICRO_SECOND        100

/**
 * Verifie et attend si l'afficheur a fini d'effectuer ses op�rations interne.
 */
void busyFlag(void) {

}

void hd44780_sendIniComLcd(unsigned char D7, unsigned char D6, unsigned char D5, unsigned char D4) {
    
}

void hd44780_sendComLcd(unsigned char comLcd) {
    
}

void hd44780_sendDataLcd(unsigned char DataLcd) {
         
   

}

void hd44780_initLcd(void) {
    
    TRIS_DATA_MATRIX = 0;
    TRIS_CLCK_MATRIX = 0;
    TRIS_STRO_MATRIX = 0;
    TRIS_A0_MATRIX = 0;
    TRIS_A1_MATRIX = 0;
    TRIS_A2_MATRIX = 0;
    TRIS_E1_MATRIX = 0;
    
    STRO_MATRIX = 0;
    DATA_MATRIX = 0;
    CLCK_MATRIX = 0;
    
}

void hd44780_writeString(const char *text) {


    int i = 0;  // character index
    int j = 0;  // bit index
    int ligne = 0; // line index
    int ligne1; //variable for the line
    char character; // character to print
    
    char str_19[40] = "";
    strcpy (str_19,text); // transfer  the text into the array

    for (ligne=0;ligne<7;ligne++){
        // print the string
        for (i=19;i>=0;i--){
            int str_1 = ((int)str_19[i])*7 ;

            character = tab_char_5x7 [str_1 + ligne]; // code ASCII
            //print character
            for (j=0;j<5;j++){                        
                DATA_MATRIX = character;
                CLCK_MATRIX = 1;
                CLCK_MATRIX = 0;
                character>>=1;
            }    
            if  (i>0) {     
            DATA_MATRIX = 0;       // clear one column     
            CLCK_MATRIX = 1;
            CLCK_MATRIX = 0;    
            }
        }  
        STRO_MATRIX = 1;  
        STRO_MATRIX = 0;    

        //select  the ligne to print
        ligne1 = ligne;            
        A0_MATRIX = ligne1;
        A1_MATRIX = ligne1>>=1;
        A2_MATRIX = ligne1>>=1;
        E1_MATRIX = 0;
        delayMilliSecs(1);
    }       
    E1_MATRIX = 1; // clear the last line while there is nothing to print  
}

void hd44780_affTexteLcdXY(const char* text, unsigned char column, unsigned char row) {
 
}

void incLcdRow() {
    currentRow++;
    if (currentRow >= LCD_ROW_COUNT) {
        currentRow = 0;
    }
}

void incLcdColumn() {
    currentColumn++;
    if (currentColumn >= LCD_COLUMN_COUNT) {
        incLcdRow();
        currentColumn = 0;
    }
}

void hd44780_setCursorRowAndColumn(unsigned char row, unsigned char column) {
}

void hd44780_hideCursor(void) {
}

void hd44780_showUnderlineCursor(void) {
}

void hd44780_setBacklight(bool enabled) {
    
}

void hd44780_setBlinkCursor(void) {
}

void initCursorPosition() {
}

void hd44780_setCursorAtHome(void) {
}

void hd44780_clearScreen(void) {
}

void hd44780_writeChar(unsigned char c) {
  }
