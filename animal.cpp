#include "animal.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

//get input
int getNumber(const string& prompt)
{
	int num;
	while(true)
	{
		cout << prompt;
		cin >> num;

		if(cin.fail() || num < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter a Valid Number\n";
			continue;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return num;
	}
}
string getText(const string& prompt)
{
	string text;

	while(true)
	{
		cout << prompt;

		if(!getline(cin, text))
		{
			if(cin.eof()) // if you put some control input in there it can break and close
			{ // only way i could break the getline to test this
				cout << "Stream error occurred. Try again.\n";
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter Valid Text\n";
			continue;
		}

		if(text.find_first_not_of(" \t") == string::npos)
		{
			cout << "Enter Valid Text\n";
			continue;
		}
		return text;
	}
}

//display map/data
void summary(const map<int, Animal>& animals)
{
	if(animals.size() == 0)
	{
		cout << "No Animals on Ranch\n";
		return;
	}

	map<string, int> animalCount;
	for_each(animals.begin(), animals.end(), [&animalCount] (const auto& p)
	{
		string species = p.second.species;
		if(animalCount.find(species) == animalCount.end())
		{
			animalCount.insert({species, 1});
		}
		else
		{
			animalCount[species]++;
		}
	});

	cout << "Summary of Ranch\n";
	for_each(animalCount.begin(), animalCount.end(), [](const pair<string, int> p){
		display(p.first, p.second);
	}); // compiler can't decide which template to use so have to lamba it
}
void displayAll(const map<int, Animal>& animals)
{
        if(animals.size() == 0)
        {
                cout << "No Animals on Ranch\n";
                return;
        }

	cout << left << setw(10) << "Animal ID" << setw(10) << "Species" << setw(15) << "Animal Name" << setw(4) << "Age" << endl;

	for(pair<int, Animal> p : animals)
	{
		cout << left << setw(10) << p.first << setw(10) << p.second.species << setw(15) << p.second.name << setw(4) << p.second.age << endl;
	}
}

//medical History
void displayHistory(const vector<MedicalVisit>& history)
{
	//sort before use

	if(history.size() == 0)
	{
		cout << "No History Found\n";
	}

	cout << left << "Medical History\n" << setw(6) << "Log #" << setw(12) << "Date" << setw(23) << "Animal" << "Description\n";

	int num = 0;
	for_each(history.begin(), history.end(), [&num] (MedicalVisit m)
	{
		num++;
		cout << left << setw(6) << num << setw(12) << m.date << setw(14) << m.animal.name << setw(5) << m.animal.species << " " << setw(3) << m.animal.age << m.desc << endl;
	});
}
void addHistory(vector<MedicalVisit>& history, const map<int, Animal>& animals)
{

	regex dateRGX("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");

	string date;
	Animal animal;
	string desc;

	while(true)
	{
		date = getText("Enter Date Of Visit (yyyy-mm-dd): ");

		if(!regex_match(date, dateRGX))
		{
			cout << "Invalid Date\n";
			continue;
		}
		else
		{
			break;
		}
	}

	while(true)
	{
		int id = getNumber("Enter Animal ID: ");

		if(animals.find(id) == animals.end())
		{
			cout << "Animal Not Found\n";
			continue;
		}
		else
		{
			animal = animals.at(id);
			break;
		}
	}

	desc = getText("Enter Description of Visit: ");

	history.push_back({date, animal, desc});

	sort(history.begin(), history.end(), [] (MedicalVisit& m1, MedicalVisit& m2)
	{
		//sort asc
		if(m1.date != m2.date)
		{
			return m1.date < m2.date;
		}
		else
		{
			return m1.animal.name < m2.animal.name;
		}
	});
}
void updHistory(vector<MedicalVisit>& history, const map<int, Animal>& animals)
{

	int num;

	while(true)
	{
		num = getNumber("Enter Log Number of Visit to Edit: ");

		if(num > history.size() || num <= 0)
		{
			cout << "Invalid Visit\n";
			continue;
		}
		else
		{
			break;
		}
	}

	MedicalVisit m = history[num - 1];
	cout << "Visit " << num << ": ";
	cout << left << setw(12) << m.date << setw(14) << m.animal.name << ", " << setw(5) << m.animal.species << " " << setw(3) << m.animal.age << m.desc << endl;

        regex dateRGX("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");

        string date;
	Animal animal;
        string desc;

	while(true)
	{
        	date = getText("Enter Date Of Visit (yyyy-mm-dd): ");

        	if(!regex_match(date, dateRGX))
        	{
                	cout << "Invalid Date\n";
               		continue;
        	}
        	else
        	{
                	break;
        	}
	}

	while(true)
	{
        	int id = getNumber("Enter Animal ID: ");

        	if(animals.find(id) == animals.end())
        	{
                	cout << "Animal Not Found\n";
                	continue;
        	}
        	else
        	{
                	animal = animals.at(id);
               		break;
        	}

	}

	desc = getText("Enter Description of Visit: ");

	history[num-1] = {date, animal, desc};

	sort(history.begin(), history.end(), [] (MedicalVisit& m1, MedicalVisit& m2)
	{
		//sort ascending 
        	if(m1.date != m2.date)
        	{
                	return m1.date < m2.date;
        	}
        	else
        	{
                	return m1.animal.name < m2.animal.name;
        	}
	});
}
void remHistory(vector<MedicalVisit>& history)
{
        int num;

        while(true)
        {
                num = getNumber("Enter Log Number of Visit to DELETE: ");

                if(num > history.size() || num <= 0)
                {
                        cout << "Invalid Visit\n";
                        continue;
                }
                else
                {
                        break;
                }
        }

	MedicalVisit m = history[num-1];

        cout << "Visit " << num << ": ";
        cout << left << setw(12) << m.date << setw(14) << m.animal.name << setw(5) << m.animal.species << " " << setw(3) << m.animal.age << m.desc << endl;

	string confirm = getText("To confirm deletion type 'DELETE': ");
        if(confirm == "DELETE")
        {
                history.erase(history.begin() + num - 1);
                cout << "Visit Erased Successfully\n";
        }
        else
        {
                cout << "Confirmation Failed, Visit Not Removed\n";
        }


        sort(history.begin(), history.end(), [] (MedicalVisit m1, MedicalVisit m2)
        {
                if(m1.date != m2.date)
                {
                        return m1.date < m2.date;
                }
                else
                {
                        return m1.animal.name < m2.animal.name;
                }
        });
}


void findAnimal(const map<int, Animal>& animals)
{
        if(animals.size() == 0)
        {
                cout << "No Animals on Ranch\n";
                return;
        }

        int id = getNumber("Enter ID of Animal: ");

        auto it = animals.find(id);

        if(it == animals.end())
        {
                cout << "Animal Not Found\n";
        }
	else
	{
                cout << left << setw(10) << "Animal ID" << setw(10) << "Species" << setw(15) << "Animal Name" << setw(4) << "Age" << endl;
                cout << left << setw(10) << it->first << setw(10) << it->second.species << setw(15) << it->second.name << setw(4) << it->second.age << endl;
	}
}

//edit map
void addAnimal(map<int, Animal>& animals)
{
	string name = getText("Enter Animal Name: ");
	string species = getText("Enter Animal Species: ");
	int age = getNumber("Enter Animal Age: ");

	name[0] = toupper(name[0]);
	species[0] = toupper(species[0]);

	if(!name.empty() && !species.empty() && age >= 0)
	{
		if(animals.empty())
		{
			animals.insert({10001, {name, species, age}});
		}
		else
		{
			//gets last animal before end()
			auto it = prev(animals.end());

			//get last id and increment
			int id = it->first;
			id++;

			animals.insert({id, {name, species, age}});
			cout << "Animal Added Successfully\n";
		}
	}
        else
        {
                cout << "One or more inputs were Invalid\n";
        }

}
void updAnimal(map<int, Animal>& animals)
{
        if(animals.size() == 0)
        {
                cout << "No Animals on Ranch\n";
                return;
        }

	int id = getNumber("Enter ID of Animal: ");

	auto it = animals.find(id);

	if(it == animals.end())
	{
		cout << "Animal Not Found\n";
		return;
	}
	else
	{
	        cout << left << setw(10) << "Animal ID" << setw(10) << "Species" << setw(15) << "Animal Name" << setw(4) << "Age" << endl;
                cout << left << setw(10) << it->first << setw(10) << it->second.species << setw(15) << it->second.name << setw(4) << it->second.age << endl;

        	string name = getText("Enter Animal Name: ");
        	string species = getText("Enter Animal Species: ");
        	int age = getNumber("Enter Animal Age: ");

        	name[0] = toupper(name[0]);
	        species[0] = toupper(species[0]);

	        if(!name.empty() && !species.empty() && age >= 0)
	        {
                      	animals[id] = {name, species, age};
                      	cout << "Animal Updated Successfully\n";
        	}
		else
		{
			cout << "One or more inputs were Invalid\n";
		}
	}

}
void remAnimal(map<int, Animal>& animals)
{
        if(animals.size() == 0)
        {
                cout << "No Animals on Ranch\n";
                return;
        }

        int id = getNumber("Enter ID of Animal: ");

        auto it = animals.find(id);

        if(it == animals.end())
        {
                cout << "Animal Not Found\n";
                return;
        }
	else
	{
                cout << endl << left << setw(10) << "Animal ID" << setw(10) << "Species" << setw(15) << "Animal Name" << setw(4) << "Age" << endl;
                cout << left << setw(10) << it->first << setw(10) << it->second.species << setw(15) << it->second.name << setw(4) << it->second.age << endl;

		string confirm = getText("To confirm deletion type 'DELETE': ");
		if(confirm == "DELETE")
		{
			animals.erase(it);
			cout << "Animal Erased Successfully\n";
		}
		else
		{
			cout << "Confirmation Failed, Animal Not Removed\n";
		}
	}
}

