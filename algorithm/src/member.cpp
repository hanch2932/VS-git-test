#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <fstream>

std::string fileName = "member.txt";

class MEMBER {
private:
	std::string m_name;
	unsigned int m_age = 0;
	void loadUser(std::vector<MEMBER>& v);

public:
	void setUser(std::string name, const unsigned int age);
	std::string getName();
	unsigned int getAge();

	void addUser();
	void delUser(std::string name);
	void modifyAge(std::string name, const unsigned int age);
	void updateUser(std::vector<MEMBER> v);

	bool findUser(std::string name, int& index);

	void printUser();
};

void MEMBER::setUser(std::string name, const unsigned int age) {
	m_name = name;
	m_age = age;
}

std::string MEMBER::getName() {
	return m_name;
}

unsigned int MEMBER::getAge() {
	return m_age;
}

void MEMBER::loadUser(std::vector<MEMBER>& v) {
	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile.is_open()) {
		std::cout << "file open error!\n";
		return;
	}
	for (int i = 0; !readFile.eof(); i++) {
		MEMBER mem;
		readFile >> mem.m_name;
		readFile >> mem.m_age;
		v.push_back(mem);
	}
	v.pop_back();
	readFile.close();
}

void MEMBER::addUser() {
	std::ofstream writeFile(fileName, std::ios::out | std::ios::app);
	writeFile << std::format("{:10} {:3}\n", m_name, m_age);
	writeFile.close();
}

void MEMBER::delUser(std::string name) {
	std::vector<MEMBER> v;
	loadUser(v);

	for (int i = 0; i < v.size(); i++) {
		if (name == v[i].m_name) {
			v.erase(v.begin() + i);
			break;
		}
	}
	updateUser(v);
}

void MEMBER::modifyAge(std::string name, const unsigned int age) {
	std::vector<MEMBER> v;
	loadUser(v);
	bool checkUser;
	int index;
	checkUser = findUser(name, index);
	if (checkUser == false) {
		return;
	}
	v[index].m_age = age;
	updateUser(v);
}

void MEMBER::updateUser(std::vector<MEMBER> v) {
	std::ofstream writeFile(fileName, std::ios::out);
	for (int i = 0; i < v.size(); i++) {
		writeFile << std::format("{:10} {:3}\n", v[i].m_name, v[i].m_age);
	}
	writeFile.close();
}

bool MEMBER::findUser(std::string name, int& index) {
	std::vector<MEMBER> v;
	loadUser(v);

	for (int i = 0; i < v.size(); i++) {
		if (v[i].getName() == name) {
			index = i;
			return true;
		}
	}
	return false;
}

void MEMBER::printUser() {
	std::vector<MEMBER> v;
	loadUser(v);
	for (int i = 0; i < v.size(); i++) {
		std::cout << std::format("name: {:10} | age: {:3}\n", v[i].m_name, v[i].m_age);
	}
}

int main() {
	MEMBER mem;

	while (true) {
		std::system("cls");
		std::cout << "1. addUser\n";
		std::cout << "2. delUser\n";
		std::cout << "3. modifyUser\n";
		std::cout << "4. printUser\n";
		std::cout << "5. exit\n";
		std::cout << "\nchoose: ";
		char choose;
		std::cin >> choose;

		if (choose == '5') {
			return 0;
		}

		std::string name;
		unsigned int age;
		bool check;
		int index;

		switch (choose)
		{
		case '1':
			std::cout << "name: ";
			std::cin >> name;
			std::cout << "age: ";
			std::cin >> age;
			mem.setUser(name, age);
			mem.addUser();
			break;

		case '2':
			std::cout << "name: ";
			std::cin >> name;
			mem.delUser(name);
			break;

		case '3':
			std::cout << "name: ";
			std::cin >> name;
			check = mem.findUser(name, index);
			if (check == false) {
				break;
			}
			std::cout << "change age: ";
			std::cin >> age;
			mem.modifyAge(name, age);
			break;

		case '4':
			std::system("cls");
			mem.printUser();
			std::cin.ignore();
			if (std::cin.get() == '\n')
				std::cout << "";
			break;

		default:
			break;
		}
	}
}