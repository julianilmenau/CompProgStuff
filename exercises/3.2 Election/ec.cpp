#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	
	ios_base::sync_with_stdio(false);
	int numCases, numStudents;
	cin>>numCases;
	for (int i=0;i<numCases;i++) {
		cin>>numStudents;
		vector<pair<unsigned int, unsigned int>> bothTimes;
		for (int j=0;j<numStudents;j++) {
			int computer,vote;
			cin>>computer>>vote;
			bothTimes.push_back(pair<int,int>(computer,vote));
		}
		sort(bothTimes.begin(), bothTimes.end(), [](auto &left, auto &right) {
    		return left.second > right.second;
		});
		long long maxTime=0;
		long long sumComputer=0;
		
		for (auto a:bothTimes) {
			sumComputer+=a.first;
			maxTime=max(maxTime,sumComputer+a.second);
		}
		cout<<maxTime<<endl;
	}
	return 0;
}