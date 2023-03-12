#include <iostream>
#include <windows.h>
#include <winnt.h>
#include <fstream>

int main() {
    std::ifstream peFile("example.exe", std::ios::binary);
    if (!peFile) {
        std::cout << "无法打开文件\n";
        return -1;
    }

    IMAGE_DOS_HEADER dosHeader;
    peFile.read(reinterpret_cast<char*>(&dosHeader), sizeof(dosHeader));

    if (dosHeader.e_magic != IMAGE_DOS_SIGNATURE) {
        std::cout << "不是有效的PE文件\n";
        return -1;
    }

    peFile.seekg(dosHeader.e_lfanew);
    DWORD signature;
    peFile.read(reinterpret_cast<char*>(&signature), sizeof(signature));

    if (signature != IMAGE_NT_SIGNATURE) {
        std::cout << "不是有效的PE文件\n";
        return -1;
    }

    IMAGE_FILE_HEADER fileHeader;
    peFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    std::cout << "文件大小: " << fileHeader.SizeOfOptionalHeader << " 字节\n";

   // 在此处添加更多代码以获取其他信息
    // 获取IAT表
    PIMAGE_DATA_DIRECTORY directory = &ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT];
    if (directory->Size > 0) {
    // 获取IAT表的RVA
        DWORD iatRVA = directory->VirtualAddress;
        std::cout << "IAT表位置: " << std::hex << iatRVA << std::endl;
    }
   return 0;
}