#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<long long,long long> a,pair<long long,long long> b) {
	return a.second>b.second;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int numCases;
	cin>>numCases;
	for (int i=0;i<numCases;i++) {
		int numStudents;
		cin>>numStudents;
		vector<pair<unsigned int,unsigned int>> bothTimes(numStudents);	
		for (int j=0;j<numStudents;j++) {
			int computer,vote;
			cin>>computer>>vote;
			bothTimes.push_back(make_pair(computer,vote));
		}
		sort(bothTimes.begin(), bothTimes.end(), compare);
		long long maxTime=0;
		long long sumComputer=0;
		
		for (int k=0;k<numStudents;k++) {
			//cout<<bothTimes[i].first<<" "<<bothTimes[i].second<<endl;
			sumComputer+=bothTimes[k].first;
			long long studentFinishTime= sumComputer+bothTimes[k].second;
			if (studentFinishTime>maxTime) {
				maxTime=studentFinishTime;
			}
		}
		cout<<maxTime<<endl;
	}
}