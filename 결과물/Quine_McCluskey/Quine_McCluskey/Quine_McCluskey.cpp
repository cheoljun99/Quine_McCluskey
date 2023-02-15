#include<iostream>
#include<fstream>
using namespace std;
int FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm);//����Ŭ����Ű ������� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.
int SumOfProduct(char **prr, int input, int termnumber);//prime implicnat�� ���� sum of product�� ���ϴ� �Լ��̸� SOP�� cost�� ���� �� �ִ� �Լ��̴�. ���ڷ� prime implicant�� �����ϰ� �ִ� prr�迭�� prime implicant�� ������ termnumber����, ��ǲ�� ������ input����,Tureminterm �迭�� ���´�.  

int SumOfProduct(char **prr, int input, int termnumber)
{
	/*��� prime implicant�� ������ SOP�� ����� ���� �ƴ϶� �ʼ�����ã�� �ʼ����װ� �Բ� �ʼ� ������ Ŀ������ ���ϴ� ���ø���Ʈ�� �����ϴ� prime implicant�� ����
	SOP�� �����ؾ��Ѵ�. ������ �����α׷��� �ʼ������� ã�� �˰����� �������� ���Ͽ��� ������ ������ prime implicant���� ������ SOP�� �����Ͽ���. */
	/*�̴� �����α׷��� �������̸� �ּ��ϵ� SOP�� cost�� ������ ���� ���ɼ��� �ִ�.*/
	ofstream fout;//�ƿ�ǲ��Ʈ�� Ŭ���� ���� fout�� �����Ѵ�.
	fout.open("result.txt");//"result.txt"������ ����.
	if (!fout.is_open())
	{
		cout << "������ ���� ���Ͽ����ϴ�." << endl;//������ ���°Ϳ� �����Ѱ�츦 ���� ����ó��
		return 0;
	}
	cout << "result: ";
	cout << endl;
	for (int i = 0; *prr[i] != '\0'; i++)
	{
		cout << prr[i] << endl;
	}
	cout << endl << endl << endl;
	for (int i = 0; *prr[i] != '\0'; i++)
	{
		fout << prr[i] << endl;
	}
	/*�Ʒ��� SOP�� cost�� ����ϴ� �����̴�.*/
	int cost = 0;
	for (int i = 0; i < termnumber; i++)
	{
		int inputnumber = 0;
		int inputposition = 0;
		for (int j = 0; j < input; j++)
		{

			if (prr[i][j] != '_'&&prr[i][j] == '0')/*�Է¿� 0�־� �������� �Է����� ����
												   �ι���(Ʈ��������2��)�� �߰����־���Ѵ�.*/
			{
				cost += 2;
				inputnumber++;
			}
			else if (prr[i][j] != '_'&&prr[i][j] == '1')
			{

				inputnumber++;
				inputposition = j;
			}

		}
		if (inputnumber > 1)
		{
			cost += (inputnumber * 2);/*NAND����Ʈ�� ��ǲ�� ������ �ι��
									  Ʈ���������� ����(������� 2��ǲ�� ��� Ʈ�������� 4�� 3��ǲ�ΰ�� Ʈ�������� 6��)�� �þ����
									   cost += (inputnumber * 2)������ ��ģ��.*/
		}
		if (inputnumber > 1)
		{
			cost += 2;//�츮�� ���ϰ����ϴ� ���� AND����Ʈ������ NOT����Ʈ(Ʈ��������2��)�� �߰��Ͽ����Ѵ�.
		}

	}
	if (termnumber > 1)
	{
		cost += (termnumber * 2);/*������ ���ø���Ʈ�� ������ OR����Ʈ�� ��ǲ�� ������ ������ ��ǲ�� ������ �ι��
									Ʈ���������� ����(������� 2��ǲ�� ��� Ʈ�������� 4�� 3��ǲ�ΰ�� Ʈ�������� 6��)�� �þ�� ��� cost += (termnumber * 2);�� ����Ѵ�.*/
	}

	if (termnumber > 1)
	{
		cost += 2;//�츮�� ���ϰ����ϴ� ���� OR����Ʈ������ NOT����Ʈ(Ʈ��������2��)�� �߰��Ͽ����Ѵ�.
	}
	cout << "Cost (# of transistors): ";
	cout << cost << endl;
	fout << endl << endl << endl;
	fout << "Cost (# of transistors): " << cost;
}
int FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm)//����Ŭ����Ű �����Ŀ��� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.
{
	int termnumber = 0;//�Լ��� ���������� �����ų ���ε� �׶����� implicant�� ���� ������ �����ִ� �����̴�.
	for (int i = 0; *InputMinterm[i] != '\0'; i++)
	{
		/*InputMinterm[i] != '\0'�϶����� termnumber�� ���� ���������ش�. */
		termnumber = i + 1;
	}
	char * prr[1000];// InputMinterm�� �����ϱ� ���� char�� ������ �迭 prr�� �����Ѵ�.
	for (int i = 0; i < 1000; i++)
	{
		prr[i] = new char[input + 1];//�����Ҵ�

	}
	for (int i = 0; *InputMinterm[i] != '\0'; i++)//�迭 prr�� InputMinterm�� �����Ѵ� .
	{
		prr[i] = InputMinterm[i];

		*prr[i + 1] = 0;



	}

	char * crr[1000];//�عֵ��Ͻ��� 1���̳��� ���ڿ��� ���Ͽ� ���Ͻ��� 1���̳��� �κ��� ������ �����ϱ����� �迭�� �����Ѵ�.
	for (int i = 0; i < 1000; i++)
	{
		crr[i] = new char[input + 1];//�����Ҵ�

	}
	char * rest[1000];//�عֵ��Ͻ��� 1���̳��� ���ڿ��� ���� �� ������ ������ ���ø���Ʈ�� �عֵ��Ͻ��� 1���̳��� �κ��� ���� ���ڿ��� �����ϱ����� �迭�� �����Ѵ�. 
	for (int i = 0; i < 1000; i++)
	{
		rest[i] = new char[input + 1];

	}
	int c = 0;
	int L = 0;
	int s = 0;
	for (int i = 0; i < termnumber; i++)
	{
		int x = 0;
		for (int j = 0; j < termnumber; j++)
		{

			int a = 0;
			int u = 0;
			for (int k = 0; k < input; k++)
			{


				if (InputMinterm[i][k] != InputMinterm[j][k])
				{
					a++; //�عֵ��Ͻ����̸� Ȯ���ϰ� ���� for���� �����մϴ�.
						//�عֵ��Ͻ����̸� �����մϴ�.
					u = k;//���̳ʸ� �ѹ��� �ٸ� ��ġ�� �ľ��ϱ����� �����Դϴ�.
				}

			}
			if (a == 1)//�عֵ��Ͻ��� 1�ΰ�쿡 �Ʒ��� �����մϴ�.
			{
				int y = i;
				s++;
				for (int i = 0; i < input; i++)
				{
					if (i == u)//���̳ʸ� �ѹ��� ���� �ٸ� ��ġ�� ������.
					{
						//'_'�� ä���ֽ��ϴ�.
						crr[c][i] = '_';
						crr[c][i + 1] = '\0';
						*crr[c + 1] = NULL;
					}
					else
					{
						//���̳ʸ� �ѹ��� ���� ���� ��� ���� ���� ����ֽ��ϴ�.
						crr[c][i] = InputMinterm[y][i];
						crr[c][i + 1] = '\0';
						*crr[c + 1] = NULL;
					}


				}
				c++;
				x++;
			}

		}
		if (x == 0)
		{
			rest[L] = InputMinterm[i];//�عֵ��Ͻ��� 1�� ���ڿ��� ã�����Ѱ�� ����� �Ǵ� ���ڿ��� rest�迭�� �ֽ��ϴ�.
			L++;

		}
	}
	if (s == 0)//�ƹ��͵� �عֵ��Ͻ����̰� 1�� ��찡 ���°�� �׹迭�� �ִ� ���ڿ����� prime inplicant�Դϴ� ��� FindPrimeImplicant �Լ��� �����ŵ�ϴ�.
			   //�����Ű�鼭 SumOfProduct�Լ��� �����ŵ�ϴ�.
	{

		SumOfProduct(prr, input, termnumber);
		return 0;
	}
	for (int i = 0; *crr[i] != NULL; i++)//crr �迭�� �ִ� ���ڿ� �߿��� �ߺ��Ǵ� ���� ���� ���� �ֱ� ������ �����ִ� �����Դϴ�.
	{
		for (int j = 0; *crr[j] != NULL; j++)
		{
			if ((!strcmp(crr[i], crr[j])) && i != j && crr[i] != "@@@"&&crr[j] != "@@@")
			{
				/*when we found duplicate words we change that word to "@@@" */
				strcpy(crr[j], "@@@");
			}

		}
	}

	int ip = L;
	int pa = L;
	/*�Ʒ��� ������ �ߺ��� ������ crr�� �ִ� ���ڿ����� rest �迭�� ���� rest�ִ� ������ ���ø���Ʈ�� ���� �����ϴ� �����Դϴ�.*/
	while (*crr[pa - L] != NULL)
	{
		if ((strcmp(crr[pa - L], "@@@")))
		{
			rest[ip] = crr[pa - L];
			*rest[ip + 1] = 0;
			ip++;
			pa++;
		}
		else
		{
			pa++;
		}
	}

	if (s != 0)/*�ع� ���Ͻ��� 1�� ��찡�ִ� ��� (������ ���ø���Ʈ�鸸 �ִ� ���ڿ��� �� ã�� ���)
				prime implicant�� ��ã�� ��� �ݺ��ؼ� FindPrimeImplicant�� �����ŵ�ϴ�.
				�� return 0�� main�Լ��� ���α׷��� �����Ű������ return 0�� �������� �� �Դϴ�.*/
	{
		FindPrimeImplicant(rest, input, Tureminterm);
	}

}
int main()
{
	char *InputLine[1000];//���Ͽ��� ������ �Է¹��� ���ڿ��� �����Ҽ��ִ� char�� ������ �迭�� �����մϴ�.
	for (int i = 0; i < 1000; i++)
	{
		InputLine[i] = new char[10000];//���ڿ��� �ޱ����� �����Ҵ��մϴ�.
	}
	char *Tureminterm[1000];//���ɾ� ������ ������ Ʈ�� �������ޱ����� char�� ������ �迭�� �����մϴ�.
	for (int i = 0; i < 1000; i++)
	{
		Tureminterm[i] = new char[10000];//���ڿ��� �ޱ����� �����Ҵ��մϴ�.
	}
	char count[1000];
	ifstream fin;//�����Է� Ŭ������ fin�� �����մϴ�.
	fin.open("input_minterm.txt");//open input_minterm.txt file
	if (!fin.is_open())
	{
		cout << "������ ���� ���Ͽ����ϴ�." << endl;//������ ���� ���� �����Ѱ�� ����Ǵ� ����ó�� �Դϴ�.
		return 0;
	}
	int i = 0;
	int input = 0;
	while (!fin.eof())//���Ͽ��� ������ ������ ���྿ �Է¹޾� char �� ������ �迭 InputLine�� �����մϴ�.
	{
		fin.getline(InputLine[i], 10000);
		*InputLine[i + 1] = 0;
		i++;


	}
	input = InputLine[0][0] - '0';//char �� ������ �迭 InputLine�� ù��° ���� ��ǲ�� ���� �Դϴ�.
	if (input == -48)
	{
		cout << "input�� ������ �Է����� �����̽��ϴ�." << endl;//ù��°���� ����־� ��ǲ�� ������ �� �� ���� �� ����Ǵ� ����ó���Դϴ�.
		return 0;
	}
	if (InputLine[1][input + 2] != '\0')
	{
		cout << "�Է������� ������ �ùٸ��� �ʽ��ϴ�. �����Ͻʽÿ�" << endl;
		return 0;
	}

	int v = 0;
	for (int i = 0; *InputLine[i] != 0; i++)/* InputLine�� [0]�� ��������� ���ɾ Ʈ�� �����̰� �Է¹��� ���ڿ��� ���� ��� d 0000�� ������ ������ �� �����
											   ���Ǹ� ���� dȤ��m�� ���� �����ϳ��� ����ϴ�.*/
	{
		if (InputLine[i][0] == 'm')
		{
			for (int j = 0; j <= input + 1; j++)
			{
				Tureminterm[v][j] = InputLine[i][j + 2];
				*Tureminterm[v + 1] = 0;

			}
			v++;
		}
	}
	int j = 1;
	int termnumber = 0;
	while (InputLine[j][0] == 'd' || InputLine[j][0] == 'm')//* ���������� true������ ������ TrueMinterm���� ���� d�� ���� �����ϳ��� ����ϴ�.
	{
		for (int i = 0; i <= input + 1; i++)
		{
			InputLine[j][i] = InputLine[j][i + 2];

		}
		termnumber = j;
		j++;
	}

	char * InputMinterm[1000];//Inputline �迭�� ù��°���� ��ǲ�� �����Դϴ�. �׷��� ���� ���Ǹ� ���� ��ǲ�� ������ �����Ͽ� ������ ���ڿ��� ������ �迭�� �ٽü����մϴ�.
	for (int i = 0; i < 1000; i++)
	{
		InputMinterm[i] = new char[input + 1];//�����Ҵ�

	}
	for (int i = 0; i < termnumber; i++)
	{
		for (int j = 0; j < input + 1; j++)
		{
			/*InputLine�� ù��° ��(��ǲ�� ����)�� ������ ��� Ʈ����� Ȥ�� ���ɾ� ������ InputMinterm�� �����մϴ�.*/
			InputMinterm[i][j] = InputLine[i + 1][j];
			*InputMinterm[i + 1] = 0;
		}
	}
	if (FindPrimeImplicant(InputMinterm, input, Tureminterm) == 0)//����Ŭ����Ű �����Ŀ��� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.
																//�Լ��� 0�� ��ȯ�ϸ� ���α׷��� �����Ѵ�.
	{
		cout << "���α׷� ���������� �۵��Ͽ����ϴ�. ��������� ����ʽÿ�." << endl;
		return 0;
	}

}