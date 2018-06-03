#ifndef DRAW_FFT_H
#define DRAW_FFT_H
 
template <typename T>
class DrawFFT {
private:
    T minValue;
    T maxValue;
    uint8_t peak[15];
    int display[15][10];
    T minValueAvg[8];
    T maxValueAvg[8];
 
public:
    DrawFFT();
 
    void SetDate(int year, int month, int day);
 
    int getYear() { return m_year; }
    int getMonth() { return m_month; }
    int getDay()  { return m_day; }
};
 
#endif