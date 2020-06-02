#include <iostream>
#include <windows.h>
#include <map>
#include <cstdlib>
#include <string>
#include <locale.h>
#include <fstream>
#include <conio.h>

using namespace std;

enum Options {
	Encrypt = 1,
	Decrypt,
	Exit
};
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

int GetOptionFromConsole(int& Option);
int GetPathFromConsole(string& Path);
int ReadFileFromPath(string Path, string& Text);
int GetEncryptionStepFromConsole(int& Step);
int Encryption(int Step, string& Text);
int CalculateStep(string Text, int& Step);
int Decryption(int Step, string& Text);
int GetOutputFileNameFromConsole(string& Path);
int Output(string Text);
int SetColor(string Text, int Color);
int main() {
	int ResultCode;
	int Option;
	string Path;
	string Text;

	ResultCode = GetOptionFromConsole(Option);

	if (ResultCode == 4)
	{
		SetColor("Fatal Error!!!!You have entered uncorrect option!", ConsoleColor(Red));
		return 1;
	}

	if ((Option) == Options(Exit))
	{
		SetColor("Goodby!", ConsoleColor(Magenta));
		return 0;
	}

	ResultCode = GetPathFromConsole(Path);

	if (ResultCode != 0)
	{
		SetColor("Error!!!", ConsoleColor(Red));
		return 2;
	}

	ResultCode = ReadFileFromPath(Path, Text);

	if (ResultCode == 1)
	{
		SetColor("Error,opening file!!!", ConsoleColor(Red));
		return 3;
	}

	int EncryptionStep = 0;

	switch (Option)
	{
	case Options(Encrypt):
		ResultCode = GetEncryptionStepFromConsole(EncryptionStep);
		if (ResultCode == 1)
		{
			SetColor("Error!!!You have entered uncorrect step!", ConsoleColor(Red));
			return 4;
		}

		ResultCode = Encryption(EncryptionStep, Text);
		if (ResultCode != 0)
		{
			SetColor("Error!!!Encryption!", ConsoleColor(Red));
			return 5;
		}
		break;
	case Options(Decrypt):
		ResultCode = CalculateStep(Text, EncryptionStep);
		if (ResultCode == 1)
		{
			SetColor("Error source text!!!It`s encrypted text!!!", ConsoleColor(Red));
			return 6;
		}
		else if (ResultCode == 2)
		{
			SetColor("Error CalculateStep!!!", ConsoleColor(Red));
			return 7;
		}
		else if (ResultCode == 3)
		{
			SetColor("Error write step!!!", ConsoleColor(Red));
		}

		ResultCode = Decryption(EncryptionStep, Text);
		if (ResultCode != 0) {
			SetColor("Error Decryption!!!", ConsoleColor(Red));
			return 8;
		}

		break;
	}


	ResultCode = Output(Text);
	if (ResultCode != 0)
	{
		SetColor("Error,save file!!!", ConsoleColor(Red));
		return 9;
	}



	return 0;
}




int GetOptionFromConsole(int& Option) {
	do {
		SetColor("Please enter usage option (1- Encrypt, 2 - Decrypt, 3 - Exit):", ConsoleColor(Yellow));
		cin >> Option;
		if (cin.fail()) {
			return 4;
		}
	} while (!(Option == 1 || Option == 2 || Option == 3));

	return 0;
}

int GetPathFromConsole(string& Path) {
	ifstream file;
	do {
		SetColor("Please enter valid source file path vith text:", ConsoleColor(Yellow));
		cin >> Path;
		file = ifstream(Path);
	} while (!(file.good() && file.peek() != EOF));

	return 0;
}
int  ReadFileFromPath(string Path, string& Text) {
	ifstream OpeningFile;
	OpeningFile.open(Path);
	if (!OpeningFile.is_open()) {
		return 1;
	}
	else {
		SetColor("File is open .Good!", ConsoleColor(Green));
		string str;
		while (!OpeningFile.eof()) {
			OpeningFile >> str;
			Text += str + " ";
			str.clear();
		}
		OpeningFile.close();
	}
	SetColor("Your start text:", ConsoleColor(Yellow));
	SetColor(Text, ConsoleColor(White));
	return 0;
}

int CalculateStep(string Text, int& Step) {
	map <int, int> Alfoeng = {
{97,0},
{98,0},
{99,0},
{100,0},
{101,0},
{102,0},
{103,0},
{104,0},
{105,0},
{106,0},
{107,0},
{108,0},
{109,0},
{110,0},
{111,0},
{112,0},
{113,0},
{114,0},
{115,0},
{116,0},
{117,0},
{118,0},
{119,0},
{120,0},
{121,0},
{122,0}
	};

	int TextLength = Text.length();
	for (int i = 0; i <= TextLength; i++) {
		if (int(Text[i]) > 96 && int(Text[i] < 123)) {
			Alfoeng[int(Text[i])]++;
		}
		else if (int(Text[i]) > 65 && int(Text[i] < 90)) {
			Alfoeng[int(Text[i]) + 32]++;
		}
	}

	int nomber = 0;
	for (int i = 98; i <= 122; i++) {
		if (Alfoeng[i] > Alfoeng[nomber]) {
			nomber = i;
		}
	}
	if (nomber < 101) {
		Step = nomber - 75;
	}
	else if (nomber > 101) {
		Step = nomber - 101;
	}

	if (Step == 0) {
		return 1;
	}
	else if (Step > 25 && Step < 1) {
		return 2;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << "Encriptyon step is : " << Step << endl << "Press enter to continue... " << endl;
	if (getchar() == EOF)SetColor("Error,getchar!!!", ConsoleColor(Red));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (cout.fail() == true) {
		return 3;
	}


	return 0;
}
int Decryption(int Step, string& Text)
{
	int del = Text.length();
	for (int i = 0; i <= del; i++) {
		if ((int(Text[i]) >= 65 && int(Text[i]) <= 90) || (int(Text[i]) >= 97 && int(Text[i]) <= 122)) {
			if (int(Text[i]) >= 65 && int(Text[i]) <= 90)
			{
				if (int(Text[i]) - Step < 65) {
					Text[i] = char(91 - (65 - int(Text[i] - Step)));
				}
				else
				{
					Text[i] = char(Text[i] - Step);
				}

			}
			if (int(Text[i]) >= 97 && int(Text[i]) <= 122) {

				if (int(Text[i]) - Step < 97) {
					Text[i] = char(123 - (97 - int(Text[i] - Step)));
				}
				else
				{
					Text[i] = char(Text[i] - Step);
				}
			}

		}

	}
	SetColor("Your encod text:", ConsoleColor(Yellow));
	SetColor(Text, ConsoleColor(White));
	return 0;
}

int GetEncryptionStepFromConsole(int& Step) {
	do {
		SetColor("Enter key for Encript (1 to 25):", ConsoleColor(Yellow));
		cin >> Step;
		if (cin.fail()) {
			return 1;
		}
	} while (!(Step >= 1 && Step <= 25));
	return 0;
}

int Encryption(int Step, string& Text) {

	int del = Text.length();
	for (int i = 0; i <= del; i++)
		if (int((Text[i]) + Step) > 122) {
			Text[i] = 96 + int(Text[i]) + Step - 122;

		}
		else if (int(Text[i]) >= 65 && int(Text[i] <= 90) && (int(Text[i]) + Step) > 90) {
			Text[i] = 64 + int(Text[i]) + Step - 90;
		}
		else if ((int(Text[i]) >= 65 && int(Text[i]) <= 90) || (int(Text[i]) >= 97 && int(Text[i]) <= 122)) {
			Text[i] = Text[i] + Step;
		}

	SetColor(Text, ConsoleColor(White));
	return 0;
}

int Output(string ResultingText) {
	string Path;
	ofstream Output;
	do {
		SetColor("Please enter path for saving result:", ConsoleColor(Yellow));
		cin >> Path;

		Output.open(Path);
	} while (!(Output.is_open()));
	Output << ResultingText;
	SetColor("Fail writing.Good!", ConsoleColor(Green));
	Output.close();

	return 0;
}

int SetColor(string Text, int Color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	cout << Text << endl;
	if (cout.bad() == true) {
		cout << "Error!!!SetColoe!";
		return 1;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleColor(White));
	return 0;
}