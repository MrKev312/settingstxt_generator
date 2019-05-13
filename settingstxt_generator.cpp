#include "pch.h"
#include "settingstxt_generator.h"

std::string emuiibo_path;
std::vector<std::string> folder_vec;
std::vector<std::string> subfolder_vec;

std::fstream settingstxt;
int main()
{
	settingstxt.open("settings.txt", std::ios::out | std::ios::trunc);

	std::cout << "Please enter the emuiibo path: \n";
	std::cin >> emuiibo_path;
	folder_vec = get_directories(emuiibo_path);
	sort(folder_vec.begin(), folder_vec.end());
	for(auto game : folder_vec)
	{
		settingstxt << "[" + game.substr(emuiibo_path.length()) + "]" + "\n";
		subfolder_vec = get_directories(game);
		sort(subfolder_vec.begin(), subfolder_vec.end());
		for (auto amiibo : subfolder_vec) {
			settingstxt << amiibo.substr(emuiibo_path.length()) + "\n";
		}
	}
	settingstxt.close();
}
std::vector<std::string> get_directories(const std::string& s)
{
	std::vector<std::string> r;
	for (auto& p : std::experimental::filesystem::directory_iterator(s))
		if (p.status().type() == std::experimental::filesystem::file_type::directory)
			r.push_back(p.path().string());
	return r;
}