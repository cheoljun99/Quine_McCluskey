#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include<string>


using namespace std;
void FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm);//����Ŭ����Ű ������� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.
int SumOfProduct(char **prr, int input, int termnumber, char** Tureminterm);//prime implicnat�� ���� sum of product�� ���ϴ� �Լ��̸� SOP�� cost�� ���� �� �ִ� �Լ��̴�. ���ڷ� prime implicant�� �����ϰ� �ִ� prr�迭�� prime implicant�� ������ termnumber����, ��ǲ�� ������ input����,Tureminterm �迭�� ���´�.  
void FindEssentialPrimeImplicant(char** prr, int input, int prime_inplicant_number, char** Tureminterm,int Tureminterm_number);//�ʼ����� ������ ã�� �Լ�
void Output_Result(char** Best_Essential_Prime_Implicant, int Best_Cost);//���� ����Ʈ �ʼ� ���װ� ����Ʈ �ڽ�Ʈ�� �޾� ���� �� cmd�� ����ϴ� �Լ�


class Best_Essential_Prime_Implicant_And_Best_Cost
{
	//���� ����ȭ�� �ʼ� ���׵�� ������ �ڽ�Ʈ�� ������ Ŭ����
public:
	char* Best_Essential_Prime_Implicant[1000];
	int Best_Cost;
	
};

void Output_Result(char** Best_Essential_Prime_Implicant, int Best_Cost)
{
	/*���� ����Ʈ �ʼ� ���װ� ����Ʈ �ڽ�Ʈ�� �޾� ���� �� cmd�� ����ϴ� �Լ�*/
	ofstream fout;//�ƿ�ǲ��Ʈ�� Ŭ���� ���� fout�� �����Ѵ�.
	fout.open("result.txt");//"result.txt"������ ����.
	if (!fout.is_open())
	{
		cout << "������ ���� ���Ͽ����ϴ�." << endl;//������ ���°Ϳ� �����Ѱ�츦 ���� ����ó��
		return;
	}
	cout << "result: ";
	cout << endl;
	for (int i = 0; *Best_Essential_Prime_Implicant[i] != '\0'; i++)
	{
		cout << Best_Essential_Prime_Implicant[i] << endl;
	}
	cout << endl << endl;
	for (int i = 0; *Best_Essential_Prime_Implicant[i] != '\0'; i++)
	{
		fout << Best_Essential_Prime_Implicant[i] << endl;
	}
	cout << "Cost (# of transistors): ";
	cout << Best_Cost << endl;
	fout << endl << endl;
	fout << "Cost (# of transistors): " << Best_Cost;
	cout << "���α׷� ���������� �۵��Ͽ����ϴ�. ��������� ����ʽÿ�." << endl;
	return;

}

void FindEssentialPrimeImplicant(char** prr, int input, int prime_inplicant_number, char** Tureminterm, int Tureminterm_number)
{
	//cout << "prime_inplicant_number : " << prime_inplicant_number << endl;
	//cout << "Tureminterm_number : " << Tureminterm_number << endl;

	
	//�ʼ����� ������ ã�� �Լ�

	Best_Essential_Prime_Implicant_And_Best_Cost Best_Boolean_Expressions;

	for (int i = 0; i < 1000; i++)
	{
		Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i] = new char[input + 1];//�����Ҵ�

	}
	Best_Boolean_Expressions.Best_Cost = 0;

	int** e_pls_arr = new int* [prime_inplicant_number]; //���� ũ�Ⱑ prime_inplicant_number�� ������ �迭
	for (int i = 0; i < prime_inplicant_number; i++) //������ �࿡ ���̰� Tureminterm_number�� ���� �Ҵ�
	{
		e_pls_arr[i] = new int[Tureminterm_number];
		memset(e_pls_arr[i], 0, sizeof(int)*Tureminterm_number);
	}
	
	//����Ŭ����Ű ����ȭ ������� ���׵�� Ʈ������� ���̺�ȭ�ϴ� ����

	for (int i = 0; *prr[i] != '\0'; i++)
	{
		for (int k = 0; *Tureminterm[k] != '\0'; k++)
		{
			int checker = 0;
		
			for (int j = 0; j < input; j++){

				if (prr[i][j] == Tureminterm[k][j]|| prr[i][j] == '_')
				{
					checker++;
				
				}
		
			}
			if (checker == input)
			{
				e_pls_arr[i][k] = 1;
			}
		}
	}

	
	// ���׵��� ������ ���� �ʼ� ������ ã�� ����
	for (int cnt = 1; cnt <= prime_inplicant_number; cnt++)
	{
		//n���� ������ k���� 1���� n���� �����ϴ� nCk�� ����� ���� �ʼ� ������ ã�� ����
		//k���� ������ Ʈ������� ���� Ŀ���ϴ� �� Ȯ�� �� Ŀ���Ѵٸ� �ڽ�Ʈ�� ���Ѵ�.
		//�ڽ�Ʈ�� ���� �ٸ� ��쵵 ���� �� �������� �̸� ����ؼ� �ڵ�

		int exit_count = 0;
		vector<int> v(prime_inplicant_number);
		for (int i = 0; i < prime_inplicant_number; i++) {
			v[i] = i;
		}
		vector<bool> visited(prime_inplicant_number, true);

		int* table_checker = new int[Tureminterm_number];
		int* table_saver = new int[cnt];
		for (int i = 0; i < v.size() - cnt; i++)
		{
			visited[i] = false;
		}

		do {
			
			memset(table_checker, 0, sizeof(int) * Tureminterm_number);
			memset(table_saver, 0, sizeof(int) * cnt);
			int table_saver_count = 0;
			

			for (int i = 0; i < v.size(); i++) {
				if (visited[i])
				{
					//cout << v[i] << " ";
			
					table_saver[table_saver_count] = v[i];
					table_saver_count++;
					for (int j = 0; j < Tureminterm_number; j++)
					{
						if (table_checker[j] != 1)
						{
							table_checker[j] = e_pls_arr[v[i]][j];
						}


					}

				}

			}
			int table_checker_count = 0;
			for (int i = 0; i < Tureminterm_number; i++)
			{
				table_checker_count += table_checker[i];
			}
			
			if (table_checker_count == Tureminterm_number)// ������ ������ Ʈ����ҵ��� Ŀ���ϴ��� Ȯ�� ���� �´ٸ� �ʼ� ���� �ĺ��� ��
			{
				exit_count = 1;
				char* essential_prime_implicant[1000];// InputMinterm�� �����ϱ� ���� char�� ������ �迭 essential_prime_implicant�� �����Ѵ�.
				for (int i = 0; i < 1000; i++)
				{
					essential_prime_implicant[i] = new char[input + 1];//�����Ҵ�

				}
				for (int i = 0; i < cnt; i++)//�迭 essential_prime_implicant�� InputMinterm�� �����Ѵ� .
				{
					strcpy(essential_prime_implicant[i],prr[table_saver[i]]);
					*essential_prime_implicant[i + 1] = 0;
				}
				int SumOfProduct_Checker = 0;
				
				SumOfProduct_Checker =SumOfProduct(essential_prime_implicant, input, cnt, Tureminterm);//�ڽ�Ʈ�� ���ϴ� �Լ� ȣ��

				if (Best_Boolean_Expressions.Best_Cost == 0)//�ʱ⿡�� �ڽ�Ʈ�� 0�̱� ������ ����
				{
					Best_Boolean_Expressions.Best_Cost = SumOfProduct_Checker;

					for (int i = 0;  i<cnt; i++)//�迭 prr�� InputMinterm�� �����Ѵ� .
					{
						strcpy(Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i],essential_prime_implicant[i]);
						*Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i + 1] = 0;
					}
					

				}
				else if (Best_Boolean_Expressions.Best_Cost >= SumOfProduct_Checker)// ������ �ڽ�Ʈ�� ������ ������ �ִ� ����Ʈ �ڽ�Ʈ ���� ���� ��� ����Ʈ �ڽ�Ʈ �� ����Ʈ �ʼ� ���� ����
				{
					Best_Boolean_Expressions.Best_Cost = SumOfProduct_Checker;

					for (int i = 0; i < cnt; i++)//�迭 prr�� InputMinterm�� �����Ѵ� .
					{
						strcpy(Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i], essential_prime_implicant[i]);
						*Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i + 1] = 0;

					}
				}

				for (int i = 0; i < 1000; i++)
				{
					delete[] essential_prime_implicant[i]; //�����Ҵ�����
				}
			}
			//puts("");
		} while (next_permutation(visited.begin(), visited.end()));
		
		delete[] table_checker;//�����Ҵ� ����
		delete[] table_saver;//�����Ҵ� ����
		if (exit_count == 1)
		{
			//���� ��� 4C2���� �ʼ������� �ĺ��� �߰��ߴٸ� 4C3,4C4�� �ڽ�Ʈ�� ������ ���� ���� ������ �� �ʿ䰡 ����. �׷��Ƿ� nCk���� k���� ������Ű�� for�� ����
			break;
		}
		
	}
	
	Output_Result(Best_Boolean_Expressions.Best_Essential_Prime_Implicant, Best_Boolean_Expressions.Best_Cost);//��� ���� �� cmd ���

	for (int i = 0; i < 1000; i++)
	{
		delete[] Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i];//�����Ҵ�����
		delete[] prr[i];//�����Ҵ�����
		delete[] Tureminterm[i];//�����Ҵ�����

	}
	for (int i = 0; i < prime_inplicant_number; i++) //������ �࿡ ���̰� Tureminterm_number�� ���� �Ҵ�
	{
		delete[] e_pls_arr[i];//�����Ҵ�����
	}
	delete[] e_pls_arr;//�����Ҵ�����
	return;
}

int SumOfProduct(char** essential_prime_implicant , int input, int termnumber, char** Tureminterm)
{
	
	/*�Ʒ��� SOP�� cost�� ����ϴ� �����̴�.*/

	int* cost_table = new int [input]; 
	//���� ũ�Ⱑ prime_inplicant_number�� ������ �迭 
	memset(cost_table, -1, sizeof(int)*input);
	//�迭�� �����ϴ� ������ input�� ��� ��ġ�� not���� �� �ȴٸ� �� ��ġ�� �����Ͽ� �ٸ� �ʼ����׿��� ���� ��ġ�� not���� ����ϰ��� �Ҷ� ������ ����� not�� ���� Ʈ�������͸� ����Ͽ� �ڽ�Ʈ ���� ���� �� ����

	/*
	for (int j = 0; j < input; j++)
	{
		cout << cost_table[j] << " ";
	}
	cout << endl;
	*/

	int cost = 0;
	for (int i = 0; i < termnumber; i++)
	{
		int inputnumber = 0;
		int inputposition = 0;
		for (int j = 0; j < input; j++)
		{

			if (essential_prime_implicant[i][j] != '_'&& essential_prime_implicant[i][j] == '0')/*�Է¿� 0�־� �������� �Է����� ���� �ι���(Ʈ��������2��)�� �߰����־���Ѵ�.*/
			{
				if (cost_table[j] == -1)
				{
					cost += 2;
					inputnumber++;
					cost_table[j] = 0;
				}
				else
				{
					inputnumber++;
				}
			}
			else if (essential_prime_implicant[i][j] != '_'&& essential_prime_implicant[i][j] == '1')
			{
				inputnumber++;
				inputposition = j;
			}
		}
		if (inputnumber > 1)
		{
			cost += (inputnumber * 2);/*NAND����Ʈ�� ��ǲ�� ������ �ι�� Ʈ���������� ����(������� 2��ǲ�� ��� Ʈ�������� 4�� 3��ǲ�ΰ�� Ʈ�������� 6��)�� �þ���� cost += (inputnumber * 2)������ ��ģ��.*/
		}
		if (inputnumber > 1)
		{
			cost += 2;//�츮�� ���ϰ����ϴ� ���� AND����Ʈ������ NOT����Ʈ(Ʈ��������2��)�� �߰��Ͽ����Ѵ�.
		}
	}
	if (termnumber > 1)
	{
		cost += (termnumber * 2);/*������ ���ø���Ʈ�� ������ OR����Ʈ�� ��ǲ�� ������ ������ ��ǲ�� ������ �ι�� Ʈ���������� ����(������� 2��ǲ�� ��� Ʈ�������� 4�� 3��ǲ�ΰ�� Ʈ�������� 6��)�� �þ��
		��� cost += (termnumber * 2);�� ����Ѵ�.*/
	}

	if (termnumber > 1)
	{
		cost += 2;//�츮�� ���ϰ����ϴ� ���� OR����Ʈ������ NOT����Ʈ(Ʈ��������2��)�� �߰��Ͽ����Ѵ�.
	};
	delete [] cost_table;//�����Ҵ� ����
	return cost;

}

void FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm)//����Ŭ����Ű �����Ŀ��� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.
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
		strcpy(prr[i],InputMinterm[i]);
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
			strcpy(rest[L],InputMinterm[i]);//�عֵ��Ͻ��� 1�� ���ڿ��� ã�����Ѱ�� ����� �Ǵ� ���ڿ��� rest�迭�� �ֽ��ϴ�.
			L++;

		}
	}
	if (s == 0)//�ƹ��͵� �عֵ��Ͻ����̰� 1�� ��찡 ���°�� �׹迭�� �ִ� ���ڿ����� prime inplicant�Դϴ� ��� FindPrimeImplicant �Լ��� �����ŵ�ϴ�.
			   //�����Ű�鼭 SumOfProduct�Լ��� �����ŵ�ϴ�.
	{
		int Tureminterm_number = 0;
		for (int i = 0; *Tureminterm[i] != '\0'; i++)
		{
			/*InputMinterm[i] != '\0'�϶����� termnumber�� ���� ���������ش�. */
			Tureminterm_number = i + 1;
		}

		for (int i = 0; i < 1000; i++)
		{
			delete[] crr[i];//�����Ҵ�����
			delete[] rest[i];//�����Ҵ�����
			delete[] InputMinterm[i];//�����Ҵ�����
		}
		FindEssentialPrimeImplicant(prr, input, termnumber, Tureminterm, Tureminterm_number);//�ʼ� ����ã�� ����
		return ;

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
	if (s != 0)
	{
		/*�ع� ���Ͻ��� 1�� ��찡�ִ� ��� (������ ���ø���Ʈ�鸸 �ִ� ���ڿ��� �� ã�� ���) or prime implicant�� ��ã�� ��� �ݺ��ؼ� FindPrimeImplicant�� �����ŵ�ϴ�.*/
		FindPrimeImplicant(rest, input, Tureminterm);
	}

}
int main()
{
	char *InputLine[1000];//���Ͽ��� ��ǲ ������ �Է¹��� ���ڿ��� �����Ҽ��ִ� char�� ������ �迭�� �����մϴ�.
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
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//����
			delete[] Tureminterm[i];//����
		}
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
	
	
	input = atoi(InputLine[0]);//char �� ������ �迭 InputLine�� ù��° ���� ��ǲ�� ���� �Դϴ�.

	if (input == -48)
	{
		cout << "input�� ������ �Է����� �����̽��ϴ�." << endl;//ù��°���� ����־� ��ǲ�� ������ �� �� ���� �� ����Ǵ� ����ó���Դϴ�.
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//����
			delete[] Tureminterm[i];//����
		}
		return 0;
	}

	if (InputLine[1][input + 2] != '\0')
	{
		cout << "�Է������� ������ �ùٸ��� �ʽ��ϴ�. �����Ͻʽÿ�" << endl;
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//����
			delete[] Tureminterm[i];//����
		}
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
	if (v == 0)
	{
		cout << "TrueMinterm�� �������� �ʽ��ϴ�." << endl;
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//����
			delete[] Tureminterm[i];//����
			delete[] InputMinterm[i];//����
		}
		return 0;

	}
	
	FindPrimeImplicant(InputMinterm, input, Tureminterm);//����Ŭ����Ű �����Ŀ��� prime Implicant�� ã�� �Լ��̸� ���ڷδ� InputMinterm �迭��, input�� ����, Tureminterm �迭�� ���´�.


	for (int i = 0; i < 1000; i++)
	{
		delete[] InputLine[i];//����
	}

	return 0;

}