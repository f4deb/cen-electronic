#include "../../common/commons.h"

#include <plib.h>

#include <string.h>

#include "lcdHd44780_Matrix.h"
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
    

        
    TRIS_DATA_MATRIX = 0;
    TRIS_CLCK_MATRIX = 0;
    TRIS_STRO_MATRIX = 0;
    TRIS_A0_MATRIX = 0;
    TRIS_A1_MATRIX = 0;
    TRIS_A2_MATRIX = 0;
    TRIS_E1_MATRIX = 0;

    int ligne = 0;
    while (1){
        for (ligne=0;ligne<7;ligne++){
            STRO_MATRIX = 0;
            DATA_MATRIX = 0;
            CLCK_MATRIX = 0;

            char character[6]; 

            character[0] =0b11111;
            character[1] =0b11110;
            character[2] =0b11101;
            character[3] =0b11011;
            character[4] =0b10111;
            character[5] =0b01111;

            int i = 0;
            int j = 0;
                for (i=0;i<6;i++){
                    for (j=0;j<5;j++){
                        DATA_MATRIX = character[i];
                        //delayMicroSecs(100);
                        CLCK_MATRIX = 0;
                        //delayMicroSecs(100);
                        CLCK_MATRIX = 1;
                        //delayMicroSecs(100);
                        CLCK_MATRIX = 0;
                        //delayMicroSecs(100);
                        character[i]>>=1;
                    }    
                 }  
                    STRO_MATRIX = 0;    
                    //delayMicroSecs(100);
                    STRO_MATRIX = 1;    
                    //delayMicroSecs(100);    
                    STRO_MATRIX = 0;    
                    //delayMicroSecs(100);    

                    int ligne1;
            ligne1 = ligne;            
            A0_MATRIX = ligne1;
            A1_MATRIX = ligne1>>=1;
            A2_MATRIX = ligne1>>=1;
            E1_MATRIX = 0;
            delayMicroSecs(1000);
        }    
    }

}

void hd44780_initLcd(void) {
    
}

void hd44780_writeString(const char* text) {
    unsigned char i;
    unsigned char a;

    a = strlen(text);

    for (i = 1; i <= a; i++) {
        hd44780_sendDataLcd(*text);
        text++;
    }
}

void hd44780_affTexteLcdXY(const char* text, unsigned char column, unsigned char row) {
    unsigned char i;
    unsigned char a;

    hd44780_setCursorRowAndColumn(column, row);

    a = strlen(text);

    for (i = 1; i <= a; i++) {
        hd44780_sendDataLcd(*text);
        text++;
    }
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
    currentRow = row;
    currentColumn = column;

    unsigned char cursor;
    if (row == 0) {
        cursor = 0x80;
    }
    if (row == 1) {
        cursor = 0xC0;
    }
    if (row == 2) {
        cursor = 0x94;
    }
    if (row == 3) {
        cursor = 0xD4;
    }
    cursor = cursor + column;
    hd44780_sendComLcd(cursor);

}

void hd44780_hideCursor(void) {
    hd44780_sendComLcd(0b00001100);
}

void hd44780_showUnderlineCursor(void) {
    hd44780_sendComLcd(0b00001110);
}

void hd44780_setBacklight(bool enabled) {
    
}

void hd44780_setBlinkCursor(void) {
    hd44780_sendComLcd(0b00001111);
}

void initCursorPosition() {
    currentColumn = 0;
    currentRow = 0;
}

void hd44780_setCursorAtHome(void) {
    initCursorPosition();
    hd44780_sendComLcd(0b00000010);
}

void hd44780_clearScreen(void) {
    initCursorPosition();
    hd44780_sendComLcd(0b00000001);
}

void hd44780_writeChar(unsigned char c) {
    hd44780_setCursorRowAndColumn(currentRow, currentColumn);

    // does not handle CR
    if (c == CARRIAGE_RETURN) {
        return;
    }
    if (c == LF) {
        while (currentColumn != 0) {
            // Fill with spaces
            hd44780_sendDataLcd(' ');
            incLcdColumn();
        }
        hd44780_setCursorRowAndColumn(currentRow, currentColumn);
    } else if (c == CLS) {
        hd44780_setCursorAtHome();
        hd44780_clearScreen();
    } else {
        hd44780_sendDataLcd(c);
        incLcdColumn();
    }
}
