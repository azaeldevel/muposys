
/*
 * main.cc
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * muposys-core is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * muposys-core is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <list>

#ifdef __linux__
    #include <muposysdb.hpp>
#elif defined MSYS2
    #include <muposys/core/bin/muposysdb.hpp>
#elif defined(_WIN32) || defined(_WIN64)
    #include <muposysdb.hh>
#else
	#error "Plataforma desconocida"
#endif

const char* cmdbegin = "";
int main(int argc, char* argv[])
{
    std::filesystem::path repository;
    std::string user = "root", password, host = "localhost",pakage;
    int port = 3306;
    std::string muposys_database = "muposys", muposys_user = "muposys", muposys_password;

    for(int i = 0; i < argc; i++)
    {
        if(strcmp("-r",argv[i]) == 0 or strcmp("--repository",argv[i]) == 0)
        {
            if(i + 1 >= argc)
            {
                std::cerr << "No se espesifico el valor para repository" << std::endl;
                return EXIT_FAILURE;
            }

            repository = argv[++i];
        }
        else if(strcmp("--package",argv[i]) == 0)
        {
            if(i + 1 >= argc)
            {
                std::cerr << "No se espesifico el valor para pakage" << std::endl;
                return EXIT_FAILURE;
            }

            pakage = argv[++i];
        }
        else if(strcmp("--password",argv[i]) == 0)
        {
            if(i + 1 >= argc)
            {
                std::cerr << "No se espesifico el valor para pakage" << std::endl;
                return EXIT_FAILURE;
            }

            password = argv[++i];
        }
        else if(strcmp("--muposys-database",argv[i]) == 0)
        {
            if(i + 1 >= argc)
            {
                std::cerr << "No se espesifico el valor para muposys database" << std::endl;
                return EXIT_FAILURE;
            }

            muposys_database = argv[++i];
        }
        else if(strcmp("--muposys-password",argv[i]) == 0)
        {
            if(i + 1 >= argc)
            {
                std::cerr << "No se espesifico el valor para muposys password" << std::endl;
                return EXIT_FAILURE;
            }

            muposys_password = argv[++i];
        }
    }
    if(repository.empty())
    {
        std::cerr << "No se espesifico un reposistorio para trabajar" << std::endl;
        return EXIT_FAILURE;
    }
    if(pakage.empty())
    {
        std::cerr << "No se espesifico un paquete para trabajar" << std::endl;
        return EXIT_FAILURE;
    }
    if(password.empty())
    {
        std::cerr << "No se espesifico un contraseņa para trabajar" << std::endl;
        return EXIT_FAILURE;
    }
    if(muposys_password.empty())
    {
        std::cerr << "No se espesifico un contraseņa para base de datos muposys" << std::endl;
        return EXIT_FAILURE;
    }

	/*
	mps::Datconnect datconn(host,port,"",user,password);
    mps::Connector connDB;
    mps::Datresult datres;
    bool connDB_flag;
    try
    if(muposys_password.empty())
    {
        connDB_flag = connDB.connect(datconn);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "No se espesifico un contrase?a para base de datos muposys" << std::endl;
        return EXIT_FAILURE;
    }
	*/
	
    std::fstream mpk(repository/pakage, std::ios::in);

    std::cout << "Cargado desde : " << repository << std::endl;

    std::string cmdbegin = "mysql ";
    cmdbegin += "--host=\"" + host + "\" ";
    cmdbegin += "--user=\"" + user + "\" ";
    cmdbegin += "--password=\"" + password + "\" ";

    std::string strline,strcmd,strparams,cmdsql;
    std::list<std::string> cmdlist;

    cmdsql = "CREATE USER IF NOT EXISTS `" + muposys_user + "`@localhost IDENTIFIED BY `" + muposys_password + "`;";
    cmdlist.push_back(cmdbegin + " --execute '" + cmdsql + "'");
    cmdsql = "CREATE DATABASE `" + muposys_database + "`";
    cmdlist.push_back(cmdbegin + " --execute '" + cmdsql + "'");
    cmdsql = "GRANT ALL PRIVILEGES ON `" + muposys_database + "`.* TO `" + muposys_user + "`@`localhost`;";
    cmdlist.push_back(cmdbegin + " --execute '" + cmdsql + "'");

    std::stringstream sline;
    int retcmd;
    /*while(std::getline(mpk,strline))
    {
        sline.clear();
        sline << strline;

        std::getline(sline,strcmd,':');
        std::getline(sline,strparams,':');

        //std::cout << strcmd << " : " << strparams << std::endl;
        if(strcmd.compare("source") == 0)
        {
            cmdsql = "mysql ";
            cmdsql += "--host=\"" + host + "\" ";
            cmdsql += "--user=\"" + user + "\" ";
            cmdsql += "--password=\"" + password + "\" ";
            cmdsql += "--execute 'source ";
            cmdsql += (repository/strparams).make_preferred().string();
            cmdsql += "'";
            std::cout << std::endl;
            std::cout << cmdsql << std::endl;
            cmdlist.push_back(cmdsql);
            //connDB.execute(cmdsql,datres);
            //retcmd = system(cmdsql.c_str());
            //(retcmd == EXIT_SUCCESS) ? std::cout << " - done." : std::cout << " - fail.";
        }
    }*/

    for(const std::string& s : cmdlist)
    {
        std::cout << s ;
        retcmd = system(s.c_str());
        std::cout << ((retcmd == EXIT_SUCCESS) ? " - done." : " - fail.") << std::endl;
    }

	
    /*if(connDB_flag) 
	{
		connDB.commit();
		connDB.close();
	}*/
	
	return EXIT_SUCCESS;
}

