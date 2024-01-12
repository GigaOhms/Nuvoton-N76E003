#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "I2Ceeprom.h"


void I2C_Init(void)
{
	I2CLK = I2C_CLOCK;
	/* P1.3 */
	/* Quasi */
	P1M1 &= ~(1 << 3);
	P1M2 &= ~(1 << 3);
	/* P1.4 */
	/* Quasi */
	P1M1 &= ~(1 << 4);
	P1M2 &= ~(1 << 4);
	
	P13=1;
	P14=1;
	
	I2CEN=1;
}

bit I2C_Write_Address(uint8_t addWrite)
{
	uint16_t xdata t;
	uint8_t xdata u8TimeOut;
	
	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = EEPROM_SLA;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x18) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	/* send data */
	// for (i = 0; i < length; ++i) {
		I2DAT = addWrite;
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x28) {
			/* send data error */
			send_stop();
			return 0;
		}
	// }
	
	/* stop */
	return send_stop();
}

bit I2C_Write(uint8_t addWrite, uint8_t pData)
{
	// uint8_t i;
	uint16_t xdata t;
	uint8_t xdata u8TimeOut;
	
	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = EEPROM_SLA;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x18) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	/* send data */
	// for (i = 0; i < length; ++i) {
		I2DAT = addWrite;
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x28) {
			/* send data error */
			send_stop();
			return 0;
		}
	// }

		I2DAT = pData;
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x28) {
			/* send data error */
			send_stop();
			return 0;
		}
	
	/* stop */
	return send_stop();
}

bit I2C_WriteInt(uint8_t addWrite, uint16_t pData)
{
	uint8_t xdata i;
	uint8_t xdata u8TimeOut;
	uint16_t xdata t;
	
	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = EEPROM_SLA;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x18) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	/* send data */
	// for (i = 0; i < length; ++i) {
		I2DAT = addWrite;
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x28) {
			/* send data error */
			send_stop();
			return 0;
		}
	// }

	for (i = 0; i < 2; ++i) {
        if (i == 0) I2DAT = HIBYTE(pData);
        else I2DAT = LOBYTE(pData);
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x28) {
			/* send data error */
			send_stop();
			return 0;
		}
	}
	
	/* stop */
	return send_stop();
}

bit I2C_Read(uint8_t addRead, uint8_t *pData)
{
	// uint8_t i;
	uint8_t xdata u8TimeOut;
	uint16_t xdata t;

	if (!I2C_Write_Address(addRead)) {
		return 0;
	}

	
	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = (EEPROM_SLA | EEPROM_RD);
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x40) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	/* last byte */
	AA = 0;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	if (u8TimeOut) {
		/* send data error */
		send_stop();
		return 0;
	}
	if (I2STAT != 0x58) {
		/* send data error */
		send_stop();
		return 0;
	}
	*pData = I2DAT;
	/* stop */
	return send_stop();
}

bit I2C_ReadInt(uint8_t addRead, uint16_t *pData)
{
	// uint8_t i;
	uint8_t xdata u8TimeOut;
	uint16_t xdata t;

	if (!I2C_Write_Address(addRead)) {
		return 0;
	}


	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = (EEPROM_SLA | EEPROM_RD);
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x40) {
		/* send address error */
		send_stop();
		return 0;
	}

	// get Data
	// for (i = 0; i < length - 1; ++i) {
		AA = 1;
		SI = 0;
		t = 1;
		u8TimeOut = 0;
		while (1) {
			if (SI) {
				break;
			}
			if (!t) {
				u8TimeOut = 1;
				break;
			}
			++t;
		}
		if (u8TimeOut) {
			/* send data error */
			send_stop();
			return 0;
		}
		if (I2STAT != 0x50) {
			/* send data error */
			send_stop();
			return 0;
		}
		*pData = I2DAT;
	// }
	
	/* last byte */
	AA = 0;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	if (u8TimeOut) {
		/* send data error */
		send_stop();
		return 0;
	}
	if (I2STAT != 0x58) {
		/* send data error */
		send_stop();
		return 0;
	}
	*pData = (*pData << 8) | I2DAT;
	/* stop */
	return send_stop();
}

bit I2C_CheckAddress(uint8_t Address)
{
	uint16_t xdata t;
	uint8_t xdata u8TimeOut;
	
	
	if (I2STAT != 0xF8) {
		return 0;
	}
	
	/* start */
	STO = 0;
	STA = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* start error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x08) {
		/* start error */
		send_stop();
		return 0;
	}
	
	/* send address */
	STA = 0;
	STO = 0;
	I2DAT = (Address | EEPROM_RD);
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	
	if (u8TimeOut) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	if (I2STAT != 0x40) {
		/* send address error */
		send_stop();
		return 0;
	}
	
	/* last byte */
	AA = 0;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (SI) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	if (u8TimeOut) {
		/* send data error */
		send_stop();
		return 0;
	}
	if (I2STAT != 0x58) {
		/* send data error */
		send_stop();
		return 0;
	}
	t = I2DAT;
	/* stop */
	return send_stop();
}

bit send_stop(void)
{
	uint16_t xdata t;
	uint8_t xdata u8TimeOut;
	
	STA = 0;
	STO = 1;
	SI = 0;
	t = 1;
	u8TimeOut = 0;
	while (1) {
		if (I2STAT == 0xF8) {
			break;
		}
		if (!t) {
			u8TimeOut = 1;
			break;
		}
		++t;
	}
	return (!u8TimeOut);
}
