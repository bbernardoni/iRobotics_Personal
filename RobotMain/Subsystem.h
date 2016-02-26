#ifndef SUBSYSTEM_H_
#define SUBSYSTEM_H_

class Subsystem
{
  public:
    virtual void startUp() = 0;
    virtual void periodic() = 0;
    
  private:
};


#endif

