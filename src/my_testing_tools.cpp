#include "my_testing_tools.hpp"

TestsExecutor& GetTestsExecutorInstance()
{
  static TestsExecutor testExecutor;
  return testExecutor;
}

void TestsExecutor::AddTest(Test* test)
{
  CheckIfExecuted();

  std::string fullTestName;
  fullTestName.reserve(test->GetCaseName().size() + test->GetGroupName().size() + 1);
  fullTestName = test->GetGroupName();
  fullTestName += '.';
  fullTestName += test->GetCaseName();
  m_Tests.push_back({ std::move(fullTestName), test });
}

void TestsExecutor::Run()
{
  CheckIfExecuted();

  m_isExecuted = true;

  for (auto& tmp : m_Tests)
  {
    const std::string& testName = tmp.first;
    Test* test = tmp.second;
    m_tr.RunTest([&] () { test->Run(); }, testName);
  }
}
