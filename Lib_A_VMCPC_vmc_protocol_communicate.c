/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_VMCPC_vmc_protocol_communicate.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
static uint16_t
VMCPC_LEGACY_CalcCRC16For3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s);
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/
void
VMCPC_LEGACY_SetCotrolPackageFor3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s,
	__VMCPC_FPT__ roll,
	__VMCPC_FPT__ pitch,
	__VMCPC_FPT__ yaw)
{
	/* Условие начала пакета данных */
	p_s->startFrame = VMVPC_START_FRAME_1_BYTE;

	/* Заполнение массива управления. Значения из этого массива будут
	 * применены к 3-м электродвигателям */
	p_s->actualControl_a[VMCPC_VECT_X_ROLL] 	= roll;
	p_s->actualControl_a[VMCPC_VECT_Y_PITCH] 	= pitch;
	p_s->actualControl_a[VMCPC_VECT_Z_YAW] 		= yaw;

	/* Расчет контрольной суммы пакета данных и копирование в конец пакета
	 * данных */
	p_s->poly0x1021_crc16 =
		VMCPC_LEGACY_CalcCRC16For3Motors(p_s);
}

__VMCPC_FPT__
VMCPC_LEGACY_ParceControlPackageFor3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s,
	vmcpc_who_i_am_e whoIAm)
{
	/* Если начало пакета и контрольная сумма верны */
	if ((p_s->startFrame == VMVPC_START_FRAME_1_BYTE)
			&& (p_s->poly0x1021_crc16 == VMCPC_LEGACY_CalcCRC16For3Motors(p_s)))
	{
		switch (whoIAm)
		{
		case VMCPC_I_AM_ROLL:
			return ((__VMCPC_FPT__) p_s->actualControl_a[VMCPC_VECT_X_ROLL]);
			break;

		case VMCPC_I_AM_PITCH:
			return ((__VMCPC_FPT__) p_s->actualControl_a[VMCPC_VECT_Y_PITCH]);
			break;

		case VMCPC_I_AM_YAW:
			return ((__VMCPC_FPT__) p_s->actualControl_a[VMCPC_VECT_Z_YAW]);
			break;

		default:
			break;
		}
	}
	/* Если принятый пакет данных не валиден */
	return ((__VMCPC_FPT__)0.0);
}

/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
uint16_t
VMCPC_LEGACY_CalcCRC16For3Motors(
	vmcpc_legacy_package_for_3_motors_s *p_s)
{
	return (CRC_XOR_CCITT_Poly0x1021_Crc16(
				(uint8_t*)p_s,
				sizeof(vmcpc_legacy_package_for_3_motors_s) - VMCPC_LEGACY_PACKAGE_FOR_3_MOTORS_S_BYTES_NUMB));
}
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
