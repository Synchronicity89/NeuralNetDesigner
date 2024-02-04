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
