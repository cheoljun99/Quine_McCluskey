#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include<string>


using namespace std;
void FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm);//퀸맥클러스키 방법에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 갖는다.
int SumOfProduct(char **prr, int input, int termnumber, char** Tureminterm);//prime implicnat를 통해 sum of product를 구하는 함수이며 SOP의 cost를 구할 수 있는 함수이다. 인자로 prime implicant를 저장하고 있는 prr배열과 prime implicant의 갯수인 termnumber변수, 인풋의 갯수인 input변수,Tureminterm 배열를 갖는다.  
void FindEssentialPrimeImplicant(char** prr, int input, int prime_inplicant_number, char** Tureminterm,int Tureminterm_number);//필수주항 조합을 찾는 함수
void Output_Result(char** Best_Essential_Prime_Implicant, int Best_Cost);//가장 베스트 필수 주항과 베스트 코스트를 받아 파일 및 cmd에 출력하는 함수


class Best_Essential_Prime_Implicant_And_Best_Cost
{
	//가장 최적화된 필수 주항들과 최적의 코스트를 저장할 클래스
public:
	char* Best_Essential_Prime_Implicant[1000];
	int Best_Cost;
	
};

void Output_Result(char** Best_Essential_Prime_Implicant, int Best_Cost)
{
	/*가장 베스트 필수 주항과 베스트 코스트를 받아 파일 및 cmd에 출력하는 함수*/
	ofstream fout;//아웃풋스트림 클래스 변수 fout을 선언한다.
	fout.open("result.txt");//"result.txt"파일을 연다.
	if (!fout.is_open())
	{
		cout << "파일을 열지 못하였습니다." << endl;//파일을 여는것에 실패한경우를 위한 예외처리
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
	cout << "프로그램 성공적으로 작동하였습니다. 결과파일을 열어보십시오." << endl;
	return;

}

void FindEssentialPrimeImplicant(char** prr, int input, int prime_inplicant_number, char** Tureminterm, int Tureminterm_number)
{
	//cout << "prime_inplicant_number : " << prime_inplicant_number << endl;
	//cout << "Tureminterm_number : " << Tureminterm_number << endl;

	
	//필수주항 조합을 찾는 함수

	Best_Essential_Prime_Implicant_And_Best_Cost Best_Boolean_Expressions;

	for (int i = 0; i < 1000; i++)
	{
		Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i] = new char[input + 1];//동적할당

	}
	Best_Boolean_Expressions.Best_Cost = 0;

	int** e_pls_arr = new int* [prime_inplicant_number]; //행의 크기가 prime_inplicant_number인 이차원 배열
	for (int i = 0; i < prime_inplicant_number; i++) //각각의 행에 길이가 Tureminterm_number인 열을 할당
	{
		e_pls_arr[i] = new int[Tureminterm_number];
		memset(e_pls_arr[i], 0, sizeof(int)*Tureminterm_number);
	}
	
	//퀸맥클러스키 간소화 방법에서 주항들과 트루민텀을 테이블화하는 과정

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

	
	// 주항들의 조합을 통해 필수 주항을 찾는 과정
	for (int cnt = 1; cnt <= prime_inplicant_number; cnt++)
	{
		//n개의 주항중 k개를 1부터 n까지 조합하는 nCk의 방법을 통해 필수 주항을 찾는 과정
		//k개의 조합이 트루민텀을 전부 커버하는 지 확인 후 커버한다면 코스트를 구한다.
		//코스트가 낮은 다른 경우도 있을 수 있음으로 이를 고려해서 코딩

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
			
			if (table_checker_count == Tureminterm_number)// 조합한 주항이 트루민텀들을 커버하는지 확인 만약 맞다면 필수 주항 후보가 됨
			{
				exit_count = 1;
				char* essential_prime_implicant[1000];// InputMinterm을 저장하기 위한 char형 포인터 배열 essential_prime_implicant을 선언한다.
				for (int i = 0; i < 1000; i++)
				{
					essential_prime_implicant[i] = new char[input + 1];//동적할당

				}
				for (int i = 0; i < cnt; i++)//배열 essential_prime_implicant에 InputMinterm을 저장한다 .
				{
					strcpy(essential_prime_implicant[i],prr[table_saver[i]]);
					*essential_prime_implicant[i + 1] = 0;
				}
				int SumOfProduct_Checker = 0;
				
				SumOfProduct_Checker =SumOfProduct(essential_prime_implicant, input, cnt, Tureminterm);//코스트를 구하는 함수 호출

				if (Best_Boolean_Expressions.Best_Cost == 0)//초기에는 코스트가 0이기 때문에 저장
				{
					Best_Boolean_Expressions.Best_Cost = SumOfProduct_Checker;

					for (int i = 0;  i<cnt; i++)//배열 prr에 InputMinterm을 저장한다 .
					{
						strcpy(Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i],essential_prime_implicant[i]);
						*Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i + 1] = 0;
					}
					

				}
				else if (Best_Boolean_Expressions.Best_Cost >= SumOfProduct_Checker)// 조합의 코스트가 기존에 가지고 있던 베스트 코스트 보다 작은 경우 베스트 코스트 및 베스트 필수 주항 변경
				{
					Best_Boolean_Expressions.Best_Cost = SumOfProduct_Checker;

					for (int i = 0; i < cnt; i++)//배열 prr에 InputMinterm을 저장한다 .
					{
						strcpy(Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i], essential_prime_implicant[i]);
						*Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i + 1] = 0;

					}
				}

				for (int i = 0; i < 1000; i++)
				{
					delete[] essential_prime_implicant[i]; //동적할당해제
				}
			}
			//puts("");
		} while (next_permutation(visited.begin(), visited.end()));
		
		delete[] table_checker;//동적할당 해제
		delete[] table_saver;//동적할당 해제
		if (exit_count == 1)
		{
			//예를 들어 4C2에서 필수주항의 후보를 발견했다면 4C3,4C4는 코스트가 무조건 많아 지기 때문에 볼 필요가 없다. 그러므로 nCk에서 k개를 증가시키는 for문 종료
			break;
		}
		
	}
	
	Output_Result(Best_Boolean_Expressions.Best_Essential_Prime_Implicant, Best_Boolean_Expressions.Best_Cost);//결과 파일 및 cmd 출력

	for (int i = 0; i < 1000; i++)
	{
		delete[] Best_Boolean_Expressions.Best_Essential_Prime_Implicant[i];//동적할당해제
		delete[] prr[i];//동적할당해제
		delete[] Tureminterm[i];//동적할당해제

	}
	for (int i = 0; i < prime_inplicant_number; i++) //각각의 행에 길이가 Tureminterm_number인 열을 할당
	{
		delete[] e_pls_arr[i];//동적할당해제
	}
	delete[] e_pls_arr;//동적할당해제
	return;
}

int SumOfProduct(char** essential_prime_implicant , int input, int termnumber, char** Tureminterm)
{
	
	/*아래는 SOP의 cost를 계산하는 과정이다.*/

	int* cost_table = new int [input]; 
	//행의 크기가 prime_inplicant_number인 일차원 배열 
	memset(cost_table, -1, sizeof(int)*input);
	//배열을 선언하는 이유는 input의 어떠한 위치에 not값이 들어가 된다면 그 위치를 저장하여 다른 필수주항에서 같은 위치에 not값을 사용하고자 할때 기존에 사용한 not에 대한 트랜지스터를 사용하여 코스트 낭비를 막을 수 있음

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

			if (essential_prime_implicant[i][j] != '_'&& essential_prime_implicant[i][j] == '0')/*입력에 0있어 부정값이 입력으로 들어가면 인버터(트랜지스터2개)를 추가해주어야한다.*/
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
			cost += (inputnumber * 2);/*NAND게이트의 인풋의 갯수에 두배로 트렌지스터의 개수(예를들어 2인풋인 경우 트랜지스터 4개 3인풋인경우 트랜지스터 6개)가 늘어남으로 cost += (inputnumber * 2)과정을 거친다.*/
		}
		if (inputnumber > 1)
		{
			cost += 2;//우리가 구하고자하는 것은 AND게이트임으로 NOT게이트(트랜지스터2개)를 추가하여야한다.
		}
	}
	if (termnumber > 1)
	{
		cost += (termnumber * 2);/*프라임 임플리컨트의 갯수가 OR게이트의 인풋의 갯수가 됨으로 인풋의 갯수에 두배로 트렌지스터의 개수(예를들어 2인풋인 경우 트랜지스터 4개 3인풋인경우 트랜지스터 6개)가 늘어난다
		고로 cost += (termnumber * 2);을 계산한다.*/
	}

	if (termnumber > 1)
	{
		cost += 2;//우리가 구하고자하는 것은 OR게이트임으로 NOT게이트(트랜지스터2개)를 추가하여야한다.
	};
	delete [] cost_table;//동적할당 해제
	return cost;

}

void FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm)//퀸맥클러스키 방정식에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 같는다.
{
	
	int termnumber = 0;//함수를 연속적으로 실행시킬 것인데 그때마다 implicant의 항의 개수를 세어주는 변수이다.
	for (int i = 0; *InputMinterm[i] != '\0'; i++)
	{
		/*InputMinterm[i] != '\0'일때까지 termnumber의 수를 증가시켜준다. */
		termnumber = i + 1;
	}
	char * prr[1000];// InputMinterm을 저장하기 위한 char형 포인터 배열 prr을 선언한다.
	for (int i = 0; i < 1000; i++)
	{
		prr[i] = new char[input + 1];//동적할당

	}
	for (int i = 0; *InputMinterm[i] != '\0'; i++)//배열 prr에 InputMinterm을 저장한다 .
	{
		strcpy(prr[i],InputMinterm[i]);
		*prr[i + 1] = 0;

	}
	char * crr[1000];//해밍디스턴스가 1차이나는 문자열을 비교하여 디스턴스가 1차이나는 부분을 지워서 저장하기위한 배열을 선언한다.
	for (int i = 0; i < 1000; i++)
	{
		crr[i] = new char[input + 1];//동적할당

	}
	char * rest[1000];//해밍디스턴스가 1차이나는 문자열이 없을 때 나오는 프라임 임플리컨트와 해밍디스턴스가 1차이나는 부분을 지운 문자열을 저장하기위한 배열을 선언한다. 
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
					a++; //해밍디스턴스차이를 확인하고 위한 for문을 선언합니다.
						//해밍디스턴스차이를 저장합니다.
					u = k;//바이너리 넘버가 다른 위치를 파악하기위한 변수입니다.
				}

			}
			if (a == 1)//해밍디스턴스가 1인경우에 아래를 실행합니다.
			{
				int y = i;
				s++;
				for (int i = 0; i < input; i++)
				{
					if (i == u)//바이너리 넘버가 서로 다른 위치에 있을때.
					{
						//'_'을 채워넣습니다.
						crr[c][i] = '_';
						crr[c][i + 1] = '\0';
						*crr[c + 1] = NULL;
					}
					else
					{
						//바이너리 넘버가 서로 같은 경우 같은 수를 집어넣습니다.
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
			strcpy(rest[L],InputMinterm[i]);//해밍디스턴스가 1인 문자열을 찾지못한경우 대상이 되는 문자열을 rest배열에 넣습니다.
			L++;

		}
	}
	if (s == 0)//아무것도 해밍디스턴스차이가 1인 경우가 없는경우 그배열에 있는 문자열들은 prime inplicant입니다 고로 FindPrimeImplicant 함수를 종료시킵니다.
			   //종료시키면서 SumOfProduct함수를 실행시킵니다.
	{
		int Tureminterm_number = 0;
		for (int i = 0; *Tureminterm[i] != '\0'; i++)
		{
			/*InputMinterm[i] != '\0'일때까지 termnumber의 수를 증가시켜준다. */
			Tureminterm_number = i + 1;
		}

		for (int i = 0; i < 1000; i++)
		{
			delete[] crr[i];//동적할당해제
			delete[] rest[i];//동적할당해제
			delete[] InputMinterm[i];//동적할당해제
		}
		FindEssentialPrimeImplicant(prr, input, termnumber, Tureminterm, Tureminterm_number);//필수 주항찾기 시작
		return ;

	}
	for (int i = 0; *crr[i] != NULL; i++)//crr 배열에 있는 문자열 중에서 중복되는 것이 있을 수도 있기 때문에 지워주는 과정입니다.
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
	/*아래의 과정은 중복을 제거한 crr의 있는 문자열들을 rest 배열에 합쳐 rest있던 프라임 임플리컨트와 같이 나열하는 과정입니다.*/
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
		/*해밍 디스턴스가 1인 경우가있는 경우 (프라임 임플리컨트들만 있는 문자열을 못 찾은 경우) or prime implicant를 못찾은 경우 반복해서 FindPrimeImplicant를 실행시킵니다.*/
		FindPrimeImplicant(rest, input, Tureminterm);
	}

}
int main()
{
	char *InputLine[1000];//파일에서 인풋 민텀을 입력받을 문자열을 저장할수있는 char형 포인터 배열를 선언합니다.
	for (int i = 0; i < 1000; i++)
	{
		InputLine[i] = new char[10000];//문자열을 받기위해 동적할당합니다.
	}
	char *Tureminterm[1000];//돈케어 민텀을 제외한 트루 민텀을받기위한 char형 포인터 배열를 선언합니다.
	for (int i = 0; i < 1000; i++)
	{
		Tureminterm[i] = new char[10000];//문자열을 받기위해 동적할당합니다.
	}
	char count[1000];
	ifstream fin;//파일입력 클래스인 fin을 선언합니다.
	fin.open("input_minterm.txt");//open input_minterm.txt file
	if (!fin.is_open())
	{
		cout << "파일을 열지 못하였습니다." << endl;//파일을 여는 것을 실패한경우 실행되는 예외처리 입니다.
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//해제
			delete[] Tureminterm[i];//해제
		}
		return 0;
	}
	int i = 0;
	int input = 0;
	while (!fin.eof())//파일에서 파일의 끝까지 한행씩 입력받아 char 형 포인터 배열 InputLine에 저장합니다.
	{
		fin.getline(InputLine[i], 10000);
		*InputLine[i + 1] = 0;
		i++;


	}
	
	
	input = atoi(InputLine[0]);//char 형 포인터 배열 InputLine의 첫번째 행은 인풋의 개수 입니다.

	if (input == -48)
	{
		cout << "input의 갯수를 입력하지 않으셨습니다." << endl;//첫번째행이 비어있어 인풋의 개수를 알 수 없을 때 실행되는 예외처리입니다.
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//해제
			delete[] Tureminterm[i];//해제
		}
		return 0;
	}

	if (InputLine[1][input + 2] != '\0')
	{
		cout << "입력파일의 형식이 올바르지 않습니다. 수정하십시오" << endl;
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//해제
			delete[] Tureminterm[i];//해제
		}
		return 0;
	}

	int v = 0;
	for (int i = 0; *InputLine[i] != 0; i++)/* InputLine의 [0]의 다음행들은 돈케어나 트루 민텀이고 입력받은 문자열은 예를 들면 d 0000의 형식을 가지는 데 계산의
											   편의를 위해 d혹은m과 띄어쓰기 공백하나를 지웁니다.*/
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
	while (InputLine[j][0] == 'd' || InputLine[j][0] == 'm')//* 마찬가지로 true민텀을 저장한 TrueMinterm에서 영어 d와 띄어쓰기 공백하나를 지웁니다.
	{
		for (int i = 0; i <= input + 1; i++)
		{
			InputLine[j][i] = InputLine[j][i + 2];

		}
		termnumber = j;
		j++;
	}

	char * InputMinterm[1000];//Inputline 배열의 첫번째행은 인풋의 개수입니다. 그래서 계산상 편의를 위해 인풋의 갯수를 제외하여 나머지 문자열을 저장할 배열을 다시선언합니다.
	for (int i = 0; i < 1000; i++)
	{
		InputMinterm[i] = new char[input + 1];//동적할당

	}
	for (int i = 0; i < termnumber; i++)
	{
		for (int j = 0; j < input + 1; j++)
		{
			/*InputLine의 첫번째 행(인풋의 개수)을 제외한 모든 트루민텀 혹은 돈케어 민텀을 InputMinterm에 저장합니다.*/
			InputMinterm[i][j] = InputLine[i + 1][j];
			*InputMinterm[i + 1] = 0;
		}
	}
	if (v == 0)
	{
		cout << "TrueMinterm이 존재하지 않습니다." << endl;
		for (int i = 0; i < 1000; i++)
		{
			delete[] InputLine[i];//해제
			delete[] Tureminterm[i];//해제
			delete[] InputMinterm[i];//해제
		}
		return 0;

	}
	
	FindPrimeImplicant(InputMinterm, input, Tureminterm);//퀸맥클러스키 방정식에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 같는다.


	for (int i = 0; i < 1000; i++)
	{
		delete[] InputLine[i];//해제
	}

	return 0;

}