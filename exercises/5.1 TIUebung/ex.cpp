#include <bits/stdc++.h>
using namespace std;

int binarySearch(int l,int r) {
    string answer;
    int m=l+(r-l)/2;
    //cout<<l<<" "<<m<<" "<<endl;
    cout<<"a "<< m<<endl;
    getline(cin,answer);
    if (answer.compare("h")) {
        return binarySearch(l,m);
    } else {
        if (r-l==1) {
            return r;
        }
        return binarySearch(m,r);
    }

}

int main() {
        int nGames;
        cin>>nGames;
        getchar();
        for (int g=0;g<nGames;g++) {
            string answer;
            int i=1,j=0;
            cout<<"a "<<i<<endl;
            getline(cin,answer);
            while (answer.compare("h")==0) {
                j=i;
                i*=2;
                cout<<"a "<<i<<endl;
                getline(cin,answer);
            }
            cout<<"i "<< binarySearch(j,i)<<endl;;
        }
        return 0;
}
