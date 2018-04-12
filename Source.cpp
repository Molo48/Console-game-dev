#include<iostream>
#include<windows.h>
#include<string>

using namespace std;



//f koja postavlja poziciju kursora
void GotoXY(COORD pozicija) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pozicija);
}

class MyClass
{
private:
	COORD pozicija;
	//rubovi okvira
	static const int MAX_X = 50;
	static const int MAX_Y = 50;
	static const int MIN_X = 10;
	static const int MIN_Y = 10;
public:
	MyClass() 
	{
		pozicija.X = MIN_X+1;
		pozicija.Y = MIN_Y+1;
	};
	

	void Ispis(int a) 
	{
		//moving part
		if (a == 1)
			cout << "0";
		//erasing part (space after b needed)
		else if(a==0)
			cout << "\b ";
	}

	void IspisOkvira()
	{
		COORD temp;
		//ispis okomite granice
		for (int i = MIN_X; i < MAX_X+1; i++)
		{
			temp.X = i;
			temp.Y = MAX_Y+1;
			GotoXY(temp);
			cout << "-";
		}
		for (int i = MIN_X; i < MAX_X + 1; i++)
		{
			temp.X = i;
			temp.Y = MIN_Y;
			GotoXY(temp);
			cout << "-";
		}
		//ispis vodoravne granice
		for (int i = MIN_Y; i < MAX_Y+2; i++)
		{
			temp.Y = i;
			temp.X = MAX_X+1;
			GotoXY(temp);
			cout << "|";
		}
		for (int i = MIN_Y; i < MAX_Y + 2; i++)
		{
			temp.Y = i;
			temp.X = MIN_X;
			GotoXY(temp);
			cout << "|";
		}
		
	}
	//provjera stisnutih tipki, zatim promjena pozicije te postavljanje kursora na novu
	//VK_nesto (arrow keys)
	//&0x8000 u if-u neznam zasto
	void Pomak()
	{
		if (GetKeyState('A') & 0x8000) pozicija.X--;
		if (GetKeyState(VK_LEFT) & 0x8000) pozicija.X--;
		if (GetKeyState('D') & 0x8000) pozicija.X++;
		if (GetKeyState(VK_RIGHT) & 0x8000) pozicija.X++;
		if (GetKeyState('W') & 0x8000) pozicija.Y--;
		if (GetKeyState(VK_UP) & 0x8000) pozicija.Y--;
		if (GetKeyState('S') & 0x8000) pozicija.Y++;
		if (GetKeyState(VK_DOWN) & 0x8000) pozicija.Y++;

		if (pozicija.X < MIN_X+1) pozicija.X = MIN_X+1;
		if (pozicija.Y < MIN_Y+1) pozicija.Y = MIN_Y+1;
		if (pozicija.X > MAX_X) pozicija.X = MAX_X;
		if (pozicija.Y > MAX_Y) pozicija.Y = MAX_Y;
		GotoXY(pozicija);
	}
	//ispis naziva i uputa
	void IspisNaziva()
	{
		COORD t;
		t.X = MIN_X;
		t.Y = MIN_Y - 8;

		GotoXY(t);
		cout << "RUNNING O";

		t.Y += 4;
		GotoXY(t);

		cout << "WASD or arrows for movement";

		t.Y+=2;
		GotoXY(t);
		cout << "X for exit";
		
		

		/*
		cout << "     ___               _             _ _  ___  _ _ ";

		t.Y++;
		GotoXY(t);
		cout << "    | _ \\_ _ _ _  _ _ (_)_ _  __ _  ( | )/ _ \( | )";
	

		t.Y++;
		GotoXY(t);
		cout << "    |   / || | ' \| ' \| | ' \/ _` |  V V| (_) |V V ";

		t.Y++;
		GotoXY(t);
		cout << "    |_|_\\_,_|_||_|_||_|_|_||_\__, |      \___/     ";

		t.Y++;
		GotoXY(t);
		cout << "                              |___/";
		*/
	}

};




int main() 
{
	//fixed window size and position
	HWND wh = GetConsoleWindow();
	MoveWindow(wh, 120, 120, 600, 600, TRUE);

	MyClass m= MyClass();


	//bliking cursor remover part
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursoInfo;
		CursoInfo.dwSize = 1;         /* The size of caret */
		CursoInfo.bVisible = false;   /* Caret is visible? */
		SetConsoleCursorInfo(hConsole, &CursoInfo);



		m.IspisNaziva();
		
		m.IspisOkvira();
		
	while (true)
	{
		//x za prekid
		if (GetKeyState('X') & 0x8000) break;
		
		//brisanje stare pozicije
		m.Ispis(0);
		//promjena (ako ista pritisnuto)
		m.Pomak();
		//ispis nove pozicije
		m.Ispis(1);
		//cekanje, mogucnost upravljanja brzinom ovisno o vrijednosti (u ms)
		Sleep(100);
		
	}

	//pauzira prije zatvaranja, press any key to continue
	system("pause");
	return 0;
}