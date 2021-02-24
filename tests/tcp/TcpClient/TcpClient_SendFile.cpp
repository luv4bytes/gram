#include "../../../include/tcp/TcpClient.hpp"

int main()
{
    gram::TcpClient client("github.com", 80);

    client.Open();

    char* s = getcwd(NULL, 0);

    std::string path(s);
    std::string buffer = "Hello GitHub!";

    path = path + "/testfile";

    std::ofstream stream;
    stream.open(path);
    stream.write(buffer.c_str(), buffer.size());
    stream.close();

    client.SendFile(path);

    client.Close();

    remove(path.c_str());

    return 0;
}