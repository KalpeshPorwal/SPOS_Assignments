#include <unistd.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
using namespace std;

struct objs
{
    int len;
    int bre;
    int height;
};

struct answers
{
    int ans;
};

void unpack(int &l, int &b, int &h, objs &p)
{
    l = p.len;
    b = p.bre;
    h = p.height;
};

void pack(answers &s, int res)
{
    s.ans = res;
};

int volume(int l, int b, int h){
    return l * b * h;
};

int main()
{
    int s_sock, c_sock;
    s_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, other;
    memset(&server, 0, sizeof(server));
    memset(&other, 0, sizeof(other));

    server.sin_family = AF_INET;
    server.sin_port = htons(9009);
    server.sin_addr.s_addr = INADDR_ANY;

    
    if(bind(s_sock, (struct sockaddr*) &server, sizeof(server)) == -1){
        cout << "Binding failed..\n";
        return 0;
    }

    listen(s_sock, 10);

    socklen_t add = sizeof(other);
    c_sock = accept(s_sock, (struct sockaddr *)&other, &add);

    objs parmetr;
    int l, b, h;
    recv(c_sock, &parmetr, sizeof(parmetr), 0);

    unpack(l, b, h, parmetr);

    int result = volume(l, b, h);

    answers ser;
    pack(ser, result);
    send(c_sock, &ser, sizeof(ser), 0);

    cout << "Server closing..\n";
    close(c_sock);
    close(s_sock);
    return 0;
}


