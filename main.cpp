#include "includes/threads.h"
#include "includes/game.h"
#include "includes/storage_templates.h"
#include "src/bench.cpp"
#include "src/exceptions.cpp"

using namespace threads;

int main()
{
  // exceptions();

  // bench_test();

  // Thread:
  // Counter count;
  // count.counter();

  // AtomicCounter aCounter;
  // aCounter.atomicCounter();

  FutureThread fThread;
  // fThread.futureThread();
  // fThread.futureWaitFor();
  // fThread.futureRet();

  // Template:
  // storage_templates::templates();

  // Game::game();

  return 0;
}