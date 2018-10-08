/**
 * @file   	%<%NAME%>%.%<%EXTENSION%>%
 * @author 	%<%USER%>%
 * @version
 * @date 	%<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include <Lib_A_VMCPC_vmc_protocol_communicate/Lib_A_VMCPC_F3M_vmc_protocol_communicate.h>
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
static uint16_t
VMCPC_F3M_CalcCRC16For3Motors(
	vmcpc_f3m_package_s *p_s);
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/
/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/

/**
 * @brief	Функция формирует пакет данных для управления 3-мя
 * 			электродвигателями
 * @param[out]	*p_s:	Указатель на структуру, содержащую пакет данных для
 * 						управления электродвигателями
 * @param[in]	roll:	Момент на валу, который необходимо выдерживать
 * 						двигателю крена
 * @param[in]	pitch:	Момент на валу, который необходимо выдерживать
 * 						двигателю тангажа
 * @param[in]	yaw:	Момент на валу, который необходимо выдерживать
 * 						двигателю азимута
 * @return	None
 */
void
VMCPC_F3M_SetControlPackage(
	vmcpc_f3m_package_s *p_s,
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
		VMCPC_F3M_CalcCRC16For3Motors(p_s);
}

/**
 * @brief	Функция выполняет разбор принятого пакета данных
 * @param[in]	*p_s:	Указатель на структуру, которая содержит пакет данных
 * 						для управления электродвигателями
 * @param[in]	whoIAm:	Перечисляемый тип, который указывает, управление по
 * 						какой оси осуществляет контроллер векторного регулятора
 * 						@arg VMCPC_I_AM_ROLL
 * 						@arg VMCPC_I_AM_PITCH
 * 						@arg VMCPC_I_AM_YAW
 * 						@arg VMCPC_VECT_RIGHT
 * 						@arg VMCPC_VECT_LEFT
 * @return	Момент на валку, который необходимо выдерживать до следующей команды
 */
__VMCPC_FPT__
VMCPC_F3M_ParceControlPackage(
	vmcpc_f3m_package_s *p_s,
	vmcpc_who_i_am_e whoIAm)
{
	/* Если начало пакета и контрольная сумма верны */
	if ((p_s->startFrame == VMVPC_START_FRAME_1_BYTE)
			&& (p_s->poly0x1021_crc16 == VMCPC_F3M_CalcCRC16For3Motors(p_s)))
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

/**
 * @brief	Функция выполняет расчет 16-ти битной контрольной суммы пакета данных
 * @param[in]	*p_s:	Указатель на структуру, которая содержит пакет данных
 * 						для управления электродвигателям
 * @return	16-ти битная контрольная сумма пакета данных
 */
uint16_t
VMCPC_F3M_CalcCRC16For3Motors(
	vmcpc_f3m_package_s *p_s)
{
	return (CRC_XOR_CCITT_Poly0x1021_Crc16(
				(uint8_t*)p_s,
				sizeof(vmcpc_f3m_package_s) - VMCPC_F3M_PACKAGE_S_CRC_BYTES_NUMB));
}
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
