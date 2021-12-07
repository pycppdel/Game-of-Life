#ifndef __TIMER__
#define __TIMER__

class Timer{

private:

  long long last_tick;
  long long current;
  long long wait_time;
  void (*func)();

public:

  Timer(long long);

  void set_f(void (*f)());
  void tick();

};

Timer::Timer(long long wt){
  last_tick = 0;
  wait_time = wt;
  current = 0;
}

void Timer::set_f(void (*f)()){
  func = f;
}

void Timer::tick(){

  current = SDL_GetTicks();
  if(current-last_tick >= wait_time){
    last_tick = current;
    func();
  }

}

#endif
