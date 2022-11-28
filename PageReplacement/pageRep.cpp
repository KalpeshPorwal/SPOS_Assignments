#include <bits/stdc++.h>
using namespace std;

void fifo(int *pr, int prl)
{
    int fsize;
    int pagefault = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;
    vector<int> frame(fsize, -1);
    int pointer = 0;
    for(int i = 0; i < prl; i++){
        bool exists = count(frame.begin(), frame.end(), pr[i]) > 0;
        if(exists){
            cout<<"Page hit = "<<pr[i]<<"\n";
            for(int it: frame ){
            cout<<it<<" ";
            }
            cout<<"\n";
        }else{
            cout<<"Page Fault = "<<pr[i]<<"\n";
            pagefault++;
            frame[pointer] = pr[i];
            for(int it: frame ){
                cout<<it<<" ";
            }
            pointer = (pointer+1) % fsize;
            cout<<"\n";
        }
        
    }
    cout<<"Total page fault: "<<pagefault<<"\n";
}

void LRU(int *pr, int prl){
    int fsize, pagefault = 0 , pagehit = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;

    vector<int> frame, que;
    // int front = -1, end = -1;
    for(int i = 0; i < prl; i++){
        bool exists = count(frame.begin(), frame.end(), pr[i]) > 0;
        if(!exists){
            cout<<"Page fault = "<<pr[i]<<"\n";
            pagefault++;
            if(frame.size() != fsize){
                frame.push_back(pr[i]);
                que.push_back(pr[i]);
            }else{
                for(int j = 0; j < fsize; j++){
                    if(frame[j] == que[0]){
                        frame[j] = pr[i];
                        que.push_back(pr[i]);
                        que.erase(que.begin());
                        break;
                    }
                }
            }
        }else{
            cout<<"Page hit = "<<pr[i]<<"\n";
            pagehit++ ;
            for(auto it = que.begin(); it != que.end();){
                if(*it == pr[i]){
                    que.erase(it);
                    que.push_back(pr[i]);
                    break;
                }else
                    ++it;
            }
        }
        cout<<"FRAME: ";
        for(auto it : frame){
            cout<<it<<" ";
        }
        cout<<"\nQUE: ";
        for(auto it : que){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    cout<<"LRU :: Total no. of page faults: "<<pagefault<<"\n";
    cout<<"LRU :: Total no. of page hits: "<<pagehit<<"\n";
}

void MRU(int *pr, int prl){
    int fsize, pagefault = 0 , pagehit = 0;
    cout<<"Enter the frame size: ";
    cin >> fsize;

    vector<int> frame, que;
    int front = -1, end = -1;
    for(int i = 0; i < prl; i++){
        bool exists = count(frame.begin(), frame.end(), pr[i]) > 0;
        if(!exists){
            cout<<"Page fault = "<<pr[i]<<"\n";
            pagefault++;
            if(frame.size() != fsize){
                frame.push_back(pr[i]);
                que.push_back(pr[i]);
            }else{
                for(int j = 0; j < fsize; j++){
                    if(frame[j] == (que.back())){
                        frame[j] = pr[i];
                        que.erase(que.end() - 1);
                        que.push_back(pr[i]);
                        break;
                    }
                }
            }
        }else{
            cout<<"Page hit = "<<pr[i]<<"\n";
            pagehit++ ;
            for(auto it = que.begin(); it != que.end();){
                if(*it == pr[i]){
                    que.erase(it);
                    que.push_back(pr[i]);
                    break;
                }else
                    ++it;
            }
        }
        cout<<"FRAME: ";
        for(auto it : frame){
            cout<<it<<" ";
        }
        cout<<"\nQUE: ";
        for(auto it : que){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
    cout<<"LRU :: Total no. of page faults: "<<pagefault<<"\n";
    cout<<"LRU :: Total no. of page hits: "<<pagehit<<"\n";
}

// Function to check whether a page exists
// in a frame or not
bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], vector<int> &fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn)
{
    int fn;
    cout << "Enter frame size: ";
    cin >> fn;

    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int>
        fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++)
    {

        // Page found in a frame : HIT
        if (search(pg[i], fr))
        {
            hit++;
            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < fn)
            fr.push_back(pg[i]);

        // Find the page to be replaced.
        else
        {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

int main()
{
    int ch;
    int nopr;
    cout << "Enter the no of page references: ";
    cin >> nopr;

    int *pr = new int[nopr];
    cout<<"Enter the page references: ";
    for (int i = 0; i < nopr; i++)
    {
        cin >> pr[i];
    }

    do{
    cout<<"1. FIFo\n2. Least Recently used\n3. Most Recently used\n4.Optimal";
    cout<<"Enter your Choice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        fifo(pr, nopr);
        break;
    case 2:
        LRU(pr, nopr);
        break;
    case 3:
        MRU(pr, nopr);
        break;
    case 4:
        optimalPage(pr, nopr);
        break;

    case -1:
        cout<<"Program terminated !\n";
        break;

    default:
        cout<<"Invalid choice..\n";
        break;
    }
    }while(ch != -1);

    return 0;
}