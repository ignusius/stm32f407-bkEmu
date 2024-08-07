#include <string.h>
#include <stdint.h>

#include "startup.h"
#include "emulator.h"
#include "SDCard.h"
#include "Emulator/bkEmu.h"
#include "Keyboard/ps2Keyboard.h"
#include "Emulator/pdp/defines.h"

extern "C" void initialize()
{
	initializeVideo();

	// SD card read / write LED
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
#ifdef BOARD2
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
#else
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
#endif
}

extern "C" void setup()
{
	startVideo();

	// Initialize PS2 Keyboard
	Ps2_Initialize();

	// Initialize BK emulator
	bk_setup(&MainScreen);

	showHelp();
}

extern "C" void loop()
{
	if (loadSnapshotLoop())
	{
		return;
	}

	if (saveSnapshotLoop())
	{
		return;
	}

	if (showKeyboardLoop())
	{
		return;
	}

	if (setDateTimeLoop())
	{
		return;
	}

	int32_t result = bk_loop();

//    char* buf = (char*)_buffer16K_1;
//    sprintf(buf, "PC %04x", pdp.regs[PC]);
//    DebugScreen.PrintAlignCenter(2, buf);

	switch (result)
	{


	case KEY_F1:
		toggleHelp();
		break;

#ifndef BOARD2
	case KEY_F2:
		if (!saveSnapshotSetup())
		{
			showErrorMessage("Cannot initialize SD card");
		}
		break;
#endif

	case KEY_F3:
		if (!loadSnapshotSetup())
		{
			showErrorMessage("Error when loading from SD card");
		}
		break;

	case KEY_F5:
		bk_reset();
		showHelp();
		break;

#ifndef BOARD2
	case KEY_F6:
		setDateTimeSetup();
		break;
#endif

	case KEY_F7:
		togglePalette();
		break;

	case KEY_F10:
		showKeyboardSetup();
		break;

	case KEY_F12:
		showRegisters();
		break;
	}
}
