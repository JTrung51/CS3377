#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string url;
    vector<string> listProtocol{"https", "ftp", "ftps"};
    vector<string> listDomains{"com", "net", "edu", "biz", "gov","org"};
    string errorLine = "Invalid URL with following erroneous components: \n";
    cout << "Please enter a valid url: ";
    cin >> url;
    cout << endl;
    if(url.find("://")==-1){
        errorLine+= "Protocol:\tMissing ://\nUnable to continue\n";
        cout << errorLine;
    } else{
    string protocol = url.substr(0, url.find("://"));
    string tempUrl = url.substr(url.find("://") + 3);
    if (find(listProtocol.begin(), listProtocol.end(), protocol) ==listProtocol.end()) {
        errorLine += "Protocol:\t" + protocol + " is not a valid protocol.\n";
    }
    vector<string> domains;

    int index = tempUrl.find(':');
    if (index == -1) {
        index = tempUrl.find('/');
        if (index == -1) {
            index = tempUrl.size();
        }
    }
    string domainLine = tempUrl.substr(0, index);
    string domainZ = domainLine.substr(domainLine.find_last_of('.') + 1);
    tempUrl = tempUrl.substr(index);
    if (count(domainLine.begin(), domainLine.end(), '.') != 2) {
        errorLine += "Domain:\t\tToo many or too little domain arguments\n";
    } else if (find(listDomains.begin(), listDomains.end(), domainZ) == listDomains.end()) {
        errorLine += "Domain:\t\t" + domainZ + " is an invalid domain name.\n";
    }
    bool Bport = false;
    if(tempUrl.size()>0) {
        Bport = tempUrl.at(0) == ':';
    }
    int port = -1;
    if (Bport) {
        tempUrl = tempUrl.substr(1);
        port = stoi(tempUrl.substr(0, tempUrl.find('/')));
        tempUrl = tempUrl.substr(tempUrl.find('/'));
        if (port < 1 || port > 65535) {
            errorLine += "Port:\t\tport number must be between 1 and 65535\n";
        }
    }
    index = tempUrl.find('?');
    if (index == -1) {
        index = tempUrl.size();
    }
    string path = tempUrl.substr(0, index);
    if (path.size() > 0 && path.at(0) != '/') {
        errorLine += "Path\t\tMissing starting key\n";
    } else if (path.size() > 0 && path.substr(path.find_last_of('.') + 1) != "html" && path.substr(path.find_last_of('.') + 1) != "htm") {
        errorLine += "Path\t\tMissing .html or htm at the end of path\n";
    }
    if(path==""){
        path = "None";
    }

    tempUrl = tempUrl.substr(index);
    string parameter = "None";
    if (tempUrl.size() > 0) {
        if (tempUrl.at(0) != '?') {
            errorLine += "Parameter\t\tMissing ? at the beginning\n";
        } else {
            parameter = tempUrl.substr(1);
        }
    }
    string aString;
    if (port==-1){
        aString = "None";
    } else{
        aString = to_string(port);
    }
    if (errorLine.size() == 50) {
        cout << "Protocol: \t" << protocol << "\n"
                "Domain: \t" << domainLine << "\n"
                "Port:\t\t" << aString << "\n"
                "File path:\t"<< path << "\n"
                "Parameters:\t" << parameter << "\n";
    } else {
        cout << errorLine << endl;
    }
    }
    return 0;
}


