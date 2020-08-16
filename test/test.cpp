#include <gtest/gtest.h>
#include <stdio.h>
#include "afprintf.h"

// ----------------------------------------------------------------------------
// test struct to print
struct foo {
    int a;
    int b;
};
// Function to print "struct foo" to the FILE*

void format_foo(FILE* f, void* data)
{
    if (data == NULL) {
        fprintf(f, "foo(nill)");
        return;
    }

    struct foo* foo = (struct foo*)data;
    fprintf(f, "foo{a=%d, b=%d}", foo->a, foo->b);
}

#define FORMAT_FOO(ptr)format_foo, (ptr)
// ----------------------------------------------------------------------------

class TestAfprintf : public ::testing::Test
{
    void SetUp() override 
    {
        fake_file = open_memstream(&buffer, &size); 
    }

    void TearDown() override
    {
        if (buffer) {
            free(buffer);
            buffer = nullptr;
        }
    }

    size_t size;

protected:
    FILE* fake_file;
    char* buffer = nullptr;
    foo fake_foo = {10, 100};
};

TEST_F(TestAfprintf, test_no_struct_in_format_positive)
{
    afprintf(fake_file, "Test %d %s", 1, "hello");
    fclose(fake_file);
    ASSERT_STREQ(buffer, "Test 1 hello");
}

TEST_F(TestAfprintf, test_struct_is_only_item_positive)
{
    afprintf(fake_file, "%Y", FORMAT_FOO(&fake_foo));
    fclose(fake_file);
    ASSERT_STREQ(buffer, "foo{a=10, b=100}");
}

TEST_F(TestAfprintf, test_struct_in_the_begining_positive)
{
    afprintf(fake_file, "%Y test %d %s", FORMAT_FOO(&fake_foo), 1, "hello");
    fclose(fake_file);
    ASSERT_STREQ(buffer, "foo{a=10, b=100} test 1 hello");
}

TEST_F(TestAfprintf, test_struct_in_the_middle_positive)
{
    afprintf(fake_file, "test %d %Y test %s", 1, FORMAT_FOO(&fake_foo), "hello");
    fclose(fake_file);
    ASSERT_STREQ(buffer, "test 1 foo{a=10, b=100} test hello");
}

TEST_F(TestAfprintf, test_struct_in_the_end_positive)
{
    afprintf(fake_file, "test %d %s %Y", 1, "hello", FORMAT_FOO(&fake_foo));
    fclose(fake_file);
    ASSERT_STREQ(buffer, "test 1 hello foo{a=10, b=100}");
}

TEST_F(TestAfprintf, test_struct_is_nullptr_negative)
{
    afprintf(fake_file, "test %d %s %Y", 1, "hello", FORMAT_FOO(nullptr));
    fclose(fake_file);
    ASSERT_STREQ(buffer, "test 1 hello foo(nill)");
}

TEST_F(TestAfprintf, test_formatter_callback_is_nullptr_negative)
{
    afprintf(fake_file, "test %d %s %Y", 1, "hello", nullptr, &fake_foo);
    fclose(fake_file);
    ASSERT_STREQ(buffer, "test 1 hello <invalid handler>");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
