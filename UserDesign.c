// ######################################################################################
// #                                                                                    #
// #  This module implements the users design                                           #
// #                                                                                    #
// ######################################################################################

#include <util/delay.h>
#include "UserDesign.h"

AutomatStates_t State;


void StateMachineInit(void) {
	State = Init;
}

void SetY_0(){
	Actuators.TransportTableMoveToConveyorBelt3 = 0;							// y0 Транспортный стол - перейти к конвейерной ленте 3 
	Actuators.TransportTableMoveToConveyorBelt1 = 0;							// y1 Транспортный стол - перейти к конвейерной ленте 1
	Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt1 = 0;    // y2 Транспортный стол - приводная конвейерная лента, аналогичная конвейерной ленте 1
	Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt3 = 0;    // y3 Транспортный стол - приводная конвейерная лента, аналогичная конвейерной ленте 3
	Actuators.ConveyorBelt1DriveBelt = 0;                                   // y4 конвейерная лента 1 - приводной ремень
	Actuators.Turntable1RotateToConveyorBelt1 = 0;                          // y5 Поворотный стол 1 - повернуть на ленточный конвейер 1
	Actuators.Turntable1RotateToConveyorBelt2 = 0;                          // y6  Поворотный стол 1 - повернуть на ленточный конвейер 2
	Actuators.Turntable1DriveBelt = 0;                                       // y7 Поворотный стол 1 - приводной ремень
	Actuators.ConveyorBelt2DriveBelt = 0;                                 // y8 конвейерная лента 2 - приводной ремень
	Actuators.Turntable2RotateToConveyorBelt2 = 0;                            // y9 поворотный стол 2 - повернуть на конвейер 2
	Actuators.Turntable2RotateToConveyorBelt_3 = 0;                           // y10 поворотный стол 2 - повернуть на конвейер 3
	Actuators.Turntable2DriveBelt = 0;                                       // y11 поворотный стол 2 - приводной ремень
	Actuators.ConveyorBelt3DriveBelt = 0;                                    // y12 конвейерная лента 3 - приводной ремень
	Actuators.MillingMachineApproachConveyorBelt_2 = 0;                     // y13 Фрезерный станок - отступление от конвейерной ленты 2
	Actuators.MillingMachineRetreatFromConveyorBelt2 = 0;                   // y14  Фрезерный станок - подъездной конвейер 2
	Actuators.MillingHeadRise = 0;                                         // y15 фрезерная головка - подъем
	Actuators.MillingHeadLower = 0;                                        // y16 фрезерная головка - нижняя
	Actuators.MillingHeadDriveHead = 0;                                       // y17 фрезерная головка - головка привода 
}

void SetY(int z){
	if (z == 0) Actuators.TransportTableMoveToConveyorBelt3 = 1;                        // y0
	if (z == 1) Actuators.TransportTableMoveToConveyorBelt1 = 1;                        // y1
	if (z == 2) Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt1 = 1;    // y2
	if (z == 3) Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt3 = 1;    // y3
	if (z == 4) Actuators.ConveyorBelt1DriveBelt = 1;                                   // y4
	if (z == 5) Actuators.Turntable1RotateToConveyorBelt1 = 1;                          // y5
	if (z == 6) Actuators.Turntable1RotateToConveyorBelt2 = 1;                          // y6
	if (z == 7) Actuators.Turntable1DriveBelt = 1;                                       // y7
	if (z == 8) Actuators.ConveyorBelt2DriveBelt = 1;                                   // y8
	if (z == 9) Actuators.Turntable2RotateToConveyorBelt2 = 1;                           // y9
	if (z == 10) Actuators.Turntable2RotateToConveyorBelt_3 = 1;                          // y10
	if (z == 11) Actuators.Turntable2DriveBelt = 1;                                       // y11
	if (z == 12) Actuators.ConveyorBelt3DriveBelt = 1;                                   // y12
	if (z == 13) Actuators.MillingMachineApproachConveyorBelt_2 = 1;                     // y13
	if (z == 14) Actuators.MillingMachineRetreatFromConveyorBelt2 = 1;                   // y14
	if (z == 15) Actuators.MillingHeadRise = 1;                                          // y15
	if (z == 16) Actuators.MillingHeadLower = 1;                                         // y16
	if (z == 17) Actuators.MillingHeadDriveHead = 1;                                     // y17
}

void delay(int t) {
	int g = 1;
	for (int k = 0; k < t; k++){
		for (int i = 0; i < 14000; i++){
			for (int j = 0; j < 1000; j++){
				g *= -1;
			}
		}
	}
}

void StateMachineUpdate(void){
	SetY_0();
	int s[] = {
		Sensors.TransportTableInLineWithConveyorBelt3,      // x0=s[0]  Транспортный стол на одной линии с конвейерной лентой 3
		Sensors.TransportTableInLineWithWonveyorBelt1,      // x1  Транспортный стол в соответствии с конвейерной лентой 1
		Sensors.TransportTableWorkpieceAvailable,           // x2  Транспортный стол - заготовка доступна
		Sensors.ConveyorBelt1WorkpieceAvailable,            // x3  Конвейерная лента 1 - заготовка доступна
		Sensors.Turntable1InLineWithConveyorBelt1,          // x4  Поворотный стол 1 на одной линии с конвейерной лентой 1
		Sensors.Turntable1InLineWithConveyorBelt2,          // x5  Поворотный стол 1 на одной линии с конвейерной лентой 2
		Sensors.Turntable1WorkpieceAvailable,               // x6  поворотный стол 1 - заготовка доступна
		Sensors.ConveyorBelt2WorkpieceAvailable,            // x7  Конвейерная лента 2 - возможна заготовка
		Sensors.Turntable2InLineWithConveyorBelt2,          // x8  поворотный стол 2 на одной линии с конвейерной лентой 2
		Sensors.Turntable2InLineWithConveyorBelt3,          // x9  поворотный стол 2 на одной линии с конвейерной лентой 3
		Sensors.Turntable2WorkpieceAvailable,               // x10  поворотный стол 2 - заготовка доступна
		Sensors.ConveyorBelt3WorkpieceAvailable,            // x11  Конвейерная лента 3 - возможна заготовка
		Sensors.MillingMachineAwayFromConveyorBelt2,        // x12  фрезерный станок от конвейерной ленты 2
		Sensors.MillingMachineAtConveyorBelt2,              // x13  Фрезерный станок на конвейерной ленте 2
		Sensors.MillingHeadIsUp,                            // x14  фрезерная головка поднята
		Sensors.MillingHeadIsDown,                          // x15  фрезерная головка не работает
		Sensors.EmergencyStop                               // x16  аварийная остановка
	};

	switch(State) {
		case Init: {
			State = Init;
			if (s[7] || s[10]) State = RT2_init;		//переход заготовки с ленты CB2 на ленту СВ3, если заготовка на ленте СВ2 или на столе RT2 
			if (s[2] || s[11]) State = TT_init;			//переход заготовки с ленты СВ3 на ленту СВ1, если заготовка на ТТ или на ленте СВ3
			if (s[3] || s[6]) State = RT1_init;			//переход заготовки с ленты CB1 на ленту СВ2, если заготовка на ленте СВ1 или на столе RT1
			if (s[7]) State = MM_init;					// работа фрезерного станка , если заготовка на ленте СВ2
			break;
		}
		case RT2_init: {   //перемещение груза с ленты СВ2 на ленту СВ3, при помощи стола RT2
			State = Init;
			if (s[7] && !s[8]) State = RT2_rotate_l;	// вращение RT2 в горизонтально, если заготовка на ленте СВ2 и стол RT2 не стоит горизонтально (поворотный стол 2 не на одной линии с конвейерной лентой 2)  
			if (s[8] && !s[10]) State = RT2_download; 	// перемещение груза с ленты СВ2 на стол RT2, если поворотный стол RT2 на одной линии с конвейерной лентой СВ2 и заготовка не на ленте СВ2
			if (s[10] && !s[9]) State = RT2_rotate_r;	// вращение RT2 в вертикально, если заготовка на поворотном столе RT2 и стол RT2 не стоит вертикально (поворотный стол 2 не на одной линии с конвейерной лентой 3)
			if (s[9] && !s[11]) State = RT2_upload;		// перемещение груза с стола RT2 на ленту СВ3, если поворотный стол RT2 на одной линии с конвейерной лентой СВ3(вертикально) и заготовка не на ленте СВ3
			if (s[9] && s[11]) State = RT2_to_wait;		// нахождение груза на ленте СВ3, если поворотный стол RT2 на одной линии с конвейерной лентой СВ3(вертикально) и заготовка на ленте СВ3
			break;
		}
		case RT2_rotate_l: {	// вращение RT2 в горизонтально
			SetY(9);					//поворотный стол RT2 - повернуть на конвейер СВ2(гор)
			if (s[7] && !s[8]) State = RT2_rotate_l;
			else State = RT2_init;
			break;
		}
		case RT2_download: {	// перемещение груза с ленты СВ2 на стол RT2
			SetY(8);					//конвейерная лента СВ2 - приводной ремень
			SetY(11);					//поворотный стол RT2 - приводной ремень
			if (s[8] && !s[10]) State = RT2_download;
			else State = RT2_init;
			break;
		}
		case RT2_rotate_r: {	// вращение RT2 в вертикально
			SetY(10);					//поворотный стол RT2 - повернуть на конвейер СВ3(верт)
			if (!s[9] && s[10]) State = RT2_rotate_r;
			else State = RT2_init;
			break;
		}
		case RT2_upload: {	// перемещение груза с стола RT2 на ленту СВ3
			SetY(11);					//поворотный стол RT2 - приводной ремень
			SetY(12);					//конвейерная лента СВ3 - приводной ремень
			if (s[9] && !s[11]) State = RT2_upload;
			else State = RT2_init;
			break;
		}
		case RT2_to_wait: {	// нахождение груза на ленте СВ3 и возвращение стола RT2 в горизонтальное положение
			SetY(9);				//поворотный стол RT2 - повернуть на конвейер СВ2(гор)
			if (s[9] && s[11]) State = RT2_to_wait;
			else State = RT2_init;
			break;
		}
		case TT_init: {	//переход заготовки с ленты СВ3 на ленту СВ1, при помощи транспортного стола TT
			State = Init;
			if (!s[0] && s[11]) State = TT_move_r;  // перемещение транспортного стола ТТ вправо, если его нет перед лентой RT2 и на ленте RT2 лежит груз
			if (s[0] && !s[2]) State = TT_download; //перемещение груза с ленты СВ3 на транспортный стол ТТ, если на ТТ нет груза и он находится под лентой RT2
			if (!s[1] && s[2]) State = TT_move_l;   // перемещение транспортного стола ТТ влево, если его нет перед лентой RT1 и на транспортном столе ТТ лежит груз
			if (s[1] && !s[3]) State = TT_upload;		//перемещение груза с транспортного стола ТТ на ленту СВ1, если на ленте RT1 нет груза и  ТТ под лентой RT1
			if (s[1] && (s[3] || s[11])) State = TT_to_wait;  // нахождение груза на ленте СВ1 и возвращение TT направо, под ленту СВ3
			break;
		}
		case TT_move_r: { // перемещение транспортного стола ТТ вправо
			SetY(0);  //Транспортный стол TT - перейти к конвейерной ленте СВ3
			if (!s[0] && s[11]) State = TT_move_r;
			else State = TT_init;
			break;
		}
		case TT_download: {  //перемещение груза с ленты СВ3 на транспортный стол ТТ
			SetY(3);   //Транспортный стол TT - приводная конвейерная лента, аналогичная конвейерной ленте СВ3
			SetY(12);    //конвейерная лента СВ3 - приводной ремень
			if (s[0] && !s[2]) State = TT_download;
			else State = TT_init;
			break;
		}
		case TT_move_l: {  // перемещение транспортного стола ТТ влево
			SetY(1);  //Транспортный стол TT - перейти к конвейерной ленте СВ1
			if (!s[1] && s[2]) State = TT_move_l;
			else State = TT_init;
			break;
		}
		case TT_upload: {  //перемещение груза с транспортного стола ТТ на ленту СВ1
			 SetY(2);   //Транспортный стол TT - приводная конвейерная лента, аналогичная конвейерной ленте СВ1
			SetY(4);   //конвейерная лента СВ1 - приводной ремень
			if (s[1] && !s[3]) State = TT_upload;
			else State = TT_init;
			break;
		}
		case TT_to_wait: {  // нахождение груза на ленте СВ1 и возвращение TT направо, под ленту СВ3
			SetY(0);  //Транспортный стол TT - перейти к конвейерной ленте СВ3
			if (s[1] && (s[3] || s[11])) State = TT_to_wait;
			else State = TT_init;
			break;
		}
		case RT1_init: {   //перемещение груза с ленты СВ1 на ленту СВ2, при помощи стола RT1
			State = Init;
			if (s[3] && !s[4]) State = RT1_rotate_l; // вращение RT1 в вертикальное положение
			if (!s[0] && s[4] && !s[6]) State = RT1_download; // перемещение груза с ленты СВ1 на стол RT1
			if (!s[5] && s[6]) State = RT1_rotate_r;// вращение RT1 в горизонтальное положение
			if (s[5] && !s[7]) State = RT1_upload; // перемещение груза с стола RT1 на ленту СВ2
			if (s[5] && (s[7] || s[3])) State = RT1_to_wait; // нахождение груза на ленте СВ2 и возвращение стола RT1 в вертикальное положение
			break;
		}
		case RT1_rotate_l: { // вращение RT1 в вертикально
			SetY(5);   //Поворотный стол RT1 - повернуть на ленточный конвейер СВ1
			if (s[3] && !s[4]) State = RT1_rotate_l;
			else State = RT1_init;
			break;
		}
		case RT1_download: { 	// перемещение груза с ленты СВ1 на стол RT1
			SetY(4);   //конвейерная лента СВ1 - приводной ремень
			SetY(7);   //Поворотный стол RT1 - приводной ремень
			if (!s[0] && s[4] && !s[6]) State = RT1_download;
			else State = RT1_init;
			break;
		}
		case RT1_rotate_r: {	// вращение RT1 в горизонтально
			SetY(6);   //Поворотный стол RT1 - повернуть на ленточный конвейер СВ2
			if (!s[5] && s[6]) State = RT1_rotate_r;
			else State = RT1_init;
			break;
		}
		case RT1_upload: {  // перемещение груза с стола RT1 на ленту СВ2
			SetY(7);   //Поворотный стол RT1 - приводной ремень
			SetY(8);	  //конвейерная лента СВ2 - приводной ремень
			if (s[5] && !s[7]) State = RT1_upload;
			else State = RT1_init;
			break;
		}
		case RT1_to_wait: { // нахождение груза на ленте СВ2 и возвращение стола RT1 в вертикальное положение
			SetY(5);   //Поворотный стол RT1 - повернуть на ленточный конвейер СВ1
			if (s[5] && (s[7] || s[3])) State = RT1_to_wait;
			else State = RT1_init;
			break;
		}
		case MM_init: {   // работа фрезерного станка
			State = Init;
			if (s[7]) State = MM_move_f;
			break;
		}
		case MM_move_f: {
			SetY(14);   //Фрезерный станок MM - подъездной конвейер СВ2
			if (s[7] && !s[13]) State = MM_move_f;
			else State = MM_down;
			break;
		}
		case MM_down: {
			SetY(16);   //фрезерная головка - нижняя
			SetY(17);   //фрезерная головка - головка привода
			if (s[7] && s[13] && !s[15]) State = MM_down;
			else State = MM_work;
			break;
		}
		case MM_work: {
			SetY(17);   //фрезерная головка - головка привода
			if (s[7] && s[13] && s[15]) State = MM_work_time;
			break;
		}
		case MM_work_time: {
			delay(10000);	//задержка 
			State = MM_up;
			break;
		}
		case MM_up: {
			SetY(15);   //фрезерная головка - подъем
			if (!s[14]) State = MM_up;
			else State = MM_move_b;
			break;
		}
		case MM_move_b: {
			SetY(13);   //Фрезерный станок MM - отступление от конвейерной ленты СВ2
			if (!s[12]) State = MM_move_b;
			else State = RT2_init;
			break;
		}
	}
}
