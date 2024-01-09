
#include <iostream>
#include <string>
#include <fstream>// for file system functionality
#include <iomanip>// this is INPUT OUTPUT MANIPULATION  and it is just used to control how data is entered into or out of the system
#include <algorithm>

using namespace std;

/*This program is a console application to store three details of football players:
// their names
// their number
// their ages
// the method of storing the information is by using the FSTREAM in c++
// this writes information into a file, i chose a .dat file system,  i can use a .txt file system as well but I just chose this
*/
void questionnaire() {

	/*This function is going to be called to ask the user to input information.
	// basically it asks the user questions so we have the information we need for our system
	*/
	string name;
	int ages;
	int numbers;
	int size = NULL, x = 0;
	fstream pfile("players.dat", ios::in | ios::out | ios::app);
	cout << "\n\t->How many players do you want to add? : "; cin >> size;
	cin.ignore();
	for (int i = 0; i < size; i++) {
		if (pfile.is_open()) {
			system("cls");
			do {
				cout << "\n\t->Enter name : "; getline(cin, name);
				cout << "\t->Enter number/position : "; cin >> numbers;
				cout << "\t->Enter age : "; cin >> ages;
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				pfile << name << "\t\t\t" << numbers << "\t\t\t  " << ages << endl;
				cin.ignore();
				x++;
			} while (x != size);
			cout << endl;
			cout << endl;
		}
		pfile.close();
	}
}
void output() {
	/*This function is going to be called to output information about everything in our database
	*/
	fstream pfile;
	string line;
	pfile.open("players.dat", ios::in | ios::out | ios::app);
	cout << "\n=========================================================\n";
	cout << setw(0) << "NAME \t\t NUMBER/POSITION \t\t AGE" << endl;
	cout << "\n=========================================================\n";

	while (getline(pfile, line)) {
		cout << line << endl;
	}
	cout << "\n=========================================================\n";

	pfile.close();
}
void search() {
	/*This function is going to be called to search for an entry in our database
	// it receives a player name (string format) and then changes it into uppercase, then searches the database
	*/
	string query, line;
	bool found = false;
	cout << "\n\t\t S E A R CH \t P L A Y E R " << endl;
	cout << "\n\t ->Enter the name of the player : "; getline(cin, query);
	transform(query.begin(), query.end(), query.begin(), ::toupper);

	fstream pfile;
	pfile.open("players.dat");

	while (getline(pfile, line) && !found) {
		if (line.find(query) != string::npos) {
			found = true;
			cout << "\n=========================================================\n";
			cout << setw(0) << "NAME \t\t NUMBER/POSITION \t\t AGE" << endl;
			cout << "\n=========================================================\n";
			cout << line << endl;
			cout << "\n=========================================================\n";

		}
	}
	if (!found) {
		cout << "\n\t No record of player could be found.";
	}

}

void remove() {
	/*This function is going to be called to delete an entry from the database
	// but first it searches for the entry to make sure it exists
	// then it deletes it, actually it replaces the entire line with empty quotation marks ""
	// then it rewrites the rest of the information into a new file and renames it as the previous file name
	*/
	string deleteline, line;
	bool found = false;
	cout << "\n\t\t D E L E T E \t P L A Y E R " << endl;
	cout << "\n\t ->Name of player : "; getline(cin, deleteline);
	transform(deleteline.begin(), deleteline.end(), deleteline.begin(), ::toupper);
	/* transform is from the "algorithm" header and I just used it to change all the string inputs to uppercase so that i can easily search for an entry if i need to
	// otherwise i will have difficulty searching for an entry if it is in lowercase and i search in uppercase or it is in lowercase and i search in uppercase. so the best thing is to make them all the same size
	*/

	fstream pfile;
	pfile.open("players.dat");
	ofstream opfile;
	opfile.open("temp.dat");
	if (pfile.is_open() && opfile.is_open()) {
		cout << "\n\t Opening records . . .";

		while (getline(pfile, line)) {

			if (!(line.find(deleteline) != string::npos) && !pfile.eof()) {
				opfile << line << endl;
			}
			else {
				found = true;
				cout << "\n=========================================================\n";
				cout << setw(0) << "NAME \t\t NUMBER/POSITION \t\t AGE" << endl;
				cout << "\n=========================================================\n";
				cout << line << endl;
				cout << "\n=========================================================\n";
				line.replace(0, line.length(), "");
				cout << "\n\t The information above is now deleted." << endl;
			}
		}
	}
	opfile.close();
	pfile.close();
	remove("players.dat");
	rename("temp.dat", "players.dat");

	if (!found) {
		cout << "\n\t No record of player could be found.";
	}
}

void menu() {
	int ch = 0;
	do {
		cout << "\n\t M A I N  \t M E N U" << endl;
		cout << "\n\t [ 1 ] Add Player." << endl;
		cout << "\t [ 2 ] Output  Information." << endl;
		cout << "\t [ 3 ] Remove Player." << endl;
		cout << "\t [ 4 ] Search Player." << endl;
		cout << "\n\t\t |->|"; cin >> ch;
		switch (ch) {
		case 1:system("cls");//this line clears the screen so it looks neat
			cin.ignore();
			questionnaire();
			break;
		case 2:system("cls");
			cin.ignore();
			output();
			break;
		case 3:system("cls");
			cin.ignore();
			remove();
			break;
		case 4: system("cls");
			cin.ignore();
			search();
			break;
		}
	} while (ch != 1 || ch != 2 || ch != 3 || ch != 4);
}

int main() {

	menu();

	return 0;
}