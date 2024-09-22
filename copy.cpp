// copy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>
namespace fs = std::filesystem;

std::string findAndReplace(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // 防止无限循环，如果`to`包含`from`
    }
    return str;
}

int main()
{
    std::string source_dir = "D:\\yolo-faster\\Yolo-FastestV2\\UIMap\\train"; // 源目录路径
    std::string dest_dir = "D:\\yolo-faster\\Yolo-FastestV2\\UIMap\\test"; // 目标目录路径
    int file_counter = 1; // 文件编号计数器

    try {
        // 检查源目录是否存在
        if (!fs::exists(source_dir) || !fs::is_directory(source_dir)) {
            std::cerr << "Source directory does not exist or is not a directory." << std::endl;
            return 1;
        }

        // 创建目标目录
        fs::create_directory(dest_dir);

        // 遍历源目录下的所有文件
        for (const auto& entry : fs::directory_iterator(source_dir)) {
            // 如果是文件
            if (fs::is_regular_file(entry.status())) {
                std::string filename = entry.path().filename().string();
                if (filename.find(".jpg") != std::string::npos)
                {
                   // std::cout << std::stoi(filename.substr(0, filename.find_last_of('.'))) << std::endl;;
                    std::string dest_filename = std::to_string(file_counter) + ".jpg";
                    std::cout << entry.path().string() << std::endl;;
                    fs::copy(entry.path(), fs::path(dest_dir) / dest_filename, fs::copy_options::update_existing);
                    std::cout << dest_filename << std::endl;;

                    auto t = entry.path().string();
                    auto s = findAndReplace(t, ".jpg", ".txt");
                    std::string dest_filename2 = std::to_string(file_counter) + ".txt";
                    std::cout << s << std::endl;;
                    fs::copy(fs::path(s), fs::path(dest_dir) / dest_filename2, fs::copy_options::update_existing);
                    std::cout << dest_filename2 << std::endl;;
                    file_counter++;
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "Hello World!\n";
    getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
