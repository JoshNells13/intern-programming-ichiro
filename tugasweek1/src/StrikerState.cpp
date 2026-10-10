#include "StrikerState.hpp"
#include "Ball.hpp"
#include "Exceptions.hpp"
#include "Field.hpp"
#include "Striker.hpp"
#include <algorithm>
#include <cmath>

static int searchCount = 0;
static int waypointIdx = 0;

void SearchState::handle(Striker &striker, Ball &ball) {
  if (striker.isBallVisible()) {
    searchCount = 0;
    waypointIdx = 0;
    striker.changeState(new ApproachState());
    return;
  }

  searchCount++;
  // Putar robot 90 derajat setiap tick untuk menyapu pandangan 360 derajat
  striker.rotateTowards(striker.getOrientation() + 90.0, 90.0);

  // Setelah berputar penuh 360 derajat di satu titik (4 ticks), jelajahi titik
  // patroli lapangan
  if (searchCount % 4 == 0) {
    static const Vector2D waypoints[] = {
        Vector2D(0.0, 1.5),  Vector2D(2.0, 1.5),   Vector2D(2.0, -1.5),
        Vector2D(0.0, -1.5), Vector2D(-2.5, -1.5), Vector2D(-2.5, 1.5),
        Vector2D(-1.0, 0.0)};
    const int numWaypoints = sizeof(waypoints) / sizeof(waypoints[0]);
    Vector2D targetWp = waypoints[waypointIdx % numWaypoints];
    Vector2D pos = striker.getPosition();
    Vector2D diff = targetWp - pos;

    if (diff.length() < 0.6) {
      waypointIdx++;
    } else {
      double nextX =
          pos.x + (diff.x > 0.2 ? 0.5 : (diff.x < -0.2 ? -0.5 : 0.0));
      double nextY =
          pos.y + (diff.y > 0.2 ? 0.5 : (diff.y < -0.2 ? -0.5 : 0.0));
      striker.setPosition(nextX, nextY);
    }
  }
}

static int lostBallCount = 0;

void ApproachState::handle(Striker &striker, Ball &ball) {
  if (!striker.isBallVisible()) {
    lostBallCount++;
    if (lostBallCount >= 3) {
      lostBallCount = 0;
      striker.changeState(new SearchState());
      return;
    }
  } else {
    lostBallCount = 0;
  }

  Vector2D bPos = striker.isBallVisible() ? ball.getPosition()
                                          : striker.getLastKnownBallPos();
  int rRow, rCol, bRow, bCol;
  Field::worldToGrid(striker.getPosition(), rRow, rCol);
  Field::worldToGrid(bPos, bRow, bCol);

  int targetRow = bRow;
  int targetCol = std::max(0, bCol - 1);

  // Jika robot sudah berada tepat di posisi tembak belakang bola
  if (rRow == targetRow && rCol == targetCol) {
    striker.setOrientation(0.0); // Hadapkan ke kanan (0 deg) ke arah gawang
    striker.changeState(new AlignState());
    return;
  }

  // Jika robot berada di depan bola (rCol >= bCol) dan berada di baris yang
  // sama, lakukan manuver menghindar ke samping agar tidak menabrak bola
  if (rCol >= bCol && rRow == bRow) {
    if (rRow > 0) {
      striker.setOrientation(90.0); // Geser ke atas
      striker.moveForward(0.5);
    } else {
      striker.setOrientation(270.0); // Geser ke bawah
      striker.moveForward(0.5);
    }
    return;
  }

  // Jika robot berada di sebelah kiri atau sejajar target, samakan baris
  // terlebih dahulu agar saat bergerak mendekat robot selalu menghadap lurus ke
  // arah bola
  if (rRow < targetRow) {
    striker.setOrientation(270.0);
    striker.moveForward(0.5);
  } else if (rRow > targetRow) {
    striker.setOrientation(90.0);
    striker.moveForward(0.5);
  } else if (rCol < targetCol) {
    striker.setOrientation(0.0);
    striker.moveForward(0.5);
  } else if (rCol > targetCol) {
    striker.setOrientation(180.0);
    striker.moveForward(0.5);
  }
}

void AlignState::handle(Striker &striker, Ball &ball) {
  int rRow, rCol, bRow, bCol;
  Field::worldToGrid(striker.getPosition(), rRow, rCol);
  Field::worldToGrid(ball.getPosition(), bRow, bCol);

  // Pastikan robot menghadap kanan (0 deg) dan bola tepat 1 petak di depan
  // robot
  if (rRow == bRow && rCol + 1 == bCol) {
    striker.setOrientation(0.0);
    striker.changeState(new KickState());
  } else {
    striker.changeState(new ApproachState());
  }
}

void KickState::handle(Striker &striker, Ball &ball) {
  if (!striker.isBallInFront()) {
    throw InvalidKickException();
  }

  Vector2D bPos = ball.getPosition();
  Vector2D kickDir(1.0, 0.0);
  std::string kickName;

  bool canScoreStraight = (bPos.y >= -1.2 && bPos.y <= 1.2);

  if (canScoreStraight) {

    kickDir = Vector2D(1.0, 0.0);
    kickName = "LURUS (ROOK ➔) [AI R: Bola sejajar gawang, lurus pasti masuk!]";
  } else {

    Vector2D goalTarget(4.5, 0.0);
    kickDir = (goalTarget - bPos).normalized();

    if (bPos.y > 1.2) {
      kickName = "DIAGONAL GAJAH (BISHOP ↘) [AI R: Kalau lurus meleset, belok "
                 "serong ke gawang!]";
    } else {
      kickName = "DIAGONAL GAJAH (BISHOP ↗) [AI R: Kalau lurus meleset, belok "
                 "serong ke gawang!]";
    }
  }

  striker.setLastKickType(kickName);

  // Hitung kecepatan tendangan terukur agar bola meluncur sampai ke dalam
  // gawang
  double dist = (Vector2D(4.5, 0.0) - bPos).length();
  double requiredSpeed = 3.0;
  while ((requiredSpeed * (requiredSpeed + 1.0) / 2.0) < dist + 0.5) {
    requiredSpeed += 1.0;
  }

  ball.kick(kickDir, requiredSpeed);

  // Setelah menendang, kembali ke ApproachState untuk memantau bola
  striker.changeState(new ApproachState());
}
