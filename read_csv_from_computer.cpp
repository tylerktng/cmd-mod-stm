#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::string fileName = "WindlessSim.csv";
    std::vector<std::vector<double>> csvContent;
    std::vector<double> row;
	string line, word;

    fstream file (fileName, ios::in);
	if(file.is_open()) {
		while(getline(file, line)) {
			row.clear();
            if (line[0] == '#') {
                continue;
            }
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(stod(word));
			csvContent.push_back(row);
		}
	}
	else {
		std::cout << "Could not open the file" << std::endl;
    }

    // Prints the contents of the CSV file to test
    for(int i = 0; i < csvContent.size(); i++) {
		for(int j = 0; j < csvContent[i].size(); j++) {
			std::cout << csvContent[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}