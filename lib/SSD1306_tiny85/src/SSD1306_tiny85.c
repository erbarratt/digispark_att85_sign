#include "SSD1306_tiny85.h"

const unsigned char digital_font5x7[] PROGMEM =
{
	0x00, 0x05, 0x07, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x00, // char ' ' (0x20/32)
	0x00, 0x00, 0x2E, 0x00, 0x00, // char '!' (0x21/33)
	0x06, 0x00, 0x06, 0x00, 0x00, // char '"' (0x22/34)
	0x14, 0x7F, 0x14, 0x7F, 0x14, // char '#' (0x23/35)
	0x06, 0x49, 0x7F, 0x49, 0x30, // char '$' (0x24/36)
	0x24, 0x10, 0x08, 0x24, 0x00, // char '%' (0x25/37)
	0x36, 0x49, 0x36, 0x50, 0x00, // char '&' (0x26/38)
	0x00, 0x00, 0x00, 0x06, 0x00, // char ''' (0x27/39)
	0x00, 0x41, 0x36, 0x00, 0x00, // char '(' (0x28/40)
	0x00, 0x36, 0x41, 0x00, 0x00, // char ')' (0x29/41)
	0x00, 0x08, 0x00, 0x00, 0x00, // char '*' (0x2A/42)
	0x00, 0x08, 0x1C, 0x08, 0x00, // char '+' (0x2B/43)
	0x40, 0x20, 0x00, 0x00, 0x00, // char ',' (0x2C/44)
	0x00, 0x08, 0x08, 0x00, 0x00, // char '-' (0x2D/45)
	0x20, 0x00, 0x00, 0x00, 0x00, // char '.' (0x2E/46)
	0x00, 0x30, 0x06, 0x00, 0x00, // char '/' (0x2F/47)
	0x36, 0x41, 0x41, 0x36, 0x00, // char '0' (0x30/48)
	0x00, 0x00, 0x00, 0x36, 0x00, // char '1' (0x31/49)
	0x30, 0x49, 0x49, 0x06, 0x00, // char '2' (0x32/50)
	0x00, 0x49, 0x49, 0x36, 0x00, // char '3' (0x33/51)
	0x06, 0x08, 0x08, 0x36, 0x00, // char '4' (0x34/52)
	0x06, 0x49, 0x49, 0x30, 0x00, // char '5' (0x35/53)
	0x36, 0x49, 0x49, 0x30, 0x00, // char '6' (0x36/54)
	0x00, 0x01, 0x01, 0x36, 0x00, // char '7' (0x37/55)
	0x36, 0x49, 0x49, 0x36, 0x00, // char '8' (0x38/56)
	0x06, 0x49, 0x49, 0x36, 0x00, // char '9' (0x39/57)
	0x00, 0x14, 0x00, 0x00, 0x00, // char ':' (0x3A/58)
	0x20, 0x14, 0x00, 0x00, 0x00, // char ';' (0x3B/59)
	0x00, 0x08, 0x14, 0x22, 0x00, // char '<' (0x3C/60)
	0x00, 0x14, 0x14, 0x14, 0x00, // char '=' (0x3D/61)
	0x00, 0x22, 0x14, 0x08, 0x00, // char '>' (0x3E/62)
	0x00, 0x01, 0x31, 0x06, 0x00, // char '?' (0x3F/63)
	0x36, 0x49, 0x55, 0x59, 0x2E, // char '@' (0x40/64)
	0x36, 0x09, 0x09, 0x36, 0x00, // char 'A' (0x41/65)
	0x77, 0x49, 0x49, 0x36, 0x00, // char 'B' (0x42/66)
	0x36, 0x41, 0x41, 0x00, 0x00, // char 'C' (0x43/67)
	0x77, 0x41, 0x41, 0x36, 0x00, // char 'D' (0x44/68)
	0x36, 0x49, 0x49, 0x00, 0x00, // char 'E' (0x45/69)
	0x36, 0x09, 0x09, 0x00, 0x00, // char 'F' (0x46/70)
	0x36, 0x41, 0x51, 0x30, 0x00, // char 'G' (0x47/71)
	0x36, 0x08, 0x08, 0x36, 0x00, // char 'H' (0x48/72)
	0x00, 0x00, 0x36, 0x00, 0x00, // char 'I' (0x49/73)
	0x00, 0x40, 0x40, 0x36, 0x00, // char 'J' (0x4A/74)
	0x36, 0x08, 0x14, 0x22, 0x00, // char 'K' (0x4B/75)
	0x36, 0x40, 0x40, 0x00, 0x00, // char 'L' (0x4C/76)
	0x36, 0x01, 0x06, 0x01, 0x36, // char 'M' (0x4D/77)
	0x36, 0x04, 0x10, 0x36, 0x00, // char 'N' (0x4E/78)
	0x36, 0x41, 0x41, 0x36, 0x00, // char 'O' (0x4F/79)
	0x36, 0x09, 0x09, 0x06, 0x00, // char 'P' (0x50/80)
	0x36, 0x41, 0x21, 0x56, 0x00, // char 'Q' (0x51/81)
	0x36, 0x09, 0x19, 0x26, 0x00, // char 'R' (0x52/82)
	0x06, 0x49, 0x49, 0x30, 0x00, // char 'S' (0x53/83)
	0x00, 0x01, 0x37, 0x01, 0x00, // char 'T' (0x54/84)
	0x36, 0x40, 0x40, 0x36, 0x00, // char 'U' (0x55/85)
	0x36, 0x40, 0x36, 0x00, 0x00, // char 'V' (0x56/86)
	0x36, 0x40, 0x30, 0x40, 0x36, // char 'W' (0x57/87)
	0x36, 0x08, 0x08, 0x36, 0x00, // char 'X' (0x58/88)
	0x06, 0x48, 0x48, 0x36, 0x00, // char 'Y' (0x59/89)
	0x20, 0x51, 0x49, 0x45, 0x02, // char 'Z' (0x5A/90)
	0x77, 0x41, 0x41, 0x00, 0x00, // char '[' (0x5B/91)
	0x00, 0x06, 0x30, 0x00, 0x00, // char '\' (0x5C/92)
	0x00, 0x41, 0x41, 0x77, 0x00, // char ']' (0x5D/93)
	0x00, 0x02, 0x01, 0x02, 0x00, // char '^' (0x5E/94)
	0x00, 0x40, 0x40, 0x00, 0x00, // char '_' (0x5F/95)
	0x00, 0x01, 0x02, 0x00, 0x00, // char '`' (0x60/96)
	0x20, 0x54, 0x54, 0x38, 0x40, // char 'a' (0x61/97)
	0x00, 0x36, 0x48, 0x30, 0x00, // char 'b' (0x62/98)
	0x30, 0x48, 0x48, 0x00, 0x00, // char 'c' (0x63/99)
	0x30, 0x48, 0x48, 0x76, 0x00, // char 'd' (0x64/100)
	0x38, 0x54, 0x54, 0x08, 0x00, // char 'e' (0x65/101)
	0x08, 0x6C, 0x0A, 0x00, 0x00, // char 'f' (0x66/102)
	0x08, 0x54, 0x54, 0x38, 0x00, // char 'g' (0x67/103)
	0x36, 0x08, 0x08, 0x30, 0x00, // char 'h' (0x68/104)
	0x00, 0x34, 0x00, 0x00, 0x00, // char 'i' (0x69/105)
	0x00, 0x40, 0x34, 0x00, 0x00, // char 'j' (0x6A/106)
	0x36, 0x10, 0x28, 0x00, 0x00, // char 'k' (0x6B/107)
	0x36, 0x00, 0x00, 0x00, 0x00, // char 'l' (0x6C/108)
	0x30, 0x08, 0x10, 0x08, 0x30, // char 'm' (0x6D/109)
	0x30, 0x08, 0x08, 0x30, 0x00, // char 'n' (0x6E/110)
	0x30, 0x48, 0x48, 0x30, 0x00, // char 'o' (0x6F/111)
	0x78, 0x14, 0x14, 0x08, 0x00, // char 'p' (0x70/112)
	0x08, 0x14, 0x14, 0x68, 0x00, // char 'q' (0x71/113)
	0x30, 0x08, 0x08, 0x00, 0x00, // char 'r' (0x72/114)
	0x08, 0x54, 0x54, 0x20, 0x00, // char 's' (0x73/115)
	0x08, 0x2C, 0x48, 0x00, 0x00, // char 't' (0x74/116)
	0x30, 0x40, 0x40, 0x30, 0x00, // char 'u' (0x75/117)
	0x30, 0x40, 0x30, 0x00, 0x00, // char 'v' (0x76/118)
	0x30, 0x40, 0x20, 0x40, 0x30, // char 'w' (0x77/119)
	0x28, 0x10, 0x10, 0x28, 0x00, // char 'x' (0x78/120)
	0x08, 0x50, 0x50, 0x38, 0x00, // char 'y' (0x79/121)
	0x24, 0x34, 0x2C, 0x24, 0x00, // char 'z' (0x7A/122)
	0x08, 0x36, 0x41, 0x00, 0x00, // char '{' (0x7B/123)
	0x00, 0x36, 0x00, 0x00, 0x00, // char '|' (0x7C/124)
	0x00, 0x41, 0x36, 0x08, 0x00, // char '}' (0x7D/125)
	0x08, 0x08, 0x10, 0x10, 0x00, // char '~' (0x7E/126)
	0x36, 0x41, 0x36, 0x00, 0x00, // char '' (0x7F/127)
};

	unsigned char USI_Buf[USI_BUF_SIZE]; // holds I2C send and receive data
	unsigned char USI_BufIdx = 1;     // current number of bytes in the send buff

	unsigned char OLED_addToUSIBuffer(unsigned char data) { // buffers up data to send
		if (USI_BufIdx >= USI_BUF_SIZE - 1){
			return 0;   // dont blow out the buffer
		}
		USI_Buf[USI_BufIdx] = data;
		USI_BufIdx++; // inc for next byte in buffer
		return 1;
	}

	unsigned char OLED_transmitBuffer(unsigned char stop) { // actually sends the buffer

		bool xferOK = false;
		unsigned char errorCode;
		xferOK = USI_TWI_Start_Transceiver_With_Data( USI_Buf, USI_BufIdx + 1); // core func that does the work
		USI_BufIdx = 1;
		if (xferOK) {
			if (stop) {
				errorCode = USI_TWI_Master_Stop();
				if (errorCode == 0) {
					errorCode = USI_TWI_Get_State_Info();
					return errorCode;
				}
			}
			return 0;
		} else { // there was an error
			errorCode = USI_TWI_Get_State_Info(); // this function returns the error number
			return errorCode;
		}

	}

	unsigned char OLED_sendCommand(unsigned char command)
	{
		USI_TWI_Master_Initialise();         									//initialize I2C
		OLED_addToUSIBuffer(SSD1306_Command_Mode);	     					//Set OLED Command mode
		OLED_addToUSIBuffer(command);										//add the byte of data
		return OLED_transmitBuffer(1);										//transmit buffer
	}

	void OLED_init()
	{

		//write address as always the first byte in the buffer
		USI_Buf[0] = (SlaveAddress << TWI_ADR_BITS) | USI_SEND;

		//USI_TWI_Master_Initialise();         									//initialize I2C

		OLED_sendCommand(SSD1306_Display_Off_Cmd);    					/*display off*/

		OLED_sendCommand(Set_Multiplex_Ratio_Cmd);    					/*multiplex ratio*/
		OLED_sendCommand(0x3F);    									/*duty = 1/64*/

		OLED_sendCommand(Set_Display_Offset_Cmd);    					/*set display offset*/
		OLED_sendCommand(0x00);

		OLED_sendCommand(Set_Memory_Addressing_Mode_Cmd); 				//set addressing mode
		OLED_sendCommand(HORIZONTAL_MODE); 							//set horizontal addressing mode

		OLED_sendCommand(0xB0); 										//set page address
		OLED_sendCommand(0x00); 										//set column lower address
		OLED_sendCommand(0x10); 										//set column higher address

		OLED_sendCommand(0x40);    									/*set display starconstructort line*/

		OLED_sendCommand(Set_Contrast_Cmd);    						/*contract control*/
		OLED_sendCommand(0xcf);    									/*128*/

		OLED_sendCommand(Segment_Remap_Cmd);   						/*set segment remap*/

		OLED_sendCommand(COM_Output_Remap_Scan_Cmd);    				/*Com scan direction*/

		OLED_sendCommand(SSD1306_Normal_Display_Cmd);    				/*normal / reverse*/

		OLED_sendCommand(Set_Display_Clock_Divide_Ratio_Cmd);    		/*set osc division*/
		OLED_sendCommand(0x80);

		OLED_sendCommand(Set_Precharge_Period_Cmd);    				/*set pre-charge period*/
		OLED_sendCommand(0xf1);

		OLED_sendCommand(Set_COM_Pins_Hardware_Config_Cmd);    		/*set COM pins*/
		OLED_sendCommand(0x12);

		OLED_sendCommand(Set_VCOMH_Deselect_Level_Cmd);    			/*set vcomh*/
		OLED_sendCommand(0x30);

		OLED_sendCommand(Deactivate_Scroll_Cmd);

		OLED_sendCommand(Charge_Pump_Setting_Cmd);    					/*set charge pump enable*/
		OLED_sendCommand(Charge_Pump_Enable_Cmd);

		OLED_sendCommand(SSD1306_Display_On_Cmd);    					/*display ON*/
	}

	void OLED_clipArea(unsigned char col, unsigned char row, unsigned char w, unsigned char h){

		USI_TWI_Master_Initialise();         									//initialize I2C

		OLED_addToUSIBuffer(SSD1306_Command_Mode);            				// command mode
		OLED_addToUSIBuffer(Set_Column_Address_Cmd);
		OLED_addToUSIBuffer(0);
		OLED_addToUSIBuffer(col);
		OLED_addToUSIBuffer(col + w - 1);
		OLED_transmitBuffer(1);                    						// stop I2C transmission

		USI_TWI_Master_Initialise();         									//initialize I2C

		OLED_addToUSIBuffer(SSD1306_Command_Mode);            				// command mode
		OLED_addToUSIBuffer(Set_Page_Address_Cmd);
		OLED_addToUSIBuffer(0);
		OLED_addToUSIBuffer(row);
		OLED_addToUSIBuffer(row + h - 1);
		OLED_transmitBuffer(1);                    						// stop I2C transmission

	}

	void OLED_cursorTo(unsigned char col, unsigned char row){
		OLED_clipArea(col, row, 128 - col, 8 - row);
	}

	void OLED_clear() {

		OLED_sendCommand(0x00 | 0x0);  // low col = 0
		OLED_sendCommand(0x10 | 0x0);  // hi col = 0
		OLED_sendCommand(0x40 | 0x0); // line #0

		OLED_clipArea(0, 0, 128, 8);

		for (unsigned char i=0; i<= (unsigned char)((128*64/8)/16); i++){
			OLED_addToUSIBuffer(SSD1306_Data_Mode);            // data mode
			for (unsigned char k=0;k<16;k++){
				OLED_addToUSIBuffer(0);
			}
			OLED_transmitBuffer(1);
		}

	}

	void OLED_printChar( unsigned char ch ){

		//address = hex value of char * 5 - 156
		//get 5 bytes

		OLED_addToUSIBuffer(SSD1306_Data_Mode);            // data mode

		OLED_addToUSIBuffer(0x00);
		OLED_addToUSIBuffer(pgm_read_byte( &(digital_font5x7[(ch*5) - 156]) ));
		OLED_addToUSIBuffer(pgm_read_byte( &(digital_font5x7[(ch*5) - 156 + 1]) ));
		OLED_addToUSIBuffer(pgm_read_byte( &(digital_font5x7[(ch*5) - 156 + 2]) ));
		OLED_addToUSIBuffer(pgm_read_byte( &(digital_font5x7[(ch*5) - 156 + 3]) ));
		OLED_addToUSIBuffer(pgm_read_byte( &(digital_font5x7[(ch*5) - 156 + 4]) ));
		OLED_addToUSIBuffer(0x00);

		OLED_transmitBuffer(1);

	}

	void OLED_printString( char * pText ){
		for (unsigned char i=0; pText[i] != '\0'; i++){
			OLED_printChar(pText[i]);
		}
	}
