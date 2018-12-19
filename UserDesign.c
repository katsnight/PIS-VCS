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
	Actuators.TransportTableMoveToConveyorBelt3 = 0;							// y0 ������������ ���� - ������� � ����������� ����� 3 
	Actuators.TransportTableMoveToConveyorBelt1 = 0;							// y1 ������������ ���� - ������� � ����������� ����� 1
	Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt1 = 0;    // y2 ������������ ���� - ��������� ����������� �����, ����������� ����������� ����� 1
	Actuators.TransportTableDriveConveyorBeltSimilarToConveyorBelt3 = 0;    // y3 ������������ ���� - ��������� ����������� �����, ����������� ����������� ����� 3
	Actuators.ConveyorBelt1DriveBelt = 0;                                   // y4 ����������� ����� 1 - ��������� ������
	Actuators.Turntable1RotateToConveyorBelt1 = 0;                          // y5 ���������� ���� 1 - ��������� �� ��������� �������� 1
	Actuators.Turntable1RotateToConveyorBelt2 = 0;                          // y6  ���������� ���� 1 - ��������� �� ��������� �������� 2
	Actuators.Turntable1DriveBelt = 0;                                       // y7 ���������� ���� 1 - ��������� ������
	Actuators.ConveyorBelt2DriveBelt = 0;                                 // y8 ����������� ����� 2 - ��������� ������
	Actuators.Turntable2RotateToConveyorBelt2 = 0;                            // y9 ���������� ���� 2 - ��������� �� �������� 2
	Actuators.Turntable2RotateToConveyorBelt_3 = 0;                           // y10 ���������� ���� 2 - ��������� �� �������� 3
	Actuators.Turntable2DriveBelt = 0;                                       // y11 ���������� ���� 2 - ��������� ������
	Actuators.ConveyorBelt3DriveBelt = 0;                                    // y12 ����������� ����� 3 - ��������� ������
	Actuators.MillingMachineApproachConveyorBelt_2 = 0;                     // y13 ��������� ������ - ����������� �� ����������� ����� 2
	Actuators.MillingMachineRetreatFromConveyorBelt2 = 0;                   // y14  ��������� ������ - ���������� �������� 2
	Actuators.MillingHeadRise = 0;                                         // y15 ��������� ������� - ������
	Actuators.MillingHeadLower = 0;                                        // y16 ��������� ������� - ������
	Actuators.MillingHeadDriveHead = 0;                                       // y17 ��������� ������� - ������� ������� 
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
		Sensors.TransportTableInLineWithConveyorBelt3,      // x0=s[0]  ������������ ���� �� ����� ����� � ����������� ������ 3
		Sensors.TransportTableInLineWithWonveyorBelt1,      // x1  ������������ ���� � ������������ � ����������� ������ 1
		Sensors.TransportTableWorkpieceAvailable,           // x2  ������������ ���� - ��������� ��������
		Sensors.ConveyorBelt1WorkpieceAvailable,            // x3  ����������� ����� 1 - ��������� ��������
		Sensors.Turntable1InLineWithConveyorBelt1,          // x4  ���������� ���� 1 �� ����� ����� � ����������� ������ 1
		Sensors.Turntable1InLineWithConveyorBelt2,          // x5  ���������� ���� 1 �� ����� ����� � ����������� ������ 2
		Sensors.Turntable1WorkpieceAvailable,               // x6  ���������� ���� 1 - ��������� ��������
		Sensors.ConveyorBelt2WorkpieceAvailable,            // x7  ����������� ����� 2 - �������� ���������
		Sensors.Turntable2InLineWithConveyorBelt2,          // x8  ���������� ���� 2 �� ����� ����� � ����������� ������ 2
		Sensors.Turntable2InLineWithConveyorBelt3,          // x9  ���������� ���� 2 �� ����� ����� � ����������� ������ 3
		Sensors.Turntable2WorkpieceAvailable,               // x10  ���������� ���� 2 - ��������� ��������
		Sensors.ConveyorBelt3WorkpieceAvailable,            // x11  ����������� ����� 3 - �������� ���������
		Sensors.MillingMachineAwayFromConveyorBelt2,        // x12  ��������� ������ �� ����������� ����� 2
		Sensors.MillingMachineAtConveyorBelt2,              // x13  ��������� ������ �� ����������� ����� 2
		Sensors.MillingHeadIsUp,                            // x14  ��������� ������� �������
		Sensors.MillingHeadIsDown,                          // x15  ��������� ������� �� ��������
		Sensors.EmergencyStop                               // x16  ��������� ���������
	};

	switch(State) {
		case Init: {
			State = Init;
			if (s[7] || s[10]) State = RT2_init;		//������� ��������� � ����� CB2 �� ����� ��3, ���� ��������� �� ����� ��2 ��� �� ����� RT2 
			if (s[2] || s[11]) State = TT_init;			//������� ��������� � ����� ��3 �� ����� ��1, ���� ��������� �� �� ��� �� ����� ��3
			if (s[3] || s[6]) State = RT1_init;			//������� ��������� � ����� CB1 �� ����� ��2, ���� ��������� �� ����� ��1 ��� �� ����� RT1
			if (s[7]) State = MM_init;					// ������ ���������� ������ , ���� ��������� �� ����� ��2
			break;
		}
		case RT2_init: {   //����������� ����� � ����� ��2 �� ����� ��3, ��� ������ ����� RT2
			State = Init;
			if (s[7] && !s[8]) State = RT2_rotate_l;	// �������� RT2 � �������������, ���� ��������� �� ����� ��2 � ���� RT2 �� ����� ������������� (���������� ���� 2 �� �� ����� ����� � ����������� ������ 2)  
			if (s[8] && !s[10]) State = RT2_download; 	// ����������� ����� � ����� ��2 �� ���� RT2, ���� ���������� ���� RT2 �� ����� ����� � ����������� ������ ��2 � ��������� �� �� ����� ��2
			if (s[10] && !s[9]) State = RT2_rotate_r;	// �������� RT2 � �����������, ���� ��������� �� ���������� ����� RT2 � ���� RT2 �� ����� ����������� (���������� ���� 2 �� �� ����� ����� � ����������� ������ 3)
			if (s[9] && !s[11]) State = RT2_upload;		// ����������� ����� � ����� RT2 �� ����� ��3, ���� ���������� ���� RT2 �� ����� ����� � ����������� ������ ��3(�����������) � ��������� �� �� ����� ��3
			if (s[9] && s[11]) State = RT2_to_wait;		// ���������� ����� �� ����� ��3, ���� ���������� ���� RT2 �� ����� ����� � ����������� ������ ��3(�����������) � ��������� �� ����� ��3
			break;
		}
		case RT2_rotate_l: {	// �������� RT2 � �������������
			SetY(9);					//���������� ���� RT2 - ��������� �� �������� ��2(���)
			if (s[7] && !s[8]) State = RT2_rotate_l;
			else State = RT2_init;
			break;
		}
		case RT2_download: {	// ����������� ����� � ����� ��2 �� ���� RT2
			SetY(8);					//����������� ����� ��2 - ��������� ������
			SetY(11);					//���������� ���� RT2 - ��������� ������
			if (s[8] && !s[10]) State = RT2_download;
			else State = RT2_init;
			break;
		}
		case RT2_rotate_r: {	// �������� RT2 � �����������
			SetY(10);					//���������� ���� RT2 - ��������� �� �������� ��3(����)
			if (!s[9] && s[10]) State = RT2_rotate_r;
			else State = RT2_init;
			break;
		}
		case RT2_upload: {	// ����������� ����� � ����� RT2 �� ����� ��3
			SetY(11);					//���������� ���� RT2 - ��������� ������
			SetY(12);					//����������� ����� ��3 - ��������� ������
			if (s[9] && !s[11]) State = RT2_upload;
			else State = RT2_init;
			break;
		}
		case RT2_to_wait: {	// ���������� ����� �� ����� ��3 � ����������� ����� RT2 � �������������� ���������
			SetY(9);				//���������� ���� RT2 - ��������� �� �������� ��2(���)
			if (s[9] && s[11]) State = RT2_to_wait;
			else State = RT2_init;
			break;
		}
		case TT_init: {	//������� ��������� � ����� ��3 �� ����� ��1, ��� ������ ������������� ����� TT
			State = Init;
			if (!s[0] && s[11]) State = TT_move_r;  // ����������� ������������� ����� �� ������, ���� ��� ��� ����� ������ RT2 � �� ����� RT2 ����� ����
			if (s[0] && !s[2]) State = TT_download; //����������� ����� � ����� ��3 �� ������������ ���� ��, ���� �� �� ��� ����� � �� ��������� ��� ������ RT2
			if (!s[1] && s[2]) State = TT_move_l;   // ����������� ������������� ����� �� �����, ���� ��� ��� ����� ������ RT1 � �� ������������ ����� �� ����� ����
			if (s[1] && !s[3]) State = TT_upload;		//����������� ����� � ������������� ����� �� �� ����� ��1, ���� �� ����� RT1 ��� ����� �  �� ��� ������ RT1
			if (s[1] && (s[3] || s[11])) State = TT_to_wait;  // ���������� ����� �� ����� ��1 � ����������� TT �������, ��� ����� ��3
			break;
		}
		case TT_move_r: { // ����������� ������������� ����� �� ������
			SetY(0);  //������������ ���� TT - ������� � ����������� ����� ��3
			if (!s[0] && s[11]) State = TT_move_r;
			else State = TT_init;
			break;
		}
		case TT_download: {  //����������� ����� � ����� ��3 �� ������������ ���� ��
			SetY(3);   //������������ ���� TT - ��������� ����������� �����, ����������� ����������� ����� ��3
			SetY(12);    //����������� ����� ��3 - ��������� ������
			if (s[0] && !s[2]) State = TT_download;
			else State = TT_init;
			break;
		}
		case TT_move_l: {  // ����������� ������������� ����� �� �����
			SetY(1);  //������������ ���� TT - ������� � ����������� ����� ��1
			if (!s[1] && s[2]) State = TT_move_l;
			else State = TT_init;
			break;
		}
		case TT_upload: {  //����������� ����� � ������������� ����� �� �� ����� ��1
			 SetY(2);   //������������ ���� TT - ��������� ����������� �����, ����������� ����������� ����� ��1
			SetY(4);   //����������� ����� ��1 - ��������� ������
			if (s[1] && !s[3]) State = TT_upload;
			else State = TT_init;
			break;
		}
		case TT_to_wait: {  // ���������� ����� �� ����� ��1 � ����������� TT �������, ��� ����� ��3
			SetY(0);  //������������ ���� TT - ������� � ����������� ����� ��3
			if (s[1] && (s[3] || s[11])) State = TT_to_wait;
			else State = TT_init;
			break;
		}
		case RT1_init: {   //����������� ����� � ����� ��1 �� ����� ��2, ��� ������ ����� RT1
			State = Init;
			if (s[3] && !s[4]) State = RT1_rotate_l; // �������� RT1 � ������������ ���������
			if (!s[0] && s[4] && !s[6]) State = RT1_download; // ����������� ����� � ����� ��1 �� ���� RT1
			if (!s[5] && s[6]) State = RT1_rotate_r;// �������� RT1 � �������������� ���������
			if (s[5] && !s[7]) State = RT1_upload; // ����������� ����� � ����� RT1 �� ����� ��2
			if (s[5] && (s[7] || s[3])) State = RT1_to_wait; // ���������� ����� �� ����� ��2 � ����������� ����� RT1 � ������������ ���������
			break;
		}
		case RT1_rotate_l: { // �������� RT1 � �����������
			SetY(5);   //���������� ���� RT1 - ��������� �� ��������� �������� ��1
			if (s[3] && !s[4]) State = RT1_rotate_l;
			else State = RT1_init;
			break;
		}
		case RT1_download: { 	// ����������� ����� � ����� ��1 �� ���� RT1
			SetY(4);   //����������� ����� ��1 - ��������� ������
			SetY(7);   //���������� ���� RT1 - ��������� ������
			if (!s[0] && s[4] && !s[6]) State = RT1_download;
			else State = RT1_init;
			break;
		}
		case RT1_rotate_r: {	// �������� RT1 � �������������
			SetY(6);   //���������� ���� RT1 - ��������� �� ��������� �������� ��2
			if (!s[5] && s[6]) State = RT1_rotate_r;
			else State = RT1_init;
			break;
		}
		case RT1_upload: {  // ����������� ����� � ����� RT1 �� ����� ��2
			SetY(7);   //���������� ���� RT1 - ��������� ������
			SetY(8);	  //����������� ����� ��2 - ��������� ������
			if (s[5] && !s[7]) State = RT1_upload;
			else State = RT1_init;
			break;
		}
		case RT1_to_wait: { // ���������� ����� �� ����� ��2 � ����������� ����� RT1 � ������������ ���������
			SetY(5);   //���������� ���� RT1 - ��������� �� ��������� �������� ��1
			if (s[5] && (s[7] || s[3])) State = RT1_to_wait;
			else State = RT1_init;
			break;
		}
		case MM_init: {   // ������ ���������� ������
			State = Init;
			if (s[7]) State = MM_move_f;
			break;
		}
		case MM_move_f: {
			SetY(14);   //��������� ������ MM - ���������� �������� ��2
			if (s[7] && !s[13]) State = MM_move_f;
			else State = MM_down;
			break;
		}
		case MM_down: {
			SetY(16);   //��������� ������� - ������
			SetY(17);   //��������� ������� - ������� �������
			if (s[7] && s[13] && !s[15]) State = MM_down;
			else State = MM_work;
			break;
		}
		case MM_work: {
			SetY(17);   //��������� ������� - ������� �������
			if (s[7] && s[13] && s[15]) State = MM_work_time;
			break;
		}
		case MM_work_time: {
			delay(10000);	//�������� 
			State = MM_up;
			break;
		}
		case MM_up: {
			SetY(15);   //��������� ������� - ������
			if (!s[14]) State = MM_up;
			else State = MM_move_b;
			break;
		}
		case MM_move_b: {
			SetY(13);   //��������� ������ MM - ����������� �� ����������� ����� ��2
			if (!s[12]) State = MM_move_b;
			else State = RT2_init;
			break;
		}
	}
}
