#include "../../include/utils/Misc.hpp"
using namespace std;
vector< vector<double> > utils::Misc::fetchData(string path) {
	vector< vector<double> > data;

	ifstream infile(path);
	// validate file
	if (!infile) {
		cout << "Error: File not found: " << endl;
		// if the path variable just has the file name, determine the current working directory using only std::filesystem
		// and build up the full path that failed to be found
		return data;
	}

	string line;
	while (getline(infile, line)) {
		vector<double>  dRow;
		string          tok;
		stringstream    ss(line);

		while (getline(ss, tok, ',')) {
			dRow.push_back(stof(tok));
		}

		data.push_back(dRow);
	}

	return data;
}

void utils::Misc::writeData(string path, vector<vector<double>> data)
{
	ofstream outfile(path);

	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (j != 0) { outfile << ","; }
			outfile << data[i][j];
		}
		outfile << endl;
	}
	outfile.close();
}

// Windows centric way of reading a file
//
//std::vector<std::vector<double>> utils::Misc::fetchData(const std::string& filename) {
//    std::vector<std::vector<double>> data;
//
//    HANDLE hFile = CreateFileW(std::wstring(filename.begin(), filename.end()).c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    if (hFile != INVALID_HANDLE_VALUE) {
//        DWORD fileSize = GetFileSize(hFile, NULL);
//        char* buffer = new char[fileSize + 1];
//        DWORD bytesRead;
//
//        if (ReadFile(hFile, buffer, fileSize, &bytesRead, NULL)) {
//            buffer[bytesRead] = '\0'; // Null-terminate the buffer
//
//            std::stringstream ss(buffer);
//            std::string line;
//            while (std::getline(ss, line)) {
//                std::vector<double> row;
//                std::stringstream lineStream(line);
//                std::string value;
//                while (std::getline(lineStream, value, ',')) {
//                    row.push_back(std::stod(value));
//                }
//                data.push_back(row);
//            }
//        }
//
//        delete[] buffer;
//        CloseHandle(hFile);
//    }
//    else {
//        // Handle error - file could not be opened
//        DWORD errorCode = GetLastError();
//        LPSTR errorMessage = nullptr;
//        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//            NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorMessage, 0, NULL);
//        std::cerr << "Failed to open file: " << filename << ". Error code: " << errorCode << ". Error message: " << errorMessage << std::endl;
//        LocalFree(errorMessage);
//    }
//
//    return data;
//}

