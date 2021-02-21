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

void gram::ServerSettings::createWriteToFileSetting()
{
    WriteToFile.Name = "WriteToFile";
    WriteToFile.Description = "Controls if received messages should be written to a given file";
    WriteToFile.Value = false;
}

void gram::ServerSettings::createOutputFileSetting()
{
    OutputFile.Name = "OutputFile";
    OutputFile.Description = "If set, this is the file the output is written to";
    OutputFile.Value = std::string();
}

void gram::ServerSettings::createCloseAfterTimeoutSetting()
{
    CloseAfterTimeout.Name = "CloseAfterTimeout";
    CloseAfterTimeout.Description = "Sets a timeout after a server should be stopped";
    CloseAfterTimeout.Value = -1;
}