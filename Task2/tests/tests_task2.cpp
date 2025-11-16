#include <gtest/gtest.h>
#include <fstream>
#include "../src/task2.hpp"

static void writeFile(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream out(path, std::ios::trunc);
    for (const auto& s : lines) out << s << "\n";
}

TEST(GetServersList, CreatesFileWhenMissing) {
    std::string path = "test_missing.txt";
    std::remove(path.c_str());

    auto [status, list] = GetServersList(path);

    EXPECT_EQ(status, ServerOpStatus::Ok);
    EXPECT_TRUE(list.empty());

    std::ifstream in(path);
    EXPECT_TRUE(in.is_open());
}

TEST(GetServersList, ReadsExistingFile) {
    std::string path = "test_read.txt";
    writeFile(path, { "10.0.0.1", "192.168.1.2" });

    auto [status, list] = GetServersList(path);

    EXPECT_EQ(status, ServerOpStatus::Ok);
    ASSERT_EQ(list.size(), 2u);
    EXPECT_EQ(list[0], "10.0.0.1");
    EXPECT_EQ(list[1], "192.168.1.2");
}

TEST(AddServer, AddsToEmptyFile) {
    std::string path = "test_add1.txt";
    writeFile(path, {});

    auto st = AddServer(path, "1.1.1.1");
    EXPECT_EQ(st, ServerOpStatus::Ok);

    auto [status2, list] = GetServersList(path);
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0], "1.1.1.1");
}

TEST(AddServer, DuplicateIP) {
    std::string path = "test_add2.txt";
    writeFile(path, { "1.1.1.1" });

    auto st = AddServer(path, "1.1.1.1");
    EXPECT_EQ(st, ServerOpStatus::Duplicate);

    auto [status2, list] = GetServersList(path);
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0], "1.1.1.1");
}

TEST(DeleteServer, DeletesExistingIP) {
    std::string path = "test_del1.txt";
    writeFile(path, { "1.1.1.1", "2.2.2.2" });

    auto st = DeleteServer(path, "2.2.2.2");
    EXPECT_EQ(st, ServerOpStatus::Ok);

    auto [status2, list] = GetServersList(path);
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0], "1.1.1.1");
}

TEST(DeleteServer, RemovingMissingIP) {
    std::string path = "test_del2.txt";
    writeFile(path, { "1.1.1.1" });

    auto st = DeleteServer(path, "5.5.5.5");
    EXPECT_EQ(st, ServerOpStatus::NotFound);

    auto [status2, list] = GetServersList(path);
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0], "1.1.1.1");
}

TEST(DeleteServer, DeleteFromEmptyFile) {
    std::string path = "test_del3.txt";
    writeFile(path, {});

    auto st = DeleteServer(path, "1.1.1.1");
    EXPECT_EQ(st, ServerOpStatus::NotFound);
}
