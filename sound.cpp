// sound of silence http://www.boi2007.de/tasks/sound.pdf

// input
// The input is read from a text file named sound.in. The first line of the file
// contains three integers: n (1 ≤ n ≤ 1,000,000), the number of samples in the
// recording; m (1 ≤ m ≤ 10,000), the required length of the silence; 
// and c (0 ≤ c ≤ 10,000), the maximal noise level allowed within silence. The 
// second line of the file contains n integers ai (0 ≤ ai ≤ 1,000,000 for 1 ≤ i ≤ n),
// separated by single spaces: the samples in the recording.

// output 
// The output is written into a text file named sound.out. The file should list all
// values of i such that max(a[i . . . i + m − 1]) − min(a[i . . . i + m − 1]) ≤ c.
// The values should be listed in increasing order, each on a separate line. If
// there is no silence in the input file, write NONE on the first and only line of
// the output file.


// ex 
// input				output
// 7 2 0				2
// 0 1 1 2 3 2 2		6

#include <fstream>
#include <iostream>
#include <ios>
#include <deque>
#include <cstdlib>

using namespace std;

void findSilence(int arr[], int n, int m, int c, char fname[]) {
	fstream outputFile;
	char found = 0;
	outputFile.open(fname, ios::out);
	deque<int> minQ;
	deque<int> maxQ;
	for (int i = 0; i < m; i++) {
		while(!minQ.empty() && arr[i] <= arr[minQ.back()])
			minQ.pop_back();
		while(!maxQ.empty() && arr[i] >= arr[maxQ.back()])
			maxQ.pop_back();
		minQ.push_back(i);
		maxQ.push_back(i);
	}
	for (int i = m; i < n; i++) {
		if (arr[maxQ.front()] - arr[minQ.front()] <= c) {
			found = 1;
			outputFile << i - m + 1 << "\n";
		}

		while(!minQ.empty() && minQ.front() <= i - m)
			minQ.pop_front();
		while(!minQ.empty() && arr[i] <= arr[minQ.back()])
			minQ.pop_back();
		while(!maxQ.empty() && maxQ.front() <= i - m)
			maxQ.pop_front();
		while(!maxQ.empty() && arr[i] >= arr[maxQ.back()])
			maxQ.pop_back();

		minQ.push_back(i);
		maxQ.push_back(i);
	}
	if (arr[maxQ.front()] - arr[minQ.front()] <= c) {
		found = 1;
		outputFile << n - m +1 << "\n";
	}
	if (found == 0) {
		outputFile << "NONE\n";
	}
	outputFile.close();
}

int main(int argc, char* argv[]){

	if(argc < 2 || argc > 3) {
		cerr << "Usage: " << argv[0] << " <input file>\n";
		return 1;
	}
	else {
		// read input file
		int n = 0, m = 0, c = 0, temp = 0;
		char *fname = argv[1];
		fstream inputFile;
		inputFile.open(fname, ios::in);
		inputFile >> n >> m >> c;
		int arr[n];
		for (int i = 0; i < n; i++) {
			inputFile >> temp;
			arr[i] = temp;
		}
		inputFile.close();

		char outputFileName[10];

		if (argc == 2)
			sprintf(outputFileName, "sound.out");
		else 
			sprintf(outputFileName, "sound.out%i", atoi(argv[2]));
		findSilence(arr, n, m, c, outputFileName);
	}

	return 0;
}