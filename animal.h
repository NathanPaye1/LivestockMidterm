#pragma once
#ifndef PAYE_ANIMAL_H
#define PAYE_ANIMAL_H

#include <string>
#include<map>
#include<vector>
#include<iostream>

struct Animal
{
	std::string name;
	std::string species;
	int age;
};

struct MedicalVisit
{
	std::string date;
	Animal animal;
	std::string desc;
};

//template
template <typename T, typename T2>
void display(T key, T2 value)
{
	std::cout << key << ": " << value << std::endl;
}

//get input
int getNumber(const std::string& prompt);
std::string getText(const std::string& prompt);

//display map/data
void summary(const std::map<int, Animal>& animals);
void displayAll(const std::map<int, Animal>& animals);
void findAnimal(const std::map<int, Animal>& animals);

//Medical Stuff
void displayHistory(const std::vector<MedicalVisit>& history);
void addHistory(std::vector<MedicalVisit>& history, const std::map<int, Animal>& animals);
void updHistory(std::vector<MedicalVisit>& history, const std::map<int, Animal>& animals);
void remHistory(std::vector<MedicalVisit>& history);

//edit map
void addAnimal(std::map<int, Animal>& animals);
void updAnimal(std::map<int, Animal>& animals);
void remAnimal(std::map<int, Animal>& animals);
#endif
