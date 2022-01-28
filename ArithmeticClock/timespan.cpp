// A object that represents a Time on a clock that is able to do basic
// arithmatics with other Time objects can also compare to other Time objects
// based on amount of time on clock
// Created by Yusuf Pisan on 4/2/18.
// Substantial edits by Connor Lauerman 1/23/2021
#include "timespan.h"

// explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
TimeSpan::TimeSpan(double hour, double minute, double second) {
  double totalsec = hour * 3600 + minute * 60 + second;
  hours = (int)totalsec / 3600;
  totalsec = totalsec - hours * 3600;
  minutes = (int)totalsec / 60;
  totalsec = totalsec - minutes * 60;
  seconds = totalsec;
}

// takes hours minutes and seconds and converts them to seconds
// Input: three doubles for hour minutes and seconds to be converted
// Outputs: toltal number of seconds as double
double TimeSpan::toTotalSeconds(double hour, double minute,
                                double second) const {
  double totalSeconds = hour * 3600 + minute * 60 + second;
  return totalSeconds;
}

// converts a number of seconds into a TimeSpan object
// Input: a double for amount of seconds to be converted
// Output: a TimeSpan object with hours minutes seconds based total seconds
// given
TimeSpan TimeSpan::convertToTime(double totalSeconds) const {

  double hour = (int)totalSeconds / 3600;
  totalSeconds = totalSeconds - hour * 3600;
  double minute = (int)totalSeconds / 60;
  totalSeconds = totalSeconds - (minute * 60);
  double second = totalSeconds;
  TimeSpan ts(hour, minute, second);
  return ts;
}

// hour component
// Output retirns hours of TimeSpan Object
int TimeSpan::getHour() const { return TimeSpan::hours; }

// minute component
// Output returns minuets of TimeSpan Object
int TimeSpan::getMinute() const { return TimeSpan::minutes; }

// second component
// Output returns hours of TimeSpan Object
int TimeSpan::getSecond() const { return TimeSpan::seconds; }

// true if timespan is 0 or larger
// Output true or false based on if TimeSpan is poisitve or not
bool TimeSpan::isPositive() const {
  bool isPos = false;
  double totalSeconds = toTotalSeconds(hours, minutes, seconds);
  if (totalSeconds > 0 || totalSeconds == 0) {
    isPos = true;
  }
  return isPos;
}

// add
// Input TimeSpan object to be added
// Output the new TimeSpan object after addition is taken place
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {
  TimeSpan tsSum;
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  double total = t1 + t2;
  tsSum = convertToTime(total);
  return tsSum;
}

// subtract
// Input: TimeSpan object to be subtracted
// Output: the new TimeSpan object after subtraction is taken place
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan tsSub;
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  double total = t2 - t1;
  tsSub = convertToTime(total);

  return tsSub;
}

// multiply with an integer
// Input: an int that will multiply the TimeSpan
// Output: the new TimeSpan object after multiplication is taken place
TimeSpan TimeSpan::operator*(unsigned int number) const {
  TimeSpan tsLarge;
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  double t3 = t2 * number;
  tsLarge = convertToTime(t3);
  return tsLarge;
}

// equality ==
// Input: TimeSpan object to compare to
// Output: true or false if the times are the same or not
bool TimeSpan::operator==(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t1 == t2) {
    return true;
  } else {
    return false;
  }
}

// inequality !=
// Input: TimeSpan object to be compared
// Output: true or false based on weather the two objects are not the same or
// the same
bool TimeSpan::operator!=(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t1 == t2) {
    return false;
  } else {
    return true;
  }
}

// Oberloads << operator to print Time as clock
// Input: TimeSpan object to print out to be written to screen
// Output: the TimeSpan ojbect as clock
ostream &operator<<(ostream &out, const TimeSpan &ts) {
  if (ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond()) < 0)

    if ((ts.getMinute() == 0 ||
         (ts.getMinute() > -10 && ts.getMinute() < 10)) &&
        (ts.getSecond() == 0 ||
         (ts.getSecond() > -10 && ts.getSecond() < 10))) {
      out << "-" << abs(ts.getHour()) << ":0" << abs(ts.getMinute()) << ":0"
          << abs(ts.getSecond());
    } else if ((ts.getMinute() == 0 ||
                (ts.getMinute() > -10 && ts.getMinute() < 10))) {
      out << "-" << abs(ts.getHour()) << ":0" << abs(ts.getMinute()) << ":"
          << abs(ts.getSecond());
    } else if ((ts.getSecond() == 0 ||
                (ts.getSecond() > -10 && ts.getSecond() < 10))) {
      out << "-" << abs(ts.getHour()) << ":" << abs(ts.getMinute()) << ":0"
          << abs(ts.getSecond());
    } else {
      out << "-" << abs(ts.getHour()) << ":" << abs(ts.getMinute()) << ":"
          << abs(ts.getSecond());
    }

  else {

    if ((ts.getMinute() == 0 ||
         (ts.getMinute() > -10 && ts.getMinute() < 10)) &&
        (ts.getSecond() == 0 ||
         (ts.getSecond() > -10 && ts.getSecond() < 10))) {
      out << ts.getHour() << ":0" << ts.getMinute() << ":0" << ts.getSecond();
    } else if ((ts.getMinute() == 0 ||
                (ts.getMinute() > -10 && ts.getMinute() < 10))) {
      out << ts.getHour() << ":0" << ts.getMinute() << ":" << ts.getSecond();
    } else if ((ts.getSecond() == 0 ||
                (ts.getSecond() > -10 && ts.getSecond() < 10))) {
      out << ts.getHour() << ":" << ts.getMinute() << ":0" << ts.getSecond();
    } else {
      out << ts.getHour() << ":" << ts.getMinute() << ":" << ts.getSecond();
    }
  }

  return out;
}

// addtion to ojbect
// Input: TimeSpan to be added
// Output: change to calling Object
TimeSpan TimeSpan::operator+=(const TimeSpan &ts) {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  double total = t1 + t2;
  *this = convertToTime(total);
  return *this;
}

// subtraction to ojbect
// Input: TimeSpan to be subtracted
// Output: change to calling Object
TimeSpan TimeSpan::operator-=(const TimeSpan &ts) {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  double total = t2 - t1;
  *this = convertToTime(total);
  return *this;
}

// returns true if the calling object is less than another time
// Input: TimeSpan object to be compared to
// Output: true or false based on comparison
bool TimeSpan::operator<(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t2 < t1) {
    return true;
  } else {
    return false;
  }
}

// returns true if the calling object is greater than another time
// Input: TimeSpan object to be compared to
// Output: true or false based on comparison
bool TimeSpan::operator>(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t2 > t1) {
    return true;
  } else {
    return false;
  }
}

// returns true if the calling object is less than or equal another time
// Input: TimeSpan object to be compared to
// Output: true or false based on comparison
bool TimeSpan::operator<=(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t2 < t1 || t2 == t1) {
    return true;
  } else {
    return false;
  }
}

// returns true if the calling object is greater than or equal another time
// Input: TimeSpan object to be compared to
// Output: true or false based on comparison
bool TimeSpan::operator>=(const TimeSpan &ts) const {
  double t1 = ts.toTotalSeconds(ts.getHour(), ts.getMinute(), ts.getSecond());
  double t2 = this->toTotalSeconds(this->getHour(), this->getMinute(),
                                   this->getSecond());
  if (t2 > t1 || t2 == t1) {
    return true;
  } else {
    return false;
  }
}
