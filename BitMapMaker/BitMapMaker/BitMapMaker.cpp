// BitMapMaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

//Creates the level collision bitmap.
void levelBase();
//Creates the enemy spawns bitmap.
void enemySpawn();

int _tmain(int argc, _TCHAR* argv[])
{
	levelBase();
	enemySpawn();
	return 0;
}


//Creates the level collision bitmap.
//Loads the level bases image.
//Converts the colors to a bitmap form in an 8:1 ratio.
//Places them in a file, with a new line per data member.
void levelBase()
{
	//Load the filename file.
	std::ifstream input;
	input.open("levelBaseFileNames.txt");
	if (input.is_open())
	{
		std::string temp;
		std::vector<std::string> fileNames;
		while (!input.eof())
		{
			input >> temp;
			fileNames.push_back(temp);
		}
		input.close();

		//go through every image filename.
		for (int i = 0; i < fileNames.size(); i++)
		{
			sf::Image image;
			//Open the image.
			if (image.loadFromFile(fileNames.at(i)))
			{
				//Create the new vector of vectors.
				int width = image.getSize().x;
				int height = image.getSize().y;

				std::vector<std::vector<int>> bitmap;


				std::vector<int> populator;
				for (int y = 0; y < height / 8; y++)
				{
					populator.push_back(0);
				}
				for (int x = 0; x < width / 8; x++)
				{
					bitmap.push_back(populator);
				}

				//Go through the raw data. Place a one if there is color.
				for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
					{
						int positionX = std::floor(x / 8);
						int positionY = std::floor(y / 8);
						if (bitmap.at(positionX).at(positionY) == 0)
							if (image.getPixel(x, y) != sf::Color::Black)
								bitmap.at(positionX).at(positionY) = 1;
					}
				}
				//Go through the bitmap changing 1s to 2s if it is a platform.
				for (int x = 0; x < bitmap.size(); x++)
				{
					for (int y = 0; y < bitmap.at(x).size() - 1; y++)
					{
						if (bitmap.at(x).at(y) == 0 && bitmap.at(x).at(y + 1) == 1)
							bitmap.at(x).at(y + 1) = 2;
					}
				}
				//Go through the bitmap changing 2s to threes to signal a platform above.
				for (int x = 0; x < bitmap.size(); x++)
				{
					for (int y = 0; y < bitmap.at(x).size() - 5; y++)
					{
						if (bitmap.at(x).at(y) == 2 || bitmap.at(x).at(y) == 3)
						{
							for (int increment = 1; increment <= 5; increment++)
							{
								if (bitmap.at(x).at(y + increment) == 2)
									bitmap.at(x).at(y + increment) = 3;
							}
						}
					}
				}
				//Go through the bitmap changing platform edges to 4s to signal an edge.
				for (int x = 1; x < bitmap.size() - 1; x++)
				{
					for (int y = 0; y < bitmap.at(x).size() - 5; y++)
					{
						if ((bitmap.at(x).at(y) == 2 || bitmap.at(x).at(y) == 3) && bitmap.at(x - 1).at(y) == 0 || (bitmap.at(x).at(y) == 2 || bitmap.at(x).at(y) == 3) && bitmap.at(x + 1).at(y) == 0)
						{
							bitmap.at(x).at(y) = 4;
						}
					}
				}
				//Save the data to a file.
				std::ofstream output;
				std::string file = fileNames.at(i);
				file = file.substr(0, file.find_last_of("."));
				output.open(file + ".txt", std::ios_base::trunc);
				if (output.is_open())
				{
					for (int x = 0; x < bitmap.size(); x++)
					{
						for (int y = 0; y < bitmap.at(x).size(); y++)
						{
							output << bitmap.at(x).at(y) << std::endl;
						}
					}
				}
				else
				{
					std::cout << "Failed to open " + file + ".txt" << std::endl;
				}
				output.close();
				///*
				//Show the bitmap for viewer enjoyment.
				for (int y = 0; y < bitmap.at(1).size(); y++)
				{
					std::cout << y << "::";
					for (int x = 0; x < bitmap.size(); x++)
					{
						std::cout << x << ":" << bitmap.at(x).at(y) << " ";
					}
					std::cout << std::endl;
				}

				system("pause");//*/
			}
		}
	}
	else
	{
		std::cout << "Failed to open imageFileNames.txt" << std::endl;
	}
	system("pause");

}


//Creates the monster spawn bitmap.
//Loads the monster spawns image.
//Converts the colors to a bitmap form in an 8:1 ratio with 
//different numbers and colors for different monsters.
//Places them in a file, with a new line per data member.
void enemySpawn()
{
	//Load the filename file.
	std::ifstream input;
	input.open("levelSpawnFileNames.txt");
	int levelNumber = 0;
	if (input.is_open())
	{
		std::string temp;
		std::vector<std::string> fileNames;
		while (!input.eof())
		{
			input >> temp;
			fileNames.push_back(temp);
		}
		input.close();

		//go through every image filename.
		for (int i = 0; i < fileNames.size(); i++)
		{
			//Load the image.
			sf::Image image;
			if (image.loadFromFile(fileNames.at(i)))
			{
				int width = image.getSize().x;
				int height = image.getSize().y;

				//Create the new vector of vectors.
				std::vector<std::vector<int>> bitmap;


				std::vector<int> populator;
				for (int y = 0; y < height / 8; y++)
				{
					populator.push_back(0);
				}
				for (int x = 0; x < width / 8; x++)
				{
					bitmap.push_back(populator);
				}

				//Go through every pixel, assigning a value to the color value.
				//Each color signals a type of monster according to order of appearance.
				for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
					{
						int positionX = std::floor(x / 8);
						int positionY = std::floor(y / 8);
						if (bitmap.at(positionX).at(positionY) == 0)
						{
							if (image.getPixel(x, y) == sf::Color(1, 1, 1))
								bitmap.at(positionX).at(positionY) = 1;
							if (image.getPixel(x, y) == sf::Color(2, 2, 2))
								bitmap.at(positionX).at(positionY) = 2;
							if (image.getPixel(x, y) == sf::Color(3, 3, 3))
								bitmap.at(positionX).at(positionY) = 3;
							if (image.getPixel(x, y) == sf::Color(4, 4, 4))
								bitmap.at(positionX).at(positionY) = 4;
							if (image.getPixel(x, y) == sf::Color(5, 5, 5))
								bitmap.at(positionX).at(positionY) = 5;
							if (image.getPixel(x, y) == sf::Color(6, 6, 6))
								bitmap.at(positionX).at(positionY) = 6;
							if (image.getPixel(x, y) == sf::Color(7, 7, 7))
								bitmap.at(positionX).at(positionY) = 7;
							if (image.getPixel(x, y) == sf::Color(8, 8, 8))
								bitmap.at(positionX).at(positionY) = 8;
							if (image.getPixel(x, y) == sf::Color(9, 9, 9))
								bitmap.at(positionX).at(positionY) = 9;
						}
					}
				}
				//Save the data to a file.
				std::ofstream output;
				std::string file = fileNames.at(i);
				file = file.substr(0, file.find_last_of("."));
				output.open(file + ".txt", std::ios_base::trunc);
				if (output.is_open())
				{
					for (int x = 0; x < bitmap.size(); x++)
					{
						for (int y = 0; y < bitmap.at(x).size(); y++)
						{
							output << bitmap.at(x).at(y) << std::endl;
						}
					}
				}
				else
				{
					std::cout << "Failed to open " + file + ".txt" << std::endl;
				}
				output.close();
				///*
				//Show the spawns in the console for user enjoyment.
				for (int y = 0; y < bitmap.at(1).size(); y++)
				{
					for (int x = 0; x < bitmap.size(); x++)
					{
						std::cout << bitmap.at(x).at(y);
					}
					std::cout << std::endl;
				}
				std::cout << levelNumber << std::endl;

				levelNumber++;

				system("pause");//*/
			}
		}
	}
	else
	{
		std::cout << "Failed to open imageFileNames.txt" << std::endl;
	}
	system("pause");
}