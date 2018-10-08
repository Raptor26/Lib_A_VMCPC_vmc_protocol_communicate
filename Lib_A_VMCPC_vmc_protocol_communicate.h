/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


#ifndef LIB_A_VMCPC_VMC_PROTOCOL_COMMUNICATE_H_
#define LIB_A_VMCPC_VMC_PROTOCOL_COMMUNICATE_H_


/*#### |Begin| --> Секция - "Include" ########################################*/
/*==== |Begin| --> Секция - "C libraries" ====================================*/
#include <math.h>
#include <stdint.h>
/*==== |End  | <-- Секция - "C libraries" ====================================*/

/*==== |Begin| --> Секция - "MK peripheral libraries" ========================*/
/*==== |End  | <-- Секция - "MK peripheral libraries" ========================*/

/*==== |Begin| --> Секция - "Extern libraries" ===============================*/
#include "../Lib_A_CRC_cyclic_redundancy_check/Lib_A_CRC_cyclic_redundancy_check.h"
/*==== |End  | <-- Секция - "Extern libraries" ===============================*/
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Определение констант" ###########################*/
#if !defined (__VMCPC_FPT__)	///< __VMCPC_FPT__ - FLOAT_POINT_TYPE
#error "Please, set value for macros __VMCPC_FPT__ float or double"
#endif

#define VMVPC_START_FRAME_1_BYTE				((uint8_t)0xAA)
/*#### |End  | <-- Секция - "Определение констант" ###########################*/


/*#### |Begin| --> Секция - "Определение типов" ##############################*/
enum
{
	VMCPC_VECT_X_ROLL = 0,
	VMCPC_VECT_Y_PITCH,
	VMCPC_VECT_Z_YAW,

	/**
	 * @brief	Размерность вектора управления 3-мя электродвигателями
	 */
	VMCPC_SIZE_VECT_ARR,

	VMCPC_VECT_RIGHT 	= VMCPC_VECT_X_ROLL,
	VMCPC_VECT_LEFT 	= VMCPC_VECT_Y_PITCH,
};

typedef enum
{
	VMCPC_I_AM_ROLL 	= VMCPC_VECT_X_ROLL,
	VMCPC_I_AM_PITCH 	= VMCPC_VECT_Y_PITCH,
	VMCPC_I_AM_YAW 		= VMCPC_VECT_Z_YAW,
	VMCPC_I_AM_UNKNOW,

	VMCPC_I_AM_RIGHT 	= VMCPC_I_AM_ROLL,
	VMCPC_I_AM_LEFT 	= VMCPC_I_AM_PITCH,
} vmcpc_who_i_am_e;

/**
 * @brief	Структура пакета данных для управления 3-мя электродвигателями.
 * 			Три электродвигателя принимают данный пакет данных одновременно, в
 * 			зависимости от того, какой осью управляет электродвигатель,
 * 			в качестве управления берется соответствующая ячейка из массива
 * 			"actualControl_a":
 * 				- если двигатель управляет осью крена, то берется 0-я ячейка массива
 *					@arg VMCPC_VECT_X_ROLL
 * 				- если двигатель управляет осью тангажа, то берется 1-я ячейка массива
 * 					@arg VMCPC_VECT_Y_PITCH
 * 				- если двигатель управляет осью азимута, то берется 2-я ячейка массива
 * 					@arg VMCPC_VECT_Z_YAW
 */
typedef struct
{
	/* Условие начала пакета данных */
	uint8_t startFrame;

	/* Массив, в котором содержится значение управления для каждой из 3-х осей */
	__VMCPC_FPT__ actualControl_a[VMCPC_SIZE_VECT_ARR];

	/* Контрольная сумма пакета данных */
	uint16_t poly0x1021_crc16;
}
__attribute__((__packed__))
vmcpc_legacy_package_for_3_motors_s;
#define VMCPC_LEGACY_PACKAGE_FOR_3_MOTORS_S_BYTES_NUMB	2
/*#### |End  | <-- Секция - "Определение типов" ##############################*/


/*#### |Begin| --> Секция - "Определение глобальных переменных" ##############*/
/*#### |End  | <-- Секция - "Определение глобальных переменных" ##############*/


/*#### |Begin| --> Секция - "Прототипы глобальных функций" ###################*/
extern void
VMCPC_LEGACY_SetCotrolPackageFor3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s,
	__VMCPC_FPT__ roll,
	__VMCPC_FPT__ pitch,
	__VMCPC_FPT__ yaw);

extern __VMCPC_FPT__
VMCPC_LEGACY_ParceControlPackageFor3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s,
	vmcpc_who_i_am_e whoIAm);
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif	/* LIB_A_VMCPC_VMC_PROTOCOL_COMMUNICATE_H_ */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
