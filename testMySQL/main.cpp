#include <iostream>
#include <mysql.h>
int main()
{
	std::cout<<"Hello world!"<<std::endl;
	MYSQL mysql, *sock;
	if(mysql_init(&mysql)!=NULL)
	{
		std::cout<<"mysql_init() succeed!"<<std::endl;
	}
	else
	{
		std::cout<<"mysql_init() failed!"<<std::endl;
		return -1;
	}
    if(mysql_library_init(0,NULL,NULL)==0)
    {
        std::cout<<"mysql_library_init() succeed!"<<std::endl;
    }
    else
    {
        std::cout<<"mysql_library_init() failed!"<<std::endl;
        return -1;
    }
	mysql_options(&mysql,MYSQL_OPT_CONNECT_ATTR_RESET,0);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"testMySQL");

	if((mysql_real_connect(&mysql,"10.10.15.37","westshellShip","11111111","navshipmodel",3306,NULL,0)!=NULL))
	{
		std::cout<<"mysql_real_connect() succeed!"<<std::endl;
	}
	else
	{
		std::cout<<"failed connect!"<<std::endl<<mysql_error(&mysql)<<std::endl;
		return -1;
	}
	//²Ù×÷
	mysql_close(&mysql);
	std::cout<<"connect success!"<<std::endl;
	return 0;
}
