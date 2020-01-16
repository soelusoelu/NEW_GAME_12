#pragma once

class Time {
public:
    Time(float sec);
    ~Time();
    void update();
    void reset();
    bool isTime() const;
    void setLimitTime(float sec);

public:
    static float deltaTime;

private:
    float mCurrentTime;
    float mLimitTime;
    bool mIsOverLimit;
};
