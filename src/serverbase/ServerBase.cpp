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

#include "../../include/serverbase/ServerBase.hpp"

gram::ServerBase::ServerBase()
{
    createId();
}

gram::ServerBase::~ServerBase()
{
}

void gram::ServerBase::Start()
{
}

void gram::ServerBase::Stop()
{
}

void gram::ServerBase::received(std::string message)
{
    std::cout << message << std::endl;
}

void gram::ServerBase::PromptAndSetSetting(int settingId)
{
    for(size_t i = 0; i < Settings.Entries.size(); i++)
    {
        if (Settings.Entries.at(i)->Id == settingId)
        {
            Settings.Entries.at(i)->PromptAndSet();
            break;
        }
    }
}

void gram::ServerBase::createId()
{
    char str[UUID_STR_LEN];
    uuid_t uuid;

    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    uuid_clear(uuid);

    std::string id("S" + std::string(str).substr(0, 3));

    ServerId = id;
}
