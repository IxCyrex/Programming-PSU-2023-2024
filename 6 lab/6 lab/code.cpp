#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;

struct spisok_soed {
	int vershina;
	struct spisok_soed* next;
};

struct spisok_head {
	int nomber;
	struct spisok_soed* head;
	struct spisok_head* next;
};

struct spisok_head* head_spisok1 = NULL, * head_spisok2 = NULL;



struct spisok_soed* creation_element(int nomber) {

	struct spisok_soed* p = NULL;

	if ((p = (spisok_soed*)malloc(sizeof(struct spisok_soed))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	p->vershina = nomber;
	p->next = NULL;

	return p;


}

struct spisok_head* creation_element_head(int nomber, int** M, int size) {

	struct  spisok_head* p = NULL;
	struct spisok_soed* q, * save = NULL;

	if ((p = (spisok_head*)malloc(sizeof(struct  spisok_head))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	p->next = NULL;
	p->nomber = nomber;
	p->head = NULL;

	for (int i = 0; i < size; i++) {
		if (M[nomber][i] == 1) {
			q = creation_element(i);
			if (p->head == NULL) {
				p->head = q;
				save = q;
			}
			else {
				save->next = q;
				save = q;
			}
		}
	}

	return p;


}

void creation_spisok(int** M, struct spisok_head* spisok, int size, struct spisok_head** head_spisok) {

	struct spisok_head* h, * save = NULL;
	for (int i = 0; i < size; i++) {
		h = creation_element_head(i, M, size);
		if ((*head_spisok) == NULL) {
			(*head_spisok) = h;
			save = h;
		}
		else {
			save->next = h;
			save = h;
		}
	}


}

void review(int size, struct spisok_head** head_spisok) {
	struct spisok_soed* save;
	struct spisok_head* save_head = (*head_spisok);
	cout << "\n";
	for (int i = 0; i < size; i++) {
		save = save_head->head;
		cout << "[" << save_head->nomber << "]";
		while (save != NULL) {
			cout << " -> " << save->vershina;
			save = save->next;
		}
		cout << "\n";
		save_head = save_head->next;
	}
	cout << "\n";

}
void output_mas(int** M, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << M[i][j] << " ";
		}
		cout << "\n";
	}
}


void input_output(int** M, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) { M[i][j] = 0; }
			else {
				M[i][j] = rand() % 2;
				M[j][i] = M[i][j];

			}
		}

	}
	output_mas(M, size);

}



int** identification(int** M, int* size, bool input) {
	int** M3, vershina1, vershina2;
	M3 = new int* [(*size) - 1]; // ������ ��������� ������ 

	for (int i = 0; i < (*size) - 1; i++) {
		M3[i] = new int[(*size) - 1];
	}

	if (input) {
		cout << "������� ������� ��� ��������������\n 1 ������� : ";
		cin >> vershina1;
		cout << " 2 ������� : ";
		cin >> vershina2;
	}
	else {
		cout << "������� ������� ����������� ����� ������� �� ������ �������\n 1 ������� : ";
		cin >> vershina1;
		cout << " 2 ������� : ";
		cin >> vershina2;
	}

	for (int i = 0; i < (*size) - 1; i++) {
		for (int j = i; j < (*size) - 1; j++) {

			if (i == min(vershina1, vershina2) && j >= max(vershina1, vershina2)) {
				M3[i][j] = (M[min(vershina1, vershina2)][j + 1] || M[max(vershina1, vershina2)][j + 1]);
				M3[j][i] = M3[i][j];
			}
			else
				if (i >= max(vershina1, vershina2) && j >= max(vershina1, vershina2)) {
					M3[i][j] = M[i + 1][j + 1];
					M3[j][i] = M3[i][j];
				}
				else if (i == min(vershina1, vershina2)) {
					M3[i][j] = (M[min(vershina1, vershina2)][j] || M[max(vershina1, vershina2)][j]);
					M3[j][i] = M3[i][j];
				}
				else if (j >= max(vershina1, vershina2)) {
					M3[i][j] = M[i][j + 1];
					M3[j][i] = M3[i][j];
				}
				else if (j == min(vershina1, vershina2)) {
					M3[i][j] = M[i][min(vershina1, vershina2)] || M[i][max(vershina1, vershina2)];
					M3[j][i] = M3[i][j];
				}
				else {
					M3[i][j] = M[i][j];
					M3[j][i] = M3[i][j];
				}
		}
	}

	output_mas(M3, (*size) - 1);
	(*size)--;
	return M3;

}

void proverka_vershin(int* vershina, int size) {
	while ((*vershina) >= size || (*vershina) < 0) {
		cout << "����� ������� ���\n ���������� ��� ���: ";
		cin >> (*vershina);
	}
}

struct spisok_head* poisk_vershini(struct spisok_head* save, int vershina) {
	while (save->nomber != vershina) {
		save = save->next;
	}
	return save;
}

void identification_spisok(struct spisok_head** head_spisok, bool input, int* size) {
	int vershina1, vershina2;
	struct spisok_head* save1 = NULL, * save2 = NULL;
	struct spisok_soed* save1_soed = NULL, * save2_soed = NULL, * save2_1_soed = NULL;
	if (input) {
		cout << "������� ������� ��� ��������������\n 1 �������: ";
		cin >> vershina1;
		proverka_vershin(&vershina1, *size);
		cout << " 2 �������: ";
		cin >> vershina2;
		proverka_vershin(&vershina2, *size);
	}
	else {
		cout << "������� ������� ����������� ����� ������� �� ������ �������\n 1 �������: ";
		cin >> vershina1;
		proverka_vershin(&vershina1, *size);
		cout << " 2 �������: ";
		cin >> vershina2;
		proverka_vershin(&vershina2, *size);
	}
	save1 = poisk_vershini(*head_spisok, vershina1);
	save2 = poisk_vershini(*head_spisok, vershina2);
	save1_soed = save1->head;
	save2_soed = save2->head;
	if (save1->head == NULL) {
		save1->head = save2->head;
	}
	else {
		while (save2_soed != NULL && save2->head != NULL) {
			save1_soed = save1->head;

			if (save2_soed != NULL && save1_soed != NULL && save1_soed->vershina > save2_soed->vershina) {
				save2_1_soed = save2_soed;
				save2_soed = save2_soed->next;
				save2_1_soed->next = save1->head;
				save1->head = save2_1_soed;
			}
			else {
				while ((save1_soed->next->vershina != save2_soed->vershina) && (save1_soed->next != NULL) && (save1_soed->next->vershina < save2_soed->vershina)) {
					save1_soed = save1_soed->next;
				}
				if (save1_soed->next->vershina == save2_soed->vershina) {
					save2_soed = save2_soed->next;
				}
				else if (save1_soed->next == NULL) {
					save2_1_soed = save2_soed;
					save2_soed = save2_soed->next;
					save1_soed->next = save2_1_soed;
					save2_1_soed->next = NULL;
				}
				else {
					save2_1_soed = save2_soed;
					save2_soed = save2_soed->next;
					save2_1_soed->next = save1_soed->next;
					save1_soed->next = save2_1_soed;

				}
			}
		}
	}

	save2 = poisk_vershini(*head_spisok, vershina2 - 1);
	save2->next = save2->next->next;
	(*size)--;


}

int** rashiplenie(int** M, int* size) {
	int** M3, vershina, colvo_connect = 0, counter = 0;
	M3 = new int* [*size + 1]; // ������ ��������� ������ 

	for (int i = 0; i < *size + 1; i++) {
		M3[i] = new int[*size + 1];
	}

	cout << "������� ������� ��� ����������� : ";
	cin >> vershina;


	for (int i = 0; i < *size; i++) {
		if (M[vershina][i] == 1) { colvo_connect++; }
	}

	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < *size; j++) {
			if (j == vershina)
			{
				if (M[i][j] == 1) {
					if (counter < (colvo_connect / 2)) {
						M3[i][j] = 1;
						M3[i][*size] = M3[*size][i] = 0;
						counter++;
					}
					else {
						M3[i][j] = 0;
						M3[i][*size] = M3[*size][i] = 1;

					}
				}
				else {
					M3[i][j] = 0;
					M3[i][*size] = M3[*size][i] = 0;
				}

			}
			else {
				M3[i][j] = M[i][j];
			}

		}
	}
	M3[vershina][*size] = M3[*size][vershina] = 1;
	M3[*size][*size] = 0;

	output_mas(M3, *size + 1);
	(*size)++;
	return M3;


}

void rashiplenie_spisok(struct spisok_head** head_spisok, int* size, int** M) {
	int vershina, colvo_reber = 0;
	struct spisok_head* save1 = NULL, * q = NULL;
	struct spisok_soed* save1_soed = NULL, * save2_soed = NULL;


	cout << "������� ������� ��� ����������� : ";
	cin >> vershina;
	proverka_vershin(&vershina, *size);

	save1 = poisk_vershini(*head_spisok, vershina);
	save1_soed = save1->head;

	while (save1_soed != NULL) {
		save1_soed = save1_soed->next;
		colvo_reber++;
	}

	save1_soed = save1->head;
	for (int i = 0; i < ((colvo_reber / 2) - 1); i++) {
		save1_soed = save1_soed->next;
	}

	save2_soed = save1_soed->next;
	save1_soed->next = NULL;

	q = creation_element_head(*size, M, 0);
	q->head = save2_soed;

	save1 = poisk_vershini(*head_spisok, (*size) - 1);
	save1->next = q;

	(*size)++;

}

void obedinen(int** M1, int** M2, int size1, int size2) {
	int** M3, size;
	size = max(size1, size2);
	M3 = new int* [size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				M3[i][j] = M3[j][i] = (M1[i][j] | M2[i][j]);
			}
			else if (size1 < size2) {
				M3[i][j] = M3[j][i] = M2[i][j];
			}
			else { M3[i][j] = M3[j][i] = M1[i][j]; }
		}
	}
	output_mas(M3, size);

}

void peresechenie(int** M1, int** M2, int size1, int size2) {
	int** M3, size;
	size = min(size1, size2);
	M3 = new int* [size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				M3[i][j] = M3[j][i] = (M1[i][j] & M2[i][j]);
			}
			else {
				M3[i][j] = M3[j][i] = 0;
			}

		}
	}
	output_mas(M3, size);

}

void circle_sum(int** M1, int** M2, int size1, int size2) {
	int** M3, size, * colvo_reber, otstup;
	size = max(size1, size2);
	M3 = new int* [size];
	colvo_reber = new int[size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
		colvo_reber[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				if (M1[i][j] == M2[i][j]) {
					M3[i][j] = M3[j][i] = 0;
				}
				else { M3[i][j] = M3[j][i] = 1; }
			}
			else if (size1 < size2) {
				M3[i][j] = M3[j][i] = M2[i][j];
			}
			else { M3[i][j] = M3[j][i] = M1[i][j]; }

		}
	}
	output_mas(M3, size);
	size1 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (M3[i][j] == 1) {
				colvo_reber[i]++;
			}
		}
		if (colvo_reber[i] > 0) {
			size1++;
		}
	}
	M1 = new int* [size1];
	for (int i = 0; i < size1; i++) {
		M1[i] = new int[size1];
	}

	for (int i = 0; i < size1; i++) {
		otstup = 0;
		for (int j = 0; j < size1; j++) {
			if (colvo_reber[j] = 0) { otstup++; }
			M1[i][j] = M3[i + otstup][j + otstup];
		}
	}
	cout << "\n";
	output_mas(M1, size1);


}
void dec(int** M1, int** M2, int size1, int size2) {
	int** M3, size = size1 * size2;

	M3 = new int* [size]; // ������ ��������� ������ 
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
	}
	int* nomera = new int[size];

	
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			nomera[j + i * size2] = (i + 1) * 10 + j + 1;
		}
	}
	
	cout <<"\n";
	for (int m = 0; m < size; m++) {
		for (int n = 0; n < size; n++) {
			M3[m][n] = 0;
		}
	}
	

	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1; j++) {
			if (M1[i][j] == 1) {
				for (int m = 0; m < size; m++) {
					for (int n = 0; n < size; n++) {
						if ((m!=n)&&(i+1==nomera[m]/10)&&(j+1==nomera[n]/10)&&(nomera[n]%10==nomera[m]%10)) {
							M3[m][n] = 1;
							}
						}
					}
				}
			}
		}

	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size2; j++) {
			if (M2[i][j] == 1) {
				for (int m = 0; m < size; m++) {
					for (int n = 0; n < size; n++) {
						if ((m != n) && (i + 1 == nomera[m] % 10) && (j + 1 == nomera[n] % 10) && (nomera[n] / 10 == nomera[m] / 10)) {
							M3[m][n] = 1;
						}
					}
				}
			}
		}
	}
		
		for (int m = 0; m < size; m++) {
			for (int n = 0; n < size; n++) {
				cout << M3[m][n];
			}
			cout << "\n";
		}
	}
	


				



int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** M1, ** M2, size1, size2, vibor1, vibor2;
	struct spisok_head* spisok1, * spisok2;
	bool uslovie = TRUE;
	cout << " ������� ��������� \n \n ������� ���������� ������ ����� �1: ";
	cin >> size1;
	cout << " ������� ���������� ������ ����� �2: ";
	cin >> size2;
	M1 = new int* [size1]; // ������ ��������� ������ 
	M2 = new int* [size2];
	spisok1 = new struct spisok_head[size1];
	spisok2 = new struct spisok_head[size2];
	for (int i = 0; i < size1; i++) {
		M1[i] = new int[size1];
	}
	for (int i = 0; i < size2; i++) {
		M2[i] = new int[size2];
	}
	cout << "M1:\n";
	input_output(M1, size1);
	//M1[0][0] = 0;
	//M1[0][1] = 1;
	//M1[0][2] = 0;
	//M1[1][0] = 1;
	//M1[1][1] = 0;
	//M1[1][2] = 1;
	//M1[2][0] = 0;
	//M1[2][1] = 1;
	//M1[2][2] = 0;
	//output_mas(M1, size1);
	cout << "\nM2:\n";
	/*M2[0][0] = 0;
	M2[0][1] = 1;
	M2[1][0] = 1;
	M2[1][1] = 0;
	output_mas(M2, size2);*/
	input_output(M2, size2);
	cout << "\n";
	cout << "�������� ��������\n 1) �������\n 2) ������\n �������� ��������: ";
	cin >> vibor2;
	switch (vibor2) {
	case(1):
		while (uslovie) {
			cout << " 1) �������������� ������\n 2) ���������� �����\n 3) ����������� �������\n 4) �����������\n 5) �����������\n 6) ��������� �����\n 7) ��������� ������������ ������\n 8) ����������\n �������� ��������: ";
			cin >> vibor1;
			switch (vibor1) {
			case(1):
				cout << "\n";
				M2 = identification(M2, &size2, TRUE);
				break;
			case(2):
				cout << "\n";
				M2 = identification(M2, &size2, FALSE);
				break;
			case(3):
				cout << "\n";
				M2 = rashiplenie(M2, &size2);
				break;
			case(4):
				cout << "\n";
				obedinen(M1, M2, size1, size2);
				break;
			case(5):
				cout << "\n";
				peresechenie(M1, M2, size1, size2);
				break;
			case(6):
				cout << "\n";
				circle_sum(M1, M2, size1, size2);
				break;
			case(7):
				dec(M1, M2, size1, size2);
				break;
			case(8):
				uslovie = FALSE;
				break;
			default:
				cout << "������";
			}
		}
		break;
	case(2):
		creation_spisok(M1, spisok1, size1, &head_spisok1);
		review(size1, &head_spisok1);

		creation_spisok(M2, spisok2, size2, &head_spisok2);
		review(size2, &head_spisok2);

		while (uslovie) {
			cout << "\n 1) �������������� ������\n 2) ���������� �����\n 3) ����������� �������\n 4) ���������\n �������� ��������: ";
			cin >> vibor1;
			switch (vibor1) {
			case(1):
				identification_spisok(&head_spisok1, TRUE, &size1);
				review(size1, &head_spisok1);
				break;
			case(2):
				identification_spisok(&head_spisok1, FALSE, &size1);
				review(size1, &head_spisok1);
				break;
			case(3):
				rashiplenie_spisok(&head_spisok1, &size1, M1);
				review(size1, &head_spisok1);
				break;
			case(4):
				uslovie = FALSE;
				break;

			default:
				cout << "������";
			}
		}
		break;

	default:
		cout << "������";



	}
	system("pause");
	return 0;
}
