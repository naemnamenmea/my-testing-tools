#include "test_runner.h"
#include <string_view>
#include <vector>
#include <string>

class Test
{
public:
  Test(std::string groupName, std::string caseName) : 
    m_groupName(std::move(groupName)), m_caseName(std::move(caseName))
  {}

  virtual ~Test() = default;

  virtual void Run() = 0;

  const std::string& GetGroupName() const {
    return m_groupName;
  }
  const std::string& GetCaseName() const {
    return m_caseName;
  }
private:
  std::string m_groupName;
  std::string m_caseName;
};

class TestsExecutor
{
public:
  TestsExecutor() : m_isExecuted(false) {}

  void AddTest(Test* test);

  void Run();

  ~TestsExecutor()
  {
    for (auto& [_, test] : m_Tests)
    {
      delete test;
    }
  }

private:
  void CheckIfExecuted() const
  {
    if (m_isExecuted)
    {
      std::cout << "Tests are already executed. Run skipped." << std::endl;
      return;
    }
  }

  TestRunner m_tr;
  std::vector < std::pair < std::string, Test* >> m_Tests;
  bool m_isExecuted;
};

TestsExecutor& GetTestsExecutorInstance();

#define TEST_CLASS_NAME(a, b) a##b
#define GET_THIS(v) _##v
#define GET_UNIQUE_NAME(v) GET_THIS(v)
#define TO_STRING(x) #x

#define TEST(test_group, test_name)\
  class TEST_CLASS_NAME(test_group, test_name) : public Test \
{\
public:\
TEST_CLASS_NAME(test_group, test_name)() : Test(TO_STRING(test_group), TO_STRING(test_name)) {\
GetTestsExecutorInstance().AddTest(static_cast<Test*>(this));\
}\
void Run() override;\
};\
TEST_CLASS_NAME(test_group, test_name)* const GET_UNIQUE_NAME(__LINE__) = new TEST_CLASS_NAME(test_group, test_name)();\
  void TEST_CLASS_NAME(test_group, test_name)::Run()

#define RUN_ALL_TESTS() {  \
  GetTestsExecutorInstance().Run();     \
}
