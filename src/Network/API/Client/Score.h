//
// Created by pnavratil on 5/5/17.
//

#ifndef PV264_PROJECT_SCORE_H
#define PV264_PROJECT_SCORE_H

struct Score {
  Score() = default;

  Score(int trueTeam, int falseTeam) : team1(trueTeam), team2(falseTeam) {}

  int team1;
  int team2;
};

#endif // PV264_PROJECT_SCORE_H
