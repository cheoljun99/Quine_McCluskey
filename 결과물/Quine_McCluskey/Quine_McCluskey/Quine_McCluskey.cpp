#include<iostream>
#include<fstream>
using namespace std;
int FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm);//퀸맥클러스키 방법에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 갖는다.
int SumOfProduct(char **prr, int input, int termnumber);//prime implicnat를 통해 sum of product를 구하는 함수이며 SOP의 cost를 구할 수 있는 함수이다. 인자로 prime implicant를 저장하고 있는 prr배열과 prime implicant의 갯수인 termnumber변수, 인풋의 갯수인 input변수,Tureminterm 배열를 갖는다.  

int SumOfProduct(char **prr, int input, int termnumber)
{
	/*모든 prime implicant만 가지고 SOP를 만드는 것이 아니라 필수주항찾고 필수주항과 함께 필수 주항이 커버하지 못하는 임플리컨트를 만족하는 prime implicant을 통해
	SOP를 구성해야한다. 하지만 이프로그램은 필수주항을 찾는 알고리즘을 구성하지 못하였기 때문에 오로지 prime implicant만을 가지고 SOP를 구성하였다. */
	/*이는 이프로그램의 문제점이며 최소하된 SOP와 cost가 나오지 못할 가능성이 있다.*/
	ofstream fout;//아웃풋스트림 클래스 변수 fout을 선언한다.
	fout.open("result.txt");//"result.txt"파일을 연다.
	if (!fout.is_open())
	{
		cout << "파일을 열지 못하였습니다." << endl;//파일을 여는것에 실패한경우를 위한 예외처리
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
	/*아래는 SOP의 cost를 계산하는 과정이다.*/
	int cost = 0;
	for (int i = 0; i < termnumber; i++)
	{
		int inputnumber = 0;
		int inputposition = 0;
		for (int j = 0; j < input; j++)
		{

			if (prr[i][j] != '_'&&prr[i][j] == '0')/*입력에 0있어 부정값이 입력으로 들어가면
												   인버터(트랜지스터2개)를 추가해주어야한다.*/
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
			cost += (inputnumber * 2);/*NAND게이트의 인풋의 갯수에 두배로
									  트렌지스터의 개수(예를들어 2인풋인 경우 트랜지스터 4개 3인풋인경우 트랜지스터 6개)가 늘어남으로
									   cost += (inputnumber * 2)과정을 거친다.*/
		}
		if (inputnumber > 1)
		{
			cost += 2;//우리가 구하고자하는 것은 AND게이트임으로 NOT게이트(트랜지스터2개)를 추가하여야한다.
		}

	}
	if (termnumber > 1)
	{
		cost += (termnumber * 2);/*프라임 임플리컨트의 갯수가 OR게이트의 인풋의 갯수가 됨으로 인풋의 갯수에 두배로
									트렌지스터의 개수(예를들어 2인풋인 경우 트랜지스터 4개 3인풋인경우 트랜지스터 6개)가 늘어난다 고로 cost += (termnumber * 2);을 계산한다.*/
	}

	if (termnumber > 1)
	{
		cost += 2;//우리가 구하고자하는 것은 OR게이트임으로 NOT게이트(트랜지스터2개)를 추가하여야한다.
	}
	cout << "Cost (# of transistors): ";
	cout << cost << endl;
	fout << endl << endl << endl;
	fout << "Cost (# of transistors): " << cost;
}
int FindPrimeImplicant(char ** InputMinterm, int input, char **Tureminterm)//퀸맥클러스키 방정식에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 같는다.
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
		prr[i] = InputMinterm[i];

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
			rest[L] = InputMinterm[i];//해밍디스턴스가 1인 문자열을 찾지못한경우 대상이 되는 문자열을 rest배열에 넣습니다.
			L++;

		}
	}
	if (s == 0)//아무것도 해밍디스턴스차이가 1인 경우가 없는경우 그배열에 있는 문자열들은 prime inplicant입니다 고로 FindPrimeImplicant 함수를 종료시킵니다.
			   //종료시키면서 SumOfProduct함수를 실행시킵니다.
	{

		SumOfProduct(prr, input, termnumber);
		return 0;
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

	if (s != 0)/*해밍 디스턴스가 1인 경우가있는 경우 (프라임 임플리컨트들만 있는 문자열을 못 찾은 경우)
				prime implicant를 못찾은 경우 반복해서 FindPrimeImplicant를 실행시킵니다.
				이 return 0는 main함수의 프로그램을 종료시키기위한 return 0로 가기위한 것 입니다.*/
	{
		FindPrimeImplicant(rest, input, Tureminterm);
	}

}
int main()
{
	char *InputLine[1000];//파일에서 민텀을 입력받을 문자열을 저장할수있는 char형 포인터 배열를 선언합니다.
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
	input = InputLine[0][0] - '0';//char 형 포인터 배열 InputLine의 첫번째 행은 인풋의 개수 입니다.
	if (input == -48)
	{
		cout << "input의 갯수를 입력하지 않으셨습니다." << endl;//첫번째행이 비어있어 인풋의 개수를 알 수 없을 때 실행되는 예외처리입니다.
		return 0;
	}
	if (InputLine[1][input + 2] != '\0')
	{
		cout << "입력파일의 형식이 올바르지 않습니다. 수정하십시오" << endl;
		return 0;
	}

	int v = 0;
	for (int i = 0; *InputLine[i] != 0; i++)/* InputLine의 [0]의 다음행들은 돈케어나 트루 민텀이고 입력받은 무자열은 예를 들면 d 0000의 형식을 가지는 데 계산의
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
	if (FindPrimeImplicant(InputMinterm, input, Tureminterm) == 0)//퀸맥클러스키 방정식에서 prime Implicant를 찾는 함수이며 인자로는 InputMinterm 배열과, input의 개수, Tureminterm 배열을 같는다.
																//함수가 0을 반환하면 프로그램을 종료한다.
	{
		cout << "프로그램 성공적으로 작동하였습니다. 결과파일을 열어보십시오." << endl;
		return 0;
	}

}