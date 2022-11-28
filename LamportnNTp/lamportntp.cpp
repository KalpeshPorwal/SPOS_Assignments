#include<bits/stdc++.h>
using namespace std;

void ntp(string hr, string min){
    int hrs = stoi(hr);
    int mins = stoi(min);

    cout << "The original UTC time at server is " << hrs << ":" << mins << "\n";

    int t1, t2, t3, t4;
    cout << "Enter the time t1: ";
    cin >> t1;
    cout << "Enter the time t2: ";
    cin >> t2;
    cout << "Enter the time t3: ";
    cin >> t3;
    cout << "Enter the time t4: ";
    cin >> t4;

    int delay = 9999, offset = 9999;

    for (float i = -0.3; i < 0.4; i+= 0.1)
    {
        float del = (float)(((t4 + i) - (t1 + i)) - ((t3 + i) - (t2 + i)));
        float off = (float)(((t2 + i) - (t1 + i)) + ((t3 + i) - (t4 + i))) / (float)2;
        if (abs((int)del) < delay)
        {
            delay = abs((int)del);
            offset = abs((int)off);
        }
    }

    cout << "\nThe delay for secondary server is: " << delay << endl;
    cout << "The offset for secondary server is: " << (int)offset << endl;

    mins += offset;
    while(mins >= 60){
        hrs += 1;
        mins -= 60;
    }

    cout << "Hence after adding offset the time at secondary server is " << hrs << ":" << mins << "\n";
}

void ntp()
{
    cout << "Enter the time :-\n";
    cout << "Hours:=";
    int h;
    cin >> h;
    cout << "Minutes:=";
    int m;
    cin >> m;

    cout << "The actual time at UTC is " << h << ":" << m << endl;
    int t1, t2, t3, t4;
    int delay, offset;
    cout << "Enter t1 :-";
    cin >> t1;
    cout << "Enter t2 :-";
    cin >> t2;
    cout << "Enter t3 :-";
    cin >> t3;
    cout << "Enter t4 :-";
    cin >> t4;

    delay = (t4 - t1) - (t3 - t2);
    offset = ((t2 - t1) + (t3 - t4)) / 2;
    if (abs(offset) < m)
    {
        m += (offset);
    }
    if (abs(offset) > m && offset < 0)
    {
        h -= 1;
        m += (60 - abs(offset));
    }
    cout << "delay is :-" << delay << endl;
    cout << "Offset  is :-" << offset << endl;

    cout << "The final time after synchronization is :-" << h << ":" << m << endl;
}

void lamport(int e1, int e2, int m[6][3]){
    // stores the timestamp of events in process 1 and 2
    int t1[e1], t2[e2];

    cout << "***** Before applying Lamport's algo *****\n";

    cout << "TimeStamp for events in process 1:\n";
    for (int i = 0; i < e1; i++){
        t1[i] = i + 1;
        cout << t1[i] << " ";
    }
    cout << "\nTimestamps for events in process 2:\n";
    for (int i = 0; i < e2; i++){
        t2[i] = i + 1;
        cout << t2[i] << " ";
    }

    for (int i = 0; i < e1; i++)
    {
        for (int j = 0; j < e2; j++)
        {
            if (m[i][j] == 1)
            {
                if(t1[i] > t2[j]){
                    t2[j] = t1[i] + 1;
                    for (int k = j + 1; k < e2; k++){
                        t2[k] = t2[k - 1] + 1;
                    }
                }
            }
            else if (m[i][j] == -1)
            {
                if(t1[i] < t2[j]){
                    t1[i] = t2[j] + 1;
                    for (int k = i + 1; k < e1; k++){
                        t1[k] = t1[k - 1] + 1;
                    }
                }
            }
            
        }
        
    }

    cout << "***** After applying Lamport's algo *****\n";
    cout << "TimeStamp for events in process 1:\n";
    for (int i = 0; i < e1; i++)
    {
        // t1[i] = i + 1;
        cout << t1[i] << " ";
    }
    cout << "\nTimestamps for events in process 2:\n";
    for (int i = 0; i < e2; i++)
    {
        // t2[i] = i + 1;
        cout << t2[i] << " ";
    }
    cout << "\n";
}


int main(){
    int e1 = 6, e2 = 3;
    int m[6][3];

    // for (int i = 0; i < e1; i++){
    //     for (int j = 0; j < e2; j++){
    //         cout << "Enter 1 for message from " << i + 1 << " -> " << j + 1 << "\nor -1 for message from " << j + 1 << " -> " << i + 1 << "\notherwise 0 : ";
    //         cin >> m[i][j];
    //     }
    // }

    m[0][0] = 0;  m[1][0] = 0;  m[2][0] = 0;  m[3][0] = -1;  m[4][0] = 0; m[5][0] = 0;  
    m[0][1] = 0;  m[1][1] = 0;  m[2][1] = 0;  m[3][1] =  0;  m[4][1] = 1; m[5][1] = 0;  
    m[0][2] = 0;  m[1][2] = 0;  m[2][2] = 0;  m[3][2] =  0;  m[4][2] = 0; m[5][2] = 1;

    int ch;
    do
    {
        cout << "1.Lamport's clock algorithm\n2. NTP\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        string s, hr, min;
        switch (ch)
        {
        case 1:
            lamport(e1, e2, m);
            break;
        case 2:
            // string s;
            // cout << "Enter the UTC time in HH:MM format: ";
            // cin >> s;
            // // string hr, min;
            // hr = s.substr(0, 2);
            // min = s.substr(3, 2);
            // ntp(hr, min);
            ntp();
            break;
        case 3:
            cout << "PRogram ended...\n";
            break;
        
        default:
            break;
        }
    } while (ch != 3);
    

    lamport(e1, e2, m);

    return 0;
}