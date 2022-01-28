//
// Created by Yusuf Pisan on 4/2/18.
// Edits by Connor Lauerman 1/23/21

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan {
  // overloads << operator to print clock as desired
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // add
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;

  // TODO(student)
  // to add operator+=, operator-=, operator<, operator>, operator<=, operator>=
  // will change calling object to add another time to
  TimeSpan operator+=(const TimeSpan &ts);

  // will change calling object to subtract another time
  TimeSpan operator-=(const TimeSpan &ts);

  // returns true if the calling object is less than another time
  bool operator<(const TimeSpan &ts) const;

  // returns true if the calling object is greater than another time
  bool operator>(const TimeSpan &ts) const;

  // returns true if the calling object is less than or equal another time
  bool operator<=(const TimeSpan &ts) const;

  // returns true if the calling object is greater than or equal another time
  bool operator>=(const TimeSpan &ts) const;

  // hour component of timespan
  int getHour() const;

  // minute component of timespan
  int getMinute() const;

  // second component of timespan
  int getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

  // takes hours minutes and seconds and converts them to seconds
  double toTotalSeconds(double hour, double minute, double second) const;

private:
  // converts a number of seconds into a TimeSpan object
  TimeSpan convertToTime(double totoalSeconds) const;
  // hours data of the time
  int hours;

  // minutes data of the time
  int minutes;

  // seconds data of the time
  int seconds;
};

#endif // ASS2_TIMESPAN_H
