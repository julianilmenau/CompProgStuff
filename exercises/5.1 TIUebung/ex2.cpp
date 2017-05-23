	#include <bits/stdc++.h>
using namespace std;

unsigned long long binarySearch( unsigned long long l,unsigned long long r) {
    if (r-l<=1) {
        return r;
    }
    string answer;
    unsigned long long m=l+(r-l)/2;
    //cout<<l<<" "<<m<<" "<<endl;
    cout<<"a "<< m<<endl;
    getline(cin,answer);
    if (answer.compare("h")) {
        return binarySearch(l,m);
    } else {
        return binarySearch(m,r);
    }

}

int main() {
        int nGames;
        unsigned long long max=(unsigned long long)(pow(2,64)-1);
        cin>>nGames;
        getchar();
        for (int g=0;g<nGames;g++) {
            cout<<"i "<< binarySearch(0,max)<<endl;
        }
        return 0;
}
