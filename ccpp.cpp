#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>	// UNIX standard library : not part off statndard c/cpp. part of OS
#include <string>
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <fstream>
#include "ccpp.h"

using namespace std;

void crawl_directories(const char *root)
{
	struct dirent **namelist;	
	int dir_count = scandir(root, &namelist, NULL, alphasort);
	if (dir_count < 0) {
		cout << "scandir Error" << endl;
		exit(0);
	} else {
		while (dir_count--) {
			if (namelist[dir_count]->d_name[0] != '.') {
				cout << namelist[dir_count]->d_name << endl;
			}
			delete namelist[dir_count];
		}
		delete namelist;
	}
	return;
}

void help()
{
	cout << "Usage :" << endl;
	cout << "\t -P" << endl << "\t\t List all algorithmic problem" << endl;
	cout << "\t -P <problem name>" << endl << "\t\t Add new algorithmic problem" << endl;
	cout << "\t -S" << endl << "\t\t List all scratchpad example" << endl;
	cout << "\t -S <example name>" << endl << "\t\t Add new scratchpad example" << endl;
	cout << "\t -h" << endl << "\t\t print this message and display available options" << endl;
	cout << "\t <no args>" << endl << "\t\t Display available options" << endl;
}

void usage()
{
	//system("clear"); for clearing screen ... not platform independent maybe ... let's keep it for further research
	cout << endl;
	cout << "=====================================================" << endl;
	cout << "Options:" << endl;
	cout << "[1] Add new algorithmic problem" << endl;
	cout << "[2] List all algorithmic problem" << endl;
	cout << "[3] Add new scratchpad example" << endl;
	cout << "[4] List all scratchpad example" << endl;
	cout << "[5] Add new implementation directory" << endl;
	cout << "[6] List all implementation directories" << endl;
	cout << "=====================================================" << endl;
	cout << endl;
}

const int MAX_DIR_NAMELEN = 1024;

inline void get_dirname(char *dirname, int size)
{
	cout << "Enter the directory name : ";
	cin.ignore();
	cin.get(&dirname[0], size, '\n');
}

inline void sanitize_dirname(char *dirname, int size)
{
	for (int i = 0; i < size; i++) {
		if (dirname[i] == '\0') break;
		char ch = dirname[i];
		int ch_code = static_cast<int>(ch);
		if ((ch_code >=48) && (ch_code <= 57)) {
			//allow numbers
			continue;
		}

		ch |= 0x20; // convert to lower case
		ch_code = static_cast<int>(ch);

		if ((ch_code < 97) || (ch_code > 122)) {
			// replace non-alpha chars with underscore
			dirname[i] = '_';
		}
	}
	cout << dirname << endl;
}

inline void wait_for_key()
{
	cout << "Press any key to continue....." << endl;
	cin.ignore();
	getchar();
}

int verbose = 1;


char *create_and_change_dir(char *dirname, const char *subdir)
{
	char buffer[MAX_DIR_NAMELEN];
	if (getcwd(buffer, MAX_DIR_NAMELEN) == NULL) {
		cout << "getcwd() failed..." << endl;
		NULL;
	}
	
	if (verbose) {
		cout << "current working directory : " << buffer << endl;
	}

	const char *prob_dir = subdir;

	char *dir_buffer = (char *) malloc(sizeof(char)*MAX_DIR_NAMELEN);
	if (dir_buffer == NULL) {
		cout << "malloc failed dir_buffer" << endl;
		return NULL;
	}
	char *write_ptr = dir_buffer;

	//construct final directory
	int buffer_len = strlen(buffer);
	for (int i = 0; i < buffer_len; i++) {
		*write_ptr++ = buffer[i];
	}
	*write_ptr++ = '/';
	int prob_len = strlen(prob_dir);
	for (int i = 0; i < prob_len; i++) {
		*write_ptr++ = prob_dir[i];
	}
	*write_ptr++ = '/';
	int dirname_len = strlen(dirname);
	for (int i = 0; i < dirname_len; i++) {
		*write_ptr++ = dirname[i];
	}
	*write_ptr = '\0';

	if (verbose) {
		cout << "New directory : " << dir_buffer << endl;
	}

	if (mkdir(dir_buffer, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0) {
		if (errno == EEXIST) {
			cout << "Directory is already present.." << endl;
			free(dir_buffer);
			return NULL;
		}
		cout << "mkdir() failed ... " << endl;
		free(dir_buffer);
		return NULL;
	}

	//change directory 
	if (chdir(dir_buffer) < 0) {
		cout << "chdir failed.." << endl;
		free(dir_buffer);
		return NULL;
	}

	return dir_buffer;
}

void create_program_files(char *dirname)
{
	const char *subdir = "programs";
	char *dir_buffer = create_and_change_dir(dirname, subdir);
	if (dir_buffer == NULL) {
		exit(0);
	}
	return;
}

void create_scratchpad_files(char *dirname)
{
	const char *subdir = "scratchpad";
	char *dir_buffer = create_and_change_dir(dirname, subdir);
	if (dir_buffer == NULL) {
		exit(0);
	}
	return;
}

void create_problem_files(char *dirname)
{
	const char *subdir = "problems";
	char *dir_buffer = create_and_change_dir(dirname, subdir);
	if (dir_buffer == NULL) {
		exit(0);
	}

	ofstream outfile;

	outfile.open("solution.cpp", ios::out | ios::trunc );
outfile << "#include <map>\n\
#include <set>\n\
#include <list>\n\
#include <cmath>\n\
#include <ctime>\n\
#include <deque>\n\
#include <queue>\n\
#include <stack>\n\
#include <string>\n\
#include <bitset>\n\
#include <cstdio>\n\
#include <limits>\n\
reate_problem_files(char *dirnamenclude <vector>\n\
#include <climits>\n\
#include <cstring>\n\
#include <cstdlib>\n\
#include <fstream>\n\
#include <numeric>\n\
#include <sstream>\n\
#include <iostream>\n\
#include <algorithm>\n\
#include <unordered_map>\n\
\n\
using namespace std;\n\
\n\
int main()\n\
{\n\
    return 0;\n\
}\n" << endl;
	outfile.close();

	outfile.open("Makefile", ios::out | ios::trunc );
	outfile << "all : solution.cpp" << endl;
	outfile << "\tg++ -std=c++11 -o solution solution.cpp";
	outfile.close();

	outfile.open("run.sh", ios::out | ios::trunc );
	outfile << "cat input | ./solution" << endl;
	chmod("run.sh", S_IRWXU);
	outfile.close();

	outfile.open("input", ios::out | ios::trunc );
	outfile.close();

	outfile.open("program", ios::out | ios::trunc );
	outfile.close();
}

int main(int argc, char **argv)
{
	// argument parsing
	char c = '\0'; // hmm..  can't declare the variable in while loop
	while ((c = getopt(argc, argv, "P:S:X:h")) != EOF) {
		switch (c) {
			case 'P':
				if (optarg != NULL) {
					cout << "value is : " << optarg << endl;
				}
				break;
			case 'S':
				if (optarg != NULL) {
					cout << "value is : " << optarg << endl;
				}
				break;
			case 'X':
				if (optarg != NULL) {
					cout << "value is : " << optarg << endl;
				}
				break;
			case 'h':
				help();
				break;
			default:
				cout << "not a valid argument" << endl;
				break;
		}
	}

	wait_for_key();
	usage();
	int choice = 0;
	while (1) {
		cin >> choice;
		if (cin == NULL) {
			cout << "wrong input !" << endl;
			cin.clear();			// clear the error flag from cin
			cin.ignore(10000, '\n'); // ignore next 10K bytes till you get a newLine
			continue;
		}
		cout << "You entered : [" << choice << "]" << endl;
		char dirname[MAX_DIR_NAMELEN];
		switch (choice) {
			case 1:
				get_dirname(dirname, MAX_DIR_NAMELEN);
				sanitize_dirname(dirname, MAX_DIR_NAMELEN);
				create_problem_files(dirname);
				break;
			case 2:
				crawl_directories("./problems");
				break;
			case 3:
				get_dirname(dirname, MAX_DIR_NAMELEN);
				sanitize_dirname(dirname, MAX_DIR_NAMELEN);
				create_scratchpad_files(dirname);
				break;
			case 4:
				crawl_directories("./scratchpad");
				break;
			case 5:
				get_dirname(dirname, MAX_DIR_NAMELEN);
				sanitize_dirname(dirname, MAX_DIR_NAMELEN);
				create_program_files(dirname);
				break;
			case 6:
				crawl_directories("./implementations");
				break;
			default:
				cout << "This option is not implemented Yet!!" << endl;
				break;
		}
		wait_for_key();
		usage();
	}

	return 0;
}
