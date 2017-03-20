// BitMapMaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream input;
	input.open("imageFileNames.txt");
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

		for (int i = 0; i < fileNames.size(); i++)
		{
			sf::Image image;
			if (image.loadFromFile(fileNames.at(i)))
			{
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

				for (int x = 0; x < bitmap.size(); x++)
				{
					for (int y = 0; y < bitmap.at(x).size() - 1; y++)
					{
						if (bitmap.at(x).at(y) == 0 && bitmap.at(x).at(y + 1) == 1)
							bitmap.at(x).at(y + 1) = 2;
					}
				}

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

				for (int y = 0; y < bitmap.at(1).size(); y++)
				{
					for (int x = 0; x < bitmap.size(); x++)
					{
						std::cout << bitmap.at(x).at(y);
					}
					std::cout << std::endl;
				}

				system("pause");
			}
		}
	}
	else
	{
		std::cout << "Failed to open imageFileNames.txt" << std::endl;
	}
	system("pause");
	return 0;
}

