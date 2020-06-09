#include <iostream>
#include "VRComUse.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    InitVRCom();

    CreateServer();
    std::string cmdStr = "I5,5,3.267491,-7.419345,38.1,2.8,5";
    //CString ipStr = "127.0.0.1";
    //VR_CUSTOM_CMDDATA cd;
    //strcpy(cd.szCmd, cmdStr.c_str());
    //SendVRCommandSvr2Clt(cd,ipStr.GetString());
    VR_CUSTOM_CMDDATA cd;
    strcpy(cd.szCmd, cmdStr.c_str());
//    SendVRCommandSvr2Clt(cd);
    while(true)
    {

    }
    ClearVRCom();
    return 0;
}
