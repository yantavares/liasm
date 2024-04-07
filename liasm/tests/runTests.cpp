#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <vector>
#include <sys/wait.h>

std::vector<std::string> getTestFiles(const std::string &directory)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory.c_str())) != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            if (ent->d_type == DT_REG)
            { // Make sure it's a file and not a directory
                files.emplace_back(ent->d_name);
            }
        }
        closedir(dir);
    }
    else
    {
        std::perror("Could not open directory");
        exit(EXIT_FAILURE);
    }
    return files;
}

int main()
{
    const std::string directory = "./tests";
    const std::string commandPrefix = "make run FILE=";

    auto testFiles = getTestFiles(directory);
    for (const auto &file : testFiles)
    {
        if (file == "runTests.cpp")
        {
            continue;
        }
        std::string command = commandPrefix + directory + "/" + file;
        std::cout << "\nRunning: " << command << std::endl;

        int status = system(command.c_str());

        if (WIFEXITED(status))
        {
            int exitStatus = WEXITSTATUS(status);
            if (exitStatus == 0)
            {
                std::cout << "Success: " << file << " ran without errors." << std::endl;
            }
            else
            {
                std::cerr << "Error: " << file << " exited with status " << exitStatus << std::endl;
            }
        }
        else
        {
            std::cerr << "Error running command for file: " << file << std::endl;
        }
    }
    return 0;
}