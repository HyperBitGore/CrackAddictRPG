#include "Header.h"


void Game::saveGame(Entity* player, int* crack, int *xpreq) {
	std::ofstream mfile;
	mfile.open("save.save", std::ios::in);
	if (!mfile) {
		std::fstream f;
		f.open("save.save", std::fstream::in | std::fstream::out | std::fstream::trunc);
		f.close();
		mfile.open("save.save", std::ios::in);
	}
	mfile << std::to_string((*player).atkdmg) << "\n";
	mfile << std::to_string((*player).health) << "\n";
	mfile << std::to_string((*player).level) << "\n";
	mfile << std::to_string((*player).xp) << "\n";
	mfile << std::to_string((*crack)) << "\n";
	mfile << std::to_string((*xpreq)) << "\n";
	mfile << std::to_string((*player).skillpoints) << "\n";
	mfile << std::to_string((*player).strength) << "\n";
	mfile << std::to_string((*player).agility) << "\n";
	mfile << std::to_string((*player).intelligence) << "\n";
	mfile.close();
}
void Game::loadGame(Entity* player, int* crack, int *xpreq) {
	std::ifstream mfile;
	mfile.open("save.save", std::ios::out);
	if (!mfile) {
		return;
	}
	std::string line;
	int i = 0;
	while (getline(mfile, line)) {
		switch (i) {
		case 0:
			(*player).atkdmg = std::stof(line);
			break;
		case 1:
			(*player).health = std::stoi(line);
			break;
		case 2:
			(*player).level = std::stoi(line);
			break;
		case 3:
			(*player).xp = std::stoi(line);
			break;
		case 4:
			(*crack) = std::stoi(line);
			break;
		case 5:
			(*xpreq) = std::stoi(line);
			break;
		case 6:
			(*player).skillpoints = std::stoi(line);
			break;
		case 7:
			(*player).strength = std::stof(line);
			break;
		case 8:
			(*player).agility = std::stof(line);
			break;
		case 9:
			(*player).intelligence = std::stof(line);
			break;
		}
		i++;
	}

	mfile.close();
}