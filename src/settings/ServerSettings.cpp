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

gram::ServerSettings::ServerSettings()
    : WriteToFile("WriteToFile", "Controls if received messages should be written to a given file", 0, false),
      OutputFile("OutputFile", "If set, this is the file the output is written to", 1, ""),
      CloseAfterTimeout("CloseAfterTimeout", "Sets a timeout after a server should be stopped", 2, -1)
{
}

void gram::ServerSettings::PrintServerSettings()
{
    std::string format = "  %-3d|  %-20s|  %-40s\n";

    printf(format.c_str(), WriteToFile.Id, WriteToFile.Name.c_str(), WriteToFile.Description.c_str());
    printf(format.c_str(), OutputFile.Id, OutputFile.Name.c_str(), OutputFile.Description.c_str());
    printf(format.c_str(), CloseAfterTimeout.Id, CloseAfterTimeout.Name.c_str(), CloseAfterTimeout.Description.c_str());
}