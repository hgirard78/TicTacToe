#include<iostream>
#include<string>
#include<chrono>
#include<sstream>
#include<thread>
using namespace std;
enum class ansi_color_code: int{
	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,
	magenta = 35,
	cyan = 36,
	white = 37,
	bright_black = 90,
    bright_red=91,
    bright_green=92,
    bright_yellow=93,
    bright_blue=94,
    bright_magenta=95,
    bright_cyan=96,
    bright_white=97,
};
template<typename printable>
string print_as_color(printable const& value, ansi_color_code color){
	stringstream sstr;
	sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
	return sstr.str();
}
template<ansi_color_code color, typename printable>
string print_as_color(printable const& value){
	stringstream sstr;
	sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
	return sstr.str();
}
void printGrid(string **tab){
	cout << " ";
	for (int i = 0; i < 3; i++)
		cout << " " << print_as_color<ansi_color_code::bright_cyan>(i + 1);
	cout << endl;
	cout << " ";
	for (int i = 0; i < 7; i++)
		cout << print_as_color<ansi_color_code::bright_white>("-");
	cout << endl;
	for (int i = 0; i < 3; i++){
		cout << print_as_color<ansi_color_code::bright_cyan>(i + 1);
		for (int j = 0; j < 3; j++){
			cout << print_as_color<ansi_color_code::bright_white>("|");
			if (tab[i][j] == "X")
				cout << print_as_color<ansi_color_code::red>(tab[i][j]);
			else if (tab[i][j] == "O")
				cout << print_as_color<ansi_color_code::blue>(tab[i][j]);
			else
				cout << tab[i][j];
		}
		cout <<	print_as_color<ansi_color_code::bright_white>("|") << endl;
		cout << " ";
		for (int j = 0; j < 7; j++)
			cout << print_as_color<ansi_color_code::bright_white>("-");
		cout << endl;
	}
}
bool isFinish(string **tab){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			string val = tab[i][j];
			if (j == 0 && (val == "X" || val == "O") && tab[i][j + 1] == val && tab[i][j + 2] == val)
				return true;
			if (i == 0 && (val == "X" || val == "O") && tab[i + 1][j] == val && tab[i + 2][j] == val)
				return true;
			if (i == 0 & j == 0 && (val == "X" || val == "O") && tab[i + 1][j + 1] == val && tab[i + 2][j + 2] == val)
				return true;
			if (j == 2 && i == 0 && (val == "X" || val == "O") && tab[i + 1][j - 1] == val && tab[i + 2][j - 2] == val)
				return true;
		}
	}
	return false;
}
bool placerPion(string **tab, int player){
	int row,col;
	cout << "Entrez les coordonnées où placer le pion : " << endl;
	cout << "Ligne : ";
	cin >> row;
	cout << "Colonne : ";
	cin >> col;
	cout << endl;
	if (tab[row - 1][col - 1] == "X" || tab[row - 1][col - 1] == "O"){
		cout << "Vous ne pouvez pas placer le pion ici ! Veuillez choisir un emplacement libre." << endl;
		return false;
	}
	else if (player == 1){
		tab[row - 1][col - 1] = "X";
		return true;
	}
	else{
		tab[row - 1][col - 1] = "O";
		return true;
	}
}
void play(string **tab){
	int player = 1;
	bool finished = isFinish(tab);
	while(!finished){
		printGrid(tab);
		cout << "Player : " << player << endl;
		bool played = placerPion(tab, player);
		if (played && player == 1){
			player = 2;
			played = false;
		}
		if (played && player == 2){
			player = 1;
			played = false;
		}
		finished = isFinish(tab);
	}
	printGrid(tab);
	if (player == 1)
		player = 2;
	else
		player = 1;
	cout << "Bravo au joueur " << player << " !" << endl;
	int n;
	cout << "Presser 1 si vous voulez rejouer sinon pressez 2" << endl;
	cin >> n;
	if (n == 1){
		string **tab = new string * [3];
		for (int i = 0; i < 3; i++){
			tab[i] = new string [3];
			for (int j = 0; j < 3; j++)
				tab[i][j] = " ";
		}
		play(tab);
	}
}
int main(int argc, char *argv[]){
	cout << print_as_color<ansi_color_code::bright_green>("Tic Tac Toe") << endl;
	int n = 3;
	string **tab = new string * [n];
	for (int i = 0; i < n; i++){
		tab[i] = new string [n];
		for (int j = 0; j < n; j++)
			tab[i][j] = " ";
	}
	play(tab);
	for(int i = 0; i < n; i++)
		delete[] tab[i];
	delete[] tab;
	return 0;
}