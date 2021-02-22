/* Copyright (c) 2021 Lukas Pfeifer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "../../include/settings/ServerSettings.hpp"

gram::ServerSettings::SettingsEntry::SettingsEntry(std::string name, std::string description, int id, std::string value) :
    Name(name),
    Description(description),
    Id(id),
    Value(value),
    Validator(nullptr)
{
}

gram::ServerSettings::SettingsEntry::SettingsEntry(std::string name, std::string description, int id, std::string value, ValidatorFunction validator) :
    Name(name),
    Description(description),
    Id(id),
    Value(value),
    Validator(validator)
{
}

void gram::ServerSettings::SettingsEntry::PromptAndSet()
{
    std::string val;
    std::cout << "Enter value: ";
    std::cin >> val;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (Validator != nullptr)
        if (!Validator(val))
            throw GramException("Given value not valid");
    
    Value = val;
}

static bool
isNumeric(std::string input)
{
    if (input.empty())
        return false;

    for(size_t i = 0; i < input.size(); i++)
        if (!isdigit(input[i]))
            return false;

    return true;
}

gram::ServerSettings::ServerSettings()
    : WriteToFile("WriteToFile", "Controls if received messages should be written to a given file", 0, "false",
                  [](std::string val){
                      if (val.compare("false") == 0 || val.compare("true") == 0)  
                        return true;
                      return false;
                  }),
      OutputFile("OutputFile", "If set, this is the file the output is written to", 1, ""),
      CloseAfterTimeout("CloseAfterTimeout", "Sets a timeout after a server should be stopped", 2, "-1",
                   [](std::string val){
                      return isNumeric(val);
                   })
{
    Entries.push_back(&WriteToFile);
    Entries.push_back(&OutputFile);
    Entries.push_back(&CloseAfterTimeout);
}

void gram::ServerSettings::PrintServerSettingsInfo()
{   
    const char* header = "  %-3s|  %-20s|  %-40s\n";
    const char* format = "  %-3d|  %-20s|  %-40s\n";

    printf(header, "Id", "Name", "Description");
    printf("--------------------------------------------------------------\n");

    printf(format, WriteToFile.Id, WriteToFile.Name.c_str(), WriteToFile.Description.c_str());
    printf(format, OutputFile.Id, OutputFile.Name.c_str(), OutputFile.Description.c_str());
    printf(format, CloseAfterTimeout.Id, CloseAfterTimeout.Name.c_str(), CloseAfterTimeout.Description.c_str());
}

void gram::ServerSettings::PrintServerSettings()
{
    const char* header = "  %-3s|  %-20s|  %-40s\n";
    const char* format = "  %-3d|  %-20s|  %-40s\n";

    printf(header, "Id", "Name", "Value");
    printf("--------------------------------------------------------------\n");

    printf(format, WriteToFile.Id, WriteToFile.Name.c_str(), WriteToFile.Value.c_str());
    printf(format, OutputFile.Id, OutputFile.Name.c_str(), OutputFile.Value.c_str());
    printf(format, CloseAfterTimeout.Id, CloseAfterTimeout.Name.c_str(), CloseAfterTimeout.Value.c_str());
}