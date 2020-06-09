#include "dialog.h"
#include <QApplication>
#include "VRComUse.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

    Dialog w;
    w.show();

    ClearVRCom();
    return a.exec();
}
