#include <bits/stdc++.h>
using namespace std;

// -------------------- CONSTANTS --------------------

const double h = 0.66 - 0.66;   // goal height relative to shooter
const double m = 0.21;         // ball mass (kg)
const double dt = 0.01;
const double g = 9.81;
const double rho = 1.225;
const double dragCoefficient = 0.2;
const double radius = 0.09;    // ball radius (m)
const double PI = 3.14159265358979323846;

const double simulationTime = 6.0;
const double desiredHitAccuracy = 0.05;
const double extraHeightFromHub = 0.3;

// Shooter model
const double hoodSpeedRatio = 0.5;              // hood wheel = 0.5 * main
const double wheelToBallVelocityRatio = 0.85;   // slip/compression loss
const double magnusSlope = 0.6;                 // lift slope coefficient

// Search ranges
const double minDistance = 1.0;
const double maxDistance = 13.0;
const double distanceStep = 0.5;

// const double minRadialVelocity = 0.0;
// const double maxRadialVelocity = 0.0;
// const double radialVelocityStep = 0.0;

const double minAngle = 52;
const double maxAngle = 86;
const double angleStep = 0.5;

const double minMainWheelSpeed = 2.0;   // m/s
const double maxMainWheelSpeed = 25.0;
const double mainWheelSpeedStep = 0.05;

const double velocityInaccuracy = 0.2;   // m/s
const double angleInaccuracy = 0.1;      // deg

const double velocityRobustnessCoefficient = 10;
const double angleRobustnessCoefficient = 2;
const double heightRobustnessCoefficient = 10.0;

// ---------------------------------------------------

struct SimRes {
    bool hit;
    double xError;
    double maxHeight;
    double tof;
};

// ---------------------------------------------------

void saveToCSV(const vector<vector<double>>& solutions, const string& filename) {
    ofstream file(filename);
    file << "distance,radialVelocity,solutionVelocity,solutionAngle,robustness,tof\n";
    file << fixed << setprecision(5);

    for (const auto& row : solutions) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i + 1 < row.size()) file << ",";
        }
        file << "\n";
    }
    file.close();
}

// ---------------------------------------------------

pair<double, double> computeForces(pair<double,double> vel, double ballSpin) {
    pair<double,double> fg = {0, -m * g};

    double velMag = hypot(vel.first, vel.second);
    if (velMag < 1e-6) return fg;

    double area = PI * radius * radius;

    // ---- DRAG ----
    double dragMag = 0.5 * rho * dragCoefficient * area * velMag * velMag;
    pair<double,double> fd = {
        -dragMag * vel.first / velMag,
        -dragMag * vel.second / velMag
    };

    // ---- MAGNUS ----
    pair<double,double> vPerp = {
        -vel.second / velMag,
         vel.first / velMag
    };

    double spinRatio = (ballSpin * radius) / velMag;
    spinRatio = min(spinRatio, 0.6);  // realistic saturation

    double Cl = magnusSlope * spinRatio;

    double liftMag = 0.5 * rho * area * velMag * velMag * Cl;

    pair<double,double> fm = {
        liftMag * vPerp.first,
        liftMag * vPerp.second
    };

    return {
        fg.first + fd.first + fm.first,
        fg.second + fd.second + fm.second
    };
}

// ---------------------------------------------------

SimRes simulate(double mainWheelSpeed,
                double hoodAngle,
                double radialVel,
                double d)
{
    // Wheel surface speeds (m/s)
    double vMain = mainWheelSpeed;
    double vHood = hoodSpeedRatio * vMain;

    // Ball exit velocity
    // Uses average wheel speed instead of only the main wheel
    double velMag =
        ((vMain + vHood) / 2.0) *
        wheelToBallVelocityRatio;

    // Ball spin (rad/s)
    // Derived from:
    // V + ωR = vMain
    // V - ωR = vHood
    double ballSpin =
        (vMain - vHood) /
        (2.0 * radius);

    pair<double,double> pos = {0, 0};

    pair<double,double> vel = {
        velMag * cos(hoodAngle * PI / 180.0) + radialVel,
        velMag * sin(hoodAngle * PI / 180.0)
    };

    double maxHeight = 0;
    pair<double,double> lastPos = pos;
    double xError = -d;

    for (double t = 0; t < simulationTime; t += dt) {

        lastPos = pos;

        auto f = computeForces(vel, ballSpin);

        pair<double,double> a = {
            f.first / m,
            f.second / m
        };

        vel.first += a.first * dt;
        vel.second += a.second * dt;

        pos.first += vel.first * dt;
        pos.second += vel.second * dt;

        maxHeight = max(maxHeight, pos.second);

        if (lastPos.second >= h &&
            pos.second <= h &&
            vel.second < 0)
        {
            double l = lastPos.second - h;
            double k = h - pos.second;

            double crossX =
                (lastPos.first * k +
                 pos.first * l) /
                (l + k);

            xError = crossX - d;

            bool isHit =
                abs(xError) < desiredHitAccuracy &&
                maxHeight >= h + extraHeightFromHub;

            return {
                isHit,
                xError,
                maxHeight,
                t
            };
        }

        if (pos.second < -1) {
            return {
                false,
                xError,
                maxHeight,
                t
            };
        }
    }

    return {
        false,
        xError,
        maxHeight,
        simulationTime
    };
}

// ---------------------------------------------------

int main() {
    vector<vector<double>> solutions;

    for (double distance = minDistance;
         distance <= maxDistance;
         distance += distanceStep)
    {
        constexpr double radialVel = 0.0;

        double bestRobustness = 1e9;
        SimRes best{false, 0, 0, 0};
        double bestSpeed = 0;
        double bestAngle = 0;

        for (double mainSpeed = minMainWheelSpeed;
             mainSpeed <= maxMainWheelSpeed;
             mainSpeed += mainWheelSpeedStep)
        {
            for (double angle = minAngle;
                 angle <= maxAngle;
                 angle += angleStep)
            {
                auto cur = simulate(mainSpeed, angle, radialVel, distance);
                if (!cur.hit)
                    continue;

                double velRob =
                    (simulate(mainSpeed + velocityInaccuracy, angle, radialVel, distance).xError -
                     simulate(mainSpeed - velocityInaccuracy, angle, radialVel, distance).xError)
                    / (2 * velocityInaccuracy);

                double angRob =
                    (simulate(mainSpeed, angle + angleInaccuracy, radialVel, distance).xError -
                     simulate(mainSpeed, angle - angleInaccuracy, radialVel, distance).xError)
                    / (2 * angleInaccuracy);

                double robustness =
                    velocityRobustnessCoefficient * velRob * velRob +
                    angleRobustnessCoefficient * angRob * angRob +
                    heightRobustnessCoefficient * abs(cur.maxHeight - h);

                if (robustness < bestRobustness) {
                    bestRobustness = robustness;
                    best = cur;
                    bestSpeed = mainSpeed;
                    bestAngle = angle;
                }
            }
        }

        if (best.hit) {
            solutions.push_back({
                distance,
                0.0,
                bestSpeed,
                bestAngle,
                bestRobustness,
                best.tof
            });
        }
    }

    saveToCSV(solutions, "fetchingSolutions.csv");
}