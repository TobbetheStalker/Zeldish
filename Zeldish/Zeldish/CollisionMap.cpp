#include "CollisionMap.h"

CollisionMap::CollisionMap()
{
	this->width = 0;
	this->height = 0;
	this->size = 0;
	this->tiles = nullptr;

}

CollisionMap::~CollisionMap()
{
	if (this->tiles) {
		delete[] this->tiles;
	}
}

bool CollisionMap::Load(std::string filename)
{
	std::string path = "..\\Zeldish\\Resources\\CollisionMaps\\" + filename + ".txt";
	std::ifstream readFile;
	int counter = 0;
	readFile.open(path);

	if (!readFile.is_open()) {
		std::cout << "[C++] Could not open file for reading" << std::endl;
		return false;
	}
	else {
		readFile >> this->width;
		readFile >> this->height;

		this->size = this->width * this->height;
		this->tiles = new int[this->size];
		for (int i = 0; i < this->size; i++)
			tiles[i] = 0;

		while (!readFile.eof() && counter < this->size) {

			readFile >> this->tiles[counter];
			counter++;

		}

		readFile.close();
	}


	return true;
}

bool CollisionMap::Save(std::string filename)
{
	std::string path = "..\\Zeldish\\Resources\\CollisionMaps\\" + filename + ".txt";
	std::ofstream writeFile;
	int counter = 0;
	char temp;
	writeFile.open(path);

	if (!writeFile.is_open()) {
		std::cout << "[C++] Could not open file for writing" << std::endl;
		return false;
	}
	else {
		writeFile << this->width << " " << this->height << "\r\n";

		for (int i = 0; i < this->height; i++) {

			for (int j = 0; j < this->width; j++) {
				writeFile << this->tiles[(i * this->width) + j] << " ";
			}
			writeFile << "\r\n";

		}

		writeFile.close();
	}


	return true;
}

int CollisionMap::getTile(int index)
{
	return this->tiles[index];
}

void CollisionMap::setTile(int value, int index)
{
	this->tiles[index] = value;
}

