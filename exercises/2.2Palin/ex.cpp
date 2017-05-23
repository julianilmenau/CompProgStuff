#include <iostream>

using namespace std;


void findLongestPalindromicString(string text)
{
    int N = text.length();
    if(N == 0)
        return;
    N = 2*N + 1; //Position count
    int L[N]; //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int expand = -1;
    int diff = -1;
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;

    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror  = 2*C-i;
        expand = 0;
        diff = R - i;
        if(diff > 0)
        {
            if(L[iMirror] < diff) // Case 1
                L[i] = L[iMirror];
            else if(L[iMirror] == diff && i == N-1) // Case 2
                L[i] = L[iMirror];
            else if(L[iMirror] == diff && i < N-1)  // Case 3
            {
                    L[i] = L[iMirror];
                    expand = 1;  // expansion required
            }
            else if(L[iMirror] > diff)  // Case 4
            {
                L[i] = diff;
                expand = 1;  // expansion required
            }
        }
        else
        {
            L[i] = 0;
            expand = 1;  // expansion required
        }

        if (expand == 1)
        {
            while (((i + L[i]) < N && (i - L[i]) > 0) &&
                ( ((i + L[i] + 1) % 2 == 0) ||
                (text[(i + L[i] + 1)/2] == text[(i-L[i]-1)/2] )))
            {
                L[i]++;
            }
        }

        if(L[i] > maxLPSLength)  // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }

        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }
    start = (maxLPSCenterPosition - maxLPSLength)/2;
    end = start + maxLPSLength - 1;
        if (end-start<=0) {
                cout<<-1<<endl;
        } else {
      cout<<end-start+1<<endl;
        }
}


int main(int argc, char *argv[])
{
        ios_base::sync_with_stdio(false);
        string l1;
        getline(cin,l1);
        int lines=stoi(l1);
        for (int i=0;i<lines;i++) {
                getline(cin,l1);
                if (l1=="") {
                        cout<<-1<<endl;
                }
                findLongestPalindromicString(l1);
        }
    return 0;
}
