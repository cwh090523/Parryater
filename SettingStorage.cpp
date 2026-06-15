#include "SettingStorage.h" 
#include <fstream>

void SaveSettings(const SettingData& setting)
{
	std::ofstream fout("settings.txt");

	if (!fout)
		return;
	fout << setting.bgmVolume << '\n';
	fout << setting.sfxVolume << '\n';


	fout << setting.movementSettingData.moveUpArrowKey<< '\n';
	fout << setting.movementSettingData.moveDownArrowKey<< '\n';
	fout << setting.movementSettingData.moveLeftArrowKey<< '\n';
	fout << setting.movementSettingData.moveRightArrowKey<< '\n';
	fout << setting.movementSettingData.attackKey<< '\n';
	fout << setting.movementSettingData.dashKey<< '\n';
}

void LoadSettings(SettingData& setting)
{
	std::ifstream fin("setting.txt");

	if (!fin)
		return;

	fin >> setting.bgmVolume;
	fin >> setting.sfxVolume;

	fin >> setting.movementSettingData.moveUpArrowKey;
	fin >> setting.movementSettingData.moveDownArrowKey;
	fin >> setting.movementSettingData.moveLeftArrowKey;
	fin >> setting.movementSettingData.moveRightArrowKey;
	fin >> setting.movementSettingData.attackKey;
	fin >> setting.movementSettingData.dashKey;
}
