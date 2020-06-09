#include <iostream>

using namespace std;

unsigned int _resolution=4;
unsigned int getVertex( unsigned int x, unsigned int y )
{
    return  x + y * _resolution ;
}
int main()
{
    cout << "Hello World!" << endl;
    int x1,x2,y1,y2;
    for(int y=-1;y<(int)_resolution;++y)
    {
        y1=y%_resolution;
        y2=(y+1)%_resolution;
        for(int x=-1;x<(int)_resolution;++x)
        {
            x1=x%_resolution;
            x2=(x+1)%_resolution;
            std::cout<<"(x,y):"<<x<<","<<y<<" (x1,y1): "<<x1<<","<<y1<<"  "<<getVertex(x1,y1)<<endl;
            std::cout<<"(x,y):"<<x<<","<<y<<" (x1,y2): "<<x1<<","<<y2<<"  "<<getVertex(x1,y1)<<endl;
            std::cout<<"(x,y):"<<x<<","<<y<<" (x2,y1): "<<x2<<","<<y1<<"  "<<getVertex(x1,y1)<<endl;
            std::cout<<"(x,y):"<<x<<","<<y<<" (x2,y2): "<<x2<<","<<y2<<"  "<<getVertex(x1,y1)<<endl;
        }
    }
    std::cout<<-1%4<<endl;
    std::cout<<-1%(unsigned int )4<<" "<<(unsigned int )-1<<endl;
    unsigned int num=1;
    std::cout<<num<<endl;
    return 0;
}
