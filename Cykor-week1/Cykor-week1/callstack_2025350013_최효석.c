
/*  call_stack

	���� �ý��ۿ����� ������ �޸𸮿� ���������, �� ���������� `int` �迭�� �̿��Ͽ� �޸𸮸� �����մϴ�.
	������ SFP�� Return Address�� ���� ���� �޸� �ּҰ� ��������, �̹� ���������� -1�� ��ü�մϴ�.

	int call_stack[]      : ���� ������(`int ��`) �Ǵ� `-1` (��Ÿ������ ���п�)�� �����ϴ� int �迭
	char stack_info[][]   : call_stack[]�� ���� ��ġ(index)�� ���� ������ �����ϴ� ���ڿ� �迭

	==========================call_stack ���� ��Ģ==========================
	�Ű� ���� / ���� ������ push�� ���   : int �� �״��
	Saved Frame Pointer �� push�� ���  : call_stack������ index
	��ȯ �ּҰ��� push�� ���       : -1
	=======================================================================


	==========================stack_info ���� ��Ģ==========================
	�Ű� ���� / ���� ������ push�� ���        : ������ ���� ����
	Saved Frame Pointer �� push�� ���  : � �Լ��� SFP����
	��ȯ �ּҰ��� push�� ���                 : "Return Address"
	========================================================================
*/
#include <stdio.h>
#define STACK_SIZE 50 // �ִ� ���� ũ��

int     call_stack[STACK_SIZE];         // Call Stack�� �����ϴ� �迭
char    stack_info[STACK_SIZE][20];     // Call Stack ��ҿ� ���� ������ �����ϴ� �迭

/*  SP (Stack Pointer), FP (Frame Pointer)

	SP�� ���� ������ �ֻ�� �ε����� ����ŵ�ϴ�.
	������ ������� �� SP = -1, �ϳ��� ���̸� `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

	FP�� ���� �Լ��� ���� ������ �������Դϴ�.
	���� ���� �Լ� ���� �������� sfp�� ����ŵ�ϴ�.
*/
int SP = -1;
int FP = -1;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

/*
	���� call_stack ��ü�� ����մϴ�.
	�ش� �Լ��� ��� ������� �������� ���� �ϼ����� ���� �����Դϴ�.
*/
void print_stack()
{
	if (SP == -1)
	{
		printf("Stack is empty.\n");
		return;
	}

	printf("====== Current Call Stack ======\n");

	for (int i = SP; i >= 0; i--)
	{
		if (call_stack[i] != -1)
			printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
		else
			printf("%d : %s", i, stack_info[i]);

		if (i == SP)
			printf("    <=== [esp]\n");
		else if (i == FP)
			printf("    <=== [ebp]\n");
		else
			printf("\n");
	}
	printf("================================\n\n");
}


//func ���δ� �����Ӱ� �߰��ص� ��������, �Ʒ��� ������ �ٲ����� ������
void func1(int arg1, int arg2, int arg3)
{
	int var_1 = 100;

	// func1�� ���� ������ ���� (�Լ� ���ѷα� + push)
	call_stack[0] = 3;       // �Ű����� arg1, arg2, arg3�� call_stack�� push
	snprintf(stack_info[0], sizeof(stack_info[0]), "arg3");
	call_stack[1] = 2;
	snprintf(stack_info[1], sizeof(stack_info[1]), "arg2");
	call_stack[2] = 1;
	snprintf(stack_info[2], sizeof(stack_info[2]), "arg1");
	call_stack[3] = -1;      // ��ȯ �ּҰ��� call_stack�� push
	snprintf(stack_info[3], sizeof(stack_info[3]), "Return Address");
	call_stack[4] = -1;      // SFP�� call_stack�� push
	snprintf(stack_info[4], sizeof(stack_info[4]), "func1 SFP");
	call_stack[5] = var_1;   // �������� var_1�� call_stack�� push
	snprintf(stack_info[5], sizeof(stack_info[5]), "var_1");
	SP = 5; FP = 4;          // SP�� FP ������Ʈ

	print_stack();
	func2(11, 13);
	// func2�� ���� ������ ���� (�Լ� ���ʷα� + pop)
	for (int j = SP; j > FP; j--) {      // FP���� �������� pop
		call_stack[j] = -1;
		snprintf(stack_info[j], sizeof(stack_info[j]), "");
	}
	SP = FP; FP = call_stack[FP];        // SP�� FP ������Ʈ
	call_stack[FP] = -1;               // SFP�� call_stack�� pop
	snprintf(stack_info[FP], sizeof(stack_info[FP]), "");
	call_stack[FP - 1] = -1;           // ��ȯ �ּҰ��� call_stack�� pop
	snprintf(stack_info[FP - 1], sizeof(stack_info[FP - 1]), "");
	SP = SP - 2;                         // SP ������Ʈ
	call_stack[SP] = -1;               // �Ű����� arg1, arg2�� call_stack�� pop
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = SP - 1;
	call_stack[SP] = -1;
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = SP - 1;                         // SP ������Ʈ

	print_stack();
}


void func2(int arg1, int arg2)
{
	int var_2 = 200;

	// func2�� ���� ������ ���� (�Լ� ���ѷα� + push)
	call_stack[6] = 13;       // �Ű����� arg1, arg2�� call_stack�� push
	snprintf(stack_info[6], sizeof(stack_info[6]), "arg2");
	call_stack[7] = 11;
	snprintf(stack_info[7], sizeof(stack_info[7]), "arg1");
	call_stack[8] = -1;       // ��ȯ �ּҰ��� call_stack�� push
	snprintf(stack_info[8], sizeof(stack_info[8]), "Return Address");
	call_stack[9] = 4;        // SFP�� call_stack�� push
	snprintf(stack_info[9], sizeof(stack_info[9]), "func2 SFP");
	call_stack[10] = var_2;   // �������� var_2�� call_stack�� push
	snprintf(stack_info[10], sizeof(stack_info[10]), "var_2");
	SP = 10; FP = 9;           // SP�� FP ������Ʈ

	print_stack();
	func3(77);
	// func3�� ���� ������ ���� (�Լ� ���ʷα� + pop)
	for (int j = SP; j > FP; j--) {      // FP���� �������� pop
		call_stack[j] = -1;
		snprintf(stack_info[j], sizeof(stack_info[j]), "");
	}
	SP = FP; FP = call_stack[FP];        // SP�� FP ������Ʈ
	call_stack[FP] = -1;               // SFP�� call_stack�� pop
	snprintf(stack_info[FP], sizeof(stack_info[FP]), "");
	call_stack[FP - 1] = -1;           // ��ȯ �ּҰ��� call_stack�� pop
	snprintf(stack_info[FP - 1], sizeof(stack_info[FP - 1]), "");
	SP = SP - 2;                         // SP ������Ʈ
	call_stack[SP] = -1;               // �Ű����� arg1�� call_stack�� pop
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = SP - 1;                         // SP ������Ʈ

	print_stack();
}


void func3(int arg1)
{
	int var_3 = 300;
	int var_4 = 400;

	// func3�� ���� ������ ���� (�Լ� ���ѷα� + push)
	call_stack[11] = 77;       // �Ű����� arg1�� call_stack�� push
	snprintf(stack_info[11], sizeof(stack_info[11]), "arg1");
	call_stack[12] = -1;       // ��ȯ �ּҰ��� call_stack�� push
	snprintf(stack_info[12], sizeof(stack_info[12]), "Return Address");
	call_stack[13] = 9;        // SFP�� call_stack�� push
	snprintf(stack_info[13], sizeof(stack_info[13]), "func3 SFP");
	call_stack[14] = var_3;   // �������� var_3�� call_stack�� push
	snprintf(stack_info[14], sizeof(stack_info[14]), "var_3");
	call_stack[15] = var_4;   // �������� var_4�� call_stack�� push
	snprintf(stack_info[15], sizeof(stack_info[15]), "var_4");
	SP = 15; FP = 13;          // SP�� FP ������Ʈ

	print_stack();
}


//main �Լ��� ���õ� stack frame�� �������� �ʾƵ� �˴ϴ�.
int main()
{
	func1(1, 2, 3);
	// func1�� ���� ������ ���� (�Լ� ���ʷα� + pop)
	for (int j = SP; j > FP; j--) {      // FP���� pop
		call_stack[j] = -1;
		snprintf(stack_info[j], sizeof(stack_info[j]), "");
	}
	SP = FP; FP = call_stack[FP];        // SP�� FP ������Ʈ
	call_stack[FP] = -1;               // SFP�� call_stack�� pop
	snprintf(stack_info[FP], sizeof(stack_info[FP]), "");
	call_stack[FP - 1] = -1;           // ��ȯ �ּҰ��� call_stack�� pop
	snprintf(stack_info[FP - 1], sizeof(stack_info[FP - 1]), "");
	SP = SP - 2;                         // SP ������Ʈ
	call_stack[SP] = -1;               // �Ű����� arg1, arg2, arf3�� call_stack�� pop
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = SP - 1;
	call_stack[SP] = -1;
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = SP - 1;
	call_stack[SP] = -1;
	snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
	SP = - 1;						// SP ������Ʈ
	

	print_stack();
	return 0;
}

