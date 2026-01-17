#include <bits/stdc++.h>
using namespace std;

const double h = 1.82 - 0.35; // 2.64 - shooter height
const double m = 0.21;
const double dt = 0.05; // s
const double velocityRobustnessCoefficient = 2;
const double angleRobustnessCoefficient = 60;
const double velocityInaccuracy = 0.5; // m/s
const double angleInaccuracy = 2; // deg
const double g = 9.81;
const double rho = 1.225;
const double dragCoefficient = 0.2;
const double radius = 0.09;
const double desiredHitAccuracy = 0.05;
const double PI = 3.14159265358979323846;
const double simulationTime = 6.0;
const double extraHeightFromHub = 0.2;
const double minDistance = 0.0;
const double maxDistance = 8;
const double distanceStep = 0.15;
const double minRadialVelocity = -4.0;
const double maxRadialVelocity = 4.0;
const double radialVelocityStep = 0.5;
const double minAngle = 1;
const double maxAngle = 130;
const double angleStep = 1;
const double minVelocity = 2.0;
const double maxVelocity = 17.0;
const double velocityStep = 0.5;

const double robustnessThreshhold = 100;

struct SimRes {
    bool hit;
    double xError;
    double maxHeight;
};

// Save all found solutions to CSV
void saveToCSV(const vector<vector<double>>& solutions, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }
    file << "distance,radialVelocity,solutionVelocity,solutionAngle,robustness\n";
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

// Detects if the ball passes near the goal
bool hit(pair<double, double> pos, double d) {
    return (abs(pos.second - h) < 0.2 && abs(pos.first - d) < desiredHitAccuracy);
}

// Compute net forces (gravity + drag)
pair<double, double> computeForces(pair<double, double> vel) {
    pair<double, double> fg = {0, -m * g};
    double velMag = hypot(vel.first, vel.second);
    if (velMag == 0) return fg; // prevent NaN
    pair<double, double> vHat = {vel.first / velMag, vel.second / velMag};
    double dragMag = rho * velMag * velMag * dragCoefficient * radius * radius * PI / 2;
    pair<double, double> fd = {-dragMag * vHat.first, -dragMag * vHat.second};
    return {fg.first + fd.first, fg.second + fd.second};
}

// Run a single trajectory simulation
SimRes simulate(double velMag, double velAngle, double radialVel, double d) {
    pair<double, double> pos = {0, 0};
    pair<double, double> vel = {
        velMag * cos(velAngle * PI / 180.0) + radialVel,
        velMag * sin(velAngle * PI / 180.0)
    };
    double maxHeight = 0;
    pair<double, double> lastPos = pos;
    double xError = -d;

    for (double t = 0; t < simulationTime; t += dt) {
        lastPos = pos;
        auto a = computeForces(vel);
        a = {a.first / m, a.second / m};
        pos.first += vel.first * dt;
        pos.second += vel.second * dt;
            vel.first += a.first * dt;
        vel.second += a.second * dt;

        maxHeight = max(maxHeight, pos.second);

        // If ball crosses goal height, estimate xError
        if (lastPos.second >= h && pos.second <= h && vel.second < 0) {
            double l = lastPos.second - h; // last
            double k = h - pos.second; // pos
            double crossX = (lastPos.first * k + pos.first * l) / (l+k);
            xError = crossX - d;
            if(hit({crossX, h}, d) && maxHeight >= h + extraHeightFromHub) {
                return {true, xError, maxHeight};
            } 
            else {
                return {false, xError, maxHeight};
            }
        }

        if (pos.second < -1) return {false, xError, maxHeight};
        // if (hit(pos, d)) {
        //     if (maxHeight >= h + extraHeightFromHub) {
        //         return {true, xError, maxHeight};
        //     } else {
        //         return {false, xError, maxHeight}; // too flat, even if it hit
        //     }
        // }
    }
    return {false, xError, maxHeight};
}

int main() {
    vector<vector<double>> solutions;

    #pragma omp parallel
    {
        vector<vector<double>> localSolutions;

        #pragma omp for collapse(2) schedule(dynamic)
        for (int i = 0; i < (int)((maxDistance - minDistance) / distanceStep) + 1; i++) {
            for (int j = 0; j < (int)((maxRadialVelocity - minRadialVelocity) / radialVelocityStep) + 1; j++) {
                double distance = minDistance + i * distanceStep;
                double radialVel = minRadialVelocity + j * radialVelocityStep;

                double minRobustness = 1e9;
                SimRes best = {false, -1, -1};
                double bestVel = 0, bestAngle = 0;

                for (double velMag = minVelocity; velMag < maxVelocity; velMag += velocityStep) {
                    for (double velAngle = minAngle; velAngle < maxAngle; velAngle += angleStep) {
                        auto cur = simulate(velMag, velAngle, radialVel, distance);
                        if (!cur.hit) continue;

                        double velocityRobustness =
                            (simulate(velMag + velocityInaccuracy, velAngle, radialVel, distance).xError -
                             simulate(velMag - velocityInaccuracy, velAngle, radialVel, distance).xError) /
                            (2 * velocityInaccuracy);
                            // pow(simulate(velMag + velocityInaccuracy, velAngle, radialVel, distance).xError, 2) +
                            // pow(simulate(velMag - velocityInaccuracy, velAngle, radialVel, distance).xError, 2);

                        double angleRobustness =
                            (simulate(velMag, velAngle + angleInaccuracy, radialVel, distance).xError -
                             simulate(velMag, velAngle - angleInaccuracy, radialVel, distance).xError) /
                            (2 * angleInaccuracy);
                            // pow(simulate(velMag, velAngle + angleInaccuracy, radialVel, distance).xError, 2) +
                            // pow(simulate(velMag, velAngle - angleInaccuracy, radialVel, distance).xError, 2);
                        double robustness =
                            angleRobustnessCoefficient * angleRobustness * angleRobustness +
                            velocityRobustnessCoefficient * velocityRobustness * velocityRobustness +
                            6 * (abs(cur.maxHeight > 0 ? cur.maxHeight : 500)-h);
                            //  + abs(0.5 * cur.xError);

                        if (robustness < minRobustness) {
                            minRobustness = robustness;
                            best = cur;
                            bestVel = velMag;
                            bestAngle = velAngle;
                        }
                    }
                }

                if (best.hit) {
                    localSolutions.push_back({distance, radialVel, bestVel, bestAngle, minRobustness});
                }
            }
        }

        #pragma omp critical
        {
            solutions.insert(solutions.end(), localSolutions.begin(), localSolutions.end());
        }
    }

    saveToCSV(solutions, "shootingSolutions2.csv");
}
