#pragma once

#ifdef _DEBUG
#pragma comment(lib,"osgQt5d.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"OpenThreadsd.lib")

#else
#pragma comment(lib,"osgQt5.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"OpenThreads.lib")

#endif