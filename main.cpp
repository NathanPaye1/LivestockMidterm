#include "animal.h"

using namespace std;

int main()
{
	map<int, Animal> animals 
	{
		{10001, {"Albert", "Cow", 3}},
		{10002, {"Bertha", "Sheep", 2}},
		{10003, {"Garry", "Cat", 1}}
 	};

 	vector<MedicalVisit> history;
 	history.push_back({"2026-10-23", animals.at(10003), "Declawed"});
 	history.push_back({"2026-10-24", animals.at(10001), "Hoof Cleaning"});
 	history.push_back({"2026-10-01", animals.at(10003), "Kitty Checkup"});

	cout << "Ranch Helper App\n";

	int choice = 1;
	// main code loop
	while(choice)// as long as not 0 (false) keep going
	{
		cout << "\n1. Ranch Summary\n" <<
		"2. Show All Animals\n3. Medical History\n" <<
		"4. Add New Medical Visit\n5. Update Medical Visit\n6. Remove Medical Visit\n" <<
		"7. Find Animal\n8. Add Animal\n" <<
		"9. Update Animal\n10. Remove Animal\n" <<
		"0. Exit\n\n";
		choice = getNumber("Select Action: ");
		cout << endl;
		switch(choice)
		{
			case 1:
				summary(animals);
				break;
			case 2:
				displayAll(animals);
				break;
			case 3:
				displayHistory(history);
				break;
			case 4:
				addHistory(history, animals);
				break;
			case 5:
				updHistory(history, animals);
				break;
			case 6:
				remHistory(history);
				break;
			case 7:
				findAnimal(animals);
				break;
			case 8:
				addAnimal(animals);
				break;
			case 9:
				updAnimal(animals);
				break;
			case 10:
				remAnimal(animals);
				break;
			case 0:
				cout << "Happy Farming!\n\n";
				break;
			default:
				cout << "Please Select A Valid Option\n\n";
		}
	}
	return 0;
}
