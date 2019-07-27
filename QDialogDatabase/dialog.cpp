#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <stdlib.h>
#include <io.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_openShipXXXButton_clicked()
{
    QString s=QFileDialog::getOpenFileName(this,"open SHIP.XXX file dialog","/","SHIP.XXX files (SHIP.*)");

    /*    std::string fileName=s.toStdString();

    std::size_t found=fileName.find_last_of("/\\");
    std::string shipXXXPath=fileName.substr(0,found);
    */
    unsigned int lTypeId=0;
    long k,num,id;

    FILE* shipXXXFile=fopen(s.toStdString().c_str(),"r");

    if(!shipXXXFile)
		return;
    {
        
		char str[255];
		fscanf(shipXXXFile,"%s\n",str);
        if(strncmp(str,"[ID]",4)==0)
        {
            fgets(str,255,shipXXXFile);
            sscanf_s(str,"ID=%d",&lTypeId);
        }
		fscanf(shipXXXFile,"%s\n",str);

		if(strncmp(str,"[PATH]",6)==0)
		{
			fscanf(shipXXXFile, "OS=%s\n", m_stShipType[lTypeId].szOsModelPath);
			fscanf(shipXXXFile, "TARGET=%s\n", m_stShipType[lTypeId].szTargetModelPath);
		}
		            m_stShipType[lTypeId].bLightNumber=0;
        while(!feof(shipXXXFile))
        {
            fgets(str,255,shipXXXFile);

            if(strncmp(str,"[PARAMETER]", 11) == 0 )
            {
				fscanf(shipXXXFile, "LEN=%f\n" , &m_stShipType[lTypeId].dLen);
				fscanf(shipXXXFile, "BREADTH=%f\n" , &m_stShipType[lTypeId].dBreadth);
				fscanf(shipXXXFile, "EYEHEIGHT=%f\n" , &m_stShipType[lTypeId].dEyeHeight);
				fscanf(shipXXXFile, "OFFSET=%f\n" , &m_stShipType[lTypeId].dOriginOffset);
            }
            else if(strncmp(str,"[WAKEPOS]",9)==0)
            {
				fscanf(shipXXXFile, "BOWOFFSET=%f\n" , &m_stShipType[lTypeId].dBowOffset);
				fscanf(shipXXXFile, "STERNOFFSET=%f\n" , &m_stShipType[lTypeId].dSternOffset);
            }
            else if ( strncmp(str, "[FACTOR]", 8) == 0 )
            {
				fscanf(shipXXXFile, "ROLLFACTOR=%f\n" , &m_stShipType[lTypeId].dRollFactor);
				fscanf(shipXXXFile, "PITCHFACTOR=%f\n" , &m_stShipType[lTypeId].dPitchFactor);

            }
            else if ( strncmp(str, "[SMOOTH]", 8) == 0 )
            {
				fscanf(shipXXXFile, "BOWANDSTERN=%f\n" , &m_stShipType[lTypeId].dBowSternSmooth);
				fscanf(shipXXXFile, "PORTANDSTARB=%f\n" , &m_stShipType[lTypeId].dPortStarbSmooth);

            }
			if ( strncmp(str, "[LIGHT]", 7) == 0 )
			{
				fscanf(shipXXXFile, "LITNUM=%d\n" , &num);

				m_stShipType[lTypeId].bLightNumber = num;
				memset(&m_stShipType[lTypeId].stLight[0], 0, 64*sizeof(ST_SHIP_LIT));
				for (k = 0; k < num; k++)
				{
					fscanf(shipXXXFile, "%d" , &id);
					//if id = 0 , then it is the first light，value = 2, binary= 10
					if (id < 32)
						m_stShipType[lTypeId].stLight[id].lType = (1<<(id + 1));
					else
						m_stShipType[lTypeId].stLight[id].lType = 0xffffffff;

					fscanf(shipXXXFile,"%d%d%f%f%f",&m_stShipType[lTypeId].stLight[id].lMode,
						&m_stShipType[lTypeId].stLight[id].lColor,
						&m_stShipType[lTypeId].stLight[id].dOffset[0],
						&m_stShipType[lTypeId].stLight[id].dOffset[1],
						&m_stShipType[lTypeId].stLight[id].dOffset[2]);

					if ( 0 != m_stShipType[lTypeId].stLight[id].lMode )
					{
						fscanf(shipXXXFile,"%f%f%f%f%f%f\n",&m_stShipType[lTypeId].stLight[id].dVect[0][0],
							&m_stShipType[lTypeId].stLight[id].dVect[0][1],
							&m_stShipType[lTypeId].stLight[id].dVect[0][2],
							&m_stShipType[lTypeId].stLight[id].dVect[1][0],
							&m_stShipType[lTypeId].stLight[id].dVect[1][1],
							&m_stShipType[lTypeId].stLight[id].dVect[1][2]);
					}
					else
					{
						fscanf(shipXXXFile, "\n");
					}
				}//for (k = 0; k < num; k++) read a sequence
			}//if ( strncmp(str, "[LIGHT]", 7) == 0 )
			if ( strncmp(str, "[LINE]", 6) == 0 )
			{
				fscanf(shipXXXFile, "LINENUM=%d\n", &num);
				memset(&m_stShipType[lTypeId].stLine[0], 0, 26*sizeof(ST_SHIP_LINE));
				for (k = 0; k < num; k++)
				{
					fscanf(shipXXXFile, "%d" , &id);
					fscanf(shipXXXFile,"%f%f%f%f%f\n",&m_stShipType[lTypeId].stLine[id].dDiameter,
						&m_stShipType[lTypeId].stLine[id].dLength,
						&m_stShipType[lTypeId].stLine[id].dOffset[0],
						&m_stShipType[lTypeId].stLine[id].dOffset[1],
						&m_stShipType[lTypeId].stLine[id].dOffset[2]);
					m_stShipType[lTypeId].stLine[id].lActive = 1; 
				}//for (k = 0; k < num; k++) read a sequence
			}//if ( strncmp(str, "[LIGHT]", 7) == 0 )*/
        }
    }
    fclose(shipXXXFile);


    QFile data("data.txt");
    if(data.open(QFile::WriteOnly|QFile::Truncate))
    {
       QTextStream out(&data);
	   out<<"[ID]"<<endl<<"ID="<<lTypeId<<endl<<endl;

	   out<<"[PATH]"<<endl<<"OS="<<m_stShipType[lTypeId].szOsModelPath<<endl<<"TARGET="<<m_stShipType[lTypeId].szTargetModelPath<<endl;
	   
	   out<<"[PARAMETER]"<<endl;
       out<<"LEN="<<m_stShipType[lTypeId].dLen<<endl;
	   out<<"BREADTH="<<m_stShipType[lTypeId].dBreadth<<endl;
	   out<<"EYEHEIGHT="<<m_stShipType[lTypeId].dEyeHeight<<endl;
	   out<<"OFFSET="<<m_stShipType[lTypeId].dOriginOffset<<endl;

	   out<<"[WAKEPOS]"<<endl;
	   out<<"BOWOFFSET="<<m_stShipType[lTypeId].dBowOffset<<endl;
	   out<<"STERNOFFSET="<<m_stShipType[lTypeId].dSternOffset<<endl;

	   out<<"[FACTOR]"<<endl;
	   out<<"ROLLFACTOR="<<m_stShipType[lTypeId].dRollFactor<<endl;
	   out<<"PITCHFACTOR="<<m_stShipType[lTypeId].dPitchFactor<<endl;
	   
	   out<<"[SMOOTH]"<<endl;
	   out<<"BOWANDSTERN="<<m_stShipType[lTypeId].dBowSternSmooth<<endl;
	   out<<"PORTANDSTARB="<<m_stShipType[lTypeId].dPortStarbSmooth<<endl<<endl;


       out<<"[LIGHT]"<<endl;
	   out<<"LITNUM="<<m_stShipType[lTypeId].bLightNumber<<endl;
       out<<m_stShipType[lTypeId].dLightSize<<endl;				//the size of light

    }
    if(data.isOpen())
        data.close();
}

void Dialog::on_saveShipDataButton_clicked()
{

}
