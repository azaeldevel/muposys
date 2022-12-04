/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
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
#include <sstream>
#include <fstream>
#include <filesystem>

#include <muposys/core/bin/muposysdb.hpp>
#include <muposys/core/src/apidb.hh>

int main(int argc, char* argv[])
{
    std::filesystem::path repository;
    std::string user = "root", password, host = "localhost",pakage;
    int port = 3306;


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
        std::cerr << "No se espesifico un contraseña para trabajar" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream mpk(repository/pakage, std::ios::in);

    mps::Datconnect datconn(host,port,"",user,password);

    mps::Connector connDB;
    mps::Datresult datres;
    bool connDB_flag;
    try
    {
        connDB_flag = connDB.connect(datconn);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Cargado desde : " << repository << std::endl;

    std::string strline,strcmd,strparams,cmdsql;
    std::stringstream sline;
    while(std::getline(mpk,strline))
    {
        sline.clear();
        sline << strline;

        std::getline(sline,strcmd,':');
        std::getline(sline,strparams,':');

        //std::cout << strcmd << " : " << strparams << std::endl;
        if(strcmd.compare("source") == 0)
        {
            cmdsql = "source ";
            cmdsql += (repository/strparams).string();
            cmdsql += "";
            std::cout << cmdsql << std::endl;
            connDB.execute(cmdsql,datres);
        }
    }
    connDB.commit();
    if(connDB_flag) connDB.close();
	return EXIT_SUCCESS;
}

