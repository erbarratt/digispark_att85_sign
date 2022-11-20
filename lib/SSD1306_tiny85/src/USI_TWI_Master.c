/*****************************************************************************
*
* AppNote           : AVR310 - Using the USI (Universal Serial Interface) module as a TWI (I2C or Two wire serial Interface) Master
*
*		Extensively modified to provide complete I2C driver.
*
*Notes:
*		- T4_TWI and T2_TWI delays are modified to work with 1MHz default clock and now use hard code values. They would need to change for other clock rates.
*		Refer to the Apps Note.
*
*	12/17/08	Added USI_TWI_Start_Memory_Read Routine		-jkl
*		Note msg buffer will have slave adrs ( with write bit set) and memory adrs;
*			length should be these two bytes plus the number of
bytes to read.
****************************************************************************/
#include "USI_TWI_Master.h"

/**
 * @brief Stores the state of the USI_TWI
 */
union USI_TWI_state
{
	unsigned char errorState; //!< Can reuse the TWI_state for error states since
	//!< it will not be needed if there is an error.
	/**
	* @brief Struct that stores the modes for the device
	*/
	struct
	{
		unsigned char addressMode: 1;         //!< Address mode
		unsigned char masterWriteDataMode: 1; //!< Write data mode
		unsigned char memReadMode: 1;         //!< Read memory mode
		unsigned char unused: 5;              //!< Unused
	};

} USI_TWI_state; //!< USI_TWI_state The state of the USI_TWI

/**
 * @brief USI TWI single master initialization function
 */
void USI_TWI_Master_Initialise()
{

	//set pin B0 and B2 to 1 (high)
	PORT_USI |= (1 << PIN_USI_SDA);                        		// Enable pullup on SDA, to set high as released state.
	PORT_USI |= (1 << PIN_USI_SCL);                        		// Enable pullup on SCL, to set high as released state.

	//set the data direction register for port B as outputs for pin B0 and B2
	DDR_USI |= (1 << PIN_USI_SCL);                            	// Enable SCL as output.
	DDR_USI |= (1 << PIN_USI_SDA);                            	// Enable SDA as output.

	//set USI Data Register with 255
	USIDR = 0xFF;                                            	// Preload dataregister with "released level" data.

	//set USI Control Register
	USICR = (0 << USISIE) | (0 << USIOIE) |                		// Disable Interrupts.
		(1 << USIWM1) | (0 << USIWM0) |                    		// Set USI in Two-wire mode.
		(1 << USICS1) | (0 << USICS0) |
		(1 << USICLK) |                                    		// Software stobe as counter clock source
		(0 << USITC);

	//set USI status register
	USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
		(1 << USIDC) |                                    		// Clear flags,
		(0x0 << USICNT0);                                		// and reset counter (4 bits)

}

/**
 * @brief Use this function to get hold of the error message from the last
 * transmission
 * @return Returns error state
 */
	unsigned char USI_TWI_Get_State_Info()
	{
		return (USI_TWI_state.errorState); // Return error state.
	}
	
/**
 * @brief Function for generating a TWI Start Condition.
 * @return Returns true if the signal can be verified, otherwise returns false
 */
	unsigned char USI_TWI_Master_Start(void)
	{
		/* Release SCL to ensure that (repeated) Start can be performed */
		PORT_USI |= (1 << PIN_USI_SCL); // Release SCL.
		while(!(PORT_USI & (1 << PIN_USI_SCL))){} // Verify that SCL becomes high.
		_delay_us(T2_TWI);

		/* Generate Start Condition */
		PORT_USI &= ~(1 << PIN_USI_SDA); // Force SDA LOW.
		_delay_us(T4_TWI);
		PORT_USI &= ~(1 << PIN_USI_SCL); // Pull SCL LOW.
		PORT_USI |= (1 << PIN_USI_SDA);  // Release SDA.

		if(!(USISR & (1 << USISIF))){
			USI_TWI_state.errorState = USI_TWI_MISSING_START_CON;
			return (FALSE);
		}

		return (TRUE);
	}

/**
 * @brief Function for generating a TWI Stop Condition. Used to release
 * the TWI bus.
 * @return Returns true if it was successful
 */
	unsigned char USI_TWI_Master_Stop(void)
	{
		PORT_USI &= ~(1 << PIN_USI_SDA); // Pull SDA low.
		PORT_USI |= (1 << PIN_USI_SCL);  // Release SCL.
		while(!(PIN_USI & (1 << PIN_USI_SCL))){} // Wait for SCL to go high.
		_delay_us(T4_TWI);
		PORT_USI |= (1 << PIN_USI_SDA); // Release SDA.
		_delay_us(T2_TWI);

		#ifdef SIGNAL_VERIFY
			if(!(USISR & (1 << USIPF))){
				USI_TWI_state.errorState = USI_TWI_MISSING_STOP_CON;
				return (FALSE);
			}
		#endif

		return (TRUE);
	}

/**
 * @brief Core function for shifting data in and out from the USI.
 * Data to be sent has to be placed into the USIDR prior to calling
 * this function. Data read, will be return'ed from the function.
 * @param temp Temporary status to set the USISR
 * @return Returns the read read from the device
 */
	unsigned char USI_TWI_Master_Transfer(unsigned char temp)
	{

		USISR = temp;                          				// Set USISR according to temp.

		// Prepare clocking.
		temp = (0 << USISIE) | (0 << USIOIE) | 				// Interrupts disabled
			(1 << USIWM1) | (0 << USIWM0) | 				// Set USI in Two-wire mode.
			(1 << USICS1) | (0 << USICS0) |
			(1 << USICLK) | 								// Software clock strobe as source.
			(1 << USITC);   								// Toggle Clock Port.

		do{
			_delay_us(T2_TWI);
			USICR = temp; 									// Generate positve SCL edge.
			while(!(PIN_USI & (1 << PIN_USI_SCL))){} 		// Wait for SCL to go high.
			_delay_us(T4_TWI);
			USICR = temp;                     				// Generate negative SCL edge.
		} while(!(USISR & (1 << USIOIF))); 					// Check for transfer complete.

		_delay_us(T2_TWI);
		temp = USIDR;                  						// Read out data.
		USIDR = 0xFF;                  						// Release SDA.
		DDR_USI |= (1 << PIN_USI_SDA); 						// Enable SDA as output.

		return temp; // Return the data from the USIDR
	}

/**
 * @brief USI Transmit and receive function. LSB of first byte in buffer
 * indicates if a read or write cycles is performed. If set a read
 * operation is performed.
 *
 * Function generates (Repeated) Start Condition, sends address and
 * R/W, Reads/Writes Data, and verifies/sends ACK.
 *
 * This function also handles Random Read function if the memReadMode
 * bit is set. In that case, the function will:
 * The address in memory will be the second
 * byte and is written *without* sending a STOP.
 * Then the Read bit is set (lsb of first byte), the byte count is
 * adjusted (if needed), and the function function starts over by sending
 * the slave address again and reading the data.
 *
 * Success or error code is returned. Error codes are defined in
 * USI_TWI_Master.h
 * @param msg Pointer to the location of the msg buffer
 * @param msgSize How much data to send from the buffer
 */
	unsigned char USI_TWI_Start_Transceiver_With_Data(unsigned char *msg, unsigned char msgSize)
	{

		// try to Send a START condition on the TWI bus.
			if(!USI_TWI_Master_Start()){
				return (FALSE);
			}

		//temporary USI status reg 8 bit
		//11110000
		unsigned char const tempUSISR_8bit =
			(1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
				(1 << USIDC) |    // Prepare register value to: Clear flags, and
				(0x0 << USICNT0); // set USI to shift 8 bits i.e. count 16 clock edges.

		//11111110
		unsigned char const tempUSISR_1bit =
			(1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
				(1 << USIDC) |    // Prepare register value to: Clear flags, and
				(0xE << USICNT0); // set USI to shift 1 bit i.e. count 2 clock edges.

		//save iniitial values for use later
		unsigned char *savedMsg = msg;
		unsigned char savedMsgSize = msgSize;

		// This OLED_clear must be done before calling this function so that memReadMode
		// can be specified.
		//  USI_TWI_state.errorState = 0;				// Clears all
		//  mode bits also

		//#ifdef PARAM_VERIFICATION
		//  if (msg > (unsigned char *)RAMEND) // Test if address is outside SRAM space
		//  {
		//    USI_TWI_state.errorState = USI_TWI_DATA_OUT_OF_BOUND;
		//    return (FALSE);
		//  }
		//  if (msgSize <= 1) // Test if the transmission buffer is empty
		//  {
		//    USI_TWI_state.errorState = USI_TWI_NO_DATA;
		//    return (FALSE);
		//  }
		//#endif

		//#ifdef NOISE_TESTING // Test if any unexpected conditions have arrived prior to
		//    // this execution.
		//  if (USISR & (1 << USISIF)) {
		//    USI_TWI_state.errorState = USI_TWI_UE_START_CON;
		//    return (FALSE);
		//  }
		//  if (USISR & (1 << USIPF)) {
		//    USI_TWI_state.errorState = USI_TWI_UE_STOP_CON;
		//    return (FALSE);
		//  }
		//  if (USISR & (1 << USIDC)) {
		//    USI_TWI_state.errorState = USI_TWI_UE_DATA_COL;
		//    return (FALSE);
		//  }
		//#endif

		// The LSB in the address byte determines if is a masterRead or masterWrite operation.
		// *msg - dereference the pointer, i.e. look at the actual data - 8 bits
		// take these 8 bits and butwise & them with 1 bit shifted left by the amount in TWI_READ_BIT, in this case 0
		// this makes the bit mask 00000001
		// therefor, the seven most signficant bits are 0, which when bitwise & will always give 0 (In &, 1 AND 1 = 1)
		//
		//	ie  xxxxxxxx &
		//	    00000001
		//
		//	In this case, if when bitwised & the result is 0 (the !), then set to master write data mode
		//  a 1 ould be master read mod

			if((*msg & (1 << TWI_READ_BIT)) == 0){
				USI_TWI_state.masterWriteDataMode = TRUE;
			}

		//	if (USI_TWI_state.memReadMode)
		//	{
		//savedMsg = msg;
		//savedMsgSize = msgSize;
		//	}

		USI_TWI_state.addressMode = TRUE; // Always true for first byte

		/*Write address and Read/Write data */
		while(msgSize > 0) // Until all data sent/received.
		{

			/* If masterWrite cycle (or initial address tranmission)*/
			if(USI_TWI_state.addressMode || USI_TWI_state.masterWriteDataMode){

				/* Write a byte */
					//  1 << 2 = 00000100
					//get inverse = 11111011
					//bitwise and, ensuring bit as position 2 is always 0, as X & 0 is always 0
					//bitmask keeps all other values as they were
					PORT_USI &= ~(1 << PIN_USI_SCL);         				// Pull SCL LOW.
					USIDR = *(msg++);                        				// Setup data. Deref msg and put that byte on data reg, then increment the pointer -
																			// -i.e. move one byte in memory
					USI_TWI_Master_Transfer(tempUSISR_8bit); 			// Send 8 bits on USIDR on the bus.

				/* Clock and verify (N)ACK from slave */
					DDR_USI &= ~(1 << PIN_USI_SDA); 						// Enable SDA as input.
					if(USI_TWI_Master_Transfer(tempUSISR_1bit) & (1 << TWI_NACK_BIT)){
						if(USI_TWI_state.addressMode){
							USI_TWI_state.errorState = USI_TWI_NO_ACK_ON_ADDRESS;
						} else{
							USI_TWI_state.errorState = USI_TWI_NO_ACK_ON_DATA;
						}
						return (FALSE);
					}

				// means memory start address has been written
				if(USI_TWI_state.addressMode == FALSE && USI_TWI_state.memReadMode){

					msg = savedMsg;                   						// start at slave address again
					*(msg) |= (1 << TWI_READ_BIT); 							// set the Read Bit on Slave address
					USI_TWI_state.errorState = 0;
					USI_TWI_state.addressMode = TRUE; 						// Now set up for the Read cycle
					msgSize = savedMsgSize;           						// Set byte count correctly

					// NOte that the length should be Slave adrs byte + # bytes to read + 1
					// (gets decremented below)
					if(!USI_TWI_Master_Start()){
						USI_TWI_state.errorState = USI_TWI_BAD_MEM_READ;
						return (FALSE); // Send a START condition on the TWI bus.
					}

				} else {
					USI_TWI_state.addressMode = FALSE; // Only perform address transmission once.
				}

			}

				/* Else masterRead cycle*/
			else{

				/* Read a data byte */
				DDR_USI &= ~(1 << PIN_USI_SDA); // Enable SDA as input.
				*(msg++) = USI_TWI_Master_Transfer(tempUSISR_8bit);

				/* Prepare to generate ACK (or NACK in case of End Of Transmission) */
				// If transmission of last byte was performed.
				if(msgSize == 1){
					USIDR = 0xFF; // Load NACK to confirm End Of Transmission.
				} else{
					USIDR = 0x00; // Load ACK. Set data register bit 7 (output for SDA) low.
				}
				USI_TWI_Master_Transfer(tempUSISR_1bit); // Generate ACK/NACK.

			}

			msgSize--;

		}

		// usually a stop condition is sent here, but TinyWireM needs to choose
		// whether or not to send it

		/* Transmission successfully completed*/

		USI_TWI_Master_Stop();
		return (TRUE);

	}

/**
 * @brief USI Random (memory) Read function. This function sets up for call
 * to USI_TWI_Start_Transceiver_With_Data which does the work.
 * Doesn't matter if read/write bit is set or cleared, it'll be set
 * correctly in this function.
 *
 * The msgSize is passed to USI_TWI_Start_Transceiver_With_Data.
 *
 * Success or error code is returned. Error codes are defined in
 * USI_TWI_Master.h
 * @param msg Pointer to the buffer that contains the messages to be read
 * @param msgSize How much to read from the buffer
 * @return Returns the message read
 */
//unsigned char USI_TWI_Start_Random_Read(unsigned char *msg, unsigned char msgSize)
//{
//	*(msg) &= ~(TRUE << TWI_READ_BIT); // OLED_clear the read bit if it's set
//	USI_TWI_state.errorState = 0;
//	USI_TWI_state.memReadMode = TRUE;
//	return (USI_TWI_Start_Transceiver_With_Data(msg, msgSize));
//}

/**
 * @brief USI Normal Read / Write Function
 * Transmit and receive function. LSB of first byte in buffer
 * indicates if a read or write cycles is performed. If set a read
 * operation is performed.
 *
 * Function generates (Repeated) Start Condition, sends address and
 * R/W, Reads/Writes Data, and verifies/sends ACK.
 *
 * Success or error code is returned. Error codes are defined in
 * USI_TWI_Master.h
 * @param msg Pointer to the buffer that has the messages
 * @param msgSize The size of the message
 * @return Returns the data read
 */
	//unsigned char USI_TWI_Start_Read_Write(unsigned char *msg, unsigned char msgSize)
	//{
	//	USI_TWI_state.errorState = 0; // Clears all mode bits also
	//	return (USI_TWI_Start_Transceiver_With_Data(msg, msgSize));
	//}
