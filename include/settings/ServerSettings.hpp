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

#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <string>
#include <vector>
#include <iostream>

#include "../exceptions/GramException.hpp"

namespace gram
{
    class ServerSettings
    {
    public:

        ServerSettings();

        class SettingsEntry
        {
        public:

            typedef bool (*ValidatorFunction)(std::string val);

            SettingsEntry(std::string name, std::string description, int id, std::string value);
            SettingsEntry(std::string name, std::string description, int id, std::string value, ValidatorFunction validator);

            const std::string Name;
            const std::string Description;
            const int Id;
            const ValidatorFunction Validator;
            std::string Value;            
            
            void PromptAndSet();
        };

        SettingsEntry WriteToFile;
        SettingsEntry OutputFile;
        SettingsEntry CloseAfterTimeout;

        std::vector<SettingsEntry*> Entries;

        void PrintServerSettingsInfo();
        void PrintServerSettings();
    };
}

#endif