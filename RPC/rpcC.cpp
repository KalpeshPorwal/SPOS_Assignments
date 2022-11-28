#include<unistd.h>
#include<arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;

struct obj{
    int len;
    int bre;
    int height;
};

struct answer{
    int ans;
};

void pack(int l, int b, int h, obj &p){
    p.len = l;
    p.bre = b;
    p.height = h;
}

void unpack(answer &s, int &res){
    res = s.ans;
}

int main(){
    int c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));

    client.sin_family = AF_INET;
    client.sin_port = htons(9009);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(c_sock, (struct sockaddr*) &client, sizeof(client)) == -1){
        cout << "Connection failed\n";
        return 0;
    }

    int len, bre, ht;
    cout << "Enter the length, breadth and height of cuboid : ";
    cin >> len >> bre >> ht;

    obj para;
    pack(len, bre, ht, para);

    send(c_sock, &para, sizeof(para), 0);

    int volume;
    answer ser;

    recv(c_sock, &ser, sizeof(ser), 0);

    unpack(ser, volume);

    cout << "Hence the volume of cuboid having l*b*h = " << len << " * " << bre << " * " << ht << " is : "<< volume<<"\n";

    cout << "Client closing...\n";
    close(c_sock);
    return 0;
}