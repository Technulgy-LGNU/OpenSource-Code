#pragma once
#include <Arduino.h>

struct JetsonMsg
{
  bool receivedMsg, isBall, isGoalY, isGoalB;
  uint16_t Xx, Yy, Ww, Hh, GoalYx, GoalYy, GoalYw, GoalYh, GoalBx, GoalBy, GoalBw, GoalBh;

  JetsonMsg(bool receivedMsg) : receivedMsg(receivedMsg) {}

  JetsonMsg(bool receivedMsg, bool isBall, uint16_t Xx, uint16_t Yy, uint16_t Ww, uint16_t Hh,
            bool isGoalY, uint16_t GoalYx, uint16_t GoalYy, uint16_t GoalYw, uint16_t GoalYh,
            bool isGoalB, uint16_t GoalBx, uint16_t GoalBy, uint16_t GoalBw, uint16_t GoalBh)
    : receivedMsg(receivedMsg), isBall(isBall), isGoalY(isGoalY), isGoalB(isGoalB),
      Xx(Xx), Yy(Yy), Ww(Ww), Hh(Hh),
      GoalYx(GoalYx), GoalYy(GoalYy), GoalYw(GoalYw), GoalYh(GoalYh),
      GoalBx(GoalBx), GoalBy(GoalBy), GoalBw(GoalBw), GoalBh(GoalBh) {}

  void print()
  {
    Serial.println("JetsonMsg:");
    Serial.print("\treceivedMsg: ");
    Serial.println(receivedMsg);
    if (receivedMsg)
    {
      Serial.print("\tisBall: ");
      Serial.println(isBall);
      if (isBall) {
        Serial.print("\tBall X: ");
        Serial.println(Xx);
        Serial.print("\tBall Y: ");
        Serial.println(Yy);
        Serial.print("\tBall W: ");
        Serial.println(Ww);
        Serial.print("\tBall H: ");
        Serial.println(Hh);
      }

      Serial.print("\tisGoalY: ");
      Serial.println(isGoalY);
      if (isGoalY) {
        Serial.print("\tGoalY X: ");
        Serial.println(GoalYx);
        Serial.print("\tGoalY Y: ");
        Serial.println(GoalYy);
        Serial.print("\tGoalY W: ");
        Serial.println(GoalYw);
        Serial.print("\tGoalY H: ");
        Serial.println(GoalYh);
      }

      Serial.print("\tisGoalB: ");
      Serial.println(isGoalB);
      if (isGoalB) {
        Serial.print("\tGoalB X: ");
        Serial.println(GoalBx);
        Serial.print("\tGoalB Y: ");
        Serial.println(GoalBy);
        Serial.print("\tGoalB W: ");
        Serial.println(GoalBw);
        Serial.print("\tGoalB H: ");
        Serial.println(GoalBh);
      }
    }
    Serial.println("--------");
  }
};
