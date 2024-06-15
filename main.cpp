#include "includes/threads.hpp"
#include "includes/game.hpp"
#include "includes/storage_templates.hpp"
#include "includes/exceptions.hpp"
#include "src/bench.cpp"
#include "src/example.cpp"

// using namespace threads;

int main()
{
  runExample();

  // Exceptions:
  // user_exceptions::Exceptions exc;
  // exc.doExceptions();
  // user_exceptions::IntArray array;

  // try
  // {
  //   int value{array[4]};
  // }
  // catch (const user_exceptions::ArrayException &exception) // derived catch blocks go first
  // {
  //   std::cerr << "An array exception occurred (" << exception.what() << ")\n";
  // }
  // catch (const std::exception &exception)
  // {
  //   std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
  // }

  // bench_test();

  // Thread:
  // Counter count;
  // count.counter();

  // AtomicCounter aCounter;
  // aCounter.atomicCounter();

  // FutureThread fThread;
  // fThread.futureThread();
  // fThread.futureWaitFor();
  // fThread.futureRet();

  // Template:
  // storage_templates::templates();

  // Game::game();

  return 0;
}