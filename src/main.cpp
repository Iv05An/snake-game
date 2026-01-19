#include <iostream>
using namespace std;

int main() {
    const int width = 20;
    const int height = 10;

    int playerX = width/2;
    int playerY = height/2;

    for (int j = 0; j<height; ++j)
    {
        for (int i=0; i<width; ++i)
        {
            if ( ( playerX-1)==i && (playerY-1)==j) cout<<'@';
            else if ( j==0 || j==(height-1) || i==0 || i==(width-1)) cout<<'#';
            else cout<<' ';
        }
        cout<<endl;
    }
    return 0;
}
