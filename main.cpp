#include "includes/threads.hpp"
#include "includes/game.hpp"
#include "includes/storage_templates.hpp"
#include "includes/exceptions.hpp"
#include "includes/fraction.hpp"
#include "includes/animal.hpp"
#include "src/bench.cpp"
#include "src/example.cpp"

// using namespace threads;

int main()
{
  // runExample();

  // >>> Fraction:
  fraction::fraction();

  // >>> Animal:
  // animal::animalAction();

  // >>> Exceptions:
  // user_exceptions::Exceptions exc;
  // exc.doExceptions();
  // user_exceptions::arrayExceptionAction();
  // user_exceptions::moveClassAction();

  // bench_test();

  // >>> Thread:
  // Counter count;
  // count.counter();

  // AtomicCounter aCounter;
  // aCounter.atomicCounter();

  // FutureThread fThread;
  // fThread.futureThread();
  // fThread.futureWaitFor();
  // fThread.futureRet();

  // >>> Template:
  // storage_templates::templates();

  // >>> Game:
  // Game::game();

  return 0;
}